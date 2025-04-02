//============================================================================
// CFAG12864T3 CFAG12864U3 128x64 LCD in SPI mode
// LCD_draw.cpp : Higher-level LCD drawing routines
// 2017 - 06 - 15 Brent A. Crosby
// 2019 - 05 - 02 Trevin Jorgenson
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
//============================================================================
#include <Arduino.h>
#include <SPI.h>
#include "fnt08x08.h"
#include "LCD_low.h"
#include "LCD_draw.h"
#include "images.h"
//============================================================================
// There is limited memory on the Arduino, so we can have the SD card or
// we could have a RAM display buffer, but not both.
uint8_t
  framebuffer[8][128];
//============================================================================
void Fill_Framebuffer(uint8_t data1, uint8_t data2)
  {
  uint16_t
    count;
  uint8_t
    *target;
  target=&framebuffer[0][0];
  for(count=0;count<512;count++)
    {
    *target=data1;
    target++;
    *target=data2;
    target++;
    }              
  }
//============================================================================
void Send_Framebuffer_To_Display(void)
  {
#if 0
  //simple 2.57mS flash 2952 ram 1211
  uint8_t
    page;
  uint8_t
    column;
  for(page=0;page<8;page++)
    {
    //Set the LCD to the left of this line.
    Set_Address(0,page);
    //Move across the columns, sending the data.
    for(column=0;column<128;column++)
      {
      SPI_sendData(framebuffer[page][column]);
      }
    }
#endif

#if 0
  //Optimized pointer 2.32mS flash 2588 ram 1211
  uint8_t
    page;
  uint8_t
    column;
  uint8_t
    *source;
  source=&framebuffer[0][0];        
  for(page=0;page<8;page++)
    {
    //Set the LCD to the left of this line.
    Set_Address(0,page);
    //Move across the columns, alternating the two data
    //bytes.
    for(column=0;column<128;column++)
      {
      SPI_sendData(*source);
      source++;
      }
    }
#endif

#if 1
  //Optimized pointer, plus unwrap SPI 1.94mS flash 2588 ram 1211
  uint8_t
    page;
  uint8_t
    column;
  uint8_t
    *source;
  source=&framebuffer[0][0];        
  for(page=0;page<8;page++)
    {
    //Set the LCD to the left of this line.
    Set_Address(0,page);
    //Move across the columns, alternating the two data
    //bytes.
    // Select the LCD's data register
    SET_RS;
    // Select the LCD controller
    CLR_CS;
    for(column=0;column<128;column++)
      {
      //Send the data via SPI:
      SPI.transfer(*source);
      source++;
      }
    // Deselect the LCD controller
    SET_CS;
    }
#endif
  }
//============================================================================

//---------------------------------------------------------------------------- 
void logo_to_framebuffer(void)
{
  uint8_t
    column;
  uint8_t
    page;
  uint8_t
    i;
  uint8_t
    j;

  uint8_t pixels;
  uint8_t theByte;
  uint16_t coordinate;

  for (page = 0; page <= 7; page++)
  {
    for (column = 0; column < 128 / 8; column++)
    {
      for (i = 0; i < 8; i++)
      {
        pixels = 0;
        for (j = 0; j < 8; j++)
        {
          // First determine the coordinate of the byte we wish to read from
          coordinate = column + ((page * 8) + j)*HRES / 8;
          Serial.println(coordinate);
          // Read the byte
          theByte = pgm_read_byte(&NFH_Mono_1BPP[coordinate]);
          // Determine which bit we need to keep and put it in the correct spot
          pixels |= (((theByte << i) & 0x80) >> (7 - j));
        }
        framebuffer[page][column*8+i] = pixels;
      }
    }
  }
}
//============================================================================
void Put_Pixel(uint8_t x, uint8_t y, uint8_t set)
  {
  //2.48uS ~ 4.70uS
  if(0 != set)
    {
    //Setting the bit
    framebuffer[y>>3][x]|=(0x01 << (y&0x07));
    }
  else
    {
    //Clearing the bit
    framebuffer[y>>3][x]&=~(0x01 << (y&0x07));
    }
  }
//============================================================================
// From: http://en.wikipedia.org/wiki/Midpoint_circle_algorithm
void LCD_Circle(uint8_t x0, uint8_t y0, uint8_t radius, uint8_t set)
  {
  uint8_t
    x;
  uint8_t
    y;
  int8_t
    radiusError;

  x = radius;
  y = 0;
  radiusError = 1 - (int8_t) x;

  while (x >= y)
    {
    //11 O'Clock
    Put_Pixel(x0 - y, y0 + x, set);
    //1 O'Clock
    Put_Pixel(x0 + y, y0 + x, set);
    //10 O'Clock
    Put_Pixel(x0 - x, y0 + y, set);
    //2 O'Clock
    Put_Pixel(x0 + x, y0 + y, set);
    //8 O'Clock
    Put_Pixel(x0 - x, y0 - y, set);
    //4 O'Clock
    Put_Pixel(x0 + x, y0 - y, set);
    //7 O'Clock
    Put_Pixel(x0 - y, y0 - x, set);
    //5 O'Clock
    Put_Pixel(x0 + y, y0 - x, set);

    y++;
    if (radiusError < 0)
      {
      radiusError += (int16_t)(2 * y + 1);
      }
    else
      {
      x--;
      radiusError += 2 * (((int16_t) y - (int16_t) x) + 1);
      }
    }
  }
//============================================================================
typedef union
  {
  uint8_t
    as_bytes[2];
  uint16_t
    as_word;
  }WORD_UNION;

void put_string(uint8_t x, uint8_t y, uint8_t Field_Width, const char *input)
  {
  register uint8_t
    Terminator_Found;
  register uint8_t
    Characters_Placed;
  register uint8_t
    this_character;
  register uint8_t
    *LCD_Memory;
  register uint8_t
    column;
  register uint8_t
    row;
  WORD_UNION
    Clearing_Mask;
  WORD_UNION
    Pixel_Data;

  //Get the first row of the display character.
  row=y>>3;
  //Calculate the address of the first uint8_t in display in LCD_Memory
  LCD_Memory=&framebuffer[row][x];

  //Calculate Clearing_Mask, the vertical mask that we will and with
  //LCD_Memory to clear the space before we or in the data from the
  //font. It is 9 pixels.
  Clearing_Mask.as_word=~(0x01FF<<(y&0x07));

  //Clear the first col to the left of the string.
  LCD_Memory[0]&=Clearing_Mask.as_bytes[0];
  if(row<7)
    LCD_Memory[128]&=Clearing_Mask.as_bytes[1];
  LCD_Memory++;

  //Initialize Terminator_Found.
  Terminator_Found=0;
  //Move across the field. We will either put the character or a blank
  //in every position of Field_Width.
  for(Characters_Placed=0;Characters_Placed<Field_Width;Characters_Placed++)
    {
    //If we have not passed the terminator, then get the next
    //character in the string. If we find the terminator,
    //remember that we are out of characters.
    if(!Terminator_Found)
      {
      this_character=*input++;
      if(!this_character)
        {
        Terminator_Found=1;
        this_character=' ';
        }
      }
    else
      this_character=' ';
    //Get a pointer into the font information for this
    //character.

    //Write the eight columns of this character.
    for(column=0;column<=7;column++)
      {
      //Clear the correct bits in this row and the next row down.
      LCD_Memory[0]&=Clearing_Mask.as_bytes[0];
      if(row<7)
        {
        LCD_Memory[128]&=Clearing_Mask.as_bytes[1];
        }
      //Get the font data, convert it to a word and shift it down. Leave
      //one blank row of pixels above as a spacer.
      Pixel_Data.as_word=((uint16_t)(pgm_read_byte(&Font_08x08[(this_character-FONT_08X08_BASE)][column])))<<((y&0x07));
      
      //Set the correct bits in this row and the next row down.
      LCD_Memory[0]|=Pixel_Data.as_bytes[0];
      if(row<7)
        {
        LCD_Memory[128]|=Pixel_Data.as_bytes[1];
        }
      LCD_Memory++;
      }
    }
  }  
//============================================================================
// void invert_string(uint8_t x, uint8_t y, uint8_t Field_Width);
//
// invert_string() will invert an area on the screen starting at (x-1, y-1)
// and extending to (x+Field_Width*9+1, y+9).
//---------------------------------------------------------------------------
void invert_string(uint8_t x, uint8_t y, uint8_t Field_Width)
  {
  register uint8_t
    *LCD_Memory;
  register uint8_t
    column;
  register uint8_t
    row;
  register uint8_t
    Columns_To_Invert;
  WORD_UNION
    Inverting_Mask;

  //Get the first row of the display character.
  row=y>>3;
  //Calculate the address of the first uint8_t in display in LCD_Memory
  LCD_Memory=&framebuffer[row][x];

  //Calculate Inverting_Mask, the vertical mask that we will xor with
  //LCD_Memory to invert the area. It is 9 pixels.
  Inverting_Mask.as_word=0x01FF<<(y&0x07);

  //Invert the first col to the left of the string, and 8 more for
  //each of Field_Width characters.
  Columns_To_Invert=Field_Width<<3;
  for(column=0;column<=Columns_To_Invert;column++)
    {
    //Clear the correct bits in this row and the next row down.
    LCD_Memory[0]^=Inverting_Mask.as_bytes[0];
    if(row<7)
      LCD_Memory[128]^=Inverting_Mask.as_bytes[1];
    LCD_Memory++;
    }
  }
//============================================================================
// From: http://rosettacode.org/wiki/Bitmap/Bresenham's_line_algorithm#C
void LCD_Line(uint8_t x0, uint8_t y0,
              uint8_t x1, uint8_t y1,
              uint8_t set)
  {
  int8_t
    dx;
  int8_t
    sx;
  int8_t
    dy;
  int8_t
    sy;
  int8_t
    err;
  int8_t
    e2;      
  dx = abs((int16_t )x1 - (int16_t )x0);
  sx = x0 < x1 ? 1 : -1;
  dy = abs((int16_t )y1 - (int16_t )y0);
  sy = y0 < y1 ? 1 : -1;
  err = (dx > dy ? dx : -dy) / 2;

  for (;;)
    {
    Put_Pixel(x0, y0, set);
    if ((x0 == x1) && (y0 == y1))
      break;
    e2 = err;
    if (e2 > -dx)
      {
      err -= dy;
      x0 = (uint16_t)((int16_t) x0 + sx);
      }
    if (e2 < dy)
      {
      err += dx;
      y0 = (uint16_t)((int16_t) y0 + sy);
      }
    }
  }
//============================================================================
void outline_rectangle(uint8_t x1, uint8_t y1, uint8_t x2, uint8_t y2)
  {
  LCD_Line(x1+1,y1,x2-1,y1,1);
  LCD_Line(x1+1,y2,x2-1,y2,1);
  LCD_Line(x1,y1,x1,y2,1);
  LCD_Line(x2,y1,x2,y2,1);
  }
//============================================================================
void clear_rectangle(uint8_t x1,uint8_t y1,uint8_t x2,uint8_t y2)
  {
  register uint8_t
    *LCD_Memory;
  register uint8_t
    *LCD_Memory_1;
  register uint8_t
    *LCD_Memory_2;
  register uint8_t
    mask;
  register uint8_t
    column;
  //Draw the last pixel too.
  y2++;
  //Bail for bogus parametrers.
  if((x2<x1)||
     (y2<y1)||
     (127<x1)||
     (127<x2)||
     (63<y1)||
     (63<y2))
    return;
  //Calculate the address of the first ubyte in display in LCD_Memory
  LCD_Memory_1=&framebuffer[y1>>3][x1];
  //Calculate the address of the last ubyte in display in LCD_Memory
  LCD_Memory_2=&framebuffer[y2>>3][x1];
  //If they are the same, then this is a special case.
  if(LCD_Memory_1==LCD_Memory_2)
    {
    //The rectangle fits in one row.
    mask=~((0xFF<<(y1&0x07))&(~(0xFF<<(y2&0x07))));
    for(column=x1;column<=x2;column++)
      {
      *LCD_Memory_1&=mask;
      LCD_Memory_1++;
      }
    }
  else
    {
    //This is the case where we need to loop over multiple
    //(possibly 0) lines rows. Do the top ubyte.
    mask=~(0xFF<<(y1&0x07));
    LCD_Memory=LCD_Memory_1;
    for(column=x1;column<=x2;column++)
      {
      *LCD_Memory&=mask;
      LCD_Memory++;
      }
    //Do the bytes in the middle.
    for(LCD_Memory_1+=128;LCD_Memory_1!=LCD_Memory_2;LCD_Memory_1+=128)
      {
      LCD_Memory=LCD_Memory_1;
      for(column=x1;column<=x2;column++)
        {
        *LCD_Memory=0;
        LCD_Memory++;
        }
      }
    //Do the bottom ubyte.
    mask=0xFF<<(y2&0x07);
    for(column=x1;column<=x2;column++)
      {
      *LCD_Memory_2&=mask;
      LCD_Memory_2++;
      }
    }
  }
//============================================================================
 #define mSwap(a,b,t)\
  {\
  t=a;\
  a=b;\
  b=t;\
  }
void Rounded_Rect(uint8_t x0, uint8_t y0, uint8_t x1, uint8_t y1, uint8_t radius,uint8_t set)
  {
  uint8_t
    x;
  uint8_t
    y;
  int8_t
    radiusError;
  uint8_t
    Left_X_Center;
  uint8_t
    Lower_Y_Center;
  uint8_t
    Right_X_Center;
  uint8_t
    Upper_Y_Center;

  uint8_t
    temp;
  if (y1 < y0)
    mSwap(y0, y1, temp);
  if (x1 < x0)
    mSwap(x0, x1, temp);

  x = radius;
  y = 0;
  radiusError = 1 - (int8_t) x;

  Left_X_Center = x0 + radius;
  Lower_Y_Center = y0 + radius;

  Right_X_Center = x1 - radius;
  Upper_Y_Center = y1 - radius;

  if(0 != radius)
    {
    while(x >= y)
      {
      //Lower Left Corner, no offset
      Put_Pixel(Left_X_Center - x, Lower_Y_Center - y, set); //8 o'clock
      Put_Pixel(Left_X_Center - y, Lower_Y_Center - x, set); //7 o'clock
      //Lower Right Corner, X offset
      Put_Pixel(Right_X_Center + x, Lower_Y_Center - y, set); //4 o'clock
      Put_Pixel(Right_X_Center + y, Lower_Y_Center - x, set); //5 o'clock
      //Upper Left Corner, Y offset
      Put_Pixel(Left_X_Center - x, Upper_Y_Center + y, set); //10 o'clock
      Put_Pixel(Left_X_Center - y, Upper_Y_Center + x, set); //11 o'clock
      //Upper Right Corner, X & Y offset
      Put_Pixel(Right_X_Center + x, Upper_Y_Center + y, set); //2 o'clock
      Put_Pixel(Right_X_Center + y, Upper_Y_Center + x, set); //1 o'clock
      y++;
      if (radiusError < 0)
        {
        radiusError += (int16_t)(2 * y + 1);
        }
      else
        {
        x--;
        radiusError += 2 * (((int16_t) y - (int16_t) x) + 1);
        }
      }
    }

  //Put in the lines.
  //Bottom
  LCD_Line(Left_X_Center, y0, Right_X_Center, y0,1);
  //Top
  LCD_Line(Left_X_Center, y1, Right_X_Center, y1,1);
  //Left
  LCD_Line(x0, Lower_Y_Center, x0, Upper_Y_Center,1);
  //Right
  LCD_Line(x1, Lower_Y_Center, x1, Upper_Y_Center,1);
  }
//============================================================================

