package models

import(
	"fmt"
	"strconv"
  "encoding/json"
  "gopkg.in/mgo.v2/bson"
)

func moduleMobileRequest(Id string, cst string) ModuleArray{
  var listModules ModuleArray
  var err error
  ses, c := accessDB(modules_collection)
  defer ses.Close()
  if Id != ""{
    listmoduleAux := idModulesRequest(Id)
    if cst ==""{
      err = c.Find(bson.M{"id_moduleiot": bson.M{"$in":listmoduleAux} }).All(&listModules.Array_json)
    } else if cst != "" && stringInSlice(cst,listmoduleAux){
      err = c.Find(bson.M{"id_moduleiot": cst}).All(&listModules.Array_json)
    }
  } else {
    err = c.Find(bson.M{}).All(&listModules.Array_json)
  }
  verifyErr(err)
  js, __ := json.Marshal(listModules)
  verifyErr(__)
  fmt.Printf("\nlista de IoTDevices:\n%s\n\n",js)
  return listModules
}

func sensorsMobileRequest(Id string,Tipo string) SensorArray{
  var listSensores SensorArray
  var err error
  ses, c := accessDB(modules_collection)
  defer ses.Close()
  if Id != ""{
    listmoduleAux := idModulesRequest(Id)
    if Tipo == ""{
      err = c.Find(bson.M{"id_moduleiot": bson.M{"$in":listmoduleAux}}).Sort("id_moduleiot").All(&listSensores.Array_json)
    } else {
      err = c.Find(bson.M{"id_moduleiot": bson.M{"$in":listmoduleAux},"sensors.type":Tipo}).All(&listSensores.Array_json)
    }
  } else {
    err = c.Find(bson.M{}).Sort("id_moduleiot").All(&listSensores.Array_json)
  }
  verifyErr(err)
  js, __ := json.Marshal(listSensores)
  verifyErr(__)
  fmt.Printf("\nlista de sensores:\n%s\n\n",js)
  return listSensores
}

func dataMeasuredMobileRequest(Id_user string,Tipo_sensor string,Id_module string, dateInit string, dateFin string, horaInit string, horaFin string, Last string) DataArray{
  var listDato DataArray
  var leng, num int
  var lastitems = 10
  var err error
  ses, c := accessDB(datameasured_collection)
  defer ses.Close()
  if Id_user !="" {
    listmoduleAux := idModulesRequest(Id_user)
    if Tipo_sensor == ""{
      leng, err = c.Find(bson.M{"id_moduleiot": bson.M{"$in":listmoduleAux}}).Count()
      err = c.Find(bson.M{"id_moduleiot": bson.M{"$in":listmoduleAux}}).Sort("id_moduleiot").All(&listDato.Array_json)
    } else if Tipo_sensor !=""{
      if Id_module == ""{
        err = c.Find(bson.M{"id_moduleiot": bson.M{"$in":listmoduleAux},"type": Tipo_sensor}).Sort("id_moduleiot","date").All(&listDato.Array_json)
      } else if Id_module != "" && stringInSlice(Id_module,listmoduleAux){
        if dateInit != "" && dateFin != "" {
          if horaInit != "" && horaFin != "" {
            leng, err = c.Find(bson.M{"id_moduleiot": Id_module,"type": Tipo_sensor,"date":bson.M{"$gte":dateInit+" "+horaInit,"$lte":dateFin+" "+horaFin}}).Count()
            if Last == ""{
              err = c.Find(bson.M{"id_moduleiot": Id_module,"type": Tipo_sensor,"date":bson.M{"$gte":dateInit+" "+horaInit,"$lte":dateFin+" "+horaFin}}).Sort("date").All(&listDato.Array_json)
            } else if Last =="last"{
              err = c.Find(bson.M{"id_moduleiot": Id_module,"type": Tipo_sensor,"date":bson.M{"$gte":dateInit+" "+horaInit,"$lte":dateFin+" "+horaFin}}).Skip(leng-lastitems).Sort("date").All(&listDato.Array_json)
            } else if num, err = strconv.Atoi(Last); err == nil {
        		  err = c.Find(bson.M{"id_moduleiot": Id_module,"type": Tipo_sensor,"date":bson.M{"$gte":dateInit+" "+horaInit,"$lte":dateFin+" "+horaFin}}).Skip(leng-num).Sort("date").All(&listDato.Array_json)
	          }
          } else {
            leng, err = c.Find(bson.M{"id_moduleiot": Id_module,"type": Tipo_sensor,"date":bson.M{"$gte":dateInit+" 00:00:00","$lte":dateFin+" 00:00:00"}}).Count()
            if Last == ""{
              err = c.Find(bson.M{"id_moduleiot": Id_module,"type": Tipo_sensor,"date":bson.M{"$gte":dateInit+" 00:00:00","$lte":dateFin+" 00:00:00"}}).Sort("date").All(&listDato.Array_json)
            } else if Last =="last"{
              err = c.Find(bson.M{"id_moduleiot": Id_module,"type": Tipo_sensor,"date":bson.M{"$gte":dateInit+" 00:00:00","$lte":dateFin+" 00:00:00"}}).Skip(leng-lastitems).Sort("date").All(&listDato.Array_json)
            } else if num, err = strconv.Atoi(Last); err == nil {
        		  err = c.Find(bson.M{"id_moduleiot": Id_module,"type": Tipo_sensor,"date":bson.M{"$gte":dateInit+" 00:00:00","$lte":dateFin+" 00:00:00"}}).Skip(leng-num).Sort("date").All(&listDato.Array_json)
	          }
          }
        } else {
          leng, err = c.Find(bson.M{"id_moduleiot": Id_module,"type": Tipo_sensor}).Count()
          if Last == ""{
            err = c.Find(bson.M{"id_moduleiot": Id_module,"type": Tipo_sensor}).Sort("date").All(&listDato.Array_json)
          } else if Last =="last"{
            err = c.Find(bson.M{"id_moduleiot": Id_module,"type": Tipo_sensor}).Skip(leng-lastitems).Sort("date").All(&listDato.Array_json)
          } else if num, err = strconv.Atoi(Last); err == nil {
      		  err = c.Find(bson.M{"id_moduleiot": Id_module,"type": Tipo_sensor}).Skip(leng-num).Sort("date").All(&listDato.Array_json)
	        }
	      }
      }
    }
  } else {
    leng, err = c.Find(bson.M{}).Count()
    err = c.Find(bson.M{ }).Sort("id_moduleiot").Skip(leng-lastitems).All(&listDato.Array_json)
  }
  
  js, __ := json.Marshal(listDato)
  if __ != nil {
    panic(__)
  }
  fmt.Printf("\nlista de los datos de sensores:\n%s\n\n",js)
  return listDato
}
