#!/usr/bin/python
# -*- coding: utf-8 -*-

# server.py
 
import sys
import time
import socket
import select
from server import *
import threading

HOST = ''
PORT = 9009

class Router():
  serverThreads = []
  def __init__(self,host,port,numServers):
    self.host = host
    self.port = port
    self.numServers = numServers

  def routingServers(self,host,port,numServers):
    port1 = port
    for i in range(numServers):
      port1 = port + i
      #serverSock = serverThread(host,port1)
      t = threading.Thread(target=serverThread, args=(host,port1))
      Router.serverThreads.append(t)
      t.start()
    time.sleep(1)
    print Router.serverThreads
    time.sleep(1)
    while len(Router.serverThreads)>0:
      try:
        serverClose=int(input("Ingrese el servidor a cerrar: "))
      except:
        serverClose = ''
      if serverClose==None or serverClose == '':
        continue
      s = getIndexServer(serverClose)
      print s

def serverThread(host,port):
  servr = Server(host,port)
  servr.serverRun()
  return

def getIndexServer(num):
  st = getAllServers()
  for servers in st:
    if(servers.getName()=="Thread-"+str(num)):
      return servers
  return None

def getAllServers():
  return Router.serverThreads
  

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
  router = Router(host,port,numServers)
  sys.exit(router.routingServers(host,port,numServers))
