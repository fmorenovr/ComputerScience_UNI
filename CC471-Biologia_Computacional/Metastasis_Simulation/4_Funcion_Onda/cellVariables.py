#!/usr/bin/python
# -*- coding: utf-8 -*-

import pygame
import math
from random import random, randint, uniform
from os import getcwd, system
from sys import exit

# color de fondo
background_colour = (2,0,0)
# ruta de la carpeta actual
path = getcwd() +'/'

# colores predeterminados
blue = (0, 0, 255)
red = (255, 0, 0)
green = (0, 255, 0)
darkGreen = (0,204,102)
purple = (255,0,127)
darkPurple = (127,0,255)
yellow = (255,255,0)
darkYellow = (255,204,153)
lightYellow = (255,220,100)
pink = (255,102,102)

# 1 libra = 0.453592 kg
# 1 pie = 0.3048 m
# 1lb/pie = 1.488162 kg/m
# 1mmhg = 13.5950 kg/m^2

#funciones de onda
def u(x,y,t,xtot,ytot):
  uxyt = 0.426*(math.cos(5*math.pi*math.sqrt(5)/xtot*t)*math.sin(math.pi*x/xtot)*math.sin(math.pi*y/ytot) + 1/27.*math.cos(5*math.pi/xtot*math.sqrt(37)*t)*math.sin(math.pi*x/xtot)*math.sin(3*math.pi*y/ytot) + 1/27.*math.cos(5*math.pi*math.sqrt(13)/xtot*t)*math.sin(3*math.pi*x/xtot)*math.sin(math.pi*y/ytot) + 1/729.*math.cos(5*math.pi*math.sqrt(45)/xtot*t)*math.sin(3*math.pi*x/xtot)*math.sin(3.*math.pi*y/ytot))
  return uxyt
  
# tipos de celulas
#     tipo
#     color vivo
#     color muriendo
#     tamano minimo
#     tamano maximo
#     velocidad de propagacion
#     velocidad de muerte
kind_Cells = [["Cancer",yellow,lightYellow,4,8,0.5,0.05]]#,["Benigna",yellow,lightYellow,3,6,0.5,0.15]]
#              

# funciones de onda de los puntos de activacion
activationPoints_WaveFunc = [u, u, u, u, u, u, u, u, u, u, u, u]
# factor de consumo
consumeFactor = 0.5

drag = 1.0# 0.999  # velocidad de frenado debido a la perdida de energia
# si drag es (0) el choque es perfectamente inelastico
# choque elastico (1), inelastico
elasticidad = 0.75
# set la gravedad
gravity = (math.pi, 0.000)
# tamano del screen
(width, height) = (800, 450)

# screen del programa
screen = pygame.display.set_mode((width, height))
# titulo del programa
pygame.display.set_caption('Metastasis Simulation')

# tiempo de actualizacion de frames (a menor numero mas lento)
clock=pygame.time.Clock()

# teclas especiales para jugar con la interaccion
key_to_function = {
    pygame.K_LEFT:   (lambda x: x.scroll(dx = 1)),
    pygame.K_RIGHT:  (lambda x: x.scroll(dx = -1)),
    pygame.K_DOWN:   (lambda x: x.scroll(dy = -1)),
    pygame.K_UP:     (lambda x: x.scroll(dy = 1)),
    pygame.K_EQUALS: (lambda x: x.zoom(1.5)),
    pygame.K_MINUS:  (lambda x: x.zoom(0.5)),
    pygame.K_r:      (lambda x: x.reset())}

########################################
# Clase de comida
class ActivationPoint():
  numActivationPoints = 1
  ArrayActivationPoints = []
  # x = posicion X
  # y = posicion Y
  # size = tamano (radio)
  # consume = factor de consumision
  # colour = color
  # thickness = colorea o solo dibuja linea
  def __init__(self,colour, (x, y), size, consume,function):
    self.x = x
    self.y = y
    self.size = size
    self.consume = consume
    self.colour = colour
    self.function = function
    self.thickness = 0
    self.idactivationpoint = ActivationPoint.numActivationPoints
    ActivationPoint.numActivationPoints+=1
    ActivationPoint.ArrayActivationPoints.append(self)

  def consumir(self):
    dead = self.consume*round(random(),2)
    self.size -= dead
    if(self.size<=0):
      ActivationPoint.ArrayActivationPoints.remove(getIndexActivationPoint(self.idactivationpoint))
      WavePoint.ArrayWavePoints.remove(getIndexWavePoint(self.idactivationpoint))

  def display(self,x,y,size):
    if size < 2:
      pygame.draw.rect(screen, self.colour, (x, y, 2, 2))
    else:
      pygame.draw.circle(screen, self.colour, (x, y), size, self.thickness)


# obtiene la comida que esta en el index num en el ArrayCells
def getIndexActivationPoint(num):
  activationPoints = getAllActivationPoints()
  for activationPoint in activationPoints:
    if(activationPoint.idactivationpoint==num):
      return activationPoint
  return None

# obtiene el array de celulas
def getAllActivationPoints():
  return ActivationPoint.ArrayActivationPoints

################################################
# clase onda
class WavePoint:
  numWavePoints = 1
  ArrayWavePoints = []
  # x = posicion X
  # y = posicion Y
  # size = tamano (radio)
  # colour = color
  # thickness = colorea o solo dibuja linea
  def __init__(self,colour, (x, y), size):
    self.x = x
    self.y = y
    self.originalSize = size
    self.size = size
    self.colour = colour
    self.thickness = 1
    self.idwavepoint = WavePoint.numWavePoints
    WavePoint.numWavePoints+=1
    WavePoint.ArrayWavePoints.append(self)

  def display(self,x,y,size):
    if size < 2:
      pygame.draw.rect(screen, self.colour, (x, y, 2, 2))
    else:
      pygame.draw.circle(screen, self.colour, (x, y), size, self.thickness)

# obtiene la comida que esta en el index num en el ArrayCells
def getIndexWavePoint(num):
  wavePoints = getAllWavePoints()
  for wavePoint in wavePoints:
    if(wavePoint.idwavepoint==num):
      return wavePoint
  return None

# obtiene el array de celulas ondas
def getAllWavePoints():
  return WavePoint.ArrayWavePoints
