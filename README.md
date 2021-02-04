# CFAF240320A0-024Sx-A1

Example Seeeduino (Arduino clone) code for the Crystalfontz CFAG12864T and CFAG12864U family of displays. These displays come in relfective and transflective models, are extremely low power, and slim designs. They also come with optional carrier boards and development kits for quick product evaluation. Full part numbers and links to the products can be found below.

Displays without carrier boards can be found here:

[CFAG12864T3-TFH](https://www.crystalfontz.com/product/cfag12864t3tfh) - 1.3" transflective

[CFAG12864T3-NFH](https://www.crystalfontz.com/product/cfag12864t3nfh) - 1.3" reflective

[CFAG12864U3-TFH](https://www.crystalfontz.com/product/cfag12864u3tfh) - 2.4" transflective

[CFAG12864U3-NFH](https://www.crystalfontz.com/product/cfag12864u3nfh) - 2.4" reflective
  
Kits for these products can be found here:  

[CFAF240320A0-024SC-A1-2](https://www.crystalfontz.com/product/cfaf240320a0024sca12)

[CFAF240320A0-024SN-A1-2](https://www.crystalfontz.com/product/cfaf240320a0024sna12)

## Connection Details
#### To CFA10098 Adapter Board (See kits above)
##### SPI Configuration
| 10110 Pin         | Seeeduino Pin | Connection Description            
|-------------------|---------------|-----------------------------------
| 1  GND            | GND           | Ground
| 2  3v3            | 3v3           | Voltage in
| 3  RES            | D9            | Reset pin
| 4  DNC            | no connect    | Do not connect
| 5  DC (RS)        | D8            | Data or Command Register Select
| 6  CS             | D10           | Chip Select
| 7  RD/E           | DNC           | Read (8080) or Enable (6800)
| 8  WR/RW          | DNC           | Write (9090) or Read/Write (6800)
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
| 7  WR/RW            | DNC           | Write (9090) or Read/Write (6800)
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
