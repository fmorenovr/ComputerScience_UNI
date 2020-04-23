#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

int indice;
int buffer[10];

pthread_mutex_t mutex;
pthread_cond_t var_cond_buffer_lleno;
pthread_cond_t var_cond_buffer_vacio;

void imprimirbuffer();

void * productor()
{
  while(1)
  {
    int valor = random()%100;
    pthread_mutex_lock(&mutex);

    if (indice == 9) pthread_cond_wait(&var_cond_buffer_lleno, &mutex);

    if(indice < 9)
    {
      indice = indice + 1;
      buffer[indice] = valor;
      printf("IN  ");
      imprimirbuffer();
      printf(" : %d\n", valor);
    }
    else
    {
      printf("desperdicio\n");
    }

    if (indice == 0) pthread_cond_signal(&var_cond_buffer_vacio);

    pthread_mutex_unlock(&mutex);
  }
}

void * consumidor()
{
  while(1)
  {
    pthread_mutex_lock(&mutex);

    if(indice == -1) pthread_cond_wait(&var_cond_buffer_vacio, &mutex);

    if(indice>=0)
    {
      int valor = buffer[indice];
      indice = indice-1;
      printf("OUT ");
      imprimirbuffer();
      printf(" : %d\n", valor);
    }
    else 
    {
      printf("desperdicion de horas de trabajador\n");
    }

    if (indice == 8) pthread_cond_signal(&var_cond_buffer_lleno);

    pthread_mutex_unlock(&mutex);
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
  pthread_mutex_init(&mutex, NULL);
  pthread_cond_init(&var_cond_buffer_lleno, NULL);
  pthread_cond_init(&var_cond_buffer_vacio, NULL);

  pthread_t tid_productor;
  pthread_t tid_consumidor;

  pthread_create(&tid_productor, NULL, productor, NULL);
  pthread_create(&tid_consumidor, NULL, consumidor, NULL);

  pthread_join(tid_productor, NULL);
  pthread_join(tid_consumidor, NULL);

  return 0;
}
