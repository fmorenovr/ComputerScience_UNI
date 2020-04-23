#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

char mensaje_str[100] ="Hola Mundo";

void * mensaje()
{
    while(1) {
        printf("%s\n", mensaje_str);
        sleep(2);
    }
}

void * nuevo_mensaje()
{
    while(1) {
      gets(mensaje_str);
    }
}

int main() 
{
   pthread_t tid1;
   pthread_t tid2;

   pthread_create(&tid1, NULL, mensaje, NULL);
   pthread_create(&tid2, NULL, nuevo_mensaje, NULL);

   pthread_join(tid1, NULL);
   pthread_join(tid2, NULL);

    return 0;
}
