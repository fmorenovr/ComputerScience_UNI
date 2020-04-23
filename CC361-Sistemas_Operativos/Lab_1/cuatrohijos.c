#include <stdlib.h>
#include <stdio.h>

int main() {
    if( fork() ){
        if( fork() ){
            if( fork() ){
                if( fork() ){
                }
            }
        }
    }
    char c;
    gets(&c);
    return 0;
}
