;Encontrar el resultado (X * Y). 
;Donde X=20 e Y=10 son almacenados en los registros R6 y R7. 
;Hacer un programa que encuentre el valor del producto de ambos números. 
;Guardando el resultado en la posición de memoria 30h.

org 8000h
clr c
mov 30h,#20h
mov 31h,#10h
mov A,30h
mov B,31h
mul AB
mov 32h,B
mov 33h,A
ljmp 2F0h	;retorna al monitor del firmware
end