#ifndef __LCD_LOW_H__
#define __LCD_LOW_H__
//============================================================================
// LCD SPI & control lines
// |------------+------------+---------------------------|
// |    Pin     | CFA-10110  |      Raspberry Pi         |
// | Definition | Pin Number | Pin Number | Pin Function |
// |------------+------------+------------+--------------|
// | 3v3        | 2          | 1          | 3V3          |
// | GND        | 1          | 6          | GND          |
// | RESET      | 3          | 7          | GPIO4        |
// | RS         | 5          | 11         | GPIO17       |
// | CS         | 6          | 24         | SPI CE0      |
// | MOSI       | 16         | 19         | SPI MOSI     |
// | SCK        | 15         | 23         | SPI SCLK     |
// |------------+------------+------------+--------------|
// The NT7534 datasheet recommends tying DB0-DB5 to VCC (3.3v) or ground.
// DB0-DB5 appear to have ~12K pull-up to VCC, so to mimimize current
// consumption and still follow the advice of the controller datasheet,
// you would want to tie the unused data pins to VCC.

#include "wiringPi.h"
#include <cstdint>
#define PIN_RS      17  //11
#define PIN_RESET   4   //7
#define CLR_RS    (digitalWrite(PIN_RS, 0))
#define SET_RS    (digitalWrite(PIN_RS, 1))
#define CLR_RESET (digitalWrite(PIN_RESET, 0))
#define SET_RESET (digitalWrite(PIN_RESET, 1))

// Define the display type
#define CFAG12864T3 (0)
#define CFAG12864T4 (0)
#define CFAG12864U3 (0)
#define CFAG12864U4 (1)

#define display_type CFAG12864U4
//////////////////////////

#define HRES 128
#define VRES 64

static const int CHANNEL = 0;
static int fd;

//============================================================================
void SPI_sendCommand(uint8_t command);
void SPI_sendData(uint8_t data);
void Set_Address(uint8_t column, uint8_t page);
void Set_Static_Indicators(uint16_t state_mask);
void Set_Contrast(uint8_t contrast);
void CFAG12864T2U2_Init(void);
void SI_Test(void);
//============================================================================
#endif //  __LCD_LOW_H__
