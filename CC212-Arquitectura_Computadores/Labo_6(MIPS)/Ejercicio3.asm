	.data
resultado:
	.asciiz "El Resultado de la suma es "
	
	.text
main:

	li $t0,116
	add $t1,$t0,44
	
	li $v0,4
	la $a0, resultado
	syscall
	
	move $a0,$t1
	li $v0,1
	syscall
	
	#li $v0,5
	#syscall
	#move $t1,$v0
	
	li $v0,10
	syscall