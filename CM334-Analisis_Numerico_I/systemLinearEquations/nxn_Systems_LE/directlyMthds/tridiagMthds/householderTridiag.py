#!/usr/bin/python
from auxFuncSLE import *

# ------------------------------------------------------------
# 1.2 METODO DE HOUSEHOLDER
# usar este de ejemplo: A = [[4.75,2.25,-0.25],[2.25,4.75,1.25],[-0.25,1.25,4.75]]
def householderTridiag(A):
  n = len(A)
  R = A
  Q = [[0.0] * n for i in xrange(n)]
  for k in range(n-2):
    I = [[float(i == j) for i in xrange(n)] for j in xrange(n)]
    #Se crea el vector x y el escalar alpha
    x = [row[k] for row in R[k:]]
    #Se crea la constante que inicializa cada vector columna
    if x[1]!=0:
      alpha = -(x[1])/fabs(x[1]) * eucliNorm(x[1:])
    else:
      alpha = -1.0*eucliNorm(x[1:])
    #Se crea r
    r = sqrt(1.0/2*alpha*alpha - 1.0/2*x[1]*alpha)
    #Se el vector v
    u = [0.0]*n
    u[k+1] = (x[1]-alpha)/(2.0*r)
    for i in range(k+2,n):
        u[i] = x[i-k]/(2.0*r)
    v = u
    #Se crea la matriz Q_t = I - 2*v*vt
    Q_t = [ [float(i==j) - 2.0 * v[i] * v[j] for i in xrange(n)] for j in xrange(n) ]
    # T = Q_t*A*Q_t
    if k == 0:
      Q = Q_t
      R = matrixMulti(Q_t,A)
      R = matrixMulti(R,Q_t)
    else:
      Q = matrixMulti(Q_t,Q)
      R = matrixMulti(Q_t,R)
      R = matrixMulti(R,Q_t)
  #Se retorna la transpuesta de los Q_t, ie, trans(Q_tn* ... *Q_t1) = Q
  T = R
  Q = transMatrix(Q)
  return Q,T

# ------------------------------------------------------------
