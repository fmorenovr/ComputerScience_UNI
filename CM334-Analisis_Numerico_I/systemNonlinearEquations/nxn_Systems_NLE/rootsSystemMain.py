#!/usr/bin/env python
from math import *
from auxFuncSNLE import *
from newtonRaphsonSystem import *
from newtonJacobi import *
from newtonGaussSeidel import *
from newtonSor import *
from broyden import *
from fixedPointSystem import *
from gradientDescentSNLE import *
from homotopyContinuation import *

def f(x):
  n = len(x)
  f = [ 0. for i in range(n)]
  f[0] = 3*x[0] - cos(x[1]*x[2]) - 0.5
  f[1] = x[0]*x[0] - 81*(x[1] + 0.1)*(x[1] + 0.1) + sin(x[2]) + 1.06
  f[2] = exp(-x[0]*x[1]) + 20*x[2] + 10*pi/3 - 1
  return f


def g(x):
  n = len(x)
  g = [ 0. for i in range(n)]
  g[0] = cos(x[1]*x[2])/3. + 1/6.
  g[1] = sqrt(x[0]*x[0] + sin(x[2]) + 1.06)/9. - 0.1
  g[2] = -exp(-x[0]*x[1])/20. - pi/6 + 1/20.
  return g

x0 = [.1,.1,-.1]
# metodo de newton
print "\nMetodo de Newton Generalizado"
print newtonRaphsonSystem(f,x0,printText = 0)
# metodo newton jacobi
print "\nMetodo de Newton Jacobi"
print newtonJacobi(f,x0,printText=0)
# metodo newton gauss seidel
print "\nMetodo de Newton Gauss Seidel"
print newtonGaussSeidel(f,x0,printText=0)
# metodo newton sor
print "\nMetodo de Newton SOR"
print newtonSor(f,x0,w=1.25,printText=0)
# broyden
print "\nMetodo de Broyden"
print broyden(f,x0,printText=0)
# punto fijo
print "\nMetodo de Fixed Point generalizado"
print fixedPointSystem(g,x0,printText = 0)
# Descenso Gradiente
print "\nMetodo del Descenso Gradiente"
print gradientDescentSNLE(f,x0,printText=0)
# Homotopia y continuacion
print"\nMetodo Homotopia"
print homotopyContinuation(f,x0,printText=0)
print
