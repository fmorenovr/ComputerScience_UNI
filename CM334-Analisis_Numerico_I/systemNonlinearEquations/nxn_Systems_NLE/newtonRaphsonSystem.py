#!/usr/bin/env python
from math import *
from auxFuncSNLE import *

# -------------------------------------------------------
# 1.1 METODO NEWTON GENERALIZADO
def newtonRaphsonSystem(F,x0,printText=1,tol=1.0e-6,nmaxiter=100):
  for i in range (nmaxiter):
    Jac = jacobianMatrix(F,x0)
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
