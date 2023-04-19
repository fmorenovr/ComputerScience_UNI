#!/usr/bin/python
# -*- encoding: utf-8 -*-
import pygame as pg
import inputbox as ib
import compAritm
import compAritm.aproxNCifras
import compAritm.auxFuncBinario
import compAritm.floatToBinario
import compAritm.intToBinario
import compAritm.mchEps
import compAritm.numToDecimal
import sys
import math
import os

path = os.getcwd() + '/'

# para efectos descomentar las lineas 70-75, 340, 91, 125, 131, 237, 336, 272-279
# cambiar la direccion /home/jenazad/ por la direccion de usuario de su computadora
# linux:  /home/nombreusuario/
# windows C:/user/
# instalado pygame 

pg.init()
screen=pg.display.set_mode([1200,680])
# Colores
yellow = (255, 255, 0)
white=(255,255,255)
black=(0,0,0)
red=(255,0,0)
blue=(0,0,255)
green = (0,255,0)

# Clase cursor
class Cursor(pg.Rect):
  def __init__(self):
    pg.Rect.__init__(self,0,0,1,1)
  def update(self):
    self.left,self.top = pg.mouse.get_pos()

# Clase boton
class Boton(pg.sprite.Sprite):
  def __init__(self,imagen1,imagen2,x,y):
    self.imagen_normal = imagen1
    self.imagen_seleccion = imagen2
    self.imagen_actual = self.imagen_normal
    self.rect = self.imagen_actual.get_rect()
    self.rect.left,self.rect.top=(x,y)
  def update(self,pantalla,cursor):
    if cursor.colliderect(self.rect):
      self.imagen_actual = self.imagen_seleccion
    else: self.imagen_actual = self.imagen_normal
    pantalla.blit(self.imagen_actual,self.rect)

# Clase Label
class Label(pg.sprite.Sprite):
  """ Label Class (simplest version) 
      Attributes:
          font: any pg Font or SysFont objects
          text: text to display
          center: desired position of label center (x, y)
  """
  def __init__(self):
    pg.sprite.Sprite.__init__(self)
    self.font = pg.font.Font(None, 35)
    self.text = ""
    self.color = (0,0,0)
    self.center = ((screen.get_width()/2),(screen.get_height()/2)) # centro de la palabra

  def update(self):
    self.image = self.font.render(self.text, 0, self.color)
    self.rect = self.image.get_rect()
    self.rect.center = self.center

def mainScreen():
# Inicio
  pg.display.set_caption("Examen Parcial Analisis Numerico I")
  pg.mixer.music.load(path+"extras/Topgear.mp3")
  pg.mixer.music.play(0)

  azul1 = pg.image.load(path+"extras/exit.png")
  azul2 = pg.image.load(path+"extras/exit1.png")
  imagenfondo1 = pg.image.load(path+"extras/fondo1.jpg")

  clock=pg.time.Clock()
  background = pg.Surface(screen.get_size())
  background.fill(white)
  screen.blit(background,(0,0))

  cursor1 = Cursor()

  '''
  label1 = Label()
  label2 = Label()
  labelEvent = Label()
  allSprites = pg.sprite.Group(label1,label2,labelEvent)
  '''

  boton = Boton(azul1,azul2,20,590)
  
  labelEvent = Label()
  labelEvent.center = (350,430)
  labelEvent.color = red
  labelEvent.center = (600,50)
  allSprites = pg.sprite.Group(labelEvent)
  '''
  label1.text = "Pregunta Numero 2"
  label1.center = (365,20)
  label1.color = (245,164,8)
  
  label2.text = "Almacenamiento en memoria"
  label2.center = (360,50)
  label2.color = (206,188,65)
  '''  

  numesp = compAritm.mchEps.machineEpsilon()
  numbits = compAritm.mchEps.machineArch(numesp)
#  numbits = 32
  mantislon,explon = compAritm.mchEps.machineDescription(numbits)
  numFlo,maxExp,minExp,minNum,maxNum,interlon = compAritm.mchEps.machineFloatSet(explon,mantislon,2)
  
  if numbits == 64:
    bitlon = 578
    numlon = 595
  elif numbits == 32:
    bitlon = 260
    numlon = 275
  elif numbits == 16:
    bitlon = 120
    numlon = 135

  pg.display.flip()
  screen.blit(imagenfondo1,(0,0))
  binario = ''
  binarioaux = ''
  isFloat = False

  while not isFloat:
#    screen.blit(imagenfondo1,(0,0))
    ib.printText(screen,"El Numero epsilon de Maquina es: "+str(numesp),30,10,198,(165,25,4))
    ib.printText(screen,"La arquitectura del Sistema es de: "+str(numbits)+" bits.",30,10,218,(165,25,4))
    ib.printText(screen,"El numero de elementos del conjunto de numeros maquina es: "+str(numFlo),30,10,238,(165,25,4))
    ib.printText(screen,"El min exponente es: "+str(minExp),30,10,258,(165,25,4))
    ib.printText(screen,"El max exponente es: "+str(maxExp),30,10,278,(165,25,4))
    ib.printText(screen,"El max numero representado es: "+str(maxNum),30,10,298,(165,25,4))
    ib.printText(screen,"El min numero representado es: "+str(minNum),30,10,318,(165,25,4))
    ib.printText(screen,"El intervalo entre 2 numeros del conjunto de numeros maquina es: "+str(interlon),30,10,338,(165,25,4))
    answer = ib.ask(screen,"Ingrese Numero: ",60,150)
    cad = answer[0]
    auxanswer = answer
    if cad=='-':
      answer = answer[1:]
      signnum = '1'
      posnega = "negativo"
    else:
      cad = '+'
      signnum = '0'
      posnega = "positivo"
    try:
      number = float(answer)
    except ValueError:
      ib.printText(screen,"Ingreso Erroneo !!",30,320,408,red)
      ib.printText(screen,"Ingrese un Numero !!!",30,320,428,red)
      pg.time.delay(1200)
      #screen.fill(white)
      screen.blit(imagenfondo1,(0,0))
    else:
      ib.printText(screen,"Ingreso Correcto !!",30,320,408,blue)
      isFloat = True
  
  # ----------------------------------------------------------------------------
  # Convirtiendo a Binario un entero, decimal o real
  if number == 0.0:
    binario = '0'
    binarioaux = '0'
    expbin1 = 0
    exp=0
  elif (number - int(number))==0.0: # Entero
    numberdec,exp = compAritm.numToDecimal.intToDec(number)
    number = int(number)
    # almacenamiento real
    binario = compAritm.intToBinario.intToBinary(number)
    # exponente binario
    expbin1 = len(binario) - 1
    # expresion binaria para la mantisa
    binarioaux = binario
    binario = binario[1:]
  else: # real
    numberdec,exp = compAritm.numToDecimal.decToDec(number)
    # calculo de los binario
    numberint = int(number)
    numberflo = number - numberint
    expbin1=0
    if numberint !=0: # decimal
      binaint = compAritm.intToBinario.intToBinary(numberint)
      expbin1 = len(binaint) - 1
      binario = binario + binaint
      binarioaux = binario
      binario = binario[1:]

    binarioflo = compAritm.floatToBinario.floatToBinary(float(numberflo),mantislon-expbin1)
    binario = binario + binarioflo
    binarioaux = binarioaux + binarioflo

    if expbin1==0:
      binario,expbin1 = compAritm.auxFuncBinario.oneExpBin(binario)
  # expresion binario final de la mantisa
  binario = compAritm.auxFuncBinario.agregarZerosRight(binario,mantislon)
  binario = binario[:mantislon]
  # expresion binaria del exponente
  expbinario = compAritm.intToBinario.intToBinary(expbin1+maxExp) # 110,335
  expbinario = compAritm.auxFuncBinario.agregarZerosLeft(expbinario,explon)
  # ----------------------------------------------------------------------------
  # rellenado de la parte decimal
  exponent = str(exp)
  if exp>=0:
    exponent = compAritm.auxFuncBinario.agregarZerosLeft(exponent,4)
    exponent = '+'+ exponent
  else:
    exponent = exponent[1:]
    exponent = compAritm.auxFuncBinario.agregarZerosLeft(exponent,4)
    exponent = '-'+exponent
  
  numberredon,expredon = compAritm.numToDecimal.decToDec(number)
  numberdecR,j = compAritm.numToDecimal.decToDec(float(numberredon))
  numberdecR = str(numberdecR)
  numstr = compAritm.auxFuncBinario.agregarZerosRight(numberdecR[2:],mantislon)
  numstr = cad + numstr
  # ----------------------------------------------------------------------------
  # la parte de transformacion a binario
  if number ==0:
    binariodec = binario
  else:
    binariodec = "1." + binario
  expbin1aux=0
  expbincero = str(expbin1)
  if expbin1>=0:
    expbin1aux=expbin1+1
    expbincero = '+' + expbincero
  else:
    expbin1aux = expbin1
  # ----------------------------------------------------------------------------
  binaerror = compAritm.floatToBinario.binaryToFloat(binarioaux,expbin1aux)
  pg.time.delay(1200)
  screen.fill(white)
  screen.blit(imagenfondo1,(0,0))
  # ---------------------------------------------------------------------------
  # Errores
  cifras = 10
  if binaerror == 0:
    numbertrunc = 0.0
    numberredon = 0.0
  else:
    numbertrunc,exptrunc = compAritm.aproxNCifras.methTrunc(binaerror,cifras)
    numberredon,expredon = compAritm.aproxNCifras.methRedond(binaerror,cifras)
    numbertrunc = str(numbertrunc)
    numberredon = str(numberredon)
    if expredon>0 and exptrunc>0:
      numbertrunc = numbertrunc[:exptrunc] +'.'+ numbertrunc[exptrunc:]
      numberredon = numberredon[:expredon] +'.'+ numberredon[expredon:]
    elif exptrunc<0 or expredon<0:
      numbertrunc = compAritm.auxFuncBinario.addZerosLeft(numbertrunc,exptrunc*-1)
      numberredon = compAritm.auxFuncBinario.addZerosLeft(numberredon,expredon*-1)
      numbertrunc = "0."+numbertrunc
      numberredon = "0."+numberredon
  if numbertrunc==0 and numberredon ==0:
    errorAbsT = 0
    errorRelT = 0
    errorAbsR = 0
    errorRelR = 0
  else:
    errorAbsT = float(math.fabs(number - float(numbertrunc)))
    errorRelT = errorAbsT/number
    errorAbsR = float(math.fabs(number - float(numberredon)))
    errorRelR = errorAbsR/number
  
  while True:
    for event in pg.event.get():
      if event.type == pg.QUIT:
        raise SystemExit
      if cursor1.colliderect(boton.rect):
        if event.type == pg.MOUSEBUTTONDOWN:
          pg.quit()
          salir = False
          sys.exit()
      elif event.type == pg.MOUSEMOTION:
        (mouseX, mouseY) = pg.mouse.get_pos()
        #ib.printText(screen,"mouse: (%d, %d)" % (mouseX, mouseY),30,750,50,red)

    allSprites.clear(screen, background)
    allSprites.update()
    allSprites.draw(screen)
    ib.printText(screen,"Pregunta Numero 2",35,250,10,(245,164,8))
    ib.printText(screen,"Almacenamiento en memoria",35,175,50,(206,188,65))
    ib.printText(screen,"Simula el almacenamiento en una memoria de "+str(numbits)+" bits",30,20,90,(100,200,86))
    
    ib.drawMemorySign(screen,"",19,120,193,26,0,0)
    ib.printText(screen,"Numero Ingresado: ",30,22,120,(5,245,255))
    ib.drawMemoryExp(screen,"",212,120,350,26,0,0)
    ib.printText(screen,auxanswer,30,221,120,yellow)
    
    # representacion en almacenamiento decimal
    ib.printText(screen,"Numero almacenado en memoria en notacion Decimal "+str(numbits)+"-bits",30,20,160,(100,200,86))
    ib.drawMemorySign(screen,"Numero",19,200,numlon,26,20,180) # X, Y , long, alt
    ib.drawMemoryExp(screen,"Exponente (10^"+str(exp)+")",numlon+19,200,70,26,390,180)
    ib.printText(screen,numstr,30,22,200,yellow)
    ib.printText(screen,exponent,30,numlon+20,200,yellow)
    # en binario
    ib.printText(screen,"Numero almacenado en memoria en notacion binaria "+str(numbits)+"-bits",30,20,235,(100,200,86))
    ib.drawMemorySign(screen,"Numero ("+posnega+")",19,279,numlon,26,20,260) # X, Y , long, alt
    ib.drawMemoryExp(screen,"Exponente (2^"+str(expbin1)+")",numlon+19,279,201,26,390,260)
    ib.printText(screen,binariodec,30,22,280,yellow)
    ib.printText(screen,expbincero,30,numlon+20,280,yellow)
    
    # ERRORES
    ib.printText(screen,"Errores: El Valor de binario a decimal es: ",30,20,380,(100,200,86))
    ib.printText(screen,str(binaerror),30,420,380,blue)
    # ERROR REDONDEO
    ib.printText(screen,"Redondeo a "+str(cifras) +" cifras es: ",30,45,410,(100,200,86))
    ib.printText(screen,str(numberredon),30,330,410,blue)
    ib.printText(screen,"Abs: ",30,85,440,(100,200,86))
    ib.printText(screen,str(errorAbsR),30,135,440,red)
    ib.printText(screen,"Rel: ",30,85,470,(100,200,86))
    ib.printText(screen,str(errorRelR),30,135,470,red)
    # ERROR TRUNCAMIENTO
    ib.printText(screen,"Truncamiento a "+str(cifras) +" cifras es: ",30,45,500,(100,200,86))
    ib.printText(screen,str(numbertrunc),30,330,500,blue)
    ib.printText(screen,"Abs: ",30,85,530,(100,200,86))
    ib.printText(screen,str(errorAbsT),30,135,530,red)
    ib.printText(screen,"Rel: ",30,85,560,(100,200,86))
    ib.printText(screen,str(errorRelT),30,135,560,red)

    # representacion binaria
    ib.printText(screen,"Numero almacenado en memoria en notacion IEEE "+str(numbits)+"-bits",30,20,310,(100,200,86))
    # Signo
    ib.drawMemorySign(screen,"Signos",19,349,47,26,17,330) # X, Y , long, alt
    # Exponente
    ib.drawMemoryExp(screen,"Exponente: ("+str(expbin1)+"+"+str(maxExp)+")",66,349,129,26,85,330)
    # Mantisa
    ib.drawMemoryMantis(screen,"Mantisa",195,349,bitlon,26,375,330)
    # representacion
    ib.printText(screen,signnum ,30,22,351,yellow)
    ib.printText(screen,str(expbinario),30,70,351,yellow)
    ib.printText(screen,str(binario),30,198,351,yellow)
    ib.printText(screen,"Moreno Vera,Felipe Adrian", 30,450,660,(220,150,0))
    
    clock.tick(30)
    cursor1.update()
    boton.update(screen,cursor1)
    ib.printText(screen,"Salir del Programa ~~ Meoww ~~",35,115,615,(180,180,130))
    pg.display.update()

  pg.quit()

if __name__ == "__main__":
  mainScreen()
