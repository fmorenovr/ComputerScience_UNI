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
SetupP1
			bis.b #41h,&P1DIR 					; P1.0 como salida
 			mov.b #08h,&P1OUT 					; P1.3 se pone a uno, sino cero
 			bis.b #08h,&P1REN 					; P1.3 pullup
Mainloop
			bit.b #08h,&P1IN 					; P1.3 alto/bajo?
 			jc ON 								; jmp--> si P1.3 es 1
OFF
			bic.b #01h,&P1OUT 					; P1.6 = 1 / LED VERDE OFF
			bis.b #40h,&P1OUT 					; P1.0 = 0 / LED ROJO ON
 			jmp Mainloop 						;
ON
			bis.b #01h,&P1OUT 					; P1.6 = 1 / LED ROJO OFF
			bic.b #40h,&P1OUT 					; P1.6 = 1 / LED VERDE ON
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
