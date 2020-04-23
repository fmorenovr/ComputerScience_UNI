;===================================
;lcd_TMC51_4_NC.asm
;Programa que muestra 
;caracteres nuevos que han sido creados
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
print	  equ 136h
crlf      equ 115h
getchr	  equ 121h
	org 8000h
inicio:
	lcall resetLCD4    	; power on reset
	mov A,#1
    	lcall delay		; un retardo de 1 milisegundo
	lcall initLCD4		; inicializa el LCD (para que sea MODO 4 bits,
				; se usen 2 filas, etc.).
	mov A,#1
    	lcall delay		; retardo de 1 milisegundo
	mov R0,#clrDsp		; limpia el display
	lcall wrLCDcom4		; envio de comando o orden para ejecutar
	mov A,#2		; indica que se va tener 2 milisegundos de retardo
	lcall delay		; retardo de 2 milisegundos
    	
; Vamos a definir algunos caracteres personalizados
; primero se fija la dirección CGRAM, luego descargas los
; patrones del font. Caracteres 0 y 1 son definidos
; sucesivamente. Caracter 0 es una Caja, y caracter
; 1 es un Diamante. Para una fila en blanco usamos
; el número 20h es enviado.  Notar que los últimos 5
; bits de 20h son 0s, esto es para evitar enviar 0,
; que señalaría el final de la cadena de datos.

    mov   a, #0     ; selecciona caracter 0
    mov   b, #0     ; selecciona la fila 0
    lcall setCGRAM4
    lcall prtLCD4
    db    1Fh, 11h, 11h, 11h, 11h, 11h, 1Fh, 20h    	; Box
    db    20h, 04h, 0Eh, 1Fh, 0Eh, 04h, 20h, 20h 	; Diamond
    db    20h, 11h, 20h, 04h, 20h, 11h, 0Eh, 20h	; Carita feliz
    db	  20h, 0Eh, 1Fh, 0Eh, 04h, 1Fh, 04h, 04h,0	; flor

; limpiando el display selecciona el DDRAM en la 
; posición 0(homes the cursor) en preparación a 
; mostrar los nuevos caracteres.
    mov   r0, #clrDsp
    lcall wrLCDcom4
     mov A,#1		; indica que se va tener 1 milisegundo de retardo
    lcall delay
; Muestra caracter.Desde que 0 implica un fin de la cadena,
; usa el caracter 8. Nota que los caracteres del 0..7
; son los mismos que los caracteres del 8..Fh.
    mov   a, #1               ; linea 1
    mov   b, #0               ; posición 0
    lcall placeCur4
    lcall prtLCD4             ; print message
    db    "     Caja : ", 8, 0
; move cursor to line 2
    mov   a, #2               ; linea 2
    mov   b, #0               ; posición 0
    lcall placeCur4

    lcall prtLCD4             ; muestra mensaje
    db    " Diamante : ", 1, 0

    lcall waitKey      		; espera para presionar cualquier tecla
    mov   r0, #clrDsp
    lcall wrLCDcom4
     mov A,#1			; indica que se va tener 1 milisegundo de retardo
    lcall delay
    mov   a, #1               	; linea 1
    mov   b, #0               	; posición 0
    lcall placeCur4
    lcall prtLCD4             	; print mensaje
    db    "Carita feliz : ", 2,0
    mov   a, #2               	; linea 2
    mov   b, #0               	; posición 0
    lcall placeCur4
    lcall prtLCD4             	; print mensaje
    db    "        Flor : ", 3, 0
    lcall waitKey
    jmp $	       ; se queda aquí dando vueltas
; waitKey es una utilidad que imprime el mensaje
; "presione una tecla para continuar" y luego espera hasta
; que un caracter es recibido.
waitKey:
    lcall print
    db    "presione una tecla para continuar", 0
    lcall crlf
    lcall getchr       ; espera por una tecla que se presione
    ret
$include(SubrutinasLCD.inc)
end