#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>

int bano[10];
int n_masc = 0;
int n_fem = 0;
int n_total = 0;

sem_t mutex;
sem_t mutex_genero;
sem_t sem_cap_max;

void * mas()
{
  while(1) {
    sem_wait(&sem_cap_max);

    sem_wait(&mutex);
    n_total++;
    printf("m%d", n_total);
    fflush(stdout);
    sem_post(&mutex);
    sleep(rand()%2);
    sem_wait(&mutex);
    n_total--;
    printf("(%d)", n_total);
    sem_post(&mutex);

    sem_post(&sem_cap_max);

    sleep(5);
  }
}

void * fem()
{
  while(1) {
    sem_wait(&sem_cap_max);

    sem_wait(&mutex);
    n_total++;
    printf("f%d", n_total);
    fflush(stdout);
    sem_post(&mutex);
    sleep(rand()%5);
    sem_wait(&mutex);
    n_total--;
    printf("(%d)", n_total);
    sem_post(&mutex);

    sem_post(&sem_cap_max);

    sleep(5);
  }
}

int main() 
{
  pthread_t pid;
  sem_init(&mutex, 0, 1);
  sem_init(&mutex_genero, 0, 1);
  sem_init(&sem_cap_max, 0, 3);

  pthread_create(&pid, NULL, mas, NULL);
  pthread_create(&pid, NULL, mas, NULL);
  pthread_create(&pid, NULL, mas, NULL);
  pthread_create(&pid, NULL, mas, NULL);
  pthread_create(&pid, NULL, mas, NULL);
  pthread_create(&pid, NULL, mas, NULL);
  pthread_create(&pid, NULL, fem, NULL);
  pthread_create(&pid, NULL, fem, NULL);
  pthread_create(&pid, NULL, fem, NULL);
  pthread_create(&pid, NULL, fem, NULL);

  pthread_join(pid, NULL);
  return 0;
}

