## Libreria C

Para ejecutar este programa hacer (usando el header maf):

    gcc mafMain.c maf.c

* Creamos el compilado sin linkear:

    gcc -c maf.c -o maf.o
    gcc mafMain.c maf.o

* Crear libreria estatica maf

    ar rcs libmaf.a maf.o
    gcc mafMain.c libmaf.a
    gcc -L. mafMain.c -lmaf
