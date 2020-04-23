//
// Imprimir A luego B
//
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>

pthread_mutex_t mutex;
sem_t semaforo;

void * imprimirA()
{
  printf("A\n");
  sem_post(&semaforo);
}
void * imprimirB()
{
  sem_wait(&semaforo);
  printf("B\n");
}

int main()
{
    pthread_t thread_impA;
    pthread_t thread_impB;

    pthread_mutex_init(&mutex, NULL);
    sem_init(&semaforo, 0, 0);

    pthread_create(&thread_impA, NULL, imprimirA, NULL );
    pthread_create(&thread_impB, NULL, imprimirB, NULL );

    pthread_join(thread_impA, NULL);

    return 0;
}
