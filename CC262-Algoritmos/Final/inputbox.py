import pygame, pygame.font, pygame.event, pygame.draw, string
from pygame.locals import *

def get_key():
  while 1:
    event = pygame.event.poll()
    if event.type == KEYDOWN:
      return event.key
    else:
      pass

'''
pygame.draw.rect(screen, (0,0,0),
                   ((screen.get_width() / 2) - 100,
                    (screen.get_height() / 2) - 10,
                    200,20), 0)
  pygame.draw.rect(screen, (255,255,255),
                   ((screen.get_width() / 2) - 102,
                    (screen.get_height() / 2) - 12,
                    204,24), 1)
'''

def printText(screen,txtText, Textsize , Textx, Texty, Textcolor):
  # Escogemos el tipo de fuente
  Textfont = None
  myfont = pygame.font.SysFont(Textfont, Textsize)
  # le aplicamos texto a nuestro label
  label = myfont.render(txtText, 1, Textcolor)
  # pegamos en las posiciones Textx y Texty el label
  screen.blit(label, (Textx, Texty))
  # mostramos
  pygame.display.flip()

def drawMemorySign(screen,message,a,b,c,d,posx,posy):
  "Print a message in a box in the middle of the screen"
  fontobject = pygame.font.Font(None,25)
  # rectangulo de signos
  pygame.draw.rect(screen, (0,0,0),(a,b,c,d), 1)
  pygame.draw.rect(screen, (175,95,200),(a+1,b+1,c-2,d-2), 0) # 1 solo borde, 0 relleno
  # mensajes de info
  screen.blit(fontobject.render(message, 1, (255,255,0)), (posx,posy))
  pygame.display.flip()

def drawMemoryExp(screen,message,a,b,c,d,posx,posy):
  "Print a message in a box in the middle of the screen"
  fontobject = pygame.font.Font(None,25)
  # rectangulo de exp
  pygame.draw.rect(screen, (0,0,0),(a,b,c,d), 1)
  pygame.draw.rect(screen, (145,125,184),(a+1,b+1,c-2,d-2), 0) # 1 solo borde, 0 relleno
  # mensajes de info
  screen.blit(fontobject.render(message, 1, (0,255,255)), (posx,posy))
  pygame.display.flip()

def drawMemoryMantis(screen,message,a,b,c,d,posx,posy):
  "Print a message in a box in the middle of the screen"
  fontobject = pygame.font.Font(None,25)
  # rectangulo de mantisa
  pygame.draw.rect(screen, (0,0,0),(a,b,c,d), 1)
  pygame.draw.rect(screen, (145,125,184),(a+1,b+1,c-2,d-2), 0) # 1 solo borde, 0 relleno
  # mensajes de info
  screen.blit(fontobject.render(message, 1, (255,255,255)), (posx,posy))
  pygame.display.flip()

def display_box(screen, message,a,b):
  "Print a message in a box in the middle of the screen"
  fontobject = pygame.font.Font(None,25)
  pygame.draw.rect(screen, (0,0,0),(59,149, 160,26), 1)
  pygame.draw.rect(screen, (175,95,200),(60,150, 158,24), 0) # 1 solo borde, 0 relleno
  pygame.draw.rect(screen, (0,0,0),(219,149, 516,26), 1)
  pygame.draw.rect(screen, (145,125,184),(220,150, 514,24), 0) # 1 solo borde, 0 relleno
  if len(message) != 0:
    screen.blit(fontobject.render(message, 1, (5,245,255)), (a,b))
  pygame.display.flip()

def ask(screen, question,a,b):
  "ask(screen, question) -> answer"
  pygame.display.set_caption("Examen Parcial Analisis Numerico I")
  printText(screen,"Pregunta Numero 2",35,255,9,(245,164,8))
  printText(screen,"Almacenamiento en memoria",35,190,36,(206,188,65))
  pygame.font.init()
  current_string = []
  n = len(question)
  display_box(screen, question + " " + string.join(current_string,""),n+a,b)
  while 1:
    inkey = get_key()
    if inkey == K_BACKSPACE:
      current_string = current_string[0:-1]
    elif inkey == K_RETURN:
      break
    elif inkey == K_MINUS:
      current_string.append("-")
    elif inkey == K_PLUS:
      current_string.append("+")
    elif inkey <= 127:
      current_string.append(chr(inkey))
    display_box(screen, question + " " + string.join(current_string,""),n+a,b)
  return string.join(current_string,"")

def main():
  screen = pygame.display.set_mode([800,580])
  print ask(screen, "Numero: ") + " was entered"

if __name__ == '__main__':
  main()
