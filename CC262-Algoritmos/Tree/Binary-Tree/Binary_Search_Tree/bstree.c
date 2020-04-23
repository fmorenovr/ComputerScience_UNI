/*
########################################################
###       @Copyright Moreno Vera, Felipe Adrian      ###
###               Binary Search Tree                 ###
########################################################
*/

#include <stdio.h>
#include <stdlib.h>
#include "bstree.h"

int strrcbff(char *str, int n)
{
  int i, c;
  c=getchar();
  if (c == EOF)
  {
    str[0] = '\0';
    return 0;
  }
  if (c == '\n')  i = 0;
  else
  {
    str[0] = c;
    i = 1;
  }
  for(; i < n-1 && (c=getchar())!=EOF && c!='\n'; i++)  str[i] = c;
  str[i] = '\0';
  if (c != '\n' && c != EOF)
    while ((c = getchar()) != '\n' && c != EOF);
  return 1;
}

void Generate_BST(BSTREE *root,int n)
{
  Destroy_bst(root);
  int i=0,correcto=1;
  char in[1],cad;
  for(i=0;i<n;)
  {
    strrcbff(in,2);
    cad=in[0];
    correcto=Insert_bst(root,cad,NULL);
    if(correcto==1) i++;
  }
}

Nodobst new_nodebst()
{
  Nodobst leaf = (Nodobst)malloc(sizeof(nodobst));
  leaf->parent=NULL;
  leaf->left=NULL;
  leaf->right=NULL;
  return (leaf);
}

void Create_bst(BSTREE *root)
{
  (*root)=NULL;
}

int isEmpty_bst(BSTREE root)
{
  return (root == NULL);
}

void Destroy_bst(BSTREE *root)
{
  if((*root)!=NULL)
  {
    Nodobst actual = (*root);
    Destroy_bst(&(actual->left));
    Destroy_bst(&(actual->right));
    actual->parent=NULL;
    actual->left=NULL;
    actual->right=NULL;
    free(actual);
  }
  (*root)=NULL;
}

int isLeaf_nodebst(Nodobst h)
{
  return (h->left==NULL && h->right==NULL);
}

void bstPreorder_print(BSTREE root)
{
  if (root != NULL)
  {
    printf("%c ", root->elem);
    bstPreorder_print(root->left);
    bstPreorder_print(root->right);
  }
}

void bstInorder_print(BSTREE root)
{
  if (root != NULL)
  {
    bstInorder_print(root->left);
    printf("%c ", root->elem);
    bstInorder_print(root->right);
  }
}

void bstPostorder_print(BSTREE root)
{
  if (root != NULL)
  {
    bstPostorder_print(root->left);
    bstPostorder_print(root->right);
    printf("%c ", root->elem);
  }
}

Nodobst Search_bst(BSTREE root,char dato)
{
  if(root==NULL)
  {
    return NULL;
  }
  else
  {
    Nodobst actual=root;
    if(actual->elem > dato)
      return Search_bst(actual->left,dato);
    else if( actual->elem < dato)
      return Search_bst(actual->right,dato);
    else return actual;
  }
}

int Insert_bst(BSTREE *root,char dato,Nodobst padre)
{
  if((*root)==NULL)
  {
    Nodobst aux=new_nodebst();
    aux->elem=dato;
    aux->parent=padre;
    (*root)=aux;
    return 1;
  }
  if(dato < (*root)->elem)
    Insert_bst(&((*root)->left),dato,(*root));
  else if(dato > (*root)->elem)
    Insert_bst(&((*root)->right),dato,(*root));
  else
  {
    printf("El dato ya esta en el arbol\n");
    return 0;
  }
}

Nodobst Transplant_bst(BSTREE root,Nodobst u,Nodobst v)
{
  if(u->parent==NULL) // para cuando es Nodobst raiz
    root=v;
  else if(u==u->parent->left)
    u->parent->left=v;
  else if(u==u->parent->right)
    u->parent->right=v;
  if(v!=NULL)
    v->parent=u->parent;
  return root;
}

BSTREE Delete_bst(BSTREE root,char dato)
{
  Nodobst z=Search_bst(root,dato);
  if(z!=NULL)
  {
    if(isLeaf_nodebst(z))
    {
      if(z->parent!=NULL){} //Replace_bst(z,z->parent);
    }
    else if(z->left==NULL&&z->right!=NULL)
      root=Transplant_bst(root,z,z->right);
    else if(z->right==NULL&&z->left!=NULL)
      root=Transplant_bst(root,z,z->left);
    else
    {
      Nodobst y=Minimum_bst(z->right);
      if(y->parent!=z)
      {
        root=Transplant_bst(root,y,y->right);
        y->right=z->right;
        y->right->parent=y;
      }
      root=Transplant_bst(root,z,y);
      y->left=z->left;
      y->left->parent=y;
    }
    free(z);
  }
  else  printf("\nNo se encontro elemento\n");
  return root;
}

void Node_print_bst(Nodobst t,int h)
{
  int i;
  if(h==0)  printf("nil<---");
  else
  {
	  printf("       ");
	  for(i=0; i<h; i++)
	  {
      if(h==1)
      {
        if(t!=NULL&&t->parent->left==t)
	        printf("\\---->");
	      if(t!=NULL&&t->parent->right==t)
	        printf("/---->");
	      if(t==NULL)
	        printf("\n");
      }
      else{
	      if(i<h-1)  printf("      ");
	      else
	      {
	        if(t!=NULL&&t->parent->left==t)
	          printf("\\---->");
	        if(t!=NULL&&t->parent->right==t)
	          printf("/---->");
	        if(t==NULL)
	          printf("\n");
	      }
	    }
	  }
	}
	if(t!=NULL) printf("%c\n", t->elem);
}

void BST_show(BSTREE root,int h)
{
  	if(root==NULL) Node_print_bst(root,h);
	  else
	  {
	    BST_show(root->right, h+1);
	    Node_print_bst(root, h);
	    BST_show(root->left, h+1);
	  }
}

int Height_bst(BSTREE root)
{
  if(root!=NULL)
  {
    int a,b;
    Nodobst actual=root;
    a=Height_bst(actual->left);
    b=Height_bst(actual->right);
    if(a>b) return (a+1);
    else  return (b+1);
  }
  else  return -1;
}

int Height_node_bst(BSTREE root,char dato)
{
  int height=0; // altura
  Nodobst actual=root;
  while(actual!=NULL)
  {
    if(dato == actual->elem)  return height;
    else
    {
      height++;
      if(dato < actual->elem) actual = actual->left;
      else if(dato > actual->elem) actual = actual->right;
    }
  }
  return -1;
}

int Leaf_count_bst(BSTREE root,int *count)
{
  if(root == NULL)  return (*count);
  if(isLeaf_nodebst(root)) (*count)++;
  Leaf_count_bst(root->left,count);
  Leaf_count_bst(root->right,count);
}

int Size_bst(BSTREE root)
{
  if(root==NULL)  return 0;
  else  return (Size_bst(root->left) + 1 + Size_bst(root->right));
}

void Mirror_bst(BSTREE root)
{
  if(root !=NULL)
  {
    Nodobst temp;
    Mirror_bst(root->left);
    Mirror_bst(root->right);
    temp = root->left;
    root->left = root->right;
    root->right=temp;
  }
}

int Same_bst(BSTREE a,BSTREE b)
{
  if(a==NULL && b==NULL) return 1;
  else if(a!=NULL && b!=NULL)
  {
    return(Same_bst(a->left,b->left) && Same_bst(a->right,b->right));
  }
  else  return 0;
}

Nodobst Minimum_bst(BSTREE root)
{
  if(root == NULL)
  {
    return NULL;
  }
  else
  {
    Nodobst actual = root;
    while (actual->left != NULL) { 
      actual = actual->left; 
    }
    return (actual);
  }
}

Nodobst Maximum_bst(BSTREE root)
{
  if(root == NULL)
  {
    return NULL;
  }
  else
  {
    Nodobst actual = root;
    while (actual->right != NULL) { 
      actual = actual->right; 
    }
    return (actual);
  }
}

void Level_print_bst(BSTREE root)
{
  int h,i;
  h=Height_bst(root)+1;
  for(i = 0;i < h;i++)
  {
    printf("\nNIVEL %d  :", i);
    Node_print_level_bst(root, i, 0);
    printf("\n");
  }
}

void Node_print_level_bst(BSTREE root,int a,int b)
{
  if(root)
  {
    if(a==b)  printf("  %5c",root->elem);
    else
    {
      Node_print_level_bst(root->left,a,b+1);
      Node_print_level_bst(root->right,a,b+1);
    }
  }
}

int Sum_node_bst(BSTREE root,int *sum)
{
  if(root)
  {
    Sum_node_bst(root->left,sum);
    (*sum)=(*sum) + (int)(root->elem)-48;
    Sum_node_bst(root->right,sum);
  }
  else  return (*sum);
}

void Paths_print_bst(BSTREE root)
{
  char path[100];
  printPaths_bst(root,path,0);
}

void printPaths_bst(BSTREE root,char path[],int pathlen)
{
  if(root==NULL)  return;
  path[pathlen]=root->elem;
  pathlen++;
  if(isLeaf_nodebst(root)) printArray_bst(path,pathlen);
  else
  {
    printPaths_bst(root->left,path,pathlen);
    printPaths_bst(root->right,path,pathlen);
  }
}

void printArray_bst(char ints[],int len)
{
  int i,sum=0;
  for(i=0;i<len;i++)
  {
    printf("%c ",ints[i]);
    sum=sum+(int)(ints[i])-48;
  }
  printf(" :::: La suma del camino es %i ",sum);
  printf("\n");
}

Nodobst Successor_bst(BSTREE tree,char dato)
{
  Nodobst root=Search_bst(tree,dato);
  if(root!=NULL)
  {
    if(root->right!=NULL)
      return (Minimum_bst(root->right));
    Nodobst actual=root->parent;
    while(actual!=NULL&& root==actual->right){
      root=actual;
      actual=actual->parent;
    }
    return actual;
  }
  else  return NULL;
}

Nodobst Predecessor_bst(BSTREE tree,char dato)
{
  Nodobst root=Search_bst(tree,dato);
  if(root!=NULL)
  {
    if(root->left!=NULL)
      return (Maximum_bst(root->left));
    Nodobst actual=root->parent;
    while(actual!=NULL && root== actual->left){
      root=actual;
      actual=actual->parent;
    }
    return actual;
  }
  else  return NULL;
}

Nodobst Nodo_parent_bst(BSTREE root,char dato)
{
  Nodobst actual=Search_bst(root,dato);
  if(actual!=NULL)  return actual->parent;
  else  return NULL;
}

Nodobst Nodo_brother_bst(BSTREE root,char dato)
{
  Nodobst actual=Search_bst(root,dato);
  if(actual!=NULL && actual->parent!=NULL && actual->parent->right==actual)  return actual->parent->left;
  if(actual!=NULL && actual->parent!=NULL && actual->parent->left==actual)  return actual->parent->right;
  else if(actual!=NULL && actual->parent==NULL)
  {
    return actual;
  }
  else  return NULL;
}

void Nodo_childs_bst(BSTREE tree,char dato)
{
  Nodobst root = Search_bst(tree,dato);
  if(root==NULL)  printf("No esta en el arbol o arbol vacio\n");
  else if(root->right==NULL && root->left==NULL)  printf("No tiene hijos\n");
  else if(root->right!=NULL && root->left==NULL)  printf("Solo tiene hijo derecho y es %c \n",root->right->elem);
  else if(root->right==NULL && root->left!=NULL)  printf("Solo tiene hijo izquierdo y es %c \n",root->left->elem);
  else  printf("Tiene hijo izquierdo a %c e hijo derecho a %c \n",root->left->elem,root->right->elem);
}

void Menu_family_bst(BSTREE root)
{
  int opcion;
  char dato,cad[1],opcion1[2];
  BSTREE ro;
  while(1)
  {
    printf("\n-----------------------------------------------");
    printf("\n-----------------------------------------------");
    printf("\n              Menu Familia");
    printf("\n1. Mostrar Padre");
    printf("\n2. Mostrar Hermano");
    printf("\n3. Mostrar Hijos");
    printf("\n4. Mostrar Sucesor");
    printf("\n5. Mostrar Predecesor");
    printf("\n6. exit");
    printf("\n-----------------------------------------------");
    printf("\n-----------------------------------------------");
    printf("\nIngrese Opcion: ");
    strrcbff(opcion1,4);
    opcion=atoi(opcion1);
    switch(opcion)
    {
      case 1:
        if(root==NULL)  printf("\nArbol vacio\n");
        else
        {
          printf("\nIngrese el elemento a mostrar padre: \n");
          strrcbff(cad,3);
          dato=cad[0];
          ro=Nodo_parent_bst(root,dato);
          if(ro==NULL)  printf("\nSu padre es NULL o no existe elemento\n");
          else  printf("\nSu padre es %c\n",ro->elem);
        }
        opcion=1;
        break;

      case 2:
        if(root==NULL)  printf("\nArbol vacio\n");
        else
        {
          printf("\nIngrese el elemento a mostrar hermano: \n");
          strrcbff(cad,3);
          dato=cad[0];
          ro=Nodo_brother_bst(root,dato);
          if(ro==NULL)  printf("\nNo tiene hermano o no existe elemento\n");
          else if(ro->parent==NULL) printf("\nEs el nodo raiz\n");
          else  printf("\nSu hermano es %c\n",ro->elem);
        }
        opcion=2;
        break;

      case 3:
        if(root==NULL)  printf("\nArbol vacio\n");
        else
        {
          printf("\nIngrese el elemento a mostrar hijos: \n");
          strrcbff(cad,3);
          dato=cad[0];
          Nodo_childs_bst(root,dato);
        }
        opcion=3;
        break;
        
      case 4:
        if(root==NULL)  printf("\nArbol vacio\n");
        else
        {
          printf("\nIngrese el elemento a mostrar Sucesor: \n");
          strrcbff(cad,3);
          dato=cad[0];
          ro=Successor_bst(root,dato);
          if (ro!=NULL)  printf("\nEl sucesor de %c es: %c \n",dato,ro->elem);
          else  printf("\nNo tiene sucesor o elemento no encontrado");
        }
        opcion=4;
        break;
        
      case 5:
        if(root==NULL)  printf("\nArbol vacio\n");
        else
        {
          printf("\nIngrese el elemento a mostrar Predecesor: \n");
          strrcbff(cad,3);
          dato=cad[0];
          ro=Predecessor_bst(root,dato);
          if (ro!=NULL)  printf("\nEl predecesor de %c es: %c \n",dato,ro->elem);
          else  printf("\nNo tiene sucesor o elemento no encontrado");
        }
        opcion=5;
        break;
        
      case 6:
      default:
        break;
    }
    if(opcion==6||(opcion!=1&&opcion!=2&&opcion!=3&&opcion!=4&&opcion!=5))  break;
  }
}

void Menu_print_bst(BSTREE root)
{
  int opcion;
  char opcion1[2];
  while(1)
  {
    printf("\n-----------------------------------------------");
    printf("\n-----------------------------------------------");
    printf("\n             Menu Imprimir");
    printf("\n1. Imprimir Preorder");
    printf("\n2. Imprimir Inorder");
    printf("\n3. Imprimir Postorder");
    printf("\n4. Imprimir por niveles");
    printf("\n5. Imprimir los caminos");
    printf("\n6. Imprimir el arbol");
    printf("\n7. exit");
    printf("\n-----------------------------------------------");
    printf("\n-----------------------------------------------");
    printf("\nIngrese Opcion: ");
    strrcbff(opcion1,4);
    opcion=atoi(opcion1);
    switch(opcion)
    {
      case 1:
        if(root==NULL)  printf("\nArbol vacio\n");
        else
        {
          printf("\nEl recorrido preorder es:\n");
          bstPreorder_print(root);
        }
        opcion=1;
        break;

      case 2:
        if(root==NULL)  printf("\nArbol vacio\n");
        else
        {
          printf("\nEl recorrido inorder es:\n");
          bstInorder_print(root);
        }
        opcion=2;
        break;

      case 3:
        if(root==NULL)  printf("\nArbol vacio\n");
        else
        {
          printf("\nEl recorrido postorder es:\n");
          bstPostorder_print(root);
        }
        opcion=3;
        break;
        
      case 4:
        if(root==NULL)  printf("\nArbol vacio\n");
        else
        {
          printf("\nLos Niveles son : \n");
          Level_print_bst(root);
        }
        opcion=4;
        break;
        
      case 5:
        if(root==NULL)  printf("\nArbol vacio\n");
        else
        {
          printf("\nLos caminos son : \n");
          Paths_print_bst(root);
        }
        opcion=5;
        break;

      case 6:
        if(root==NULL)  printf("\nArbol vacio\n");
        else
        {
          printf("\n\n");
          printf("\nEl arbol es : \n");
          BST_show(root,0);
          printf("\n\n");
        }
        opcion=6;
        break;

      case 7:
      default:
        break;
    }
    if(opcion==7||(opcion!=1&&opcion!=2&&opcion!=3&&opcion!=4&&opcion!=5&&opcion!=6))  break;
  }
}

void Menu_info_bst(BSTREE root)
{
  int opcion,*p,*q,sum=0,count=0,altura;
  char cad[1],dato,opcion1[2];
  p=&count;
  q=&sum;
  BSTREE ro;
  while(1)
  {
    printf("\n-----------------------------------------------");
    printf("\n-----------------------------------------------");
    printf("\n             Menu Informacion");
    printf("\n1. Buscar elemento");
    printf("\n2. Altura del arbol");
    printf("\n3. Tamano del arbol");
    printf("\n4. Numero de hojas del arbol");
    printf("\n5. Maximo valor del arbol");
    printf("\n6. Minimo valor del arbol");
    printf("\n7. Suma de los nodos del arbol");
    printf("\n8. Altura de un nodo determinado del arbol");
    printf("\n9. exit");
    printf("\n-----------------------------------------------");
    printf("\n-----------------------------------------------");
    printf("\nIngrese Opcion: ");
    strrcbff(opcion1,4);
    opcion=atoi(opcion1);
    switch(opcion)
    {
      case 1:
        if(root==NULL)  printf("\nArbol vacio\n");
        else
        {
          printf("\nIngrese dato a buscar:\n");
          strrcbff(cad,3);
          dato=cad[0];
          ro=Search_bst(root,dato);
          if(ro!=NULL)  printf("\nElemento encontrado!!\n");
          else  printf("\nNo existe elemento o arbol vacio\n");
        }
        opcion=1;
        break;

      case 2:
        if(root==NULL)  printf("\nArbol vacio\n");
        else
        {
          printf("\nLa altura del arbol es: %i \n",Height_bst(root));
        }
        opcion=2;
        break;

      case 3:
        if(root==NULL)  printf("\nArbol vacio\n");
        else
        {
          printf("\nEl tamano del arbol es: %i \n",Size_bst(root));
        }
        opcion=3;
        break;
        
      case 4:
        count=0;
        if(root==NULL)  printf("\nArbol vacio\n");
        else
        {
          printf("\nEl numero de hojas del arbol es: %i \n",Leaf_count_bst(root,p));
        }
        opcion=4;
        break;
        
      case 5:
        ro=Maximum_bst(root);
        if(ro==NULL)  printf("\nArbol vacio\n");
        else  printf("\nEl maximo valor del arbol es : %c \n",ro->elem);
        opcion=5;
        break;

      case 6:
        ro=Minimum_bst(root);
        if(ro==NULL)  printf("\nArbol vacio\n");
        else  printf("\nEl minimo valor del arbol es : %c \n",ro->elem);
        opcion=6;
        break;

      case 7:
        sum=0;
        if(root==NULL)  printf("\nArbol vacio\n");
        else
        {
          printf("\nLa suma de los nodos del arbol es: %i \n",Sum_node_bst(root,q));
        }
        opcion=7;
        break;

      case 8:
        if(root==NULL)  printf("\nArbol vacio\n");
        else
        {
          printf("Ingrese nodo para buscar su altura:\n");
          strrcbff(cad,3);
          dato=cad[0];
          altura=Height_node_bst(root,dato);
          if(altura==-1)  printf("\nElemento no existe\n");
          else  printf("\nLa altura del nodo %c es: %i \n",dato,altura);
        }
        opcion=8;
        break;

      case 9:
      default:
        break;
    }
    if(opcion==9||(opcion!=1&&opcion!=2&&opcion!=3&&opcion!=4&&opcion!=5&&opcion!=6&&opcion!=7&&opcion!=8))  break;
  }
}

void Menu_operations_bst(BSTREE *root)
{
  int opcion,numelem;
  char dato,cad[1],opcion1[2],elem[3];
  while(1)
  {
    printf("\n-----------------------------------------------");
    printf("\n-----------------------------------------------");
    printf("\n               Menu Operaciones");
    printf("\n1. Generar el arbol");
    printf("\n2. Insertar en el arbol");
    printf("\n3. Eliminar del arbol");
    printf("\n4. Destruir el arbol");
    printf("\n5. exit");
    printf("\n-----------------------------------------------");
    printf("\n-----------------------------------------------");
    printf("\nIngrese Opcion: ");
    strrcbff(opcion1,4);
    opcion=atoi(opcion1);
    switch(opcion)
    {
      case 1:
        printf("\nIngrese el tamano del arbol:\n");
        strrcbff(elem,4);
        numelem=atoi(elem);
        printf("\nIngrese los elementos del arbol:\n");
        Generate_BST(root,numelem);
        opcion=1;
        break;

      case 2:
        printf("\nIngrese el elemento a ingresar: \n");
        strrcbff(cad,3);
        dato=cad[0];
        Insert_bst(root,dato,NULL);
        opcion=2;
        break;

      case 3:
        if(isEmpty_bst((*root)))  printf("\nArbol vacio\n");
        else
        {
          printf("\nIngrese el elemento a eliminar: \n");
          strrcbff(cad,3);
          dato=cad[0];
          (*root)=Delete_bst((*root),dato);
        }
        opcion=3;
        break;

      case 4:
        printf("\nEl arbol se destruira!!\n");
        Destroy_bst(root);
        opcion=4;
        break;

      case 5:
      default:
        break;
    }
    if(opcion==5||(opcion!=1&&opcion!=2&&opcion!=3&&opcion!=4))  break;
  }
}

void Menu_comparison_bst(BSTREE root)
{
  int opcion,numelem,mirror=0,igual=1;
  char dato,cad[1],opcion1[2],elem[3];
  BSTREE aux;
  Create_bst(&aux);
  while(1)
  {
    printf("\n-----------------------------------------------");
    printf("\n-----------------------------------------------");
    printf("\n               Menu Comaracion y Espejo");
    printf("\n1. Generar el arbol auxiliar");
    printf("\n2. Imprimir el arbol auxiliar");
    printf("\n3. Comparar con el arbol original");
    printf("\n4. Reflejar el arbol");
    printf("\n5. exit");
    printf("\n-----------------------------------------------");
    printf("\n-----------------------------------------------");
    printf("\nIngrese Opcion: ");
    strrcbff(opcion1,4);
    opcion=atoi(opcion1);
    switch(opcion)
    {
      case 1:
        printf("\nIngrese el tamano del arbol:\n");
        strrcbff(elem,4);
        numelem=atoi(elem);
        printf("\nIngrese los elementos del arbol:\n");
        Generate_BST(&aux,numelem);
        opcion=1;
        break;

      case 2:
        if(root==NULL)  printf("\nArbol vacio\n");
        else
        {
          printf("\nEl arbol es : \n");
          BST_show(aux,0);
        }
        opcion=2;
        break;

      case 3:
        igual=Same_bst(root,aux);
        if(igual) printf("\nSon arboles similares\n");
        else  printf("\nNo son similares\n");
        opcion=3;
        break;

      case 4:
        if(isEmpty_bst(root))  printf("\nArbol vacio\n");
        else
        {
          if(mirror==0)
          {
            Mirror_bst(root);
            mirror=1;
          }
          else 
          {
            Mirror_bst(root);
            mirror=0;
          }
          BST_show(root,0);
        }
        opcion=4;
        break;

      case 5:
      default:
        break;
    }
    if(opcion==5||(opcion!=1&&opcion!=2&&opcion!=3&&opcion!=4))  break;
  }
  if(mirror==1)
  {
    Mirror_bst(root);
    mirror=0;
  }
  Destroy_bst(&aux);
}

void Menu_BSTmain()
{
  int opcion;
  char opcion1[2];
  BSTREE root;
  Create_bst(&root);
  while(1)
  {
    printf("\n-----------------------------------------------");
    printf("\n-----------------------------------------------");
    printf("\n               Menu Principal");
    printf("\n************ Binary Search Tree ************");
    printf("\n1. Menu operaciones");
    printf("\n2. Menu informacion");
    printf("\n3. Menu imprimir");
    printf("\n4. Menu familia");
    printf("\n5. Menu comparacion y espejo");
    printf("\n6. exit");
    printf("\n-----------------------------------------------");
    printf("\n-----------------------------------------------");
    printf("\nIngrese Opcion: ");
    strrcbff(opcion1,4);
    opcion=atoi(opcion1);
    switch(opcion)
    {
      case 1:
        Menu_operations_bst(&root);
        opcion=1;
        break;

      case 2:
        Menu_info_bst(root);
        opcion=2;
        break;

      case 3:
        Menu_print_bst(root);
        opcion=3;
        break;

      case 4:
        Menu_family_bst(root);
        opcion=4;
        break;

      case 5:
        Menu_comparison_bst(root);
        opcion=5;
        break;

      case 6:
      default:
        break;
    }
    if(opcion==6||(opcion!=1&&opcion!=2&&opcion!=3&&opcion!=4&&opcion!=5))  break;
  }
  
}

int main()
{
  Menu_BSTmain();
}
