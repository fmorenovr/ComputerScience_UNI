#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

void * proc1()
{
    while(1) {
        printf("Proc 1\n");
        sleep(1);
    }
}

void * proc2()
{
    while(1) {
        printf("Proc 2\n");
        sleep(1);
    }
}

int main() 
{
   pthread_t tid1;
   pthread_t tid2;

   pthread_create(&tid1, NULL, proc1, NULL);
   pthread_create(&tid2, NULL, proc2, NULL);

   pthread_join(tid1, NULL);
   pthread_join(tid2, NULL);

    return 0;
}
