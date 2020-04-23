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

	org 8000h
; poniendo datos en la RAM
	MOV 30H, #'A'
	MOV 31H, #'B'
	MOV 32H, #'C'
	mov 33H, #'D'
	mov 34H, #'E'
	MOV 35H, #0		; caracter de indicación de fin de envio
	lcall resetLCD4    	; power on reset
	mov A,#1		;1milisegundo para que el display reaccione a las instrucciones
    	lcall delay
	lcall initLCD4
	mov A,#1
    	lcall delay	;todo esto es obligatorio para iniciar el display
    	
;=====================================================
; Comienza el envio de datos
	MOV R1, #30H		; datos a enviar ya han sido almacenados en la RAM 
				; del 8051, dirección de inicio 30H
loop:
	mov A, @R1		; 
	jz finish		; si A es 0, entonces termina salta a "finish"
	mov R0,A
	lcall wrLCDdata4	; envia datos en el registro "A" al módulo LCD
	inc R1			; 
	jmp loop		; repite
finish:
	sjmp $

$include(SubrutinasLCD.inc)
end