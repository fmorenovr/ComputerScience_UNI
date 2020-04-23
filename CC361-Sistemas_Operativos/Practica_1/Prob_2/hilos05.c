#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

int n = 0;

void * sumar()
{
    while(1) {
        n++;
        printf("%d\n", n);
        //sleep(1);
    }
}

void * restar()
{
    while(1) {
        n--;
        printf("%d\n", n);
        //sleep(2);
    }
}

int main() 
{
   pthread_t tid1;
   pthread_t tid2;

   pthread_create(&tid1, NULL, sumar, NULL);
   pthread_create(&tid2, NULL, restar, NULL);

   pthread_join(tid1, NULL);
   pthread_join(tid2, NULL);

    return 0;
}
