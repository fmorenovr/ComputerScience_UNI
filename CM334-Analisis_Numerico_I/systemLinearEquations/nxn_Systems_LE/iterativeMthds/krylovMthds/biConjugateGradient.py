#!/usr/bin/python
from math import *
from sys import exit
from auxFuncSLE import *

# ------------------------------------------------------------
# 1.3 METODO DE GRADIENTE BICONJUGADO
# Usar de ejemplo:
# A = [[4,-1,2,7],[5,-1,4,-2],[3,1,-2,4],[4,9,8,3]]
# b = [12,-1,5,6]
def biconjGrad(M, b, tol=1.0e-7):
  n = len(M)
  A = [row[:] for row in M]
  A = matrixToFloat(A)
  for i in range(n):
    if A[i][i] == 0:
      exit('Los elementos A[i][i] deben ser diferentes de 0')
  minus = lambda x, y: [x[i]-y[i] for i in range(n)]
  Xk = [0.0]*n
  Axk = multiMatrixVector(A,Xk)
  rk = [(b[i] - Axk[i]) for i in range(len(b))]
  rt0 = [a for a in rk]
  pk = [i for i in rk ]
  print Xk ,
  print " Condiciones iniciales"
  h=0
  while True:
    Apk = multiMatrixVector(A,pk)
    rkrt0 = 0.
    Apkrt0 = 0.
    for i in range(len(pk)):
      rkrt0 += rk[i]*rt0[i]
      Apkrt0 += rt0[i]*Apk[i]
    alphak = rkrt0/Apkrt0
    sk = [ rk[i] - alphak*Apk[i] for i in range(len(rk))]
    Ask = multiMatrixVector(A,sk)
    skAsk = 0.
    AskAsk = 0.
    for i in range(len(pk)):
      skAsk += sk[i]*Ask[i]
      AskAsk += Ask[i]*Ask[i]
    wk = rkrt0/Apkrt0
    Xk1 = [ Xk[i] + alphak*pk[i] + wk*sk[i] for i in range(len(Xk)) ]
    if (normaInfVector(minus(Xk1,Xk)) / float(normaInfVector(Xk1))) < tol:
      break
    else:
      rk1 = [(sk[i] - wk*Ask[i]) for i in range(len(sk))]
      rk1rt0=0.
      rkrt0=0.
      for i in range(len(pk)):
        rk1rt0 += rk1[i]*rt0[i]
        rkrt0 += rk[i]*rt0[i]
      betak = (alphak/wk)*rk1rt0/rkrt0
      pk1 = [rk1[i] + betak*(pk[i] - wk*Apk[i]) for i in range(len(pk))]
      pk[:] = pk1[:]
      rk[:] = rk1[:]
      Xk[:] = Xk1[:]
    print Xk,
    print " Iteracion: " + str(h+1)
    h+=1
  return Xk1

# ------------------------------------------------------------
