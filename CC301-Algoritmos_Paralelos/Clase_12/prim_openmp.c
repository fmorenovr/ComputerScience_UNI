#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <omp.h>

void prim()
{
  int numVertices; // numero de vertices del grafo
  int numEdges;   // numero de aristas del grafo
  int root = 0;   // vertice inicial
  int i,j,k;    // contadores
  int* key,* parent;
  int** adj,**edges;
  printf("Ingrese numero de vertices: ");
  scanf("%d", &numVertices);
  printf("Ingrese numero de aristas: ");
  scanf("%d", &numEdges);
  // valores de cada nodo del arbol generado, son los pesos
  key = (int *) malloc(sizeof(int)*numVertices);
  // padres, del arbol generado
  parent = (int *) malloc(sizeof(int)*numVertices);
  // aristas
  edges = (int **)malloc(sizeof(int*)*numEdges);
  // reservamos memoria para los caminos
  for(i = 0; i < numEdges; i++)
    edges[i] = (int *) malloc(sizeof(int)*3);
  // Reservamos memoria para la matriz de adjacencia
  adj = (int **) malloc(sizeof(int *)*numVertices);
  for(i = 0; i < numVertices; i++)
    adj[i] = (int *) malloc(sizeof(int)*numVertices);
  // Matriz de adjacencia
  // donde se considera INT_MAX camino infinito
  for(i = 0; i < numVertices; i++){
    for(j = 0; j < numVertices; j++){
      if(i == j)
        adj[i][j] = 0;
      else
        adj[i][j] = INT_MAX;
    }
  }
  // arista de vertice a vertice y con peso (grafo dirigido)
  printf("Ingrese las aristas y su peso (v1, v2, weight): \n");
  for(i = 0; i < numEdges; i++)
  {
    scanf("%d %d %d", &edges[i][0], &edges[i][1], &edges[i][2]);
    adj[edges[i][0]][edges[i][1]] = edges[i][2];
    adj[edges[i][1]][edges[i][0]] = edges[i][2];
  }  
  // muestra la nueva matriz de adjacencia
  for(i = 0; i < numVertices; i++){
    for(j = 0; j < numVertices; j++){
      printf("%d ",adj[i][j]);
    }
    printf("\n");
  }
  // construccion del arbol minimo generado
  // iniciados con pesos infinitos (INT_MAX)
  // y -1 indica padre es NULL o nil
  #pragma parallel for
  for(i = 0; i < numVertices; i++){
      key[i] = INT_MAX;
      parent[i] = -1;
  }

  key[root] = 0;
  // Reserva memoria para el array de vertices que seran usados
  int * used = (int *) malloc(sizeof(int)*numVertices);
  int numUnused = numVertices;
  for(i = 0; i < numVertices; i++)
    used[i] = 0;

  int u = root;
  int closestIdx = root;    // indice del vertice mas cercano
  int closestVal = INT_MAX; // valor del vertice mas cercano

  while(numUnused > 0){
    closestVal = INT_MAX;
    // Encuentra la arista con menor peso
    #pragma parallel for
    for(i = 0; i < numVertices; i++){
      if(used[i] == 0 && key[i] < closestVal){
        closestIdx = i;
        closestVal = key[i];
      }
    }

    printf("vertice visitado actual es %d\n", u);
    u = closestIdx;
    // marca como visitado
    used[u] = 1;
    // decrementa el numero de vertices
    numUnused--;
    // para cada vertice i adjacente al vertice u
    #pragma parallel for
    for(i = 0; i < numVertices; i++){
      if(used[i] == 0 && adj[u][i] > 0 && adj[u][i] < key[i]){
        parent[i] = u;
        key[i] = adj[u][i];
        printf("key[%d] is %d\n", i, adj[u][i]);
      }
    }
  }
  #pragma parallel for
  for(i = 0; i < numVertices; i++)
    printf("vertice: %d parent: %d\n", i, parent[i]);
}

int main(int argc, char* argv){
  prim();
  return 0;
}

/*

probar
7
11
0 1 7
0 3 5
1 2 8
1 3 9
1 4 7
2 4 5
3 4 15
3 5 6
4 5 8
4 6 9
5 6 11
*/
