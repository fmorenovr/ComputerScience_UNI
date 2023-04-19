# -*- encoding: utf-8 -*-

# conversion de un numero entero a binario

'''
-*- coding: latin-1 -*-
-*- coding: iso-8859-15 -*-
-*- coding: ascii -*-

'''

import auxBinario  

def binToInteger(bina):
  pow_ = 1
  decimal = 0
  binlist = list(bina)
  while binlist:
    cifra = int(binlist.pop())
    decimal = decimal + cifra * pow_
    pow_ *= 2
  return decimal


def main():
  '''
  Ejemplo de uso
  '''
  binario = input('Introduce el número a convertir a decimal: ')
  binario = auxBinario.quitarZeros(binario)
  correcto = auxBinario.verificarBinario(binario)
  if correcto == 0:
    print("Error al ingresar, solo ingrese numero binarios\n\n")
    exit()
  print("Su resultado en decimal es: " + str(binToInteger(binario)))

if __name__ == "__main__":
  main()
