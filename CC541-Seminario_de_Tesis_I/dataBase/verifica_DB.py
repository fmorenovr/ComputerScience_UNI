#!/usr/bin/python
# -*- coding: utf-8 -*-

import os

def verificaExtension(fichero):
  splitFile = fichero.split('.')
  if splitFile[len(splitFile)-1]=='json':
    return True
  return False

def verificaExistencia(fichero):
  openFile = fichero
  infile = os.path.isfile(openFile)
  if infile == False:
    return False
  return True

