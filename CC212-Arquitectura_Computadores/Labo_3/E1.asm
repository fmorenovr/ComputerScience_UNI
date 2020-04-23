;Ejemplo de interrupci�n debido al timer 0
setintvec	equ 145h
sndchr		equ 148h
delay		equ 118h
print		equ 136h

org 8000h
mov TMOD,#20h	;Modo 0 del timer 0, para que no interfiera 
		;con la comunicaci�n serial
	mov a, #1	;Tiemr 0 es la fuende de interrupci�n
	mov dptr, #IntTimer0	;IntTimer0 es la direcci�n inicial de
	lcall setintvec	;posibilita tener el ISR en RAM
	setb TR0	;incia el timer 0
	setb ET0	;habilita interrupci�n del timer 0
;----------------------
	setb IT1	; fija la interrupci�n externa sensible
			; en el flanco de bajada
	mov a, #2	; fuente de interrupci�n externa 0
	mov dptr, #ISR1	; fijar dptr con la direcci�n de inicio
			; de la interrupci�n externa 0 para llamar a
			; setintvec
	lcall setintvec ; fija el ISR para INT0
	setb EX1 ; habilita interrupci�n externa 0 en el registro IE
	setb p3.3 ; fija el pin p3.2 como entrada bot�n conectado
	setb p3.2
;------------------------------
	setb IT0	; fija la interrupci�n externa sensible
			; en el flanco de bajada
	mov a, #0	; fuente de interrupci�n externa 0
	mov dptr, #ISR0	; fijar dptr con la direcci�n de inicio
			; de la interrupci�n externa 0 para llamar a
			; setintvec
	lcall setintvec ; fija el ISR para INT0
	setb EX0 	; habilita interrupci�n externa 0 en el registro IE
	setb EA 	; flag de interrupci�n maestra del registro IE
	setb p3.2 	; fija el pin p3.2 como entrada bot�n conectado
	setb p3.3
;----------------------------
	setb EA		;habilita interripci�n global
	mov R6,#2	;contador
	;sjmp $
repite:
	mov R4,#10
	mov R2,#0
loop:
	mov A,R2
	add A,#30h
	lcall sndchr
	mov A,#250
	lcall delay
	mov A,#0dh
	lcall sndchr
	inc R2
	djnz R4,loop
	sjmp repite

IntTimer0:
	djnz R6,sale
	mov R6,#2
	clr TF0
	clr TR0
	mov TH0,#34h
	mov TL0,#13h
	setb TR0
no_overflow:
	jnb TF0,no_overflow
	clr TF0
	cpl P1.0
sale:
	clr TF0
	reti
ISR0:
	lcall print
	db 0dh,0ah,"Me interrumpen :v P0",0ah,0
	reti
ISR1:
	lcall print
	db 0dh,0ah,"Me interrumpen :v P1",0ah,0
	reti
end