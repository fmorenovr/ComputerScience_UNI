#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

char buffer[100];
int indice;

void agregar(char c);
void quitar();

void * productor()
{
  while(1)
  {
    char c = 'a' + rand()%24;
    agregar(c);
    sleep(1);
  }
}
void * consumidor()
{
  while(1)
  {
    quitar();
    sleep(1);
  }
}

void * imprimir()
{
    while(1){
        int i;
        printf("%d",indice);
        printf("\n");
        sleep(1);
    }
}

int main()
{
    //pthread_t thread_imprimir;
    pthread_t thread_consumidor;
    pthread_t thread_productor;

    indice = 0;

    //pthread_create(&thread_imprimir, NULL, imprimir, NULL );
    pthread_create(&thread_consumidor, NULL, consumidor, NULL );
    pthread_create(&thread_productor, NULL, productor, NULL );

    pthread_join(thread_consumidor, NULL);

    return 0;
}

void agregar(char c)
{
  if(indice<100){
    buffer[indice] = c;
    indice++;
    printf("%d\n",indice);
  }
}

void quitar()
{
  if(indice>0)
  {
    indice--;
    printf("%d\n",indice);
  }
}
