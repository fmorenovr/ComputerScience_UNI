#!/usr/bin/python
# -*- coding: utf-8 -*-

import os

path_xbe = os.getcwd() + '/input_xbe/'

def verificaExtension(fichero):
  splitFile = fichero.split('.')
  if splitFile[len(splitFile)-1]=='xbe':
    return True
  return False

def verificaExistencia(fichero):
  openFile = path_xbe + fichero
  infile = os.path.isfile(openFile)
  if infile == False:
    return False
  return True

