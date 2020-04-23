	.data
cantidad:
	.asciiz "La cantidad de primos es: "
resultado:
	.asciiz "Los Primos son: "
coma:
	.asciiz ","
salto_linea:
	.asciiz "\n"
numero:
	.half 2400
	
	.text 
	
main:	
	li $v0,4
	la $a0,resultado
	syscall
	
	li $t0,0		#$t0 = cantidad de primos
	li $t2,2		#$t2 = numero a comprobar (n)
	lh $t3,numero		#$t3 = N
while:
	bge  $t2,$t3,sale
	li $s1,1		#$s1 = bandera
	li $t1,2		#$t1 = divisor (i)
primo:
	div $t2,$t1
	mflo $t5
	add $t5,$t5,1
	bge $t1,$t5,siguiente
	div $t2,$t1
	mfhi $s2		#s2 = residuo de dividir n/i
	beqz $s2,no_es_primo
	add $t1,$t1,1		#i++
	b primo
no_es_primo:
	li $s1,0
siguiente:
	beqz $s1,imprimir_primo
	li $v0,1
	move $a0,$t2
	syscall
	li $v0,4
	la $a0,coma
	syscall
	add $t0,$t0,1
	li $t5,20
	div $t0,$t5
	mfhi $s2
	bge $s2,1,imprimir_primo
	li $v0,4
	la $a0,salto_linea
	syscall
imprimir_primo:
	add $t2,$t2,1
	b while
sale:
	li $v0,4
	la $a0,salto_linea
	syscall

	li $v0,4
	la $a0,cantidad
	syscall
	
	li $v0,1
	move $a0,$t0
	syscall
	
	li $v0,10
	syscall
