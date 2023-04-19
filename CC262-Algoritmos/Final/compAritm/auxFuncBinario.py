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
