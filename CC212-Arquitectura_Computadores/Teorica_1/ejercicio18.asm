;Hacer parpadear un led conectado a P1.0 
;en caso se presiona el botón conectado a P3.2. 
;Si se presiona el botón conectado a P3.3 se detiene el parpadeo.

delay equ 118h
mov P1,#0

parpadeo:
	jnb P3.2,empiezaParpadeo
	sjmp parpadeo
repite:
	jnb P3.3,detieneParpadeo
	sjmp empiezaParpadeo
detieneParpadeo:
	sjmp parpadeo
empiezaParpadeo:
	setb P1.0
	mov A,#75
	lcall delay
	clr P1.0
	mov A,#70
	lcall delay
	sjmp repite
	
	end