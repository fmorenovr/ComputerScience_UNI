#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>

int saldo = 0;
sem_t semA;
sem_t semB;
sem_t semC;

void * imprimirA() {
    while(1){
        sem_wait(&semA);
        printf("A\n");
        sem_post(&semB);
    }
}

void * imprimirB() {
    while(1){
        sem_wait(&semB);
        printf("B\n");
        sem_post(&semC);
    }
}

void * imprimirC() {
    while(1){
        sem_wait(&semC);
        printf("C\n");
        sem_post(&semA);
    }
}



void main()
{
    pthread_t thread_1;
    pthread_t thread_2;
    pthread_t thread_3;

    sem_init(&semA, 0, 0);
    sem_init(&semB, 0, 0);
    sem_init(&semC, 0, 0);

    pthread_create(&thread_1, NULL, imprimirA, NULL);
    pthread_create(&thread_2, NULL, imprimirB, NULL);
    pthread_create(&thread_3, NULL, imprimirC, NULL);

    pthread_join(thread_1, NULL);
}
