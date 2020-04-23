#!usr/bin/env python
from auxFuncSLE import *
from householder import *
from givens import *
from gramSchmidt import *

A=[[12,-51,4],[6,167,-68],[-4,24,-41]]

# gramSchmidt
print "\nMetodo Gram Schmidt"
Q,R = gramSchmidt(A)
print "\tMatrix Q"
printMatrix(Q)
print "\tMatrix R"
printMatrix(R)
# householder
print "\nMetodo Householder"
Q,R = householder(A)
print "\tMatrix Q"
printMatrix(Q)
print "\tMatrix R"
printMatrix(R)
# givens
print "\nMetodo Givens"
Q,R = givens(A)
print "\tMatrix Q"
printMatrix(Q)
print "\tMatrix R"
printMatrix(R)
print
