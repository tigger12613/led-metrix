/*
 * File:   main.c
 * Author: kaoti
 *
 * Created on 2019年12月18日, 下午 7:54
 */
// CONFIG1H
#pragma config OSC = INTIO67    // Oscillator Selection bits (Internal oscillator block, port function on RA6 and RA7)
#pragma config FCMEN = OFF      // Fail-Safe Clock Monitor Enable bit (Fail-Safe Clock Monitor disabled)
#pragma config IESO = OFF       // Internal/External Oscillator Switchover bit (Oscillator Switchover mode disabled)

// CONFIG2L
#pragma config PWRT = OFF       // Power-up Timer Enable bit (PWRT disabled)
#pragma config BOREN = SBORDIS  // Brown-out Reset Enable bits (Brown-out Reset enabled in hardware only (SBOREN is disabled))
#pragma config BORV = 3         // Brown Out Reset Voltage bits (Minimum setting)

// CONFIG2H
#pragma config WDT = OFF        // Watchdog Timer Enable bit (WDT disabled (control is placed on the SWDTEN bit))
#pragma config WDTPS = 32768    // Watchdog Timer Postscale Select bits (1:32768)

// CONFIG3H
#pragma config CCP2MX = PORTC   // CCP2 MUX bit (CCP2 input/output is multiplexed with RC1)
#pragma config PBADEN = OFF      // PORTB A/D Enable bit (PORTB<4:0> pins are configured as analog input channels on Reset)
#pragma config LPT1OSC = OFF    // Low-Power Timer1 Oscillator Enable bit (Timer1 configured for higher power operation)
#pragma config MCLRE = ON       // MCLR Pin Enable bit (MCLR pin enabled; RE3 input pin disabled)

// CONFIG4L
#pragma config STVREN = ON      // Stack Full/Underflow Reset Enable bit (Stack full/underflow will cause Reset)
#pragma config LVP = OFF        // Single-Supply ICSP Enable bit (Single-Supply ICSP disabled)
#pragma config XINST = OFF      // Extended Instruction Set Enable bit (Instruction set extension and Indexed Addressing mode disabled (Legacy mode))

// CONFIG5L
#pragma config CP0 = OFF        // Code Protection bit (Block 0 (000800-001FFFh) not code-protected)
#pragma config CP1 = OFF        // Code Protection bit (Block 1 (002000-003FFFh) not code-protected)
#pragma config CP2 = OFF        // Code Protection bit (Block 2 (004000-005FFFh) not code-protected)
#pragma config CP3 = OFF        // Code Protection bit (Block 3 (006000-007FFFh) not code-protected)

// CONFIG5H
#pragma config CPB = OFF        // Boot Block Code Protection bit (Boot block (000000-0007FFh) not code-protected)
#pragma config CPD = OFF        // Data EEPROM Code Protection bit (Data EEPROM not code-protected)

// CONFIG6L
#pragma config WRT0 = OFF       // Write Protection bit (Block 0 (000800-001FFFh) not write-protected)
#pragma config WRT1 = OFF       // Write Protection bit (Block 1 (002000-003FFFh) not write-protected)
#pragma config WRT2 = OFF       // Write Protection bit (Block 2 (004000-005FFFh) not write-protected)
#pragma config WRT3 = OFF       // Write Protection bit (Block 3 (006000-007FFFh) not write-protected)

// CONFIG6H
#pragma config WRTC = OFF       // Configuration Register Write Protection bit (Configuration registers (300000-3000FFh) not write-protected)
#pragma config WRTB = OFF       // Boot Block Write Protection bit (Boot block (000000-0007FFh) not write-protected)
#pragma config WRTD = OFF       // Data EEPROM Write Protection bit (Data EEPROM not write-protected)

// CONFIG7L
#pragma config EBTR0 = OFF      // Table Read Protection bit (Block 0 (000800-001FFFh) not protected from table reads executed in other blocks)
#pragma config EBTR1 = OFF      // Table Read Protection bit (Block 1 (002000-003FFFh) not protected from table reads executed in other blocks)
#pragma config EBTR2 = OFF      // Table Read Protection bit (Block 2 (004000-005FFFh) not protected from table reads executed in other blocks)
#pragma config EBTR3 = OFF      // Table Read Protection bit (Block 3 (006000-007FFFh) not protected from table reads executed in other blocks)

// CONFIG7H
#pragma config EBTRB = OFF      // Boot Block Table Read Protection bit (Boot block (000000-0007FFh) not protected from table reads executed in other blocks)

// #pragma config statements should precede project file includes.
// Use project enums instead of #define for ON and OFF.

#include <xc.h>
#include "led-metrix.h"
#include "snake.h"
#include "ball.h"
#include <pic18f4520.h>
#define count_val  255
#define _XTAL_FREQ 1000000
unsigned char end =0;
unsigned char mode =0;
unsigned char select =0;
unsigned char input=9;
unsigned char outputMap1[16][16]={
	1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1,
	1,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,1,
	1,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,1,
	1,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,1,
	1,0,0,0,0,0,1,1, 1,1,1,1,1,1,0,1,
	1,0,0,0,0,0,1,1, 1,1,1,1,1,1,0,1,
	1,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,1,
	1,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,1,
    1,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,1,
    1,0,0,0,0,0,1,1, 1,1,1,1,1,1,0,1,
    1,0,0,0,0,0,1,1, 1,1,1,1,1,1,0,1,
    1,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,1,
    1,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,1,
    1,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,1,
    1,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,1,
    1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1,
};

unsigned char a,b,c,d;
void clear_input()
{
    a = 0;
    b = 0;
    c = 0;
    d = 0;
}

void __interrupt(high_priority) ISR()
{
    if(TMR0IF && TMR0IE)
    {
        TMR0IF = 0;
        if(mode==1){
        if(PORTDbits.RD3)
            move(0);
        else if(PORTDbits.RD1)
            move(1);
        else if(PORTDbits.RD0)
            move(2);
        else if(PORTDbits.RD2)
            move(3);
        //updatePlayer();
            //plot(map);
        }
        else if(mode==2){
            board(PORTDbits.RD0,PORTDbits.RD1,PORTDbits.RD3,PORTDbits.RD2);
            //plot(LED);
        }
        else{
            if(PORTDbits.RD1){
                if(select==0){
                    mode=1;
                }
                else{
                    mode=2;
                }
            }
        }
        //board(PORTDbits.RD0,PORTDbits.RD1,PORTDbits.RD2,PORTDbits.RD3);
        //plot(LED);
        /*if(PORTDbits.RD0 == 1)
            a = 1;
        //a = PORTDbits.RD0;
        b = PORTDbits.RD1;
        c = PORTDbits.RD2;
        d = PORTDbits.RD3;
        PIR1 = a;*/
        //LATDbits.LATD1 = 1;
        //__delay_ms(500);
        //LATDbits.LATD1 = 0;
        TMR0L = count_val;
    }
}

void main(void) {
    int speed=1;
    TRISB = 0;
    TRISC = 0;
    TRISD = 0b00001111;
    LATBbits.LATB4 = HIGH;
    LATBbits.LATB1 = HIGH;
    LATDbits.LATD5 = HIGH;
    LATCbits.LATC5 = HIGH;
    ADCON0=0b00000001;
    ADCON1=0b00001110;
    ADCON2=0b10001000;
    
    /////////////
    PORTA = 0x00;
    LATA = 0x00;
    TRISAbits.RA4 = 1;
    PORTD = 0x00;
    
    TMR0L = count_val;
    
    T0CON = 0b11101000;
    RCONbits.IPEN = 1;
    INTCONbits.GIE = 1;
    INTCONbits.TMR0IE = 1;
    INTCONbits.TMR0IF = 0;    
    ///////////////

    if(select==0){
        outputMap1[4][2]=1;
        outputMap1[4][3]=1;
        outputMap1[5][2]=1;
        outputMap1[5][3]=1;
    }
    else{
        outputMap1[10][2]=1;
        outputMap1[10][3]=1;
        outputMap1[11][2]=1;
        outputMap1[11][3]=1;
    }
    init_max7219();
    initial();
    initMap();
    endBall=&mode;
    endSnake=&mode;
    while(1)
    {
        if(mode==0){
            speed=5;
            ADCON0bits.GO=1;
            if(ADRES<512){
                select=1;
                outputMap1[4][2]=0;
                outputMap1[4][3]=0;
                outputMap1[5][2]=0;
                outputMap1[5][3]=0;
                outputMap1[9][2]=1;
                outputMap1[9][3]=1;
                outputMap1[10][2]=1;
                outputMap1[10][3]=1;
            }
            else{
                select=0;
                outputMap1[4][2]=1;
                outputMap1[4][3]=1;
                outputMap1[5][2]=1;
                outputMap1[5][3]=1;
                outputMap1[9][2]=0;
                outputMap1[9][3]=0;
                outputMap1[10][2]=0;
                outputMap1[10][3]=0;
            }
            plot(outputMap1);
        }
        else if(mode==1){
            ADCON0bits.GO=1;
           /*if(input==0){
                move(0);
                input=9;
           }
            else if(input==1){
                move(1);
                input=9;
            }
            else if(input==2){
                move(2);
                input=9;
            }
            else if(input==3){
                move(3);
                input=9;
            }*/
            updateMap();
            plot(map);
            if(error==1){
                initMap();
                 mode=0;
            }
            speed=ADRES/204.6;
        }
        else if(mode==2){
            ADCON0bits.GO=1;
            ball();
            //board(1,0,0,0);
            plot(LED);
            if(ball_x == 0 || ball_x == 15)
                mode=0;
            speed=ADRES/204.6;
        }
        //ball();
        //board(1,0,0,0);
        
        //clear_input();
        switch(speed){
            case 5:
                _delay(250000);
                break;
            case 4:
                _delay(125000);
                break;
            case 3:
                _delay(100000);
                break;
            case 2:
                _delay(50000);
                break;
            default:
                _delay(25000);
                break;
        }
        
        //if(ball_x == 0 || ball_x == 15)//end
        //{
        //    break;
        //}
    }
    //initSnake(0,0);
	//setPoint();
    
    _delay(25000000);
    //plot(test1);
    while(1){}
    
    return;
}
