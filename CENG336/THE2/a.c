// ============================ //
// Do not edit this part!!!!    //
// ============================ //
// 0x300001 - CONFIG1H
#pragma config OSC = HSPLL      // Oscillator Selection bits (HS oscillator,
// PLL enabled (Clock Frequency = 4 x FOSC1))
#pragma config FCMEN = OFF      // Fail-Safe Clock Monitor Enable bit
// (Fail-Safe Clock Monitor disabled)
#pragma config IESO = OFF       // Internal/External Oscillator Switchover bit
// (Oscillator Switchover mode disabled)
// 0x300002 - CONFIG2L
#pragma config PWRT = OFF       // Power-up Timer Enable bit (PWRT disabled)
#pragma config BOREN = OFF      // Brown-out Reset Enable bits (Brown-out
// Reset disabled in hardware and software)
// 0x300003 - CONFIG1H
#pragma config WDT = OFF        // Watchdog Timer Enable bit
// (WDT disabled (control is placed on the SWDTEN bit))
// 0x300004 - CONFIG3L
// 0x300005 - CONFIG3H
#pragma config LPT1OSC = OFF    // Low-Power Timer1 Oscillator Enable bit
// (Timer1 configured for higher power operation)
#pragma config MCLRE = ON       // MCLR Pin Enable bit (MCLR pin enabled;
// RE3 input pin disabled)
// 0x300006 - CONFIG4L
#pragma config LVP = OFF        // Single-Supply ICSP Enable bit (Single-Supply
// ICSP disabled)
#pragma config XINST = OFF      // Extended Instruction Set Enable bit
// (Instruction set extension and Indexed
// Addressing mode disabled (Legacy mode))
#pragma config DEBUG = OFF      // Disable In-Circuit Debugger

// Timer Related Definitions
#define KHZ 1000UL
#define MHZ (KHZ * KHZ)
#define _XTAL_FREQ (40UL * MHZ)
// ============================ //
//             End              //
// ============================ //
#include <xc.h>
#include <stdint.h>

// ============================ //
//        DEFINITIONS           //
// ============================ //

#define T_HIGH_BIT 0x9E
#define T_LOW_BIT 0x58

// ============================ //
//          GLOBALS             //
// ============================ //

// You can write globals definitions here...

uint8_t gravity_count; // 350 ms
uint8_t blink_count; // 500 ms
uint8_t hippo_size; 
uint8_t score_count; // 1000 ms
uint8_t prev_b;
uint8_t soft_count; // 400 ms
uint8_t score;
uint16_t total_score;
uint8_t prev_d;
uint8_t prevd_bit;

// ============================ //
//          FUNCTIONS           //
// ============================ //

void init_ports_vars(){
TRISD = 0x00;
TRISB = 0x1;
PORTB = 0x00;
PORTD = 0x81;
gravity_count = 0;
blink_count = 0;
hippo_size = 1;
score_count = 0;
soft_count = 0;
score = 100;
prev_d = 0;
prevd_bit = 0;
total_score = 0;
}

void init_ints_timers(){
T0CON = 0x00;
TMR0H = T_HIGH_BIT;
TMR0L = T_LOW_BIT;
RCONbits.IPEN = 0;
INTCON = 0x00;

INTCONbits.TMR0IE = 1;
INTCONbits.INT0IE = 1;
T0CONbits.TMR0ON = 1;

INTCONbits.GIE = 1;
}

void init_new_game(){
gravity_count = 0;
blink_count = 0;
hippo_size = (hippo_size>>1) | 0x80;
score_count = 0;
score = 100;
if(hippo_size==0xfa){
hippo_size = 1; // make it like 0b11110
}
PORTD = hippo_size;
PORTDbits.RD0 = 1;

}

void soft_reset(){
soft_count = 0;
PORTD = 0xff;
while(soft_count!=80){
}
soft_count = 0;
PORTD = 0x00;
while(soft_count!=80){
}
soft_count = 0;
PORTD = 0xff;
while(soft_count!=80){
}
soft_count = 0;
PORTD = 0x00;
while(soft_count!=80){
}
soft_count = 0;
PORTD = 0xff;
while(soft_count!=80){
}
soft_count = 0;
init_new_game();
}

// ============================ //
//   INTERRUPT SERVICE ROUTINE  //
// ============================ //
__interrupt(high_priority)
void HandleInterrupt()
{
if(INTCONbits.TMR0IF){
INTCONbits.TMR0IF = 0;
TMR0H = T_HIGH_BIT;
TMR0L = T_LOW_BIT;
gravity_count++;
blink_count++;
score_count++;
soft_count++;

if(gravity_count==70){
if(PORTDbits.RD7==1){
gravity_count = 0;
}
else{
prev_d = PORTD;
prevd_bit = PORTDbits.RD0;
prev_d = (prev_d << 1) & 0xfa;
PORTD = prev_d;
PORTDbits.RD0 = prevd_bit;
gravity_count = 0;
}
}
if(blink_count==100){
PORTDbits.RD0 ^= 1;
blink_count = 0;
}
if(score_count==200){
if(score>=10){
score -= 10;
}
score_count = 0;
}

}
if(INTCONbits.INT0IF){
INTCONbits.INT0IF = 0;
if(PORTDbits.RD1){
soft_reset();
total_score += score;
// this place might be total score or 7 display
}
else{
prevd_bit = PORTDbits.RD0;
PORTD = PORTD >> 1;
PORTDbits.RD0 = prevd_bit;
}
}
}

// ============================ //
//            MAIN              //
// ============================ //
void main()
{

init_ports_vars();
init_ints_timers();
while(1){
continue;
}

}