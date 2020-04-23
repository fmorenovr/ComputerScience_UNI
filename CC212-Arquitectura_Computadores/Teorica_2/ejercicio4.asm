;Pregunta 4: al presionar P3.2 se inicia el contador desde 0
;cuando se presiona P3.3 el contador se detiene hasta presionar de nuevo el P3.2
;que hace continuar el conteo desde su último valor

delay equ 118h
display equ 11Bh

org 8000h

inicio:
	mov P1,#0h
	jnb P3.2,contador
	sjmp inicio
	
parar:
	jnb P3.2,lazo
	sjmp parar

contador:

	mov R2,#10
	mov R3,#0
lazo:
	jnb P3.3,parar
	mov A,R3
	lcall display
	cpl A
	mov P1,A
	mov R1,A
	mov A,#200
	lcall delay
	inc R3
	mov A,R1
	djnz R2,lazo
	sjmp contador
		
	end