;programa de multiplicacion los valores son almacenados en 40h y 41 h
;el resultado es almacenado en 42h y 43h
	org 8000h
	mov a,40h
	clr c
	mov b,41h
	mul ab
	mov 42h,b
	mov 43h,a
	ljmp 2F0H	; retorna al monitor
	end