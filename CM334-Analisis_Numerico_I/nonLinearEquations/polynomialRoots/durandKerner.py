#!/usr/bin/env python
from numpy import *
from random import *
from cmath import *
from auxFuncRoots import *

# ------------------------------------------------------------
# 1.7 METODO DURAND-KERNER
# probar P=[1,-3,3,-5]
def durandKerner(P,printText=1,tol=1.e-12,nmaxiter = 100):
  n = len(P) - 1
  x0 = [(0.4+0.9j)**i for i in range(n)]
  x1 = [0.0+0.0j]*n
  Px = [0.0+0.0j]*n
  cont=0
  for i in range(nmaxiter):
    for j in range(n):
      Px[j]=evalPoly(P,x0[j])[0]
      diffXs = 1.0 + 0.0j
      for k in range(n):
        if k!=j:
          diffXs = diffXs * (x0[j]-x0[k])
      x1[j] = x0[j] - Px[j]/diffXs
    if printText:
      for j in range(n):
        print "root["+str(j)+"]=%s"%x0[j],
      print
    for j in range(n):
      if abs(x1[j]-x0[j])<tol*max(abs(x1[j]),1.0):
        cont+=1
    if cont == n:
      return x1
    x0[:] = x1[:]
  print("No fueron suficientes iteraciones")
  return None

# ------------------------------------------------------------
