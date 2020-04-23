/*
########################################################
###       @Copyright Moreno Vera, Felipe Adrian      ###
###               Binary Search Tree                 ###
########################################################
*/

struct nodebst{
  char elem;
  struct nodebst *parent;
  struct nodebst *left;
  struct nodebst *right;
};

typedef struct nodebst nodobst;
typedef struct nodebst *Nodobst; // este representara a una hoja del arbol
typedef struct nodebst *BSTREE; // este representara al arbol total

// ------------------------------------------------------------------------ //

extern int strrcbff(char *str,int n);
// ------------------------------------------------------------------------ //
// Funciones de ayuda
extern Nodobst new_nodebst(void);
extern void Create_bst(BSTREE *);
extern int isEmpty_bst(BSTREE);
extern int isLeaf_nodebst(Nodobst);
// ------------------------------------------------------------------------ //
// Funciones de operaciones
extern void Generate_BST(BSTREE *,int);
extern void Destroy_bst(BSTREE *);
extern int Insert_bst(BSTREE *,char,Nodobst);
extern BSTREE Delete_bst(BSTREE ,char);
extern Nodobst Transplant_bst(BSTREE,Nodobst,Nodobst);

extern void Menu_operations_bst(BSTREE *);

// ------------------------------------------------------------------------ //
// Funciones de informacion del arbol
extern Nodobst Search_bst(BSTREE,char);
extern int Height_bst(BSTREE);
extern int Size_bst(BSTREE);
extern int Leaf_count_bst(BSTREE,int *);
extern Nodobst Maximum_bst(BSTREE);
extern Nodobst Minimum_bst(BSTREE);
extern int Sum_node_bst(BSTREE,int *);
extern int Height_node_bst(BSTREE,char);

extern void Menu_info_bst(BSTREE);

// ------------------------------------------------------------------------ //
// Funcion de los tipos de recorridos de arbol
extern void bstPreorder_print(BSTREE);
extern void bstInorder_print(BSTREE);
extern void bstPostorder_print(BSTREE);

// Funcion que muestra los niveles del arbol
extern void Level_print_bst(BSTREE);
extern void Node_print_level_bst(BSTREE,int,int);

// Funcion que muestra todos los caminos del arbol
extern void Paths_print_bst(BSTREE);
extern void printPaths_bst(BSTREE,char [],int);
extern void printArray_bst(char [],int);

// Funcion que muestra el arbol
extern void BST_show(BSTREE,int);
extern void Node_print_bst(Nodobst,int);

extern void Menu_print_bst(BSTREE);

// ------------------------------------------------------------------------ //

extern Nodobst Nodo_parent_bst(BSTREE,char);
extern Nodobst Nodo_brother_bst(BSTREE,char);
extern void Nodo_childs_bst(BSTREE,char);
extern Nodobst Successor_bst(BSTREE,char);
extern Nodobst Predecessor_bst(BSTREE,char);

extern void Menu_family_bst(BSTREE);
// ------------------------------------------------------------------------ //

extern int Same_bst(BSTREE,BSTREE);
// Funcion que refleja al arbol
extern void Mirror_bst(BSTREE ); // Despues del mirror ya no es arbol binario hay que convertirlo de nuevo

extern void Menu_comparison_bst(BSTREE);
// ------------------------------------------------------------------------ //
extern void Menu_BSTmain();
