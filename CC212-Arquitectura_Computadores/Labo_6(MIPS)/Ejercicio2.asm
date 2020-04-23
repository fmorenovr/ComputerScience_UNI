	.data
str1:
	.ascii "Hola a todos\n"
	.asciiz "Bienvenidos a MIPS\n"
numero: .float 34.567901
	.text
main:

	li $v0,4
	la $a0,str1
	syscall

	li $v0,1
	li $a0,25
	syscall 		#imprime el valor 25
	
	li $v0,11
	li $a0,10
	syscall			#imprime un line feed

	li $v0, 2 		# llamada al sistema para imprimir un número real
	lwc1 $f12, numero 
	syscall 		# imprime el número real

				# llamada al sistema para terminar y salir
	li $v0, 10		# cargo servicio “10” en el registro $v0
	syscall			# realiza la acción