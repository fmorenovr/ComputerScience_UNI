#!/usr/bin/python
# -*- encoding: utf-8 -*-

# conversion de un numero entero a binario


'''
-*- coding: latin-1 -*-
-*- coding: iso-8859-15 -*-
-*- coding: ascii -*-

'''

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

def main():
#  entero = int(input('Introduce el número entero a convertir a decimal: '))
#  a,b = intToDec(entero)
  decimal = float(input('Introduce el número decimal 0<y<1 a convertir a decimal: '))
  c,d = decToDec(decimal)
  decimal1 = float(input('Introduce el número decimal >1 a convertir a decimal: '))
  e,f = decToDec(decimal1)

#  print(str(a)+"x10^"+str(b))
  print(str(c)+"x10^"+str(d))
  print(str(e)+"x10^"+str(f))

if __name__ == "__main__":
  main()
