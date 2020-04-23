#!/usr/bin/env python
from math import *
from auxFuncRoots import *

# ------------------------------------------------------------
# 1.6 METODO DE POSICION FALSA
def falseRule(f,a,b,printText = 1,tol=1e-9,NMAX=100):
  ya = f(a)
  yb = f(b)
  if a>=b:
    print("Error, a > b")
    return None
  if f(a)==0:
    return a
  elif f(b) ==0:
    return b
  elif f(a)*f(b) > 0:
    print("f(a) y f(b) son del mismo signo")
    return None
  n=1
  KL = 0
  KR = 0
  while n<=NMAX:
    c = a - ya*(b-a)/(yb-ya)    
    yc = f(c)
    if printText:
      print "a=%s\tb=%s\tc=%s\tf(c)=%s"%(a,b,c,f(c))
    if abs(c - a)<tol:
      return c
    if ya*yc<0:
      b = c
      yb = yc
      KR = 0
      KL = KL + 1
      if KL>1:
        ya = ya/2.
    else:
      a = c
      ya = yc
      KL = 0
      KR = KR + 1
      if KR > 1:
        yb=yb/2.
  print("No fueron suficientes iteraciones")
  return None

# ------------------------------------------------------------
