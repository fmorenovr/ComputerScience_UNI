#!/usr/bin/python
# -*- coding: utf-8 -*-

# server.py
 
import sys
import time
import socket
import select
import server
import threading

HOST = ''
serverThreads = []
RECV_BUFFER = 4096 
PORT = 9009

def routingServers(host,port,numServers):
  port1 = port
  for i in range(numServers):
    port1 = port + i
    t = threading.Thread(target=serverThread, args=(host,port1))
    serverThreads.append(t)
    t.start()
  time.sleep(1)
  print serverThreads
  time.sleep(1)
  while len(serverThreads)>0:
    try:
      serverClose=int(input("Ingrese el servidor a cerrar: "))
    except:
      serverClose = ''
    if serverClose==None or serverClose == '':
      continue
    s = getIndexServer(serverClose)
    print s

def serverThread(host,port):
  server.server(host,port)
  return

def getIndexServer(num):
  st = getAllServers()
  for server in st:
    if(server.getName()=="Thread-"+str(num)):
      return server
  return None

def getAllServers():
  return serverThreads
  

if __name__ == "__main__":
  host = HOST
  port = PORT
  numServers = 4
  if len(sys.argv)==2 and len(sys.argv[1])<3:
    numServers = int(sys.argv[1])
  elif len(sys.argv)==3:
    host = sys.argv[1]
    port = int(sys.argv[2])
  elif len(sys.argv)==4:
    host = sys.argv[1]
    port = int(sys.argv[2])
    numServers = int(sys.argv[4])
  sys.exit(routingServers(host,port,numServers))
