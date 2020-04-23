#!/usr/bin/env python
from math import *
from auxFuncEigen import *

# -----------------------------------------------------
# 1.4 METODO INVERSE-POWER
# A = [[-4,14,0],[-5,13,0],[-1,0,2]]
# x0 = [1,1,1]
def inversePower(A,x0,printText=1,tol=1.0e-6,nmaxiter=100):
  n = len(A)
  I = [[float(i==j) for i in range(n)] for j in range(n)]
  x = [i for i in x0]
  Ax = multiMatrixVector(A,x)
  xtAx = sum([x[i]*Ax[i] for i in range(n)])
  xtx = sum([x[i]*x[i] for i in range(n)])
  s = 1.*xtAx/xtx
  Is = prodMatrix(I,s)
  aStar = matrixSus(A,Is) # Form [A*] = [A] - s[I]
  aStar = LUdecomp(aStar) # Decompose [A*]
  xMag = min(x)
  if printText:
    print x
  x = [1.*x[i]/xMag for i in range(len(x))]
  for j in range(nmaxiter):
    xOld = [i for i in x] # Save current [x]
    x = LUsolve(aStar,x) # Solve [A*][x] = [xOld]
    xMag = min(x) # Normalize [x]
    x = [1.*x[i]/xMag for i in range(len(x))]
    if printText:
      print xOld
    xOldx = sum([xOld[i]*x[i] for i in range(len(x))])
    if xOldx < 0.0:
      sign = -1.0
      x = [ -1.*x[i] for i in range(len(x))]
    else:
      sign = 1.0
    # analizamos el error
    auxX = [xOld[i] - x[i] for i in range(len(x))]
    auxXnorm = eucliNorm(auxX)
    if auxXnorm < tol:
      lamb = s + sign/xMag
      return lamb,x
  print 'Inverse power method no converge'
  return None,None

# -----------------------------------------------------
# 1.4.1 MAX EIGEN
# probar de ejemplo
# A = [[-30.0,10.0,20.0], [10.0,40.0,-50.0], [20.0,-50.0,-10.0]]
# v = [1.0, 0.0, 0.0]
def maxEigenInvPower(A,v,tol=1e-6,nmaxiter=100):
  for j in range(nmaxiter):
	  vOld = [i for i in v]
	  z = multiMatrixVector(A,v)
	  zMag = eucliNorm(z)
	  v = [1.*z[i]/zMag for i in range(len(z))]
	  vOldv = sum([vOld[i]*v[i] for i in range(len(v))])
	  if vOldv < 0.0:
		  sign = -1.0
		  v = [ -1.*v[i] for i in range(len(v))]
	  else:
	    sign = 1.0
	  auxV = [vOld[i] - v[i] for i in range(len(v))]
	  auxVnorm = eucliNorm(auxV)
	  if auxVnorm < tol:
	    break
  print 'Number of iterations =',j
  maxEigen = sign*zMag
  return maxEigen,v

# -----------------------------------------------------
