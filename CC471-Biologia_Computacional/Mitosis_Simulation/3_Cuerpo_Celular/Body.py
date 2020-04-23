#!/usr/bin/python
# -*- coding: utf-8 -*-

from Cell import *

# clase de screen
class BodyScreen():
  def __init__ (self, width, height):
    self.width = width
    self.height = height
    (self.dx, self.dy) = (0, 0)
    (self.mx, self.my) = (0, 0)
    self.magnification = 1.0

  def scroll(self, dx=0, dy=0):
    self.dx += dx * width / (self.magnification*10)
    self.dy += dy * height / (self.magnification*10)

  def zoom(self, zoom):
    self.magnification *= zoom
    self.mx = (1-self.magnification) * self.width/2
    self.my = (1-self.magnification) * self.height/2
      
  def reset(self):
    (self.dx, self.dy) = (0, 0)
    (self.mx, self.my) = (0, 0)
    self.magnification = 1.0

# clase del contenedor del screen
class Environment():
  def __init__(self, (width, height)):
    self.width = width
    self.height = height
    self.cells = []
    self.ArrayActivationPoints = []
    self.colour = (255,255,255)
    self.cell_functions1 = []
    self.cell_functions2 = []
    self.function_dict = {
    'move': (1, lambda p: p.move()),
    'bounce': (1, lambda p: self.bounce(p)),
    'collide': (2, lambda p1, p2: collide(p1, p2))}

# anade las funciones
  def addFunctions(self, function_list):
    for func in function_list:
      (n, f) = self.function_dict.get(func, (-1, None))
      if n == 1:
        self.cell_functions1.append(f)
      elif n == 2:
        self.cell_functions2.append(f)
      else:
        print "No such function: %s" % f

# anade las celulas
  def addCells(self,kind,colour,deadcolour,minsize,maxsize,(x, y), vel, deadFactor):
    for i in range(1):
      cell = Cell(kind,colour,deadcolour,minsize,maxsize,(x, y), vel, deadFactor)
      self.cells.append(cell)

# anade los puntos de activacion
  def addActivationPoints(self,n):
    for i in range(n):
      size = randint(10, 20)
      x = randint(size, width-size)
      y = randint(size, height-size)
      activationPoint = ActivationPoint((x, y), size)
      self.ArrayActivationPoints.append(activationPoint)

# limites del screen
  def bounce(self, cell):
    if cell.x > self.width - cell.size:
      cell.x = 2*(self.width - cell.size) - cell.x
      cell.angle = - cell.angle
      cell.speed *= elasticidad
    elif cell.x < cell.size:
      cell.x = 2*cell.size - cell.x
      cell.angle = - cell.angle
      cell.speed *= elasticidad

    if cell.y > self.height - cell.size:
      cell.y = 2*(self.height - cell.size) - cell.y
      cell.angle = math.pi - cell.angle
      cell.speed *= elasticidad
    elif cell.y < cell.size:
      cell.y = 2*cell.size - cell.y
      cell.angle = math.pi - cell.angle
      cell.speed *= elasticidad

