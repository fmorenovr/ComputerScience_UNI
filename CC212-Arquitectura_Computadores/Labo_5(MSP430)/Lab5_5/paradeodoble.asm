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
SetupP1		bis.b #41h,&P1DIR		; P1.0 como salida

Mainloop	mov.b #41h,&P1OUT 		; Cambia el estado de salida de P1.0

Wait		mov.w #20000,R15		; Retardo en R15
L1			dec.w R15				; Decrementa R15
			jnz L1					; Retardo se ha terminado?
			mov.b #0h,&P1OUT

			mov.w #20000,R15		; Retardo en R15
L2			dec.w R15				; Decrementa R15
			jnz L2					; Retardo se ha terminado?

			jmp Mainloop			; salta a Main loop
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
