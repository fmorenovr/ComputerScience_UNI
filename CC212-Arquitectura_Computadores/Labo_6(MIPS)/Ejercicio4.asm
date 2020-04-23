	.data
ingreso:
	.asciiz "Ingrese número: "
resultado:
	.asciiz "El menor es: "
	
	.text
main:

	li $v0,4		
	la $a0, ingreso
	syscall
	li $v0,5		# carga el modo lectura de syscall en $v0.
	syscall
	move $t0,$v0		#lee el número y lo guarda en $t0
	
	li $v0,4
	la $a0, ingreso
	syscall
	li $v0,5
	syscall
	move $t1,$v0		#lee el número y lo guarda en $t1
	
	## pone el mas grande de $t0 y $t1 en $t2.
	bgt $t0, $t1, t0_bigger		# si $t0 > $t1, branch a t0_bigger,
	move $t2, $t0		# de otro modo, copia $t1 a $t2.
	b endif 			# y luego salta a endif
t0_bigger:
	move $t2, $t1 			# copia $t0 a $t2
endif:
	## Imprime $t2.
	
	li $v0,4
	la $a0,resultado
	syscall
	move $a0, $t2			# muevo el número a imprimir en $a0.
	li $v0, 1			# carga el modo de impresión de un entero en $v0.
	syscall 			# hace el syscall.
	
	li $v0,10
	syscall