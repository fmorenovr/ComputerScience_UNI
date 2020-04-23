;programa a parpadea un led conectado al pin p1.0
;cuando se presiona el boton p3.2 empieza el parpadeo
;y si preisono el boton p3.3 detengo el parpadeo
	sdelay equ 142h	;retardo de 1 seg
	delay equ 118h	;retardo en milisegundos, el valor de los miliseg se guarda en A
	org 8000h
	mov P1,#0	;se apaga todo

repite:
	jnb p3.2,empiezaParpadeo	;jnb cheqea si esta presionado
	sjmp repite
repite1:
	jnb p3.3,detieneParpadeo
	sjmp empiezaParpadeo
detieneParpadeo:
	sjmp repite
empiezaParpadeo:
	setb p1.0
	mov a,#70
	lcall delay
	clr p1.0
	mov a,#70
	lcall delay
	sjmp repite1
	end