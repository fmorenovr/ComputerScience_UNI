;Imprime los 6 primeros terminos de la serie de fibonacci
sndchr	equ 148h
crlf	equ 115h

org 8000h

mov A,#1	;acumulador de fibonacci
mov R6,#1	;auxiliar 1
mov R5,#0	;auxiliar 2
mov R7,#7	;numero de terminos de terminos

fibonacci:
	mov R4,A
	add A,#30h	;imprime el valor de A
	lcall sndchr
	mov A,#20h	;imprime el espacio en blanco
	lcall sndchr
	;mov A,R4	
	mov A,R6
	mov R5,A
	mov A,R4
	mov R6,A
	mov A,R4
	add A,R5
	
	djnz R7,fibonacci
	lcall crlf
	ljmp 2f0h
end