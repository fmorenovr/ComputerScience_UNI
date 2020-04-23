#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>

int indice;
int buffer[10];

sem_t mutex;
sem_t semaforo_espacios_vacios;
sem_t semaforo_espacios_ocupados;
//pthread_cond_t var_cond_buffer_lleno;
//pthread_cond_t var_cond_buffer_vacio;

void imprimirbuffer();

void * productor()
{
  while(1)
  {
    int valor = random()%100;

    sem_wait(&semaforo_espacios_vacios);

    sem_wait(&mutex);

    indice = indice + 1;
    buffer[indice] = valor;
    printf("IN  ");
    imprimirbuffer();
    printf(" : %d\n", valor);

    sem_post(&mutex);

    sem_post(&semaforo_espacios_ocupados);
  }
}

void * consumidor()
{
  while(1)
  {

    sem_wait(&semaforo_espacios_ocupados);

    sem_wait(&mutex);

    int valor = buffer[indice];
    indice = indice-1;
    printf("OUT ");
    imprimirbuffer();
    printf(" : %d\n", valor);

    sem_post(&mutex);

    sem_post(&semaforo_espacios_vacios);

  }
}

void imprimirbuffer()
{
  printf("[");
  int i;
  for(i=0; i<10; i++) {
    if (i <= indice)
      printf("*");
    else
      printf("0");
  }
  printf("]");
}

int main()
{
  indice = -1;
  sem_init(&mutex, 0, 1);
  sem_init(&semaforo_espacios_vacios, 0, 10);
  sem_init(&semaforo_espacios_ocupados, 0, 0);
  //pthread_cond_init(&var_cond_buffer_lleno, NULL);
  //pthread_cond_init(&var_cond_buffer_vacio, NULL);

  pthread_t tid_productor;
  pthread_t tid_consumidor;

  pthread_create(&tid_productor, NULL, productor, NULL);
  pthread_create(&tid_consumidor, NULL, consumidor, NULL);

  pthread_join(tid_productor, NULL);
  pthread_join(tid_consumidor, NULL);

  return 0;
}
