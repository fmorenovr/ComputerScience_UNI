#!/usr/bin/env python
from math import *
from auxFuncRoots import *

# ------------------------------------------------------------
# 1.9 METODO DE RIDDER
def ridder(f,a,b,printText = 1,tol=1.0e-9):
  if a>=b:
    print("Error, a > b")
    return None
  fa = f(a)
  if fa == 0.0:
    return a
  fb = f(b)
  if fb == 0.0:
    return b
  if fa*fb > 0.0:
    print("f(a) y f(b) son del mismo signo")
    return None
  for i in range(30):
    # Compute the improved root x from Ridder's formula
    c = 0.5*(a + b)
    fc = f(c)
    if printText:
      print "a=%s\tb=%s\tc=%s\tf(c)=%s"%(a,b,c,f(c))
    s = sqrt(fc**2 - fa*fb)
    if s == 0.0:
      return None
    dx = (c - a)*fc/s
    if (fa - fb) < 0.0: dx = -dx
    x = c + dx; fx = f(x)
    # Evalua la convergencia
    if abs(x - c) < tol*max(abs(x),1.0):
      return x
    # acerca a la raiz lo mas posible
    if fc*fx > 0.0:
      if fa*fx < 0.0:
        b = x
        fb = fx
      else:
        a = x
        fa = fx
    else:
      a = c
      b = x
      fa = fc
      fb = fx
  print("No fueron suficientes iteraciones")
  return None

# ------------------------------------------------------------
