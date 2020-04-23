#!/usr/bin/env python
from numpy import *
from random import *
from cmath import *
from auxFuncRoots import *
from muller import *
from iqi import *
from hornerRuffini import *
from laguerre import *
from bairstow import *
from jenkinsTraub import *
from durandKerner import *

# ------------------------------------------------------------
# use esta funcion de prueba
def f(x):
  return 1*x*x*x - 3*x*x + 3*x - 5

P = [1,-3,3,-5]

print "\nEvaluando el polinomio: 1x^3 - 3x^2 + 3x - 5"
# muller
print "\nMetodo de Muller"
print muller(f,0.5,-0.5,0.0,printText=0)
# iqi
print "\nInverse Quadratic Interpolation"
print iqi(f, 0.19, 2.7,printText = 0)
# horner Ruffini
print "\nMetodo de Horner Ruffini"
print hornerRuffini(P,0.9,printText=0)
# laguerre
print "\nMetodo de Laguerre"
print laguerre(P,printText=0)
# bairstow
print "\nMetodo de Bairstow"
print bairstow(P,printText=0)
# jenkins Traub
print "\nMetodo de Jenkins Traub"
print jenkinsTraub(P,printText=0)
# durand kerner
print "\nMetodo de Durand Kerner"
print durandKerner(P,printText=0)
print 
