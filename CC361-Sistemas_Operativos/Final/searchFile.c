#include <unistd.h>
#include <time.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <sys/mman.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BSIZE 1024
void busca(char * file, char * secuencia);
void buscaFile(FILE * file);

int main(int argc, char *argv[]) {
		if(argc != 3){
			// cerr << "Usar: " << argv[0] << " archivoingreso archivosalida" << endl;
			printf("Usar: %s archivoingreso archivosalidan", argv[0]);
			return -1;
		}

	    // char *nombreArchivo = "archivo1.txt";
		int fd_in = open(argv[1], O_RDONLY);
		if(fd_in < 0){
			perror(argv[1]);
			return -1;
		}

		struct stat info;
		if(fstat(fd_in, &info) < 0){
			perror("Error status de archivo de ingreso");
			return -1;
		}

		// FILE * input = fopen(argv[1], "a");

		char *addr_in = (char *)mmap(0, info.st_size, PROT_READ, MAP_SHARED, fd_in, 0);
		printf("%s\n", addr_in);
		if(addr_in == MAP_FAILED){
			perror("Error mapeando archivo de ingreso");
			return -1;
		}

		/*BUSCAR CON mmap*/
		clock_t t = time(NULL);
		char *dst = (char *)mmap(0, info.st_size, PROT_READ, MAP_SHARED, fd_in, 0);

		char temp[20] = "75 6e 69 66 63";
		busca(dst, temp); 

		t = time(NULL) - t;
		printf("tiempo MMAP %lf\n", (float)t/CLOCKS_PER_SEC);


        /*Busca con fopen*/
		// char temp[20] = "75 6e 69 66 63";
		t = clock();
		FILE * fp = fopen(argv[1], "r");

		// printf("%d\n", longi);
		/*BUSCAR EN EL FILE, CON FOPEN*/
		buscaFile(fp);
		t = clock() - t;
		printf(" tiempo FOPEN%lf\n", (float)t/CLOCKS_PER_SEC);

		fclose(fp);
		/*fopen*/

		// int fd_out = open(argv[2], O_RDWR | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR);
		// if(fd_out < 0){
		// 	perror(argv[2]);
		// 	return -1;
		// }


		return 0;
}

void busca(char * file, char * secuencia){
        int longi = strlen(secuencia);
        printf("longi:%d\n",longi);
        int longiFile = strlen(file);
        int i=0,j;
        
        char aux[longi];
        while(i <= longiFile-longi){
                j=0;
              while(j<longi){
                if(file[i+j] != secuencia[j])break;
                j++;
                if(j==longi){printf("index:%d\n",i);          return;}
               
              }
              
             i++; 
            /*   copia(file,aux,i,longi);
               if(strcmp(file,aux) == 0) {
                        printf("index:%d\n",i);
                        break;
               }*/
        }
}

void buscaFile(FILE * file){
    char cadena[1024*1024];
    char *pcadena;
    pcadena =  fgets(cadena, 1024*1024, file);
    int i = 0;
    while (!(feof(file))) {
        // char temp;
        // temp = (char )fgetc(file);//fscanf(file, "%c", &temp);
        // printf("%c\n", temp);
        if (pcadena[i++] == '5'){
            printf("Encontrado\n");
            break;
        }
    }
}