	.data
texto:
	.asciiz "La cantidad de vocales son: "
frase:
	.asciiz "long time ago in a galaxy away"
nueva_linea:
	.asciiz "\n"
	
	.text
main:

	la $a0,frase
	li $s0,0		#contador de vocales
	move $s1,$a0		#dirección de la cadena
bucle:
	lb $a0,($s1)		#consigue cada caracter de la cadena
	beqz $a0,Termina
	li $t0,0
	beq $a0,'a',Si_es_vocal
	beq $a0,'e',Si_es_vocal
	beq $a0,'i',Si_es_vocal
	beq $a0,'o',Si_es_vocal
	beq $a0,'u',Si_es_vocal
continua:
	add $s1,$s1,1
	b bucle
	
Si_es_vocal:
	add $s0,$s0,1
	b continua
	
Termina:
	li $v0,4
	la $a0,texto
	syscall
	
	li $v0,1
	move $a0,$s0
	syscall
	
	li $v0,10
	syscall