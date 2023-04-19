#!/usr/bin/python
# -*- encoding: utf-8 -*-

# conversion de un numero entero a binario


'''
-*- coding: latin-1 -*-
-*- coding: iso-8859-15 -*-
-*- coding: ascii -*-

'''

def intToBinary(decimal):
  decimal=int(decimal)
  binario = ''
  while decimal!= 0:
    binario = str(decimal % 2) + binario
    decimal = decimal // 2
  return binario

def main():
  decimal = int(input('Introduce el número a convertir a binario: '))
  print(intToBinary(decimal))
  

if __name__ == "__main__":
  main()
