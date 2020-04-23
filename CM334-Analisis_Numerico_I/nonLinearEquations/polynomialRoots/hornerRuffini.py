#!/usr/bin/env python
from numpy import *
from random import *
from cmath import *
from auxFuncRoots import *

# ------------------------------------------------------------
# 1.3 METODO DE HORNER-RUFFINI
# probar
# P=[2, 0, -3, 3, -4]
# x0 = -2
def hornerRuffini(P,x0,printText=1,tol=1e-7,nmaxiter = 100):
  Px0 = horner(P,x0)
  if Px0==0:
    print 'x0 es raiz'
    return x0
  n = 1
  Q = [ i for i in P]
  while n<=nmaxiter:
    Px0,dPx0,ddPx0 = evalPoly(P,x0)
    try: dx = Px0/dPx0
    except ZeroDivisionError: return x0
    x1 = x0 - dx
    if printText:
      print "x0=%s\tx1=%s\tP(x0)=%s"%(x0,x1,Px0)
    if abs(x1 - x0) < tol:
      return x1
    else:
      x0 = x1
  print("No fueron suficientes iteraciones")
  return None

# ------------------------------------------------------------
