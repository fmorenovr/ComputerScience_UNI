#!/usr/bin/env python
"""Definiciones:
   A, M : Matriz original.
   a : Matriz aumentada (A|b)
   b : Vector independiente. 
   L : Matriz triangular inferior unitaria.
   M : Matriz triangular inferior unitaria.
   U : Matriz triangular superior unitaria.
   D : Matriz diagonal.
   P : Matriz de permutacion
   Pr : Matriz de permutacion de filas
   Pc : Matriz de permutacion de columnas
   G : Matriz superior hallada con el metodo de Cholesky.
   Gt : Transpuesta de G.
   A = LU : significa factorizacion sin pivoteo
   PA = LU : significa factorizacion con pivoteo parcial
   PAQ = LU : significa factorizacion con pivoteo total
   piv: pivoteo, piv=0 sin pivoteo, piv=1 con pivoteo parcial piv=2 con pivoteo total
"""
from math import *
from sys import exit

# ------------------------------------------------------------
# Ingresar datos a una matrix
def inputMatrix():
  print("Ingreso de datos de la matriz")
  done=0
  while not done:
    m = raw_input("Ingrese el orden (dimension) de la matriz: ")
    if m=='':
      print("vuelva a ingresar")
    else:
      n=int(m)
      print("Ingrese los elementos de la matriz A fila por fila con un espacio luego enter")
      A = [[0.0]*n for i in range(n)]
      aux = [[0.0]*n for i in range(n)]
      for i in range(n):
        temp = raw_input()
        A[i] = temp.split()
        for j in range(n):
          A[i][j] = float(A[i][j])
      if A == aux:
        exit('Matriz nula, vuelva a escribir la matriz')
      else:
        done=1
  return A

# ------------------------------------------------------------
# ingresar datos a un vector
def inputVector():
  print("Ingreso de datos del vector")
  done=0
  while not done:
    m = raw_input("Ingrese la dimension del vector b: ")
    if m=='':
        print("vuelva a ingresar")
    else:
      n = int(m)
      b = [0.0]*n
      temp = raw_input()
      b = temp.split()
      for i in range(n):
        b[i] = float(b[i])
      done=1
  return b

# ------------------------------------------------------------
# imprime matrix con indices
def printMatrixIndex(M):
  for i in range(len(M)):
    for j in range(len(M[i])):
      if(i == 0 and j == 0):
        print " "
        for x in range(len(M[i])):
          print '{0:8}'.format(x),
        print("")
      if(j == 0):
        print i,
      print '{0:8.4f}'.format(M[i][j]),	
    print '|'
  print

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
# norma infinita de una matriz
def normInfMatrix(A):
  summation = 0
  for j in range(len(A)):
    summation += abs(A[0][j])
  for i in range(1, len(A)):
    temp = 0
    for j in range(len(A[i])):
      temp += abs(A[i][j])
    summation = temp if (temp > summation) else summation
  return summation

# ------------------------------------------------------------
# norma euclidiana o de fobrenius del vector x, ie, ||x||2
def eucliNorm(x):
  return sqrt(sum([x_i*x_i for x_i in x]))

# ------------------------------------------------------------
# Calcula la norma infinita de un vector:	||x|| = max {|xi|}, i = 0, 1, ... n.
def normaInfVector(L):
  maximum = fabs(L[0])
  for i in range(1, len(L)):
    maximum = max(maximum, fabs(L[i]))
  return maximum

# ------------------------------------------------------------
# evalua si una matrix es simetrica
def isSymmetricMatrix(A):
#  print("Evalua si una matriz es simetrica")
  for i in range(len(A)):
    for j in range(i+1,len(A)):
      if A[i][j] != A[j][i]:
#        print("No es simetrica")
        return False
#  print("Si es simetrica")
  return True 

# ------------------------------------------------------------
# transpuesta de una matriz
# [M[i][j] for i in range(n)] imprime M[i][j] (j fijo), es decir, imprime A[0][j],A[1][j], ... y con el siguiente igual
# probar [M[i][1] for i in range(n)]
def transMatrix(M):
  n = len(M)
  m = len(M[0])
  return [[ M[i][j] for i in range(n)] for j in range(m)]

# ------------------------------------------------------------
# transpuesta inversa de una matriz
# [M[i][j] for i in range(n)] imprime M[i][j] (j fijo), es decir, imprime A[0][j],A[1][j], ... y con el siguiente igual
# probar [M[i][1] for i in range(n)]
def transInvMatrix(M):
  n = len(M)
  m = len(M[0])
  return [[ M[i][j] for i in range(n-1,-1,-1)] for j in range(m-1,-1,-1)]

# ------------------------------------------------------------
# inversa de una matriz
def invMatrix(D):
  n = len(D)
  A = [row[:] for row in D]
  B = [[float(i == j) for j in range(n)] for i in range(n)]
  C = [[0.0]*n for i in range(n)]
  # transformacion de la matriz y de los terminos independientes
  for k in range(n-1):
    for i in range(k+1,n):
      # terminos independientes
      for s in range(n):
        B[i][s] -= A[i][k]*B[k][s]/A[k][k]
      # elementos de la matriz
      for j in range(k+1,n):
        A[i][j] -= A[i][k]*A[k][j]/A[k][k]
  # calculo de las incognitas, elementos de la matriz inversa
  for s in range(n):
    C[n-1][s] = B[n-1][s]/A[n-1][n-1]
    for i in range(n-2,-1,-1):
      C[i][s] = B[i][s]/A[i][i]
      for k in range(n-1,i,-1):
        C[i][s] -= A[i][k]*C[k][s]/A[i][i]
  return C

# ------------------------------------------------------------
# inversa de una matriz triangular inferior ( menos pasos )
def invMatrixInf(Lower):
  n = len(Lower)
  L = [ row[:] for row in Lower]
  Inv = [ [float(q==w) for q in range(n) ] for w in range(n)]
  for i in range(n):
    # dividimos la fila i entre L[i][i]
    for j in range(0,i+1):
      Inv[i][j] = 1.*Inv[i][j]/L[i][i]
      L[i][j] = 1.*L[i][j]/L[i][i]
  # operamos sobre la fila
  for i in range(n):
    for j in range(i+1,n):
      const = L[j][i]
      susRows(L,j,i,const)
      susRows(Inv,j,i,const)
  return Inv

# ------------------------------------------------------------
# Aumenta una matriz un vector
# Retorna la matriz aumentada
def augmentedMatrixVector(M, b):
  A = [row[:] for row in M]
  for i in range(len(M)):
    A[i].append(b[i])
  return A

# ------------------------------------------------------------
# Maximo numero en una columna empezando de la diagonal
def maxColum(M, c):
  r = c #fila
  maximum = M[c][c]
  for i in range(c+1,len(M)):
    if(fabs(maximum) < fabs(M[i][c])):
      maximum = M[i][c]
      r = i
  return r

# ------------------------------------------------------------
# Devuelve el mayor en una fila empezando de la diagonal
def maxRow(M, c):
  r = c #fila
  maximum = M[c][c]
  for i in range(c+1,len(M)):
    if(fabs(maximum) < fabs(M[c][i])):
      maximum = M[c][i]
      r = i
  return r

# ------------------------------------------------------------
# Maximo numero en una columna empezando debajo la diagonal
def maxColumDiag(M, c):
  r = c #fila
  maximum = M[c+1][c]
  for i in range(c+1,len(M)):
    if(fabs(maximum) < fabs(M[i][c])):
      maximum = M[i][c]
      r = i
  return r

# ------------------------------------------------------------
# Devuelve el mayor en una fila empezando derecha la diagonal
def maxRowDiag(M, c):
  r = c #fila
  maximum = M[c][c+1]
  for i in range(c+1,len(M)):
    if(fabs(maximum) < fabs(M[c][i])):
      maximum = M[c][i]
      r = i
  return r

# ------------------------------------------------------------
# intercambia las filas r1 y r2 de M
def exchangeRows(A, r1, r2):
  M = [row[:] for row in A]
  M[r1], M[r2] = M[r2], M[r1]
  return M

# ------------------------------------------------------------
# intercambia las columnas c1 y c2 de M
def exchangeCols(A, c1, c2):
  M = [row[:] for row in A]
  for k in range(len(M)):
    M[k][c1] , M[k][c2] = M[k][c2], M[k][c1]
  return M

# ------------------------------------------------------------
# Retorna el mayor elemento de la submatriz iniciada desde A[c][c]
def maxSubMatrix(M, c):
  row = c
  colum = c
  n = len(M)
  maximum = M[c][c]
  for j in range(c, n):
    for k in range(c, n):
      maxTemp = M[k][j]
      if(fabs(maximum) < fabs(maxTemp)):
        maximum = maxTemp
        colum = j
        row = k
  return row, colum

# ------------------------------------------------------------
# Privote de cualquier metodo
def pivot(a, P, Q, colum,s=[],piv=0):
  done=0
  if piv > 3 or piv < 0:
    exit('Valores invalidos para el parametro pivoteo, valores validos: 0, 1, 2, 3.')
  n = len(a)
  temp = a[colum][colum]
  if(temp == 0.0 and piv == 0): # sin pivot
    row_maxColumn = maxColum(a, colum)
    a = pivotP(a, row_maxColumn, colum)
    P = exchangeRows(P, row_maxColumn, colum)
    #print 'P(%d,%d)' % (row_maxColumn, colum)
    #printMatrix(rowsPermutMatrix(n, row_maxColumn, colum))
  elif piv == 1: # privoteo parcial
    row_maxColumn = maxColum(a, colum)
    if row_maxColumn != colum:
      a = pivotP(a, row_maxColumn, colum)
      P = exchangeRows(P, row_maxColumn, colum)
      #print 'P(%d,%d)' % (row_maxColumn, colum)
      #printMatrix(rowsPermutMatrix(n, row_maxColumn, colum))
  elif piv == 2: # pivoteo escalonado
    row_maxColumn = pivotE(a,colum,s)
    if row_maxColumn != colum:
      a = pivotP(a, row_maxColumn, colum)
      P = exchangeRows(P, row_maxColumn, colum)
      #print 'P(%d,%d)' % (row_maxColumn, colum)
      #printMatrix(rowsPermutMatrix(n, row_maxColumn, colum))
  elif piv == 3: # pivoteo total
    row, c = maxSubMatrix(a, colum)
    if (row != colum) or (c != colum) :
      a = pivotT(a, colum)
      P = exchangeCols(P, row, colum)
      Q = exchangeCols(Q, colum, c)
      #print 'P(%d,%d):' % (colum, row)
      #printMatrix(rowsPermutMatrix(n, row, colum))
      #print 'Q(%d,%d):' % (colum, c)
      #printMatrix(rowsPermutMatrix(n, c, colum))
  return 	a, P, Q

# ------------------------------------------------------------
# Privoteo Parcial
# Permuta la fila r1 con la fila r2 de la matriz M
def pivotP(M, r1, r2):
  return exchangeRows(M, r1, r2)

# ------------------------------------------------------------
# pivoteo escalonado
# escoge los maximos de cada fila
# y por medio de divisiones escoge el intercambio de filas
def pivotE(M,r,s):
  n = len(M)
  a = [0.]*n
  for i in range(r,n):
    a[i] = 1.*abs(M[i][r])/s[i]
  ai = a[0]
  index = 0
  for i in range(1,n):
    if a[i]>ai:
      ai = a[i]
      index = i
  return index

# ------------------------------------------------------------
# retorna las proporciones por fila
def escalPortion(M):
  n = len(M)
  s = [0.]*n
  aux = []
  for i in range(n):
    aux = []
    for j in range(n):
      aux.append(abs(M[i][j]))
    s[i] = max(aux)
  return s

# ------------------------------------------------------------
# Privoteo Total
# Busca el mayor elemento de la submatriz iniciada desde A[i][i] y permuta filas y columnas
def pivotT(M, i):
  r, c = maxSubMatrix(M, i)
  M = pivotP(M, i, r)
  return exchangeCols(M, c, i)

# ------------------------------------------------------------
# Calcula la matriz de permutacion de fila
def rowsPermutMatrix(n, r1, r2):
  #Matriz identidad
  I = [[float(i == j) for j in range(n)] for i in range(n)]
  return exchangeRows(I, r1, r2)

# ------------------------------------------------------------
# Calcula la matriz de permutacion de columna
def columsPermutMatrix(n, c1, c2):
  #Matriz identidad
  I = [[float(i == j) for j in range(n)] for i in range(n)]
  return exchangeCols(I, c1, c2)

# ------------------------------------------------------------
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
# Suma de matrices
def matrixSum(A,B):
  n = len(A)
  m = len(A[0])
  C = [[0. for row in range(n)] for col in range(m)]
  for i in range(n):
    for j in range(m):
      C[i][j] = A[i][j] + B[i][j]
  return C

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
# multiplicacion vector matrix
def multiVectorMatrix(A,x):
  c=[]
  col = len(x) # numero filas de b y numero de columnas de A
  row = len(A[0]) # numero de columnas de A
  if col!=len(A):
    exit('No tiene longuitudes igual')
  for i in range(row):
    suma=0.
    for j in range(col):
      suma += A[j][i]*x[j]
    c.append(suma)
  return c

# ------------------------------------------------------------
# conviete todo a float
def matrixToFloat(A):
  n=len(A)
  m=len(A[0])
  for i in range(n):
    for j in range(m):
      A[i][j] = float(A[i][j])
  return A

# ------------------------------------------------------------
# convierte un vector a float
def vectorToFloat(P):
  return [float(i) for i in P]

# ------------------------------------------------------------
# resta 2 filas, fila i = fila i - fila j*const
def susRowsMatrix(M,i,j,const):
  A = [row[:] for row in M]
  n = len(A[0])
  for m in range(n):
    A[i][m] = A[i][m] - const*A[j][m]
  return A

# ------------------------------------------------------------
# Suma 2 filas, fila i = fila i - fila j*const
def addRowsMatrix(M,i,j,const):
  A = [row[:] for row in M]
  n = len(A[0])
  for m in range(n):
    A[i][m] = A[i][m] + const*A[j][m]
  return A

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
# rotacion de matriz de givens
def rotmat(a,b):
  if b==0:
    c=1.
    s=0.
  elif abs(b)>abs(a):
    temp = 1.*a/b
    s = 1.0 / sqrt( 1.0 + temp*temp )
    c = temp * s
  else:
    temp = b / a
    c = 1.0 / sqrt( 1.0 + temp*temp )
    s = temp * c
  return c,s

# ------------------------------------------------------------
# reemplaza la columna i en la matrix
def replace(V,r,i):
  n=len(r)
  V = transMatrix(V)
  V[i] = r
  V = transMatrix(V)
  return V

# ------------------------------------------------------------
# aproxima mas la solucion
def iterRefinery(A,b,X,maxiter=100,tol=1e-7):
  n = len(b)
  for i in range(n):
    Ax = multiMatrixVector(A,X)
    r0 = [(b[z] - Ax[z]) for z in range(n)]
    y = gauss(A, r0,piv=0)
    XX = [ X[z] + y[z] for z in range(n) ]
    Xxx = [ X[z] - XX[z] for z in range(n) ]
    error = eucliNorm(Xxx)
    if error<tol or error == 0:
      return XX
    X = XX[:]
  return XX

# ------------------------------------------------------------
#	Resuelve la matriz superior U con el metodo de sustitucion inversa	
def solMatrixSup(U, b):
  x = []
  for i in range(len(U)-1,-1,-1):
    if(U[i][i]!=0):
      x.append((1.0/(U[i][i]))*(b[i]-sum(U[i][len(U)-j-1]*x[j] for j in range(len(x)))))
    else:
      x.append(0.0)
  x.reverse()
  return x

# ------------------------------------------------------------
#	Resuelve la matriz inferior L con el metodo de sustitucion inversa	
def solMatrixInf(L, b):
  x = []
  for i in range(len(L)):
    if(L[i][i]!=0):
      x.append((1.0/(L[i][i]))*(b[i]-sum(L[i][j]*x[j] for j in range(len(x)))))
    else:
      x.append(0.0)
  return x

# ------------------------------------------------------------
# Se usa para resolver la matriz superior generada por gauss y gauss-Jordan
def backSustitution(a):
  n = len(a)
  x = [0]*n
  for j in range(n-1, -1, -1):
    x[j] = (a[j][n] - sum(a[j][k]*x[k] for k in range(j+1, n)))/float(a[j][j])
  return x

# ------------------------------------------------------------
# Se usa para calcular el maximo elemento de una diagonal
def maxDiagon(A,i):
  n = len(A)
  maxim = A[i][i]
  index = i
  for p in range (i,n):
    if fabs(A[p][p])>maxim:
      maxim = A[p][p]
      index = p
  maxim = fabs(maxim)
  return maxim,index

# ------------------------------------------------------------
# Se usa para calcular el maximo elemento de una diagonal
def isPosSemiDef(A):
  n = len(A)
  for i in range(n):
    if i!=maxRow(A,i):
#      print "Debe ser aii el maximo"
      return False
    for j in range(n):
      if i!=j:
        if fabs(A[i][j])>(A[i][i]+A[j][j])/2:
#          print "debe ser <= que la media aritmetica"
          return False
        if fabs(A[i][j])>sqrt(A[i][i]*A[j][j]):
#          print "debe ser <= que la media geometrica"
          return False
      if A[i][i]==0:
        if A[i][j]!=0 and A[j][i]!=0:
          return False
  return True

# ------------------------------------------------------------
# dominancia de una matriz
def dominance(A):
  n=len(A)
  m=len(A[0])
  for j in range(n):
    dominancia = 0.0
    for i in range(j+1, m):
      if j != i:
        dominancia += fabs(A[i][j])
    if A[i][i] < dominancia:
      return False
  return True

# ------------------------------------------------------------
