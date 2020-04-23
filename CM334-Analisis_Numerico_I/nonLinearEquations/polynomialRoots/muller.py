#!/usr/bin/env python
from numpy import *
from random import *
from cmath import *
from auxFuncRoots import *

# ------------------------------------------------------------
# 1.1 METODO DE MULLER
# probar muller(f,0.5,-0.5,0.0)
def muller(f, p0, p1, p2,printText=1,tol= 1e-5, max_iter=100):
  h1 = p1 - p0
  h2 = p2 - p1
  f_p1 = f(p1)
  f_p2 = f(p2)
  d1 = ( f_p1 - f(p0) ) / h1
  d2 = ( f_p2 - f_p1 ) / h2
  d = (d2-d1) / (h2+h1)
  i = 3
  while i <= max_iter:
    b = d2 + h2*d
    # sqrt, trabaja raice cuadradas de complejos
    # D es la discriminante
    D = sqrt(b*b - 4 * f_p2 *d + 0j)
    if abs(b-D) < abs(b+D):
      E = b+D
    else:
      E = b-D
    h = -2 * f_p2 / E
    p = p2 + h
    if abs(h) < tol:
      return p
    p0 = p1
    p1 = p2
    p2 = p
    h1 = p1 - p0
    h2 = p2 - p1
    f_p1 = f(p1)
    f_p2 = f(p2)
    if printText:
      f_p = f(p)
      print "p0= %.6f + %.6fj\tp1= %.6f + %.6fj\tp2= %.6f + %.6fj" % (p0.real,p0.imag,p1.real,p1.imag,p2.real,p2.imag)
      print "D= %f, p= %.6f + %.6fj, f=%.6f + %.6fj" % (D, p.real, p.imag,f_p.real,f_p.imag)
    d1 = ( f_p1 - f(p0) ) / h1
    d2 = ( f_p2 - f_p1 ) / h2
    d = (d2-d1) / (h2+h1)
    i += 1
  print "Excedio el numero de iteraciones"
  return None

# ------------------------------------------------------------
