delay equ 118h

org 8000h

inicio:
	mov P1,#0h
	jnb P3.2,leds		;se inicia el recorrido
	sjmp inicio
	
leds:
	mov A,#10000000b	
	mov P1,A
;	mov R0,A		
	mov R2,#7h
	
loop1:	
	rr A
	mov R0,A
	mov A,#50
	lcall delay
	mov A,R0
	mov P1,A
	jnb P3.3,inicio		;se detiene todo al presionar P3.3
	djnz R2,loop1		;repite hasta llegar al final
	mov R2,#7h		;se actualiza R2 para regresar la luz
	sjmp loop2		;comienza a retroceder
	
loop2:	
	rl A
	mov R0,A
	mov A,#50
	lcall delay
	mov A,R0
	mov P1,A
	jnb P3.3,inicio		;se detiene todo al presionar P3.3
	djnz R2,loop2		;repite hasta llegar al final
	mov R2,#7h		;se actualiza R2 para regresar la luz
	sjmp loop1		;comienza a retroceder
	
end
