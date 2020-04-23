;Selección de frecuencias
;de señales de 500hz, 1khz y 4khz
;en los pines P1.0 y P1.1
;utilizando el timer 0
;frecuencia del reloj: 11.0592Mhz

ascbin    equ  100h
binasc    equ  109h
break     equ  010ch  ; a, (lee acumulador)
inkey     equ  012ah  ; a
prthex    equ  13fh
prsphx    equ  139h
crlf      equ  115h 
endloop   equ  2f0h
print     equ  136h
getbyt    equ  11eh
getchr    equ  121h
sndchr    equ  148h            
chkbrk    equ  10fh
display   equ  11bh
 
          org       8000h    ;El programa empieza en esta direcci¢n de
                             ;de memoria
ejemplo:  
          lcall     print   ;PRINT es una subrutina grabado en la EPROM
                            ;se usa para imprimir mensajes en la computadora.
          db        0dh,0ah," M E N U "
          db        0dh,0ah,"=========",0dh,0ah
          db        0dh,0ah," HECHO POR: C. Martin Cruz Salazar",0dh,0ah
          db        0dh,0ah," 01) FRECUENCIA: 500 HZ"
          db        0dh,0ah," 02) FRECUENCIA: 1 KHZ"          
          db        0dh,0ah," 03) FRECUENCIA: 4 KHZ",0dh,0ah
          db        0dh,0ah," Seleccione numero hexadecimal: ",0
          lcall     getbyt
          cjne      a,#1h,salir                  
          sjmp      frec500hz
salir:
          sjmp      otrafrecuencia

frec500hz:
	lcall     print
          db       0dh,0ah,"FRECUENCIA SELECCIONADA: 500Hz"
          db       0dh,0ah,"==============================",0dh,0ah,0h
	mov TMOD,#02h		;configura el timer 0 en modo 2
				; como un temporizador de 8 bits con auto recarga
	mov TH0,#27		;valor de recarga
	setb TR0		;inicia el timer 0
	mov R7,#0		;contador
loop:
	lcall f500hz
	lcall inkey         ; 
 	lcall break         ; termina programa si CTL-C
	sjmp loop
	
otrafrecuencia:
	cjne      a,#2h,salir1                  
  	sjmp      frec1khz
salir1:
	sjmp otrafrecuencia1
frec1khz:
	lcall     print
          db       0dh,0ah,"FRECUENCIA SELECCIONADA: 1KHz"
          db       0dh,0ah,"==============================",0dh,0ah,0h
	mov TMOD,#02h		;configura el timer 0 en modo 2
				; como un temporizador de 8 bits con auto recarga
	mov TH0,#27		;valor de recarga
	setb TR0		;inicia el timer 0
	mov R7,#0		;contador
loop1:
	lcall f1khz
	sjmp loop1

otrafrecuencia1:
	cjne      a,#3h,salir2                  
  	sjmp      frec4khz
salir2:
	sjmp salir2
frec4khz:
	lcall     print
          db       0dh,0ah,"FRECUENCIA SELECCIONADA: 4KHz"
          db       0dh,0ah,"==============================",0dh,0ah,0h
	mov TMOD,#02h		;configura el timer 0 en modo 2
				; como un temporizador de 8 bits con auto recarga
	mov TH0,#141		;valor de recarga
	setb TR0		;inicia el timer 0
	mov R7,#0		;contador
loop2:
	lcall f4khz
	sjmp loop2


f500hz:
	jnb TF0,$		;esto se repite mientras TF0 es cero y no hay
				;desbordamiento
	inc R7			;incrementa el contador
	clr TF0			;este flag de desbordamiento se pone a 1 por hardware,
				;este flag debe ser puesto a 0 por software
	cjne R7,#4,f500hz	;R7 debe ser 4 para hacer el complemento de P1.0 y P1.1
	mov R7,#0
	cpl P1.0	
	cpl P1.1			;complementa el pin 2 en el Puerto 1	
	ret
f1khz:
	jnb TF0,$		;esto se repite mientras TF0 es cero y no hay
				;desbordamiento
	inc R7			;incrementa el contador
	clr TF0			;este flag de desbordamiento se pone a 1 por hardware,
				;este flag debe ser puesto a 0 por software
	cjne R7,#2,f1khz	;R7 debe ser 4 para hacer el complemento de P1.0 y P1.1
	mov R7,#0
	cpl P1.0	
	cpl P1.1			;complementa el pin 2 en el Puerto 1	
	ret
	
f4khz:
	jnb TF0,$		;esto se repite mientras TF0 es cero y no hay
				;desbordamiento
	cpl P1.0	
	cpl P1.1		;complementa el pin 2 en el Puerto 1
	clr TF0
	ret
	end

