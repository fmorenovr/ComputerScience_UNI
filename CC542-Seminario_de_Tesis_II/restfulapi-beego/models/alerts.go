package models

import (
	"errors"
	"strconv"
	"fmt"
)

type Alert struct{
  Id_alert            string      `json:"id_alert"          bson:"id_alert"`
  Passwd              string      `json:"passwd"            bson:"passwd"`
  Type                string      `json:"type"              bson:"type"`
  Parameters          []Params    `json:"parameters"        bson:"parameters"`
  Creation_date       string      `json:"creation_date"     bson:"creation_date"`
  Last_modification   string      `json:"last_modification" bson:"last_modification"`
}

type Params struct {
  Type_value   string    `json:"type"      bson:"type"`
  Min_value    float32   `json:"min_value" bson:"min_value"`
  Max_value    float32   `json:"max_value" bson:"max_value"`
}
// db.cansats.aggregate([{$unwind:"$id_sensores"},{$project:{_id:0,id_sensores:1}}])
// db.cansats.aggregate([{$unwind:"$id_sensores"},{$match:{"id_cansat":"C1001"}},{$project:{_id:0,id_sensores:1}}])

var listAlerts []Alert

func init(){
}

func GetAllAlerts() []Alert {
  listAlerts = alertRequest("","")
	return listAlerts
}

func GetAlert(Id_user string, Id_alert string) (alert []Alert, err error) {
  id_user := UsernameToId(Id_user)
  listAlerts = alertRequest(id_user, Id_alert)
  if listAlerts == nil {
    fmt.Printf("\nNo se encontro IoTDevice !\n\n")
    return nil, errors.New("IotDevice no existe")
  } else {
    return listAlerts, nil
  }
}

func createIDAlert() (cad string){
  var str string
  var leng = alertLength()
  if leng < 9 {
    str = "Alarm" + strconv.Itoa(leng+1)
  } else {
    if leng < 99 {
      str = "Alarm" + strconv.Itoa(leng+1)
    } else {
      if leng < 999 {
        str = "Alarm" + strconv.Itoa(leng+1)
      }
    }
  }
  return str
}

func AddAlert(object Alert, params []map[string]string) (Objstring string,err error) {
	object.Id_alert = createIDAlert()
	var paramsLen = len(params)
  paramsObj := make([]Params,paramsLen)
	var f32 float64
	for i:=0; i<paramsLen;i++ {
    paramsObj[i].Type_value = params[i]["type_value"]
    f32, err = strconv.ParseFloat(params[i]["min_value"],64)
    paramsObj[i].Min_value = float32(f32)
    f32, err = strconv.ParseFloat(params[i]["max_value"],64)
    paramsObj[i].Max_value = float32(f32)
  }
  object.Parameters = paramsObj
  alertAdd(object)
	return object.Id_alert, nil
}

func UpdateAlert(Id_alert string, obj Alert, params []map[string]string) (err error) {
  var paramsLen = len(params)
  paramsObj := make([]Params,paramsLen)
	var f32 float64
	for i:=0; i<paramsLen;i++ {
    paramsObj[i].Type_value = params[i]["type_value"]
    f32, err = strconv.ParseFloat(params[i]["min_value"],64)
    paramsObj[i].Min_value = float32(f32)
    f32, err = strconv.ParseFloat(params[i]["max_value"],64)
    paramsObj[i].Max_value = float32(f32)
  }
  obj.Parameters = paramsObj
  err = alertUpdate(Id_alert, obj)
	return err
}

func DeleteAlert(Id string) (err error){
	err = alertDelete(Id)
	return err
}
