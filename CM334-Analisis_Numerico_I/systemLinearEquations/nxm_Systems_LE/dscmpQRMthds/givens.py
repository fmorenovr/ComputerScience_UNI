#!/usr/bin/python
from auxFuncSLE import *

# ------------------------------------------------------------
# 1.3 METODO DE GIVENS
# usar este de ejemplo: A=[[12,-51,4],[6,167,-68],[-4,24,-41]]
# A = QR, Q es una matriz ortonormal (Q.Qt = I ) y R una matriz superior
# A = [ [6,5,0],[5,1,4],[0,4,3]]
def givens(A):
  n = len(A)
  An = A	
  Gn = [[float(i == j) for j in range(n)] for i in range(n)]
  Q_t = [[float(i == j) for j in range(n)] for i in range(n)]
  a = An[0][n-2]
  b = An[0][n-1]
  index = 1
  for i in range(n):
    for j in range(n-1, i, -1):
      a = An[j-1][i]
      b = An[j][i]
      if a*a + b*b == 0:
        continue
      cosX = a / (sqrt(a*a + b*b)) 
      sinX = -b / (sqrt(a*a + b*b))
      Gn[j][j] = cosX
      Gn[j][j-1] = sinX
      Gn[j-1][j] = -sinX
      Gn[j-1][j-1] = cosX
#      print 'G' +str(index) + ':'
#      printMatrix(Gn)
      An = matrixMulti(Gn, An)
#      print 'A' +str(index) + ':'
#      printMatrix(An)
      Q_t = matrixMulti(Gn, Q_t)
      #Volviendo la matriz Gn a la identidad
      Gn = [[float(k == l) for l in range(n)] for k in range(n)]
      index += 1
      Q=transMatrix(Q_t)
      R=An
  return Q,R

# ------------------------------------------------------------
