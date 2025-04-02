#ifndef __LCD_LOW_H__
#define __LCD_LOW_H__
//============================================================================
// LCD SPI & control lines
//   ARD      | Port | LCD
// -----------+------+-------------------------
//  #7/D7     |  PD7 | SD_CS      (no SD in this demo)
//  #8/D8     |  PB0 | LCD_RS
//  #9/D9     |  PB1 | LCD_RESET
// #10/D10    |  PB2 | LCD_CS_NOT   (or SPI SS)
// #11/D11    |  PB3 | LCD_MOSI/DB7 (hardware SPI)
// #12/D12    |  PB4 | not used     (would be MISO)
// #13/D13    |  PB5 | LCD_SCK/DB6  (hardware SPI)
//
// The NT7534 datasheet recommends tying DB0-DB5 to VCC (3.3v) or ground.
// DB0-DB5 appear to have ~12K pull-up to VCC, so to mimimize current
// consumption and still follow the advice of the controller datasheet,
// you would want to tie the unused data pins to VCC.
//

#define CLR_RS    (PORTB &= ~(0x01))
#define SET_RS    (PORTB |=  (0x01))
#define CLR_RESET (PORTB &= ~(0x02))
#define SET_RESET (PORTB |=  (0x02))
#define CLR_CS    (PORTB &= ~(0x04))
#define SET_CS    (PORTB |=  (0x04))
#define CLR_MOSI  (PORTB &= ~(0x08))
#define SET_MOSI  (PORTB |=  (0x08))
#define CLR_SCK   (PORTB &= ~(0x20))
#define SET_SCK   (PORTB |=  (0x20))

//PD.7
#define PIN_TIME   (7)
#define CLR_TIME   (PORTD &= ~(0x80))
#define SET_TIME   (PORTD |=  (0x80))

// Define the display type
#define CFAG12864T3 (0)
#define CFAG12864T4 (0)
#define CFAG12864U3 (0)
#define CFAG12864U4 (1)

#define display_type CFAG12864U4
//////////////////////////

#define HRES 128
#define VRES 64

//============================================================================
void SPI_sendCommand(uint8_t command);
void SPI_sendData(uint8_t data);
void Set_Address(uint8_t column, uint8_t page);
void Set_Static_Indicators(uint16_t state_mask);
void Set_Contrast(uint8_t contrast);
void Initialize_CFAG12864T2U2(void);
//============================================================================
#endif //  __LCD_LOW_H__
