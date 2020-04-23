;-------------------------------------------------------------------------------
; MSP430 Assembler Code Template for use with TI Code Composer Studio
;
;
;-------------------------------------------------------------------------------
            .cdecls C,LIST,"msp430.h"       ; Include device header file

;-------------------------------------------------------------------------------
            .text                           ; Assemble into program memory
            .retain                         ; Override ELF conditional linking
                                            ; and retain current section
            .retainrefs                     ; Additionally retain any sections
                                            ; that have references to current
                                            ; section
;-------------------------------------------------------------------------------
RESET       mov.w   #__STACK_END,SP         ; Initialize stackpointer
StopWDT     mov.w   #WDTPW|WDTHOLD,&WDTCTL  ; Stop watchdog timer

;-------------------------------------------------------------------------------
;Lee la entrada por P1.3, Se enciende el LED del P1.0 si P1.3 = 1
; Descripción: Chequea P1.3 dentro de un lazo, si es alto P1.0 es alto, si bajo,P1.0 bajo.
;
; MSP430G2xx3
; -----------------
; /|\| XIN|-
; | | |
; --|RST XOUT|-
; /|\ | |
; --o--|P1.4 P1.0|-->LED
; \|/
SetupP1 	bis.b #001h,&P1DIR 					; P1.0 como salida
 			mov.b #08h,&P1OUT 					; P1.3 se pone a uno, sino cero
 			bis.b #08h,&P1REN 					; P1.3 pullup
Mainloop 	bit.b #08h,&P1IN 					; P1.3 alto/bajo?
 			jc ON 								; jmp--> si P1.3 es 1
OFF 		bis.b #001h,&P1OUT 					; P1.0 = 0 / LED OFF
 			jmp Mainloop ;
ON 			bic.b #001h,&P1OUT 					; P1.0 = 1 / LED ON
 			jmp Mainloop
;-------------------------------------------------------------------------------


;-------------------------------------------------------------------------------
;           Stack Pointer definition
;-------------------------------------------------------------------------------
            .global __STACK_END
            .sect 	.stack

;-------------------------------------------------------------------------------
;           Interrupt Vectors
;-------------------------------------------------------------------------------
            .sect   ".reset"                ; MSP430 RESET Vector
            .short  RESET
