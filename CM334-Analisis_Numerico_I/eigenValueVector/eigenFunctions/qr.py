#!/usr/bin/env python
from math import *
from auxFuncEigen import *
from jacobi import *

# -----------------------------------------------------
# 1.7 METODO QR
# probar A = [[ 30,  -5, -10,   0,   0,   0,   0],[ -5,  10,  -5,   0,   0,   0,   0],[-10,  -5,  30,  -5, -10,   0,   0],[  0,   0,  -5,  10,  -5,   0,   0], [  0,   0, -10,  -5,  30,  -5, -10],[  0,   0,   0,   0,  -5,  10,  -5],[  0,   0,   0,   0, -10,  -5,  15]]
def qrEigen(M,tol = 1.e-6,maxiter = 100):
  n = len(M)
  A = [row[:] for row in M]
  I = [[float(i==j) for i in range(n)] for j in range(n)]
  itera = 0
  while (norm1Matrix(tridiagLower(A,-1)) > tol*norm1Matrix(A)) and itera<maxiter:
    A22 = [[ A[i][j] for i in range(n-2,n)]for j in range(n-2,n)]
    sc , dummy = jacobiEigen(A22)
    _ , k = minIndexElem(sc,A[n-1][n-1])
    shift = sc[k]
    Is = prodMatrix(I,shift)
    AIs = matrixSus(A,Is)
    Q,R = householder(AIs)
    AQ = matrixMulti(A,Q)
    Qt = transMatrix(Q)
    A = matrixMulti(Qt,AQ)
    itera +=1
  d = [A[i][i] for i in range(n)]
  return d

# -----------------------------------------------------
