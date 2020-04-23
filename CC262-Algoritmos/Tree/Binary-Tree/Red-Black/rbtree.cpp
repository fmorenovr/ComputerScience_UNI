#include <iostream>
#include <stdio.h>
using namespace std;

int power(int x , int y){
	if(y==0)
		return 1;
	return x*power(x,--y);
}

struct node{
	int key;
	node* right;
	node* left;
	node* parent;
	char color;
};



struct t{
	node* root;
	node* nil;
};


node* NIL = new node;

node* newNode(int ikey){
	node* z = new node;
	z->key = ikey;
	z->parent = NIL;
	z->right = NIL;
	z->left = NIL;
	z->color = 'b';
	return z;
}

void leftRotate(t* T , node* x){
	node* y = x->right;
	x->right = y->left;
	if(y->left != T->nil)
		y->left->parent = x;
	y->parent = x->parent;
	if(x->parent == T->nil)
		T->root = y;
	else if(x==x->parent->left)
		x->parent->left = y;
	else
		x->parent->right = y;
	y->left = x;
	x->parent = y;
}

void rightRotate(t* T, node* y){
	node* x = y->left;
	y->left = x->right;
	if(x->right != T->nil)
		x->right->parent = y;
	x->parent = y->parent;
	if(y->parent == T->nil)
		T->root = x;
	else if(y == y->parent->right)
		y->parent->right = x;
	else 
		y->parent->left = x;
	x->right = y;
	y->parent = x;
}

void rbInsertFixup(t* T, node* z){
	node* y;
	while(z->parent->color == 'r'){
		if(z->parent == z->parent->parent->left){
			y = z->parent->parent->right;
			if(y->color == 'r'){
				z->parent->color = 'b';
				y->color = 'b';
				z->parent->parent->color = 'r';
				z = z->parent->parent;
			}
			else{
				if(z==z->parent->right){
					z = z->parent;
					leftRotate(T,z);
				}
				z->parent->color = 'b';
				z->parent->parent->color = 'r';
				rightRotate(T,z->parent->parent);
			}
		}
	else{
		y = z->parent->parent->left;
			if(y->color == 'r'){
				z->parent->color = 'b';
				y->color = 'b';
				z->parent->parent->color = 'r';
				z = z->parent->parent;
			}
			else{
				if(z==z->parent->left){
					z = z->parent;
					rightRotate(T,z);
				}
				z->parent->color = 'b';
				z->parent->parent->color = 'r';
				leftRotate(T,z->parent->parent);
			}
	}
	}
	T->root->color = 'b';
}

void rbInsert(t* T , node* z){
	node* y = T->nil;
	node* x = T->root;
	while(x!=T->nil){
		y = x;
		if(z->key < x->key)
			x = x->left;
		else
			x = x->right;
	}
	z->parent = y;
	if(y==T->nil)
		T->root = z;
	else if(z->key < y->key)
		y->left = z;
	else 
		y->right = z;
	z->left = T->nil;
	z->right = T->nil;
	z->color = 'r';
	rbInsertFixup(T,z);
}
//tree minimum
node* treeMinimum(node* root){
	node* aux;
	aux = root;
	while(aux->left != NULL)
		aux = aux->left;
	return aux;
}
//----------------------------------------------------------------

void inOrden(node* root){
	if(root!=NIL){
		inOrden(root->left);
		cout << root->key <<root->color<< " ";
		inOrden(root->right);
	}
}


node* buscar(node* root,int key){
	node* fnode = NIL;
	if(root == NIL)
		return NIL;
	else if(root->key == key){
		fnode = root;
		return fnode;
	}
	else if(key<root->key)
		return buscar(root->left,key);
	else
		return buscar(root->right,key);
}

void rbTransplant(t* T,node* u,node* v){
	if(u->parent==T->nil)
		T->root = v;
	else if(u == u->parent->left)
		u->parent->left = v;
	else
		u->parent->right = v;
	v->parent = u->parent;
}

void rbDeleteFixup(t* T,node* x){
	node* w;
	while(x != T->root && x->color == 'b'){
		if(x == x->parent->left){
			w = x->parent->right;
			if(w->color == 'r'){
				w->color = 'b';
				x->parent->color = 'r';
				leftRotate(T,x->parent);
				w = x->parent->right;
			}
			if(w->left->color == 'b' && w->right->color == 'b'){
				w->color = 'r';
				x = x->parent;
			}
			else {
				if (w->right->color == 'b'){
					w->left->color = 'b';
					w->color = 'r';
					rightRotate(T,w);
					w = x->parent->right;
				}
				w->color = x->parent->color;
				x->parent->color = 'b';
				w->right->color = 'b';
				leftRotate(T,x->parent);
				x = T->root;
			}
		}

		else{
			 w= x->parent->left;
			if(w->color == 'r'){
				w->color = 'b';
				x->parent->color = 'r';
				rightRotate(T,x->parent);
				w = x->parent->left;
			}
			if(w->right->color == 'b' && w->left->color == 'b'){
				w->color = 'r';
				x = x->parent;
			}
			else {
				if (w->left->color == 'b'){
					w->right->color = 'b';
					w->color = 'r';
					leftRotate(T,w);
					w = x->parent->left;
				}
				w->color = x->parent->color;
				x->parent->color = 'b';
				w->left->color = 'b';
				rightRotate(T,x->parent);
				x = T->root;
			}

		}


	}
	x->color = 'b';

}


void rbDelete(t* T,node* z){
	node* y = z;
	char original = y->color;
	node* x;
	if(z->left == T->nil){
		x = z->right;
		rbTransplant(T,z,z->right);
	}
	else if (z->right == T->nil){
		x= z->left;
		rbTransplant(T,z,z->left);		
	}
	else{
		y = treeMinimum(z->right);
		original = y->color;
		x = y->right;
		if(y->parent==z)
			x->parent = y;
		else{
			rbTransplant(T,y,y->right);
			y->right = z->right;
			y->right->parent = y;
		}
		rbTransplant(T,z,y);
		y->left = z->left;
		y->left->parent = y;
		y->color = z->color;
	}
	if(original == 'b')
		rbDeleteFixup(T,x);

}
//----------------Codigo para imprimir arbol--------------------------------------//
//nodo de lista
struct Node {
	Node *next;
	Node *prev;
	int value;
	char color;
	int level;
};
//Estructura de lista
struct List {
 	int count;
	Node *first;
	Node *last;
};
//crear lista
List *List_create(){
	List* list;
	list = new List;
	list->first=NULL;
	list->last=NULL;
	list->count = 0;
    return list;
}	
//push en la lista
void insertaF(List *list, int value,char color){
    Node *node = new Node;
    node->next=NULL;
    node->prev=NULL;
    node->value = value;
    node->color = color;
    if(list->last == NULL){
        list->first = node;
        list->last = node;
    } 
    else {
        list->last->next = node;
        node->prev = list->last;
        list->last = node;
    }
    list->count++;
    return;
}
//algo auxiliar
void Print_list(List *list){
	 if(list->first == NULL && list->last == NULL){
    	cout << "La lista esta vacia" << endl;
    	return;
    } 
    Node *p;
    p = list->first;
    while(p != NULL){
    	cout <<p->level<<" -> ";
    	p = p->next;
    } 
    cout <<"NIL"<<endl;      
    return;
}
//eliminaf
void eliminaF(List* list){
	/*cuando hay 1 elemento*/
	if(list->first == list->last){
		list->first=NULL;
		list->last=NULL;
		return;
	}
	Node* p;
	p = list->last;
	list->last = list->last->prev;
	p->prev=NULL;
	list->last->next=NULL;
	p=NULL;
	delete p;
}
// para imprimir espacios
void espacios(int n){
	for(int i=0;i<n;i++ )
		cout << " ";
}

//Funcion que imprimira el arbol****
void print(t* T){
	int e1,e2;
	int rkey,lkey;
	node* aux;
	node* lnode,rnode;
	List* list;
	
	list=List_create();
	
	if(T->root != NIL)
		insertaF(list,T->root->key,T->root->color);
	
	Node* p = list->first;

	while(p!=NULL){
		aux = buscar(T->root,p->value);
		if(aux != NIL){
			if(aux->left==NIL)
				insertaF(list,-1,'b');
			else
				insertaF(list,aux->left->key,aux->left->color);
			if(aux->right==NIL)
				insertaF(list,-1,'b');
			else
				insertaF(list,aux->right->key,aux->right->color);
		}
		p = p->next;
	}

	p = list->last;
	//corregir lista
	while(p->value == -1 ){
		eliminaF(list);
		p=list->last;
	}
	p=list->first;
	int lvl = 0;
	while(p!=NULL){
		for(int i = 1;i<=power(2,lvl) && p != NULL ;i++){
			p->level = lvl;
			p = p->next;
		}
		lvl++;
	}
	
	p = list->first;
	e1 = 0;
	e2 = 0;
	while(p!=NULL){
		espacios(power(2,lvl)-2);
		for(int i= 1;i<=power(2,e1)&& p!= NULL;i++){
			if(p->value!=-1){
				cout << p->value;
				cout << p->color;
				espacios(power(2,lvl+1)-1);
			}
			else{
				cout <<"  ";
				espacios(power(2,lvl+1)-1);
			}
				
			
			p=p->next;
		}
		cout << endl;
		e1++;
		lvl--;
	}
	
	Print_list(list);
	cout << "Elementos: " << list->count << endl;
}

//-----------------------------Codigo para imprimir el arbol----------------------------------------------//
void TreePrint(t* T, node* x, int k){
	int i;
	if(x!=NIL){
		TreePrint(T,x->right,k+1);
		for(i=1;i<=k;i++)
			printf("   ");
			printf("%3d",x->key);
			if(x->color=='r')
			printf("(R)\n");
			else printf("(B)\n");	
		
		TreePrint(T,x->left,k+1);
	}
	else{

		for(i=1;i<=k;i++)
			printf("    ");
			if(x->color=='b')
			printf("NIL(B)\n");	
		
	}
}
int main(){
	
	int opcion;
	int input;
	node* aux;
	
	t* T = new t;
	T->nil = NIL;
	T->root = NIL;
	
	
	
	do{
		cout << "Red Black Tree :v" << endl;
		cout << "---------------------------------";
		cout << "Elegir una opcion"<< endl;
		cout << "1-->Insertar Elemento" << endl;
		cout << "2-->Imprimir Arbol" << endl;
		cout << "3-->Mostrar un Nodo" << endl;
		cout << "4-->Eliminar un Nodo" << endl;
		cout << "-->Salir" << endl;
		cout << "Opcion ---> ";
		cin >> opcion;
		switch(opcion){
			case 1:
				cout << "Key---> ";
				cin >> input;
				aux = newNode(input);
				rbInsert(T,aux);
				break;
			case 2:
				print(T);
				cout << endl;
				break;
			case 3:
				cout <<"Valor del nodo"<< endl;
				cin >> input;
				aux=buscar(T->root,input);
				if(aux!=NIL){
					cout << "EL nodo contiene: " << aux->key << endl;
					cout << "Color del nodo: " << aux->color << endl;
				}
				else
					cout << "Nodo no encontrado again plz" << endl;
				break;
			case 4:
				cout <<"Valor del nodo " << endl;
				cin >> input;
				aux = buscar(T->root,input);
				rbDelete(T,aux);
				break;
			case 5:
				break;
			default:
				cout <<"Opcion Incorrecta"<<endl;
				
		}
	}while(opcion!=5);
	
	//TreePrint(T,T->root,0);

	//print(T);
}
