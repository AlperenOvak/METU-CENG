PROCESSOR 18F8722

#include <xc.inc>

; CONFIGURATION (DO NOT EDIT)
; CONFIG1H
CONFIG OSC = HSPLL      ; Oscillator Selection bits (HS oscillator, PLL enabled (Clock Frequency = 4 x FOSC1))
CONFIG FCMEN = OFF      ; Fail-Safe Clock Monitor Enable bit (Fail-Safe Clock Monitor disabled)
CONFIG IESO = OFF       ; Internal/External Oscillator Switchover bit (Oscillator Switchover mode disabled)
; CONFIG2L
CONFIG PWRT = OFF       ; Power-up Timer Enable bit (PWRT disabled)
CONFIG BOREN = OFF      ; Brown-out Reset Enable bits (Brown-out Reset disabled in hardware and software)
; CONFIG2H
CONFIG WDT = OFF        ; Watchdog Timer Enable bit (WDT disabled (control is placed on the SWDTEN bit))
; CONFIG3H
CONFIG LPT1OSC = OFF    ; Low-Power Timer1 Oscillator Enable bit (Timer1 configured for higher power operation)
CONFIG MCLRE = ON       ; MCLR Pin Enable bit (MCLR pin enabled; RE3 input pin disabled)
; CONFIG4L
CONFIG LVP = OFF        ; Single-Supply ICSP Enable bit (Single-Supply ICSP disabled)
CONFIG XINST = OFF      ; Extended Instruction Set Enable bit (Instruction set extension and Indexed Addressing mode disabled (Legacy mode))
CONFIG DEBUG = OFF      ; Disable In-Circuit Debugger


GLOBAL counter1
GLOBAL counter2
GLOBAL counter3
GLOBAL released_flag
GLOBAL index
GLOBAL sequence

; Define space for the variables in RAM
PSECT udata_acs
sequence:
    DS 6  ; 6 bytes for the number sequence
index:
    DS 1  ; Current sequence index
pause_flag:
    DS 1  ; Flag for pausing the sequence
counter1:
    DS 1
counter2:
    DS 1
counter3:
    DS 1
released_flag:
    DS 1
current_porte:
    DS 1
last_porte:
    DS 1


PSECT resetVec,class=CODE,reloc=2
resetVec:
    goto       main


PSECT CODE
main:
    ; Initialize registers
    clrf index         ; Start from first number
    clrf pause_flag    ; Not paused initially
    clrf counter1
    clrf counter2
    clrf counter3
    clrf last_porte
    ; FSR1 will keep a pointer to the current index
    clrf FSR1L
    ; Temp pointer
    clrf FSR0L

    ; Load student ID (example: 123456)
    movlw 0x01
    movwf POSTINC0
    movlw 0x02
    movwf POSTINC0
    movlw 0x03
    movwf POSTINC0
    movlw 0x04
    movwf POSTINC0
    movlw 0x05
    movwf POSTINC0
    movlw 0x06
    movwf POSTINC0

    ; Set up I/O
    clrf TRISC ; PORTC as output (binary display)
    clrf TRISD ; PORTD as output (blinking LED)
    setf TRISE ; PORTE as input (buttons)

    ; Initialization period (1s delay, all LEDs on)
    setf LATC
    setf LATD
    call delay_1s

    call reset_counter
    ; Set the output LEDs and start main loop
    movff sequence, LATC
    clrf LATD
main_loop:
    call check_inputs
    call display_routine
    goto main_loop


check_inputs:
    movf PORTE, W
    movwf current_porte
    comf WREG
    andwf last_porte, 0
    ; released_flag = ~current_porte & last_porte
    movwf released_flag
    movff current_porte, last_porte

    ; If RE7 was released, toggle paused flag.
    btfsc released_flag, 7
    btg pause_flag, 0

    check_inc_buttons:
        ; Check increment buttons, starting from RE5
        movlw 5
        movwf FSR0L
        check_inc_buttons_loop:
            btfss released_flag, 5
            bra check_inc_buttons_loop_inc
            ; The button at this index is released
            incf INDF0  ; Increase this number
            ; If it is >= 10, set it to 0
            movlw 10
            cpfslt INDF0
            clrf INDF0
        check_inc_buttons_loop_inc:
            ; Rotate released_flag left so that the previous button's flag is at 5th bit.
            rlncf released_flag
            ; Decrease the pointer
            decf FSR0L
            ; If the result is positive (no underflow), continue loop
            bc check_inc_buttons_loop
    return
    

display_routine:
    decf counter1
    bnz display_routine_out
    decf counter2
    bnz display_routine_out
    ; If we're here, 500 ms have passed
    call reset_counter
    ; Blink LED
    btg PORTD, 0
    ; Return if paused
    btfsc pause_flag, 0
    return
    ; Display the next number
    incf FSR1L
    movlw 6
    cpfslt FSR1L ; Skip next instruction if index < 6
    clrf FSR1L   ; if (index >= 6) index = 0;
    movff INDF1, PORTC  ; PORTC = *FSR1;
    nop
display_routine_out:
    return

reset_counter:
    movlw 31
    movwf counter2
    movlw 16
    movwf counter1
    return


delay_1s:
    movlw 6
    movwf counter3
    movlw 19
    movwf counter2
    outermost_loop:
        outer_loop:
            inner_loop:
                decf counter1
                bnz inner_loop
        decf counter2
        bnz outer_loop
    decf counter3
    bnz outermost_loop
    ; All counters will be set to 0 after these loops.
    return

end resetVec
