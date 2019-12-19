#include "led-metrix.h"

void shiftOut(uint8_t bitOrder, uint8_t val)
{
    uint8_t i;

    for (i = 0; i < 8; i++)  {
        if (bitOrder == LSBFIRST)
        {
            LATDbits.LATD2 = (val & 1)==1 ;
            val >>= 1;
        }
        else
        {
            LATDbits.LATD2 = (val & 128) != 0;
            val <<= 1;
        }

        LATDbits.LATD0 = HIGH;
        _delay(10);
        LATDbits.LATD0 = LOW;        
    }
}

void set_register(unsigned char address, unsigned char value)  
{
  LATDbits.LATD0 = LOW;
  LATDbits.LATD1 = LOW;
  shiftOut(MSBFIRST, address);
  shiftOut(MSBFIRST, value);
  LATDbits.LATD1 = HIGH;
}

void clear_matrix()
{
  // clear the dot matrix
  for (int i = 0; i < NUM_OF_COLUMNS; i++)
  {
    set_register(MAX7219_COLUMN_REG(i), 0b0000000);
  }
}

void init_max7219()
{
  // disable test mode. datasheet table 10
  set_register(MAX7219_DISPLAYTEST_REG, MAX7219_OFF);
  // set medium intensity. datasheet table 7
  set_register(MAX7219_INTENSITY_REG, 0x1);
  // turn off display. datasheet table 3
  set_register(MAX7219_SHUTDOWN_REG, MAX7219_OFF);
  // drive 8 digits. datasheet table 8
  set_register(MAX7219_SCANLIMIT_REG, 7);
  // no decode mode for all positions. datasheet table 4
  set_register(MAX7219_DECODE_REG, 0B00000000);

  // clear matrix display
  clear_matrix();
}

void plot(unsigned char *pattern)
{
    int i;
  
    // turn off display first
    set_register(MAX7219_SHUTDOWN_REG, MAX7219_OFF);

    // display one bitmap
    for (i = 0; i < 8; i++)
    {
      // starting from column 2
      set_register(MAX7219_COLUMN_REG(i), pattern[i]);
    }
    // turn on display
    set_register(MAX7219_SHUTDOWN_REG, MAX7219_ON);
}