; ----------------------------------------------------
; Interrupcion3.asm      
;
; Ejemplo de dos interrupciones externas

; Interrupciones Externas  0 y 1 son habilitados y
; se fijan para responder transiciones de 1-a-0. La
; tarea principal es parpadear un LED conectado al pin P1.0
; Note que no hay una llamada explicita
; a las rutinas de servicio de interrupción
; Inter0 e Inter1.  Las rutinas de servicio de interrup-
; ción son invocados sólo bajo señales externas.
; Puede salir del programa presionando las teclas ctl + C.
; Este programa necesita la tarjeta TMC51 y dos botones para 
; interrumpir por el pin P3.2 y el pin P3.3.
;--------------------------------------------
;Hecho por C.Martin Cruz Salazar
;--------------------------------------------
; subrutinas             registros usados
; ----------------------------------------------
 break     equ  010ch  ; a, (reads accumulator)
 crlf      equ  0115h  ; a
 inkey     equ  012ah  ; a
 print     equ  0136h  ; a, dptr
 prthex    equ  013fh  ; a, r2
 setintvec equ  0145h  ; a, dptr
; ====================================================
;       P R O G R A M A   P R I N C I P A L 
;
      org   8000h         ; correr usando el comando G
                          ; G8000
      setb P3.2
      setb P3.3
      setb  IT0           ; fija la interrupción externa 0
                          ; para ser sensible a transición de alta a baja 
      mov   a, #0         ; INT0 es la fuente de interrupci¢n 0           
      mov   dptr, #Inter0 ; 
      lcall setintvec     ;
      setb  EX0           ; habilita interrupción externa 0

      setb  IT1           ; fijar interrupción externa 1
                          ; para ser sensible a transición
      mov   a, #2         ; INT1 es la segunda fuente de interrupci¢n
      mov   dptr, #Inter1                         
      lcall setintvec     
      setb  EX1           ; habilita interrupción externa 1
      setb  EA            ; habilita interrupciones globalmente    
      mov   r6, #0        ; 
      mov   r7, #0        ; 
loop:
      djnz  r6, loop      ; 
      djnz  r7, loop
      cpl P1.0		  ; parpadeo del LED en el pin P1.0
      lcall inkey         ; termina programa si CTL-C
      lcall break         ; 
      sjmp loop           ; se repite por siempre...

; ====================================================
;  subrutina Inter0
; ----------------------------------------------------
Inter0:
    push acc
    lcall print
    db    0dh,0ah,"Interrumpiendo por el pin P3.2"
    db    0dh,0ah,"I N T E R R U P C I O N  E X T E R N A  0",0
    lcall crlf
    pop acc
    reti

; ====================================================
;  subrutina Inter1
; ----------------------------------------------------
Inter1:
    push acc
    lcall print
    db    0dh,0ah,"Interrumpiendo por el pin P3.3"
    db    0dh,0ah,"I N T E R R U P C I O N  E X T E R N A  1",0
    lcall crlf
    pop acc
    reti
    end
; ====================================================
; fin de programa
