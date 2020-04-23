#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>

int saldo = 0;
int contadorA = 0;
int contadorB = 0;
int contadorC = 0;
sem_t semA;
sem_t semContadorA;
sem_t semB;
sem_t semContadorB;
sem_t semC;
sem_t semContadorC;

void * imprimirA() {
    while(1){
        sem_wait(&semA);
        printf("A\n");
        sem_post(&semB);
    }
}

void * imprimirB() {
    while(1){
//
//        sem_wait(&semContadorB);
//	if(contadorB==0) {
//            sem_wait(&semB);
//	}
//
//        printf("B\n");
//
//	contadorB++;
//	if(contadorB==2) {
//            sem_post(&semA);
//            contadorB=0;
//	}
//        sem_post(&semContadorB);

	sem_wait(&semB);
	printf("B\n");
        contadorB++;
        if(contadorB%2==0)
            sem_post(&semA);
        else
            sem_post(&semB);
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

    sem_init(&semA, 0, 1);
    sem_init(&semContadorA, 0, 1);
    sem_init(&semB, 0, 0);
    sem_init(&semContadorB, 0, 1);
    sem_init(&semC, 0, 0);
    sem_init(&semContadorC, 0, 1);

    pthread_create(&thread_1, NULL, imprimirA, NULL);
    pthread_create(&thread_1, NULL, imprimirA, NULL);
    pthread_create(&thread_1, NULL, imprimirA, NULL);
    pthread_create(&thread_2, NULL, imprimirB, NULL);
    pthread_create(&thread_2, NULL, imprimirB, NULL);
    pthread_create(&thread_2, NULL, imprimirB, NULL);
    pthread_create(&thread_3, NULL, imprimirC, NULL);
    pthread_create(&thread_3, NULL, imprimirC, NULL);
    pthread_create(&thread_3, NULL, imprimirC, NULL);

    pthread_join(thread_1, NULL);
}
