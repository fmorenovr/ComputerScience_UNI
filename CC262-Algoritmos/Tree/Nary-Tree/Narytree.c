/*

        implement N-ary Tree

*/
#include <stdio.h>
#include <stdlib.h>
#define MARKER ')'
#define N 5
 
// A node of N-ary tree
struct Node {
   char key;
   struct Node *parent; // apunta a su padre
   struct Node *child[N];  // An array of pointers for N children
};

typedef struct Node node;
typedef struct Node *Nodeary;
typedef struct Node *NaryTree;

// A utility function to create a new N-ary tree node
Nodeary newNode(char key)
{
  Nodeary temp = (Nodeary)malloc(sizeof(node));
  temp->key = key;
  int i;
  for (i = 0; i < N; i++)
    temp->child[i] = NULL;
  return temp;
}
 
// This function stores the given N-ary tree in a file pointed by fp
void serialize(NaryTree root, FILE *fp)
{
  int i;
  // Base case
  if (root == NULL) return;

  // Else, store current node and recur for its children
  fprintf(fp, "%c ", root->key);
  for (i = 0; i < N && root->child[i]; i++)
    serialize(root->child[i],  fp);

  // Store marker at the end of children
  fprintf(fp, "%c ", MARKER);
}
 
// This function constructs N-ary tree from a file pointed by 'fp'.
// This functionr returns 0 to indicate that the next item is a valid
// tree key. Else returns 0
int deSerialize(NaryTree root, FILE *fp)
{
  // Read next item from file. If theere are no more items or next
  // item is marker, then return 1 to indicate same
  int i;
  char val;
  if ( !fscanf(fp, "%c ", &val) || val == MARKER )
    return 1;

  // Else create node with this item and recur for children
  root = newNode(val);
  for (i = 0; i < N; i++)
    if (deSerialize(root->child[i], fp))
      break;

  // Finally return 0 for successful finish
  return 0;
}
 
// A utility function to create a dummy tree shown in above diagram
NaryTree createTree()
{
  NaryTree root = newNode('A');
  root->child[0] = newNode('B');
  root->child[1] = newNode('C');
  root->child[2] = newNode('D');

  root->child[0]->child[0] = newNode('E');
  root->child[0]->child[1] = newNode('F');

  root->child[2]->child[0] = newNode('G');
  root->child[2]->child[1] = newNode('H');
  root->child[2]->child[2] = newNode('I');
  root->child[2]->child[3] = newNode('J');

  root->child[0]->child[1]->child[0] = newNode('K');
  return root;
}
 
 
void Insert_nary(NaryTree *root,char key,Nodeary parent){}
// A utlity function to traverse the constructed N-ary tree
void naryPreorder(NaryTree root)
{
  if (root)
  {
    int i;
    printf("%c ", root->key);
    for (i = 0; i < N; i++)
      naryPreorder(root->child[i]);
  }
}

void naryInorder(NaryTree root)
{
  if (root)
  {
    int i;
    for (i = 0; i < N; i++)
    {
      printf("%c ", root->key);
      naryPreorder(root->child[i]);
      printf("\n");
    }
  }
}

// Driver program to test above functions
int main()
{
  // Let us create an N-ary tree shown in above diagram
  NaryTree root = createTree();

  // Let us open a file and serialize the tree into the file
  FILE *fp = fopen("tree.txt", "w");
  if (fp == NULL)
  {
    puts("Could not open file");
    return 0;
  }
  serialize(root, fp);
  fclose(fp);
 
  // Let us deserialize the storeed tree into root1
  NaryTree root1 = NULL;
  fp = fopen("tree.txt", "r");
  deSerialize(root1, fp);
 
  printf("Constructed N-Ary Tree from file is \n");
  naryPreorder(root1);
  printf("\n");
  naryInorder(root1);
  printf("\n");
  return 0;
}
