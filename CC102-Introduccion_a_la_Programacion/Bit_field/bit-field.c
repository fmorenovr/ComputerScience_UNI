#include <stdio.h>
#include <string.h>

struct Age
{
  unsigned int age : 3;
};

// el 2 puntitos nos dice que nuestro entero solo usara 3 bit
// es decir 8 = 1000 por eso no lo toma

typedef struct Age Age;

int main()
{
  Age Age;
   Age.age = 4;
   printf( "Sizeof( Age ) : %lu\n", sizeof(Age) );
   printf( "Age.age : %d\n", Age.age );

   Age.age = 7;
   printf( "Age.age : %d\n", Age.age );

//   Age.age = 8; devuelve overflow !!!
   printf( "Age.age : %d\n", Age.age );

   return 0;
}
