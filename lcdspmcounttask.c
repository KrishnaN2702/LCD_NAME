// PIC16F877A Configuration Bit Settings

// 'C' source line config statements

// CONFIG
#pragma config FOSC = EXTRC     // Oscillator Selection bits (RC oscillator)
#pragma config WDTE = OFF       // Watchdog Timer Enable bit (WDT disabled)
#pragma config PWRTE = OFF      // Power-up Timer Enable bit (PWRT disabled)
#pragma config BOREN = OFF      // Brown-out Reset Enable bit (BOR disabled)
#pragma config LVP = OFF        // Low-Voltage (Single-Supply) In-Circuit Serial Programming Enable bit (RB3 is digital I/O, HV on MCLR must be used for programming)
#pragma config CPD = OFF        // Data EEPROM Memory Code Protection bit (Data EEPROM code protection off)
#pragma config WRT = OFF        // Flash Program Memory Write Enable bits (Write protection off; all program memory may be written to by EECON control)
#pragma config CP = OFF         // Flash Program Memory Code Protection bit (Code protection off)

// #pragma config statements should precede project file includes.
// Use project enums instead of #define for ON and OFF.

#include <xc.h>
#define _XTAL_FREQ 6000000
void init();
void lcdcmd(unsigned char);
void lcddata(unsigned char);
void lcdoutput(unsigned int);
void keyscane();
void batterylevel();
unsigned char array[30]={"BATT VOL:    V"};

unsigned char x,m,n;
unsigned int d4,d3,d2,d1,j,i,valve;

void main(){
    init();
    while(1)
    {
        keyscane();
    }
}

void init(){
    TRISC =0x00;
    TRISD=0x00;
    TRISB=0xF0;
    OPTION_REG &=0x7F;
      lcdcmd(0x3F);
    __delay_ms(100);
      lcdcmd(0x3F);
    __delay_ms(100);
      lcdcmd(0x3F);
    __delay_ms(100);
      lcdcmd(0x38);
    __delay_ms(100);
      lcdcmd(0x06);
    __delay_ms(100);
      lcdcmd(0x0C);
    __delay_ms(100);
      lcdcmd(0x01);
    __delay_ms(100);
    j=150;
}
void keyscane(){
    valve=PORTB&0xF0;
    switch(valve)
    {
        case 0xE0:
            lcdcmd(0x80);
            for(x=0;x<9;x++)
            {
                lcddata(array[x]);
            }
            lcdcmd(0x8A);
            {
                lcdoutput(j);
            }
            lcdcmd(0x8E);
            for(x=13;x<14;x++)
            {
                lcddata(array[x]);
                
            }
              lcdcmd(0xC0); 
            for (x = 0; x < 11; x++){
            lcddata("BATTERY LOW"[x]);
            
        }
            break;
      case 0xD0:
            lcdcmd(0x8A);
            j++;
            
            
            
            if(j>225)
            {
                j=225;
            }
          
            lcdoutput(j);
            batterylevel();
            break;
            
        case 0xB0:
            j--;
            lcdcmd(0x8A);
            if(j<150)
            {
                j=150;
            }
            
            lcdoutput(j);
            batterylevel();
            break;
            
        case 0x70:
            j=176;
            lcdcmd(0x84);
            
            lcdoutput(j);
            batterylevel();
            break;
            

            
    }
}



void lcdcmd(unsigned char i)
{
    PORTC&=0xF7;  //RS =0
    PORTD=i; // data set to portd
    PORTC|=0x01; //EN=1
    PORTC&=~0x01;  //EN=0
    __delay_ms(100);
}
void lcddata(unsigned char i)
{
    PORTC|=0x08;
    PORTD=i;
    PORTC|=0x01;
    PORTC&=~0x01;
    __delay_ms(100);
}

void lcdoutput(unsigned int i)
{
    d4=0;
    d3=0;
    d2=0;

    d4=(i%10);
    d3=(i/10)%10;
    d2=(i/100);
     lcdcmd(0x8A);
      lcddata(0x30+d2);
//      
//    
    lcdcmd(0x8B);
     lcddata(0x30+d3);
     lcdcmd(0x8C);
     
     lcddata(0x2E);
     
    lcdcmd(0x8D);
    lcddata(0x30+d4);
  
}
void batterylevel()
{
    if (j>=150  && j<=175){
            lcdcmd(0xC0); 
            for (x = 0; x < 14; x++){
            lcddata("BATTERY LOW   "[x]);
            
            }
    }
             if(j>=176 && j<=205)
            {
                lcdcmd(0xC0);
                for(x=0;x<14;x++)
                lcddata("BATTERY NORMAL"[x]);
            }
            if(j>=206 && j<=225)
            {
                lcdcmd(0xC0);
                for(x=0;x<=14;x++)
                lcddata("BATTERY HIGH  "[x]);
            }
            
           
    
    
}