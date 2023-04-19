#!/usr/bin/python
# -*- encoding: utf-8 -*-

# la liea de arriba sirve para decirle que acepte caracteres UTF-8


def cambio_base(decimal, base):
    conversion = ''
    while decimal // base != 0:
        conversion = str(decimal % base) + conversion
        decimal = decimal // base
    return str(decimal) + conversion

def main():

  numero = int(input('Introduce el número a cambiar de base: '))
  base = int(input('Introduce la base: '))
  print(cambio_base(numero, base))
  
main()
