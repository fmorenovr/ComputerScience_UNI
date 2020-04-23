;Averigua si un numero es primo o no
print	equ 136h
sndchr	equ 148h
getbyt	equ 11Eh
crlf 	equ 115h

org 8000h

otravez:
	lcall print
	db "Ingrese el Numero a averiguar: ",0
	lcall getbyt	;ingresa por teclado
	mov 30h,A
	cjne	A,#2,otroN
	sjmp SiPrimo
otroN:
	mov R2,#2
continua:
	mov A,30h
	mov B,R2
	div AB
	mov A,B
	cjne A,#0,sigue
	sjmp Noprimo
sigue:
	inc R2
	mov A,R2
	cjne A,30h,continua
	sjmp Siprimo
NoPrimo:
	mov A,30h
	lcall numero
	lcall print
	db " no es Primo",0dh,0Ah,0
	lcall crlf
	ljmp otravez
SiPrimo:
	mov A,30h
	lcall numero
	lcall print
	db " si es Primo",0dh,0Ah,0
	lcall crlf
	ljmp otravez
numero:
	mov B,#100
	div AB
	mov 39h,A
	mov A,B
	mov B,#10
	div AB
	mov 40h,A
	mov 41h,B
	mov A,#0Ah
	lcall sndchr
	mov A,#0dh
	mov A,39h
	add A,#30h
	lcall sndchr
	mov A,40h
	add A,#30h
	lcall sndchr
	mov A,41h
	add A,#30h
	lcall sndchr
	ret
	
end