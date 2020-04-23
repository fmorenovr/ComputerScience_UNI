;programa a parpadea un led conectado al pin p1.3
	sdelay equ 142h	;retardo de 1 seg
	delay equ 118h	;retardo en milisegundos, el valor de los miliseg se guarda en A
	org 8000h

repite:
	mov P1,#0FFh
	mov a,#100
	lcall delay
	mov P1,#0
	mov a,#100
	lcall delay
	sjmp repite
	end