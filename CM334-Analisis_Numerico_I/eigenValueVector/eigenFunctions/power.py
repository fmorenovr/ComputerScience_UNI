#!/usr/bin/env python
from math import *
from auxFuncEigen import *

# -----------------------------------------------------
# 1.2 METODO POWER
# A = [[-4,14,0],[-5,13,0],[-1,0,2]]
# x0 = [1,1,1]
def power(A,x0,printText = 1,tol=1.0e-6,nmaxiter=100):
  n = len(A)
  x = [i for i in x0]
  xMag = max(x)
  if printText:
    print x
  x = [1.*x[i]/xMag for i in range(len(x))]
  for j in range(nmaxiter):
    xOld = [i for i in x] # Save current [x]
    x = multiMatrixVector(A,x)
    xMag = max(x)
    if xMag==0:
      print "valor caracteristico 0"
      return 0,x
    if printText:
      print xOld
    x = [1.*x[i]/xMag for i in range(len(x))]
    xOldx = sum([xOld[i]*x[i] for i in range(len(x))])
    if xOldx < 0.0:
      x = [ -1.*x[i] for i in range(len(x))]
    # analisis de error
    auxX = [xOld[i] - x[i] for i in range(len(x))]
    auxXnorm = eucliNorm(auxX)
    if auxXnorm < tol:
      return xMag,x
  print 'power method no converge'
  return None,None

# -----------------------------------------------------
