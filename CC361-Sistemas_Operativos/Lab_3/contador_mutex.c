#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

int contador;
// Declaramos Mutex
pthread_mutex_t mutex;

void agregar(char c);
void quitar();

void * productor()
{
  while(1)
  {
    char c = 'a' + rand()%24;
    agregar(c);
    usleep(1000);
  }
}
void * consumidor()
{
  while(1)
  {
    quitar();
    usleep(1000);
  }
}

void * imprimir()
{
    while(1){
        int i;
        printf("%d",contador);
        printf("\n");
        usleep(1000);
    }
}

int main()
{
    //pthread_t thread_imprimir;
    pthread_t thread_consumidor;
    pthread_t thread_productor;

    contador = 0;
    // Inicializamos mutex
    pthread_mutex_init(&mutex, NULL);

    //pthread_create(&thread_imprimir, NULL, imprimir, NULL );
    pthread_create(&thread_consumidor, NULL, consumidor, NULL );
    pthread_create(&thread_productor, NULL, productor, NULL );

    pthread_join(thread_consumidor, NULL);

    return 0;
}

void agregar(char c)
{
  if(contador<100){
    pthread_mutex_lock(&mutex);
    contador++;
    printf("%d\n",contador);
    pthread_mutex_unlock(&mutex);
  }
}

void quitar()
{
  if(contador>0)
  {
    pthread_mutex_lock(&mutex);
    contador--;
    printf("%d\n",contador);
    pthread_mutex_unlock(&mutex);
  }
}
