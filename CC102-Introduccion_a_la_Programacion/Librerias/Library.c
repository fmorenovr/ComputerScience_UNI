CREAR UNA LIBRERIA C

Crea un archivo .h
  por ejemplo mylib.h
  que contenga archivo const o funciones extern

luego creamos un archivo mylib.c
  que contenga las funciones definidas en .h
  
luego creamos un Library Object File un ejecutable

gcc -o mylib.o -c mylib.c

Ahora creamos un SHARED FILE

gcc -shared -o libmylib.so mylib.o otromas.o -lm

Ahora compilamos

step 1: Add an include line (#include "mylib.h") in all program source files that use library definitions (e.g., test.c).

step 2: Link the program's .c file with the library object file 
        gcc  test.c mylib.o

        OR to link in libmylib.so (or libmylib.a):

        gcc  test.c -lmylib

        OR to link with a library not in the standard path:

        gcc  test.c -L/home/newhall/lib -lmylib

        The resulting a.out out will contain machine code for all the functions 
        defined in test.c plus any mylib library functions that are called by 
        the test.c code. 
        
ahora le damos nuestra direccion de librreria

export LD_LIBRARY_PATH=/home/newhall/lib:$LD_LIBRARY_PATH
