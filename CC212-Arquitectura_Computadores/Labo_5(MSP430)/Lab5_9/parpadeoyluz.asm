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
 			jc OFF								; jmp--> si P1.3 es 1
ON
			bis.b #41h,&P1OUT 					; P1.6 = 1 / LED ROJO OFF
Mainloop2
			xor.b #01h,&P1OUT 					; Cambia el estado de salida de P1.0
			mov.w #20000,R15					; Retardo en R15
L1
			dec.w R15							; Decrementa R15
			jnz L1								; Retardo se ha terminado?
			bit.b #08h,&P1IN 					; P1.3 alto/bajo?
 			jc OFF								; jmp--> si P1.3 es 1
			jmp Mainloop2						; salta a Main loop
 			jmp Mainloop
OFF
			bic.b #41h,&P1OUT 					; P1.6 = 1 / LED ROJO OFF
 			jmp Mainloop 						;
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
