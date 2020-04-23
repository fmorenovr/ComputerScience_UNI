.data

mensaje_re:
	.asciiz " El resultado de la suma es: "
	.text
#lee desde el teclado un valor punto flotante
#Primer Numero
	li $v0,7
	syscall
#El valor se alamacena en $f0
mov.d $f2,$f0

#segundo numero
	li $v0,7
	syscall
	add.d $f12,$f2,$f0#$f12=$f2+$f0
	
	li $v0,4
	la $a0,mensaje_re
	syscall
	li $v0,3
	syscall
	
	li $v0,10
	syscall