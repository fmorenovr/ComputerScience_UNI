;Realizar un contador creciente (de 0 a 9) 
;que se muestre en el display de 7 segmentos. Y que se repita en forma indefinida.
sdelay equ 142h
display equ 11Bh

	org 8000h
repite:
	mov R2,#10	; de 0 a 9 son 10 veces
	mov R3,#0
lazo:
	mov A,R3
	lcall display
	cpl A
	mov P1,A
	lcall sdelay
	inc R3
	djnz R2,lazo
	sjmp repite
		
	end