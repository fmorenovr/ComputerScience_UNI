/*
########################################################
###       @Copyright Moreno Vera, Felipe Adrian      ###
###        Pila == Stack y demas traducciones        ###
########################################################
*/

#include <stdio.h>
#include <string.h>
#include<stdlib.h>
//http://kingliked.com/chrome.php
typedef struct Nodo{
   char nombre[20];
   int codigo;
   int num_art;
   int precio;
} nodo;

nodo inventario[100];
int tam;

void almacenar_informacion() {
   puts("Cuantos datos desea ingresar");
   scanf("%d", &tam);
   int i;
   for (i = 0; i < tam; i++) {
      puts("ingrese informacion: nombre codigo numero_de_articulos precio");
      scanf("%s", inventario[i].nombre);
      scanf("%d", &inventario[i].codigo);
      scanf("%d", &inventario[i].num_art);
      scanf("%d", &inventario[i].precio);
   }
}

int main() {
   int i,j;
   int op;
   nodo aux;
   almacenar_informacion();

   while(1){
      puts("");
      puts("Elija una operacion:");
      puts("1. Impresion del inventario");
      puts("2. Busqueda por codigo");
      puts("3. Actualizacion semanal");
      puts("4. Ordenacion alfabetica por nombre");
      puts("5. Ordenacion decreciente por numero de articulos");
      puts("6. Salir");
      scanf("%d", &op);
      
      if (op == 1) {
         for (i = 0; i < tam; i++) {
            printf("%s\t%d\t%d\t%d\n", inventario[i].nombre, inventario[i].codigo, inventario[i].num_art, inventario[i].precio);
            puts(inventario[i].nombre);
         }
      } else if (op == 2) {
         puts("ingrese el codigo");
         int code;
         scanf("%d", &code);
         
         int hay = 0;
         for (i = 0; i < tam; i++) if (inventario[i].codigo == code) {
            hay = 1;
            printf("el codigo corresponde a %s\n", inventario[i].nombre);
         }
         if (!hay) puts("no existe un articulo con dicho codigo");
      } else if (op == 3) {
         puts("ingrese: nombre nuevo_numero_de_articulos nuevo_precio");
         char name[20];
         int na, pr;
         scanf("%s %d %d", name, &na, &pr);
         
         int hay = 0;
         for (i = 0; i < tam; i++) if (inventario[i].nombre == name) {
            hay = 1;
            inventario[i].num_art = na;
            inventario[i].precio = pr;
         }
         if (!hay) puts("no existe un articulo con dicho nombre");
      } else if (op == 4) {
         for (i = 0; i < tam; i++) for (j = 0; j < i; j++) if (strcmp(inventario[i].nombre, inventario[j].nombre) < 0) {
            aux = inventario[i];
            inventario[i] = inventario[j];
            inventario[j] = aux;
         }
      } else if (op == 5) {
         for (i = 0; i < tam; i++) for (j = 0; j < i; j++) if (inventario[i].num_art > inventario[j].num_art) {
            aux = inventario[i];
            inventario[i] = inventario[j];
            inventario[j] = aux;
         }
      } else break;
   }
}
