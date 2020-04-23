#!/usr/bin/python
from auxFuncSLE import *

# ------------------------------------------------------------
# 1.4 METODO DE CROUT TRIDIAGONAL
# descomposicion LU de una tridiagonal
# T = [[2,-1,0,0],[-1,2,-1,0],[0,-1,2,-1],[0,0,-1,2]]
def croutTridiag(M):
  A = [row[:] for row in M]
  n = len(A)
  L = [[ float(c==z) for c in range(n)] for z in range(n)]
  U = [[ float(c==z) for c in range(n)] for z in range(n)]
  L[0][0] = A[0][0]
  U[0][1] = 1.*A[0][1]/L[0][0]
  for i in range(1,n-1):
    L[i][i-1] = A[i][i-1]
    L[i][i] = A[i][i] - L[i][i-1]*U[i-1][i]
    U[i][i+1] = 1.*A[i][i+1]/L[i][i]
  L[n-1][n-2] = A[n-1][n-2]
  L[n-1][n-1] = A[n-1][n-1] - L[n-1][n-2]*U[i-1][i]
  return L,U

# ------------------------------------------------------------
# Soluciona el sistema Crout tridiagonal
# b = [1,0,0,1]
def solCroutTridiag(L,U,b):
  n = len(b)
  z = [0.]*n
  x = [0.]*n
  # resolvemos Lz = b
  z[0] = 1.*b[0]/L[0][0]
  for i in range(1,n):
    z[i] = 1.*(b[i] - L[i][i-1]*z[i-1])/L[i][i]
  print z
  # resolvemos Ux = z
  x[n-1] = z[n-1]
  for i in range(n-2,-1,-1):
    x[i] = z[i] - U[i][i+1]*x[i+1]
  return x

# ------------------------------------------------------------
