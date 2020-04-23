#!/usr/bin/python
# -*- coding: utf-8 -*-

import pygame
import math
from os import getcwd
from sys import exit

drag = 1.0# 0.999  # velocidad de frenado debido a la perdida de energia
# si drag es (0) el choque es perfectamente inelastico
elasticidad = 0.75 # choque elastico (1), inelastico
gravity = (math.pi, 0.000) # set la gravedad
(width, height) = (800, 450) # tamano del screen

# screen del programa
screen = pygame.display.set_mode((width, height))

background_colour = (2,0,0) # color de fondo
path = getcwd() +'/' # ruta de la carpeta actual

# colores predeterminados
blue = (0, 0, 255)
red = (255, 0, 0)
green = (0, 255, 0)
darkGreen = (0,204,102)
purple = (255,0,127)
darkPurple = (127,0,255)
yellow = (255,255,0)
pink = (255,102,102)
darkYellow = (255,204,153)

# tiempo de actualizacion de frames (a menor numero mas lento)
clock=pygame.time.Clock()

# titulo del programa
pygame.display.set_caption('Mitosis Simulation')

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
class Food():
  numFoods = 1
  ArrayFoods = []
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
    self.idfood = Food.numFoods
    Food.numFoods+=1
    Food.ArrayFoods.append(self)

  def display(self):
    pygame.draw.circle(screen, self.colour, (self.x, self.y), self.size, self.thickness)

# obtiene la comida que esta en el index num en el ArrayCells
def getIndexFood(num):
  foods = getAllFoods()
  for food in foods:
    if(food.idfood==num):
      return food
  return None

# obtiene el array de celulas
def getAllFoods():
  return Food.ArrayFoods
