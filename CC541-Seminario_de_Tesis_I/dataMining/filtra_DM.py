#!/usr/bin/python
# -*- coding: utf-8 -*-

import os

path_json = os.getcwd() + '/output_json/'
path_xbe = os.getcwd() + '/input_xbe/'

def creaJSON(nombreFile):
  newFile = open(path_json + nombreFile,'w')
  newFile.write('{"Datos":[')
  newFile.close()

def xbeToJSON(nombreFile,lines,num):
  openFile = open(path_json + nombreFile,'r+')
  linea1=openFile.readline()
  if num < len(lines):
    openFile.writelines(lines[0:num])
  elif num > len(lines):
    openFile.writelines(lines)
  else:
    openFile.writelines(lines)
  openFile.close()

def terminaJSON(nombreFile):
  openFile = open(path_json + nombreFile,'r+')
  content = openFile.read()
  final_fichero = openFile.tell()
  openFile.seek(final_fichero-2)
  openFile.write("\n]}")
  openFile.close()

def convertLines(nombreFile):
  openFile = open(path_xbe + nombreFile,'r')
  linea = openFile.readline()
  lineas = []
  verificalen = 0
  while linea!="":
    if verificaLinea(linea)==1:
      return
    # Filtra los datos del txt
    lineaFiltrada=splitTipos(linea)
    # devuelve el nombre del cansat
    #nombreCansat = numCansat(lineaFiltrada)
    lenCansat = numCansat(lineaFiltrada)
    # le da formato de json
    #lineaJSON = formatTipos(lineaFiltrada,nombreCansat)
    lineaJSON = formatTipos(lineaFiltrada)
    # anadimos a la lista de lineas
    lineas.append(lineaJSON)
    if verificalen ==4 and lenCansat!=2:
      print "  error de lineas de lectura"
      exit()
    verificalen = lenCansat
    linea = openFile.readline()
  openFile.close()
  return lineas

def verificaLinea(linea):
  if linea=="\n":
    return 1
  return 0

def splitTipos(linea):
  nuevaLinea = linea[1:len(linea)-2]
  nlin = []
  lineaFiltrada = nuevaLinea.split(',')
  lineaFiltrada[0] = lineaFiltrada[0][1:len(lineaFiltrada[0])-1]
  nlin.append(lineaFiltrada[0])
  for i in range(1,len(lineaFiltrada)):
    lineaFiltrada[i] = lineaFiltrada[i][2:len(lineaFiltrada[i])-1]
    if len(lineaFiltrada[i])>1:
      nlin.append(lineaFiltrada[i])
  return nlin

# forma las lineas del json
def itemCansat(linea,actual,final):
  newLine = "\t{\"name\":\"" + tipoSensor(linea[0]) + "\",\"valor\":\""
  newLine = newLine + linea[1:]
  newLine = newLine + "\"},"
  #if (actual != (final-1)):
  #  newLine = newLine + ","
  return newLine

def formatTipos(linea):
  writeLine="\n"
  final = len(linea)
  for i in range(0,len(linea)):
    writeLine = writeLine + itemCansat(linea[i],i,final)+"\n"
  return writeLine

def formatTipos1(linea,nombre,coma=True):
  writeLine = "{\""+nombre+"\":[\n"
  final = len(linea)
  for i in range(0,len(linea)):
    writeLine = writeLine + itemCansat(linea[i],i,final)+"\n"
  if coma:
    writeLine = writeLine+"]},\n"
  else:
    writeLine = writeLine+"]}\n"
  return writeLine

# generar un codigo extra por cansat
def numCansat(linea):
  if len(linea) == 4:
    return 4#"cansat_1"
  elif len(linea) == 2:
    return 2#"cansat_2"
  elif len(linea) == 6:
    return 6#"cansat_3"

def tipoSensor(letra):
  if letra == "T":
    return "Temperatura"
  elif letra == "P":
    return "Presion"
  elif letra == "H":
    return "Altura"
  elif letra == "N":
    return "Nitrogeno"
  elif letra == "C":
    return "Carbono"
  elif letra == "D":
    return "D"
  else:
    return "No_Conocido"

