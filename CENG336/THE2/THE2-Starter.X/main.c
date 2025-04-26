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

#define T_PRELOAD_LOW 0xB0
#define T_PRELOAD_HIGH 0x3C
// ============================ //
//        DEFINITIONS           //
// ============================ //
uint16_t gravity_counter = 0;
uint16_t blink_counter = 0;
uint16_t score_counter = 0; 
uint16_t first_delay_counter = 0;
uint8_t soft_counter;

uint8_t hippo;
uint8_t prize;
uint8_t hippo_size;

int game_loop = 0;
int soft_reset = 0;



// You can write struct definitions here...

// ============================ //
//          GLOBALS             //
// ============================ //

// You can write globals definitions here...

// ============================ //
//          FUNCTIONS           //
// ============================ //

// You can write function definitions here...
void initialize(){
    TRISD = 0x00;
    TRISB = 0x01;
    
    PORTB = 0x00;
    PORTD = 0x00;
    
    gravity_counter = 0;
    blink_counter = 0;
    score_counter = 0; 
    first_delay_counter = 0;
    soft_counter = 0;
    
    hippo = 0x80;
    prize = 0x01;
    hippo_size = 1;
    
    T0CON = 0x00;
    T0CONbits.PSA = 1;
   
    // Pre-load the value
    TMR0H = T_PRELOAD_HIGH;
    TMR0L = T_PRELOAD_LOW;

    RCONbits.IPEN = 0;
    INTCON = 0x00;
    INTCONbits.TMR0IE = 1;
    T0CONbits.TMR0ON = 1;
    INTCONbits.GIE = 1;
    
}
void timerInit(){
    //1sec delay 
    while(first_delay_counter < 200){ 
    }
    game_loop = 1;
    INTCONbits.INT0IE = 1;
}

void blinkPrize(){
    if(blink_counter == 100){
        prize  = prize ^ 0x01;
        blink_counter = 0;
        PORTDbits.RD0 = prize;
    }
    return;
}

void softReset(){
    //INTCONbits.INT0IE = 0;
    soft_counter = 0;
    PORTD = 0xff;
    while(soft_counter!=80){
    }
    soft_counter = 0;
    PORTD = 0x00;
    while(soft_counter!=80){
    }
    soft_counter = 0;
    PORTD = 0xff;
    while(soft_counter!=80){
    }
    soft_counter = 0;
    PORTD = 0x00;
    while(soft_counter!=80){
    }
    soft_counter = 0;
    PORTD = 0xff;
    while(soft_counter!=80){
    }
    soft_counter = 0;
    INTCONbits.INT0IE = 1;
}
void shift_hipo(){
    if(hippo & 0x02){
        soft_reset = 1; // interrupt game loop
        return;
    }    
    hippo = hippo >> 1;
    PORTD = hippo | prize;   
}


// ============================ //
//   INTERRUPT SERVICE ROUTINE  //
// ============================ //
__interrupt(high_priority)
void HandleInterrupt()
{
    if(INTCONbits.TMR0IF)
    {
        INTCONbits.TMR0IF = 0;
        // Pre-load the value
        TMR0H = T_PRELOAD_HIGH;
        TMR0L = T_PRELOAD_LOW;
        
        if(game_loop == 0){
            first_delay_counter++;
            return;
        }
        
        if(soft_reset) {
            soft_counter++;
        }
        
        blink_counter++;        
        blinkPrize();
        
    }
    if(INTCONbits.INT0IF)
    {
        // Then clear the bit
        INTCONbits.INT0IF = 0;
        shift_hipo();
        
    }
}

// ============================ //
//            MAIN              //
// ============================ //
void main()
{
    initialize();
    //wait 1 sec
    timerInit();
    
    while(1){
        if(soft_reset) {
            softReset();
        }
    }
    return;
}