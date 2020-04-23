#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>

int saldo = 0;
sem_t mutex;

void * incrementar() {
    while(1){
        sem_wait(&mutex);

        printf("+++ %d\n", ++saldo);

        sem_post(&mutex);
    }
}

void * decrementar() {
    while(1){
        sem_wait(&mutex);

        printf("--- %d\n", --saldo);

        sem_post(&mutex);
    }
}

void main()
{
    pthread_t thread_1;
    pthread_t thread_2;

    sem_init(&mutex, 0, 1);

    pthread_create(&thread_1, NULL, incrementar, NULL);
    pthread_create(&thread_2, NULL, decrementar, NULL);

    pthread_join(thread_1, NULL);
}
