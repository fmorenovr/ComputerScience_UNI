#!/usr/bin/python
from auxFuncSLE import *

# ------------------------------------------------------------
# 1.1 METODO DE AASEN
# Usar de ejemplo: A=[[1,10,20],[10,1,30],[20,30,1]]
# PAPt = LTLt
def aasen(M):
  n = len(M)
  A = [row[:] for row in M]
  if not isSymmetricMatrix(A):
    exit('La matriz no es simetrica')
  H = [0]*n
  v = [0]*n
  L = [[0]*(k) +  [1] + [0]*(n-k-1) for k in range(n)]
  P = [[float(i == j) for j in range(n)] for i in range(n)]
  I = [[float(i == j) for j in range(n)] for i in range(n)]
  T = [[0]*n for i in range(n)]
  alpha = [0]*n
  beta = [0]*n
  for j in range(n):
    if j ==0:
      H[j] = A[j][j]
    else:
      H[j] = A[j][j]
      for k in range(1,j):
        H[k] = beta[k-1]*L[j][k-1] + alpha[k]*L[j][k]+beta[k]*L[j][k+1]
        H[j] = H[j] - L[j][k]*H[k]
    if j==0:
      alpha[j] = H[j]
    else:
      alpha[j] = H[j] - beta[j-1]*L[j][j-1]
    if j < n-1:
      for i in range(j+1,n):
        suma=0.
        for k in range(j+1):
          suma = suma - L[i][k]*H[k]
        v[i] = A[i][j] + suma
# Norma infinita de v
      maximum = 0
      iq = j
      for i in range(j+1, n):
        if math.fabs(v[i])>maximum:
          maximum = math.fabs(v[i])
          iq = i
      if iq>j:
        aux = v[j+1]
        v[j+1] = v[iq]
        v[iq] = aux
        for k in range(1,j):
          aux = L[j+1][k]
          L[j+1][k] = L[iq][k]
          L[iq][k] = aux
        A = exchangeRows(A,j+1,iq)
        A = exchangeCols(A,j+1,iq)
        Pn = exchangeRows(I,j+1,iq)
        P = matrixMulti(Pn,P)
      beta[j] = v[j+1]
    if j < n-2:
      for k in range(j+2,n):
        L[k][j+1] = v[k]
      if v[j+1]!=0:
        for k in range(j+2,n):
          L[k][j+1] = L[k][j+1]/v[j+1]
  for i in range(n):
    T[i][i] += alpha[i]
    if i<n-1:
      T[i][i+1] += beta[i]
      T[i+1][i] += beta[i]
  return P,L,T

# ------------------------------------------------------------
