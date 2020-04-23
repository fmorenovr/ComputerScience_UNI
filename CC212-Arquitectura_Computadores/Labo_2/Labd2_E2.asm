;Encontrar el valor mas grande de una lista de numeros
;mostrar el resultado por display y enviarlo al puerto serie
prthex equ 13Fh
org 8000h

mov R5,#0		;R5 hace de el mas grande
mov R6,#11
mov R7,#0

loop:
	mov A,R7
	lcall tabla
	mov 50h,A
	subb A,R5	;comparo A con R5, C=0 si A>R5
	jnc intercambio	;salta a intercambio si C=0  (C = Carry)
sigue:
	inc R7
	djnz R6, loop
	mov 40h,R5
	mov A,40h
	lcall prthex
	ljmp 2f0h
	
intercambio:
	mov R5,50h
	sjmp sigue
		
tabla:
	inc A
	movc A,@A+PC
	ret
	db 3,2,14,5,4,7,6,22,0,1,4
	
end