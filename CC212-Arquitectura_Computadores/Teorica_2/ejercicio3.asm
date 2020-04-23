;Pregunta 3: opera los guardados en la memoria 41h hasta 46h

display equ 11Bh

org 8000h

	;mov 41h,#3
	;mov 42h,#80
	;mov 43h,#10
	;mov 44h,#-80
	;mov 45h,#-20
	;mov 46h,#-145
	clr C
	mov A,#2
	add A,43h
	clr C
	subb A,44h
	clr C
	subb A,45h
	clr C
	subb A,46h
	mov R0,A
	mov A,41h
	mov B,42h
	clr C
	mul AB
	add A,R0
	lcall display
	mov P1,A


end	