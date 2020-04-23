package models

import(
  "fmt";
  "encoding/json";
  "gopkg.in/mgo.v2/bson";
)

// retorna los modulos con los sensores asociados a un modulo
func sensorsRequest(Id string,Tipo string) []SensorModule{
  var listSensores []SensorModule
  var err error
  ses, c := accessDB(modules_collection)
  defer ses.Close()
  if Id != ""{
    listmoduleAux := idModulesRequest(Id)
    if Tipo == ""{
      err = c.Find(bson.M{"id_moduleiot": bson.M{"$in":listmoduleAux}}).Sort("id_moduleiot").All(&listSensores)
    } else {
      err = c.Find(bson.M{"id_moduleiot": bson.M{"$in":listmoduleAux},"sensors.type":Tipo}).All(&listSensores)
    }
  } else {
    err = c.Find(bson.M{}).Sort("id_moduleiot").All(&listSensores)
  }
  verifyErr(err)
  js, __ := json.Marshal(listSensores)
  verifyErr(__)
  fmt.Printf("\nlista de sensores:\n%s\n\n",js)
  return listSensores
}
