/*
########################################################
###       @Copyright Moreno Vera, Felipe Adrian      ###
###        Pila == Stack y demas traducciones        ###
########################################################
*/

struct pila{ // creo una estructura tipo Lista
   char elem; // elemento de la lista
   struct pila *sgte;
};

typedef struct pila pila;
typedef struct pila *Pila;

int strrcbff(char *str,int n);
void Crear_pila(Pila *l);
int esPila_vacia(Pila l);
void Destruir_pila(Pila *l);
Pila Crear_pila_sgte();

int Generar_pila(Pila *l,int n);
void Pila_insert_left(Pila *l,char dato);
void Pila_insert_right(Pila *l,char dato);
char Pila_delet_right(Pila *l);

int Buscar_elem_Pila(Pila l,char info);
Pila Invertir_pila(Pila *l);
void Pila_print(Pila l);
int esNumero(char i);
void Completar_zeros(Pila *l,int n,int m);
// Operaciones suma resta division multiplicacion

Pila Suma(Pila l,Pila q);
Pila Resta(Pila l,Pila q);
