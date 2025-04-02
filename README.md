# CFAG12864Ux and CFAG12864Tx family of displays

Example code for the Crystalfontz CFAG12864T and CFAG12864U family of displays for Seeeduino (Arduino clone) and RaspberryPi. These displays come in reflective and transflective models, are extremely low power, and have slim designs. They also come with optional carrier boards and development kits for quick product evaluation.

Full part numbers and links to the products can be found below.

## Displays without carrier boards can be found here:
| Part Number | Description |
| --- | --- |
| [CFAG12864T3-TFH](https://www.crystalfontz.com/product/cfag12864t3tfh) | 1" transflective, backlit |
| [CFAG12864T3-NFH](https://www.crystalfontz.com/product/cfag12864t3nfh) | 1" reflective, no backlight |
| [CFAG12864T4-NFI](https://www.crystalfontz.com/product/cfag12864t4nfi) | 1" transmissive, no backlight |
| [CFAG12864U3-TFH](https://www.crystalfontz.com/product/cfag12864u3tfh) | 2.2" transflective, backlit |
| [CFAG12864U3-NFH](https://www.crystalfontz.com/product/cfag12864u3nfh) | 2.2" reflective, no backlight |
| [CFAG12864U4-NFI](https://www.crystalfontz.com/product/cfag12864u4nfi) | 2.2" transmissive, no backlight |

## Kits for these products can be found here:  
| Part Number | Description |
| --- | --- |
| [CFAG12864T3-NFH-E1-1](https://www.crystalfontz.com/product/cfag12864t3nfhe11) | Low Power Transflective Graphic LCD Module |
| [CFAG12864T3-NFH-E1-2](https://www.crystalfontz.com/product/cfag12864t3nfhe12) | Low Power Transflective LCD Dev Kit |
| [CFAG12864T3-TFH-E1-1](https://www.crystalfontz.com/product/cfag12864t3tfhe11) | 128x64 Backlit Transflective LCD with Breakout Board 
| [CFAG12864T3-TFH-E1-2](https://www.crystalfontz.com/product/cfag12864t3tfhe12) | Small Backlit Monochrome LCD Dev Kit 
| [CFAG12864U3-NFH-E1-1](https://www.crystalfontz.com/product/cfag12864u3nfhe11) | Low Power Transflective LCD Display Module |
| [CFAG12864U3-NFH-E1-2](https://www.crystalfontz.com/product/cfag12864u3nfhe12) | Low Power Monochrome LCD Dev Kit 
| [CFAG12864U3-TFH-E1-1](https://www.crystalfontz.com/product/cfag12864u3tfhe11) | 128x64 Monochrome Transflective Backlit LCD Module 
| [CFAG12864U3-TFH-E1-2](https://www.crystalfontz.com/product/cfag12864u3tfhe12) | 128x64 Transflective Backlit LCD Development Kit  |

## Pre-processor directives
There are a number of pre-processor directives in the code that allow you to change the display the code is written for. They can also change which tests are run.

Edit `LCD_low.h` to reflect the appropriate base display (either `CFAG12864T3`, `CFAG12864T4`, `CFAG12864U3` or `CFAG12864U4`) for the correct initialization. 

## Connection Details
### To CFA10110 Adapter Board (See kits above)
#### SPI Configuration (Arduino)
| Pin Definition | 10110 Pin | Seeeduino Pin | Connection Description            |
|----------------|-----------|---------------|-----------------------------------|
| GND            | 1         | GND           | Ground                            |
| 3V3            | 2         | 3V3           | Voltage in                        |
| RES            | 3         | D9            | Reset pin                         |
| DNC            | 4         | DNC           | Do not connect                    |
| DC (RS)        | 5         | D8            | Data or Command Register Select   |
| CS             | 6         | D10           | Chip Select                       |
| RD/E           | 7         | DNC           | Read (8080) or Enable (6800)      |
| WR/RW          | 8         | DNC           | Write (8080) or Read/Write (6800) |
| D0             | 9         | DNC           | Data pin 0                        |
| D1             | 10        | DNC           | Data pin 1                        |
| D2             | 11        | DNC           | Data pin 2                        |
| D3             | 12        | DNC           | Data pin 3                        |
| D4             | 13        | DNC           | Data pin 4                        |
| D5             | 14        | DNC           | Data pin 5                        |
| D6/CLK         | 15        | D13           | Data pin 6 or Clock pin for SPI   |
| D7/MOSI        | 16        | D11           | Data pin 7 or MOSI pin for SPI    |

#### SPI Configuration (Raspberry Pi)
| Pin Definition | 10110 Pin | Arduino Pin   | Connection Description            |
|----------------|-----------|---------------|-----------------------------------|
| GND            | 1         | GND           | Ground                            |
| 3V3            | 2         | 3V3           | Voltage in                        |
| RES            | 3         | 3 (GPIO4)     | Reset pin                         |
| DNC            | 4         | DNC           | Do not connect                    |
| DC (RS)        | 5         | 11 (GPIO17)   | Data or Command Register Select   |
| CS             | 6         | 24 (SPI CE0)  | Chip Select                       |
| RD/E           | 7         | DNC           | Read (8080) or Enable (6800)      |
| WR/RW          | 8         | DNC           | Write (8080) or Read/Write (6800) |
| D0             | 9         | DNC           | Data pin 0                        |
| D1             | 10        | DNC           | Data pin 1                        |
| D2             | 11        | DNC           | Data pin 2                        |
| D3             | 12        | DNC           | Data pin 3                        |
| D4             | 13        | DNC           | Data pin 4                        |
| D5             | 14        | DNC           | Data pin 5                        |
| D6/CLK         | 15        | 19 (SPI MOSI) | Clock pin for SPI                 |
| D7/MOSI        | 16        | 23 (SPI SCLK) | MOSI pin for SPI                  |

#### Parallel Configuration
This code currently only demonstrates using the SPI interface.


### To the display ZIF tail
#### SPI Configuration
| CFAG12864[T/U] Pin  | Seeeduino Pin | Connection Description            
|---------------------|---------------|-----------------------------------
| 1  3V3              | 3V3           | Voltage in
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
| 17 C86              | 3V3           | Selects between 8080 and 6800 when in parallel mode
| 18 P/S              | GND           | Selects between parallel and SPI mode

#### Parallel Configuration
This code currently only demonstrates using the SPI interface.

## Build instructions for Raspberry Pi
- Install and built [WiringPi](https://github.com/WiringPi/WiringPi) from source, following it's documentation
- After cloning this repo, build the executable by running this command:

  `g++ *.cpp -l wiringPi -o cfag12864u4`

## Contributors
    2017-06-15 Brent A. Crosby
    2019-05-01 Trevin Jorgenson
    2022-06-20 Kelsey Zaches
    2023-12-08 Khayam Sariffodeen
    2025-04-01 Max Roberg
