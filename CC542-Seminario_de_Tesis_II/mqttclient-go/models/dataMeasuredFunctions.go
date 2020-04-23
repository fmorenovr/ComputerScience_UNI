package models

import (
  "encoding/json";
  "gopkg.in/mgo.v2/bson";
  MQTT "github.com/eclipse/paho.mqtt.golang";
)

// devuelve todas los modulos
func AllModuleRequest() []string{
  var listModules []Module
  
  ses, c := accessDB(modules_collection)
  defer ses.Close()
  
  err := c.Find(bson.M{}).All(&listModules)
  VerifyErr(err)
  js, __ := json.Marshal(listModules)
  if __ != nil || js == nil{
    panic(__)
  }
  lenModules := len(listModules)
  listArrayId := make([]string,lenModules)
  for j:=0; j< lenModules; j++ {
    listArrayId[j] = listModules[j].Id_moduleiot
  }
  return listArrayId
}

// busca si existe el modulo
func ModulesRequest(id_module string) Module{
  var ob []Module
  
  ses, c := accessDB(modules_collection)
  defer ses.Close()
  
  err := c.Find(bson.M{"id_moduleiot":id_module,"sensors.state": "free"}).All(&ob)
  VerifyErr(err)
  js, __ := json.Marshal(ob)
  if __ != nil || js == nil{
    panic(__)
  }
  return ob[0]
}

// almacena un dato
func DataMeasuredAddRequest(msg MQTT.Message) {
  var ob DataMeasured
  json.Unmarshal([]byte(msg.Payload()), &ob)
  DataMeasuredAdd(ob)
  Logger.Info("Data ingresada: %+v \n", ob)
}

// anade un dato
func DataMeasuredAdd(ob DataMeasured){
  ses, c := accessDB(datameasured_collection)
  defer ses.Close()
  err := c.Insert(&ob)
  VerifyErr(err)
}
