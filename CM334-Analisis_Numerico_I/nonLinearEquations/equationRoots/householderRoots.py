#!/usr/bin/env python
from math import *
from auxFuncRoots import *

# ------------------------------------------------------------
# 1.11 METODO DE HOUSEHOLDER ( 3er ORDEN )
def householderRoots(f,d1f,d2f,d3f,x0,printText = 1,tol=1e-9, NMAX=100):
  if f(x0)==0:
    return x0
  n=1
  while n<=NMAX:
    df0 = f(x0)
    df1 = d1f(f,x0)
    df2 = d2f(f,x0)
    df3 = d3f(f,x0)
    dx = (6*df0*df1*df1 - 3*df0*df0*df2)/( 6*df1*df1*df1 - 6*df0*df1*df2 + df0*df0*df3 )
    x1 = x0 - dx
    if printText:
      print "x0=%s\tx1=%s\tf(x1)=%s"%(x0,x1,f(x1))
    if abs(x1 - x0) < tol:
      return x1
    else:
      x0 = x1
  print("No fueron suficientes iteraciones")
  return None

# ------------------------------------------------------------
