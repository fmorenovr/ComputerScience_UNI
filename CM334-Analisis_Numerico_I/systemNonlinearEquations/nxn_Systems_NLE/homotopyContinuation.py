#!/usr/bin/env python
from math import *
from auxFuncSNLE import *

# -------------------------------------------------------
# 1.8 METODO HOMOTOPIA - CONTINUACION
def homotopyContinuation(F,x0,a=1,b=0,printText=1,nInter=100):
  n = len(x0)
  x = x0[:]
  Fx = F(x)
  h = 1.*(a-b)/nInter
  b = [ -1.*h*Fx[i] for i in range(n)]
  for itera in range(nInter):
    # A = J(x)
    A = jacobianMatrix(F,x)
    # resolviendo el sistema A.k1 = b
    k1 = gauss(A,b)
    x1 = [ x[i] + 0.5*k1[i] for i in range(n) ]
    # A1 = J(x1)
    A1 = jacobianMatrix(F,x1)
    # resolviendo el sistema A1.k2 = b
    k2 = gauss(A1,b)
    x2 = [ x[i] + 0.5*k2[i] for i in range(n) ]
    # A2 = J(x2)
    A2 = jacobianMatrix(F,x2)
    # resolviendo el sistema A2.k3 = b
    k3 = gauss(A2,b)
    x3 = [ x[i] + k3[i] for i in range(n) ]
    # A3 = J(x3)
    A3 = jacobianMatrix(F,x3)
    # resolviendo el sistema A3.k4 = b
    k4 = gauss(A3,b)
    xaux = [ x[i] + 1./6*( k1[i] + 2.*k2[i] + 2*k3[i] + k4[i] ) for i in range(n) ]
    if printText:
      print "x=%s"%x
      print "F(x) = %s"%F(x)
    x = xaux[:]
  return x

# -------------------------------------------------------
# funcion de gauss
def gauss(A, b):
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
      a, P, Q = pivot(a, P, Q, j)
      for i in range(j+1, n):
      #Eliminacion de gauss
        r[i] = a[i][j] / float(a[j][j])
        for k in range(j, len(a[0])):
          a[i][k] = a[i][k] - r[i]*a[j][k]
    if j < n:
      temp = [0]*n
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
# Se usa para resolver la matriz superior generada por gauss y gauss-Jordan
def backSustitution(a):
  n = len(a)
  x = [0]*n
  for j in range(n-1, -1, -1):
    x[j] = (a[j][n] - sum(a[j][k]*x[k] for k in range(j+1, n)))/float(a[j][j])
  return x

# ------------------------------------------------------------
# Privote de cualquier metodo
def pivot(a, P, Q, colum):
  n = len(a)
  temp = a[colum][colum]
  if(temp == 0.0): # sin pivot
    row_maxColumn = maxColum(a, colum)
    a = pivotP(a, row_maxColumn, colum)
    P = exchangeRows(P, row_maxColumn, colum)
  return 	a, P, Q

# ------------------------------------------------------------
# Privoteo Parcial
# Permuta la fila r1 con la fila r2 de la matriz M
def pivotP(M, r1, r2):
  return exchangeRows(M, r1, r2)

# ------------------------------------------------------------
# intercambia las filas r1 y r2 de M
def exchangeRows(A, r1, r2):
  M = [row[:] for row in A]
  M[r1], M[r2] = M[r2], M[r1]
  return M

# ------------------------------------------------------------
# Aumenta una matriz un vector
# Retorna la matriz aumentada
def augmentedMatrixVector(M, b):
  A = [row[:] for row in M]
  for i in range(len(M)):
    A[i].append(b[i])
  return A

# ------------------------------------------------------------
