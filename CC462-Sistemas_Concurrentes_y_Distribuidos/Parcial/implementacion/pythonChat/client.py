#!/usr/bin/python
# -*- coding: utf-8 -*-

# client.py

import sys
import socket
import select

PORT = 9009
HOST = ''

def client(host,port):
  s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
  s.settimeout(2)
  # Conecta al host remoto
  try :
    s.connect((host, port))
  except :
    print 'No se pudo conectarse'
    sys.exit()
   
  print 'Conectado desde un host remoto. Inicia la conexion'
  sys.stdout.write('[Yo] '); sys.stdout.flush()
  connect = 1
  while connect:
    socket_list = [sys.stdin, s]
    # Obtiene la lista de sockets que son leidos
    ready_to_read,ready_to_write,in_error = select.select(socket_list , [], [])
    for sock in ready_to_read:             
      if sock == s:
        # Mensaje en camino desde el servidor remoto, s
        data = sock.recv(4096)
        if not data :
          print '\nDesconectado del servidor'
          sys.exit()
        else :
          # print data
          sys.stdout.write(data);
          sys.stdout.write('[Yo] ');
          sys.stdout.flush();
      else :
        # Mensaje introducido por el usuario
        msg = sys.stdin.readline()
        s.send(msg);
        if msg == "adios\n" or msg == "Adios\n":
          connect=0
          break
        sys.stdout.write('[Yo] ');
        sys.stdout.flush()
  s.close()

if __name__ == "__main__":
  if(len(sys.argv) < 2):
    host = HOST
    port = PORT
  elif len(sys.argv)==3:
    host = sys.argv[1]
    port = int(sys.argv[2])
  sys.exit(client(host,port))
