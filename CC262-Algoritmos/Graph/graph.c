/*
########################################################
###       @Copyright Moreno Vera, Felipe Adrian      ###
###        Graph implementation                      ###
########################################################
*/

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include "graph.h"

int** createAdjMatrix(int numvertices){
  int i;
  int** adjaux;
  // Reservamos memoria para la matriz de adjacencia
  adjaux = (int **) malloc(sizeof(int *)*numvertices);
  //adjaux[0] = (int *)malloc(sizeof(int)*numvertices);
  for(i = 0; i < numvertices; i++){
    //adjaux[i] = &adjaux[0][numvertices*i];
    adjaux[i] = (int *) malloc(sizeof(int)*numvertices);
  }
  return adjaux;
}

void printAdjMatrixPointers(int**adjaux,int numvertices){
  int i, j;
  printf("\n**** Pointers Matriz de adjacencia\n");
  for(i = 0; i < numvertices; i++){
    for(j = 0; j < numvertices; j++){
      printf("%p ",&adjaux[i][j]);
    }
    printf("\n");
  }
}

void printAdjMatrix(int**adjaux, int numvertices){
  int i, j;
  printf("\n**** Matriz de adjacencia\n");
  for(i = 0; i < numvertices; i++){
    for(j = 0; j < numvertices; j++){
      printf("%d ",adjaux[i][j]);
    }
    printf("\n");
  }
}

int** createEdgesMatrix(int numedges){
  int i;
  int** edgesaux;
  // aristas
  edgesaux = (int **)malloc(sizeof(int*)*numedges);
  //edgesaux[0] = (int *)malloc(sizeof(int)*3);
  for(i = 0; i < numedges; i++){
    //edgesaux[i] = &edgesaux[0][numedges*i];
    edgesaux[i] = (int *) malloc(sizeof(int)*3);
  }
  return edgesaux;
}

void printEdgesMatrixPointers(int**edgesaux, int numedges){
  int i;
  printf("\n**** Pointers Matriz de aristas\n");
  for( i=0;i<numedges;i++){
    printf("%p ",&edgesaux[i][0]);
    printf("%p ",&edgesaux[i][1]);
    printf("%p\n",&edgesaux[i][2]);
  }
  printf("\n");
}


void printEdgesMatrix(int**edgesaux, int numedges){
  int i;
  printf("\n**** Matriz de aristas\n");
  for( i=0;i<numedges;i++){
    printf("%d ",edgesaux[i][0]);
    printf("%d ",edgesaux[i][1]);
    printf("%d\n",edgesaux[i][2]);
  }
  printf("\n");
}

void createGraph(int**adjaux, int**edgesaux, int numvertices, int numedges){
  int i,j,k;    // contadores
  // Matriz de adjacencia
  // donde se considera INT_MAX camino infinito
  for(i = 0; i < numvertices; i++){
    for(j = 0; j < numvertices; j++){
      if(i == j)
        adjaux[i][j] = 0;
      else
        adjaux[i][j] = INT_MAX;
    }
  }
  // arista de vertice a vertice y con peso (grafo dirigido)
  if(numedges!=0) {
    printf("Ingrese las aristas y su peso (v1, v2, weight): \n");
    for(i = 0; i < numedges; i++){
      scanf("%d %d %d", &edgesaux[i][0], &edgesaux[i][1], &edgesaux[i][2]);
      adjaux[edgesaux[i][0]][edgesaux[i][1]] = edgesaux[i][2];
      adjaux[edgesaux[i][1]][edgesaux[i][0]] = edgesaux[i][2];
    }
  }
  // muestra la nueva matriz de adjacencia
  printAdjMatrix(adjaux,numvertices);
  printEdgesMatrix(edgesaux,numedges);
}

void createDirectedGraph(int**adjaux, int**edgesaux, int numvertices, int numedges){
  int i,j,k;    // contadores
  // Matriz de adjacencia
  // donde se considera INT_MAX camino infinito
  for(i = 0; i < numvertices; i++){
    for(j = 0; j < numvertices; j++){
      if(i == j)
        adjaux[i][j] = 0;
      else
        adjaux[i][j] = INT_MAX;
    }
  }
  
  int v1, v2, weight;
  //printAdjMatrixPointers(adjaux,numvertices);
  //printEdgesMatrixPointers(edgesaux,numedges);
  // arista de vertice a vertice y con peso (grafo dirigido)
  if(numedges>0){
    printf("Ingrese las aristas y su peso (v1, v2, weight): \n");
    for(i = 0; i < numedges; i++){
      scanf("%d %d %d", &v1, &v2, &weight);
      edgesaux[i][0] = v1;
      //edges[i][1] = v2;
      //edges[i][2] = weight;
      //adj[edges[i][0]][edges[i][1]] = edges[i][2];
      adjaux[v1][v2] = weight;
    }
  }
  // muestra la nueva matriz de adjacencia
  printAdjMatrix(adjaux,numvertices);
  printEdgesMatrix(edgesaux,numedges);
}

void prim(int**adjaux,int numvertices,int root){
  int i,j;
  int* key,    // Valores de cada nodo del arbol generado minimo
     * parent; // nodo padre de cada nodo del arbol generado minimo
  // valores de cada nodo del arbol generado, son los pesos
  key = (int *) malloc(sizeof(int)*numvertices);
  // padres, del arbol generado
  parent = (int *) malloc(sizeof(int)*numvertices);
  // construccion del arbol minimo generado
  // iniciados con pesos infinitos (INT_MAX)
  // y -1 indica padre es NULL o nil
  for(i = 0; i < numvertices; i++){
    key[i] = INT_MAX;
    parent[i] = -1;
  }
  key[root] = 0;
  //The queue should be a priority queue, however, for brevity,
  // Reserva memoria para el array de vertices que seran usados
  int *used = (int *) malloc(sizeof(int)*numvertices);
  int numUnused = numvertices;
  for(i = 0; i < numvertices; i++)
    used[i] = 0;
  int u = root;
  int closestIdx = root;    // indice del vertice mas cercano
  int closestVal = INT_MAX; // valor del vertice mas cercano

  while(numUnused > 0){
    closestVal = INT_MAX;
    // Encuentra la arista con menor peso
    for(i = 0; i < numvertices; i++){
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
    for(i = 0; i < numvertices; i++){
      if(used[i] == 0 && adjaux[u][i] > 0 && adjaux[u][i] < key[i]){
        parent[i] = u;
        key[i] = adjaux[u][i];
        printf("key[%d] is %d\n", i, adjaux[u][i]);
      }
    }
  }

  for(i = 0; i < numvertices; i++)
    printf("vertice: %d parent: %d\n", i, parent[i]);
}

void floydWarshall(int**adjaux,int numvertices){
  int i,j,k;
  for(k = 0; k < numvertices; k++){
    for(i = 0; i < numvertices; i++){
      for(j = 0; j < numvertices; j++){
        if(adjaux[i][j] > ( (adjaux[i][k] == INT_MAX || adjaux[k][j] == INT_MAX) ? INT_MAX : (adjaux[i][k] + adjaux[k][j]) ) ){
          adjaux[i][j] = adjaux[i][k] + adjaux[k][j];
        }
      }
    }
  }
  printf("\n\nNueva matriz de adjacencia con distancias minimas:\n\n");
  printAdjMatrix(adjaux,numvertices);
}

int mainGraph(int**adj,int**edges,int numVertices, int numEdges){
  if(numVertices == 0){
    printf("Numero de vertices 0\nGrafo Nulo\n");
    return 0;
  }else if(numVertices < 0){
    printf("Numero de vertices erroneo\n");
    return 0;
  }
  if(numEdges < 0){
    printf("Numero de aristas Incorrecto!!\n");
    return 0;
  }else if(numEdges == 0){
    printf("Numero de aristas 0\n");
    return 0;
  }
  adj = createAdjMatrix(numVertices);
  edges = createEdgesMatrix(numEdges);
  printAdjMatrixPointers(adj,numVertices);
  printEdgesMatrixPointers(edges,numEdges);
  createDirectedGraph(adj,edges,numVertices,numEdges);
  return 1;
}
