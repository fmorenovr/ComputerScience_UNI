el programa funciona asi:

el directorio gspr

contiene los directorios:

  bin: contiene el ejecutable gpsr

  datasets:  contiene la data de los train y tests

  exe: tiene los executables .o de los archivos .cpp de la carpeta src

  src: contiene los programas a usar hechos en c++.

  results: contiene 4 directorios

    ejecucion_1, ejecucion_10, ejecucion_20, ejecucion_30

    y contiene los gif:

      animateBestTeoric.gif: es el gif hecho de las funciones escritas en los archivos best

      animateHits.gif: es el gif hecho de los hits alcanzados y en que generacion, obtenidos del archivo res, de las columnas 1 y 4.

      animateBestExp.gif: es la grafica de los puntos x,y del archivo res columnas 2 y 3, que dan solucion a las funciones aproximadas.




Y se ve que los respectivos fitness son:

para 1 ejecucion: 0.981389	0.000355399

para 10 ejecuciones: 0.997669	0.000354771

para 20 ejecuciones: 0.999937	0.000354512

para 30 ejecuciones: 1	0.000354573
