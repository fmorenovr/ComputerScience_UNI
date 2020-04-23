#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>

int readers;
sem_t mutex;
sem_t roomEmpty;

void leer()
{
  printf("leyendo %d\n", readers);
}
void escribir()
{
  printf("escribiendo\n");
}

void * lector()
{
    while(1){
        sem_wait(&mutex);
        readers++;
        if(readers==1)
          sem_wait(&roomEmpty);
        sem_post(&mutex);

        // Zona crítica del lector
        leer();
        // Fin zona crítica

        sem_wait(&mutex);
        readers--;
        if(readers==0)
          sem_post(&roomEmpty);
        sem_post(&mutex);
        sleep(1);
    }
}

void * escritor()
{
    while(1){
        sem_wait(&roomEmpty);
        escribir();
        sem_post(&roomEmpty);
        sleep(1);
    }
}

int main()
{
    pthread_t thread_lector1;
    pthread_t thread_lector2;
    pthread_t thread_lector3;
    pthread_t thread_escritor1;
    pthread_t thread_escritor2;

    readers = 0;
    sem_init(&mutex,0,1);
    sem_init(&roomEmpty,0,1);

    pthread_create(&thread_lector1, NULL, lector, NULL );
    pthread_create(&thread_lector2, NULL, lector, NULL );
    pthread_create(&thread_lector3, NULL, lector, NULL );
    pthread_create(&thread_escritor1, NULL, escritor, NULL );
    pthread_create(&thread_escritor2, NULL, escritor, NULL );

    pthread_join(thread_lector1, NULL);

    return 0;
}
