#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>

int contador = 0;
sem_t mutex;
sem_t barrera;

void * imprimirA() {
	sleep(3);
	printf("--- A1\n");
	// Inicio Patron Barrera
        sem_wait(&mutex);
	contador++;
        sem_post(&mutex);

	if (contador == 3) sem_post(&barrera);

	sem_wait(&barrera);
	sem_post(&barrera);
	// Fin Patron Barrera
	printf("--- A2\n");
}

void * imprimirB() {
	sleep(2);
	printf("--- B1\n");
	// Inicio Patron Barrera
	sem_wait(&mutex);
	contador++;
	sem_post(&mutex);

	if (contador == 3) sem_post(&barrera);

	sem_wait(&barrera);
	sem_post(&barrera);
	// Fin Patron Barrera
	printf("--- B2\n");
}

void * imprimirC() {
	sleep(3);
	printf("--- C1\n");
	// Inicio Patron Barrera
        sem_wait(&mutex);
	contador++;
        sem_post(&mutex);

	if (contador == 3) sem_post(&barrera);

	sem_wait(&barrera);
	sem_post(&barrera);
	// Fin Patron Barrera
	printf("--- C2\n");
}

void main()
{
    pthread_t thread_a;
    pthread_t thread_b;
    pthread_t thread_c;

    sem_init(&mutex, 0, 1);
    sem_init(&barrera, 0, 0);

    pthread_create(&thread_a, NULL, imprimirA, NULL);
    pthread_create(&thread_b, NULL, imprimirB, NULL);
    pthread_create(&thread_c, NULL, imprimirC, NULL);

    pthread_join(thread_a, NULL);
    pthread_join(thread_b, NULL);
}
