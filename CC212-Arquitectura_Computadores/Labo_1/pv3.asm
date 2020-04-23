;programa q enciende los 4 bits
;menos significativos del puerto p1

	delay equ 118h
	org 8000h
	mov P1,#0h	;apaga leds
	mov A,#01h

inicio:	
	jnb P3.2,repite1
	jnb P3.3,repite2
	sjmp inicio

repite1:
	mov R0,A
	mov A,#200	;100 milisegundos
	lcall delay	;retardo
	mov A,R0
	rl A
	mov P1,A
	jnb p3.3,repite2
	sjmp repite1
repite2:	
	mov R0,A
	mov A,#200	;100 milisegundos
	lcall delay	;retardo
	mov A,R0
	rr A
	mov P1,A
	jnb P3.2,repite1
	sjmp repite2
	
end