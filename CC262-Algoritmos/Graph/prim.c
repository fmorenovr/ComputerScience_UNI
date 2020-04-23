#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include "graph.h"

int main(int argc, char* argv){
  int** adj,  // matriz de adjacencia
    ** edges;  // matriz de caminos y/o aristas
  int numVertices; // numero de vertices del grafo
  int numEdges;   // numero de aristas del grafo
  int i;
  printf("Ingrese numero de vertices: ");
  scanf("%d",&numVertices);
  printf("Ingrese numero de aristas: ");
  scanf("%d", &numEdges);
  
  if(numVertices == 0){
    printf("Numero de vertices 0\nGrafo Nulo\n");
    return 1;
  }else if(numVertices < 0){
    printf("Numero de vertices erroneo\n");
    return -1;
  }
  if(numEdges < 0){
    printf("Numero de aristas Incorrecto!!\n");
    return -1;
  }else if(numEdges == 0){
    printf("Numero de aristas 0\n");
  }
  adj = createAdjMatrix(numVertices);
  edges = createEdgesMatrix(numEdges);
  createDirectedGraph(adj,edges,numVertices,numEdges);
  prim(adj,numVertices,0);
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
