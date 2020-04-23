;Programa que parpadea 

sdelay equ 142h   ;retardo de 1 segundo de tiempo
delay equ 118h	;retardo en milisegundos, 
		;el valor de los milisegundos se guarda en A
org 8000h
repite:
	mov P1,#0FFh
	mov A,#100
	lcall delay
	mov P1,#0
	mov A,#100
	lcall delay
	sjmp repite
	end