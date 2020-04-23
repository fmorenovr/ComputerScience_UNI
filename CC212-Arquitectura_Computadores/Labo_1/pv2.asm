;programa cortina
;menos significativos del puerto p1

	delay equ 118h
	org 8000h
;repite:
	mov R0,#00000101b
	mov R1,#10100000b
	mov A,R0
	add A,R1
	cpl A
	mov P1,A
	;mov R2,#0
inicio:
	mov A,#55	;100 milisegundos
	lcall delay	;retardo
	lcall suma
	mov P1,A
	sjmp inicio
	
suma:
	mov A,R0
	rr A
	mov R0,A
	mov A,R1
	rl A
	mov R1,A
	add A,R0
	cpl A
	ret
end