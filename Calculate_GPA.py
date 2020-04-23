#! /usr/bin/env python

# -*- coding: utf-8 -*-
# encoding: utf-8

def getNota(nota):
  if 14<=nota and nota<=20:
    return 4.0, "A+"
  elif 13<=nota and nota<14:
    return 3.5, "A"
  elif 11<=nota and nota<13:
    return 3.0, "B"
  elif 10<=nota and nota<11:
    return 2.0, "C"
  else:
    return 1.0, "D"

def getGPA(courses_list, depurar=False):
  total_credits = 0.0
  ponderate_credits = 0.0
  ponderate_grades = 0.0
  for name_couse, credit, grade in courses_list:
    points, letter = getNota(grade)
    if depurar and letter=="D":
      continue    
    total_credits += credit
    ponderate_credits += credit*points
    ponderate_grades += credit*grade
    #print(credit, points, grade, total_credits, ponderate_credits)
  
  return ponderate_credits/total_credits, ponderate_grades/total_credits


courses_list = [
# 2012-I
("Intro CC", 2, 10.5), ("Calculo I", 5, 10.2), ("Vectorial I", 5, 11.1), ("Quimica I", 5, 7.4), ("Fisica I", 5, 10.4),
# 2012-II
("Intro Prog", 2, 10.5), ("Calculo II", 5, 12.2), ("Vectorial II", 5, 12), ("Quimica I", 5, 12.1), ("Ingles I", 2, 16.7),
# 2012-III
("Calculo III", 7, 13),
# 2013-I
("Intro Obj", 4, 10), ("Ingles II", 2, 12.2), ("Fisica II", 5, 10.5), ("constitucion", 2, 14), ("discreta", 3, 13.2), ("Quimica II", 5, 8.6), ("Lineal I", 5, 9),
# 2013-II
("Aquitectura", 4, 10), ("Algoritmos", 4, 10.8), ("Lineal I", 5, 7.7), ("Quimica II", 5, 12.8),
# 2014-I
("Fisica III", 5, 9.6), ("Biologia", 3, 10.2), ("Estadistica", 5, 9.2), ("Lineal I", 5, 6.4),
# 2014-II
("Lineal I", 5, 11.3), ("Estadistica", 5, 14.9), ("Fisica III", 5, 10.4),
# 2014-III
("Estructura de datos", 5, 12.7),
# 2015-I
("Algoritmos Paralelos", 4, 16), ("Base de datos", 4, 11.1), ("Sistemas Operativos", 4, 11.7), ("CTS", 2, 13.8), ("Numerico I", 5, 11.1),
# 2015-II
("Teoria Comp", 4, 13), ("Topicos III", 5, 19.3), ("Distribuido", 4, 14.3), ("Grafica", 4, 13.2), ("Redes", 4, 11.7), ("Numerico II", 5, 18),
# 2016-I
("Movile", 3, 18.8), ("App redes", 4, 16.7), ("IA", 4, 13.7), ("Compiladores", 4, 14.6), ("Topicos Software", 4, 13.8), ("Admin redes", 4, 16.6), ("Biologia comp", 4, 15.7),
# 2016-II
("Ingles III", 2, 13.8), ("Simulacion", 4, 12.6), ("Robotica", 4, 15.9), ("Seminario I", 4, 13.5), ("Nucleo", 2, 17.9), ("Ing Software", 4, 15.3), ("Concurrentes", 4, 11.3), ("Fisica Comp", 4, 16.8),
# 2017-I
("Seminario II", 4, 17), ("SO Avanzado", 2, 16.5), ("Cloud", 4, 15.3), ("Realidad", 2, 15), ("Seguridad", 3, 13.1)
]

GPA, AVG = getGPA(courses_list, False)

print("No Depurado GPA: ", GPA, "Average: ", AVG)

GPA, AVG = getGPA(courses_list, True)

print("Depurado GPA: ", GPA, "Average: ", AVG)
