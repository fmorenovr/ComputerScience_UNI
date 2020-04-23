#include <stdio.h>
 
int main()
{
    unsigned num,base,total=0,coeficiente=1,baseinicial;
    printf("Este programa va a pasar un numero natural en base n a una determinada base. Introduce el numero y las bases: ");
    scanf("%u %u %u",&baseinicial,&num,&base);
    while((num>0)&&(base>0)&&(baseinicial>0))
    {
        total=total+coeficiente*(num%base);
        num=num/base;
        coeficiente*=baseinicial;
    }
	printf("Las bases no pueden ser 0\n");
    printf("%u\n",total);
 
    return 0;
}
