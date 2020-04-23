; waitKey es una utilidad que imprime el mensaje
; "presione una tecla para continuar" y luego espera hasta
; que un caracter es recibido.
waitKey:
    	lcall print
    	db    "presione una tecla para continuar", 0
    	lcall crlf
    	lcall getchr       ; espera por una tecla que se presione
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
; subrutina initLCD4 - inicializa el LCD
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
    
; ====================================================
; subrutina wrLCDdata4
; escribe una palabra de datos al LCD
; datos deben ser localizados en R0
; ----------------------------------------------------
wrLCDdata4:
    	setb  LCD_RS    ; selecciona envio de datos
    	clr   LCD_RW   	; selecciona operación de escritura
    	push  ACC       ; salva el acumulador
    	mov   A, R0     ; pone byte de datos en el acumulador
    	mov C, ACC.7	;
    	mov P1.7, C	;
    	mov C, ACC.6	;
    	mov P1.6, C	;
    	mov C, ACC.5	;
    	mov P1.5, C	;
    	mov C, ACC.4	;
    	mov P1.4, C	;hasta aquí se envia el nibble mas significativo

	setb LCD_E	;
	clr  LCD_E	;
	mov C, ACC.3	;
	mov P1.7, C	;
	mov C, ACC.2	;
	mov P1.6, C	;
	mov C, ACC.1	;
	mov P1.5, C	;
	mov C, ACC.0	;
	mov P1.4, C	;se envia el nibble menos significativo

	lcall pulseEwait4   ; pulso en el pin Enable...
                            ; y espera por el Flag Busy que aclare
	pop ACC
	ret
; ====================================================
; subrutina wrLCDcom4
; escribe una palabra comando al LCD
; el comando debe ser localizado en r0
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
	mov P1.4, C	;se envia el nibble menos significativo
;---------------------------------------
	lcall pulseEwait4   ; pulso en le pin Enable...
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
; toma la cadena inmediatamente que sigue a call y
; lo muestra sobre el LCD. La cadena es leida con la
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
; en 0. El acumulador da el número de línea.
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
 ; ==========================================================
; subrutina dspShLf4
; Esta rutina traslada los contenidos del LCD a la izquierda. El
; numero de caracteres a ser trasladados es localizado en el
; acumulador.
; entrada  : acumulador indica el numero de caracteres a trasladar
; salida   : nada
; ==========================================================
;
dspShLf4:
         jz    ret_sdl
         mov   r0, #shLfDsp ; palabra de control para trasladar a la
                            ; izquierda
         acall wrLCDcom4
         dec   a
         sjmp  dspShLf4
ret_sdl: ret

; ==========================================================
; subrutina dspShRt4
; Esta rutina traslada los contenidos del LCD a la derecha. El
; numero de caracteres a ser trasladados es localizado en el
; acumulador.
; entrada  : acumulador indica el numero de caracteres a trasladar
; salida   : nada
; ==========================================================
;
dspShRt4:
         jz    ret_sdr
         mov   r0, #shRtDsp ; palabra de control para trasladar a 
                            ; la derecha
         acall wrLCDcom4
         dec   a
         sjmp  dspShRt4
ret_sdr: ret
                                                                                                                         
    end
