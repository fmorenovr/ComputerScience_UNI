#include <stdio.h>
 
int main()
{
    unsigned num,base,total=0,coeficiente=1;
    printf("Este programa va a pasar un numero natural en base 10 a una determinada base. Introduce el numero y la base: ");
    scanf("%u %u",&num,&base);
    while(num!=0)
    {
        total=total+coeficiente*(num%base);
        num=num/base;
        coeficiente*=10;
    }
    printf("%u\n",total);
 
    return 0;
}
