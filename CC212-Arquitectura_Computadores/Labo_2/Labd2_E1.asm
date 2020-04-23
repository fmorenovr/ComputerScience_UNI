;Programa 1 del lab2 dirigido
;Hacer un programa que dado un número hexadecimal, lo convierta
;en un número de 3 dígitos almacenados en 40h, 41h y 42h y los envíe
;al terminal serial
sndchr	equ 148h
crlf	equ 115h
print	equ 136h
getbyt	equ 11Eh

org 8000h
;mov A,#0F5h
	lcall print
	db "Ingrese Numero : ",0  ;siempre se coloca 0 al final
	lcall getbyt		;el número ingresado se coloca en A

cifras:
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
	ljmp 2f0
end
	