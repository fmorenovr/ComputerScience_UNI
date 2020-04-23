#!/usr/bin/env python
from math import *
from auxFuncRoots import *
from bisection import *
from brent import *
from secant import *
from newton import *
from newtonRaphson import *
from posFalse import *
from fixedPoint import *
from steffensen import *
from ridder import *
from halley import *
from householderRoots import *

# ------------------------------------------------------------
# use esta funcion de prueba
def f(x):
  return x*x*x - 2*x - 10

def g(x):
  return (x*2 + 10)/x/x

# ------------------------------------------------------------
# buscar raices
a,b = rootSearch(f,-10,10,0.5,printText=1)
# bisection
print "\nMetodo Bisection"
print bisection(f,a,b,switch=1)
# brent
print "\nMetodo Brent"
print brent(f,a,b,printText = 0)
# secant
print "\nMetodo Secant"
print secant(f,a,b,printText = 0)
# newton
print "\nMetodo de Newton"
print newton(f,d1f,a,printText=0)
# newton raphson
print "\nMetodo de Newton-Raphson"
print newtonRaphson(f,d1f,a,b,printText = 0)
# posicion falsa
print "\nMetodo Posicion Falsa o Falsa Regla"
print falseRule(f,a,b,printText =0)
# punto fijo
print "\nMetodo Punto Fijo"
print fixedPoint(g,a,printText = 0)
# steffensen
print "\nMetodo Steffensen"
print steffensen(g,a,printText = 0)
# ridder
print "\nMetodo de Ridder"
print ridder(f,a,b,printText = 0)
# halley
print "\nMetodo de Halley"
print halley(f, d1f,d2f, a,printText = 0)
# house holder ( error en la 3era derivada )
print "\nMetodo de Householder"
print householderRoots(f,d1f,d2f,d3f,a,printText = 0)
print
