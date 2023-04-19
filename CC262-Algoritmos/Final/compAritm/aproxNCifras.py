#!/usr/bin/python
# -*- encoding: utf-8 -*-

# x es el numero a methTruncar
# t es el numero de cifras a methTruncar

import math
import numToDecimal

def methRedond(num,t):
  if (num==0.0 or num ==0)or t==0:
    return num,
  else:
    bi,exp = numToDecimal.decToDec(num)
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
    bi,exp = numToDecimal.decToDec(num)
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

def main():
  for i in range(15):
    print str(methTrunc(0.0,i))+"\t"+str(i)
  print
  for i in range(15):
    print str(methRedond(12.43543,i))+"\t"+str(i)
  
  
  print str(methTrunc(0.0,-1))
  print str(methRedond(0.0,-1))
if __name__=="__main__":
  main()
