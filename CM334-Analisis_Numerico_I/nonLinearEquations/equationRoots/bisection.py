#!/usr/bin/env python
from math import *
from auxFuncRoots import *

# ------------------------------------------------------------
# 1.1 METODO BISECCION
def bisection(f, a, b, switch = 0,tol=1e-9):
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
  n=int(ceil(log(abs(b-a)/tol)/log(2.0)))
  for i in range(n):
    c = (a+b)*0.5
    if switch==0:
      print "a=%s\tb=%s\tc=%s\tf(c)=%s"%(a,b,c,f(c))
    if (switch==1) and (abs(f(c)) > abs(f(a))) and (abs(f(c)) > abs(f(b))):
      return None
    if f(c)==0 or (b-a)/2.0 < tol:
      return c
    elif f(c)*f(a) < 0:
      b=c
    else:
      a=c
  print("No fueorn suficiente iteraciones")
  return None

# ------------------------------------------------------------
