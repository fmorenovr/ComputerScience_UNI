#!/usr/bin/python
from auxFuncSLE import *

# ------------------------------------------------------------
# 1.1 METODO DE THOMAS
# Usar de ejemplo: A=[[-6,3,0,0,0],[3,-4.5,3,0,0],[0,1.5,-7.5,3,0],[0,0,4.5,-7.5,3],[0,0,0,4.5,-4.5]]
# d = [0,0,100,0,0]
def thomas(T,d):
  n = len(T)
  A = [row[:] for row in T]
  # diagonal superior
  c = [float(A[i][i+1]) for i in range(n-1)]
  # diagonal
  b = [float(A[i][i]) for i in range (n)]
  # diagonal inferior
  a = [float(A[i+1][i]) for i in range (n-1)]
  # las ecuaciones
  for i in range(0,len(d)):
    d[i] = float(d[i])
  c.append(0.)
  p = []
  q = []
  p.append(c[0]/b[0])
  q.append(d[0]/b[0])
  for j in range(1,n):
    pj = c[j]/(b[j] - a[j-1]*p[j-1])
    qj = (d[j] - a[j-1]*q[j-1])/(b[j] - a[j-1]*p[j-1])
    p.append(pj)
    q.append(qj)
  # back sub
  x = []
  x.append(q[n-1])
  for j in range(n-2,-1,-1):
    xj = q[j] - p[j]*x[0]  # Value holder
    x.insert(0,xj)   # Building the list backwards
  # Return the value
  return x

# ------------------------------------------------------------
