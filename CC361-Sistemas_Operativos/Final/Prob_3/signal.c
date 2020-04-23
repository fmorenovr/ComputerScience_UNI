#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>

sem_t sem;

void * imprimirA() {
	printf("--- A\n");
        sem_post(&sem);
}

void * imprimirB() {
        sem_wait(&sem);
	printf("--- B\n");
}

void main()
{
    pthread_t thread_a;
    pthread_t thread_b;

    sem_init(&sem, 0, 0);

    pthread_create(&thread_b, NULL, imprimirA, NULL);
    pthread_create(&thread_a, NULL, imprimirB, NULL);

    pthread_join(thread_a, NULL);
    pthread_join(thread_b, NULL);
}
