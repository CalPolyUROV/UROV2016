#ifndef CURRENTSENSING_H
#define CURRENTSENSING_H

#define CHECK_BIT(var,pos) ((var) & (1<<(pos)))

#define LTC1859_CH0             0x80
#define LTC1859_CH1             0xC0
#define LTC1859_CH2             0x90
#define LTC1859_CH3             0xD0
#define LTC1859_CH4             0xA0
#define LTC1859_CH5             0xE0
#define LTC1859_CH6             0xB0
#define LTC1859_CH7             0xF0

#define CURRENTSELECT           10

uint8_t ampReading(uint8_t);

#endif
