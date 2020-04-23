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
	
; ====================================================
; subrutina initLCD4
; inicializa el LCD
;
; ----------------------------------------------------
initLCD4:
    clr LCD_RS      		; Pin Register Select del LCD
    clr LCD_RW      		; Pin Read/Write del LCD
    clr LCD_E       		; Pin Enable del LCD

    mov   r0, #Config 		; Function Set - data bits, lines, fonts
    lcall wrLCDcom4

    mov   r0, #onDsp     	; Enciende display
    lcall wrLCDcom4

    mov   r0, #entryMode 	; set Entry Mode
    lcall wrLCDcom4 		; increment cursor to right, no display shift

    mov   r0, #clrDsp  		; clear display, home cursor
    lcall wrLCDcom4
    ret

; ==========================================================
; subrutina setCGRAM4
; esta rutina fija la dirección del Character Generator RAM. El
; caracter [0..7] es localizado en el acumulador. La fila
; es localizado en el registro b. Las instrucciones 40h a 7Fh
; selecciona las direcciones CGRAM 0 a 3Fh (0 to 63 decimal).
;
; El tipo de caracter 5x7 es asumido. Dirección 0 del CGRAM corresponde
; a la primera fila del caracter 0, dirección 7 corresponde
; a la 8tava (última) fila del caracter 0, y dirección 3Fh
; corresponde a la 8tava fila del caracter 7.
;
; input  : acumulador indica el código del caracter[0..7]
;        : registro b almacena la fila [0..7]
; output : none
; ==========================================================
;
setCGRAM4:
         push  b
         mov   b, #8
         mul   ab           ; multiply character number by 8
         pop   b            ; b holds row number
         add   a, b         ; a holds CGRAM address
         add   a, #40h      ; convert to instruction

         mov   r0, a        ; place instruction
         lcall wrLCDcom4    ; issue command
         ret

   
; ====================================================
; subrutina wrLCDdata4
; escribe una palabra de datos al LCD
; datos deben ser localizados en R0
; ----------------------------------------------------
wrLCDdata4:
    	setb  LCD_RS    	; selecciona envio de datos
    	clr   LCD_RW   		; selecciona operación de escritura
    	push  ACC       	; salva el acumulador
    	mov   A, R0     	; pone byte de datos en el acumulador
    	mov C, ACC.7		;
    	mov P1.7, C		;
    	mov C, ACC.6		;
    	mov P1.6, C		;
    	mov C, ACC.5		;
    	mov P1.5, C		;
    	mov C, ACC.4		;
    	mov P1.4, C		;hasta aquí se envia el nibble mas significativo

	setb LCD_E		;
	clr  LCD_E		;
	mov C, ACC.3		;
	mov P1.7, C		;
	mov C, ACC.2		;
	mov P1.6, C		;
	mov C, ACC.1		;
	mov P1.5, C		;
	mov C, ACC.0		;
	mov P1.4, C		;hasta aquí se envia el nibble menos significativo

	lcall pulseEwait4   	; pulso en el pin Enable...
                            	; y espera por el Flag Busy que aclare
	pop ACC
	ret
; ====================================================
; subrutina wrLCDcom4
; escribe una palabra comando al LCD
; el comando debe ser localizado en R0
; ----------------------------------------------------
wrLCDcom4:
    	clr LCD_RS    	; limpia RS - y eso indica que son instrucciones a escribir 
    	clr LCD_RW      ; selecciona operación de escritura
    	push ACC
    	mov A,R0
	mov C, ACC.7	;
	mov P1.7, C	;
	mov C, ACC.6	;
	mov P1.6, C	;
	mov C, ACC.5	;
	mov P1.5, C	;
	mov C, ACC.4	;
	mov P1.4, C	;hasta aquí se envia el nibble mas significativo
;---------------------------------------
	setb LCD_E	;
	clr  LCD_E	;
	mov C, ACC.3	;
	mov P1.7, C	;
	mov C, ACC.2	;
	mov P1.6, C	;
	mov C, ACC.1	;
	mov P1.5, C	;
	mov C, ACC.0	;
	mov P1.4, C	; hasta aquí se envia el nibble menos significativo
;---------------------------------------
	lcall pulseEwait4   ; pulso en el pin Enable...
	pop ACC
	ret

; ====================================================
; subrutina pulseEwait4
; genera un pulso positivo sobre el pin enable del LCD.
; espera por el Flag Busy se aclare antes de retornar.
; input    : nada
; output   : nada
; destroys : LCD_RW, LCD_RS, LCD_DATA
; ----------------------------------------------------
pulseEwait4:
    clr   LCD_E
    setb  LCD_E           ; pulso en el pin Enable
    clr   LCD_E
    mov   LCD_DATA, #0ffh ; prepara el puerto para entrada
    setb  LCD_RW          ; prepara R/W para la operación de lectura
    push  ACC             ; salva contenidos del acumulador
pEw:
    setb  LCD_E           ; inicia el pulso Enable
    mov   A, LCD_DATA     ; lee el nibble de estado
    clr   LCD_E           ; termina el pulso en Enable
    setb  LCD_E           ; 
    clr   LCD_E
    jb    ACC.7, pEw      ; se hace el lazo mientras que Flag Busy es uno
    pop   ACC             ; restaura acumulador
    ret	
; ====================================================
; subrutina resetLCD4 - reinicia el LCD
; version en software de la operación
; power on reset
; ----------------------------------------------------
resetLCD4:
    clr   LCD_RS          ; Se pone a 0 el pin RS
    clr   LCD_RW          ; Se pone a 0 el pin Read / Write
    clr   LCD_E           ; Se pone a 0 el pin E

    clr   P1.7         	  ; se fijan los bits para...
    clr   P1.6            ; ... power-on-reset
    setb  P1.5
    setb  P1.4
                          ; paso 1
    setb  LCD_E           ; start Enable pulse
    clr   LCD_E           ; end Enable pulse
    mov   A, #4           ; retardo de 4 milisegundos
    lcall delay
                          ; paso 2
    setb  LCD_E           ; start Enable pulse
    clr   LCD_E           ; end Enable pulse
    mov   A, #1           ; retardo de 1 milisegundo
    lcall delay
                          ; paso 3
    setb  LCD_E           ; start Enable pulse
    clr   LCD_E           ; end Enable pulse
    mov   A, #1           ; retardo de 1 milisegundo
    lcall delay
    
    mov   R0, #Config     ; FUNCTION SET
    lcall wrLCDcom4

    mov   R0, #offDsp     ; display off
    lcall wrLCDcom4

    mov   R0, #clrDsp     ; clear display, home cursor
    lcall wrLCDcom4

    mov   R0, #entryMode  ; set ENTRY MODE
    lcall wrLCDcom4
    ret
    
; ==========================================================
; subrutina prtLCD4
; toma la cadena inmediatamente que sigue a la instrucción call
; y lo muestra sobre el LCD. La cadena es leida con la
; instrucción  mov a, @a+dptr.
; de este modo, la cadena se encuentra en memoria de datos.  
; la cadena debe ser terminada con un nulo (0).  
;
; input    : nada
; output   : nada
; destroys : acc, dptr
; ==========================================================
;
prtLCD4:
         pop   dph          ; pop return address into dptr
         pop   dpl
prtNext:
         clr  a             ; set offset = 0
         movc a,  @a+dptr   ; get chr from code memory
         cjne a, #0, chrOK  ; if chr = 0 then return
         sjmp retPrtLCD
chrOK:
         mov   r0, a
         lcall wrLCDdata4   ; send character
         inc   dptr         ; point at next character
         ljmp  prtNext      ; loop till end of string
retPrtLCD:
         mov   a,  #1h      ; point to instruction after string
         jmp   @a+dptr      ; return with a jump instruction

; ==========================================================
; subrutina placeCur4
; esta rutina fija la posición del cursor. La posición del cursor
; es localizado en el registro B. La posición del cursor empieza
; en 0. El acumulador es para el número de línea.
; input  : el acumulador indica el número de línea (1, 2)
;        : el registro B contiene la posición del cursor
; output : nada
; ==========================================================
;
placeCur4:
         dec  acc          ; acc=0 for line=1
         jnz  line2        ; if acc=0 then first line
         mov  a, b
         add  a, #080h     ; construct control word for line 1
         sjmp setcur
line2:
         mov  a, b
         add  a, #0C0h     ; construct control word for line 2
setcur:
         mov  r0, a        ; place control word
         lcall wrLCDcom4    ; issue command
         ret                                                                                                                          
    end
