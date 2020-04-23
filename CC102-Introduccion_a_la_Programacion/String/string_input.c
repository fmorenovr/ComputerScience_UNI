#include <string.h>
#include <stdio.h>
#include <stdlib.h>

int main() 
{ 
      int n,j,m=7; 
      char buff[m]; 
      memset(buff,0,sizeof(buff)); 
      printf("Enter a number:"); 
      scanf("%i",&n); 
      printf("You entered %i \n",n); 
      printf("\n Enter a name:");
      fflush(stdin);
      getchar();
      fgets(buff,sizeof(buff),stdin); 
      printf("\n The name entered is %s\n",buff);
      printf("%lo\n",sizeof(buff)); 
      for(j=0;j<=m;j++) printf("%c %i\n",buff[j],j);
      return 0; 
}
/*
#include <stdio.h>

int main()
{
  char line[256];

  fgets(line, 256, stdin);

  puts(line);

  return 0;
}*/
