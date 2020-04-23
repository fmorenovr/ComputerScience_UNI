#!/usr/bin/env python
from math import *
from auxFuncSNLE import *

# -------------------------------------------------------
# 1.4 METODO NEWTON-SOR
def newtonSor(F,x0,w=1.25,printText=1,tol=1.0e-6,nmaxiter=100):
  for i in range(nmaxiter):
    Jac = newtonSorMatrix(F,x0,w)
    fx0 = F(x0)
    Jinv=invMatrix(Jac)
    dx = multiMatrixVector(Jinv,fx0)
    x1 = [x0[j] - dx[j] for j in range(len(dx))]
    dxnorm = eucliNorm(dx)
    if printText:
      print"************"
      print"x0=%s"%x0
      print"x1=%s"%x1
      print"F(x0)=%s"%F(x0)
    if dxnorm<=tol:
      return x1
    x0=x1
  print "El metodo no converge\n"
  return None

# -------------------------------------------------------
