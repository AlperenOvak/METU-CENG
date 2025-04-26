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


GLOBAL var1
GLOBAL var2
GLOBAL var3
GLOBAL counter
GLOBAL prev_re7
GLOBAL prev_re0
GLOBAL prev_re1
GLOBAL prev_re2
GLOBAL prev_re3
GLOBAL prev_re4
GLOBAL prev_re5
GLOBAL pause
GLOBAL dec0
GLOBAL dec1
GLOBAL dec2
GLOBAL dec3
GLOBAL dec4
GLOBAL dec5

; Define space for the variables in RAM
PSECT udata_acs
var1:
    DS 1 ; Allocate 1 byte for var1
var2:
    DS 1 
var3:
    DS 1 
dec0:
    DS 1
dec1:
    DS 1
dec2:
    DS 1
dec3:
    DS 1
dec4:
    DS 1
dec5:
    DS 1
counter:
    DS 1 
temp_result:
    DS 1   
prev_re7: 
    DS 1
prev_re0: 
    DS 1
prev_re1: 
    DS 1
prev_re2: 
    DS 1
prev_re3: 
    DS 1
prev_re4: 
    DS 1
prev_re5: 
    DS 1
pause: 
    DS 1


PSECT resetVec,class=CODE,reloc=2
resetVec:
    goto       main

PSECT CODE
main:
    clrf var1	; var1 = 0		
    clrf var2   ; var2 = 0
    clrf var3   
    clrf prev_re7 ; prev_rb = 0
    clrf prev_re0
    clrf prev_re1
    clrf prev_re2
    clrf prev_re3
    clrf prev_re4
    clrf prev_re5
    clrf pause 
    clrf counter
    movlw 2
    movwf dec0
    movlw 5
    movwf dec1
    movlw 8
    movwf dec2
    movlw 0
    movwf dec3
    movlw 8
    movwf dec4
    movlw 0
    movwf dec5
    
    ; PORTC/D as output
    clrf TRISC
    clrf TRISD
    ; PORTB as input
    setf TRISE
    
    setf PORTC
    setf PORTD
    clrf PORTE
    
    call busy_wait
    
    clrf PORTC
    clrf PORTD
    
    
main_loop:
    ; Round robin
    ;call check_input
    ;call dec_input
    
    btfss pause, 0
    call count
    call toggle_D
    btg PORTD,0
    goto main_loop
    
toggle_D:
    movlw 1
    movwf var3
    movlw 25
    movwf var2
    toggle_outer_loop:
	toggle_loop_start:
	    toggle_inner_start:
		call check_input
		call dec_input
		incf var1
	        bnc toggle_inner_start
	    decfsz var2
	    bra toggle_loop_start
	decfsz var3
	bra toggle_outer_loop
    return
    
count:
    call update_display
    call display_port
    return

update_display:
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
    movf dec5, W
    return
display4:
    movf dec4, W
    return
display3:
    movf dec3, W
    return
display2:
    movf dec2, W
    return
display1:
    movf dec1, W
    return
display0:
    movf dec0, W
    return
    
display_port:
    movwf PORTC
    incf counter
    movlw 6
    CPFSEQ counter
    return
    clrf counter
    return

    
    
	

dec_input:
    call check0
    call check1
    call check2
    call check3
    call check4
    call check5
    return
    
    check0:
	btfsc PORTE, 0 
	goto re0_pressed ; go if RB7 = 1
	btfsc prev_re0, 0 
	goto re0_released ; go if prev_RB7 = 1
	return
	re0_released:
	    bcf prev_re0,0
	    incf dec0
	    movlw 10
	    cpfseq dec0
	    return
	    clrf dec0
	    return
	re0_pressed:
	    bsf prev_re0,0
	    return
    check1:
	btfsc PORTE, 1 
	goto re1_pressed ; go if RB1 = 1
	btfsc prev_re1, 0 
	goto re1_released ; go if prev_RB1 = 1
	return
	re1_released:
	    bcf prev_re1,0
	    incf dec1
	    movlw 10
	    cpfseq dec1
	    return
	    clrf dec1
	    return
	re1_pressed:
	    bsf prev_re1,0
	    return
    check2:
	btfsc PORTE, 2 
	goto re2_pressed ; go if RB2 = 1
	btfsc prev_re2, 0 
	goto re2_released ; go if prev_RB2 = 1
	return
	re2_released:
	    bcf prev_re2,0
	    incf dec2
	    movlw 10
	    cpfseq dec2
	    return
	    clrf dec2
	    return
	re2_pressed:
	    bsf prev_re2,0
	    return
    check3:
	btfsc PORTE, 3 
	goto re3_pressed ; go if RB7 = 1
	btfsc prev_re3, 0 
	goto re3_released ; go if prev_RB3 = 1
	return
	re3_released:
	    bcf prev_re3,0
	    incf dec3
	    movlw 10
	    cpfseq dec3
	    return
	    clrf dec3
	    return
	re3_pressed:
	    bsf prev_re3,0
	    return
    check4:
	btfsc PORTE, 4 
	goto re4_pressed ; go if RB4 = 1
	btfsc prev_re4, 0 
	goto re4_released ; go if prev_RB4 = 1
	return
	re4_released:
	    bcf prev_re4,0
	    incf dec4
	    movlw 10
	    cpfseq dec4
	    return
	    clrf dec4
	    return
	re4_pressed:
	    bsf prev_re4,0
	    return
    check5:
	btfsc PORTE, 5 
	goto re5_pressed ; go if RB5 = 1
	btfsc prev_re5, 0 
	goto re5_released ; go if prev_RB5 = 1
	return
	re5_released:
	    bcf prev_re5,0
	    incf dec5
	    movlw 10
	    cpfseq dec5
	    return
	    clrf dec5
	    return
	re5_pressed:
	    bsf prev_re5,0
	    return
    
	
check_input:
    btfsc PORTE, 7 
    goto re7_pressed ; go if RB7 = 1
    btfsc prev_re7, 0 
    goto re7_released ; go if prev_RB7 = 1
    return
    re7_released:
	bcf prev_re7,0
	btg pause,0 ; toggle pause
	return
    re7_pressed:
	bsf prev_re7,0
	return

	
    
busy_wait:
    movlw 5
    movwf var3
    movlw 255
    movwf var2
    outer_outer_loop:
	outer_loop_start:
	    loop_start:
	        incf var1
	        bnc loop_start
	    decfsz var2
	    bra outer_loop_start
	decfsz var3
	bra outer_outer_loop
    return
   
end resetVec
