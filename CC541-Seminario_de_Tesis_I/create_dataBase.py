#!/usr/bin/python
# -*- coding: utf-8 -*-
import os
import sys
from dataBase.verifica_DB import *

path_db = os.getcwd() + '/dataBase/'

path_json = os.getcwd() + '/dataMining/output_json/'

createdb = "mongoimport --db beagons --collection sensors -- drop --file " + path_json

def setDataBase(argv):
  argc = len(sys.argv);
  if argc < 2:
    print "\n\terror:==>No ingreso fichero de entrada JSON para crear la base de datos\n"
    return;
  os.system('clear')
  print "\n\n#################################################"
  print "#\t\tTesis\t\t#"
  print "#################################################"
  
  print "\n  Verificando el fichero de entrada %s ... "%(argv[0])
  if not verificaExtension(argv[0]):
    print "\t  error:==>No tiene extension json\n\n"
    return ;
  if not verificaExistencia(path_json+argv[0]):
    print "\t  error:==>No existe el fichero\n\n"
    return ;
  
  print "  Creando la base de datos ... "
  #os.system(createdb + argv[0])
  print "%s"%(createdb+argv[0])

if __name__ == "__main__":
  setDataBase(sys.argv[1:])
