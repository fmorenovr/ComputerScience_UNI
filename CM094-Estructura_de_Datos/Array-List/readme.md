gcc -c AL.c

ar cr libalist.a AL.o

gcc -L. Almain.c -lalist

o tambien

gcc Almain.c AL.c
