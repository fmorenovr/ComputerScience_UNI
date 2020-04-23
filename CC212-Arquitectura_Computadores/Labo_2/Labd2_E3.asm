;Hacer un programa que calcule el factorial de 5
;posiciones de memoria 31h,32h,33h
;enviarlo al terminal
sndchr	equ 148h
crlf	equ 115h

org 8000h
mov R6,#1	;hace de acumulador
mov R7,#2	;hace de contador

loop:
	mov A,R6
	mov B,R7
	mul AB
	inc R7
	mov R6,A
	mov A,R7
	cjne A,#6,loop
	mov 40h,R6
	lcall numero
	ljmp 2f0h

numero:
	mov A,40h
	mov B,#10
	div AB		;Divido A entre B luego => A=cociente, B=residuo
	mov 42h,B
	mov R0,A
	mov B,#10
	div AB
	mov 41h,B
	mov 40h,A
	lcall crlf
	mov A,40h
	add A,#30h
	lcall sndchr
	mov A,41h
	add A,#30h
	lcall sndchr
	mov A,42h
	add A,#30h
	lcall sndchr
	lcall crlf
	ret
	
end