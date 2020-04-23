#!/usr/bin/env python
from math import *
from auxFuncSNLE import *

# -------------------------------------------------------
# 1.7 METODO DESCENSO GRADIENTE SISTEMA ECUACIONES NO LINEALES
def gradientDescentSNLE(F,x0,printText=1,tol=1e-16,nmaxiter=400):
  n = len(x0)
  x = x0[:]
  for itera in range(nmaxiter):
    g1 = objetiveFunction(F,x)
    z = objFuncGradient(F,x)
    z0 = eucliNorm(z)
    if z0 == 0:
      print "Gradiente cero!"
      return x
    z = [ 1*z[i]/z0 for i in range(n) ]
    alpha1 = 0.
    alpha3 = 1.
    x3 = [ x[i] - alpha3*z[i] for i in range(n) ]
    g3 = objetiveFunction(F,x3)
    while g3 >= g1:
      alpha3 = alpha3/2.
      x3 = [ x[i] - alpha3*z[i] for i in range(n) ]
      g3 = objetiveFunction(F,x3)
      if alpha3 < tol/2.:
        print "resultado poco probable"
        return x
    alpha2 = alpha3/2.
    x2 = [ x[i] - alpha2*z[i] for i in range(n) ]
    g2 = objetiveFunction(F,x2)
    h1 = 1.*(g2 - g1)/(alpha2 - alpha1)
    h2 = 1.*(g3 - g2)/(alpha3 - alpha2)
    h3 = 1.*(h2 - h1)/(alpha3 - alpha1)
    # interpola el polinomio P(a) = g1 + h1.a + h3.a.(a - alpha2)
    # que interpola en h(a) en a = 0, a = aplha2, a = alpha3
    alpha0 = 0.5*(alpha2 - h1/h3)
    x1 = [ x[i] - alpha0*z[i] for i in range(n) ]
    g0 = objetiveFunction(F,x1)
    if g0<g3:
      alpha = alpha0
    elif g0>g3:
      alpha = alpha3
    xaux = [ x[i] - alpha*z[i] for i in range(n) ]
    g = objetiveFunction(F,xaux)
    if abs(g - g1) < tol:
      return x
    if printText:
      print "x0 = %s"%x
      print "g(x) = "+str(objetiveFunction(F,x))
    x = xaux[:]
  print "No fueron suficientes iteraciones"
  return None

# -------------------------------------------------------
