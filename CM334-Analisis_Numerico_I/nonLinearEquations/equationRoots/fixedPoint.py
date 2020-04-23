#!/usr/bin/env python
from math import *
from auxFuncRoots import *

# ------------------------------------------------------------
# 1.7 METODO DEL PUNTO FIJO
def fixedPoint(f,a,printText = 1,tol=1e-7,NMAX=100):
  if (f(a)-a)==0:
    return a
  n=1
  correct = True
  while n<=NMAX:
    p=f(a)
    if printText:
      print "a=%s\tp=%s\tf(a)=%s"%(a,p,f(a))
    if abs(p-a)<tol:
      return p
    a=p
    try :k = d1f(f,a)
    except FloatingPointError:
      correct = False
    if not correct or abs(k) >= 1:
      print("No existe la derivada o DIVERGE! ")
      return None
    n+=1
  print("No fueron suficientes iteraciones")
  return None

# ------------------------------------------------------------
