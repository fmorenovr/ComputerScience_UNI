#!/usr/bin/env python
from math import *
from auxFuncRoots import *

# ------------------------------------------------------------
# 1.4 METODO DE NEWTON
def newton(f, d1f, x0,printText=1, tol=1e-9, NMAX=100):
  if f(x0)==0:
    return x0
  n=1
  while n<=NMAX:
    try: dx = f(x0)/d1f(f,x0)
    except ZeroDivisionError: return x0
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
