/*
 * File:   main.c
 * Author: GROUP36
 *
 */
#include "pragmas.h"
#include <xc.h>

/* **** Ring-buffers for incoming and outgoing data **** */
// These buffer functions are modularized to handle both the input and
// output buffers with an input argument.
typedef enum {INBUF = 0, OUTBUF = 1, QUEUE = 2} buf_t;
#define BUFSIZE 512       /* Static buffer size. Maximum amount of data */ // this can be changed
uint8_t inbuf[BUFSIZE];   /* Preallocated buffer for incoming data */
uint8_t outbuf[BUFSIZE];  /* Preallocated buffer for outgoing data  */
uint16_t queue[16];
/* We have used circular queues for buffering input, output messages and cars*/
uint16_t head[3] = {0, 0, 0}; /* head for pushing, tail for popping */
uint16_t tail[3] = {0, 0, 0};
/* these heads and tails are defined for each of the circular queues.*/
char sim_msg_array[12]; // packet message for buffering purposes
int sim_count = 0; // size of message
/* Timer interrupt flags*/
uint8_t pic_msg_count = 0;
uint8_t timer_money = 0;
uint8_t timer_adc = 0;

/* Variables to keep track of things*/
int total_money = 0;
int empty_space = 40;
uint8_t msg_last_char = 0;
int emp_res_count = 0; // empty response length

uint8_t v; // char put to the TXREG register
uint8_t c; // char popped from the input buffer

uint8_t prev_rb4 = 0;  
uint8_t display_mode = 0;  // 0 ? show total money, 1 ? show empty-spaces
uint8_t selected_level = 0;  // 0=A, 1=B, 2=C, 3=D
uint16_t seven_seg_value = 0;

/* parking lot initialization*/
int park_slots[4][10];
int park_fee_counter[4][10];
int reserved_slots[4][10];

// 7-segment-display-digits mapping
uint8_t digit_map[10] = {
    0x3F,
    0x06,
    0x5B,
    0x4F,
    0x66,
    0x6D,
    0x7D,
    0x07,
    0x7F,
    0x6F
};
// used in 7 segment display
uint16_t tens_power[4] = {1, 10, 100, 1000};
uint8_t digit = 0;

inline void disable_rxtx( void ) { PIE1bits.RC1IE = 0; PIE1bits.TX1IE = 0; }
inline void enable_rxtx( void )  { PIE1bits.RC1IE = 1; PIE1bits.TX1IE = 1; }

/* Check if a buffer had data or not */
#pragma interrupt_level 2 // Prevents duplication of function
uint8_t buf_isempty( buf_t buf ) { return (head[buf] == tail[buf])?1:0; }
/* Place new data in buffer */
/* we add size input to use this function  for every buffer*/
void buf_push(uint16_t v, buf_t buf, int size) {
    if (buf == INBUF) inbuf[head[buf]] = v;
    else if (buf == QUEUE) queue[head[buf]] = v;
    else outbuf[head[buf]] = v;
    head[buf]++;
    if (head[buf] == size) head[buf] = 0;
    if (head[buf] == tail[buf]) { return; }
}

/*try so hard - respect Adilhan LORD*/
uint8_t buf_push_inbuf(uint8_t v){
    inbuf[head[INBUF]] = v;
    head[INBUF]++;
    if (head[INBUF] == BUFSIZE) head[INBUF] = 0;
    if (head[INBUF] == tail[INBUF]) { return 0; }
    return v;
}

/* Retrieve data from buffer */
/* we add size input to use this function  for every buffer*/
#pragma interrupt_level 2 // Prevents duplication of function
uint16_t buf_pop(buf_t buf , int size) {
    uint16_t v;
    if (buf_isempty(buf)) { 
        return 0; 
    } else {
        if (buf == INBUF) v = inbuf[tail[buf]];
        else if (buf == QUEUE) v = queue[tail[buf]];
        else v = outbuf[tail[buf]];
        tail[buf]++;
        if (tail[buf] == size) tail[buf] = 0;
        return v;
    }
}

/* called when buf is empty at every 100 ms*/
void push_emp_rsp(){
    char emp_response_buf[8];
    sprintf(emp_response_buf, "$EMP%02u#", empty_space);
    
    while(emp_res_count < 7) {
        buf_push(emp_response_buf[emp_res_count++],OUTBUF,BUFSIZE);
    } 
}


/* called for seven seg display every 5 ms*/
/* use seven_seg_value only, and put the value inside according to mode*/
void update_display() {
    if(display_mode == 1){
        uint8_t empty_count = 0;
        for (uint8_t j = 0; j < 10; j++) {
            if (park_slots[selected_level][j] == -1) empty_count++;
        }
        seven_seg_value = empty_count;
    } else {
        seven_seg_value = total_money;
    }
}

void __interrupt (high_priority) highPriorityISR (void) {	
    
    /*receive interrupt:
     * pushed incoming byte to inbuf
     * also checked to ensure that coming message is correct, otherwise ignore and cont.
     *  */
	if (PIR1bits.RC1IF == 1) {
        PIR1bits.RC1IF = 0;	
        c = RCREG1;
        if (RCSTA1bits.FERR || RCSTA1bits.OERR){
            RCSTA1bits.FERR = 0;
            RCSTA1bits.OERR = 0;
            RCSTA1bits.CREN = 0;
            RCSTA1bits.CREN = 1;
        }
        else{
            msg_last_char = buf_push_inbuf(c);
        }
	}
    
    
    //  the TXREGx register is empty
    if (PIR1bits.TX1IF == 1) {
        v = buf_pop(OUTBUF,BUFSIZE);
        TXREG1 = v;
        if(v=='#'){
            while(TXSTA1bits.TRMT==0){}
            TXSTA1bits.TXEN = 0;
        }
	}
    
    /*timer interrupt triggered at every 5 ms*/
    if(INTCONbits.TMR0IF==1){
        INTCONbits.TMR0IF = 0;
        TMR0H = 0x3c;
        TMR0L = 0xaf;
        timer_money++;
        pic_msg_count++;
        timer_adc++;
        
        update_display();
        PORTJ = digit_map[(seven_seg_value/tens_power[digit])%10];
        PORTH = 1 << (3-digit);
        digit = (digit+1) & 0x03;
    }
    
    /* PORT B interrupt*/
    if(INTCONbits.RBIF == 1) {
        //read PORTB to clear
        uint8_t current = PORTB;
        uint8_t rb4 = (current >> 4) & 1; // extract just RB4

        if (prev_rb4 == 1 && rb4 == 0) {
            // gone from high to low
            display_mode ^= 1;
        }
        prev_rb4 = rb4; 
        INTCONbits.RBIF = 0;
    }
}


void init_int() {
    /* configure I/O ports */
    TRISCbits.RC7 = 1; // TX1 and RX1 pin configuration
    TRISCbits.RC6 = 0;
    
	/* configure USART transmitter/receiver */
	TXSTA1 = 0x00;      // (= 00000000) 8-bit transmit, transmitter NOT enabled,TXSTA1.TXEN not enabled!
                        // asynchronous, high speed mode
	RCSTA1 = 0x90;      // (= 10010000) 8-bit receiver, receiver enabled,   
                        // continuous receive, serial port enabled RCSTA.CREN = 1
    BAUDCON1bits.BRG16 = 1;
    SPBRGH1 = 0x00;
    SPBRG1 = 0x15;		// for 40 MHz, to have 115200 baud rate, it should be 21
    
    // ==== RB4 interrupt-on-change for button release ====
    INTCON = 0;		// clear interrupt register completely
    TRISB = 0x10;
    uint8_t current_portb = PORTB; //read the portb
    INTCONbits.RBIF = 0; 
    INTCONbits.RBIE = 1;
    INTCON2bits.RBIP = 1; // Set high priority
    
    /* configure the interrupts */
	PIE1bits.TX1IE = 0;	// enable USART transmit interrupt
	PIE1bits.RC1IE = 1;	// enable USART receive interrupt
	PIR1 = 0;			// clear all peripheral flags
	
    T0CON = 0x08;
	INTCONbits.PEIE = 1;// enable peripheral interrupts
    INTCONbits.TMR0IE = 1;  // enable timer0 interrupt
	INTCONbits.GIE = 1;	// globally enable interrupts
}

void init_adc(){
    // Set ADC Inputs
    TRISH = 0x10; // AN12 input RH4
    // Configure ADC
    ADCON0 = 0x31; // Channel 12; Turn on AD Converter
    ADCON1 = 0x00; // All analog pins
    ADCON2 = 0xAA; // Right Align | 12 Tad | Fosc/32
    ADRESH = 0x00;
    ADRESL = 0x00;
}

void init_vars(){
    /* init parking slots matrices*/
    for(uint8_t i=0;i<4;i++){
        for(uint8_t j=0;j<10;j++){
            park_slots[i][j] = -1;
            park_fee_counter[i][j] = 0;
            reserved_slots[i][j] = -1;
        }
    }
}

// ==== Push Responses====
void push_park_rsp(uint8_t level, uint8_t spot, int car_id){
    char response_buf[12];
    sprintf(response_buf, "$SPC%03u%c%02u#", car_id, (level+'A'), spot+1);
    
    for(uint8_t i=0; i<11; i++){
        disable_rxtx();
        buf_push(response_buf[i], OUTBUF, BUFSIZE);
        enable_rxtx();
    }
}

void push_park_fee_rsp(int car_id, int fee){
    char response_buf[12];
    sprintf(response_buf, "$FEE%03u%03u#", car_id, fee);
    
    for(uint8_t i=0; i<11; i++){
        disable_rxtx();
        buf_push(response_buf[i], OUTBUF, BUFSIZE);
        enable_rxtx();
    }
}

void push_sub_rsp(int car_id, int fee){
    char response_buf[11];
    sprintf(response_buf, "$RES%03u%02u#", car_id, fee);
    
    for(uint8_t i=0; i<10; i++){
        buf_push(response_buf[i], OUTBUF, BUFSIZE);
    }
}

//try to park at the given spot
//returns:
// 0 if not successful
// 1 for park normally
// 2 for reserved parking
uint8_t try_park(int car_id) {
    int spot[2] = {-1, -1};
    
    for(uint8_t i=0; i<4; i++){
        for(uint8_t j=0; j<10; j++){
            if(reserved_slots[i][j] == car_id && park_slots[i][j] == -1){
                park_slots[i][j] = car_id;
                empty_space--;
                push_park_rsp(i ,j, car_id);
                return 2;
            }
           
            // control wheter there is an empty slot before find any reserved slot for the curr car.
            if(reserved_slots[i][j] == -1 && park_slots[i][j] == -1){
                spot[0] = i;
                spot[1] = j;
            }
        }
        // 
    }
    if(spot[0] != -1){
        empty_space--;
        push_park_rsp(spot[0], spot[1], car_id);
        park_slots[spot[0]][spot[1]] = car_id;
        park_fee_counter[spot[0]][spot[1]] = 0;
        return 1;
    }else{
        return 0; // there is not empty space
    }
}


void handle_park(int car_id){
    if(try_park(car_id) == 0){
        disable_rxtx();
        buf_push(car_id, QUEUE, 16);
        enable_rxtx();
        return;
    }
}


/*
 handler for exit
 * also calculates the fee
 * call handle_park for cars in the waiting queue 
 * in successful exit it calls push_park_fee_rsp
 * ow ignores
 */
void handle_exit(int car_id){
    int exit_fee = 0;
    for(uint8_t i=0;i<4;i++){
        for(uint8_t j=0;j<10;j++){
            if(park_slots[i][j]==car_id){
                park_slots[i][j] = -1;
                if(reserved_slots[i][j]!=car_id){                    
                    exit_fee = (park_fee_counter[i][j]) + 1;
                }
                park_fee_counter[i][j] = 0;
                total_money += exit_fee;
                empty_space++;
                push_park_fee_rsp(car_id, exit_fee);
                if(!buf_isempty(QUEUE)){
                    disable_rxtx();
                    uint16_t ready_car_id = buf_pop(QUEUE,16);
                    enable_rxtx();
                    handle_park(ready_car_id); // Adding next car from car waiting queue
                }
                return;
            }
        }
    }
    
    return;
}

void handle_subscr(int car_id, int level, int spot){
    int sub_fee = 0;
    if(park_slots[level][spot] == -1 && reserved_slots[level][spot] == -1){
        sub_fee = 50;
        reserved_slots[level][spot] = car_id;
    }
    total_money+=sub_fee;
    push_sub_rsp(car_id, sub_fee);
    return;
}

/* starts the messaging process & timers & 7-seg dis.*/
void handle_go(){
    T0CONbits.TMR0ON = 1;
    TMR0H = 0x3c;
    TMR0L = 0xaf;
    
    TRISJ = 0x00;
    PORTH = 0x00;
    PORTJ = 0x00;
}

/* clear the buffer
 * close the interrupts 
 */
void handle_end(){
    disable_rxtx();
    T0CONbits.TMR0ON = 0;
    INTCONbits.GIE = 0;
    while(!buf_isempty(INBUF)){
        disable_rxtx();
        buf_pop(INBUF, BUFSIZE);
        enable_rxtx();
    }
}



//parse and categorizes the incoming messages and calls specific handlers for it
void parse_sim_messages(){
    int car_id = 0;
    char level;
    int spot;
    
    if(sim_msg_array[0] != '$' || sim_msg_array[sim_count-1] != '#'){
        return; // false pop or push
    }
        
    if (sim_msg_array[1] == 'G' && sim_msg_array[2] == 'O') {
        handle_go();
        
    } else if ( 
            sim_msg_array[1] == 'E' && 
            sim_msg_array[2] == 'N' && 
            sim_msg_array[3] == 'D'){
        handle_end();
        
    } else if (
                sim_msg_array[1] == 'P' && 
                sim_msg_array[2] == 'R' && 
                sim_msg_array[3] == 'K'){
        
        car_id = (sim_msg_array[4]-'0')*100
                  + (sim_msg_array[5]-'0')*10
                  + (sim_msg_array[6]-'0');
        handle_park(car_id);
        
    } else if (
            sim_msg_array[1] == 'E' && 
            sim_msg_array[2] == 'X' && 
            sim_msg_array[3] == 'T'){
        
        car_id = (sim_msg_array[4]-'0')*100
                  + (sim_msg_array[5]-'0')*10
                  + (sim_msg_array[6]-'0');
        handle_exit(car_id);
        
    } else if (
            sim_msg_array[1] == 'S' && 
            sim_msg_array[2] == 'U' && 
            sim_msg_array[3] == 'B'){
        
        car_id = (sim_msg_array[4]-'0')*100
                  + (sim_msg_array[5]-'0')*10
                  + (sim_msg_array[6]-'0');
        
        level = sim_msg_array[7]-'A';
        spot = (sim_msg_array[8]-'0')*10 + (sim_msg_array[9]-'0')-1;
        handle_subscr(car_id, level, spot);
    }
}

//when we receive #, it's called to parse/take message and put in to message array
void packet_task() {
    // Wait until new bytes arrive
    while (!buf_isempty(INBUF)) {
        disable_rxtx();
        sim_msg_array[sim_count++] = buf_pop(INBUF, BUFSIZE);
        enable_rxtx();
    }
}

void main(void) {
    init_adc(); 
    init_int();
    init_vars();
    while(1) {
        // # means end of the message
        if(msg_last_char=='#'){
            packet_task();
            msg_last_char = 0;
            parse_sim_messages();
            for(uint8_t i=0;i<12;i++){
                sim_msg_array[i] = '\0';
            }       
            sim_count = 0;
        }
        //sends message every 100 ms
        if(pic_msg_count==20){
            pic_msg_count=0;
            emp_res_count = 0;
            if(buf_isempty(OUTBUF)){
                push_emp_rsp();
            }
            TXSTA1bits.TXEN = 1;
        }
        
        //calculates parking fee according to 
        //parking time for each of the cars
        if(timer_money==50){
            for(uint8_t i=0;i<4;i++){
                for(uint8_t j=0;j<10;j++){
                    if(park_slots[i][j]!=-1){
                        park_fee_counter[i][j]++;
                    }
                }
            }
            timer_money= 0; 
        }
        
        //read the adc val for every 500ms
        if(timer_adc==100){
            // Get ADC Sample
            GODONE = 1; // Start ADC conversion
            while(GODONE); // Poll and wait for conversion to finish.
            unsigned int result = (ADRESH << 8) + ADRESL; // Get the result;
            if (result <  256) selected_level = 0;
            else if (result <  512) selected_level = 1;
            else if (result <  768) selected_level = 2;
            else selected_level = 3;
            timer_adc = 0;
        }
    }
    return;
    
}