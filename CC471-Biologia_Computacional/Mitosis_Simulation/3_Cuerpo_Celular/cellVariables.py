#!/usr/bin/python
# -*- coding: utf-8 -*-

import pygame
import math
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
pink = (255,102,102)

# tipos de celulas
#     tipo
#     color vivo
#     color muriendo
#     tamano minimo
#     tamano maximo
#     velocidad de propagacion
#     velocidad de muerte
kind_Cells = [["Cancer",purple,darkPurple,5,10,0.75,0.5],
              ["Benigna",yellow,darkYellow,5,10,0.5,0.25]]

# numero de puntos de activacion
number_of_activationPoints = 15

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
    pygame.K_EQUALS: (lambda x: x.zoom(2)),
    pygame.K_MINUS:  (lambda x: x.zoom(0.5)),
    pygame.K_r:      (lambda x: x.reset())}

# Clase de comida
class ActivationPoint():
  numActivationPoints = 1
  ArrayActivationPoints = []
  # x = posicion X
  # y = posicion Y
  # size = tamano (radio)
  # colour = color
  # thickness = colorea o solo dibuja linea
  def __init__(self, (x, y), size):
    self.x = x
    self.y = y
    self.size = size
    self.colour = darkGreen
    self.thickness = 0
    self.idactivationpoint = ActivationPoint.numActivationPoints
    ActivationPoint.numActivationPoints+=1
    ActivationPoint.ArrayActivationPoints.append(self)

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

