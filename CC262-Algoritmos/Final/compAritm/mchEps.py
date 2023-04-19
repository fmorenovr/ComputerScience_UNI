#!/usr/bin/python
# -*- encoding: utf-8 -*-

def machineEpsilon():
  eps=1.0
  i=0
  while 1.0+eps>1.0:
    epsilon=eps
    eps=0.5*eps
  return epsilon
  
def machineArch(num):
  if num<2.221e-16 and num>2.220e-16 :
    return 64
  elif num<1.1921e-07 and num>1.1920e-07 :
    return 32
  elif num<9.77e-04 and num>9.76e-04:
    return 16
  else:
    exit("Arquitectura menor a 16 bits !!")

def machineFloatSet(m,t,b):
  # m numero de cifras del exponente
  # t num de cifras decimales
  # b base
  U = b**(m-1)-1
  L = 1 - U
  numMch = 2*(b-1)*(b**(t-1))*(U-L+1) + 1
  numMin = b**L
  numMax = (b - (b**-t)) * (b**U)
  interlon = b**-t
  return numMch,U,L,numMin,numMax,interlon

def machineDescription(numbits):
  if numbits == 64:
    mantislon = 52
    explon = 11
  elif numbits == 32:
    mantislon = 23
    explon = 8
  elif numbits == 16:
    mantislon = 10
    explon = 5
  return mantislon,explon
