#!/usr/bin/env python
from math import *
from auxFuncRoots import *

# ------------------------------------------------------------
# 1.5 METODO DE NEWTON RAPHSON
def newtonRaphson(f,d1f,a,b,printText = 1,tol=1e-9):
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
  fa = f(a)
  fb = f(b)
  x = 0.5*(a+b)
  for i in range(30):
    fx = f(x)
    if printText:
      print "a=%s\tb=%s\tc=%s\tf(c)=%s"%(a,b,x,f(x))
    if abs(fx)<tol:
      return x
    if fa*fx< 0.0:
      b = x
    else:
      a = x
      fa = fx
    dfx = d1f(f,x)
    try: dx = -fx/dfx
    except ZeroDivisionError: dx = b - a
    x = x + dx
    if (b-x)*(x-a) < 0.0:
      dx = 0.5*(b-a)
      x = a + dx
    if abs(dx) < tol*max(abs(b),1.0):
      return x
  print("No fueron suficientes irteraciones")
  return None

# ------------------------------------------------------------
