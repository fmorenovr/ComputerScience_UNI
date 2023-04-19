#!/usr/bin/python
# -*- encoding: utf-8 -*-

import auxFuncBinario
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
    num = auxFuncBinario.addZerosLeft(num,exp*-1)
    for i in range(len(num)):
      dec = dec + float(num[i])*(2**-(i+1))
  return dec


def main():
  real = float(input('Introduce el número a convertir a binario: '))
  cifras = int(input('Introduce el número de cifras a mostrar: '))
  print("0." + floatToBinary(real,cifras))
  
  print str(binaryToFloat("111",-3))
  print binaryToFloat("1100010101010101010101",3)

if __name__ == "__main__":
  main()
