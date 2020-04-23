#!/usr/bin/env python
from math import *
from cmath import *
from numpy import *
from random import *
# ------------------------------------------------------------

#   FUNCIONES DE AYUDA

# ------------------------------------------------------------
# busqueda de ceros en una funcion, incrementando dx en dx
# y cuando haya un cambio de signo, en ese intervalo esta el cero
def rootSearch(f,a,b,dx,printText=0):
  x1 = a
  f1 = f(a)
  x2 = a + dx
  f2 = f(x2)
  if dx == 0:
    print("Eliga una variacion > 0")
    return False,False
  if x1 >=b:
    print("Intervalo incorrecto")
    return False,False
  while f1*f2>0.:
    if printText==0:
      print "X1=%s\tX2=%s"%(x1,x2)
    x1 = x2
    f1 = f2
    x2 = x1 + dx
    f2 = f(x2)
    if x2 > b:
      print("se excedio del intervalo")
      return False,False
  return x1,x2

# ------------------------------------------------------------
# imprime todas las raices de un intervalo
# usar allRootsFind(f,0.0,20.0,0.01)
def allRootsFind(f,a,b,dx):
  print 'Las raices son: '
  roots = []
  while 1:
    x1,x2 = rootSearch(f,a,b,dx,1)
    if type(x1)!=bool:
      a=x2
      root = bisection(f,x1,x2,1)
      if type(root)!=bool:
        print root
        roots = roots + [root]
    else:
      print '\nDone\n'
      break
  if len(roots)==0:
    print 'No hay raices en este intervalo'
    return False
  return roots

# ------------------------------------------------------------
# Funcion ejemplo
def f(x):
#  return -1 + 10*x + 6*x*x + x*x*x
  return x-tan(x)  

# ------------------------------------------------------------
# Primera derivada
def d1f(f,x,h=1e-6):
  return (f(x+h)-f(x-h))/(2*h)

# ------------------------------------------------------------
# Segunda derivada
def d2f(f,x,h=1e-6):
  h2=h*h
  return (f(x+h)-2*f(x)+f(x-h))/h2

# ------------------------------------------------------------
# Tercera derivada
def d3f(f,x,h=1e-6):
  h3 = h*h*h
  return (f(x+2*h) + 3*f(x+h) - 3*f(x-h) - f(x-2*h)) / (2*h3)

# ------------------------------------------------------------
# Cuarta derivada
def d4f(f,x,h=1e-6):
  h4 = h*h*h*h
  return (f(x+2*h) - 4*f(x+h) + 6*f(x) - 4*f(x-h) + f(x-2*h))/h4

# ------------------------------------------------------------
# evalua el polinomio en un valor X por el metodo de horner
def horner(P,x0):
  Px0=0
  for i in P:
    Px0 = Px0*x0+i
  return Px0

# ------------------------------------------------------------
# metodo de ruffini determina P(x) = (x-x0)*Q(x) + r
# division de polinomios entre un (x-x0)
def ruffini(P,x0):
  n = len(P)
  Q = []
  Px0 = P[0] + 0.0 + 0.0j
  Q = Q + [P[0] + 0.0 + 0.0j]
  for j in range(1,n-1):
    Px0 = x0*Px0 + P[j] # calcula y = b0 = P(x0)
    Q = Q + [Px0] # agrego los coeficientes de Q(x)
  r = Px0*x0 + P[n-1]
  return Q,r

# ------------------------------------------------------------
# P = P[0]X**n + ... + P[n-2]X + P[n-1]
# P es el vector de coeficientes
# determina P(x0), P'(x0) y P''(x0)
def evalPoly(P,x0):
  n = len(P)
  Px0 = P[0] + 0.0 + 0.0j
  dPx0 = 0.0 + 0.0j
  ddPx0 = 0.0 + 0.0j
  for j in range(1,n):
    ddPx0 = x0*ddPx0 + 2.0*dPx0 # calcula P''(x0)
    dPx0 = x0*dPx0 + Px0 # calcula P'(x0) = Q(x0)
    Px0 = x0*Px0 + P[j] # calcula y = b0 = P(x0)
  return Px0,dPx0,ddPx0

# ------------------------------------------------------------
# acota las raices de un polinomio
def acotRoots(P):
  x1=1+float(normaInfVector(P))/abs(P[0])
  return -x1,x1

# ------------------------------------------------------------
# Suma de polinomios
def sumPoly(P,Q):
  n=len(P)
  m=len(Q)
  maximum = max(n,m)
  R = [0.]*maximum
  if n==m:
    for i in range(n):
      R[i] = P[i]+Q[i]
  else:
    minimum = min(n,m)
    dif = maximum - minimum
    if n==maximum:
      for i in range(dif):
        R[i] = P[i]
      for i in range(minimum):
        R[i+dif] = P[i+dif] + Q[i]
    else:
      for i in range(dif):
        R[i] = Q[i]
      for i in range(minimum):
        R[i+dif] = P[i] + Q[i+dif]
  return R

# ------------------------------------------------------------
# Diferencia de polinomios
def difPoly(P,Q):
  n=len(P)
  m=len(Q)
  maximum = max(n,m)
  R = [0.]*maximum
  if n==m:
    for i in range(n):
      R[i] = P[i]-Q[i]
  else:
    minimum = min(n,m)
    dif = maximum - minimum
    if n==maximum:
      for i in range(dif):
        R[i] = P[i]
      for i in range(minimum):
        R[i+dif] = P[i+dif] - Q[i]
    else:
      for i in range(dif):
        R[i] = Q[i]
      for i in range(minimum):
        R[i+dif] = P[i] - Q[i+dif]
  return R

# ------------------------------------------------------------
# obtiene el polinomio de cauchy del polinomio
def cauchyPol(P):
  first_idx = 0
  last_idx = len(P) - 1
  size = len(P)
  cauchy = []
  normalize = False
  norm_const = 0
  for i in range(size):
    if i == first_idx:
      val = P[i]
      if val !=1:
        normalize = True
        norm_const = val
      cauchy.append(1)
    elif i == last_idx:
      val = P[i]
      if normalize:
        val /= (1.0*norm_const)
      val = -abs(val)
      cauchy.append(val)
    else:
      val = P[i]
      if normalize:
        val /= (1.0*norm_const)
      val = abs(val)
      cauchy.append(val)
  return cauchy

# ------------------------------------------------------------
def s_initial(P):
  cauchy_poly = cauchyPol(P)
  err = 1.e-6
  x0 = uniform(0,1)
  beta = hornerRuffini(cauchy_poly,x0,printText=0,tol = err)
  rand = uniform(0,1)*2*pi
  return abs(beta) * exp(1j*rand)

# ------------------------------------------------------------
# Resuelve el sistema de ecuaciones diferenciales formado
def systemJacobian(c,d,g,h,r,s):
  dr = -c*h + g*d
  ds = -g*s*c + g*r*d - h*d
  deno = s*g*g + h*h - h*r*g
  dr = dr/deno
  ds = ds/deno
  return dr,ds

# ------------------------------------------------------------
# calcula el nuevo polinomio resultante de una division cuadratica
# y ademas calcula el polinomio residuo
def quotientRemainder(P,r,s):
  n = len(P)
  Paux = [P[i] for i in range(n-1,-1,-1)]
  b = [0.]*n
  b[n-1] = b[n-2] = 0
  for i in range(n-3,-1,-1):
    b[i] = Paux[i+2] + r*b[i+1] + s*b[i+2]
  c = Paux[1] + r*b[0] + s*b[1]
  d = Paux[0] + s*b[0]
  Q = [b[i] for i in range(n-1,-1,-1)]
  return Q,c,d

# ------------------------------------------------------------
# encuentra el minimo local de una funcion partiendo de un punto inicial
def localMinimum(f,a,gamma,printText=1,nmaxiter=100,tol = 1e-7):
  x0 = a
  for itr in range(nmaxiter):
    x1 = x0 - gamma * d1f(f,x0)
    if abs(x1 - x0) < tol:
      return x1
    if printText:
      print "x0=%s\tx1=%s\tf(x0)=%s"%(x0,x1,f(x0))
    x0 = x1
  print "No fueron suficientes iteraciones"
  return None

# ------------------------------------------------------------
