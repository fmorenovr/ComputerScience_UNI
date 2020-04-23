;Pregunta 1: se inicia una barra de progreso al presionar P3.2

delay equ 118h

org 8000h

inicio:
	mov P1,#0h	;se apagan las luces
	jnb P3.2,barra
	sjmp inicio	;se mantienen las luces apagadas hasta presionar P3.2

barra:
	mov A,#1b	;inicia la barra
	mov P1,A
	mov R1,#8h	

repite:
	rl A
	add A,#1b	;desplaza la barra y rellena el espacio vacío
	mov R0,A	;guarda temporalmente A
	mov A,#100
	lcall delay
	mov A,R0	;regresa el valor de A
	mov P1,A
	djnz R1,repite	;se repite hasta llenar la barra
;	mov R1,#8h
	sjmp barra	;reinicia la barra
end