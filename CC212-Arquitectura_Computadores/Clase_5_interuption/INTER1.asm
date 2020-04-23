; ----------------------------------------------------
; Inter1.asm      
;
; Ejemplo de interrupción simple
; Contador hexadecimal(0 a 0Fh)  que se puede interrumpir
; puede salir del programa con ctl+C.

; Este programa necesita la tarjeta TMC51 y un  
; botón para interrumpir por el pin P3.2. 
;--------------------------------------------
;Hecho por C. Martín Cruz Salazar
;----------------------------------------------
; subrutinas            registros usados
; ----------------------------------------------
break     equ  010ch  ; a, (lee acumulador)
crlf      equ  0115h  ; a
inkey     equ  012ah  ; a
print     equ  0136h  ; a, dptr
prthex    equ  013fh  ; a, r2
setintvec equ  0145h  ; a, dptr
prsphx    equ  139h

; ====================================================
;       P R O G R A M A  P R I N C I P A L
; ----------------------------------------------------

      org   8000h         ; 
      setb  IT0           ; fija la interrupción externa sensible
      			  ; en el flanco de bajada
      mov   a, #0         ; fuente de interrupci¢n externa 0
      mov   dptr, #ISR0   ; fijar  dptr con la dirección de inicio
      			  ; de la interrupción externa 0 para  llamar a
                          ; setintvec
      lcall setintvec     ; fija el ISR para INT0
      setb  EX0           ; habilita interrupción externa 0
                          ; en el registro IE
      setb  EA            ; flag de interrupci¢n maestra del registro IE
      setb  p3.2          ; fija el pin p3.2 como entrada
                          ; botón conectado
loop:
      mov   r3,#10h	  ;contador hexadecimal de 0 a F
      mov   r4, #0 ; 
loop1:
      mov   a, r4          
      lcall prthex	  ; envía por el puerto serie el valor hexadecimal de la cuenta
      lcall crlf
      lcall retar
      lcall retar
      inc   r4
      djnz  r3,loop1
      lcall inkey         ; 
      lcall break         ; termina programa si se presionan CTL-C
      sjmp loop           ; repite  por siempre...

;-------------------
;rutina de retardo
;-------------------
retar:    
          mov       r0,#0h
laso1:          
          mov       r1,#0h    
          djnz      r1,$
          djnz      r0,laso1          
          ret

; =================================================================
;  subrutina ISR0
;  rutina de servicio de interrupción para la interrupción externa 0
; ------------------------------------------------------------------
ISR0:
    push  acc
    lcall print
    db    0dh,0ah,"Hola me estan interrumpiendo voya sumar"
    db    0dh,0ah,"los numeros: ",0
    lcall crlf
    mov   a,#40h
    push  acc
    lcall prsphx
    mov   b,#20h
    mov   a,b
    lcall prsphx
    pop   acc
    add   a,b
    push  acc
    lcall print
    db 0dh,0ah,"La suma es: ",0
    pop   acc
    lcall prthex
    lcall crlf
    lcall retar
    lcall retar
    lcall retar
    pop acc
    reti
end
; ====================================================
; fin de  programa
