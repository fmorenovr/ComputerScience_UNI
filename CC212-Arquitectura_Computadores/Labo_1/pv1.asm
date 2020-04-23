;programa q enciende los 4 bits
;menos significativos del puerto p1

	delay equ 118h
	org 8000h
	mov P1,#01h	;apaga leds
	mov A,#01h
	mov R1,#7h
repite1:
	mov R0,A
	mov A,#25	;100 milisegundos
	lcall delay	;retardo
	mov A,R0
	rl A
	mov P1,A
	djnz R1,repite1
	mov R1,#7h
	lcall repite2
repite2:	
	mov R0,A
	mov A,#25	;100 milisegundos
	lcall delay	;retardo
	mov A,R0
	rr A
	mov P1,A
	djnz R1,repite2
	mov R1,#7h
	sjmp repite1
	
end