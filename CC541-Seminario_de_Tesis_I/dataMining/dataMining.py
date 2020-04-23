#!/usr/bin/python
# -*- coding: utf-8 -*-
import sys
from filtra_DM import *
from verifica_DM import *

# python dataMining.py lecturaArduino.xbe lecturaArduino.json

def dataMining(argv):
  argc = len(sys.argv);
  if argc < 2:
    print "\n\terror:==>No ingreso fichero de entrada XBE\n"
    return;
  elif argc < 3:
    print "\n\terror:==>No ingreso fichero de salida JSON\n"
    return;
  os.system('clear')
  print "\n\n#################################################"
  print "#\t\tProyecto Beagons\t\t#"
  print "#################################################"

  print "\n  Verificando el fichero de entrada %s ... "%(argv[0])
  if not verificaExtension(argv[0]):
    print "\t  error:==>No tiene extension xbe\n\n"
    return ;
  if not verificaExistencia(argv[0]):
    print "\t  error:==>No existe el fichero\n\n"
    return ;

  print "  Iniciando el Data Mining ... "
  print "  Fin del data mining ...\n"
  
  print "  Iniciando la conversion a formato JSON ... "
  lineas = convertLines(argv[0])
  creaJSON(argv[1])
  xbeToJSON(argv[1],lineas,4)
  terminaJSON(argv[1])
  print "  Fin de la conversion a formato JSON ...\n"


if __name__ == "__main__":
  dataMining(sys.argv[1:]);
