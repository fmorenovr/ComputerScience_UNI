#include <stdio.h>
#include <stdlib.h>
#include <stdlib.h>

int saldo = 0;

void * incrementar() {
    while(1){
        printf("+++ %d\n", ++saldo);
    }
}

void * decrementar() {
    while(1){
        printf("--- %d\n", --saldo);
    }
}

void main()
{
    pthread_t thread_1;
    pthread_t thread_2;

    pthread_create(&thread_1, NULL, incrementar, NULL);
    pthread_create(&thread_2, NULL, decrementar, NULL);

    pthread_join(thread_1, NULL);
}
