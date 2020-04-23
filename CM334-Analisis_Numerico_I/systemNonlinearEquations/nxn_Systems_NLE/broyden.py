#!/usr/bin/env python
from math import *
from auxFuncSNLE import *

# -------------------------------------------------------
# 1.5 METODO BROYDEN
def broyden(F,x0,printText=1,tol=1e-6,nmaxiter=100):
  n = len(x0)
  J0 = jacobianMatrix(F,x0)
  fx0 = F(x0)
  J0inv = invMatrix(J0)
  dx = multiMatrixVector(J0inv,fx0)
  x1 = [x0[i] - dx[i] for i in range(n)]
  for niter in range(nmaxiter):
    w = [i for i in fx0]
    fx0 = F(x1)
    y = [fx0[i] - w[i] for i in range(n)]
    z = multiMatrixVector(J0inv,y)
    z = [-1.*dx[i] for i in range(n)]
    p = sum([-1.*dx[i]*z[i] for i in range(n)])
    u = multiVectorMatrix(J0inv,dx)
    zdx = [1.*(z[i] + dx[i])/p for i in range(n)]
    DJ = [[ zdx[j]*u[l] for l in range(n)]for j in range(n)]
    J1inv = [[J0inv[i][j] + DJ[i][j] for i in range(n)] for j in range(n)]
    dx = multiMatrixVector(J1inv,fx0)
    x0 = x1[:]
    x1 = [x0[i] - dx[i] for i in range(n)]
    dxnorm = eucliNorm(dx)
    if printText:
      print"************"
      print"x0=%s"%x0
      print"x1=%s"%x1
      print"F(x1)=%s"%F(x1)
    if dxnorm<=tol:
      return x1
    x0=x1[:]
  print "El metodo no converge\n"
  return None

# -------------------------------------------------------
