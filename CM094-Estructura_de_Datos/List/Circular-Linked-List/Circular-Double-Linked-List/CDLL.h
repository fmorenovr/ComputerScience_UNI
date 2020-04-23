/*
########################################################
###       @Copyright Moreno Vera, Felipe Adrian      ###
###       Circular Double Linked List Functions      ###
########################################################
*/

struct cdllist{ // creo una estructura tipo cdllist
   char elem; // elemento de la cdllist
   struct cdllist *sgte;
   struct cdllist *prev;
};

typedef struct cdllist cdllist;
typedef struct cdllist *CDllist;

struct sllistf{ // sllist frecuency
  char elem;
  int times;
  struct sllistf *sgte;
};

typedef struct sllistf sllistf;
typedef struct sllistf *Sllistf;

// 1 Funcion para leer dato limpiando buffer de entrada
extern int strrcbff(char *str,int n);

// 7 Funciones de Ayuda a la cdllist
extern void Create_cdllist(CDllist *l);
extern CDllist Create_cdllist_sgte();
extern void Destroy_cdllist(CDllist *r,CDllist *l,CDllist *q);
extern int isCDllist_empty(CDllist l);
extern void Create_sllistf(Sllistf *o);
extern Sllistf Create_sllistf_sgte();
extern void Destroy_sllistf(Sllistf *o);

// 2 Funciones para generar cdllists
extern int isNumber(char i[]);
extern void Generate_cdllist_left(CDllist *r,CDllist *l,CDllist *q,int n);
extern void Generate_cdllist_right(CDllist *r,CDllist *l,CDllist *q,int n);
extern void Menu_generate(CDllist *r,CDllist *l,CDllist *q);

// 6 Funciones Insertar elementos de la cdllist
extern void CDllist_insert_init(CDllist *r,CDllist *l,CDllist *q,char dato);
extern void CDllist_insert_last(CDllist *r,CDllist *l,CDllist *q,char dato);
extern void CDllist_insert_before_val_init(CDllist *r,CDllist *l,CDllist *p,char dato,char val);
extern void CDllist_insert_after_val_init(CDllist *r,CDllist *l,CDllist *p,char dato,char val);
extern void CDllist_insert_before_val_last(CDllist *r,CDllist *l,CDllist *p,char dato,char val);
extern void CDllist_insert_after_val_last(CDllist *r,CDllist *l,CDllist *p,char dato,char val);
extern void Menu_insert(CDllist *r,CDllist *l,CDllist *q);

// 8 Funciones Extraer elementos de la cdllist
extern char CDllist_delete_init(CDllist *r,CDllist *l,CDllist *q);
extern char CDllist_delete_last(CDllist *r,CDllist *l,CDllist *q);
extern char CDllist_delete_val(CDllist *r,CDllist *l,CDllist *q,char val);
extern char CDllist_delete_before_val_init(CDllist *r,CDllist *l,CDllist *q,char val);
extern char CDllist_delete_before_val_last(CDllist *r,CDllist *l,CDllist *q,char val);
extern char CDllist_delete_after_val_init(CDllist *r,CDllist *l,CDllist *q,char val);
extern char CDllist_delete_after_val_last(CDllist *r,CDllist *l,CDllist *q,char val);
extern void CDllist_delete_elem_rep(CDllist *r,CDllist *l,CDllist *q);
extern void Menu_delete(CDllist *r,CDllist *l,CDllist *q);

// 4 Funciones de buscar y numerar los elementos de la cdllist
extern void Search_elem_cdllist(CDllist l,CDllist q,char val);
extern void CDllist_elem_frecuency(CDllist l,CDllist q,Sllistf *o);
extern int Num_elem_cdllist(CDllist q,CDllist l);
extern void Order_cdllist(CDllist r,CDllist l,CDllist q);         // Selection Sort en orden ascendente

// 4 Funciones para invertir elementos
extern void Invert_cdllist(CDllist *r,CDllist *l,CDllist *q);
extern void Invert_n_elem_init(CDllist *r,CDllist *l,CDllist*q,int n);
extern void Invert_n_elem_last(CDllist *r,CDllist *l,CDllist*q,int n);
extern void Menu_invert(CDllist *r,CDllist *l,CDllist *q);

// 2 Funcion Imprimir elementos de la cdllist
extern void CDllist_print_init(CDllist l,CDllist q);
extern void CDllist_print_last(CDllist l,CDllist q);
extern void Sllistf_print(Sllistf o);
extern void Menu_print(CDllist r,CDllist q,CDllist l);

extern void Menu_CDLLmain();
