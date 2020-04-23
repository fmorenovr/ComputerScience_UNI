#include <stdio.h>
#include <limits.h>

int main(void) {
  char a = 60;	/* 60 = 0011 1100 */  
  char b = 13;	/* 13 = 0000 1101 */
  char c = 0, shift = 3;

  c = a & b;       /* 12  = 0000 1100 */
  printf("AND     - Value of c is %d\n", c );

  c = a | b;       /* 61  = 0011 1101 */
  printf("OR      - Value of c is %d\n", c );

  c = a ^ b;       /* 49  = 0011 0001 */
  printf("XOR     - Value of c is %d\n", c );

  c = ~a;          /* -61 = 1100 0011 */
  printf("NOT     - Value of c is %d\n", c );

  c = a << 2;      /* 240 = 1111 0000 */
  printf("shift L - Value of c is %d\n", c );

  c = a >> 3;      /* 7   = 0000 0111 */
  printf("shift R - Value of c is %d\n", c );
  
  //c = (a << shift) | (a >> (sizeof(a)*CHAR_BIT - shift));      /* 7   = 0000 0111 */
  c = (a << shift) | (a >> (8 - shift));      /* 7   = 0000 0111 */
  printf("shift C - Value of c is %d\n", c );
  
  printf("length of char %zu\n",sizeof(char)*8);
  printf("length of short %zu\n",sizeof(short)*8);
  printf("length of int %zu\n",sizeof(int)*8);
  printf("length of long %zu\n",sizeof(long)*8);
  printf("length of long long %zu\n",sizeof(long long)*8);
  printf("length of float %zu\n",sizeof(float)*8);
  printf("length of double %zu\n",sizeof(double)*8);
  printf("length of double %zu\n",sizeof(long double)*8);
}
