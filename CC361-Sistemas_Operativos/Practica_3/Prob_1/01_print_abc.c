#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>

sem_t semaforo_a;
sem_t semaforo_b;
sem_t semaforo_c;

void * imprimir_a()
{
  while(1)
  {
    sem_wait(&semaforo_a);
    printf("a");
    fflush(stdout);
    sem_post(&semaforo_b);
   }
}

void * imprimir_b()
{
  int count = 0;

  while(1)
  {
  if (count==0) sem_wait(&semaforo_b);
    printf("b");
    fflush(stdout);
    count++;
    if (count == 2) {
        count = 0;
        sem_post(&semaforo_c);
    }
  }
}

void * imprimir_c()
{
  int count = 0;

  while(1)
  {
    if (count==0) sem_wait(&semaforo_c);
    printf("c");
    fflush(stdout);
    count++;
    if (count == 3) {
        count = 0;
        sem_post(&semaforo_a);
    }
  }
}

int main()
{

  pthread_t tid_print_a;
  pthread_t tid_print_b;
  pthread_t tid_print_c;
  sem_init(&semaforo_a, 0, 1);
  sem_init(&semaforo_b, 0, 0);
  sem_init(&semaforo_c, 0, 0);


  pthread_create(&tid_print_a, NULL, imprimir_a, NULL);
  pthread_create(&tid_print_a, NULL, imprimir_a, NULL);
  pthread_create(&tid_print_b, NULL, imprimir_b, NULL);
  pthread_create(&tid_print_b, NULL, imprimir_b, NULL);
  pthread_create(&tid_print_b, NULL, imprimir_b, NULL);
  pthread_create(&tid_print_c, NULL, imprimir_c, NULL);
  pthread_create(&tid_print_c, NULL, imprimir_c, NULL);
  pthread_create(&tid_print_c, NULL, imprimir_c, NULL);

  pthread_join(tid_print_a, NULL);
  pthread_join(tid_print_b, NULL);
  pthread_join(tid_print_c, NULL);

  return 0;
}
