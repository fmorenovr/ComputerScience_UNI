package models

import(
  "fmt";
  "encoding/json";
  "gopkg.in/mgo.v2/bson";
)

// numero de alertas
func alertLength() (leng int){
  var length int
  var err error
  ses, c := accessDB(alerts_collection)
  defer ses.Close()
  length, err = c.Count()
  verifyErr(err)
  return length
}

// lista los alertas por usuario
func idAlertsRequest(Id_user string) []string{
  var idmod UsersModAl
  var err error
  ses, c := accessDB(users_collection)
  defer ses.Close()
  err = c.Find(bson.M{"id_user":Id_user}).One(&idmod)
  verifyErr(err)
  js, __ := json.Marshal(idmod)
  verifyErr(__)
  fmt.Printf("\nlista de Alertas del usuario %s:\n%s\n\n",Id_user,js)
  lenAlerts := len(idmod.Alerts)
  listalert := make([]string,lenAlerts)
  for i:=0; i< lenAlerts;i++ {
    listalert[i] = idmod.Alerts[i].Id_alert
  }
  fmt.Printf("\n\n")
  return listalert
}

// lista de alertas
func alertRequest(Id string, cst string) []Alert{
  var listAlerts []Alert
  var err error
  ses, c := accessDB(alerts_collection)
  defer ses.Close()
  if Id != ""{
    listalertAux := idAlertsRequest(Id)
    if cst ==""{
      err = c.Find(bson.M{"id_alert": bson.M{"$in":listalertAux} }).All(&listAlerts)
    } else if cst != "" && stringInSlice(cst,listalertAux){
      err = c.Find(bson.M{"id_alert": cst}).All(&listAlerts)
    }
  } else {
    err = c.Find(bson.M{}).All(&listAlerts)
  }
  verifyErr(err)
  js, __ := json.Marshal(listAlerts)
  verifyErr(__)
  fmt.Printf("\nlista de Alerts:\n%s\n\n",js)
  return listAlerts
}

// anade una alerta
func alertAdd(ob Alert){
  var err error
  //ob.Passwd = generarPassword(5)
  ob.Passwd = Encrypt(ob.Id_alert)
  var auth AlertAuth
	auth.Id_alert = ob.Id_alert
	auth.Passwd = ob.Passwd
	addAuthAlerts(auth)
  ses, c := accessDB(alerts_collection)
  defer ses.Close()
  err = c.Insert(&ob)
  verifyErr(err)
}

// actualiza una alerta
func alertUpdate(id_cansat string, ob Alert) (error){
  var err error
  ses, c := accessDB(alerts_collection)
  defer ses.Close()
  colQuerier := bson.M{"id_alert":id_cansat}
  change := bson.M{
    "$set":bson.M{
      "type":ob.Type,
      "last_modification":ob.Last_modification,
      "parameters":ob.Parameters}}
  err = c.Update(colQuerier, change)
  verifyErr(err)
  return err
}

// elimina una alerta
func alertDelete(id_alert string) (error){
  var err error
  removeAuthAlerts(id_alert)
  ses, c := accessDB(alerts_collection)
  defer ses.Close()
  err = c.Remove(bson.M{"id_alert": id_alert})
  verifyErr(err)
  return err
}

// anade alert al superuser que contiene todos las alerts
func addAuthAlerts(auth AlertAuth) {
  var err error
  ses, c := accessDB(users_collection)
  defer ses.Close()
  colQuerier := bson.M{"id_user":adminId}
  change := bson.M{
    "$push":bson.M{
      "alerts":
        auth,}}
  err = c.Update(colQuerier, change)
  verifyErr(err)
}

// remueve de todos los users asociados la info del alert
func removeAuthAlerts(Id string) {
  var err error
  var usrs []string
  ses, c := accessDB(users_collection)
  defer ses.Close()
  err = c.Find(bson.M{"alerts.id_alert":Id}).Distinct("id_user",&usrs)
  verifyErr(err)

  fmt.Println(usrs)
  for i:= 0; i< len(usrs); i++ {
    colQuerier := bson.M{"id_user":usrs[i]}
    change := bson.M{
      "$pull":bson.M{
        "alerts": bson.M{
          "id_alert":Id,
      }}}
    err = c.Update(colQuerier, change)
    verifyErr(err)
  }
}

// retorna los id-passwd de cada alert
func authAlertsRequest(alerts []string) []AlertAuth{
  var err error
  var idmod UsersModAl
  ses, c := accessDB(users_collection)
  defer ses.Close()
  err = c.Find(bson.M{"id_user":adminId}).One(&idmod)
  verifyErr(err)
  js, __ := json.Marshal(idmod)
  verifyErr(__)
  fmt.Printf("\nlista de Alertas:\n%s\n\n",js)
  lenAlerts := len(idmod.Alerts)
  lenalerts  := len(alerts)
  listauth := make([]AlertAuth,lenalerts)
  for j:=0; j< lenalerts; j++ {
    for i:=0; i< lenAlerts; i++ {
      if alerts[j] == idmod.Alerts[i].Id_alert {
        listauth[j].Id_alert = idmod.Alerts[i].Id_alert
        listauth[j].Passwd   = idmod.Alerts[i].Passwd
      }
    }
  }
  return listauth
}
