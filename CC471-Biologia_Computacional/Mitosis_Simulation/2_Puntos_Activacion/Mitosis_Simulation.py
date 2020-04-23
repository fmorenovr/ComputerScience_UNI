#!/usr/bin/python
# -*- coding: utf-8 -*-

from Cell import *

cellCancer = Cell("Cancer",purple,(1,1),0.5)
cellBenigna = Cell("Benigna",yellow,(width/2, height/2),0.25)
selected_cell = None
paused = False
#initGenerations(3)

number_of_foods = 15
my_foods = []

for n in range(number_of_foods):
  size = randint(10, 20)
  x = randint(size, width-size)
  y = randint(size, height-size)
  my_foods.append(Food((x, y), size))

pygame.init()
pygame.mixer.music.load(path+"Topgear.mp3")
pygame.mixer.music.play(0)
while getNumCells()<2048:
  for event in pygame.event.get():
    if event.type == pygame.QUIT:
      exit()
    elif event.type == pygame.MOUSEBUTTONDOWN:
      (mouseX, mouseY) = pygame.mouse.get_pos()
      selected_cell = findCell(my_cells, mouseX, mouseY)
    elif event.type == pygame.MOUSEBUTTONUP:
      selected_cell = None
    elif event.type == pygame.KEYDOWN:
      if event.key in key_to_function:
        continue#key_to_function[event.key](universe_screen)
      elif event.key == pygame.K_SPACE:
        paused = (True, False)[paused]

  if selected_cell:
    (mouseX, mouseY) = pygame.mouse.get_pos()
    dx = mouseX - selected_cell.x
    dy = mouseY - selected_cell.y
    selected_cell.angle = 0.5*math.pi + math.atan2(dy, dx)
    selected_cell.speed = math.hypot(dx, dy) * 0.1

  clock.tick(10) # tiempo de renderizacion
  screen.fill(background_colour)

  for food in my_foods:
    food.display()

  my_cells = getAllCells()
  for i, cell in enumerate(my_cells):
    cell.lifeCycleCell()
    cell.bounce()
    for cell2 in my_cells[i+1:]:
      collide(cell, cell2)
    cell.display()

  print "numero total de celulas: ",getNumCells()
  print "numero de benignas: ",getTypeCells("Benigna")
  print "numero de cancerosas: ",getTypeCells("Cancer")
  pygame.display.flip()
pygame.quit()
