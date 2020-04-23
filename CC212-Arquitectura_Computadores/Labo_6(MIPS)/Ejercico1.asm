	.data
str1:
	.ascii "Hola a todos\n"
	.asciiz "Bienvenidos a MIPS"
	.text
main:
				# llamada al sistema para imprimir cadena
	li $v0, 4		# cargo servicio “4” en el registro $v0 
	la $a0, str1		# dirección de la cadena a imprimir
	syscall			# imprime la cadena

				# llamada al sistema para terminar y salir
	li $v0, 10		# cargo servicio “10” en el registro $v0
	syscall			# realiza la acción