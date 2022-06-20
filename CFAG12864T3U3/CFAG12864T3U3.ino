//===========================================================================
//
//  !! IMPORTANT !!
//
//  The CFAG12864T3 and CFAG12864U3 are a 3.3v devices. You need a 3.3v
//  Arduino to operate this code properly. We used a seeedunio v4.2 set
//  to 3.3v:
//
//  http://www.seeedstudio.com/item_detail.html?p_id=2517
//
//===========================================================================
//
// Code written for Seeeduino v4.2 runnung at 3.3v
//
// CFAG12864T3 CFAG12864U3 128x64 LCD in SPI mode
//
//  ref: https://www.crystalfontz.com/product/CFAG12864T3
//
//    Small, backlit:      https://www.crystalfontz.com/product/cfag12864t3tfh
//    Small, no backlight: https://www.crystalfontz.com/product/cfag12864t3nfh
//    Large, backlit:      https://www.crystalfontz.com/product/cfag12864u3tfh
//    Large, no backlight: https://www.crystalfontz.com/product/cfag12864u3nfh
//
//
// 2017 - 06 - 15 Brent A. Crosby
// 2019 - 05 - 01 Trevin Jorgenson
// 2022 - 06 - 20 Kelsey Zaches
//
// Crystalfontz America, Inc. http://www.crystalfontz.com
//===========================================================================
// This code can also be found on GitHub:
//
//===========================================================================
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
//
//  For Pin Connection information, see "LCD_low.h"
//
//===========================================================================

#include <SPI.h>

#include "LCD_low.h"
#include "LCD_draw.h"

//----------------------------------------------------------------------------
void Line_Demo_1(void)
{
  uint8_t
      x;
  uint8_t
      y;

  for (x = 0; x <= 127; x += 2)
  {
    LCD_Line(63, 31,
             x, 0,
             1);
    Send_Framebuffer_To_Display();
  }

  for (y = 0; y <= 63; y += 2)
  {
    LCD_Line(63, 31,
             127, y,
             1);
    Send_Framebuffer_To_Display();
  }

  for (x = 127; 1 < x; x -= 2)
  {
    LCD_Line(63, 31,
             x, 63,
             1);
    Send_Framebuffer_To_Display();
  }

  for (y = 63; 1 < y; y -= 2)
  {
    LCD_Line(63, 31,
             0, y,
             1);
    Send_Framebuffer_To_Display();
  }
}
//----------------------------------------------------------------------------
void Line_Demo_2(void)
{
  uint8_t
      x;
  uint8_t
      y;

  for (x = 0; x <= 127; x++)
  {
    LCD_Line(63, 31,
             x, 0,
             x & 0x01);
    Send_Framebuffer_To_Display();
  }

  for (y = 0; y <= 63; y++)
  {
    LCD_Line(63, 31,
             127, y,
             y & 0x01);
    Send_Framebuffer_To_Display();
  }

  for (x = 127; 0 < x; x--)
  {
    LCD_Line(63, 31,
             x, 63,
             x & 0x01);
    Send_Framebuffer_To_Display();
  }

  for (y = 63; 0 < y; y--)
  {
    LCD_Line(63, 31,
             0, y,
             y & 0x01);
    Send_Framebuffer_To_Display();
  }
}
//----------------------------------------------------------------------------
void Line_Demo_3(void)
{
  uint8_t
      x;
  uint8_t
      y;

  //Start at left, go CCW to top
  Fill_Framebuffer(0x00, 0x00);
  for (x = 0; x <= 127; x++)
  {
    LCD_Line(0, 63,
             x, 0,
             x & 0x01);
    Send_Framebuffer_To_Display();
  }
  for (y = 0; y <= 63; y++)
  {
    LCD_Line(0, 63,
             127, y,
             y & 0x01);
    Send_Framebuffer_To_Display();
  }

  //Start at top, go CCW to right
  Fill_Framebuffer(0x00, 0x00);
  for (y = 63; 0 < y; y--)
  {
    LCD_Line(127, 63,
             0, y,
             y & 0x01);
    Send_Framebuffer_To_Display();
  }
  for (x = 0; x <= 127; x++)
  {
    LCD_Line(127, 63,
             x, 0,
             x & 0x01);
    Send_Framebuffer_To_Display();
  }

  //Start at right, go CCW to bottom
  Fill_Framebuffer(0x00, 0x00);
  for (x = 127; 0 < x; x--)
  {
    LCD_Line(127, 0,
             x, 63,
             x & 0x01);
    Send_Framebuffer_To_Display();
  }
  for (y = 63; 0 < y; y--)
  {
    LCD_Line(127, 0,
             0, y,
             y & 0x01);
    Send_Framebuffer_To_Display();
  }

  //Start at bottom, go CCW to left
  Fill_Framebuffer(0x00, 0x00);
  for (y = 0; y <= 63; y++)
  {
    LCD_Line(0, 0,
             127, y,
             y & 0x01);
    Send_Framebuffer_To_Display();
  }
  for (x = 127; 0 < x; x--)
  {
    LCD_Line(0, 0,
             x, 63,
             x & 0x01);
    Send_Framebuffer_To_Display();
  }
}
//----------------------------------------------------------------------------
void Line_Demo_4(void)
{
  uint8_t
      x;
  uint8_t
      y;
  uint8_t
      repeat;
#define LINEDMO4DLY (40)
  for (repeat = 0; repeat < 1; repeat++)
  {
    //Start at left, go CCW to top
    for (x = 0; x <= 127; x++)
    {
      Fill_Framebuffer(0x00, 0x00);
      LCD_Line(0, 63,
               x, 0,
               1);
      Send_Framebuffer_To_Display();
      delay(LINEDMO4DLY);
    }
    for (y = 0; y <= 63; y++)
    {
      Fill_Framebuffer(0x00, 0x00);
      LCD_Line(0, 63,
               127, y,
               1);
      Send_Framebuffer_To_Display();
      delay(LINEDMO4DLY);
    }

    //Start at top, go CCW to right
    for (y = 63; 0 < y; y--)
    {
      Fill_Framebuffer(0x00, 0x00);
      LCD_Line(127, 63,
               0, y,
               1);
      Send_Framebuffer_To_Display();
      delay(LINEDMO4DLY);
    }
    for (x = 0; x <= 127; x++)
    {
      Fill_Framebuffer(0x00, 0x00);
      LCD_Line(127, 63,
               x, 0,
               1);
      Send_Framebuffer_To_Display();
      delay(LINEDMO4DLY);
    }

    //Start at right, go CCW to bottom
    for (x = 127; 0 < x; x--)
    {
      Fill_Framebuffer(0x00, 0x00);
      LCD_Line(127, 0,
               x, 63,
               1);
      Send_Framebuffer_To_Display();
      delay(LINEDMO4DLY);
    }
    for (y = 63; 0 < y; y--)
    {
      Fill_Framebuffer(0x00, 0x00);
      LCD_Line(127, 0,
               0, y,
               1);
      Send_Framebuffer_To_Display();
      delay(LINEDMO4DLY);
    }

    //Start at bottom, go CCW to left
    for (y = 0; y <= 63; y++)
    {
      Fill_Framebuffer(0x00, 0x00);
      LCD_Line(0, 0,
               127, y,
               1);
      Send_Framebuffer_To_Display();
      delay(LINEDMO4DLY);
    }
    for (x = 127; 0 < x; x--)
    {
      Fill_Framebuffer(0x00, 0x00);
      LCD_Line(0, 0,
               x, 63,
               1);
      Send_Framebuffer_To_Display();
      delay(LINEDMO4DLY);
    }
  }
}
//----------------------------------------------------------------------------
void Circle_Demo_1(void)
{
  uint8_t
      r;

  for (r = 1; r <= 31; r++)
  {
    Fill_Framebuffer(0x00, 0x00);
    LCD_Circle(31, 31, r, 1);
    LCD_Circle(95, 31, r, 1);
    Send_Framebuffer_To_Display();
    delay(50);
  }
  for (r = 31; 0 < r; r--)
  {
    Fill_Framebuffer(0x00, 0x00);
    LCD_Circle(31 + (31 - r), 31, r, 1);
    LCD_Circle(95 - (31 - r), 31, r, 1);
    Send_Framebuffer_To_Display();
    delay(50);
  }
}
//----------------------------------------------------------------------------
void Rounded_Rectangle_Demo(void)
{
  uint8_t
      r;

  for (r = 1; r <= 31; r++)
  {
    Fill_Framebuffer(0x00, 0x00);
    Rounded_Rect(63 - r - r, 31 - r, 63 + r + r, 31 + r, (r + r + r) >> 2, 1);
    Send_Framebuffer_To_Display();
    delay(50);
  }
  for (r = 1; r <= 63; r++)
  {
    Fill_Framebuffer(0x00, 0x00);
    Rounded_Rect(0, 0, 127 - r - r, 63 - r, (64 - r) >> 1, 1);
    Send_Framebuffer_To_Display();
    delay(50);
  }
}
//----------------------------------------------------------------------------
void Rectangle_Demo(void)
{
  uint8_t
      r;

  for (r = 1; r <= 31; r++)
  {
    Fill_Framebuffer(0x00, 0x00);
    outline_rectangle(63 - r - r, 31 - r, 63 + r + r, 31 + r);
    Send_Framebuffer_To_Display();
    delay(30);
  }
  for (r = 1; r <= 63; r++)
  {
    Fill_Framebuffer(0x00, 0x00);
    outline_rectangle(0, 0, 127 - r - r, 63 - r);
    Send_Framebuffer_To_Display();
    delay(30);
  }
}
//----------------------------------------------------------------------------
void Filled_Rectangle_Demo(void)
{
  uint8_t
      r;

  for (r = 1; r <= 31; r++)
  {
    Fill_Framebuffer(0xAA, 0x55);
    clear_rectangle(63 - r - r, 31 - r, 63 + r + r, 31 + r);
    Send_Framebuffer_To_Display();
    delay(30);
  }
  for (r = 1; r <= 63; r++)
  {
    Fill_Framebuffer(0xAA, 0x55);
    clear_rectangle(0, 0, 127 - r - r, 63 - r);
    Send_Framebuffer_To_Display();
    delay(30);
  }
}
//----------------------------------------------------------------------------
uint8_t
    xlogocrawl;
uint8_t
    xlogocrawldir;
uint8_t
    ylogocrawl;
uint8_t
    ylogocrawldir;
#define CRAWL_MAX_X (27)
#define CRAWL_MAX_Y (43)
void logo_crawl_demo(void)
{
  uint8_t
      crawl;

  //Also demonstrate the static indicators on the U3, this code
  //will be ignored for the T3.
  uint32_t
      mask;
  mask = 0xFFFF0000;

  for (crawl = 0; crawl <= 99 || 1; crawl++)
  {
    //Also demonstrate the static indicators on the U3, this code
    //will be ignored for the T3.
    Set_Static_Indicators(mask);
    if (mask & 0x00000001)
    {
      mask >>= 1;
      mask |= 0x80000000;
    }
    else
    {
      mask >>= 1;
    }

    logo_to_framebuffer();

    //Center the text & an outlining box.
    put_string(xlogocrawl + 1 + 1,
               ylogocrawl + 1 + 8 + 1,
               12,
               "CRYSTALFONTZ");
    put_string(xlogocrawl + 1 + 1,
               ylogocrawl + 1 + 1,
               12,
               "CFAG12864T/U");
    outline_rectangle(xlogocrawl,
                      ylogocrawl,
                      xlogocrawl + 1 + 1 + 12 * 8 + 1 + 1,
                      ylogocrawl + 1 + 1 + 8 * 2 + 1 + 1);
    outline_rectangle(xlogocrawl + 1,
                      ylogocrawl + 1,
                      xlogocrawl + 1 + 1 + 12 * 8 + 1,
                      ylogocrawl + 1 + 1 + 8 * 2 + 1);
    if (0 != xlogocrawldir)
    {
      //X is increasing, max is CRAWL_MAX_X
      if (CRAWL_MAX_X == xlogocrawl)
      {
        //Logo was printed at max x = CRAWL_MAX_X last time. Turn around
        xlogocrawldir = 0;
        //New coordiante
        xlogocrawl = CRAWL_MAX_X - 1;
      }
      else
      {
        xlogocrawl++;
      }
    }
    else
    {
      //X is decreasing, min is 0
      if (0 == xlogocrawl)
      {
        //Logo was printed at min x = 0 last time. Turn around
        xlogocrawldir = 1;
        //New coordiante
        xlogocrawl = 1;
      }
      else
      {
        xlogocrawl--;
      }
    }
    if (0 != ylogocrawldir)
    {
      //Y is increasing, max is CRAWL_MAX_Y
      if (CRAWL_MAX_Y == ylogocrawl)
      {
        //Logo was printed at max y = CRAWL_MAX_Y last time. Turn around
        ylogocrawldir = 0;
        //New coordiante
        ylogocrawl = CRAWL_MAX_Y - 1;
      }
      else
      {
        ylogocrawl++;
      }
    }
    else
    {
      //Y is decreasing, min is 0
      if (0 == ylogocrawl)
      {
        //Logo was printed at min y = 0 last time. Turn around
        ylogocrawldir = 1;
        //New coordiante
        ylogocrawl = 1;
      }
      else
      {
        ylogocrawl--;
      }
    }
    Send_Framebuffer_To_Display();
    delay(200);
  }
  Set_Static_Indicators(0x0000);
}
//============================================================================
void setup(void)
{
  DDRB |= 0x2F;

  //Drive the ports to a reasonable starting state.
  CLR_RESET;
  CLR_RS;
  SET_CS;
  CLR_MOSI;
  CLR_SCK;

  pinMode(PIN_TIME, OUTPUT);

  //debug console
  Serial.begin(115200);
  Serial.println(F("setup()"));

  // Initialize SPI. By default the clock is 4MHz.
  SPI.begin();
  //Bump the clock to 8MHz. Appears to be the maximum.
  SPI.beginTransaction(SPISettings(8000000, MSBFIRST, SPI_MODE0));

  //Fire up the SPI LCD
  Serial.println(F("Initialize_CFAG12864T3U3()"));

  Initialize_CFAG12864T2U2();

#if 0
  //Check current.
  //Use checkerboard, should be highest current draw.
  Fill_Framebuffer(0xAA, 0x55);
  Send_Framebuffer_To_Display();
  delay(2000);
  
  //Drive all ports to 0, except RES
  CLR_RS;
  CLR_CS;
  CLR_MOSI;
  CLR_SCK;
  //DB0-DB5 on the LCD need to be at 3.3v or left floating
  //Spin while we dig out the multi-meter  
  while(1);
  //CFAG12864T3 200uA ~ 300 uA (excluding ~40mA backlight)
  //CFAG12864U3 700uA ~ 800 uA (excluding ~60mA backlight)
#endif

  xlogocrawl = 14;
  xlogocrawldir = 1;
  ylogocrawl = 21;
  ylogocrawldir = 0;
}
//============================================================================
// Set up demos
#define logodemo 1
#define logocral 0
#define rectanglesdemo 1
#define linesdemo 1
#define circledemo 1
#define fillFBdemo 1

void loop(void)
{
  Serial.println(F("loop()"));
  Set_Static_Indicators("0xffff0000");
  logo_to_framebuffer();
#if logodemo
  Send_Framebuffer_To_Display();
  delay(2000);
#endif
//while(1);
#if logocrawl
  logo_crawl_demo();
  delay(500);
#endif

#if rectanglesdemo
  Rectangle_Demo();
  delay(500);
  Rounded_Rectangle_Demo();
  delay(500);
  Filled_Rectangle_Demo();
  Fill_Framebuffer(0x00, 0x00);
  delay(500);
#endif

#if linesdemo
  Line_Demo_1();
  delay(500);
  Line_Demo_2();
  delay(500);
  Line_Demo_3();
  delay(500);
  Line_Demo_4();
  delay(500);
#endif

#if circledemo
  Circle_Demo_1();
  delay(500);
#endif

#if fillFBdemo
  //Push out a few filled screens
  Fill_Framebuffer(0x00, 0x00);
  Send_Framebuffer_To_Display();
  delay(500);

  //Checkerboard odd
  Fill_Framebuffer(0xAA, 0x55);
  Send_Framebuffer_To_Display();
  delay(1000);
  //Checkerboard even
  Fill_Framebuffer(0x55, 0xAA);
  Send_Framebuffer_To_Display();
  delay(1000);
  //Horizontal lines odd
  Fill_Framebuffer(0xAA, 0xAA);
  Send_Framebuffer_To_Display();
  delay(1000);
  //Horizontal lines even
  Fill_Framebuffer(0x55, 0x55);
  Send_Framebuffer_To_Display();
  delay(1000);
  //Vertical lines odd
  Fill_Framebuffer(0xFF, 0x00);
  Send_Framebuffer_To_Display();
  delay(1000);
  //Vertical lines even
  Fill_Framebuffer(0x00, 0xFF);
  Send_Framebuffer_To_Display();
  delay(1000);
  //All on
  Fill_Framebuffer(0xFF, 0xFF);
  Send_Framebuffer_To_Display();
  delay(1000);
  //All off
  Fill_Framebuffer(0x00, 0x00);
  Send_Framebuffer_To_Display();
  delay(500);
 #endif 
}
//============================================================================
