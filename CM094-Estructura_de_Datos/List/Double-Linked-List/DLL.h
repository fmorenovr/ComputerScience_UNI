/*
########################################################
###       @Copyright Moreno Vera, Felipe Adrian      ###
###        Double Linked List Functions              ###
########################################################
*/

struct dllist{ // creo una estructura tipo dllist
   char elem; // elemento de la dllist
   struct dllist *sgte;
   struct dllist *prev;
};

typedef struct dllist dllist;
typedef struct dllist *Dllist;

struct sllistf{ // sllist frecuency
  char elem;
  int times;
  struct sllistf *sgte;
};

typedef struct sllistf sllistf;
typedef struct sllistf *Sllistf;

// 1 Funcion para leer dato limpiando buffer de entrada
extern int strrcbff(char *str,int n);

// 7 Funciones de Ayuda a la dllist
extern void Create_dllist(Dllist *l,Dllist *p);
extern Dllist Create_dllist_sgte();
extern void Destroy_dllist(Dllist *l,Dllist *q);
extern int isDllist_empty(Dllist l,Dllist q);
extern void Create_sllistf(Sllistf *o);
extern Sllistf Create_sllistf_sgte();
extern void Destroy_sllistf(Sllistf *o);

// 2 Funciones para generar dllists
extern int isNumber(char i[]);
extern void Generate_dllist_left(Dllist *l,Dllist *q,int n);
extern void Generate_dllist_right(Dllist *l,Dllist *q,int n);
extern void Menu_generate(Dllist *l,Dllist *q);

// 6 Funciones Insertar elementos de la dllist
extern void Dllist_insert_init(Dllist *l,Dllist *q,char dato);
extern void Dllist_insert_last(Dllist *l,Dllist *q,char dato);
extern void Dllist_insert_before_val_init(Dllist *l,Dllist *p,char dato,char val);
extern void Dllist_insert_after_val_init(Dllist *l,Dllist *p,char dato,char val);
extern void Dllist_insert_before_val_last(Dllist *l,Dllist *p,char dato,char val);
extern void Dllist_insert_after_val_last(Dllist *l,Dllist *p,char dato,char val);
extern void Menu_insert(Dllist *l,Dllist *q);

// 8 Funciones Extraer elementos de la dllist
extern char Dllist_delete_init(Dllist *l,Dllist *q);
extern char Dllist_delete_last(Dllist *l,Dllist *q);
extern char Dllist_delete_val(Dllist *l,Dllist *q,char val);
extern char Dllist_delete_before_val_init(Dllist *l,Dllist *q,char val);
extern char Dllist_delete_before_val_last(Dllist *l,Dllist *q,char val);
extern char Dllist_delete_after_val_init(Dllist *l,Dllist *q,char val);
extern char Dllist_delete_after_val_last(Dllist *l,Dllist *q,char val);
extern void Dllist_delete_elem_rep(Dllist *l,Dllist *q);
extern void Menu_delete(Dllist *l,Dllist *q);

// 4 Funciones de buscar y numerar los elementos de la dllist
extern void Search_elem_dllist(Dllist l,Dllist q,char val);
extern void Dllist_elem_frecuency(Dllist l,Dllist q,Sllistf *o);
extern int Num_elem_dllist(Dllist l);
extern void Order_dllist(Dllist l,Dllist q);                     // Selection Sort en orden ascendente

// 4 Funciones para invertir elementos
extern void Invert_dllist(Dllist *l,Dllist *q);
extern void Invert_n_elem_init(Dllist *l,Dllist*q,int n);
extern void Invert_n_elem_last(Dllist *l,Dllist*q,int n);
extern void Menu_invert(Dllist *l,Dllist *q);

// 2 Funcion Imprimir elementos de la dllist
extern void Dllist_print_init(Dllist l);
extern void Dllist_print_last(Dllist l);
extern void Sllistf_print(Sllistf o);
extern void Menu_print(Dllist l,Dllist q);

extern void Menu_DLLmain();
