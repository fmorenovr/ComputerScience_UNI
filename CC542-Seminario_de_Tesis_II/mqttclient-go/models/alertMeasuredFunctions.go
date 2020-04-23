package models

import (
  "encoding/json";
  "gopkg.in/mgo.v2/bson";
  MQTT "github.com/eclipse/paho.mqtt.golang";
)

// devuelve todas las alertas
func AllAlertRequest() []string{
  var listAlerts []Alert
  
  ses, c := accessDB(alerts_collection)
  defer ses.Close()
  
  err := c.Find(bson.M{}).All(&listAlerts)
  VerifyErr(err)
  js, __ := json.Marshal(listAlerts)
  if __ != nil || js == nil{
    panic(__)
  }
  lenAlerts := len(listAlerts)
  listArrayId := make([]string,lenAlerts)
  for j:=0; j< lenAlerts; j++ {
    listArrayId[j] = listAlerts[j].Id_alert
  }
  return listArrayId
}

// busca si existe la alarma
func AlertsRequest(id_alert string) Alert{
  var ob []Alert
  
  ses, c := accessDB(alerts_collection)
  defer ses.Close()
  
  err := c.Find(bson.M{"id_alert":id_alert}).All(&ob)
  VerifyErr(err)
  js, __ := json.Marshal(ob)
  if __ != nil || js == nil{
    panic(__)
  }
  return ob[0]
}

// almacena una alerta
func AlertMeasuredAddRequest(msg MQTT.Message) {
  var ob AlertMeasured
  json.Unmarshal([]byte(msg.Payload()), &ob)
  AlertMeasuredAdd(ob)
  Logger.Info("Alerta ingresada: %+v \n", ob)
}

// anade un alerta
func AlertMeasuredAdd(ob AlertMeasured){
  ses, c := accessDB(alertmeasured_collection)
  defer ses.Close()
  err := c.Insert(&ob)
  VerifyErr(err)
}
