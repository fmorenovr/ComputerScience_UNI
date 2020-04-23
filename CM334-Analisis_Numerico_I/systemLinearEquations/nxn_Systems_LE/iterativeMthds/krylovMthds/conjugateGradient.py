#!/usr/bin/python
from math import *
from sys import exit
from auxFuncSLE import *

# ------------------------------------------------------------
# 1.2 METODO GRADIENTE CONJUGADO
# Usar de ejemplo:
# A = [[4,-1,1],[-1,4,-2],[1,-2,4]]
# b = [12,-1,5]
def conjGrad(M, b, tol=1.0e-7):
  n = len(M)
  A = [row[:] for row in M]
  A = matrixToFloat(A)
  for i in range(n):
    if A[i][i] == 0:
      exit('Los elementos A[i][i] deben ser diferentes de 0')
  if not dominance(A):
    exit('Matriz no converge')
  if not isSymmetricMatrix(A):
    exit('Matriz no simetrica')
  Xk = [0.0]*n
  Axk = multiMatrixVector(A,Xk)
  rk = [(b[i] - Axk[i]) for i in range(len(b))]
  sk = [i for i in rk ]
  print Xk ,
  print " Condiciones iniciales"
  h=0
  while True:
    Ask = multiMatrixVector(A,sk)
    skrk = 0.
    skAsk = 0.
    for i in range(len(sk)):
      skrk += sk[i]*rk[i]
      skAsk += sk[i]*Ask[i]
    alphak = skrk/skAsk
    Xk1 = [ Xk[i] + alphak*sk[i] for i in range(len(Xk)) ]
    Xk[:] = Xk1[:]
    Axk = multiMatrixVector(A,Xk)
    rk = [(b[i] - Axk[i]) for i in range(len(b))]
    if eucliNorm(rk)<tol:
      break
    else:
      rkAsk=0.
      skAsk=0.
      for i in range(len(sk)):
        rkAsk += rk[i]*Ask[i]
        skAsk += sk[i]*Ask[i]
      betak=-rkAsk/skAsk
      sk1 = [rk[i] + betak*sk[i] for i in range(len(sk))]
      sk[:] = sk1[:]
    print Xk ,
    print " Iteracion: " + str(h+1)
    h+=1
  return Xk1

# ------------------------------------------------------------
