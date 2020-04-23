#!/usr/bin/python
from math import *
from sys import exit
from auxFuncSLE import *

# ------------------------------------------------------------
# 1.5 METODO TFQMR
# usar de ejemplo
'''
 A = [[12,0,0,0,0,0,0,1,0],
      [0,3,0,0,0,0,0,0,2],
      [0,1,1,0,0,0,0,0,0],
      [0,0,5,8,0,0,0,0,7],
      [1,0,1,0,3,0,0,3,0],
      [0,0,0,0,0,4,0,0,0],
      [0,0,1,0,0,0,15,0,0],
      [0,0,0,0,0,0,0,5,0],
      [0,0,0,3,1,0,0,0,6]]
'''
# b = [1,4,0,0,3,0,0,2,6]
# X=[1.]*len(b)
def tfqmr(M,b,precon=False,tol=1.e-6):
  n = len(M)
  X=[1.]*n
  matvec_max = 2*n
  nMatvec = 0
  A = [row[:] for row in M]
  A = matrixToFloat(A)
  for i in range(n):
    if A[i][i] == 0:
      exit('Los elementos A[i][i] deben ser diferentes de 0')
  if precon:
    D = [ [ (i==j)*sqrt(abs(A[i][j])) for i in range(n)] for j in range(n)]
    r0 = multiMatrixVector(invMatrix(D),b)
  else:
    r0 = [a for a in b]
  Ax = multiMatrixVector(A,X)
  r0 = [ b[i] - Ax[i] for i in range(len(b)) ]
  minus = lambda x, y: [x[i]-y[i] for i in range(n)]
  r0r0 = 0.
  for i in range(len(r0)):
    r0r0+=r0[i]*r0[i]
  rho = r0r0
  residNorm = abs(sqrt(rho))
  residNorm0 = residNorm
  threshold = max(1.e-8,tol,eucliNorm(b))
  # vector residual inicial
  finished = (residNorm <= threshold or nMatvec >= matvec_max)
  if not finished:
    y = [i for i in r0]
    w = [i for i in r0]
    d = [0.]*n
    # constantes
    theta = 0.
    eta = 0.
    k = 0
    # vectores matriciales
    if precon:
      z = multiMatrixVector(D,y)
    else:
      z = [ a for a in y ]
    u = multiMatrixVector(A,z)
    nMatvec+=1
    v = [i for i in u]
  print X ,
  print " Condiciones iniciales"
  # correcto
  while not finished:
    k=k+1 # empieza la iteracion 1, es decir k = 1
    # calculo de sigma
    r0v = 0.
    for i in range(len(r0)):
      r0v+=r0[i]*v[i]
    sigma = r0v
    alpha = rho/sigma
    # primer paso
    w = [ w[i] - alpha*u[i] for i in range(len(w))]
    d = [ theta*theta*eta/alpha*d[i] for i in range(len(d)) ]
    d = [ d[i] + z[i] for i in range(len(d)) ]
    theta = eucliNorm(w)/residNorm
    c = 1./sqrt(1+theta*theta)
    residNorm*=theta*c
    eta = c*c*alpha
    X = [ X[i] + eta*d[i] for i in range(len(X)) ]
    print X,
    print " Iteracion: " + str(k) + " .1"
    m = 2.*k - 1.
    if residNorm*sqrt(m+1)<=tol*threshold or nMatvec >=matvec_max:
      finished = True
      continue
    # segundo paso
    m+=1
    y = [ y[i] - alpha*v[i] for i in range(len(y)) ]
    if precon:
      z = multiMatrixVector(D,y)
    else:
      z = [ a for a in y ]
    u = multiMatrixVector(A,z)
    nMatvec+=1
    w = [ w[i] - alpha*u[i] for i in range(len(w)) ]
    d = [ theta*theta*eta/alpha*d[i] for i in range(len(d)) ]
    d = [ d[i] + z[i] for i in range(len(d)) ]
    theta = eucliNorm(w)/residNorm
    c = 1./sqrt(1+theta*theta)
    residNorm*=theta*c
    eta = c*c*alpha
    X = [ X[i] + eta*d[i] for i in range(len(X)) ]
    print X,
    print " Iteracion: " + str(k) + " .2"
    if residNorm*sqrt(m+1)<=tol*threshold or nMatvec >= matvec_max:
      finished = True
      continue
    # final updates
    r0w = 0.
    for i in range(len(r0)):
      r0w+=r0[i]*w[i]
    rho1 = r0w
    beta = rho1/rho
    rho = rho1
    # update y
    y = [ y[i]*beta for i in range(len(y)) ]
    y = [ y[i] + w[i] for i in range(len(y)) ]
    # update parcial de v y u
    v = [ v[i]*beta for i in range(len(v)) ]
    v = [ v[i] + u[i] for i in range(len(v)) ]
    v = [ v[i]*beta for i in range(len(v)) ]
    # update u
    if precon:
      z = multiMatrixVector(D,y)
    else:
      z = [ a for a in y ]
    u = multiMatrixVector(A,z)
    nMatvec+=1
    # completa update de v
    v = [ v[i] + u[i] for i in range(len(v)) ]
  return X

# ------------------------------------------------------------
