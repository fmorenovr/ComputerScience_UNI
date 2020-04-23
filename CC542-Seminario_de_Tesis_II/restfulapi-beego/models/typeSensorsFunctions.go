package models

import(
  "fmt";
  "encoding/json";
  "gopkg.in/mgo.v2/bson";
)

// distingue todos los tipos de sensores
func typeSensorRequest(Id_user string) []string{
  var listTipo []string
  var err error
  ses, c := accessDB(modules_collection)
  defer ses.Close()
  if Id_user != ""{
    listmoduleAux := idModulesRequest(Id_user)
    err = c.Find(bson.M{"id_moduleiot": bson.M{"$in":listmoduleAux}}).Distinct("sensors.type",&listTipo)
  } else {
    err = c.Find(bson.M{ }).Distinct("sensors.type",&listTipo)
  }
  verifyErr(err)
  js , __ := json.Marshal(listTipo)
  verifyErr(__)
  fmt.Printf("\nlista delos tipo de sensores:\n%s\n\n",js)
  return listTipo
}
