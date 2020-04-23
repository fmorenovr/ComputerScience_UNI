#!/usr/bin/env python
from math import *
from auxFuncEigen import *

# -----------------------------------------------------
# 1.1 METODO DE JACOBI-EIGEN
# usar A= [[1/3.,-1/3.,0.],[-1/3.,4/3.,-1],[0.,-1,2.]]
def jacobiEigen(A,tol = 1.0e-6):
  a = [row[:] for row in A]
  n = len(a)
  maxRot = 5*(n*n) # numero de rotaciones
  vectors = [ [float(i==j) for i in range(n) ] for j in range(n)]
  for i in range(maxRot):
    aMax,k,l = maxElement(a)
    if aMax < tol:
      diagonal = []
      for i in range(n):
        diagonal.append(a[i][i])
      return diagonal,vectors
    rotate(a,vectors,k,l)
  print 'El metodo no converge\n'

# -----------------------------------------------------
# 1.1.1 METODO STANDARD-JACOBI
# probar de ejemplo
# A= [[1/3.,-1/3.,0.],[-1/3.,4/3.,-1],[0.,-1,2.]]
# B = [[1.,0.,0.],[0.,1.,0.],[0.,0.,2.]]
def standardJacobi(A,B):
  H,Lt = standardForm(A,B)
  n= len(A)
  values,z=jacobiEigen(H)
  x = matrixMulti(Lt,z)
  # normalizando los vectores
  xMag = [1.]*n
  for i in range(n):
    xMag[i] = sqrt(sum([ x[j][i]*x[j][i] for j in range(n)]))
  for i in range(n):
    for j in range(n):
      x[i][j] = 1.*x[i][j]/xMag[j]
  x=sortJacobiEigen(values,x)
  return values,x


# -----------------------------------------------------
