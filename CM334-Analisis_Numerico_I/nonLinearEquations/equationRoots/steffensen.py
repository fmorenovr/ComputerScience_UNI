#!/usr/bin/env python
from math import *
from auxFuncRoots import *

# ------------------------------------------------------------
# 1.8 METODO DE STEFFENSEN
def steffensen(f,a,printText = 1,tol=1e-7,NMAX=100):
  if (f(a)-a)==0:
    return a
  correct=True
  for i in range(NMAX):
    p1 = f(a)
    p2 = f(p1)
    if printText:
      print "a=%s\tp1=%s\tp2=%s\tf(a)=%s"%(a,p1,p2,f(a))
    if (p2-2*p1+a)==0:
      return p2
    p = a - (p1-a)*(p1-a)/(p2-2*p1+a)
    if abs(p-a)<tol:
      return p
    a=p
    try :k = d1f(f,a)
    except FloatingPointError:
      correct = False
    if not correct or k >= 1:
      print("No existe la derivada o DIVERGE! ")
      return None
  print("No fueron suficientes iteraciones")
  return None

# ------------------------------------------------------------
