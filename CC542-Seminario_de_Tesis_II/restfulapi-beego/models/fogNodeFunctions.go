package models

import(
	"fmt";
  "encoding/json";
  "gopkg.in/mgo.v2/bson";
)

func fogNodeRequest(Id string) []FogNode{
  var listFogNodes []FogNode
  var err error
  ses, c := accessDB(fognodes_collection)
  defer ses.Close()
  if Id == ""{
    err = c.Find(bson.M{ }).Sort("id_fognode").All(&listFogNodes)
  } else {
    err = c.Find(bson.M{"name": Id}).All(&listFogNodes)
  }
  verifyErr(err)
  js, __ := json.Marshal(listFogNodes)
  verifyErr(__)
  fmt.Printf("\nlista de Fog Nodes:\n%s\n\n",js)
  return listFogNodes
}

func groupFogNodesByUsersRequest(username string) ([]UserFog){
  Id_user := UsernameToId(username)
  userAux, err := GetUser(username)
  verifyErr(err)
  // obtengo los modulos asociados al usuario
  var listFogNodes []FogNode
  var userFog []UserFog
  var userFogAux UserFog
  ses, c := accessDB(fognodes_collection)
  defer ses.Close()
  if Id_user != ""{
    listmodule := idModulesRequest(Id_user)
    fmt.Println(listmodule)
    err = c.Find(bson.M{"modules": bson.M{"$in":listmodule} }).All(&listFogNodes)
  } else {
    err = c.Find(bson.M{}).All(&listFogNodes)
  }
  verifyErr(err)
  userFogAux.Id_user = userAux[0].Id_user
  userFogAux.Name = userAux[0].Name
  userFogAux.Lastname = userAux[0].Lastname
  userFogAux.Document = userAux[0].Document
  userFogAux.Email = userAux[0].Email
  userFogAux.Username = userAux[0].Username
  userFogAux.Password = userAux[0].Password
  userFogAux.Registration_date = userAux[0].Registration_date
  userFogAux.Last_modification = userAux[0].Last_modification
  userFogAux.FogNodes = listFogNodes
  if userFogAux.Id_user == "U0000" {
    userFogAux.Is_admin = true
  } else {
    userFogAux.Is_admin = false
  }
  userFog = append(userFog, userFogAux)
  return userFog
}

func fogNodesLength() (leng int){
  var err error
  var length int
  ses, c := accessDB(fognodes_collection)
  defer ses.Close()
  length, err = c.Count()
  verifyErr(err)
  return length
}

func fogNodeAdd(ob FogNode, modules []string, alerts []string){
  var err error
  ob.Modules = modules
  ob.Alerts  = alerts
  ses, c := accessDB(fognodes_collection)
  defer ses.Close()
  err = c.Insert(&ob)
  verifyErr(err)
}

func fogNodeUpdate(id_fognode string, ob FogNode, modules []string, alerts []string) (error){
  var err error
  ob.Modules = modules
  ob.Alerts  = alerts
  ses, c := accessDB(fognodes_collection)
  defer ses.Close()
  colQuerier := bson.M{"id_fognode":id_fognode}
  change := bson.M{
    "$set":bson.M{
      "name":ob.Name,
      //"username":ob.Username,
      //"password": ob.Password,
      "accessPoint":ob.AccessPoint,
      "private_ip":ob.Private_ip,
      "latitude": ob.Latitude,
      "longuitude":ob.Longuitude,
      "last_modification": ob.Last_modification,
      "modules":ob.Modules,
      "alerts":ob.Alerts,}}
  err = c.Update(colQuerier, change)
  verifyErr(err)
  return err
}

func fogNodeDelete(id_fognode string) (error){
  var err error
  ses, c := accessDB(fognodes_collection)
  defer ses.Close()
  err = c.Remove(bson.M{"id_fognode": id_fognode})
  verifyErr(err)
  return err
}

