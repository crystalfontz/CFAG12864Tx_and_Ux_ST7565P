//============================================================================
// CFAG12864T3 CFAG12864U3 128x64 LCD in SPI mode
// LCD_low.cpp : Lower-level LCD interface routines
// 2017 - 06 - 15 Brent A. Crosby
// Crystalfontz America, Inc. http://www.crystalfontz.com
//============================================================================
//  This is free and unencumbered software released into the public domain.
//
//  Anyone is free to copy, modify, publish, use, compile, sell, or
//  distribute this software, either in source code form or as a compiled
//  binary, for any purpose, commercial or non-commercial, and by any
//  means.
//
//  In jurisdictions that recognize copyright laws, the author or authors
//  of this software dedicate any and all copyright interest in the
//  software to the public domain. We make this dedication for the benefit
//  of the public at large and to the detriment of our heirs and
//  successors. We intend this dedication to be an overt act of
//  relinquishment in perpetuity of all present and future rights to this
//  software under copyright law.
//
//  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
//  EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
//  MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
//  IN NO EVENT SHALL THE AUTHORS BE LIABLE FOR ANY CLAIM, DAMAGES OR
//  OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
//  ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
//  OTHER DEALINGS IN THE SOFTWARE.
//
//  For more information, please refer to <http://unlicense.org/>
//===========================================================================
#include <Arduino.h>
#include <SPI.h>
// C:\Program Files (x86)\Arduino\hardware\arduino\avr\libraries\SPI\src\SPI.cpp
// C:\Program Files (x86)\Arduino\hardware\arduino\avr\libraries\SPI\src\SPI.h
#include "LCD_low.h"

//===========================================================================
//  The controller is a NT7534. 
//  https://www.crystalfontz.com/controllers/Novatek/NT7534
#define NT7534_00_SET_LOWER_COLUMN_ADDRESS_BIT       (0x00)
#define NT7534_10_SET_UPPER_COLUMN_ADDRESS_BIT       (0x10)
#define NT7534_20_RESISTOR_RATIO_RANGE_SET_BIT       (0x20)
#define NT7534_28_POWER_CONTROL_SET_BIT              (0x28)
#define NT7534_30_PARTIAL_DISPLAY_DUTY_BIT           (0x30)
#define NT7534_38_PARTIAL_DISPLAY_BIAS_BIT           (0x38)
#define NT7534_40_SET_DISPLAY_START_LINE_BIT         (0x40)
#define NT7534_81_CONTRAST_PREFIX                    (0x81)
#define NT7534_82_PARTIAL_DISPLAY_MODE_OFF           (0x82)
#define NT7534_83_PARTIAL_DISPLAY_MODE_ON            (0x83)
#define NT7534_84_INVERSION_BY_FRAME                 (0x84)
#define NT7534_85_INVERSION_BY_NLINE_PREFIX          (0x85)
#define NT7534_A0_SEGMENT_REMAP_NORMAL               (0xA0)
#define NT7534_A1_SEGMENT_REMAP_REVERSE              (0xA1)
#define NT7534_A2_LCD_BIAS_1_9                       (0xA2)
#define NT7534_A3_LCD_BIAS_1_7                       (0xA3)
#define NT7534_A4_ENTIRE_DISPLAY_NORMAL              (0xA4)
#define NT7534_A5_ENTIRE_DISPLAY_FORCE_ON            (0xA5)
#define NT7534_A6_INVERSION_NORMAL                   (0xA6)
#define NT7534_A7_INVERSION_INVERTED                 (0xA7)
#define NT7534_AC_STATIC_INDICATOR_OFF_PREFIX        (0xAC)
#define NT7534_AD_STATIC_INDICATOR_ON_PREFIX         (0xAD)
#define NT7534_00_STATIC_IND_OFF_PARAMETER          (0x00)
#define NT7534_01_STATIC_IND_1S_BLINK_PARAMETER     (0x01)
#define NT7534_02_STATIC_IND_0P5S_BLINK_PARAMETER   (0x02)
#define NT7534_03_STATIC_IND_ON_PARAMETER           (0x03)
#define NT7534_AE_DISPLAY_OFF_SLEEP_YES              (0xAE)
#define NT7534_AF_DISPLAY_ON_SLEEP_NO                (0xAF)
#define NT7534_B0_SET_PAGE_START_ADDRESS_BIT         (0xB0)
#define NT7534_C0_COM_DIRECTION_NORMAL               (0xC0)
#define NT7534_C8_COM_DIRECTION_REVERSE              (0xC8)
#define NT7534_D3_PARTIAL_DISPLAY_START_LINE_PREFIX  (0xD3)
#define NT7534_E0_START_READ_MODIFY_WRITE            (0xE0)
#define NT7534_E2_RESET                              (0xE2)
#define NT7534_E3_NOP                                (0xE3)
#define NT7534_E4_OSC_FREQ_31KHZ                     (0xE4)
#define NT7534_E5_OSC_FREQ_26KHZ                     (0xE5)
#define NT7534_E6_DC_DC_FREQUENCY_PREFIX             (0xE6)
#define NT7534_EE_END_READ_MODIFY_WRITE              (0xEE)
//===========================================================================
void SPI_sendCommand(uint8_t command)
  {
  // Select the LCD's command register
  CLR_RS;
  // Select the LCD controller
  CLR_CS;
  //Send the command via SPI:
  SPI.transfer(command);
  // Deselect the LCD controller
  SET_CS;
  }
//============================================================================
void SPI_sendData(uint8_t data)
  {
  // Select the LCD's data register
  SET_RS;
  // Select the LCD controller
  CLR_CS;
  //Send the data via SPI:
  SPI.transfer(data);
  // Deselect the LCD controller
  SET_CS;
  }
//============================================================================
void Set_Address(uint8_t column, uint8_t page)
  {
  //For some reason the Left-most column of the CFAG12864T3/U2 is at 4. Hmmm.
  column+=4;
  //Set column-lower nibble
  SPI_sendCommand(NT7534_00_SET_LOWER_COLUMN_ADDRESS_BIT|(column&0x0F));
  //Set column-upper nibble
  SPI_sendCommand(NT7534_10_SET_UPPER_COLUMN_ADDRESS_BIT|((column>>4)&0x0F));
  //Set page address, limiting from 0 to 7
  SPI_sendCommand(NT7534_B0_SET_PAGE_START_ADDRESS_BIT|(page&0x0F));
  }
//============================================================================
//Constants for CFAG12864U3 Static Indicator (SI_) bit field
#define SI_LEAF         (0x8000)
#define SI_DOC          (0x4000)
#define SI_BATTERY      (0x2000)
#define SI_BATT_BAR_0   (0x1000)
#define SI_BATT_BAR_1   (0x0800)
#define SI_BATT_BAR_2   (0x0400)
#define SI_COMPUTER     (0x0200)
#define SI_ANTENNA      (0x0100)
#define SI_SPEAKER      (0x0080)
#define SI_SPEAKER_MUTE (0x0040)
#define SI_MAIL         (0x0020)
#define SI_PHONE        (0x0010)
#define SI_BELL         (0x0008)
#define SI_CLOCK        (0x0004)
#define SI_WARNING      (0x0002)
#define SI_SYNC         (0x0001)
//----------------------------------------------------------------------------
const uint8_t Static_Indicator_Columns[16] PROGMEM =
  {0x03, //SI_LEAF
   0x0A, //SI_DOC
   0x14, //SI_BATTERY
   0x11, //SI_BATT_BAR_0
   0x12, //SI_BATT_BAR_1
   0x13, //SI_BATT_BAR_2
   0x20, //SI_COMPUTER
   0x2F, //SI_ANTENNA
   0x3A, //SI_SPEAKER
   0x3D, //SI_SPEAKER_MUTE
   0x46, //SI_PHONE
   0x50, //SI_MAIL
   0x5B, //SI_BELL
   0x66, //SI_CLOCK
   0x71, //SI_WARNING
   0x7B};//SI_SYNC
//----------------------------------------------------------------------------
void Set_Static_Indicators(uint16_t state_mask)
  {
//There are no static indicators on the CFAG12864T3
#if (display_type == CFAG12864U3)    
  uint16_t
    mask;
  uint8_t
    indicator;
  
  for(mask=0x8000,indicator=0;mask;mask>>=1,indicator++)
    {
    Set_Address(pgm_read_byte(&Static_Indicator_Columns[indicator]),0x08);
    if(mask&state_mask)
      {
      //Set indicator to on.
      SPI_sendData(0xFF);
      }
   else      
      {
      //Clear indicator to off.
      SPI_sendData(0x00);
      }
    }
#endif
  }
//============================================================================
void Set_Contrast(uint8_t contrast)
  {
  //Set the "contrast" (brightness, max determined by IREF current)
  SPI_sendCommand(NT7534_81_CONTRAST_PREFIX);
  SPI_sendCommand(contrast);
  }
//============================================================================
void Initialize_CFAG12864T2U2(void)
  {
  //Thump the hardware reset line.
  _delay_ms(1);
  CLR_RESET;
  _delay_ms(1);
  SET_RESET;
  _delay_ms(10);
  SPI_sendCommand(NT7534_E2_RESET);
  _delay_ms(10);
  
  SPI_sendCommand(NT7534_A1_SEGMENT_REMAP_REVERSE); //set ADC
  SPI_sendCommand(NT7534_C0_COM_DIRECTION_NORMAL); //set commonn scan 
  SPI_sendCommand(NT7534_A2_LCD_BIAS_1_9); //set lcd bias1/9

#if (display_type == CFAG12864T3)
  //Set the resistor ratio range (0-7) so that the contrast is near
  //the middle of its 0-63 range.
  SPI_sendCommand(NT7534_20_RESISTOR_RATIO_RANGE_SET_BIT | 0x04);
  //The contrast has a range of 0-63.
  //For the CFAG12864T3 Contrast of 35 looks pretty good.
  SPI_sendCommand(NT7534_81_CONTRAST_PREFIX);
  SPI_sendCommand(35); 
#endif

#if (display_type == CFAG12864U3)
  //Set the resistor ratio range (0-7) so that the contrast is near
  //the middle of its 0-63 range.
  SPI_sendCommand(NT7534_20_RESISTOR_RATIO_RANGE_SET_BIT | 0x04);
  //The contrast has a range of 0-63.
  //For the CFAG12864T3 Contrast of 35 looks pretty good.
  SPI_sendCommand(NT7534_81_CONTRAST_PREFIX);
  SPI_sendCommand(24); 
#endif

  SPI_sendCommand(NT7534_28_POWER_CONTROL_SET_BIT | 0x07);
  SPI_sendCommand(NT7534_40_SET_DISPLAY_START_LINE_BIT | 0x00);
  SPI_sendCommand(NT7534_AF_DISPLAY_ON_SLEEP_NO);
  SPI_sendCommand(NT7534_A6_INVERSION_NORMAL);
  SPI_sendCommand(NT7534_A4_ENTIRE_DISPLAY_NORMAL);
  }
//============================================================================

