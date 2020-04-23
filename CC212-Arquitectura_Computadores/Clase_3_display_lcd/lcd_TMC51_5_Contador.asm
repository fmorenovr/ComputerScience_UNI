;===========================================
;lcd_TMC51_5_Contador.asm
;Programa que visualiza un contador de 0 a 9 
;===========================================
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
sdelay	  equ 142h

	org 8000h
inicio:
	lcall resetLCD4    	; power on reset
	mov A,#1
    	lcall delay		; un retardo de 1 milisegundo
	lcall initLCD4		; inicializa el LCD (para que sea MODO 4 bits,
				; se usen 2 filas, etc.).
	mov A,#1
    	lcall delay		; retardo de 1 milisegundo
otravez:
	mov R0,#clrDsp		; limpia el display
	lcall wrLCDcom4		; envio de comando o orden para ejecutar
	mov A,#2		; indica que se va tener 2 milisegundos de retardo
	lcall delay		; retardo de 2 milisegundos
    	lcall segs0_a_9
    	sjmp otravez
;==========================================================
;Subrutina segs0_a_9 de display LCD para cuenta en segundos
;Visualizacion de Segundos desde 0 a 9.
;==========================================================
segs0_a_9:
    mov r0,#30h
    lcall wrLCDdata4
    mov r0,#shlfcur
    lcall wrlcdcom4
    mov r0,#offcur	;no se ve el cursor
    lcall wrlcdcom4
    lcall sdelay
    mov r0,#31h
    lcall wrLCDdata4
    mov r0,#shlfcur
    lcall wrlcdcom4
    mov r0,#offcur	;no se ve el cursor
    lcall wrlcdcom4
    lcall sdelay
    mov r0,#32h
    lcall wrLCDdata4
    mov r0,#shlfcur
    lcall wrlcdcom4
    mov r0,#offcur	;no se ve el cursor
    lcall wrlcdcom4
    lcall sdelay
    mov r0,#33h
    lcall wrLCDdata4
    mov r0,#shlfcur
    lcall wrlcdcom4
    mov r0,#offcur	;no se ve el cursor
    lcall wrlcdcom4
    lcall sdelay
    mov r0,#34h
    lcall wrLCDdata4
    mov r0,#shlfcur
    lcall wrlcdcom4
    mov r0,#offcur	;no se ve el cursor
    lcall wrlcdcom4
    lcall sdelay
    mov r0,#35h
    lcall wrLCDdata4
    mov r0,#shlfcur
    lcall wrlcdcom4
    mov r0,#offcur	;no se ve el cursor
    lcall wrlcdcom4
    lcall sdelay
    mov r0,#36h
    lcall wrLCDdata4
    mov r0,#shlfcur
    lcall wrlcdcom4
    mov r0,#offcur	;no se ve el cursor
    lcall wrlcdcom4
    lcall sdelay
    mov r0,#37h
    lcall wrLCDdata4
    mov r0,#shlfcur
    lcall wrlcdcom4
    mov r0,#offcur	;no se ve el cursor
    lcall wrlcdcom4
    lcall sdelay
    mov r0,#38h
    lcall wrLCDdata4
    mov r0,#shlfcur
    lcall wrlcdcom4
    mov r0,#offcur	;no se ve el cursor
    lcall wrlcdcom4
    lcall sdelay
    mov r0,#39h
    lcall wrLCDdata4
    ;mov r0,#shlfcur
    ;lcall wrlcdcom4
    mov r0,#offcur	;no se ve el cursor
    lcall wrlcdcom4
    lcall sdelay
    ret

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
