/*
########################################################
###       @Copyright Moreno Vera, Felipe Adrian      ###
###               AVL Auto-Balance Tree              ###
########################################################
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "avlbstree.h"

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

Nodoavl new_nodeavl(char dato)
{
  Nodoavl leaf = (Nodoavl)malloc(sizeof(nodoavl));
  leaf->elem=dato;
  leaf->parent=NULL;
  leaf->left=NULL;
  leaf->right=NULL;
  leaf->bf=0; // cuando es hoja su factor de balance es 0
  return (leaf);
}

void Create_avl(AVLTREE *root)
{
  (*root)=NULL;
}

int isEmpty_avl(AVLTREE root)
{
  return (root == NULL);
}

int isLeaf_nodeavl(Nodoavl h)
{
  return (h->left==NULL && h->right==NULL);
}

int Sum_node_avl(AVLTREE root,int *sum)
{
  if(root)
  {
    Sum_node_avl(root->left,sum);
    (*sum)=(*sum) + (int)(root->elem)-48;
    Sum_node_avl(root->right,sum);
  }
  else  return (*sum);
}

int Height_avl(AVLTREE root)
{
  if(root!=NULL)
  {
    int a,b;
    Nodoavl actual=root;
    a=Height_avl(actual->left);
    b=Height_avl(actual->right);
    if(a>b) return (a+1);
    else  return (b+1);
  }
  else  return -1;
}

int balanceFactor_avl(Nodoavl N)
{
  if (N == NULL)
    return 0;
  return Height_avl(N->right) - Height_avl(N->left);
}

void avlPreorder_print(AVLTREE root)
{
  if (root != NULL)
  {
    printf("%c ", root->elem);
    avlPreorder_print(root->left);
    avlPreorder_print(root->right);
  }
}

void avlInorder_print(AVLTREE root)
{
  if (root != NULL)
  {
    avlInorder_print(root->left);
    printf("%c ", root->elem);
    avlInorder_print(root->right);
  }
}

void avlPostorder_print(AVLTREE root)
{
  if (root != NULL)
  {
    avlPostorder_print(root->left);
    avlPostorder_print(root->right);
    printf("%c ", root->elem);
  }
}

void Paths_print_avl(AVLTREE root)
{
  char path[100];
  printPaths_avl(root,path,0);
}

void printPaths_avl(AVLTREE root,char path[],int pathlen)
{
  if(root==NULL)  return;
  path[pathlen]=root->elem;
  pathlen++;
  if(isLeaf_nodeavl(root)) printArray_avl(path,pathlen);
  else
  {
    printPaths_avl(root->left,path,pathlen);
    printPaths_avl(root->right,path,pathlen);
  }
}

void printArray_avl(char ints[],int len)
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

void Node_print_avl(Nodoavl t,int h)
{
  int i;
  if(h==0)  printf("nil<---");
  else
  {
	  printf("         ");
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
	      if(i<h-1)  printf("        ");
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
	if(t!=NULL) printf("%c(%i)\n",t->elem,t->bf);
}

void AVL_show(AVLTREE root,int h)
{
  	if(root==NULL) Node_print_avl(root,h);
	  else
	  {
	    AVL_show(root->right, h+1);
	    Node_print_avl(root, h);
	    AVL_show(root->left, h+1);
	  }
}

void Level_print_avl(AVLTREE root)
{
  int h,i;
  h=Height_avl(root)+1;
  for(i = 0;i < h;i++)
  {
    printf("\nNIVEL %d  :", i);
    Node_print_level_avl(root, i, 0);
    printf("\n");
  }
}

void Node_print_level_avl(AVLTREE root,int a,int b)
{
  if(root)
  {
    if(a==b)  printf("  %5c",root->elem);
    else
    {
      Node_print_level_avl(root->left,a,b+1);
      Node_print_level_avl(root->right,a,b+1);
    }
  }
}

void Destroy_avl(AVLTREE *root)
{
  if((*root)!=NULL)
  {
    Nodoavl actual = (*root);
    Destroy_avl(&(actual->left));
    Destroy_avl(&(actual->right));
    actual->parent=NULL;
    actual->left=NULL;
    actual->right=NULL;
    free(actual);
  }
  (*root)=NULL;
}

int Size_avl(AVLTREE root)
{
  if(root==NULL)  return 0;
  else  return (Size_avl(root->left) + 1 + Size_avl(root->right));
}

int Height_node_avl(AVLTREE root,char dato)
{
  int height=0; // altura
  Nodoavl actual=root;
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

int Leaf_count_avl(AVLTREE root,int *count)
{
  if(root == NULL)  return (*count);
  if(isLeaf_nodeavl(root)) (*count)++;
  Leaf_count_avl(root->left,count);
  Leaf_count_avl(root->right,count);
}

int Same_avl(AVLTREE a,AVLTREE b)
{
  if(a==NULL && b==NULL) return 1;
  else if(a!=NULL && b!=NULL)
  {
    return(Same_avl(a->left,b->left) && Same_avl(a->right,b->right));
  }
  else  return 0;
}

void Mirror_avl(AVLTREE root)
{
  if(root !=NULL)
  {
    Nodoavl temp;
    Mirror_avl(root->left);
    Mirror_avl(root->right);
    temp = root->left;
    root->left = root->right;
    root->right=temp;
  }
}

void Generate_BST(AVLTREE *root)
{
  Destroy_avl(root);
  char in[100],cad;
  int i=0,correcto=1;
  strrcbff(in,100);
  int n=(int)strlen(in);
  for(i=0;i<n;)
  {
    cad=in[i];
    correcto=Insert_bst(root,cad,NULL);
    i++;
  }
}

void Generate_AVL(AVLTREE *root)
{
  Destroy_avl(root);
  char in[100],cad;
  int i=0;
  strrcbff(in,100);
  int n=(int)strlen(in);
  Nodoavl correcto;
  for(i=0;i<n;)
  {
    cad=in[i];
    correcto=Search_avl((*root),cad);
    if(correcto==NULL)
    {
      (*root)=Insert_avl(root,cad,NULL);
    }
    else
    {
      printf("\nel dato ya esta en el arbol\n");
    }
    i++;
  }
}

Nodoavl rightRotate_avl(Nodoavl y)
{
  Nodoavl x=y->left,T2=x->right;

  x->right=y;
  y->left=T2;
  x->parent=y->parent;
  y->parent=x;
  if(T2!=NULL)  T2->parent=y;
  
  y->bf=balanceFactor_avl(y);
  x->bf=balanceFactor_avl(x);
  
  return x;
}

Nodoavl leftRotate_avl(Nodoavl x)
{
  Nodoavl y=x->right,T2=y->left;

  y->left=x;
  x->right=T2;
  y->parent=x->parent;
  x->parent=y;
  if(T2!=NULL)  T2->parent=x;
  
  y->bf=balanceFactor_avl(y);
  x->bf=balanceFactor_avl(x);
  
  return y;
}

AVLTREE Insert_avl(AVLTREE *root,char dato,Nodoavl padre)
{
  if((*root)==NULL)
  {
    Nodoavl aux=new_nodeavl(dato);
    aux->parent=padre;
    (*root)=aux;
    return (*root);
  }
  if(dato < (*root)->elem)
    (*root)->left=Insert_avl(&((*root)->left),dato,(*root));
  else if(dato > (*root)->elem)
    (*root)->right=Insert_avl(&((*root)->right),dato,(*root));
  else  printf("\nEl dato ya esta en el arbol\n");

  (*root)->bf=balanceFactor_avl((*root));  
  int balance=balanceFactor_avl((*root));
  
  // si esta desbalanceado, se evalua segun getbalance

  // Left Left Case
  if (balance < -1 && dato < (*root)->left->elem)
    return rightRotate_avl((*root));

  // Left Right Case
  else if (balance < -1 && dato > (*root)->left->elem)
  {
    (*root)->left =  leftRotate_avl((*root)->left);
    return rightRotate_avl((*root));
  }

  // Right Right Case
  else if (balance > 1 && dato > (*root)->right->elem)
    return leftRotate_avl((*root));
 
  // Right Left Case
  else if (balance > 1 && dato < (*root)->right->elem)
  {
    (*root)->right = rightRotate_avl((*root)->right);
    return leftRotate_avl((*root));
  }
  return (*root);
}

AVLTREE Delete_avl(AVLTREE root,char dato)
{
  if (root == NULL)
    return root;

  if ( dato < root->elem )
    root->left = Delete_avl(root->left, dato);
  else if( dato > root->elem )
    root->right = Delete_avl(root->right, dato);
  else
  {
    // cuando tiene un hijo
    if((root->left == NULL) || (root->right == NULL))
    {
      Nodoavl temp;
      temp=root->left? root->left : root->right;
      // evalua si left es !=null si es cierto tomo left o sino right
      // sin hijos
      if(temp==NULL)
      {
        temp=root;
        root=NULL;
      }
      // un hijo
      else  root=temp;
      free(temp);
    }
    else // 2 hijos agarra el minimo del arbol derecho
    {
      Nodoavl temp=Minimum_avl(root->right);
      root->elem=temp->elem;
      root->right=Delete_avl(root->right,temp->elem);
    }
  }
  // si solo tenia un nodito q era raiz
  if(root==NULL)
    return root;
  root->bf=balanceFactor_avl(root);
  int balance=balanceFactor_avl(root);
  
  // Left left case
  if (balance < -1 && balanceFactor_avl(root->left) < 0)
    return rightRotate_avl(root);

  // Left Right Case
  if (balance < -1 && balanceFactor_avl(root->left) >= 0)
  {
    root->left =  leftRotate_avl(root->left);
    return rightRotate_avl(root);
  }
 
  // Right Right Case
  if (balance > 1 && balanceFactor_avl(root->right) > 0)
    return leftRotate_avl(root);
 
  // Right Left Case
  if (balance > 1 && balanceFactor_avl(root->right) <= 0)
  {
    root->right = rightRotate_avl(root->right);
    return leftRotate_avl(root);
  }
  
  return root;
}

Nodoavl Search_avl(AVLTREE root,char dato)
{
  if(root==NULL)
  {
    return NULL;
  }
  else
  {
    Nodoavl actual=root;
    if(actual->elem > dato)
      return Search_avl(actual->left,dato);
    else if( actual->elem < dato)
      return Search_avl(actual->right,dato);
    else return actual;
  }
}

Nodoavl Successor_avl(AVLTREE tree,char dato)
{
  Nodoavl root=Search_avl(tree,dato);
  if(root!=NULL)
  {
    if(root->right!=NULL)
      return (Minimum_avl(root->right));
    Nodoavl actual=root->parent;
    while(actual!=NULL&& root==actual->right){
      root=actual;
      actual=actual->parent;
    }
    return actual;
  }
  else  return NULL;
}

Nodoavl Predecessor_avl(AVLTREE tree,char dato)
{
  Nodoavl root=Search_avl(tree,dato);
  if(root!=NULL)
  {
    if(root->left!=NULL)
      return (Maximum_avl(root->left));
    Nodoavl actual=root->parent;
    while(actual!=NULL && root== actual->left){
      root=actual;
      actual=actual->parent;
    }
    return actual;
  }
  else  return NULL;
}

Nodoavl Minimum_avl(AVLTREE root)
{
  if(root == NULL)
  {
    return NULL;
  }
  else
  {
    Nodoavl actual = root;
    while (actual->left != NULL) { 
      actual = actual->left; 
    }
    return (actual);
  }
}

Nodoavl Maximum_avl(AVLTREE root)
{
  if(root == NULL)
  {
    return NULL;
  }
  else
  {
    Nodoavl actual = root;
    while (actual->right != NULL) { 
      actual = actual->right; 
    }
    return (actual);
  }
}

Nodoavl Nodo_parent_avl(AVLTREE root,char dato)
{
  Nodoavl actual=Search_avl(root,dato);
  if(actual!=NULL)  return actual->parent;
  else  return NULL;
}

Nodoavl Nodo_brother_avl(AVLTREE root,char dato)
{
  Nodoavl actual=Search_avl(root,dato);
  if(actual!=NULL && actual->parent!=NULL && actual->parent->right==actual)  return actual->parent->left;
  if(actual!=NULL && actual->parent!=NULL && actual->parent->left==actual)  return actual->parent->right;
  else if(actual!=NULL && actual->parent==NULL)
  {
    return actual;
  }
  else  return NULL;
}

void Nodo_childs_avl(AVLTREE tree,char dato)
{
  Nodoavl root = Search_avl(tree,dato);
  if(root==NULL)  printf("No esta en el arbol o arbol vacio\n");
  else if(root->right==NULL && root->left==NULL)  printf("No tiene hijos\n");
  else if(root->right!=NULL && root->left==NULL)  printf("Solo tiene hijo derecho y es %c \n",root->right->elem);
  else if(root->right==NULL && root->left!=NULL)  printf("Solo tiene hijo izquierdo y es %c \n",root->left->elem);
  else  printf("Tiene hijo izquierdo a %c e hijo derecho a %c \n",root->left->elem,root->right->elem);
}

int Insert_bst(AVLTREE *root,char dato,Nodoavl padre)
{
  if((*root)==NULL)
  {
    Nodoavl aux=new_nodeavl(dato);
    aux->parent=padre;
    (*root)=aux;
    return 1;
  }
  (*root)->bf=balanceFactor_avl((*root));
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

Nodoavl Transplant_bst(AVLTREE root,Nodoavl u,Nodoavl v)
{
  if(u->parent==NULL) // para cuando es Nodoavl raiz
    root=v;
  else if(u==u->parent->left)
    u->parent->left=v;
  else if(u==u->parent->right)
    u->parent->right=v;
  if(v!=NULL)
    v->parent=u->parent;
  return root;
}

AVLTREE Delete_bst(AVLTREE root,char dato)
{
  Nodoavl z=Search_avl(root,dato);
  if(z!=NULL)
  {
    if(isLeaf_nodeavl(z))
    {
      if(z->parent!=NULL){} //Replace_avl(z,z->parent);
    }
    else if(z->left==NULL&&z->right!=NULL)
      root=Transplant_bst(root,z,z->right);
    else if(z->right==NULL&&z->left!=NULL)
      root=Transplant_bst(root,z,z->left);
    else
    {
      Nodoavl y=Minimum_avl(z->right);
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


void Menu_info_avl(AVLTREE root)
{
  int opcion,*p,*q,sum=0,count=0,altura;
  char cad[1],dato,opcion1[2];
  p=&count;
  q=&sum;
  AVLTREE ro;
  system ("clear");
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
          ro=Search_avl(root,dato);
          if(ro!=NULL)  printf("\nElemento encontrado!!\n");
          else  printf("\nNo existe elemento o arbol vacio\n");
        }
        opcion=1;
        break;

      case 2:
        if(root==NULL)  printf("\nArbol vacio\n");
        else
        {
          printf("\nLa altura del arbol es: %i \n",Height_avl(root));
        }
        opcion=2;
        break;

      case 3:
        if(root==NULL)  printf("\nArbol vacio\n");
        else
        {
          printf("\nEl tamano del arbol es: %i \n",Size_avl(root));
        }
        opcion=3;
        break;
        
      case 4:
        count=0;
        if(root==NULL)  printf("\nArbol vacio\n");
        else
        {
          printf("\nEl numero de hojas del arbol es: %i \n",Leaf_count_avl(root,p));
        }
        opcion=4;
        break;
        
      case 5:
        ro=Maximum_avl(root);
        if(ro==NULL)  printf("\nArbol vacio\n");
        else  printf("\nEl maximo valor del arbol es : %c \n",ro->elem);
        opcion=5;
        break;

      case 6:
        ro=Minimum_avl(root);
        if(ro==NULL)  printf("\nArbol vacio\n");
        else  printf("\nEl minimo valor del arbol es : %c \n",ro->elem);
        opcion=6;
        break;

      case 7:
        sum=0;
        if(root==NULL)  printf("\nArbol vacio\n");
        else
        {
          printf("\nLa suma de los nodos del arbol es: %i \n",Sum_node_avl(root,q));
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
          altura=Height_node_avl(root,dato);
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

void Menu_print_avl(AVLTREE root)
{
  int opcion;
  char opcion1[2];
  system ("clear");
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
          avlPreorder_print(root);
        }
        opcion=1;
        break;

      case 2:
        if(root==NULL)  printf("\nArbol vacio\n");
        else
        {
          printf("\nEl recorrido inorder es:\n");
          avlInorder_print(root);
        }
        opcion=2;
        break;

      case 3:
        if(root==NULL)  printf("\nArbol vacio\n");
        else
        {
          printf("\nEl recorrido postorder es:\n");
          avlPostorder_print(root);
        }
        opcion=3;
        break;
        
      case 4:
        if(root==NULL)  printf("\nArbol vacio\n");
        else
        {
          printf("\nLos Niveles son : \n");
          Level_print_avl(root);
        }
        opcion=4;
        break;
        
      case 5:
        if(root==NULL)  printf("\nArbol vacio\n");
        else
        {
          printf("\nLos caminos son : \n");
          Paths_print_avl(root);
        }
        opcion=5;
        break;

      case 6:
        if(root==NULL)  printf("\nArbol vacio\n");
        else
        {
          printf("\n\n");
          printf("\nEl arbol es : \n");
          AVL_show(root,0);
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

void Menu_comparison_avl(AVLTREE root)
{
  int opcion,mirror=0,igual=1;
  char dato,cad[1],opcion1[2];
  AVLTREE aux;
  Create_avl(&aux);
  system ("clear");
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
        printf("\nIngrese los elementos del arbol:\n");
        Generate_AVL(&aux);
        opcion=1;
        break;

      case 2:
        if(root==NULL)  printf("\nArbol vacio\n");
        else
        {
          printf("\nEl arbol es : \n");
          AVL_show(aux,0);
        }
        opcion=2;
        break;

      case 3:
        igual=Same_avl(root,aux);
        if(igual) printf("\nSon arboles similares\n");
        else  printf("\nNo son similares\n");
        opcion=3;
        break;

      case 4:
        if(isEmpty_avl(root))  printf("\nArbol vacio\n");
        else
        {
          if(mirror==0)
          {
            Mirror_avl(root);
            mirror=1;
          }
          else 
          {
            Mirror_avl(root);
            mirror=0;
          }
          AVL_show(root,0);
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
    Mirror_avl(root);
    mirror=0;
  }
  Destroy_avl(&aux);
}

void Menu_family_avl(AVLTREE root)
{
  int opcion;
  char dato,cad[1],opcion1[2];
  AVLTREE ro;
  system ("clear");
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
          ro=Nodo_parent_avl(root,dato);
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
          ro=Nodo_brother_avl(root,dato);
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
          Nodo_childs_avl(root,dato);
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
          ro=Successor_avl(root,dato);
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
          ro=Predecessor_avl(root,dato);
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

void Menu_tree(AVLTREE *root)
{
  int opcion;
  char dato,cad[1],opcion1[2];
  AVLTREE ro;
  system ("clear");
  while(1)
  {
    printf("\n-----------------------------------------------");
    printf("\n-----------------------------------------------");
    printf("\n              Menu Arboles");
    printf("\n1. Binary Search Tree ");
    printf("\n2. Adelson Velski - Landis Tree");
    printf("\n3. exit");
    printf("\n-----------------------------------------------");
    printf("\n-----------------------------------------------");
    printf("\nIngrese Opcion: ");
    strrcbff(opcion1,4);
    opcion=atoi(opcion1);
    switch(opcion)
    {
      case 1:
        printf("Menu arbol binario\n");
        Menu_operations_bst(root);
        opcion=1;
        break;

      case 2:
        printf("Menu arbol avl\n");
        Menu_operations_avl(root);
        opcion=2;
        break;

      case 3:
      default:
        break;
    }
    if(opcion==3||(opcion!=1&&opcion!=2))  break;
  }
}

void Menu_AVLmain()
{
  int opcion;
  char opcion1[2];
  AVLTREE root;
  Create_avl(&root);
  system ("clear");
  while(1)
  {
    printf("\n-----------------------------------------------");
    printf("\n-----------------------------------------------");
    printf("\n               Menu Principal");
    printf("\n************ Binary Search Tree ************");
    printf("\n************ Adelson-Velski Landis Tree ************");
    printf("\n1. Menu arboles");
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
        Menu_tree(&root);
        opcion=1;
        break;

      case 2:
        Menu_info_avl(root);
        opcion=2;
        break;

      case 3:
        Menu_print_avl(root);
        opcion=3;
        break;

      case 4:
        Menu_family_avl(root);
        opcion=4;
        break;

      case 5:
        Menu_comparison_avl(root);
        opcion=5;
        break;

      case 6:
      default:
        break;
    }
    if(opcion==6||(opcion!=1&&opcion!=2&&opcion!=3&&opcion!=4&&opcion!=5))  break;
  }
  
}

void Menu_operations_bst(AVLTREE *root)
{
  int opcion;
  char dato,cad[1],opcion1[2];
  system ("clear");
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
        printf("\nIngrese los elementos del arbol:\n");
        Generate_BST(root);
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
        if(isEmpty_avl((*root)))  printf("\nArbol vacio\n");
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
        Destroy_avl(root);
        opcion=4;
        break;

      case 5:
      default:
        break;
    }
    if(opcion==5||(opcion!=1&&opcion!=2&&opcion!=3&&opcion!=4))  break;
  }
}

void Menu_operations_avl(AVLTREE *root)
{
  int opcion;
  char dato,cad[1],opcion1[2];
  system ("clear");
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
        printf("\nIngrese los elementos del arbol:\n");
        Generate_AVL(root);
        opcion=1;
        break;

      case 2:
        printf("\nIngrese el elemento a ingresar: \n");
        strrcbff(cad,3);
        dato=cad[0];
        Insert_avl(root,dato,NULL);
        opcion=2;
        break;

      case 3:
        if(isEmpty_avl((*root)))  printf("\nArbol vacio\n");
        else
        {
          printf("\nIngrese el elemento a eliminar: \n");
          strrcbff(cad,3);
          dato=cad[0];
          (*root)=Delete_avl((*root),dato);
        }
        opcion=3;
        break;

      case 4:
        printf("\nEl arbol se destruira!!\n");
        Destroy_avl(root);
        opcion=4;
        break;

      case 5:
      default:
        break;
    }
    if(opcion==5||(opcion!=1&&opcion!=2&&opcion!=3&&opcion!=4))  break;
  }
}

int main()
{
  Menu_AVLmain();
  return 0;
}
