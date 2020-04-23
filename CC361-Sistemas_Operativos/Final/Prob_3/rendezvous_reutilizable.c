#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>

int contador = 0;
sem_t mutex;
sem_t torniquete1;
sem_t torniquete2;

void * imprimirA() {
	while(1){
		sleep(3);
		printf("--- A1\n");
		// Inicio Patron Barrera
	        sem_wait(&mutex);
		contador++;
   		if(contador == 3) {
			sem_wait(&torniquete2);
			sem_post(&torniquete1); 
			printf("abrimos la barrera\n");
		}
	        sem_post(&mutex);

	        sem_wait(&torniquete1);
	        sem_post(&torniquete1);
		// Fin Patron Barrera
		printf("--- A2\n");
		// Inicio Patron Barrera
	        sem_wait(&mutex);
		contador--;
   		if(contador == 0) {
			sem_wait(&torniquete1);
			sem_post(&torniquete2); 
		}
	        sem_post(&mutex);

		sem_wait(&torniquete2);
		sem_post(&torniquete2); 
		// Fin Patron Barrera
	}
}

void * imprimirB() {
	while(1) {
		sleep(2);
		printf("--- B1\n");
		// Inicio Patron Barrera
	        sem_wait(&mutex);
		contador++;
   		if(contador == 3) {
			sem_wait(&torniquete2);
			sem_post(&torniquete1); 
			printf("abrimos la barrera\n");
		}
	        sem_post(&mutex);

	        sem_wait(&torniquete1);
	        sem_post(&torniquete1);
		// Fin Patron Barrera
		printf("--- B2\n");
		// Inicio Patron Barrera
	        sem_wait(&mutex);
		contador--;
   		if(contador == 0) {
			sem_wait(&torniquete1);
			sem_post(&torniquete2); 
		}
	        sem_post(&mutex);

		sem_wait(&torniquete2);
		sem_post(&torniquete2); 
		// Fin Patron Barrera
	}
}

void * imprimirC() {
	while(1) {
		sleep(3);
		printf("--- C1\n");
		// Inicio Patron Barrera
	        sem_wait(&mutex);
		contador++;
   		if(contador == 3) {
			sem_wait(&torniquete2);
			sem_post(&torniquete1); 
			printf("abrimos la barrera\n");
		}
	        sem_post(&mutex);

	        sem_wait(&torniquete1);
	        sem_post(&torniquete1);
		// Fin Patron Barrera
		printf("--- C2\n");
		// Inicio Patron Barrera
	        sem_wait(&mutex);
		contador--;
   		if(contador == 0) {
			sem_wait(&torniquete1);
			sem_post(&torniquete2); 
		}
	        sem_post(&mutex);

		sem_wait(&torniquete2);
		sem_post(&torniquete2); 
		// Fin Patron Barrera
	}
}

void main()
{
    pthread_t thread_a;
    pthread_t thread_b;
    pthread_t thread_c;

    sem_init(&mutex, 0, 1);
    sem_init(&torniquete1, 0, 0);
    sem_init(&torniquete2, 0, 1);

    pthread_create(&thread_a, NULL, imprimirA, NULL);
    pthread_create(&thread_b, NULL, imprimirB, NULL);
    pthread_create(&thread_c, NULL, imprimirC, NULL);

    pthread_join(thread_a, NULL);
    pthread_join(thread_b, NULL);
}
