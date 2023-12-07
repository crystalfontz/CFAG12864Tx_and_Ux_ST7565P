# CFAG12864Ux and CFAG12864Tx family of displays

Example Seeeduino (Arduino clone) code for the Crystalfontz CFAG12864T and CFAG12864U family of displays. These displays come in relfective and transflective models, are extremely low power, and have slim designs. They also come with optional carrier boards and development kits for quick product evaluation. Full part numbers and links to the products can be found below.

Displays without carrier boards can be found here:

[CFAG12864T3-TFH](https://www.crystalfontz.com/product/cfag12864t3tfh) - 1.1" transflective

[CFAG12864T3-NFH](https://www.crystalfontz.com/product/cfag12864t3nfh) - 1.1" reflective

[CFAG12864T4-NFI](https://www.crystalfontz.com/product/cfag12864t4nfi) - 1.1" reflective with transmissive polarizer

[CFAG12864U3-TFH](https://www.crystalfontz.com/product/cfag12864u3tfh) - 2.2" transflective

[CFAG12864U3-NFH](https://www.crystalfontz.com/product/cfag12864u3nfh) - 2.2" reflective

[CFAG12864U4-NFI](https://www.crystalfontz.com/product/cfag12864u4nfi) - 2.2" reflective with transmissive polarizer
  
Kits for these products can be found here:  

[Low Power Transflective Graphic LCD Module (CFAG12864T3-NFH-E1-1)](https://www.crystalfontz.com/product/cfag12864t3nfhe11)

[Low Power Transflective LCD Dev Kit (CFAG12864T3-NFH-E1-2)](https://www.crystalfontz.com/product/cfag12864t3nfhe12)

[128x64 Backlit Transflective LCD with Breakout Board (CFAG12864T3-TFH-E1-1)](https://www.crystalfontz.com/product/cfag12864t3tfhe11)

[Small Backlit Monochrome LCD Dev Kit (CFAG12864T3-TFH-E1-2)](https://www.crystalfontz.com/product/cfag12864t3tfhe12)

[Low Power Transflective LCD Display Module (CFAG12864U3-NFH-E1-1)](https://www.crystalfontz.com/product/cfag12864u3nfhe11)

[Low Power Monochrome LCD Dev Kit (CFAG12864U3-NFH-E1-2)](https://www.crystalfontz.com/product/cfag12864u3nfhe12)

[128x64 Monochrome Transflective Backlit LCD Module (CFAG12864U3-TFH-E1-1)](https://www.crystalfontz.com/product/cfag12864u3tfhe11)

[128x64 Transflective Backlit LCD Development Kit (CFAG12864U3-TFH-E1-2)](https://www.crystalfontz.com/product/cfag12864u3tfhe12)

Edit LCD_low.h to reflect the appropriate base display (either CFAG12864T3 or CFAG12864U3) for the correct initialization. For use with the CFAG12864T4 and CFAG12864U4, please specify the base display as CFAG12864T3 and CFAG12864U3 respectively. 

## Connection Details
#### To CFA10110 Adapter Board (See kits above)
##### SPI Configuration
| 10110 Pin         | Seeeduino Pin | Connection Description            
|-------------------|---------------|-----------------------------------
| 1  GND            | GND           | Ground
| 2  3v3            | 3v3           | Voltage in
| 3  RES            | D9            | Reset pin
| 4  DNC            | DNC           | Do not connect
| 5  DC (RS)        | D8            | Data or Command Register Select
| 6  CS             | D10           | Chip Select
| 7  RD/E           | DNC           | Read (8080) or Enable (6800)
| 8  WR/RW          | DNC           | Write (8080) or Read/Write (6800)
| 9  D0             | DNC           | Data pin 0
| 10 D1             | DNC           | Data pin 1
| 11 D2             | DNC           | Data pin 2
| 12 D3             | DNC           | Data pin 3
| 13 D4             | DNC           | Data pin 4
| 14 D5             | DNC           | Data pin 5
| 15 D6/CLK         | D13           | Data pin 6 or Clock pin for SPI
| 16 D7/MOSI        | D11           | Data pin 7 or MOSI pin for SPI

#### Parallel Configuration
This code currently only demonstrates using the SPI interface.


#### To the display ZIF tail
##### SPI Configuration
| CFAG12864[T/U] Pin  | Seeeduino Pin | Connection Description            
|---------------------|---------------|-----------------------------------
| 1  3v3              | 3v3           | Voltage in
| 2  GND              | GND           | Ground
| 3  CS               | D10           | Chip Select
| 4  CS               | D10           | Chip Select
| 5  RES              | D9            | Reset pin
| 6  DC (RS)          | D8            | Data or Command Register Select
| 7  WR/RW            | DNC           | Write (8080) or Read/Write (6800)
| 8  RD/E             | DNC           | Read (8080) or Enable (6800)
| 9  D0               | DNC           | Data pin 0
| 10 D1               | DNC           | Data pin 1
| 11 D2               | DNC           | Data pin 2
| 12 D3               | DNC           | Data pin 3
| 13 D4               | DNC           | Data pin 4
| 14 D5               | DNC           | Data pin 5
| 15 D6/CLK           | D13           | Data pin 6 or Clock pin for SPI
| 16 D7/MOSI          | D11           | Data pin 7 or MOSI pin for SPI
| 17 C86              | 3v3           | Selects between 8080 and 6800 when in parallel mode
| 18 P/S              | GND           | Selects between parallel and SPI mode

#### Parallel Configuration
This code currently only demonstrates using the SPI interface.
