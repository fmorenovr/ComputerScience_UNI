#include <stdlib.h>
#include <stdio.h>

int main() {
    int pid = fork();
    if( fork() )
    {
        printf("Proceso padre %d\n", getpid());
    }
    else
    {
        printf("Proceso hijo %d\n", getpid());
    }
    char c;
    gets(&c);
    return 0;
}
