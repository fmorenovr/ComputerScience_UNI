;====================================
;Programa que parpadea un led
;con ingreso de velocidad de parpadeo
;====================================
print     equ  136h
getbyt    equ  11eh
chkbrk    equ  10fh

          org 8000h
          lcall     print
          db       0dh,0ah,"Ejemplo 1----LED PARPADEANTE"
          db       0dh,0ah,"============================",0dh,0ah
          db       0dh,0ah,"Ingrese la velocidad de parpadeo entre 0-FFh ==>",0
          lcall     getbyt
          mov       B,A
          lcall     print          
          db       0dh,0ah,"Presione Ctl-C para salir....",0
laso:
          setb      P1.0
          lcall     retardo
          lcall     retardo
          clr       P1.0
          lcall     retardo
          lcall     retardo
          lcall     chkbrk
          sjmp      laso
retardo:    
          mov       R3,#0h
laso1:          
          mov       R1,b    
          djnz      R1,$
          djnz      R3,laso1          
          ret
          end