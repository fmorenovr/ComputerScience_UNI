#include <stdio.h>
#include <string.h>

void read_cmd_file(int *argc,char *argv[]){
  if (*argc != 2 ) return;
  char buf[256]; // buffer de 256
  char arguments[256][256]; // 256 arguments de 256 caracteres
  int line_nr=0,i;
  FILE *fp=(FILE *) NULL;
  fp=fopen(argv[1],"r");
  if (fp == (FILE *) NULL){
    printf("No pudo abrir el archivo: %s\n",argv[1]);
    return;
  }
  printf("lo abrio\n");
  while (fgets(buf,sizeof(buf)-1,fp) && !feof(fp)){
    line_nr++;
    strcpy(arguments[line_nr],buf);
    //printf("Argument read: %s\n",buf);
  }
  if (fp != (FILE *) NULL)  (void) fclose(fp);
  for (i=1;i<=line_nr;i++) printf("linea:%d %s\n",i,arguments[i]);
  *argv=&arguments[0][0];
  *argc=line_nr;
  return;
}

int main(int argc,char *argv[]){
  int i;
  read_cmd_file(&argc,argv);
  printf("argc=%d\n",argc);
  for (i=0;i<argc;i++) printf("%d,%s\n",i,argv[i]);
}
