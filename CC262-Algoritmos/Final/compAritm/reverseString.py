#!/usr/bin/python
# -*- encoding: utf-8 -*-

# funcion para invertir un string

def reverseString(name):

  rev_name=''
  for i in range(len(name)-1,-1,-1):
    rev_name+=name[i]

  return rev_name

def main():
  name = str(input('Introduce el string a invertir: '))
  print(reverseString(name))

main()
