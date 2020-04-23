;menu frecuencias
print	equ 136h
getbyt	equ 11Eh

org 8000h
lcall print
db 0dh,0ah," MENU DE PROGRAMA DE FRECUENCIA DE Hz "
db 0dh,0ah,"=======================================",0dh,0ah
db 0dh,0ah,"01) 10 Hz"
db 0dh,0ah,"02) 15 Hz"
db 0dh,0ah,"03) 20 Hz"
db 0dh,0ah,"Seleccione la opcion: ",0
lcall getbyt
cjne A,#1,otraopcion
sjmp diezhz

diezhz:

	mov TMOD,#81h
	mov TH0,#87h	;inicializa el timer 1 con "7DCB"
	mov TL0,#0FEh	;65536-33333 = 34814 = 87FEh
	repite:
		setb TR0	;arranca el tiemr 0
	no_overflow:
		jnb TF0,no_overflow
		clr TR0
		cpl P1.0	;se genera 15Hz
		clr TF0
		mov TH0,#87h
		mov TL0,#0FEh
		sjmp repite
	
quincehz:

	mov TMOD,#81h
	mov TH0,#87h	;inicializa el timer 1 con "7DCB"
	mov TL0,#0FEh	;65536-33333 = 34814 = 87FEh
	repite1:
		setb TR0	;arranca el tiemr 0
	no_overflow1:
		jnb TF0,no_overflow1
		clr TR0
		cpl P1.0	;se genera 15Hz
		clr TF0
		mov TH0,#87h
		mov TL0,#0FEh
		sjmp repite1
	
veintehz:

	mov TMOD,#81h
	mov TH0,#87h	;inicializa el timer 1 con "7DCB"
	mov TL0,#0FEh	;65536-33333 = 34814 = 87FEh
	repite2:
		setb TR0	;arranca el tiemr 0
	no_overflow2:
		jnb TF0,no_overflow2
		clr TR0
		cpl P1.0	;se genera 15Hz
		clr TF0
		mov TH0,#87h
		mov TL0,#0FEh
		sjmp repite2
	

otraopcion:
	cjne A,#02,quincehz
	sjmp veintehz
	
end