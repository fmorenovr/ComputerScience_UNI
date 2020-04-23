vamos a crear la libreria libhello.a

primero hacemos los ejecutables

gcc -Wall -c hello_fn.c
gcc -Wall -c bye_fn.c

son compilados en los archivos hello_fn.o y bye_fn.o

Ahora son combinados en una libreria statica usando el siguiente comando

ar cr libhello.a hello_fn.o bye_fn.o

La opcion cr -- "create and replace"
si la libreria no eixste, la crea.
si existe, cualquier archivo original con los mismos nombres son 
reemplazados por los nuevos

ar t libhello.a

muestra la lista de los ejecutables dentro de la libreria

y ejecutamos :

gcc -Wall -L. testhello_main.c -lhello

o

gcc -Wall testhello_main.c libhello.a
