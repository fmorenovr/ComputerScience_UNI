package models

import(
  "fmt";
  "encoding/json";
  "gopkg.in/mgo.v2/bson";
)

// numero de modules
func moduleLength() (leng int){
  var length int
  var err error
  ses, c := accessDB(modules_collection)
  defer ses.Close()
  length, err = c.Count()
  verifyErr(err)
  return length
}

// lista los modulos por usuario
func idModulesRequest(Id_user string) []string{
  var idmod UsersModAl
  var err error
  ses, c := accessDB(users_collection)
  defer ses.Close()
  err = c.Find(bson.M{"id_user":Id_user}).One(&idmod)
  verifyErr(err)
  js, __ := json.Marshal(idmod)
  verifyErr(__)
  fmt.Printf("\nlista de Modulos del usuario %s:\n%s\n\n",Id_user,js)
  lenModules := len(idmod.Modules)
  listmodule := make([]string,lenModules)
  for i:=0; i< lenModules;i++ {
    listmodule[i] = idmod.Modules[i].Id_moduleiot
  }
  fmt.Printf("\n\n")
  return listmodule
}

// lista los modulos
func moduleRequest(Id string, cst string) []Module{
  var listModules []Module
  var err error
  ses, c := accessDB(modules_collection)
  defer ses.Close()
  if Id != ""{
    listmoduleAux := idModulesRequest(Id)
    if cst ==""{
      err = c.Find(bson.M{"id_moduleiot": bson.M{"$in":listmoduleAux} }).All(&listModules)
    } else if cst != "" && stringInSlice(cst,listmoduleAux){
      err = c.Find(bson.M{"id_moduleiot": cst}).All(&listModules)
    }
  } else {
    err = c.Find(bson.M{}).All(&listModules)
  }
  verifyErr(err)
  js, __ := json.Marshal(listModules)
  verifyErr(__)
  fmt.Printf("\nlista de IoTDevices:\n%s\n\n",js)
  return listModules
}

// anade un moduloIoT
func moduleAdd(ob Module){
  var err error
  ob.Passwd = Encrypt(ob.Id_moduleiot)
  var auth ModuleAuth
	auth.Id_moduleiot = ob.Id_moduleiot
	auth.Passwd = ob.Passwd
	addAuthModules(auth)
  ses, c := accessDB(modules_collection)
  defer ses.Close()
  err = c.Insert(&ob)
  verifyErr(err)
}

// actualiza un modulo
func moduleUpdate(id_cansat string, ob Module) (error){
  var err error
  ses, c := accessDB(modules_collection)
  defer ses.Close()
  colQuerier := bson.M{"id_moduleiot":id_cansat}
  change := bson.M{
    "$set":bson.M{
      "model":ob.Model,
      "longuitude":ob.Longuitude,
      "latitude": ob.Latitude,
      "zone":ob.Zone,
      "sector":ob.Sector,
      "last_modification":ob.Last_modification,
      "polygons":ob.Polygons,
      "sensors":ob.Sensors}}
  err = c.Update(colQuerier, change)
  verifyErr(err)
  return err
}

// elimina un modulo
func moduleDelete(id_module string) (error){
  var err error
  removeAuthModules(id_module)
  ses, c := accessDB(modules_collection)
  defer ses.Close()
  err = c.Remove(bson.M{"id_moduleiot": id_module})
  verifyErr(err)
  return err
}

// anade module al superuser que contiene todos los modules
func addAuthModules(auth ModuleAuth) {
  var err error
  ses, c := accessDB(users_collection)
  defer ses.Close()
  colQuerier := bson.M{"id_user":adminId}
  change := bson.M{
    "$push":bson.M{
      "modules":
        auth,}}
  err = c.Update(colQuerier, change)
  verifyErr(err)
}

// remueve de todos los users asociados la info del modulo
func removeAuthModules(Id string) {
  var usrs []string
  var err error
  ses, c := accessDB(users_collection)
  defer ses.Close()
  err = c.Find(bson.M{"modules.id_moduleiot":Id}).Distinct("id_user",&usrs)
  verifyErr(err)

  fmt.Println(usrs)
  for i:= 0; i< len(usrs); i++ {
    colQuerier := bson.M{"id_user":usrs[i]}
    change := bson.M{
      "$pull":bson.M{
        "modules": bson.M{
          "id_moduleiot":Id,
      }}}
  //db.users.update({"id_user":"U0001"},{"$pull":{"modules":{"id_moduleiot":"C001"}}})    
    err = c.Update(colQuerier, change)
    verifyErr(err)
  }
}

// retorna los id-passwd de un listado de modules
func authModulesRequest(moduls []string) []ModuleAuth{
  var idmod UsersModAl
  var err error
  ses, c := accessDB(users_collection)
  defer ses.Close()
  err = c.Find(bson.M{"id_user":adminId}).One(&idmod)
  verifyErr(err)
  js, __ := json.Marshal(idmod)
  verifyErr(__)
  fmt.Printf("\nlista de Modulos:\n%s\n\n",js)
  lenModules := len(idmod.Modules)
  lenmoduls  := len(moduls)
  listauth := make([]ModuleAuth,lenmoduls)
  for j:=0; j< lenmoduls; j++ {
    for i:=0; i< lenModules; i++ {
      if moduls[j] == idmod.Modules[i].Id_moduleiot {
        listauth[j].Id_moduleiot = idmod.Modules[i].Id_moduleiot
        listauth[j].Passwd       = idmod.Modules[i].Passwd
      }
    }
  }
  return listauth
}
