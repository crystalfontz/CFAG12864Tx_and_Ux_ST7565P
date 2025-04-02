#ifndef __FNT08X08_H__
#define __FNT08X08_H__

#include <wiringPiSPI.h>
#include <cstdint>
#include <iostream>

//Base character is: 32 = 0x20 = " "
#define FONT_08X08_BASE 32
extern const unsigned char Font_08x08[96][8];

#endif //  __FNT08X08_H__
