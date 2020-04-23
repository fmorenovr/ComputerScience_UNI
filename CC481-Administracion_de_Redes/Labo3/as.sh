#!/usr/bin/bash

#Lista de dependencias.
#Nos dirijimos al directorio que contiene los paquetes.
cd /media/Packages

#install="gcc-4.4.6-4.el6.i686.rpm"
lista=$1

# Capturamos en DEPENDENCIAS la salida de error.
# se usa /dev/null para evitar que haga la interrupcion a nuestro bash, y el 2>&1 para evaluar si stdout(1) es menor que stderr(2) que si es cierto, indica error.
mensaje="$(rpm -i "$lista" 2>&1 >/dev/null )"

# depuramos todo el texto y los guiones.
# con grep =, buscamos hasta encontrar =.
# cut -f n, escoge el n-esimo termino que encuentre. n es numero.
# sed 's/X/Y', traduce toda cadena X por Y.,/g lo hace global >&1 por si hay error.
DEPENDENCIAS="$( echo "$mensaje" | grep = | cut -f 1 -d" " | sed 's/\t//g' >&1 )"

DEPENDENCIAS1="$( echo "$mensaje" | grep ".so.[0-9]" | grep -v _ | cut -f 1 -d "." | sed 's/\tlib//g' >&1 )"

#echo $DEPENDENCIAS1

DEPENDENCIAS="$DEPENDENCIAS $DEPENDENCIAS1"
mensaje="$DEPENDENCIAS $DEPENDENCIAS1"
#echo "$mensaje"
#echo "$DEPENDENCIAS"

for i in $DEPENDENCIAS ; do
  echo $i
  ups="$( ls . | grep "$i" )"
  echo $sups
  error1="$(rpm -i "$i" 2>&1 >/dev/null )"
  aux1="$( echo "$error1" | grep = | cut -f 1 -d" " | sed 's/\t//g' >&1 )"
  echo $aux1
  # pregunto si tiene dependencias por su longuitud.
  if [ ${#aux1} -ne 0 ]; then
    # obtengo los nombres de sus archivos y aumento las dependencias
    aux2="$(ls | grep "$axu1">&1)"
    mensaje="$mensaje $aux2"
  else
    # si no existe, ubicare a los que tienen nombre lib*.so.nro
    aux3="$( echo "$error1" | grep ".so.[0-9]" | grep -v _ | cut -f 1 -d "." | sed 's/\tlib//g' >&1 )"
    if [ ${#aux3} -ne 0 ]; then
      #ubicar los archivos y aumentar lista
      aux2="$(ls | grep "$axu3">&1)"
      mensaje="$mensaje $aux2"
    fi
  fi
done

echo $DEPENDENCIAS
echo $mensaje

