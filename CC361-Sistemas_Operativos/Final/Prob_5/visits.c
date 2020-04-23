#include <stdio.h>
#include <stdlib.h>

int main() {
    fork();
    fork();
    fork();
    fork(); 

    execv("./ic.out", NULL);

    return 0;
}
