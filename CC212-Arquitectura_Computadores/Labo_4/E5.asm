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
	db "SEGUNDERO:",0
	mov A,#1
	lcall delay
	
	lcall print
	db "SEGUNDERO: ",0ah,0
	
	mov A,#2
	mov B,#10
	lcall placeCur4
	mov A,#1
	lcall delay
	mov R1,#6
	mov R2,#30h
	
denuevo:
	lcall print
	db 0dh,"         ",0
	mov A,R2
	lcall sndchr
	mov A,R2
	mov R0,A
	lcall wrLCDdata4
	mov r0,#offcur		;no se ve el cursor
	lcall wrlcdcom4
	lcall segs0_a_9
	inc R2
	mov r0,#shlfcur
	lcall wrlcdcom4
	mov r0,#offcur	;no se ve el cursor
	lcall wrlcdcom4
	djnz R1,denuevo
	mov R1,#6
	mov R2,#30h
    	sjmp denuevo
    	
;==========================================================
;Subrutina segs0_a_9 de display LCD para cuenta en segundos
;Visualizacion de Segundos desde 0 a 9.
;==========================================================
segs0_a_9:
    mov r0,#30h		;código ascii del 0
    lcall wrLCDdata4	;se envía r0 al display
    mov r0,#shlfcur	;desplaza el cursor 1 posicion al a izquierda
    lcall wrlcdcom4	;activa el shifcur
    mov r0,#offcur	;no se ve el cursor
    lcall wrlcdcom4	;activa el offcur
    mov A,#30h
    lcall sndchr
    mov A,#0dh
    lcall sndchr
    lcall print
    db "           ",0
    mov A,#100
    lcall delay
    
    mov r0,#31h
    lcall wrLCDdata4
    mov r0,#shlfcur
    lcall wrlcdcom4
    mov r0,#offcur	;no se ve el cursor
    lcall wrlcdcom4
    mov A,#31h
    lcall sndchr
    mov A,#0dh
    lcall sndchr
    lcall print
    db "           ",0
    mov A,#100
    lcall delay
    
    mov r0,#32h
    lcall wrLCDdata4
    mov r0,#shlfcur
    lcall wrlcdcom4
    mov r0,#offcur	;no se ve el cursor
    lcall wrlcdcom4
    mov A,#32h
    lcall sndchr
    mov A,#0dh
    lcall sndchr
    lcall print
    db "           ",0
    mov A,#100
    lcall delay
    
    mov r0,#33h
    lcall wrLCDdata4
    mov r0,#shlfcur
    lcall wrlcdcom4
    mov r0,#offcur	;no se ve el cursor
    lcall wrlcdcom4
    mov A,#33h
    lcall sndchr
    mov A,#0dh
    lcall sndchr
    lcall print
    db "           ",0
    mov A,#100
    lcall delay
    
    mov r0,#34h
    lcall wrLCDdata4
    mov r0,#shlfcur
    lcall wrlcdcom4
    mov r0,#offcur	;no se ve el cursor
    lcall wrlcdcom4
    mov A,#34h
    lcall sndchr
    mov A,#0dh
    lcall sndchr
    lcall print
    db "           ",0
    mov A,#100
    lcall delay
    
    mov r0,#35h
    lcall wrLCDdata4
    mov r0,#shlfcur
    lcall wrlcdcom4
    mov r0,#offcur	;no se ve el cursor
    lcall wrlcdcom4
    mov A,#35h
    lcall sndchr
    mov A,#0dh
    lcall sndchr
    lcall print
    db "           ",0
    mov A,#100
    lcall delay
    
    mov r0,#36h
    lcall wrLCDdata4
    mov r0,#shlfcur
    lcall wrlcdcom4
    mov r0,#offcur	;no se ve el cursor
    lcall wrlcdcom4
    mov A,#36h
    lcall sndchr
    mov A,#0dh
    lcall sndchr
    lcall print
    db "           ",0
    mov A,#100
    lcall delay
    
    mov r0,#37h
    lcall wrLCDdata4
    mov r0,#shlfcur
    lcall wrlcdcom4
    mov r0,#offcur	;no se ve el cursor
    lcall wrlcdcom4
    mov A,#37h
    lcall sndchr
    mov A,#0dh
    lcall sndchr
    lcall print
    db "           ",0
    mov A,#100
    lcall delay
    
    mov r0,#38h
    lcall wrLCDdata4
    mov r0,#shlfcur
    lcall wrlcdcom4
    mov r0,#offcur	;no se ve el cursor
    lcall wrlcdcom4
    mov A,#38h
    lcall sndchr
    mov A,#0dh
    lcall sndchr
    lcall print
    db "           ",0
    mov A,#100
    lcall delay
    
    mov r0,#39h
    lcall wrLCDdata4
    mov r0,#shlfcur
    lcall wrlcdcom4
    mov r0,#offcur	;no se ve el cursor
    lcall wrlcdcom4
    mov A,#39h
    lcall sndchr
    mov A,#0dh
    lcall sndchr
    lcall print
    db "           ",0
    mov A,#100
    lcall delay
    ret

$include(SubrutinasLCD.inc)
end