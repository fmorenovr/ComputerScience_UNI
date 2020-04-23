#!/usr/bin/python
from auxFuncSLE import *

# ------------------------------------------------------------
# 1.2 METODO GAUSS-JORDAN
# usar de ejemplo: A=[[1e-10, 10000000.1],[20000000000.0, 5.0]]
# b=[10000000.1,20000000005.0]
def gaussJordan(A, b, piv=0):
  a = augmentedMatrixVector(A, b)
  n_rows = len(a)
  n_cols = len(a[0])
  P = [[float(i == j) for j in range(n_rows)] for i in range(n_rows)]
  Q = [[float(i == j) for j in range(n_rows)] for i in range(n_rows)]
  k = 0
  for j in range(n_cols): #0, 1, 2, 3, 4
    r = [0]*n_rows
    for i in range(j+1, n_rows+1):
      #pivoteo
      if piv !=2:
        a, P, Q = pivot(a, P, Q, j, piv)
      else:
        k = k+1
        if k==1:
          s = escalPortion(a)
        a, P, Q = pivot(a, P, Q, j,s, piv)
      if i == j+1:
      #Eliminacion de gauss
        for m in range(j):
          r[m] = a[m][j] / float(a[j][j])
        for l in range(j):
          for k in range(j, n_cols):
            if l < n_rows:
              a[l][k] = a[l][k] - r[l]*a[j][k]
      if i < n_rows:
        r[i] = a[i][j] / float(a[j][j])
        for k in range(j, n_cols):
          a[i][k] = a[i][k] - r[i]*a[j][k]
    if j < n_rows:
      temp = [0]*n_rows
      #if (temp != r):
        #print 'T%d' % (j+1)
        #printMatrix(T(n_rows, r, j))
  #para convertir la diagonal en 1's.
  for i in range(n_rows):
    temp = float(a[i][i])
    for j in range(n_cols):
      a[i][j] = a[i][j] / temp
  print 'A|b:'
  printMatrix(a)
  if piv == 3:
    return multiMatrixVector(Q, backSustitution(a))
  return backSustitution(a)

# ------------------------------------------------------------
# Calculo de las matrices Ti del metodo de Gauss-Jordan o de cualquier metodo
def T(n, ri, c):
#		ri: a[i][c] / a[c][c]
#		c : columna c-esima 
  T = [[float(i == j) for j in range(n)] for i in range(n)]
  for k in range(n):
    T[k][c] = -ri[k]
  return T

# ------------------------------------------------------------
