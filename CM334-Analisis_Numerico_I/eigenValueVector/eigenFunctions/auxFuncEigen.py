#!/usr/bin/env python
from numpy import *
from math import *

# -----------------------------------------------------
# producto escalar 2 vectores
def transProdVec(x,y):
  sum = 0
  for i in range(len(x)):
    sum = sum + x[i]*y[i]
  return sum

# -----------------------------------------------------
# encuentra el maximo de la diagonal
def maxElement(a):
  n = len(a)
  aMax = 0.0
  for i in range(n):
    for j in range(i+1,n):
      if abs(a[i][j]) >= aMax:
        aMax = abs(a[i][j])
        k = i
        l = j
  return aMax,k,l

# -----------------------------------------------------
# Rotaciones de givens para hacer 0 determinados elementos
def rotate(a,p,k,l): # rota para a[k][l] = 0
  n = len(a)
  diff = a[l][l] - a[k][k]
  if abs(a[k][l]) < abs(diff)*1.0e-36:
    t = a[k][l]/diff
  else:
    phi = diff/(2.0*a[k][l])
    t = 1.0/(abs(phi) + sqrt(phi*phi + 1.0))
    if phi < 0.0:
      t = -t
  c = 1.0/sqrt(t*t + 1.0)
  s = t*c
  tau = s/(1.0 + c)
  temp = a[k][l]
  a[k][l] = 0.0
  a[k][k] = a[k][k] - t*temp
  a[l][l] = a[l][l] + t*temp
  for i in range(k): # caso i < k
    temp = a[i][k]
    a[i][k] = temp - s*(a[i][l] + tau*temp)
    a[i][l] = a[i][l] + s*(temp - tau*a[i][l])
  for i in range(k+1,l): # caso k < i < l
    temp = a[k][i]
    a[i][k] = temp - s*(a[i][l] + tau*a[k][i]) 
    a[i][l] = a[i][l] + s*(temp - tau*a[i][l])
  for i in range(l+1,n): # caso i > 1
    temp = a[k][i]
    a[k][i] = temp - s*(a[l][i] + tau*temp)
    a[l][i] = a[l][i] + s*(temp - tau*a[l][i])
  for i in range(n): # actualiza las transformaciones
    temp = p[i][k]
    p[i][k] = temp - s*(p[i][l] + tau*p[i][k])
    p[i][l] = p[i][l] + s*(temp - tau*p[i][l])

# -----------------------------------------------------
# realiza la standarizacion
# Ax = lam*Bx
# donde B = LLt
# x = (L-1t)z
# H = L-1*A*(L-1)t
def standardForm(A,B):
  n = len(A)
  L = cholesky(B)
  Linv = invMatrixInf(L)
  Linvt = transMatrix(Linv)
  H = matrixMulti(Linv,matrixMulti(A,Linvt))
  return H,Linvt

# -----------------------------------------------------
# Ordena los autovectores y autovectores
# lam : eigen valores, x: eigen vectores
def sortJacobiEigen(lam,x):
  n = len(lam)
  for i in range(n-1):
    index = i
    val = lam[i]
    for j in range(i+1,n):
      if lam[j] < val:
        index = j
        val = lam[j]
    if index !=i:
      aux = lam[i]
      lam[i] = lam[index]
      lam[index] = aux
      x=exchangeCols(x,i,index)
  return x

# -----------------------------------------------------
# descomposicion LU
def LUdecomp(A):
  a = [row[:] for row in A]
  n = len(a)
  for k in range(n):
    for i in range(k+1,n):
      if a[i][k] != 0.0:
        lam = a [i][k]/a[k][k]
        for m in range(k+1,n):
          a[i][m] = a[i][m] - lam*a[k][m]
        a[i][k] = lam
  return a

# -----------------------------------------------------
# solucion de la matriz LU
def LUsolve(a,x):
  b = [i for i in x]
  n = len(a)
  for k in range(1,n):
    #b[k] = b[k] - dot(a[k,0:k],b[0:k])
    b[k] = b[k] - sum([a[k][l]*b[l] for l in range(0,k)])
  for k in range(n-1,-1,-1):
    #b[k] = (b[k] - dot(a[k,k+1:n],b[k+1:n]))/a[k,k]
    b[k] = (b[k] - sum([a[k][l]*b[l] for l in range(k+1,n)]) )/a[k][k]
  return b

# -----------------------------------------------------
# Retorna la secuencia de sturm (polinomio) caracteristico de 
# | [A] - lam[I] | = 0
# donde [A] = [c\d\c], tridiagonal
def sturmSeq(d,c,lam):
  n = len(d) + 1
  p = ones(n)
  p[1] = d[0] - lam
  for i in range(2,n):
    p[i] = (d[i-1] - lam)*p[i-1] - (c[i-2]*c[i-2])*p[i-2]
  return p

# -----------------------------------------------------
# Retorna el numero de eigenvalores de [A] = [c\d\c]
# menores que 'lam', usando la secuencia obtenida en sturm
def numLambdas(p):
  n = len(p)
  signold = 1
  numlam = 0
  for i in range(1,n):
    if p[i] > 0.0:
      sign = 1
    elif p[i] < 0.0:
      sign = -1
    else:
      sign = -signold
    if sign*signold < 0:
      numlam = numlam + 1
    signold = sign
  return numlam

# -----------------------------------------------------
# define circulos D1,D2, ... con centros de Aii y radio
# ri = SUM|Aij|(j!=i) 
# donde lambdaMin >= min(Aii - ri)
# y lambdaMax <= max(Aii + ri)
def gerschgorin(d,c):
  n = len(d)
  lmin = d[0] - abs(c[0])
  lmax = d[0] + abs(c[0])
  for i in range(1,n-1):
    lam = d[i] - abs(c[i]) - abs(c[i-1])
    if lam < lmin:
      lmin = lam
    lam = d[i] + abs(c[i]) + abs(c[i-1])
    if lam > lmax:
      lmax = lam
  lam = d[n-1] - abs(c[n-2])
  if lam < lmin:
    lmin = lam
  lam = d[n-1] + abs(c[n-2])
  if lam > lmax:
    lmax = lam
  return lmin,lmax

# -----------------------------------------------------
# Retorna la secuencia r0, ... rn que separa los N autovalores mas pequenos
# de la matriz [A] = [c\d\c], que es ri < lami < ri+1
# es decir, que en [ri, ri+1] existe un lami
def lamRange(d,c,N):
  lmin,lmax = gerschgorin(d,c)
  r = [1.]*(N+1)
  r[0] = lmin
  for k in range(N,0,-1):
    lam = (lmax + lmin)/2.0
    h = (lmax - lmin)/2.0
    for i in range(1000):
      p = sturmSeq(d,c,lam)
      numlam = numLambdas(p)
      h = h/2.0
      if numlam < k:
        lam = lam + h
      elif numlam > k:
        lam = lam - h
      else:
        break
    lmax = lam
    r[k] = lam
  return r

# ------------------------------------------------------------
# Retorna el minimo elemento de un vector y su indice
def minIndexElem(sc,a):
  n=len(sc)
  sc1 = [abs(sc[i]-a) for i in range(n)]
  scmin = sc1[0]
  k = 0
  for j in range(1,len(sc1)):
    if sc1[j]<scmin:
      scmin = sc1[j]
      k=j
  return scmin,k

# -----------------------------------------------------
# Devuelve algunos elementos cortados
def tridiagLower(A,num=0):
  n = len(A)
  N = [[0.]*n for i in range(n)]
  for i in range(n):
    if num<=0:
      for j in range(i-num,n):
        N[j][i] = A[j][i]
    else:
      for j in range(i,n):
        N[j][i] = A[j][i]
      for j in range(num):
        N[i][i+num-1] = A[i][i+num-1]
  return N

# -----------------------------------------------------
# Multiplicacion de 2 matrices C = A*B
def matrixMulti(A, B):
  rowsA, colsA = len(A), len(A[0])
  rowsB, colsB = len(B), len(B[0])
  if colsA != rowsB:
    exit('Dimensiones incorrectas')
  C = [[0. for row in range(colsB)] for col in range(rowsA)]
  for i in range(rowsA):
    for j in range(colsB):
      for k in range(colsA):
        C[i][j] += A[i][k]*B[k][j]
  return C

# ------------------------------------------------------------
# imprime matrix sin indices
def printMatrix(M):
  for i in range(len(M)):
    print '|',
    for j in range(len(M[i])):
      print '{0:8.4f}'.format(M[i][j]),
    print '|'
  print

# ------------------------------------------------------------
# multiplicacion matrix vector
def multiMatrixVector(A,x):
  c=[]
  col = len(x) # numero filas de b y numero de columnas de A
  row = len(A) # numero de filas de A
  if col!=len(A[0]):
    exit('No tiene longuitudes igual')
  for i in range(row):
    suma=0.
    for j in range(col):
      suma += A[i][j]*x[j]
    c.append(suma)
  return c

# ------------------------------------------------------------
# norma euclidiana o de fobrenius del vector x, ie, ||x||2
def eucliNorm(x):
  return sqrt(sum([x_i*x_i for x_i in x]))

# ------------------------------------------------------------
# producto de una matriz por un escalar
def prodMatrix(M,const):
  A = [row[:] for row in M]
  n=len(A)
  m=len(A[0])
  for i in range(n):
    for j in range(m):
      A[i][j] *=const
  return A

# ------------------------------------------------------------
# Resta de matrices
def matrixSus(A,B):
  n = len(A)
  m = len(A[0])
  C = [[0. for row in range(n)] for col in range(m)]
  for i in range(n):
    for j in range(m):
      C[i][j] = A[i][j] - B[i][j]
  return C

# ------------------------------------------------------------
# Norma 1 de una matriz
def norm1Matrix(A):
  summation = 0
  for i in range(len(A)):
    summation += abs(A[i][0])
  for j in range(1, len(A)):
    temp = 0
    for i in range(len(A[i])):
      temp += abs(A[i][j])
    summation = temp if (temp > summation) else summation
  return summation

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
# transpuesta de una matriz
# [M[i][j] for i in range(n)] imprime M[i][j] (j fijo), es decir, imprime A[0][j],A[1][j], ... y con el siguiente igual
# probar [M[i][1] for i in range(n)]
def transMatrix(M):
  n = len(M)
  m = len(M[0])
  return [[ M[i][j] for i in range(n)] for j in range(m)]

# ------------------------------------------------------------
def brent(f,a,b,printText = 1,tol=1.0e-9):
  x1 = a; x2 = b;
  f1 = f(x1)
  if f1 == 0.0:
    return x1
  f2 = f(x2)
  if f2 == 0.0:
    return x2
  if f1*f2 > 0.0:
    print("Root is not bracketed")
    return None
  x3 = 0.5*(a + b)
  for i in range(30):
    f3 = f(x3)
    if printText:
      print "x1=%s\tx2=%s\tx3=%s\tf(x3)=%s"%(x1,x2,x3,f3)
    if abs(f3) < tol:
      return x3
    # Tighten the brackets on the root
    if f1*f3 < 0.0:
      b = x3
    else:
      a = x3
    if (b - a) < tol*max(abs(b),1.0):
      return 0.5*(a + b)
    # Try quadratic interpolation
    denom = (f2 - f1)*(f3 - f1)*(f2 - f3)
    numer = x3*(f1 - f2)*(f2 - f3 + f1) + f2*x1*(f2 - f3) + f1*x2*(f3 - f1)
    # If division by zero, push x out of bounds
    try: dx = f3*numer/denom
    except ZeroDivisionError: dx = b - a
    x = x3 + dx
    # If iterpolation goes out of bounds, use bisection
    if (b - x)*(x - a) < 0.0:
      dx = 0.5*(b-a)
      x = a + dx
    # Let x3 <-- x & choose new x1 and x2 so that x1 < x3 < x2
    if x < x3:
      x2 = x3; f2 = f3
    else:
      x1 = x3; f1 = f3
    x3 = x
  print("No fueorn suficiente iteraciones")
  return None

# ------------------------------------------------------------
