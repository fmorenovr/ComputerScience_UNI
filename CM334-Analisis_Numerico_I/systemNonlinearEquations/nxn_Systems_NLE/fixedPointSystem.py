#!/usr/bin/env python
from math import *
from auxFuncSNLE import *

# -------------------------------------------------------
# 1.6 METODO PUNTO FIJO
def fixedPointSystem(g,x0,printText = 1,tol=1e-7,nmaxiter=100):
  gx0 = g(x0)
  n = len(x0)
  x0gx0 = sum([ ((x0[i] - gx0[i])==0.) for i in range(n) ])
  if x0gx0 == n:
    return x0
  niter=1
  correct = True
  while niter<=nmaxiter:
    x1 = g(x0)
    if printText:
      print"************"
      print"x0=%s"%x0
      print"x1=%s"%x1
      print"f(x0)=%s"%g(x0)
    dx = [ x1[i] - x0[i] for i in range(n)]
    if eucliNorm(dx) < tol:
      return x1
    x0 = x1[:]
    correct, i = evalPartialDif(g,x0)
    if not correct or i != -1:
      print "No existe la derivada o DIVERGE! en el punto "+str(i)
      return None
    niter+=1
  print("No fueron suficientes iteraciones")
  return None

# -------------------------------------------------------
