#!/usr/bin/python
# -*- encoding: utf-8 -*-

# conversion de un numero entero a binario

'''
-*- coding: latin-1 -*-
-*- coding: iso-8859-15 -*-
-*- coding: ascii -*-

'''

def quitarZeros(binario):
  for i in range(len(binario)):
    if binario[i] != '0':
      return binario[i:]
  return '0'

def verificarBinario(binario):
  for v in binario:
    if v not in '01':
      return 0
  return 1
  
def agregarZerosLeft(num,n):
  bina=str(num)
  i=len(bina)
  m=len(bina)
  while i<n:
    bina = '0' + bina
    i+=1
  return bina

def addZerosLeft(num,n):
  bina=str(num)
  i=len(bina)
  m=len(bina)
  while i<(n+m):
    bina = '0' + bina
    i+=1
  return bina

def agregarZerosRight(num,n):
  bina=str(num)
  i=len(bina)
  while i<n:
    bina = bina + '0'
    i+=1
  return bina
  
def oneExpBin(num):
  exp = 0
  count1 = 0
  numstr=str(num)
  binar='0'
  for i in numstr:
    binar = i
    if binar == '1':
      exp-=1
      break
    exp-=1
  return num[(-1*exp):],exp

def cambio_base(decimal, base):
  conversion = ''
  while decimal // base != 0:
    conversion = str(decimal % base) + conversion
    decimal = decimal // base
  return str(decimal) + conversion

def methRedond(num,t):
  if (num==0.0 or num ==0)or t==0:
    return num,
  else:
    bi,exp = decToDec(num)
    n=len(bi)-2
    t1 = t-1
    x=bi[2:]
    cad = bi[2:]
    if n>t:
      a = int(cad[t1])
      if int(cad[t])>=5:
        a +=1
        if a==10:
          b= int(x[t1]) + 1
          a=0
          cad = x[:t1-1] + str(b) +str(a)
        else:
          cad = x[:t1] + str(a)
      return cad[:t],exp
    else:
      return cad,exp

def methTrunc(num,t):
  if num==0.0 or t==0:
    return num
  else:
    bi,exp = decToDec(num)
    cad = bi[2:]
    n = len(bi)-2
    if n>t:
      return cad[:t],exp
    else:
      return cad,exp

'''
def methTrunca(x,t):
	if x==0:
		return 0
	else:
		e=math.trunc(math.log10(math.fabs(x)))
		if e>0:
			e=e+1
		x2=math.trunc(x*(10**(t-e)))*(10**(e-t))
	return x2
'''

def Pi(t):
	pi=0.0
	i=0
	while(i<t*100):
		pi=pi+((-1.0)**i)/(2.0*i+1.0)
		i=i+1
	return pi*4.0

def Euler(t):
	e=0.0
	i=0
	while(i<t):
		e=e+1.0/math.factorial(i)
		i=i+1
	return e

# conversion de un numero entero a binario

def floatToBinary(real,cifras):
  binario = ''
  i=0
  while i<cifras:
    real = real*2
    partEntera = int(real)
    real = real-int(real)
    binario = binario + str(partEntera)
    i=i+1
  return binario

def binaryToFloat(num,exp):
  dec = 0.0
  num = str(num)
  if exp>0:
    expb = exp-1
    for i in range(exp):
      dec = dec + float(num[i])*(2**(exp - 1 - i))
    for i in range(len(num[exp:])):
      dec = dec + float(num[i+exp])*(2**-(i+1))
  elif exp ==0:
    pass
  else:
    num = addZerosLeft(num,exp*-1)
    for i in range(len(num)):
      dec = dec + float(num[i])*(2**-(i+1))
  return dec

def binToInteger(bina):
  pow_ = 1
  decimal = 0
  binlist = list(bina)
  while binlist:
    cifra = int(binlist.pop())
    decimal = decimal + cifra * pow_
    pow_ *= 2
  return decimal

def intToBinary(decimal):
  decimal=int(decimal)
  binario = ''
  while decimal!= 0:
    binario = str(decimal % 2) + binario
    decimal = decimal // 2
  return binario

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

def intToDec(decimal):
  if decimal ==0 or decimal==0.0:
    return 0.0
  else:
    binario = ''
    exp = 0
    dec=1
    auxdecimal = decimal
    while auxdecimal!=0:
      dec*=10
      exp+=1
      auxdecimal = auxdecimal //10
    decimal = float(decimal)/dec
    binario = str(decimal)
    return binario,exp


def decToDec(decimal):
  if decimal ==0 or decimal==0.0:
    return 0.0,0
  else:
    binario = ''
    auxdecimal = decimal
    if auxdecimal>0 and auxdecimal<1:
      exp = 0
      dec=1.0
      while auxdecimal<1:
        if auxdecimal *10>1:
          break
        dec/=10
        exp-=1
        auxdecimal = auxdecimal*10
    else:
      exp = 0
      dec=1.0
      auxdecimal = decimal
      while auxdecimal!=0:
        dec*=10
        exp+=1
        auxdecimal = auxdecimal //10
    decimal = decimal/dec
    binario = str(decimal)
    return binario,exp

def reverseString(name):

  rev_name=''
  for i in range(len(name)-1,-1,-1):
    rev_name+=name[i]
  return rev_name


