/*
########################################################
###       @Copyright Moreno Vera, Felipe Adrian      ###
###        Simple Linked List Functions              ###
########################################################
*/

struct sllist{ // creo una estructura tipo sllist
   char elem; // elemento de la sllist
   struct sllist *sgte;
};

typedef struct sllist sllist;
typedef struct sllist *Sllist;

struct sllistf{ // sllist frecuency
  char elem;
  int times;
  struct sllistf *sgte;
};

typedef struct sllistf sllistf;
typedef struct sllistf *Sllistf;

// 1 Funcion para leer dato limpiando buffer de entrada
extern int strrcbff(char *str,int n);

// 7 Funciones de Ayuda a la sllist
extern void Create_sllist(Sllist *l);
extern Sllist Create_sllist_sgte();
extern void Destroy_sllist(Sllist *l);
extern int isSllist_empty(Sllist l);
extern void Create_sllistf(Sllistf *o);
extern Sllistf Create_sllistf_sgte();
extern void Destroy_sllistf(Sllistf *o);

// 3 Funciones para generar sllists
extern int isNumber(char i[]);
extern void Generate_sllist_left(Sllist *l,int n);
extern void Generate_sllist_right(Sllist *l,int n);
extern void Menu_generate(Sllist *l);

// 5 Funciones Insertar elementos de la sllist
extern void Sllist_insert_init(Sllist *l,char dato);
extern void Sllist_insert_last(Sllist *l,char dato);
extern void Sllist_insert_before_val(Sllist *l,char dato,char val);
extern void Sllist_insert_after_val(Sllist *l,char dato,char val);
extern void Menu_insert(Sllist *l);

// 7 Funciones Extraer elementos de la sllist
extern char Sllist_delete_init(Sllist *l);
extern char Sllist_delete_last(Sllist *l);
extern char Sllist_delete_val(Sllist *l,char val);
extern char Sllist_delete_before_val(Sllist *l,char val);
extern char Sllist_delete_after_val(Sllist *l,char val);
extern void Sllist_delete_elem_rep(Sllist *l);
extern void Menu_delete(Sllist *l);

// 4 Funciones de buscar y numerar los elementos de la sllist
extern void Search_elem_sllist(Sllist l,char val);
extern void Sllist_elem_frecuency(Sllist l,Sllistf *o);
extern int Num_elem_sllist(Sllist l);
extern void Order_sllist(Sllist *l);                     // Selection Sort en orden ascendente

// 4 Funciones para invertir elementos
extern void Invert_sllist(Sllist *l);
extern void Invert_n_elem_init(Sllist *l,int n);
extern void Invert_n_elem_last(Sllist *l,int n);
extern void Menu_invert(Sllist *l);

// 2 Funcion Imprimir elementos de la sllist
extern void Sllist_print(Sllist l);
extern void Sllistf_print(Sllistf o);

// FUNCION MAIN DE SLIMPLE LINKED LIST
extern void Menu_SLLmain();
