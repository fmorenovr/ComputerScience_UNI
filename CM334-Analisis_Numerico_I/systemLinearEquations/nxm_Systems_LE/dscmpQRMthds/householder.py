#!/usr/bin/python
from auxFuncSLE import *

# ------------------------------------------------------------
# 1.2 METODO DE HOUSEHOLDER
# usar este de ejemplo: A=[[12,-51,4],[6,167,-68],[-4,24,-41]]
# A = QR, Q es una matriz ortonormal (Q.Qt = I ) y R una matriz superior
def householder(A):
  n = len(A)
  R = A
  Q = [[0.0] * n for i in xrange(n)]
  for k in range(n-1):
    I = [[float(i == j) for i in xrange(n)] for j in xrange(n)]
    # Se crea los vectores x, e y un escalar alpha
    x = [row[k] for row in R[k:]]
    e = [row[k] for row in I[k:]]
    #La funcion cmp(a, b) retorna -1 si a<b, 1 si a>b, 0 si a==b
    alpha = -cmp(x[0],0) * eucliNorm(x)
    #Se crea los vectores u, v
    u = map(lambda p,q: p + alpha * q, x, e)
    norm_u = eucliNorm(u)
    v = map(lambda p: p/norm_u, u)
    #Se crea la matriz menor Q_t
    Q_min = [ [float(i==j) - 2.0 * v[i] * v[j] for i in xrange(n-k)] for j in xrange(n-k) ]
    #Se rellena la matriz menor Q (Q_min)
    Q_t = [[ Q_i(Q_min,i,j,k) for i in xrange(n)] for j in xrange(n)]
    #Si esta en la primera ejecutada, entonces se calcula Q_t*A = R
    #Sino, Q_tn .. Q_t1*A = R
    if k == 0:
      Q = Q_t
      R = matrixMulti(Q_t,A)
    else:
      Q = matrixMulti(Q_t,Q)
      R = matrixMulti(Q_t,R)
  #Se retorna la transpuesta de los Q_t, ie, trans(Q_tn* ... *Q_t1) = Q
  Q = transMatrix(Q)
  return Q, R

# ------------------------------------------------------------
# Rellenando elementos de la matrix Q_t
def Q_i(Q_min, i, j, k):
  if i < k or j < k:
    return float(i == j)
  else:
    return Q_min[i-k][j-k]

# ------------------------------------------------------------
