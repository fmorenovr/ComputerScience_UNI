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
SetupP1		bis.b #41h,&P1DIR			; P1.0 como salida
 										;
Mainloop	xor.b #01h,&P1OUT			; Cambia P1.0,
			call #Espera
			call #Espera

			xor.b #01h,&P1OUT
			xor.b #40h,&P1OUT
			call #Espera
			call #Espera
			xor.b #40h,&P1OUT
			jmp Mainloop 				; Lazo principal aqui


Espera 		mov.w #050000,R15 			; Retardo se mueve a R15
L1			dec.w R15	 				; Decrementa R15
 			jnz L1 						; se acabó el retardo?
 			Ret

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
