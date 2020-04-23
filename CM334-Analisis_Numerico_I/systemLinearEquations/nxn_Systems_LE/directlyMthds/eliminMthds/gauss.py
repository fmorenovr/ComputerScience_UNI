#!/usr/bin/python
from auxFuncSLE import *

# ------------------------------------------------------------
# 1.1 METODO DE GAUSS
# usar de ejemplo: A=[[1e-10, 10000000.1],[20000000000.0, 5.0]]
# b=[10000000.1,20000000005.0]
def gauss(A, b, piv=0):
  a = augmentedMatrixVector(A, b)
  n = len(A)
  # crea matrices identidad
  P = [[float(i == j) for j in range(n)] for i in range(n)]
  Q = [[float(i == j) for j in range(n)] for i in range(n)]
  k = 0
  for j in range(len(a[0])):
    r = [0]*n
    # pivoteo
    if j < n:
      if piv !=2:
        a, P, Q = pivot(a, P, Q, j, piv)
      else:
        k = k+1
        if k==1:
          s = escalPortion(a)
        a, P, Q = pivot(a, P, Q, j,s, piv)
      for i in range(j+1, n):
      #Eliminacion de gauss
        r[i] = a[i][j] / float(a[j][j])
        for k in range(j, len(a[0])):
          a[i][k] = a[i][k] - r[i]*a[j][k]
    if j < n:
      temp = [0]*n
      #if (temp != r):
        #print 'L%d' % (j+1)
        #printMatrix(L(n, r, j))
  print 'A|b:'
  printMatrix(a)
  if piv == 3:
    return multiMatrixVector(Q, backSustitution(a))	
  return backSustitution(a)

# ------------------------------------------------------------
# Calculo de las matrices Li del metodo de Gauss o de cualquier metodo
def L(n, ri, c):
  # ri: a[i][c] / a[c][c]
  # c : columna c-esima 
	# Matriz identidad
  L = [[float(i == j) for j in range(n)] for i in range(n)]
  for k in range(c+1, n):
    L[k][c] = -ri[k] # ri = M[k][c]/M[c][c]
  return L

# ------------------------------------------------------------
