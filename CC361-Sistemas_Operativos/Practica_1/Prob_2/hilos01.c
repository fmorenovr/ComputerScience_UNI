#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

void * mensaje()
{
    while(1) {
        printf("Hola Mundo\n");
        sleep(1);
    }
}

int main() 
{
   pthread_t tid;

   pthread_create(&tid, NULL, mensaje, NULL);

   pthread_join(tid, NULL);

    return 0;
}
