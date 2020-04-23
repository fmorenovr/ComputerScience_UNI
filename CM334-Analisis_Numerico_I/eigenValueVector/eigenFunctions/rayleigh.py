#!/usr/bin/env python
from math import *
from auxFuncEigen import *
from random import *

# -----------------------------------------------------
# 1.5 METODO RAYLEIGH
# A = [[-30.0,10.0,20.0], [10.0,40.0,-50.0], [20.0,-50.0,-10.0]]
# s = -57
# A = [[1,2,3], [1,2,1], [3,2,1]]
# s = 200
def rayleigh(A,mu,tol = 1.e-6, nmaxiter = 100):
  n = len(A)
  x = [0.]*n
  for j in range(n):
    x[j] = random()
  xMag = eucliNorm(x)
  x = [1.*x[i]/xMag for i in range(len(x))]
  I = [[float(i==j) for i in range(n)] for j in range(n)]
  Is = prodMatrix(I,mu)
  aStar = matrixSus(A,Is)
  aStar = LUdecomp(aStar)
  y = LUsolve(aStar,x)
  ynorm = eucliNorm(y)
  lamb = sum([y[i]*x[i] for i in range(n)])
  mu = mu + 1./lamb
  ylamx = [y[i] - lamb*x[i] for i in range(n)]
  err = eucliNorm(ylamx)/ynorm
  for i in range(5):
    x = [ 1.*y[i]/ynorm for i in range(n)]
    Is = prodMatrix(I,mu)
    aStar = matrixSus(A,Is)
    aStar = LUdecomp(aStar)
    y = LUsolve(aStar,x)
    ynorm = eucliNorm(y)
    lamb = sum([y[i]*x[i] for i in range(n)])
    mu = mu + 1./lamb
    ylamx = [y[i] - lamb*x[i] for i in range(n)]
    err = eucliNorm(ylamx)/ynorm
    if err<tol:
      return x,mu
  print "Rayleigh Method no converge"
  return None,None

# -----------------------------------------------------
