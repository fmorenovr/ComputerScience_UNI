# ------------------------------------------------------------	

# METODOS NUMERICOS DE RESOLUCION DE SISTEMAS DE ECUACIONES LINEALES

#  METODOS DESCOMPOSICION QR

# ------------------------------------------------------------	
# MATRIZ REGULAR = MATRIZ NO SINGULAR = MATRIZ INVERTIBLE
# MATRIZ ORTONORMAL = Q
# Qt.Q = I

# si A es nxm: n(filas) y m(columnas)
#  Q es nxm, R = mxm y Qt.Q = I ( que es  nxn )
# 1.
#   si n>=m: ( householder, givens )
#    A = [Q1,Q2]|R1| == Q1.R1
#               | 0|

# 2.
#   si m>n: ( gram schmidt )
#    se usa la transpuesta
#    At = Q.| R| = [Q1, Q3]| R|
#           | 0|           | 0|
#    A = [Rt 0].|Q1t| = [Rt 0 ].Qt
#               |Q2t|
#     x tiene dimension m y b dimension m
#     Ax=b ==>  QAx=Qb ===>  Rx = Qb
#     sea R de rango = m y Qb rango m ===> solucion unica
#     R rango <m 


# Las matries se pueden descomponer en matrices ortonormales y triangulares
# A=QR
# Q es ortonormal, R es triangular superior, de rango incompleto o completo

# 1. Metodos de Descomposicion QR
#   1.1: Gram-Schmidt
#     Este metodo transforma la Matriz A en una matriz ortonormal Q / Q.Qt=I
#     y Qt.A = R, donde R es una matriz triangular superior

#   1.2: HouseHolder
#     Este metodo, busca una transformacion lineal tal que un vector x sea colineal a e1
#     generalmente la proyeccion se usa con angulos de 45 grados,
#     a diferencia de gram-schmidt que usa 90.
#     u = x - @e1, x es el primer vector columna de una matriz A, e1 = (1,0,0,...)t
#     v = u/|u|, @ = |x|
#     Q = I - 2*v.vt o Q = I - (1+w)v.vt, donde w=(x*)v/(v*)x,
#     donde (x*) es transpuesta conjugada de x
#     Qx = (b,0,0,...)t
#     y si no lo hace a la primera, se vuelve a hacer la misma operacion
#     con la siguiente vector columna empezando de la diagonal
#     haciendo Q = Q1t*Q2t ...
#     hasta que Q*A = R, donde R es triangular superior

#   1.3: Givens
#     Este metodo consiste en rotaciones del plano, es tal que encontrar 
#     1...0...0...0
#     0...c..-s...0
#     0...s...c...0
#     0...0...0...1
#     donde c=cosx y s=senx, donde G(i,j,x) es la rotacion del plano
#     haciendo ceros, los valores de las columnas
