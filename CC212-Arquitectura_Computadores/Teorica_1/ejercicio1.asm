;programa de suma x+y
;utiliza las direcciones 23h y 46h
;también la dirección 30h para guardar la respuesta
	
	org 8000h	;de 0h a 7FFFh está ocupado por la memoria interna
			;que es el firmware
	mov R6,#24h
	mov R7,#46h
	clr C		;C es un carry que se está limpiando
	mov A,R6
	add A,R7
	mov 30h,A
	sjmp $		;salta aquí indefinidamente
	end