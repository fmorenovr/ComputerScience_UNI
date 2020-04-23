#!/usr/bin/python
from auxFuncSLE import *

# ------------------------------------------------------------
# 1.1 METODO DE GRAM-SCHMIDT
# usar este de ejemplo: A=[[12,-51,4],[6,167,-68],[-4,24,-41]]
# A = QR, Q es una matriz ortonormal (Q.Qt = I ) y R una matriz superior
def gramSchmidt(X):
  Q = [row[:] for row in X]  # hace una copia
  k = len(X[0])          # number of columns. 
  n = len(X)             # number of rows.
  for j in range(k):
    for i in range(j):
      # D = < Qi, Qj>
      D = sum([Q[p][i]*Q[p][j] for p in range(n)])
      for p in range(n): 
        # Qi tiene longuitud 1
        # Qj = Qj - <Qi,Qj> Qi/< Qi,Qi >
        Q[p][j] -= (D * Q[p][i])
    # Normalize column Q[j]
    invnorm = 1.0 / sqrt(sum([(Q[p][j])*(Q[p][j]) for p in range(n)]))
    for p in range(n):
      Q[p][j] *= invnorm
    Q_t=transMatrix(Q)  # transpuesta de Q(Matriz ortogonalizada de A)
  R=matrixMulti(Q_t,X) # forma triangular superior
  return Q,R

# ------------------------------------------------------------
# Hace una copia o trabaja con la misma matriz
def makeCopy(X,inplace=False):
  if not inplace:
    Q = [row[:] for row in X]  # hace una copia
  else:
    Q = X
  return Q

# ------------------------------------------------------------
