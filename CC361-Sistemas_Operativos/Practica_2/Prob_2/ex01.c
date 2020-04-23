#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

int n = 0;
pthread_mutex_t mutex;

void * sumar()
{
    while(1) {
        pthread_mutex_lock(&mutex);
        n++;
        printf("%d\n", n);
        //sleep(1);
        pthread_mutex_unlock(&mutex);
    }
}

void * restar()
{
    while(1) {
        pthread_mutex_lock(&mutex);
        n--;
        printf("%d\n", n);
        //sleep(2);
        pthread_mutex_unlock(&mutex);
    }
}

int main() 
{
   pthread_t tid1;
   pthread_t tid2;

   pthread_mutex_init(&mutex, NULL);

   pthread_create(&tid1, NULL, sumar, NULL);
   pthread_create(&tid2, NULL, restar, NULL);

   pthread_join(tid1, NULL);
   pthread_join(tid2, NULL);

    return 0;
}
