#!/usr/bin/python
# -*- coding: utf-8 -*-

from Body import *

# color del universo
universe = Environment((width, height))
universe.colour = background_colour
universe.addFunctions(['move'])
universe_screen = BodyScreen(width, height)

selected_cell = None
paused = False

# anade los puntos de activacion
#universe.addActivationPoints(num_activationPoints)

# crea las celulas segun lo almacenado
for infoCell in kind_Cells:
  xpos = randint(1, width)
  ypos = randint(1, height) 
  universe.addCells(infoCell[0], infoCell[1],infoCell[2],infoCell[3],infoCell[4], (xpos,ypos), infoCell[5],infoCell[6])

# crea los puntos de activacion segun lo almacenado
for fun in activationPoints_WaveFunc:
  size = randint(10, 20)
  x = randint(size, width-size)
  y = randint(size, height-size)
  universe.addActivationPoints(blue,(x,y),size,consumeFactor,fun)
  universe.addWavePoints(red,(x,y),size/4)

t = 0.0
iterCycle = 0

# inicio de la simulacion
pygame.init()
pygame.mixer.music.load(path+"Topgear.mp3")
pygame.mixer.music.play()
while getNumCells()<1024:
  my_cells = getAllCells()
  my_activationPoints = getAllActivationPoints()
  my_wavePoints = getAllWavePoints()
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
        key_to_function[event.key](universe_screen)
      elif event.key == pygame.K_SPACE:
        paused = not paused

  while paused:
    pygame.mixer.music.pause()
    for event in pygame.event.get():
      if event.type == pygame.QUIT:
        exit()
      elif event.type == pygame.KEYDOWN:
        if event.key == pygame.K_SPACE:
          paused = not paused
          pygame.mixer.music.play()

  if selected_cell:
    (mouseX, mouseY) = pygame.mouse.get_pos()
    dx = mouseX - selected_cell.x
    dy = mouseY - selected_cell.y
    selected_cell.angle = 0.5*math.pi + math.atan2(dy, dx)
    selected_cell.speed = math.hypot(dx, dy) * 0.1

  screen.fill(universe.colour)

# display los puntos de activacion
  for activationpoint in my_activationPoints:
    apx = int(universe_screen.mx + (universe_screen.dx + activationpoint.x) * universe_screen.magnification)
    apy = int(universe_screen.my + (universe_screen.dy + activationpoint.y) * universe_screen.magnification)
    apsize = int(activationpoint.size * universe_screen.magnification)
    if iterCycle%453==0:
      activationpoint.consumir()
    activationpoint.display(apx,apy,apsize)

# display las ondas
  for wavepoint in my_wavePoints:
    wpx = int(universe_screen.mx + (universe_screen.dx + wavepoint.x) * universe_screen.magnification)
    wpy = int(universe_screen.my + (universe_screen.dy + wavepoint.y) * universe_screen.magnification)
    if iterCycle%5!=0:
      wavepoint.size += 0.5*wavepoint.size
    if iterCycle%11==0:
      wavepoint.size = wavepoint.originalSize
    wpsize = int(wavepoint.size*universe_screen.magnification)    
    wavepoint.display(wpx,wpy,wpsize)

# display las celulas
  for i, cell in enumerate(my_cells):
    cell.lifeCycleCell(t)
    cx = int(universe_screen.mx + (universe_screen.dx + cell.x) * universe_screen.magnification)
    cy = int(universe_screen.my + (universe_screen.dy + cell.y) * universe_screen.magnification)
    csize = int(cell.size * universe_screen.magnification)
    universe.bounce(cell)
    for cell2 in my_cells[i+1:]:
      collide(cell, cell2)
    cell.display(cx,cy,csize)

  system('clear')
  print"\n#################################################"
  print "#\t\tMetastasis Simulation\t\t#\n#\tDeveloped by Moreno Vera Felipe Adrian\t#"
  print"#################################################"
  print "#\tnumero total de celulas: ",getNumCells(),"\t\t#"
  for infoCell in kind_Cells:
    print "#\tnumero de %s:\t"%(infoCell[0]),getTypeCells(infoCell[0]),"\t\t#"
  print"#################################################"
  pygame.display.flip()
  clock.tick(10) # tiempo de renderizacion
  t = t + 0.01
  iterCycle += 1
pygame.quit()
