#!/usr/bin/python
from auxFuncSLE import *

# ------------------------------------------------------------
# 1.2 METODO DE CROUT L1U
# usar de ejemplo: A=[[10,10,20],[20,25,40],[30,50,61]]
# A = L1U, donde L1 (tiene la diagonal de 1s)
def croutL1U(A, piv=0):
  n = len(A)
  U = [[0.0]*n for j in range(n)];
  L = [[float(i == j) for j in range(n)] for i in range(n)]
  P = [[float(i == j) for j in range(n)] for i in range(n)]
  Q = [[float(i == j) for j in range(n)] for i in range(n)]
  k=0
  #pivot
  if piv:
    for j in range(len(A)):
      if piv !=2:
        A, P, Q = pivot(A, P, Q, j, piv)
      else:
        k = k+1
        if k==1:
          s = escalPortion(A)
        A, P, Q = pivot(A, P, Q, j,s, piv)
  for k in range(n):
    for i in range(k, n):
      U[k][i] = A[k][i] - sum(L[k][p]*U[p][i] for p in range(k))
    for i in range(k+1, n):
      if U[k][k] == 0:
        exit('Debe usarse pivoteo parcial')
      L[i][k] = (A[i][k] - sum(L[i][p]*U[p][k] for p in range(k))) / float(U[k][k])
  if piv == 3:
    return P, Q, L, U
  return P, L, U

# ------------------------------------------------------------
