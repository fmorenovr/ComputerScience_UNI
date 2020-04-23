package models

import(
  "fmt";
  "strconv";
  "encoding/json";
  "gopkg.in/mgo.v2/bson";
)

// retorna los datos
func alertMeasuredRequest(Id_user string, Id_alert string, dateInit string, dateFin string, horaInit string, horaFin string, Last string) []AlertMeasured{
  var listAlerta []AlertMeasured
  var leng, num int
  var err error
  var lastitems = 10
  ses, c := accessDB(alertmeasured_collection)
  defer ses.Close()
  if Id_user !="" {
    listalertAux := idAlertsRequest(Id_user)
    if Id_alert == ""{
      leng, err = c.Find(bson.M{"id_alert": bson.M{"$in":listalertAux}}).Count()
      err = c.Find(bson.M{"id_alert": bson.M{"$in":listalertAux}}).Sort("id_alert").All(&listAlerta)
    } else if Id_alert != ""{
      if Id_alert != "" && stringInSlice(Id_alert,listalertAux){
        if dateInit != "" && dateFin != "" {
          if horaInit != "" && horaFin != "" {
            leng, err = c.Find(bson.M{"id_alert": Id_alert,"date":bson.M{"$gte":dateInit,"$lte":dateFin},"hour":bson.M{"$gte":horaInit,"$lte":horaFin}}).Count()
            if Last == ""{
              err = c.Find(bson.M{"id_alert": Id_alert,"date":bson.M{"$gte":dateInit,"$lte":dateFin},"hour":bson.M{"$gte":horaInit,"$lte":horaFin}}).Sort("date").All(&listAlerta)
            } else if Last =="last"{
              err = c.Find(bson.M{"id_alert": Id_alert,"date":bson.M{"$gte":dateInit,"$lte":dateFin},"hour":bson.M{"$gte":horaInit,"$lte":horaFin}}).Skip(leng-lastitems).Sort("date").All(&listAlerta)
            } else if num, err = strconv.Atoi(Last); err == nil {
        		  err = c.Find(bson.M{"id_alert": Id_alert,"date":bson.M{"$gte":dateInit,"$lte":dateFin},"hour":bson.M{"$gte":horaInit,"$lte":horaFin}}).Skip(leng-num).Sort("date").All(&listAlerta)
	          }
          } else {
            leng, err = c.Find(bson.M{"id_alert": Id_alert,"date":bson.M{"$gte":dateInit,"$lte":dateFin}}).Count()
            if Last == ""{
              err = c.Find(bson.M{"id_alert": Id_alert,"date":bson.M{"$gte":dateInit,"$lte":dateFin}}).Sort("date").All(&listAlerta)
            } else if Last =="last"{
              err = c.Find(bson.M{"id_alert": Id_alert,"date":bson.M{"$gte":dateInit,"$lte":dateFin}}).Skip(leng-lastitems).Sort("date").All(&listAlerta)
            } else if num, err = strconv.Atoi(Last); err == nil {
        		  err = c.Find(bson.M{"id_alert": Id_alert,"date":bson.M{"$gte":dateInit,"$lte":dateFin}}).Skip(leng-num).Sort("date").All(&listAlerta)
	          }
          }
        } else {
          leng, err = c.Find(bson.M{"id_alert": Id_alert}).Count()
          if Last == ""{
            err = c.Find(bson.M{"id_alert": Id_alert}).Sort("date").All(&listAlerta)
          } else if Last =="last"{
            err = c.Find(bson.M{"id_alert": Id_alert}).Skip(leng-lastitems).Sort("date").All(&listAlerta)
          } else if num, err = strconv.Atoi(Last); err == nil {
      		  err = c.Find(bson.M{"id_alert": Id_alert}).Skip(leng-num).Sort("date").All(&listAlerta)
	        }
	      }
      }
    }
  } else {
    leng, err = c.Find(bson.M{}).Count()
    err = c.Find(bson.M{ }).Sort("id_alert").Skip(leng-lastitems).All(&listAlerta)
  }
  js, __ := json.Marshal(listAlerta)
  verifyErr(__)
  fmt.Printf("\nlista de las alertas:\n%s\n\n",js)
  return listAlerta
}
