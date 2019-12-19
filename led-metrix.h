/* 
 * File:   led-metrix.h
 * Author: kaoti
 *
 * Created on 2019年12月19日, 下午 9:43
 */

#ifndef LED_METRIX_H
#define	LED_METRIX_H

// the MAX7219 address map (datasheet table 2)
#define MAX7219_DECODE_REG      (0x09)
#define MAX7219_INTENSITY_REG   (0x0A)
#define MAX7219_SCANLIMIT_REG   (0x0B)
#define MAX7219_SHUTDOWN_REG    (0X0C)
#define MAX7219_DISPLAYTEST_REG (0x0F)
#define MAX7219_DIGIT_REG(pos)  ((pos) + 1)
#define MAX7219_COLUMN_REG(pos) MAX7219_DIGIT_REG(pos)
// shutdown mode (datasheet table 3)
#define MAX7219_OFF             (0x0)
#define MAX7219_ON              (0x1)
// number of columns of the display matrx
#define NUM_OF_COLUMNS  (8)
// for each character bitmap, it consumes 4 bytes
#define BYTE_PER_MAP    (4)

#include <xc.h>

#define DISPLAY_STR_LENGTH  (sizeof(char_pattern) / BYTE_PER_MAP)
typedef unsigned char uint8_t;
#define LSBFIRST 0
#define MSBFIRST 1
#define HIGH 0x01
#define LOW 0x00
//LATD0 is clock, when raise the din pin signal will be store.
//LATD1 is cs (Load), for indicate which time for start and end.
//LATD2 is din, for signal input.
void shiftOut(uint8_t bitOrder, uint8_t val);
void set_register(unsigned char address, unsigned char value);
void clear_matrix();
void init_max7219();
void plot(unsigned char *pattern);
#endif	/* LED_METRIX_H */

