;programa que cuenta de 0 a F y que es interrumpido por el puerto p3.2
delay	equ 118h
display equ 11Bh
setintvec equ 145h
print	equ 136h
sndchr equ 148h

org 8000h
	mov TMOD,#20h	;Modo 0 del timer 0, para que no interfiera 
		;con la comunicación serial

	setb IT0	; fija la interrupción externa sensible
	setb IT1
			; en el flanco de bajada
	mov A, #0	; fuente de interrupción externa 0
	mov dptr, #ISR0	; fijar dptr con la dirección de inicio
			; de la interrupción externa 0 para llamar a
			; setintvec
	lcall setintvec
	mov A,#2
	mov dptr,#ISR1
	
	lcall setintvec ; fija el ISR para INT0
	setb EX0 ; habilita interrupción externa 0 en el registro IE
	setb EX1
	setb EA
	setb p3.2 ; fija el pin p3.2 como entrada botón conectado		ljmp 2f0h
	setb p3.3

loop:
	mov R7,#16
	mov R6,#0
repite:
	mov A,R6
	lcall display
	cpl A
	mov P1,A
	mov A,R6
	add A,#30h
	lcall sndchr
	mov A,#0dh
	lcall sndchr
	mov A,#150
	inc R6
	lcall delay
	djnz R7,repite
	sjmp loop
ISR0:
	lcall print
	db 0dh,0ah,"Arquitectura de Computadores",0ah
	db 0dh,"Prof. Martin Cruz Salazar",0ah,0dh,0
	reti
ISR1:
	ljmp 2f0h
end