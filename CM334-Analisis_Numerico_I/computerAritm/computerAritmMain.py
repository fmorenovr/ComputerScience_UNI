#!/usr/bin/python
# -*- encoding: utf-8 -*-

# x es el numero a methTruncar
# t es el numero de cifras a methTruncar

import math
from auxFuncBinary import *

def main():
  '''
    parte 1: redondeo truncamiento
  '''
  for i in range(15):
    print str(methTrunc(0.0,i))+"\t"+str(i)
  print
  for i in range(15):
    print str(methRedond(12.43543,i))+"\t"+str(i)
  
  
  print str(methTrunc(0.0,-1))
  print str(methRedond(0.0,-1))

  '''
    parte 2: binario a decimal
  '''
  binario = raw_input('Introduce el número binario a convertir a decimal: ')
  binario = quitarZeros(binario)
  correcto = verificarBinario(binario)
  if correcto == 0:
    print("Error al ingresar, solo ingrese numero binarios\n\n")
    exit()
  print("Su resultado en decimal es: " + str(binToInteger(binario)))

  '''
    parte 3: cambio de base
  '''
  numero = int(input('Introduce el número a cambiar de base: '))
  base = int(input('Introduce la base: '))
  print(cambio_base(numero, base))
  
  '''
    parte 4: int a binario
  '''
  decimal = int(input('Introduce el número entero a convertir a binario: '))
  print(intToBinary(decimal))
  
  '''
    parte 5: decimal a decimal
  '''
  #  entero = int(input('Introduce el número entero a convertir a decimal: '))
  #  a,b = intToDec(entero)
  decimal = float(input('Introduce el número decimal 0<y<1 a convertir a decimal: '))
  c,d = decToDec(decimal)
  decimal1 = float(input('Introduce el número decimal >1 a convertir a decimal: '))
  e,f = decToDec(decimal1)

  #  print(str(a)+"x10^"+str(b))
  print(str(c)+"x10^"+str(d))
  print(str(e)+"x10^"+str(f))
  
  '''
    parte 6: real a binario
  '''
  real = float(input('Introduce el número real a convertir a binario: '))
  cifras = int(input('Introduce el número de cifras a mostrar en la fraccion: '))
  entero = int(real)
  fraccion=real-entero
  
  enteraString = intToBinary(entero)
  fraccionString = floatToBinary(fraccion,cifras)
  if entero==0:
    print('0.' + fraccionString)
  else:
    print(enteraString + '.' + fraccionString)
  
  '''
    parte 7: invertir cadena
  '''
  name = str(raw_input('Introduce el string a invertir: '))
  print(reverseString(name))


if __name__=="__main__":
  main()
