#!/usr/bin/env python
from math import *
from auxFuncEigen import *

# -----------------------------------------------------
# 1.6 METODO GERSCHGORIN-STURM
# Retorna los N mas pequenos autovalores de una matriz A
# si N es mayor del numero natural de autovalores de A
# repetira el mayor valor, para MAtrices tridiagonales simetricas
# A = [[4,-2,0],[-2,4,-2],[0,-2,5]]
def gerschgorinSturmEigen(T,N,printText = 1):
  n = len(T)
  A = [row[:] for row in T]
  # diagonal superior
  c = [float(A[i][i+1]) for i in range(n-1)]
  # diagonal
  d = [float(A[i][i]) for i in range (n)]
  if printText:
    print "\nEvaluaciones de los polinomios de Sturm"
  def f(x):
    p = sturmSeq(d,c,x)
    if printText:
      print (p)
    return p[len(p)-1]
  lam = [0.]*N
  r = lamRange(d,c,N)
  for i in range(N):
    lam[i] = brent(f,r[i],r[i+1],printText = 0)
  return lam

# -----------------------------------------------------
