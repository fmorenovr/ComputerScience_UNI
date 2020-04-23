#!/usr/bin/env python
from math import *
from auxFuncEigen import *

# -----------------------------------------------------
# 1.3 METODO SIMMETRYC-POWER
# A = [[-4,14,0],[-5,13,0],[-1,0,2]]
# x0 = [1,1,1]
def symmetricPower(A,x0,printText=1,tol=1.0e-6,nmaxiter=100):
  n = len(A)
  I = [[float(i==j) for i in range(n)] for j in range(n)]
  xnorm = eucliNorm(x0)
  x = [ i/xnorm for i in x0 ]
  for j in range(nmaxiter):
    y = multiMatrixVector(A,x)
    mu = transProdVec(x,y)
    ynorm = eucliNorm(y)
    if ynorm == 0:
      print 'A tiene eigenvalor 0'
      return 0, x
    xy = [ x[i] - y[i]/ynorm for i in range(len(x)) ]
    error = eucliNorm(xy)
    x = [ i/ynorm for i in y]
    if error < tol:
      return mu,x
  print 'Inverse power method no converge'
  return None,None

# -----------------------------------------------------
