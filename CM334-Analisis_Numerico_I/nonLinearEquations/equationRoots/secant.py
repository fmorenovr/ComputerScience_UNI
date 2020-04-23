#!/usr/bin/env python
from math import *
from auxFuncRoots import *

# ------------------------------------------------------------
# 1.3 METODO SECANTE
def secant(f,x0,x1,printText = 1, tol=1e-7, NMAX=100):
  if x0>=x1:
    print("Error, a > b")
    return None
  if f(x0)==0:
    return x0
  elif f(x1) ==0:
    return x1
  elif f(x0)*f(x1) > 0:
    print("f(a) y f(b) son del mismo signo")
    return None
  n=1
  while n<=NMAX:
    x2 = x1 - f(x1)*((x1-x0)/(f(x1)-f(x0)))
    if printText:
      print "x0=%s\tx1=%s\tx2=%s\tf(x2)=%s"%(x0,x1,x2,f(x2))
    if abs(x2-x1) < tol:
      return x2
    else:
      x0 = x1
      x1 = x2
  print("No fueron suficientes iteraciones")
  return None

# ------------------------------------------------------------
