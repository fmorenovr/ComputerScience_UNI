#!/usr/bin/python
# -*- coding: utf-8 -*-

from random import random, randint, uniform
from cellVariables import *

class Cell():
  numCells = 1
  ArrayCells = []
  deadFactor = 0.1
  # kind = tipo de celula
  # x = posicion X
  # y = posicion Y
  # size = area (radio)
  # veloProg = velocidad de propagacion
  # colour = color de celula
  # thickness = colorea (0) o solo dibuja linea (1)
  # speed = velocidad de movimiento
  # angle = angulo al iniciar movimiento
  # idCell = id de celula
  # numChild = numero de hijos
  # state = determina si ya se dividio
  #       = 1; listo para dividir
  #       = 0; recien nacido
  #       = -1; ya se dividio y empieza a morir
  # eat = si puede comer o no
  def __init__(self, name,colour,(x, y),velProg,angle=uniform(0.0,2*math.pi),size=5,speed=0.1,caneat=False):
      self.kind = name
      self.x = x
      self.y = y
      self.size = size
      self.vel = velProg
      self.colour = colour
      self.thickness = 0
      self.speed = speed
      self.angle = angle
      self.idcell = Cell.numCells
      self.numChild = 2
      self.state = 0
      self.caneat = caneat
      Cell.numCells+=1
      Cell.ArrayCells.append(self)

# ciclo de vida de la celula
  def lifeCycleCell(self):
    self.move()
    # si esta en el area, come
    # si no consigue comida en un tiempo, muere
    # si llega a llenarse, come
    # si llega a clonarse lo suficiente muere
    if(self.state==0):
      if self.kind == "Benigna":
        self.colour = yellow
      elif self.kind == "Cancer":
        self.colour = purple
      self.eatCell()
    elif(self.state==1):
      if self.kind == "Benigna":
        self.colour = yellow
      elif self.kind == "Cancer":
        self.colour = purple
      self.cellClone()
    elif(self.state==-1):
      if self.kind == "Benigna":
        self.colour = darkYellow
      elif self.kind == "Cancer":
        self.colour = darkPurple
      self.deadCell()

# clonar celula
  def cellClone(self):
    if(self.numChild==2):
      self.numChild = self.numChild-1
      self.state = 0
    elif(self.numChild==1):
      self.numChild = self.numChild-1
      self.state = -1
    copia = Cell(self.kind,self.colour,(self.x,self.y),self.vel)

# cantidad de comida ingerida
# comen segun velocidad de propagacion
  def eatCell(self):
    eat = self.vel*round(random(),2)
    self.size += eat
    if(self.size>=10):
      self.size=5
      self.state=1

# van muriendo lentamente ... :(
  def deadCell(self):
    dead = Cell.deadFactor*round(random(),2)
    self.size -= dead
    if(self.size<=0):
      print  "celula tipo: ", self.kind," numero: ",self.idcell," muerta !!"
      Cell.ArrayCells.remove(getIndexCell(self.idcell))

  def display(self):
    pygame.draw.circle(screen, self.colour, (int(self.x), int(self.y)), int(self.size), self.thickness)

  def move(self):
    (self.angle, self.speed) = addVectors((self.angle, self.speed), gravity)
    self.x += math.sin(self.angle) * self.speed
    self.y -= math.cos(self.angle) * self.speed
    self.speed *= drag

# define las fronteras 
  def bounce(self):
    if self.x > width - self.size:
      self.x = 2*(width - self.size) - self.x
      self.angle = - self.angle
      self.speed *= elasticidad
    elif self.x < self.size:
      self.x = 2*self.size - self.x
      self.angle = - self.angle
      self.speed *= elasticidad

    if self.y > height - self.size:
      self.y = 2*(height - self.size) - self.y
      self.angle = math.pi - self.angle
      self.speed *= elasticidad
    elif self.y < self.size:
      self.y = 2*self.size - self.y
      self.angle = math.pi - self.angle
      self.speed *= elasticidad

# obtiene la celula que esta en el index num en el ArrayCells
def getIndexCell(num):
  cells = getAllCells()
  for cell in cells:
    if(cell.idcell==num):
      return cell
  return None

# obtiene el numero de celulas
def getNumCells():
  return len(Cell.ArrayCells)

# obtiene el array de celulas
def getAllCells():
  return Cell.ArrayCells

# obtiene el numero de celulas segun su tipo
def getTypeCells(name):
  cells = getAllCells()
  count = 0
  for cell in cells:
    if(cell.kind == name):
      count+=1
  return count

# anade los vectores direcciones luego de los choques
def addVectors((angle1, length1), (angle2, length2)):
  x  = math.sin(angle1) * length1 + math.sin(angle2) * length2
  y  = math.cos(angle1) * length1 + math.cos(angle2) * length2
  angle = 0.5 * math.pi - math.atan2(y, x)
  length  = math.hypot(x, y)
  return (angle, length)

# encuentra la celula con menor distancia
def findCell(cells, x, y):
  for p in cells:
    if math.hypot(p.x-x, p.y-y) <= p.size:
      return p
  return None

# choque entre las celulas
def collide(p1, p2):
  dx = p1.x - p2.x
  dy = p1.y - p2.y

  dist = math.hypot(dx, dy)
  if dist < p1.size + p2.size:
    tangent = math.atan2(dy, dx)
    angle = 0.5 * math.pi + tangent
    angle1 = 2*tangent - p1.angle
    angle2 = 2*tangent - p2.angle
    speed1 = p2.speed*elasticidad
    speed2 = p1.speed*elasticidad

    (p1.angle, p1.speed) = (angle1, speed1)
    (p2.angle, p2.speed) = (angle2, speed2)

    p1.x += math.sin(angle)
    p1.y -= math.cos(angle)
    p2.x -= math.sin(angle)
    p2.y += math.cos(angle)

# imprime las celulas y sus caracteristicas
def printCells(cells):
  for cell in cells:
    print "\n#########################################"
    print "#\tCelula N.",cell.idcell,": ", cell.kind,"\t#"
    print "#########################################"
    print "#\tX: ", cell.x,"\t\t\t\t#"
    print "#\tY: ", cell.y,"\t\t\t\t#"
    print "#\tarea: ", cell.size,"\t\t\t#"
    print "#\testado de vida", cell.state,"\t\t#"
    print "#########################################\n\n"

# crecen hasta ser una generacion ( 2^x )
def initGenerations(numcell):
  cellTotal = getAllCells()
  while(len(cellTotal)<(2**numcell)):
    for cell in cellTotal:
      print "\n#########################################"
      print "#\tCelula N.",cell.idcell,": ", cell.kind,"\t#"
      print "#########################################"
      print "#\tX: ", cell.x,"\t\t\t\t#"
      print "#\tY: ", cell.y,"\t\t\t\t#"
      print "#\tnumero de crias: ",cell.numChild,"\t\t#"
      print "#\tarea: ",cell.size,"\t\t\t#"
      print "#\testado: ",cell.state,"\t\t\t#"
      print "#########################################\n\n"
      cell.lifeCycleCell()

# ###########################################################
#  Funciones extras ( uso por ahora )

def divCells(cells):
  cellsaux = []
  for cell in cells:
    cellaux = cell._cellClone()
    cellsaux.append(cellaux)
  return cellsaux

def reprodCells(cells):
  cellsaux = divCells(cells)
  for cell in cellsaux:
    cells.append(cell)
  return cells

def genCells(cells,num):
  for i in range(0,num):
    cells=reprodCells(cells)
  return cells
