/*
########################################################
###       @Copyright Moreno Vera, Felipe Adrian      ###
###        Graph implementation                      ###
########################################################
*/

/*

  Graph funcionts pfor a set of point nulls

*/

#ifndef __GRAPH__H
  #define __GRAPH__H

typedef struct {
  int numEdges, numVertices;
  int **edges, **adj;
} Graph;

// Reserva memoria para la matriz de aristas
extern int** createEdgesMatrix(int);

// Reserva memoria para la matriz de adjacencia
extern int** createAdjMatrix(int);

// imprime las direcciones de memoria de la matriz de adjacencia
extern void printAdjMatrixPointers(int**,int);

// imprime las direcciones de memoria de la matrix de aristas
extern void printEdgesMatrixPointers(int**,int);

// imprime la matriz de adjacencia
extern void printAdjMatrix(int**,int);

// imprime la matrix de aristas
extern void printEdgesMatrix(int**,int);

// crea la matriz de adjacencia de un grafo
extern void createGraph(int**,int**,int,int);

// Crea la matriz de adjacencia de un grafo dirigido
extern void createDirectedGraph(int**,int**,int,int);

// algoritmo de arbol generador minimo
extern void prim(int**,int,int);

// distancias minimo de un vertice a otro
extern void floydWarshall(int**,int);

// Camino mas corto de grafos dirigidos
// con pesos negativos
extern void bellmanFord(int**,int);

// Camino mas corto de grafos dirigidos
// con pesos NO negativos
extern void dijkstra();

// funcion Main de grafos
extern int mainGraph(int**,int**,int,int);

#endif
