#include <stdio.h>
#include <stdint.h>

int main(void){
  int16_t i = 1;
  int8_t *p = (int8_t *) &i;

  if (p[0] == 1)
    printf("Little Endian\n");
  else
    printf("Big Endian\n");
  return 0;
}
