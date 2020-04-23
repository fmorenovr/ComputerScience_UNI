package models

import(
  "fmt";
  "strconv";
  "encoding/json";
  "gopkg.in/mgo.v2/bson";
)

// retorna los datos
func dataMeasuredRequest(Id_user string,Tipo_sensor string,Id_module string, dateInit string, dateFin string, horaInit string, horaFin string, Last string) []DataMeasured{
  var listDato []DataMeasured
  var leng, num int
  var err error
  var lastitems = 10
  ses, c := accessDB(datameasured_collection)
  defer ses.Close()
  if Id_user !="" {
    listmoduleAux := idModulesRequest(Id_user)
    if Tipo_sensor == ""{
      leng, err = c.Find(bson.M{"id_moduleiot": bson.M{"$in":listmoduleAux}}).Count()
      err = c.Find(bson.M{"id_moduleiot": bson.M{"$in":listmoduleAux}}).Sort("id_moduleiot").All(&listDato)
    } else if Tipo_sensor !=""{
      if Id_module == ""{
        err = c.Find(bson.M{"id_moduleiot": bson.M{"$in":listmoduleAux},"type": Tipo_sensor}).Sort("id_moduleiot","date").All(&listDato)
      } else if Id_module != "" && stringInSlice(Id_module,listmoduleAux){
        if dateInit != "" && dateFin != "" {
          if horaInit != "" && horaFin != "" {
            leng, err = c.Find(bson.M{"id_moduleiot": Id_module,"type": Tipo_sensor,"date":bson.M{"$gte":dateInit+" "+horaInit,"$lte":dateFin+" "+horaFin}}).Count()
            if Last == ""{
              err = c.Find(bson.M{"id_moduleiot": Id_module,"type": Tipo_sensor,"date":bson.M{"$gte":dateInit+" "+horaInit,"$lte":dateFin+" "+horaFin}}).Sort("date").All(&listDato)
            } else if Last =="last"{
              err = c.Find(bson.M{"id_moduleiot": Id_module,"type": Tipo_sensor,"date":bson.M{"$gte":dateInit+" "+horaInit,"$lte":dateFin+" "+horaFin}}).Skip(leng-lastitems).Sort("date").All(&listDato)
            } else if num, err = strconv.Atoi(Last); err == nil {
        		  err = c.Find(bson.M{"id_moduleiot": Id_module,"type": Tipo_sensor,"date":bson.M{"$gte":dateInit+" "+horaInit,"$lte":dateFin+" "+horaFin}}).Skip(leng-num).Sort("date").All(&listDato)
	          }
          } else {
            leng, err = c.Find(bson.M{"id_moduleiot": Id_module,"type": Tipo_sensor,"date":bson.M{"$gte":dateInit+" 00:00:00","$lte":dateFin+" 00:00:00"}}).Count()
            if Last == ""{
              err = c.Find(bson.M{"id_moduleiot": Id_module,"type": Tipo_sensor,"date":bson.M{"$gte":dateInit+" 00:00:00","$lte":dateFin+" 00:00:00"}}).Sort("date").All(&listDato)
            } else if Last =="last"{
              err = c.Find(bson.M{"id_moduleiot": Id_module,"type": Tipo_sensor,"date":bson.M{"$gte":dateInit+" 00:00:00","$lte":dateFin+" 00:00:00"}}).Skip(leng-lastitems).Sort("date").All(&listDato)
            } else if num, err = strconv.Atoi(Last); err == nil {
        		  err = c.Find(bson.M{"id_moduleiot": Id_module,"type": Tipo_sensor,"date":bson.M{"$gte":dateInit+" 00:00:00","$lte":dateFin+" 00:00:00"}}).Skip(leng-num).Sort("date").All(&listDato)
	          }
          }
        } else {
          leng, err = c.Find(bson.M{"id_moduleiot": Id_module,"type": Tipo_sensor}).Count()
          if Last == ""{
            err = c.Find(bson.M{"id_moduleiot": Id_module,"type": Tipo_sensor}).Sort("date").All(&listDato)
          } else if Last =="last"{
            err = c.Find(bson.M{"id_moduleiot": Id_module,"type": Tipo_sensor}).Skip(leng-lastitems).Sort("date").All(&listDato)
          } else if num, err = strconv.Atoi(Last); err == nil {
      		  err = c.Find(bson.M{"id_moduleiot": Id_module,"type": Tipo_sensor}).Skip(leng-num).Sort("date").All(&listDato)
	        }
	      }
      }
    }
  } else {
    leng, err = c.Find(bson.M{}).Count()
    err = c.Find(bson.M{ }).Sort("id_moduleiot").Skip(leng-lastitems).All(&listDato)
  }
  js, __ := json.Marshal(listDato)
  verifyErr(__)
  fmt.Printf("\nlista de los datos de sensores por filtrado de tiempo:\n%s\n\n",js)
  return listDato
}
