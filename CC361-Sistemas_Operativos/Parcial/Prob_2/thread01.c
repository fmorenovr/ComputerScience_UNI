#include <stdio.h>
#include <stdlib.h>
#include <stdlib.h>

int flag_detener = 0;

void * pares() {
    int i;
    while(1){
        while(!flag_detener){
            printf("pares: %d\n", 2*i);
            i++;
        }
    }
}

void * impares() {
    int i;
    while(1){
        printf("pares: %d\n", 2*i+1);
        i++;
    }
}

void * detener()
{ 
   char input[100];
   while(1) {
       gets(input);
       if(input[0] == 'd') {
           flag_detener = 1;
       }
       else if (input[0] == 'c') {
           flag_detener = 0;
       } 
   }
}

void main()
{
    pthread_t thread_1;
    pthread_t thread_2;

    pthread_create(&thread_1, NULL, pares, NULL);
    pthread_create(&thread_2, NULL, detener, NULL);

    pthread_join(thread_1, NULL);
}
