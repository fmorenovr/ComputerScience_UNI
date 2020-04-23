package models

import(
  "fmt";
  "encoding/json";
  "gopkg.in/mgo.v2/bson";
)

// distincion de las zonas
func zoneRequest(Id_user string) []string{ //Zone{
  var listZone []string // Zone
  var err error
  ses, c := accessDB(modules_collection)
  defer ses.Close()
  if Id_user != ""{
    listmoduleAux := idModulesRequest(Id_user)
    err = c.Find(bson.M{"id_moduleiot": bson.M{"$in":listmoduleAux}}).Distinct("zone",&listZone)//.Zone)
  } else {
    err = c.Find(bson.M{ }).Distinct("zone",&listZone)//.Zone)
  }
  verifyErr(err)
  js , __ := json.Marshal(listZone)
  verifyErr(__)
  fmt.Printf("\nlista de las zones:\n%s\n\n",js)
  return listZone
}
