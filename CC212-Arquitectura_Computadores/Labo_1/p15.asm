;p1.0 y P1.1 parpadean alternadamente

	delay equ 118h
	org 8000h
	mov P1,#0	;apaga leds
repite:
	setb P1.0	;enciende p1.0
	clr P1.1
	mov A,#50	;100 milisegundos
	lcall delay	;retardo
	clr P1.0
	setb P1.1
	mov A,#50
	lcall delay
	sjmp repite
	end