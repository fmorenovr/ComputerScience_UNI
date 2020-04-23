#!/usr/bin/env python
from math import *

# -------------------------------------------------------
# Construye la matriz :
# xk+1 = xk - Dk-1.F(xk)
# Aproxima los elementos de su diagonal principal
# Dkk = Jkk
def newtonJacobiMatrix(F,x):
  jac = jacobianMatrix(F,x)
  r = len(jac)
  d = [[ 0.0 for i in range(r)] for j in range(r)]
  for k in range(r):
    d[k][k] = jac[k][k]
  return d

# -------------------------------------------------------
# Construye la matriz :
# xk+1 = xk - Lk-1.F(xk)
# Aproxima los elementos por la matriz triangular inferior
# incluido la diagonal
# Lij = Jij, i>=j
def newtonGaussSeidelMatrix(F,x):
  jac = jacobianMatrix(F,x)
  r = len(jac)
  d = [[ 0.0 for i in range(r)] for j in range(r)]
  for k in range(r):
    for p in range(r):
      if k>=p:
        d[k][p] = jac[k][p]
  return d

# -------------------------------------------------------
# Construye la matriz :
# xk+1 = xk - (rho.Dk + Lk)-1.F(xk)
# donde w = 1/(rho+1.0)
def newtonSorMatrix(F,x0,w):
  rho = 1./w - 1.
  jac = jacobianMatrix(F,x0)
  r = len(jac)
  l = [[ 0.0 for i in range(r)] for j in range(r)]
  d = [[ 0.0 for i in range(r)] for j in range(r)]
  rDL = [[ 0.0 for i in range(r)] for j in range(r)]
  for k in range(r):
    for p in range(r):
      if k>=p:
        l[k][p] = jac[k][p]
  for k in range(r):
    d[k][k] = rho*jac[k][k]
  for k in range(r):
    for p in range(r):
      rDL[k][p] = d[k][p] + l[k][p]
  return rDL

# -------------------------------------------------------
# derivada parcial de la funcion index, en la dimension Vect
def d1fPartial(g,x0,indexFunc,indexVect,h=1e-6):
  x1 = [i for i in x0]
  x1[indexVect] = x1[indexVect] + h
  gx1 = g(x1)[indexFunc]
  gx0 = g(x0)[indexFunc]
  dfgPartial = (gx1 - gx0)/h
  return dfgPartial

# -------------------------------------------------------
# calcula las secantes en cada funcion
def secantPartial(F,x0,x1,indexFunc,indexVect,h=1.0e-6):
  h = x1[indexVect] - x0[indexVect]
  fx1 = F(x1)[indexFunc]
  fx0 = F(x0)[indexFunc]
  secantPar = (fx1 - fx0)/h
  return secantPar

# -------------------------------------------------------
# Evalua si una derivada parcial en alguna funcion es >1
# para ver si converge o diverge del punto fijo
def evalPartialDif(F,x0):
  correct = True
  punto = -1
  n=len(x0) # dimension del rango que es igual al dominio x0
  for i in range(n): # evalua todas las funciones
    for j in range(n): #  evalua todos las dinemsniones de vector
      if j!=i:
        try:  dfPg = d1fPartial(F,x0,i,j)
        except FloatingPointError:
          correct = False
        if not correct or abs(dfPg) >=1:
          punto = i
          return correct,punto
  return correct,punto

# -------------------------------------------------------
# Matriz jacobiana de una funcion F:R^n ---> R^n
def jacobianMatrix(F,x0):
  n = len(x0)
  J = [[ 0.0 for i in range(n)] for j in range(n)]
  for i in range(n):
    for j in range(n):
      J[i][j] = d1fPartial(F,x0,i,j)
  return J

# -------------------------------------------------------
# inversa de una matrix
def invMatrix(D):
  n = len(D)
  A = [row[:] for row in D]
  B = [[float(i == j) for j in range(n)] for i in range(n)]
  C = [[0.0]*n for i in range(n)]
  # transformacion de la matriz y de los terminos independientes
  for k in range(n-1):
    for i in range(k+1,n):
      # terminos independientes
      for s in range(n):
        B[i][s] -= A[i][k]*B[k][s]/A[k][k]
      # elementos de la matriz
      for j in range(k+1,n):
        A[i][j] -= A[i][k]*A[k][j]/A[k][k]
  # calculo de las incognitas, elementos de la matriz inversa
  for s in range(n):
    C[n-1][s] = B[n-1][s]/A[n-1][n-1]
    for i in range(n-2,-1,-1):
      C[i][s] = B[i][s]/A[i][i]
      for k in range(n-1,i,-1):
        C[i][s] -= A[i][k]*C[k][s]/A[i][i]
  return C

# -------------------------------------------------------
# multiplicacion matrix vector
def multiMatrixVector(A,x):
  c=[]
  col = len(x) # numero filas de b y numero de columnas de A
  row = len(A) # numero de filas de A
  if col!=len(A[0]):
    exit('No tiene longuitudes igual')
  for i in range(row):
    suma=0.
    for j in range(col):
      suma += A[i][j]*x[j]
    c.append(suma)
  return c

# ------------------------------------------------------------
# norma euclidiana o de fobrenius del vector x, ie, ||x||2
def eucliNorm(x):
  return sqrt(sum([x_i*x_i for x_i in x]))

# ------------------------------------------------------------
# multiplicacion vector matrix
def multiVectorMatrix(A,x):
  c=[]
  col = len(x) # numero filas de b y numero de columnas de A
  row = len(A[0]) # numero de columnas de A
  if col!=len(A):
    exit('No tiene longuitudes igual')
  for i in range(row):
    suma=0.
    for j in range(col):
      suma += A[j][i]*x[j]
    c.append(suma)
  return c

# ------------------------------------------------------------
# Resta de matrices
def matrixSus(A,B):
  n = len(A)
  m = len(A[0])
  C = [[0. for row in range(n)] for col in range(m)]
  for i in range(n):
    for j in range(m):
      C[i][j] = A[i][j] - B[i][j]
  return C

# ------------------------------------------------------------
# en un sistema no lineal, sea F(x) = (f1,f2,..., fn)
# se define un G(x) = SUM( (fi)*(fi) ), desde i = 1, ..., n
# que en resumen seria G(x) = Ft(x).F(x)
def objetiveFunction(F,x0):
  n = len(x0)
  Fx0 = F(x0)
  Gx0 = sum([ Fx0[i]*Fx0[i] for i in range(n) ])
  return Gx0/2.

# -------------------------------------------------------
# gradiente de la funcion objetivo
def objFuncGradient(F,x0):
  J = jacobianMatrix(F,x0)
  Fx0 = F(x0)
  Jt = transMatrix(J)
  a_JtF = multiMatrixVector(Jt,Fx0)
  return a_JtF

# -------------------------------------------------------
# transpuesta de una matriz
# [M[i][j] for i in range(n)] imprime M[i][j] (j fijo), es decir, imprime A[0][j],A[1][j], ... y con el siguiente igual
# probar [M[i][1] for i in range(n)]
def transMatrix(M):
  n = len(M)
  m = len(M[0])
  return [[ M[i][j] for i in range(n)] for j in range(m)]

# ------------------------------------------------------------
