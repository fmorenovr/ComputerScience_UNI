/*
########################################################
###       @Copyright Moreno Vera, Felipe Adrian      ###
###               AVL Auto-Balance Tree              ###
########################################################
*/

struct nodeavl{
  char elem;
  int bf;
  struct nodeavl *parent;
  struct nodeavl *left;
  struct nodeavl *right;
};

typedef struct nodeavl nodoavl;
typedef struct nodeavl *Nodoavl; // este representara a una hoja del arbol
typedef struct nodeavl *AVLTREE; // este representara al arbol total

// ------------------------------------------------------------------------ //

extern int strrcbff(char *str,int n);
// ------------------------------------------------------------------------ //
// Funciones de ayuda
extern Nodoavl new_nodeavl(char);
extern int balanceFactor_avl(Nodoavl);
extern void Create_avl(AVLTREE *);
extern int isEmpty_avl(AVLTREE);
extern int isLeaf_nodeavl(Nodoavl);
// ------------------------------------------------------------------------ //
// Funciones de operaciones
extern void Generate_AVL(AVLTREE *,int);
extern void Destroy_avl(AVLTREE *);
extern Nodoavl rightRotate_avl(Nodoavl);
extern Nodoavl leftRotate_avl(Nodoavl);
extern AVLTREE Insert_avl(AVLTREE *,char,Nodoavl);
extern AVLTREE Delete_avl(AVLTREE ,char);

extern void Menu_operations_avl(AVLTREE *);

// ------------------------------------------------------------------------ //
// Funciones de informacion del arbol
extern Nodoavl Search_avl(AVLTREE,char);
extern int Height_avl(AVLTREE);
extern int Size_avl(AVLTREE);
extern int Leaf_count_avl(AVLTREE,int *);
extern Nodoavl Maximum_avl(AVLTREE);
extern Nodoavl Minimum_avl(AVLTREE);
extern int Sum_node_avl(AVLTREE,int *);
extern int Height_node_avl(AVLTREE,char);

extern void Menu_info_avl(AVLTREE);

// ------------------------------------------------------------------------ //
// Funcion de los tipos de recorridos de arbol
extern void avlPreorder_print(AVLTREE);
extern void avlInorder_print(AVLTREE);
extern void avlPostorder_print(AVLTREE);

// Funcion que muestra los niveles del arbol
extern void Level_print_avl(AVLTREE);
extern void Node_print_level_avl(AVLTREE,int,int);

// Funcion que muestra todos los caminos del arbol
extern void Paths_print_avl(AVLTREE);
extern void printPaths_avl(AVLTREE,char [],int);
extern void printArray_avl(char [],int);

// Funcion que muestra el arbol
extern void AVL_show(AVLTREE,int);
extern void Node_print_avl(Nodoavl,int);

extern void Menu_print_avl(AVLTREE);

// ------------------------------------------------------------------------ //

extern Nodoavl Nodo_parent_avl(AVLTREE,char);
extern Nodoavl Nodo_brother_avl(AVLTREE,char);
extern void Nodo_childs_avl(AVLTREE,char);
extern Nodoavl Successor_avl(AVLTREE,char);
extern Nodoavl Predecessor_avl(AVLTREE,char);

extern void Menu_family_avl(AVLTREE);
// ------------------------------------------------------------------------ //

extern int Same_avl(AVLTREE,AVLTREE);
// Funcion que refleja al arbol
extern void Mirror_avl(AVLTREE ); // Despues del mirror ya no es arbol binario hay que convertirlo de nuevo

extern void Menu_comparison_avl(AVLTREE);
// ------------------------------------------------------------------------ //
extern void Menu_AVLmain();
