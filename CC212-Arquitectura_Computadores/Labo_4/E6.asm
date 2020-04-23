;===================================
;lcd_TMC51_2.asm
;Programa que muestra los caracteres
;A,B,C,D y E en el display LCD
;===================================
LCD_DATA  equ 90h	; Puerto P1
LCD_RS    equ 91h 	; p1.1 Register Select del LCD 
LCD_RW    equ 92h 	; p1.2 Read/Write del LCD 
LCD_E     equ 93h 	; p1.3 Enable del LCD

; Instrucciones para el LCD
Config 	  equ 28h	; Function Set: Tamaño del bus de datos(4 bits), número de líneas es 2 y tamaño del font es 5x7
entryMode equ 6    	; Modo de Entrada: Incrementa el cursor, no desplaza display

; instrucciones para el control del cursor
 offCur    equ  0Ch	; Apaga el cursor(lo desaparece)
 lineCur   equ  0Eh	; Cursor aparece como una línea
 blinkCur  equ  0Dh	; Hace parpadear el cursor
 combnCur  equ  0Fh	; Encender el Display, encender cursor y parpadea el caracter en la posición del cursor
 homeCur   equ  02h	; Coloca el cursor en el extremo izquierdo de la primera fila
 shLfCur   equ  10h	; Desplaza al cursor a la izquierda
 shRtCur   equ  14h	; Desplaza al cursor a la derecha


; instrucciones para el control del display
 clrDsp    equ  01h	; Limpia el display así como el contenido de la memoria
 onDsp     equ  0Eh	; Display On, muestra caracteres en el display
 offDsp    equ  0Ah	; Display Off, no limpia el contenido de la memoria
 
; ----------------------------------------------------
; subrutinas del TMC51     Registros usados
; ----------------------------------------------------
delay	  equ 118h  	; a
print     equ 136h  	; a, dptr
sdelay	  equ 142h
sndchr    equ 148h

	org 8000h

	lcall resetLCD4    	; power on reset
	mov A,#1
    	lcall delay		; un retardo de 1 milisegundo
	lcall initLCD4		; inicializa el LCD (para que sea MODO 4 bits,
				; se usen 2 filas, etc.).
	mov A,#1
    	lcall delay		; retardo de 1 milisegundo
    	
    	mov R0,#clrDsp
    	lcall wrLCDcom4
    	mov A,#1
    	lcall delay

	mov A,#1
	mov B,#0
	lcall placeCur4
	mov A,#1
	lcall delay
	lcall prtLCD4
	db "Segundero:",0
	mov A,#1
	lcall delay
	
	lcall print
	db "Segundero:  ",0ah,0dh,0
	
	mov A,#2
	mov B,#11
	lcall placeCur4
	mov A,#1
	lcall delay
		
denuevo:
	lcall decimaSegs0_a_59
	sjmp denuevo

 posicionOnce:
 	mov R4,#11
 sigue:
 	mov A,#20h
 	lcall sndchr
 	djnz R4,sigue
 	ret
    	
;==========================================================
;Subrutina segs0_a_9 de display LCD para cuenta en segundos
;Visualizacion de Segundos desde 0 a 9.
;==========================================================
decimaSegs0_a_59:
	mov R3,#60
	mov R2,#0
lazo:
	mov A,R2
	subb A,#10		;si es positivo el carro es 0
	jnc cuenta_desde_9
	lcall posicionOnce
	mov A,R2
	add A,#30h
	mov R0,A
	lcall sndchr
	mov A,#20h
	lcall sndchr
	mov A,0Dh
	lcall sndchr
	lcall wrLCDdata4
	mov R0,#shlfcur
	lcall wrLCDcom4
	mov R0,#offcur
	lcall wrLCDcom4
	mov A,#100
	lcall delay
	sjmp salta1
cuenta_desde_9:
	mov A,R2
	lcall obtiene_digitos
	add A,#30h
	mov R0,A
	lcall wrLCDdata4
	mov A,B
	add A,#30h
	mov R0,A
	lcall wrLCDdata4
	lcall posicionOnce
	mov A,30h
	add A,#30h
	lcall sndchr
	mov A,#0dh
	lcall sndchr
	mov R0,#shlfcur
	lcall wrLCDcom4
	mov R0,#shlfcur
	lcall wrLCDcom4
	mov R0,#shlfcur
	lcall wrLCDcom4
	mov R0,#shlfcur
	lcall wrLCDcom4
	mov A,#100
	lcall delay
salta1:
	inc R2
	djnz R3,lazo
	ret
	
obtiene_digitos:
	mov B,#10
	div AB
	mov 30h,A
	mov 31h,B
	ret

$include(SubrutinasLCD.inc)
end