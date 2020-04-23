#include <stdio.h>
#include <stdlib.h>
#include <stdlib.h>

int saldo = 0;
pthread_mutex_t mutex;

void * incrementar() {
    while(1){
        pthread_mutex_lock(&mutex);

        printf("+++ %d\n", ++saldo);

        pthread_mutex_unlock(&mutex);
    }
}

void * decrementar() {
    while(1){
        pthread_mutex_lock(&mutex);

        printf("--- %d\n", --saldo);

        pthread_mutex_unlock(&mutex);
    }
}

void main()
{
    pthread_t thread_1;
    pthread_t thread_2;

    pthread_mutex_init(&mutex, NULL);

    pthread_create(&thread_1, NULL, incrementar, NULL);
    pthread_create(&thread_2, NULL, decrementar, NULL);

    pthread_join(thread_1, NULL);
}
