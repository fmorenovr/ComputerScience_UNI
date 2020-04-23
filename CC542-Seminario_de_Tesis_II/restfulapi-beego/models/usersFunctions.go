package models

import(
	"fmt";
  "encoding/json";
  "gopkg.in/mgo.v2/bson";
)

// lista de usuarios
func userRequest(Id string) []User{
  var listUsers []User
  var err error
  ses, c := accessDB(users_collection)
  defer ses.Close()
  if Id == ""{
    err = c.Find(bson.M{ }).Sort("id_user").All(&listUsers)
  } else {
    err = c.Find(bson.M{"username": Id}).All(&listUsers)
  }
  verifyErr(err)
  js, __ := json.Marshal(listUsers)
  verifyErr(__)
  fmt.Printf("\nlista de Usuarios:\n%s\n\n",js)
  return listUsers
}

func userLength() (leng int){
  var length int
  var err error
  ses, c := accessDB(users_collection)
  defer ses.Close()
  length, err = c.Count()
  verifyErr(err)
  return length
}

func userAdd(ob User, modules []string, alerts []string){
  var err error
  list_modulo := authModulesRequest(modules)
  list_alert  := authAlertsRequest(alerts)
  ob.Modules = list_modulo
  ob.Alerts  = list_alert
  ses, c := accessDB(users_collection)
  defer ses.Close()
  err = c.Insert(&ob)
  verifyErr(err)
}

func userUpdate(id_user string, ob User, modules []string, alerts []string) (error){
  var err error
  list_modulo := authModulesRequest(modules)
  list_alert  := authAlertsRequest(alerts)
  ob.Modules = list_modulo
  ob.Alerts  = list_alert
  ses, c := accessDB(users_collection)
  defer ses.Close()
  colQuerier := bson.M{"id_user":id_user}
  change := bson.M{
    "$set":bson.M{
      "name":ob.Name,
      "lastname":ob.Lastname,
      "email":ob.Email,
      "document":ob.Document,
      "username":ob.Username,
      "password": ob.Password,
      "last_modification": ob.Last_modification,
      "modules":ob.Modules,
      "alerts":ob.Alerts,}}
  err = c.Update(colQuerier, change)
  verifyErr(err)
  return err
}

func userDelete(id_user string) (error){
  var err error
  ses, c := accessDB(users_collection)
  defer ses.Close()
  err = c.Remove(bson.M{"id_user": id_user})
  verifyErr(err)
  return err
}

