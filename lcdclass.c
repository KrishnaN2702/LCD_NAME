
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

void init();        // function declearation
void lcd_command(unsigned char);     //lcd command
void lcd_data(unsigned char);   //lcd data
unsigned char x,i;      //variable assign
unsigned char array[18]=("HELLO WORLD");   //array
void main()
{
init(); 
lcd_command(0x80); //display position

for (x=0;x<11;x++)   //for loop to print our name
{
lcd_data(array[x]);
}
while(1);
}

void init()
{
TRISC= 0x00;
TRISD = 0x00;
lcd_command(0x3F);   // 0011 1111
__delay_ms(100);
lcd_command(0x3F);  // 0011 1111
__delay_ms(100);
lcd_command(0x3F);   // 0011 1111
__delay_ms(100);
lcd_command(0x38);   // N=No of lines And F= size of the font (0011 1000)
__delay_ms(100);
lcd_command(0x06); // print the letter left to right 1 1
__delay_ms(100);
lcd_command(0x0C);  //display on cursor off
__delay_ms(100);
lcd_command(0x01); //clear the previous data
__delay_ms(100);
}

void lcd_data(unsigned char i)
{
RC3=1; //RS=RC3  
PORTD=i;
RC0=1; //Enable is 1
RC0=0; //Enable is 0
__delay_ms(100);
}

void lcd_command(unsigned char i)
{
    
RC3=0;   //RS= RC3
PORTD =i;
RC0=1; //Enable is1
RC0=0; //Enable is 0
__delay_ms(100);
}

