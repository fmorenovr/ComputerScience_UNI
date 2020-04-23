#!usr/bin/env python
from math import *
from auxFuncSLE import *

# -------------------------------------------------------
# 1.1 METODO DESCENSO GRADIENTE SISTEMA ECUACIONES LINEALES
# usar de ejemplo
# A = [[0.00300,59.14],[5.291,-6.130]]
# b = [59.17,46.78]
# x0 = [0,0]
def gradientDescentSLE(M,x0,b,printText=1,tol=1e-7,nmaxiter=100):
  A = [ row[:] for row in M]
  n = len(b)
  x = x0[:]
  for itera in range(nmaxiter):
    Ax = multiMatrixVector(A,x)
    r = [(b[i] - Ax[i]) for i in range(n)]
    rr = sum([ (1.*r[i]*r[i]) for i in range(n) ])
    Ar = multiMatrixVector(A,r)
    rAr = sum([ (1.*r[i]*Ar[i]) for i in range(n) ])
    t = rr/rAr
    x1 = [ (x[i] + t*r[i]) for i in range(n) ]
    if printText:
      print "x=%s"%x
    tr = [ (t*r[i]) for i in range(n) ]
    rNorm = eucliNorm(tr)
    if rNorm < tol:
      return x1
    x = x1[:]
  print "No fueron suficientes iteraciones"
  return None

# -------------------------------------------------------
