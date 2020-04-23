#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int main() {
    if( fork() == 0 )
    {
        char* arg[3];
        arg[0] = strdup("ls");
        arg[1] = strdup(".");
        arg[2] = NULL;
        execvp(arg[0],arg);
    }
    char c;
    gets(&c);
    return 0;
}
