#!/usr/bin/env python
from numpy import *
from random import *
from cmath import *
from auxFuncRoots import *

# ------------------------------------------------------------
# 1.4 METODO LAGUERRE
# probar P = [1,-5,-9,155,-250]
def laguerre(P,printText=1,tol=1.e-12,nmaxiter = 100):
  x0 = random()
  n = len(P)
  for i in range(nmaxiter):
    Px0,dPx0,ddPx0 = evalPoly(P,x0)
    if abs(Px0)<tol:
      return x0
    g = dPx0/Px0
    h = g*g - ddPx0/Px0
    f = sqrt((n-2)*((n-1)*h - g*g))
    if abs(f+g)>abs(g-f):
      dx = (n-1)/(g+f)
    else:
      dx = (n-1)/(g-f)
    x1 = x0 - dx
    if printText:
      print "x0=%s\tx1=%s\tP(x0)=%s"%(x0,x1,Px0)
    if abs(dx)<tol*max(abs(x1),1.0):
      return x1
    x0 = x1
  print("No fueron suficientes iteraciones")
  return None

# ------------------------------------------------------------
