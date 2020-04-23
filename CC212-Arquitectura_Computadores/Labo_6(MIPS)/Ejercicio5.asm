	.data
ingreso:
	.asciiz "Ingrese número: "
resultado:
	.asciiz "El mayor es: "
lista:
	.byte  53,9,77,66,12,115,18,26,44,14,19,78,8,12,13,0
	
	.text
main:
	li $t3,1		#t3=menor
	la $t4,lista
	move $s0,$t4
	
algoritmo:
	lb $a0,($s0)
	beqz $a0,salir
	bgt $a0, $t3, t0_bigger		# si $t0 > $t1, branch a t0_bigger,
	b endif 			# y luego salta a endif
t0_bigger:
	move $t3, $a0 			# copia $t0 a $t2
endif:
	#sub $t1,$t1,1
	add $s0,$s0,1
	b algoritmo
salir:
	
	
	## Imprime $t2.
	
	li $v0,4
	la $a0,resultado
	syscall
	move $a0, $t3			# muevo el número a imprimir en $a0.
	li $v0, 1			# carga el modo de impresión de un entero en $v0.
	syscall 			# hace el syscall.
	
	li $v0,10
	syscall
