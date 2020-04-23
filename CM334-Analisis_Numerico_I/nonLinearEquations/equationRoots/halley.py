#!/usr/bin/env python
from math import *
from auxFuncRoots import *

# ------------------------------------------------------------
# 1.10 METODO DE HALLEY
def halley(f, d1f,d2f, x0,printText = 1, tol=1e-9, NMAX=100):
  if f(x0)==0:
    return x0
  n=1
  while n<=NMAX:
    df1 = d1f(f,x0)
    df2 = d2f(f,x0)
    dx = 2*f(x0)*df1/(2*df1*df1 - f(x0)*df2)
    x1 = x0 - dx
    if printText:
      print "x0=%s\tx1=%s\tf(x1)=%s"%(x0,x1,f(x1))
    if abs(dx) < tol:
      return x1
    else:
      x0 = x1
  print("No fueron suficientes iteraciones")
  return None

# ------------------------------------------------------------
