#!/usr/bin/python
from auxFuncSLE import *
from croutLU1 import *

# ------------------------------------------------------------
# 1.4 METODO LDMt
# usar de ejemplo: A=[[1,-4,1,1],[1,0,1,3],[-2,0,-1,0],[0,0,1,0]]
# A = LDM, similar a LU1 de crout, donde U = DM
def LDMt(A, piv=0):
  if piv == 3:
    P, Q, L, U = croutLU1(A, piv)
  else:
    P, L, U = croutLU1(A, piv)
  D, M = diagLDMt(L)
  if piv == 3:
    return P, Q, L, D, M
  else:
    return P, L, D, M

# ------------------------------------------------------------
# Calcula la matrix diagonal D del metodo LDMt
def diagLDMt(U):
  n = len(U)
  D = [[float(i == j) for j in range(n)] for i in range(n)]
  for i in range(n):
    D[i][i] = float(U[i][i])
  for i in range(n):
    for j in range(n):
      U[i][j] /= (D[i][i])
  return D, U

# ------------------------------------------------------------
