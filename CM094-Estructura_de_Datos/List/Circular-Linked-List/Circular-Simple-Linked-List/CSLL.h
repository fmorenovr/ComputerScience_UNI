/*
########################################################
###       @Copyright Moreno Vera, Felipe Adrian      ###
###        Circular Simple Linked List Functions     ###
########################################################
*/

struct csllist{ // creo una estructura tipo csllist
   char elem; // elemento de la csllist
   struct csllist *sgte;
};

typedef struct csllist csllist;
typedef struct csllist *Csllist;

struct csllistf{ // csllist frecuency
  char elem;
  int times;
  struct csllistf *sgte;
};

typedef struct csllistf csllistf;
typedef struct csllistf *Csllistf;

// 1 Funcion para leer dato limpiando buffer de entrada
extern int strrcbff(char *str,int n);

// 7 Funciones de Ayuda a la csllist
extern void Create_csllist(Csllist *l);
extern Csllist Create_csllist_sgte();
extern void Destroy_csllist(Csllist *q,Csllist *l);
extern int isCsllist_empty(Csllist l);
extern void Create_csllistf(Csllistf *o);
extern Csllistf Create_csllistf_sgte();
extern void Destroy_csllistf(Csllistf *o);

// 3 Funciones para generar csllists
extern int isNumber(char i[]);
extern void Generate_csllist_left(Csllist *l,Csllist *q,int n);
extern void Generate_csllist_right(Csllist *l,Csllist *q,int n);
extern void Menu_generate(Csllist *q,Csllist *l);

// 5 Funciones Insertar elementos de la csllist
extern void Csllist_insert_init(Csllist *l,Csllist *q,char dato);
extern void Csllist_insert_last(Csllist *l,Csllist *q,char dato);
extern void Csllist_insert_before_val(Csllist *l,Csllist *q,char dato,char val);
extern void Csllist_insert_after_val(Csllist *l,Csllist *q,char dato,char val);
extern void Menu_insert(Csllist *q,Csllist *l);

// 7 Funciones Extraer elementos de la csllist
extern char Csllist_delete_init(Csllist *l,Csllist *q);
extern char Csllist_delete_last(Csllist *l,Csllist *q);
extern char Csllist_delete_val(Csllist *l,Csllist *q,char val);
extern char Csllist_delete_before_val(Csllist *l,Csllist *q,char val);
extern char Csllist_delete_after_val(Csllist *l,Csllist *q,char val);
extern void Csllist_delete_elem_rep(Csllist *l,Csllist *q);
extern void Menu_delete(Csllist *q,Csllist *l);

// 4 Funciones de buscar y numerar loselementos de la csllist
extern void Search_elem_csllist(Csllist q,Csllist l,char val);
extern void Csllist_elem_frecuency(Csllist q,Csllist l,Csllistf *o);
extern int Num_elem_csllist(Csllist l,Csllist q);
extern void Order_csllist(Csllist *l,Csllist *q);          // Selection Sort en orden ascendente

// 4 Funciones para invertir elementos
extern void Invert_csllist(Csllist *q,Csllist *l);
extern void Invert_n_elem_init(Csllist *q,Csllist *l,int n);
extern void Invert_n_elem_last(Csllist *q,Csllist *l,int n);
extern void Menu_invert(Csllist *q,Csllist *l);

// 2 Funcion Imprimir elementos de la csllist
extern void Csllist_print(Csllist l,Csllist q);
extern void Csllistf_print(Csllistf o);

// FUNCION MAIN DE CIRCULAR SLIMPLE LINKED LIST
extern void Menu_CSLLmain();
