#!/usr/bin/python
from math import *
from sys import exit
from auxFuncSLE import *

# ------------------------------------------------------------
# 1.4 METODO GMRES
# usar de ejemplo
'''
A = [[10,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0],
    [1,9,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0],
    [0,1,8,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0],
    [0,0,1,7,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0],
    [0,0,0,1,6,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0],
    [0,0,0,0,1,5,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0],
    [0,0,0,0,0,1,4,1,0,0,0,0,0,0,0,0,0,0,0,0,0],
    [0,0,0,0,0,0,1,3,1,0,0,0,0,0,0,0,0,0,0,0,0],
    [0,0,0,0,0,0,0,1,2,1,0,0,0,0,0,0,0,0,0,0,0],
    [0,0,0,0,0,0,0,0,1,1,1,0,0,0,0,0,0,0,0,0,0],
    [0,0,0,0,0,0,0,0,0,1,0,1,0,0,0,0,0,0,0,0,0],
    [0,0,0,0,0,0,0,0,0,0,1,1,1,0,0,0,0,0,0,0,0],
    [0,0,0,0,0,0,0,0,0,0,0,1,2,1,0,0,0,0,0,0,0],
    [0,0,0,0,0,0,0,0,0,0,0,0,1,3,1,0,0,0,0,0,0],
    [0,0,0,0,0,0,0,0,0,0,0,0,0,1,4,1,0,0,0,0,0],
    [0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,5,1,0,0,0,0],
    [0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,6,1,0,0,0],
    [0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,7,1,0,0],
    [0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,8,1,0],
    [0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,9,1],
    [0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,10]]

b = [11,11,10,9,8,7,6,5,4,3,2,3,4,5,6,7,8,9,10,11,11]
restrt = 21
'''
def gmres(M,b,restrt,max_it=100,tol=1e-7):
  X=[0.]*len(b)
  A = [row[:] for row in M]
  A = matrixToFloat(A)
  flag = 0
  bnorm = eucliNorm(b)
  if bnorm ==0.:
    bnorm = 1.0
  Ax = multiMatrixVector(A,X)
  r0 = [ b[i] - Ax[i] for i in range(len(b)) ]
  error = eucliNorm(r0)/bnorm
  if error<tol:
    return None
  n = len(A)
  m = restrt
  #initializa workspace
  V = [[0.]*(m+1)]*n
  H = [[0.]*m]*(m+1)
  h = [0.]*m
  cs = [0.]*m
  sn = [0.]*m
  s = [0.]*(m+1)
  e1 = [0.]*n
  e1[0] = 1.
  # begin iteration
  for j in range(max_it):
    Ax = multiMatrixVector(A,X)
    r0 = [ b[z] - Ax[z] for z in range(len(b)) ]
    rnorm = eucliNorm(r0)
    v = [ r0[z]/rnorm for z in range(len(b)) ]
    V = replace(V,v,0)
    s[0] = 1.*rnorm
    # construct orthonormal
    # gram schmidt
    for i in range(m):
      h = [0.]*m
      v=[]
      for k in range(n):
        v = v + [V[k][i]]
      w = multiMatrixVector(A,v)
      for k in range(i+1):
        v=[]
        for u in range(n):
          v = v + [V[u][k]]
        h[k] = sum([(w[z]*v[z]) for z in range(len(w))])
        H=replace(H,h,i)
        w = [ w[z] - H[k][i]*v[z] for z in range(len(w))]
      H[i+1][i] = eucliNorm(w)
      for z in range(n):
        V[z][i+1] = w[z]/H[i+1][i]
      # givens rotation
      for k in range(i):
        temp = cs[k]*H[k][i] + sn[k]*H[k+1][i]
        H[k+1][i] = -sn[k]*H[k][i] + cs[k]*H[k+1][i]
        H[k][i] = temp
      # i-th rotation matrix
      cs[i],sn[i] = rotmat(H[i][i],H[i+1][i])
      temp = cs[i]*s[i]
      s[i+1] = -sn[i]*s[i]
      s[i] = temp
      H[i][i] = cs[i]*H[i][i] + sn[i]*H[i+1][i]
      H[i+1][i] = 0.0
      error = abs(s[i+1])/bnorm
      # actualizamos aproximacion y exit
      if abs(error)<=tol:
        Hii = [[ H[c][z] for z in range(i+1) ]for c in range(i+1)]
        invHii = invMatrix(Hii)
        y = multiMatrixVector(invHii,s[:i+1])
        Vi = [[V[c][z] for z in range(i+1)] for c in range(len(V))]
        Vy = multiMatrixVector(Vi,y)
        X = [X[z] + Vy[z] for z in range(n)] 
        break
    if error <=tol:
      break
    Hmm = [[ H[c][z] for z in range(m) ]for c in range(m)]
    invHmm = invMatrix(Hmm)
    y = multiMatrixVector(invHmm,s[:m])
    Vm = [[V[c][z] for z in range(m)] for c in range(len(V))]
    Vy = multiMatrixVector(Vm,y)
    X = [X[z] + Vy[z] for z in range(n)]
    Ax = multiMatrixVector(A,X)
    r0 = [ (b[z] - Ax[z]) for z in range(len(b)) ]
    s[i+1] = eucliNorm(r0)
    error = s[i+1]/bnorm
    if error <= tol:
      break
  if error > tol:
    flag = 1
  return X

# ------------------------------------------------------------
