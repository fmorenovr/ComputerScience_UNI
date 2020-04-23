	.data
entrada1:
	.asciiz "Ingrese el numero: "
salida:
	.asciiz "El número ingresado "
salida1:
	.asciiz " es igual a "
salida2:
	.asciiz " es menor a "
salida3:
	.asciiz " es mayor a "
constante:
	.double 22700.123
	
	.text
main:
	la $a0,entrada1
	
	li $v0,53
	syscall
	
	jal calculo
	li $v0,10
	syscall
	
calculo:
	
	la $a0,constante
	l.d $f12,0($a0)
	
	mov.d $f10,$f12
	mov.d $f12,$f0
	
	li $v0,4
	la $a0,salida
	syscall
	li $v0,3
	syscall
	mov.d $f12,$f10
	
	c.eq.d $f0,$f12
	bc1t igual
	
	c.lt.d $f0,$f12
	bc1t menor
	
mayor:	
	li $v0,4
	la $a0,salida3
	syscall
	li $v0,3
	
	b salir
menor:
	li $v0,4
	la $a0,salida2
	syscall
	li $v0,3
	
	b salir
igual:
	li $v0,4
	la $a0,salida1
	syscall
	li $v0,3
	
salir:	
	syscall
	jr $ra		##retorno
