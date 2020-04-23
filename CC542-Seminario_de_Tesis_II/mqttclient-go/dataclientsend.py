import time
import os
import string
import random

master = "Master"
#master = "CTIC-SMARTCITY"

def Encrypt(cad):
  result = ""
  for v in cad:
    result = str(v) + result
  return result

def generateData():
  s = 'mosquitto_pub -t \"$topic\"  -u '+master+' -P '+Encrypt(master)+' -m \'{ \"id_moduleiot\" : \"$idIot\",\"id_sensor\" : \"$idsensor\",\"value\" : $value,\"date\" : \"$fecha $hora\", \"type\" : \"$topics1\"}\''
  #print s
  return s
 
def transformData(s):
    idusers = ["U0001", "U0002"]
    topics = ["Temperatura", "Presion", "Monoxido", "Dioxido"]
    idsensors = ["S50001", "S51002", "S55002", "S54002", "S52002", "S53002"]
    idiots = ["C001", "C002","C003","C004"]
    passwd  = ["100C","200C","300C","400C"]
    numrand = [-20,-10,0,5,10,15,18,20,21,25, 27,30,34, 38];
    fecharpi = time.strftime("%Y-%m-%d")
    horarpi  = time.strftime("%H:%M:%S")
    #hostrpi = "52.10.199.174"
    hostrpi = "localhost"
    topicnum = random.randint(0, 5);
    topicnumtip = random.randint(0, 3)
    userrand = random.randint(0,3)
    numrandtip = random.randint(0, 13);
   
    topicrpi = topics[topicnumtip]
    idsensorrpi = idsensors[topicnum]
    idiotrpi =  idiots[userrand] #random.choice(idiots)
    rpipasswd = passwd[userrand]
    iduserrpi = random.choice(idusers)
    valuerpi = numrand[numrandtip]#random.uniform(0, 100)
    t = string.Template(s)
    return t.substitute(host=hostrpi, topic=idiotrpi+"/"+topicrpi, iduser=iduserrpi,idIot=idiotrpi, Passwd=rpipasswd, idsensor=idsensorrpi, value=valuerpi, fecha=fecharpi, hora=horarpi, topics1=topicrpi)
       
while 1:
    x = generateData()
    signal = transformData(x)
    print signal
    os.system(signal)
    #xbee.write(x)
    #time.sleep(random.randint(0, 5))
    time.sleep(1)
    #print x
