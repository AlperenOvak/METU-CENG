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
GLOBAL rep0
GLOBAL rep1
GLOBAL rep2
GLOBAL rep3
GLOBAL rep4
GLOBAL rep5
GLOBAL rep7    
GLOBAL de0
GLOBAL de1
GLOBAL de2
GLOBAL de3
GLOBAL de4
GLOBAL de5
GLOBAL pause
GLOBAL counter


; Define space for the variables in RAM
PSECT udata_acs
counter1:
    DS 1 ; Allocate 1 byte for var1
counter2:
    DS 1 
counter3:
    DS 1
rep0:
    DS 1
rep1:
    DS 1
rep2:
    DS 1
rep3:
    DS 1
rep4:
    DS 1
rep5:
    DS 1
rep7:
    DS 1
de0:
    DS 1
de1:
    DS 1
de2:
    DS 1
de3:
    DS 1
de4:
    DS 1
de5:
    DS 1
de7:
    DS 1
pause:
    DS 1
counter:
    DS 1    
    



PSECT resetVec,class=CODE,reloc=2
resetVec:
    goto       main

PSECT CODE
main:
    call init
    
main_loop:
    btfss pause , 0
    call show_digit
    call robin
    btg PORTD , 0
    
    goto main_loop
    
robin:
    movlw 25
    movwf counter1
    
    robinn:
	robinnn:
	    call check_input
	    incf counter2
	    bnc robinnn
	decfsz counter1
	goto robinn	
    return    
    
check_input:
    call check_re0
    call check_re1
    call check_re2
    call check_re3
    call check_re4
    call check_re5
    call check_re7
    return
    
    check_re0:
	btfsc PORTE,0
	goto re0_pressed
	btfsc rep0,0
	goto re0_released
	return
	re0_released:
	    incf de0
	    movlw 10
	    CPFSLT de0
	    clrf de0
	    clrf rep0
	    return
	re0_pressed:
	    bsf rep0,0
	    return
    
    check_re1:
	btfsc PORTE,1
	goto re1_pressed
	btfsc rep1,0
	goto re1_released
	return
	re1_released:
	    incf de1
	    movlw 10
	    CPFSLT de1
	    clrf de1
	    clrf rep1
	    return
	re1_pressed:
	    bsf rep1,0
	    return
    
    check_re2:
	btfsc PORTE,2
	goto re2_pressed
	btfsc rep2,0
	goto re2_released
	return
	re2_released:
	    incf de2
	    movlw 10
	    CPFSLT de2
	    clrf de2
	    clrf rep2
	    return
	re2_pressed:
	    bsf rep2,0
	    return
    
    check_re3:
	btfsc PORTE,3
	goto re3_pressed
	btfsc rep3,0
	goto re3_released
	return
	re3_released:
	    incf de3
	    movlw 10
	    CPFSLT de3
	    clrf de3
	    clrf rep3
	    return
	re3_pressed:
	    bsf rep3,0
	    return
    
    check_re4:
	btfsc PORTE,4
	goto re4_pressed
	btfsc rep4,0
	goto re4_released
	return
	re4_released:
	    incf de4
	    movlw 10
	    CPFSLT de4
	    clrf de4
	    clrf rep4
	    return
	re4_pressed:
	    bsf rep4,0
	    return
    
    check_re5:
	btfsc PORTE,5
	goto re5_pressed
	btfsc rep5,0
	goto re5_released
	return
	re5_released:
	    incf de5
	    movlw 10
	    CPFSLT de5
	    clrf de5
	    clrf rep5
	    return
	re5_pressed:
	    bsf rep5,0
	    return
    
    check_re7:
	btfsc PORTE,7
	goto re7_pressed
	btfsc rep7,0
	goto re7_released
	return
	re7_released:
	    clrf rep7
	    btg pause,0
	    return
	re7_pressed:
	    bsf rep7,0
	    return
    
	    
    
show_digit:
    call decide_de
    call show
    return
    
show:
    movwf PORTC
    incf counter
    movlw 6
    CPFSLT counter
    clrf counter
    return


decide_de:
    movlw 5
    CPFSLT counter
    goto display5
    movlw 4
    CPFSLT counter
    goto display4
    movlw 3
    CPFSLT counter
    goto display3
    movlw 2
    CPFSLT counter
    goto display2
    movlw 1
    CPFSLT counter
    goto display1
    movlw 0
    CPFSLT counter
    goto display0
    
    return
    
    display5:
	movf de5 , W
	return
    display4:
	movf de4 , W
	return
    display3:
	movf de3 , W
	return
    display2:
	movf de2, W
	return
    display1:
	movf de1, W
	return
    display0:
	movf de0, W
	return
	
	


busy_wait:
    movlw 5
    movwf counter1
    
    outest:
	outer:
	    inner:
		incf counter3
		bnc inner
	    incf counter2
	    bnc outer
	decfsz counter1
	goto outest
    return	
    
init:
    clrf pause
    clrf counter
    
    movlw 2
    movwf de0
    movlw 5
    movwf de1
    movlw 8
    movwf de2
    movlw 0
    movwf de3
    movlw 8
    movwf de4
    movlw 0
    movwf de5
    
    clrf TRISC
    clrf TRISD
    setf TRISE
    
    setf PORTC
    setf PORTD
    
    clrf PORTE
    
    call busy_wait 
    
    clrf PORTC
    clrf PORTD
  
    return

end resetVec