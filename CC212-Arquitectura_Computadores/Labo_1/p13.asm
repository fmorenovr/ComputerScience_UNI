;programa q enciende los 4 bits
;menos significativos del puerto p1

	org 8000h
	mov P1,#0Fh
	ljmp 2F0H
	end