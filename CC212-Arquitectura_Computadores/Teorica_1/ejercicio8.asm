;Encontrar el resultado (Y - 9). Donde X=5Ah es almacenado 
;en la posición de memoria 30h. Hacer un programa que encuentre 
;el valor de la resta de ambos números. Guardando el resultado 
;en la posición 31h.

org 8000h
clr C
mov 30h,#5Ah	;se almacena el valor 5Ah en la memoria 30h
mov A,30h
subb A,#9	;resta 9 al valor en la memoria 30h
mov 31h,A	;mueve el valor de A en la memoria 31h
sjmp $
end