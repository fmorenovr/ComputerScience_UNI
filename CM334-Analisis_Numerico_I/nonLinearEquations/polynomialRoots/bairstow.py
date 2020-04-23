#!/usr/bin/env python
from numpy import *
from random import *
from cmath import *
from auxFuncRoots import *

# ------------------------------------------------------------
# 1.5 METODO BAIRSTOW
# Probar P = [1,-3.7,6.2,-4.069]
def bairstow(P, r=0.1, s=0.1, printText=1,tol=1e-7,nmaxiter=100):
  for i in range(nmaxiter):
    b,c,d = quotientRemainder(P,-r,-s)
    f,g,h = quotientRemainder(b,-r,-s)
    dr, ds = systemJacobian(c,d,g,h,r,s)
    r1 = r - dr
    s1 = s - ds
    if printText:
      print "r=%s s=%s"%(r,s)
      print "dr=%s ds=%s"%(dr,ds)
    if ds < tol and dr < tol:
      r=r1
      s=s1
      break
    r=r1
    s=s1
  print "Terminaron las iteraciones"
  print "**********************************"
  print "evaluando el polinomio ",
  print "x*x + r*x + s = 0"
  print "**********************************"
  dis = r*r - 4*s + 0j
  x0 = (-1.*r + sqrt(dis))/2.
  x1 = (-1.*r - sqrt(dis))/2. 
  return x0,x1

# ------------------------------------------------------------
