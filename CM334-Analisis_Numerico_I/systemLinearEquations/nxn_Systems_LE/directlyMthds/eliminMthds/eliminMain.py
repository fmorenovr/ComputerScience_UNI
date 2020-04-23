#!usr/bin/env python
from auxFuncSLE import *
from gauss import *
from gaussJordan import *

piv = 2

A = [[2.11,-4.21,0.921],
     [4.01,10.2,-1.12],
     [1.09,0.987,0.832]]

b = [2.01,-3.09,4.21]

# gauss
print "\nMetodo Gauss Jordan"
X = gauss(A,b,piv)
print X
# gauss Jordan
print "\nMetodo Gauss Jordan"
X = gaussJordan(A,b,piv)
print X
print
