package models

import (
	"errors"
	"fmt"
)

// db.sensores.aggregate([{$unwind:"$tipo_sensor"},{$project:{_id:0,tipo_sensor:1,"prefijo":1}}])

type DataArray struct{
  Array_json   []DataMeasured `json:"array_json" bson:"array_json"`
}

var listDatoMob DataArray

func init(){}

func GetAllDataMeasuredMobile() DataArray{
  listDatoMob = dataMeasuredMobileRequest("","","","","","","","")
  return listDatoMob
}

func GetDataMeasuredMobile(Id_usuario string,Tipo_sensor string,Id_usr string, dateinit string, datefin string, horainit string, horafin string, last string) (listUsrxSensor DataArray, err error) {
  id_user := UsernameToId(Id_usuario)
  listDatoMob = dataMeasuredMobileRequest(id_user,Tipo_sensor,Id_usr, dateinit, datefin, horainit, horafin, last)
  if listDatoMob.Array_json ==nil {
    fmt.Printf("\nNo se encontro Sensores !\n\n")
    return listDatoMob, errors.New("Sensor no existe")
  } else {
    return listDatoMob, nil
  }
}
