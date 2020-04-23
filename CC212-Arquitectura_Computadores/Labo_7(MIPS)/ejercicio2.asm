	.data
entrada1:
	.asciiz "Ingrese el radio: "
salida1:
	.asciiz "El area es: "
pi:
	.double 3.14159265358979323846
	
	.text
main:
	li $v0,4
	la $a0,entrada1
	syscall
	
	li $v0,7
	syscall
	
	jal calculo
	li $v0,10
	syscall
	
calculo:
	
	la $a0,pi
	l.d $f12,0($a0)
	
	mul.d $f0,$f0,$f0
	mul.d $f12,$f12,$f0
	
	li $v0,4
	la $a0,salida1
	syscall
	
	li $v0,3
	syscall
	jr $ra		##retorno