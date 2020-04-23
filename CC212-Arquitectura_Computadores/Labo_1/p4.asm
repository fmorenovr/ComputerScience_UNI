;Programa de resta x-y
;utiliza las direcciones 30h y 31h
;tambien la direccion 32h para colocar el resultado
	
	org 8000h ; es 8000h xq desde 0 hasta 7FFF esta ocupado x l firmware
	mov A,30h
	clr C
	subb A,31h
	mov 32h,A
	sjmp $	
	end