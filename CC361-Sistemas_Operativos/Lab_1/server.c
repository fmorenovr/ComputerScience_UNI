#include <stdlib.h>
#include <stdio.h>

int main() {
    if( fork() )
    {
        exit(0);
    }
    else
    {
        while(1){
            sleep(10);
            printf("proceso hijo\n");
        }
    }
    char c;
    gets(&c);
    return 0;
}
