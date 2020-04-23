//
// Imprimir A luego A luego B
//
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>

pthread_mutex_t mutex;
pthread_cond_t condA;
pthread_cond_t condB;
sem_t sem1;
sem_t sem2;
int contadorA;
int contadorB;

void * imprimirA()
{
  while(1)
  {
    pthread_mutex_lock(&mutex);
    if(contadorA == 2)
        pthread_cond_wait(&condA, &mutex);
    printf("A\n");
    contadorA++;
    if(contadorA == 2)
    {
        contadorB = 0;
        pthread_cond_signal(&condB);
    }
    pthread_mutex_unlock(&mutex);
  }
}
void * imprimirB()
{
  while(1)
  {
    pthread_mutex_lock(&mutex);
    if(contadorB == 1)
        pthread_cond_wait(&condB, &mutex);
    printf("B\n");
    contadorB++;
    contadorA = 0;
    pthread_cond_signal(&condA);
    pthread_mutex_unlock(&mutex);
  }
}

int main()
{
    pthread_t thread_impA;
    pthread_t thread_impB;
    pthread_t thread_impC;

    pthread_mutex_init(&mutex, NULL);
    sem_init(&sem1, 0, 1);
    sem_init(&sem2, 0, 2);
    contadorA = 0;
    contadorB = 0;

    pthread_create(&thread_impA, NULL, imprimirA, NULL );
    pthread_create(&thread_impC, NULL, imprimirA, NULL );
    pthread_create(&thread_impB, NULL, imprimirB, NULL );

    pthread_join(thread_impA, NULL);

    return 0;
}
