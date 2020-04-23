;mostrar una barra de progreso con los leds
	delay equ 118h
	org 8000h
repite:	
	mov R0,#0	;contador
	mov p1,#0	;apaga
	mov A,#100
	lcall delay
Inicio:
	
	mov A,R0
	lcall leds
	mov P1,A
	inc R0
	mov A,#100
	lcall delay
	cjne R0,#8,Inicio	;si es  salta a repite (reinicia)
	sjmp repite
	
leds:
	inc A
	movc A,@A+PC
	ret
	db	00000001b
	db	00000011b
	db	00000111b
	db	00001111b
	db	00011111b
	db	00111111b
	db	01111111b
	db	11111111b
	
	END