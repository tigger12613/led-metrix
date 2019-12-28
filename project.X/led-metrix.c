#include "led-metrix.h"

void shiftOut1(uint8_t bitOrder, uint8_t val)
{
    uint8_t i;

    for (i = 0; i < 8; i++)  {
        if (bitOrder == LSBFIRST)
        {
            LATBbits.LATB5 = (val & 1)==1 ;
            val >>= 1;
        }
        else
        {
            LATBbits.LATB5 = (val & 128) != 0;
            val <<= 1;
        }

        LATBbits.LATB3 = HIGH;
        _delay(5);
        LATBbits.LATB3 = LOW;        
    }
}
void shiftOut2(uint8_t bitOrder, uint8_t val)
{
    uint8_t i;

    for (i = 0; i < 8; i++)  {
        if (bitOrder == LSBFIRST)
        {
            LATBbits.LATB2 = (val & 1)==1 ;
            val >>= 1;
        }
        else
        {
            LATBbits.LATB2 = (val & 128) != 0;
            val <<= 1;
        }

        LATBbits.LATB0 = HIGH;
        _delay(5);
        LATBbits.LATB0 = LOW;        
    }
}
void shiftOut3(uint8_t bitOrder, uint8_t val)
{
    uint8_t i;

    for (i = 0; i < 8; i++)  {
        if (bitOrder == LSBFIRST)
        {
            LATDbits.LATD6 = (val & 1)==1 ;
            val >>= 1;
        }
        else
        {
            LATDbits.LATD6 = (val & 128) != 0;
            val <<= 1;
        }

        LATDbits.LATD4 = HIGH;
        _delay(5);
        LATDbits.LATD4 = LOW;        
    }
}
void shiftOut4(uint8_t bitOrder, uint8_t val)
{
    uint8_t i;

    for (i = 0; i < 8; i++)  {
        if (bitOrder == LSBFIRST)
        {
            LATCbits.LATC6 = (val & 1)==1 ;
            val >>= 1;
        }
        else
        {
            LATCbits.LATC6 = (val & 128) != 0;
            val <<= 1;
        }

        LATCbits.LATC4 = HIGH;
        _delay(5);
        LATCbits.LATC4 = LOW;        
    }
}



void set_register1(unsigned char address, unsigned char value)  
{
  LATBbits.LATB3 = LOW;
  LATBbits.LATB4 = LOW;
  shiftOut1(MSBFIRST, address);
  shiftOut1(MSBFIRST, value);
  LATBbits.LATB4 = HIGH;
}
void set_register2(unsigned char address, unsigned char value)  
{
  LATBbits.LATB0 = LOW;
  LATBbits.LATB1 = LOW;
  shiftOut2(MSBFIRST, address);
  shiftOut2(MSBFIRST, value);
  LATBbits.LATB1 = HIGH;
}
void set_register3(unsigned char address, unsigned char value)  
{
  LATDbits.LATD4 = LOW;
  LATDbits.LATD5 = LOW;
  shiftOut3(MSBFIRST, address);
  shiftOut3(MSBFIRST, value);
  LATDbits.LATD5 = HIGH;
}
void set_register4(unsigned char address, unsigned char value)  
{
  LATCbits.LATC4 = LOW;
  LATCbits.LATC5 = LOW;
  shiftOut4(MSBFIRST, address);
  shiftOut4(MSBFIRST, value);
  LATCbits.LATC5 = HIGH;
}
void clear_matrix()
{
  // clear the dot matrix
  for (int i = 0; i < NUM_OF_COLUMNS; i++)
  {
    set_register1(MAX7219_COLUMN_REG(i), 0b0000000);
    set_register2(MAX7219_COLUMN_REG(i), 0b0000000);
    set_register3(MAX7219_COLUMN_REG(i), 0b0000000);
    set_register4(MAX7219_COLUMN_REG(i), 0b0000000);
  }
}

void init_max7219()
{
  // disable test mode. datasheet table 10
  set_register1(MAX7219_DISPLAYTEST_REG, MAX7219_OFF);
  // set medium intensity. datasheet table 7
  set_register1(MAX7219_INTENSITY_REG, 0x1);
  // turn off display. datasheet table 3
  set_register1(MAX7219_SHUTDOWN_REG, MAX7219_OFF);
  // drive 8 digits. datasheet table 8
  set_register1(MAX7219_SCANLIMIT_REG, 7);
  // no decode mode for all positions. datasheet table 4
  set_register1(MAX7219_DECODE_REG, 0B00000000);
  // disable test mode. datasheet table 10
  set_register2(MAX7219_DISPLAYTEST_REG, MAX7219_OFF);
  // set medium intensity. datasheet table 7
  set_register2(MAX7219_INTENSITY_REG, 0x1);
  // turn off display. datasheet table 3
  set_register2(MAX7219_SHUTDOWN_REG, MAX7219_OFF);
  // drive 8 digits. datasheet table 8
  set_register2(MAX7219_SCANLIMIT_REG, 7);
  // no decode mode for all positions. datasheet table 4
  set_register2(MAX7219_DECODE_REG, 0B00000000);
  // disable test mode. datasheet table 10
  set_register3(MAX7219_DISPLAYTEST_REG, MAX7219_OFF);
  // set medium intensity. datasheet table 7
  set_register3(MAX7219_INTENSITY_REG, 0x1);
  // turn off display. datasheet table 3
  set_register3(MAX7219_SHUTDOWN_REG, MAX7219_OFF);
  // drive 8 digits. datasheet table 8
  set_register3(MAX7219_SCANLIMIT_REG, 7);
  // no decode mode for all positions. datasheet table 4
  set_register3(MAX7219_DECODE_REG, 0B00000000);
  // disable test mode. datasheet table 10
  set_register4(MAX7219_DISPLAYTEST_REG, MAX7219_OFF);
  // set medium intensity. datasheet table 7
  set_register4(MAX7219_INTENSITY_REG, 0x1);
  // turn off display. datasheet table 3
  set_register4(MAX7219_SHUTDOWN_REG, MAX7219_OFF);
  // drive 8 digits. datasheet table 8
  set_register4(MAX7219_SCANLIMIT_REG, 7);
  // no decode mode for all positions. datasheet table 4
  set_register4(MAX7219_DECODE_REG, 0B00000000);
  

  // clear matrix display
  clear_matrix();
}

void plot(unsigned char pattern[16][16])
{
    int i,j;
    unsigned char char_pattern1[8]={0};
    unsigned char char_pattern2[8]={0};
    unsigned char char_pattern3[8]={0};
    unsigned char char_pattern4[8]={0};
    
    for(i=0;i<8;i++)
    {
        for(j=0;j<8;j++)
        {
            char_pattern1[i] <<= 1;
            if(pattern[i][j]==1)
            {
                char_pattern1[i] += 1;
            }
        }
    }
    for(i=0;i<8;i++)
    {
        for(j=0;j<8;j++)
        {
            char_pattern2[i] <<= 1;
            if(pattern[i][j+8]==1)
            {
                char_pattern2[i] += 1;
            }
        }
    }
    for(i=0;i<8;i++)
    {
        for(j=0;j<8;j++)
        {
            char_pattern3[i] <<= 1;
            if(pattern[i+8][j]==1)
            {
                char_pattern3[i] += 1;
            }
        }
    }
    for(i=0;i<8;i++)
    {
        for(j=0;j<8;j++)
        {
            char_pattern4[i] <<= 1;
            if(pattern[i+8][j+8]==1)
            {
                char_pattern4[i] += 1;
            }
        }
    }
    // turn off display first
    
    set_register1(MAX7219_SHUTDOWN_REG, MAX7219_OFF);
    set_register2(MAX7219_SHUTDOWN_REG, MAX7219_OFF);
    set_register3(MAX7219_SHUTDOWN_REG, MAX7219_OFF);
    set_register4(MAX7219_SHUTDOWN_REG, MAX7219_OFF);
    
    // display one bitmap
    for (i = 0; i < 8; i++)
    {
      // starting from column 2
      set_register1(MAX7219_COLUMN_REG(i), char_pattern1[i]);
      set_register2(MAX7219_COLUMN_REG(i), char_pattern2[i]);
      set_register3(MAX7219_COLUMN_REG(i), char_pattern3[i]);
      set_register4(MAX7219_COLUMN_REG(i), char_pattern4[i]);
    }
    // turn on display
    
    set_register1(MAX7219_SHUTDOWN_REG, MAX7219_ON);
    set_register2(MAX7219_SHUTDOWN_REG, MAX7219_ON);
    set_register3(MAX7219_SHUTDOWN_REG, MAX7219_ON);
    set_register4(MAX7219_SHUTDOWN_REG, MAX7219_ON);
     
}