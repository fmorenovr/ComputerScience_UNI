	.data
mensaje1:
	.asciiz "Ingrese el temperatura en Farenheit: "
salida1:
	.asciiz "El temperatura en grados Celsius es"
constante1:
	.double 32
constante2:
	.double 0.555555555556
	.text
main:
	
	
	li $v0,4
	la $a0,mensaje1
	syscall
	
	li $v0,7
	syscall
	jal calculo
	
	li $v0,10
	syscall
	
calculo:
	
	la $a0,constante1
	l.d $f12,0($a0)
	la $a0,constante2
	l.d $f10,0($a0)
	
	sub.d $f12,$f0,$f12
	mul.d $f12,$f12,$f10
	
	li $v0,4
	la $a0,salida1
	syscall
	
	li $v0,3
	syscall
	jr $ra