#!/usr/bin/env python
from numpy import *
from random import *
from cmath import *
from auxFuncRoots import *

# ------------------------------------------------------------
# 1.2 METODO DE INVERSE QUADRATIC INTERPOLATION (IQI)
# probar
# iqi(g,0.39,1.57)
# a = 0.39
# b = 1.57
def iqi(f, a, b,printText = 1, tol=1.0e-7, maxiter= 100):
  if a>=b:
    print("Error, a > b")
    return False
  if f(a)==0:
    return a
  elif f(b) ==0:
    return b
  elif f(a)*f(b) > 0:
    print("f(a) y f(b) son del mismo signo")
    return False
  x0 = a
  fx0 = f(a)
  x1 = b
  fx1 = f(b)
  x2   = a + (b-a)*0.5
  fx2   = f(x2)
  fasign = (fx0 < 0.0)
  switch = True
  # controla cuando se hara interpolacion o biseccion
  for i in range(maxiter):
    if printText:
      print "x2=%s\tfx2=%s\ta=%s\tb=%s\tfx0=%s\tfx1=%s"%(x2, fx2,a, b, fx0, fx1)
    if abs(fx0-fx1)<tol or abs(fx1-fx2)<tol or abs(fx2-fx0)<tol:
      # si sucede esto, se hace bisection
      if switch:
        switch = not switch
    if switch:
      # Realiza la interpolacion cuadratica
      root = invQuadraticInterpolation(x0, x1, x2,fx0, fx1, fx2)
    else:
      # o realiza la biseccion
      root = a + (b-a) * 0.5
    switch = not switch
    froot= f(root)
    if printText:
      print "root = %s\tf(root) = %s"%( root, froot )
    if abs(froot) < tol:
      return root
    if (froot < 0) == fasign:
      x0 = root
      fx0 = froot
      a = root
    else:
      x1 = root
      fx1 = froot
      b = root
    x2   = a + (b-a)*0.5
    fx2   = f(x2)
    if abs(b-a) < tol:
      return x2
  print "Excedio el numero de iteraciones"
  return None

# ------------------------------------------------------------
# aproxima la raiz desde los 3 puntos de la parabola (root,0)
def invQuadraticInterpolation(x0, x1, x2,fx0, fx1, fx2):
    return x0 *fx1 *fx2/((fx0-fx1)*(fx0-fx2)) + x1 *fx0 *fx2/ ((fx1-fx0)* (fx1-fx2)) + x2*fx0 *fx1/((fx2 - fx0)* (fx2 - fx1))

# ------------------------------------------------------------
