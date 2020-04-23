;Genera 15 Hz

sndchr	equ 148h
org 8000h

mov TMOD,#81h
mov TH0,#87h	;inicializa el timer 1 con "7DCB"
mov TL0,#0FEh	;65536-33333 = 34814 = 87FEh
repite:
	setb TR0	;arranca el tiemr 0
no_overflow:
	jnb TF0,no_overflow
	clr TR0
	cpl P1.0	;se genera 15Hz
	clr TF0
	mov TH0,#87h
	mov TL0,#0FEh
	sjmp repite
	end