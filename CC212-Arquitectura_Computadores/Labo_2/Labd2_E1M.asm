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
	mov R1,#3		;cantidad de cifras
	mov R0,#0

cifras:
	mov B,#10
	div AB		;Divido A entre B luego => A=cociente, B=residuo
	mov 42h,B
	mov R2,A
	mov A,R0
	lcall tabla1
	mov A,B
	mov A,R2
	inc R0
	djnz R1,cifras
	
	mov 40h,A
	lcall crlf
	mov A,40h	;salto de linea
	
	mov R0,#0
	mov R1,#3
	
show:
	lcall tabla2
	lcall sndchr
	inc R0
	mov A,R0
	djnz R1,show
	lcall crlf
	ljmp 2f0h
	
tabla1:
	inc A
	movc A,@A+PC
	ret
	db 42h,41h,40h
	
tabla2:
	inc A
	movc A,@A+PC
	ret
	db 40h,41h,42h

end
	