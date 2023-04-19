#!/usr/bin/python
# -*- encoding: utf-8 -*-

import floatToBinario
import intToBinario

def main():
  real = float(input('Introduce el número a convertir a binario: '))
  cifras = int(input('Introduce el número de cifras a mostrar en la fraccion: '))
  entero = int(real)
  fraccion=real-entero
  
  enteraString = intToBinario.intToBinary(entero)
  fraccionString = floatToBinario.floatToBinary(fraccion,cifras)
  if entero==0:
    print('0.' + fraccionString)
  else:
    print(enteraString + '.' + fraccionString)

if __name__ == "__main__":
  main()
