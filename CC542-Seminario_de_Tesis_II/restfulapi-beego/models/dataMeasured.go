package models

import (
	"errors"
	"fmt"
)

// db.sensores.aggregate([{$unwind:"$tipo_sensor"},{$project:{_id:0,tipo_sensor:1,"prefijo":1}}])

type DataMeasured struct{
  Id_moduleiot     string  `json:"id_moduleiot" bson:"id_moduleiot"`
  Id_sensor        string  `json:"id_sensor"    bson:"id_sensor"`
  Value            float32 `json:"value"        bson:"value"`
  Type             string  `json:"type"         bson:"type"`
  Date             string  `json:"date"         bson:"date"`
}

var listDato []DataMeasured

func init(){}

func GetAllDataMeasured() []DataMeasured{
  listDato = dataMeasuredRequest("","","","","","","","")
  return listDato
}

func GetDataMeasured(Id_usuario string,Tipo_sensor string,Id_usr string, dateinit string, datefin string, horainit string, horafin string, last string) (listUsrxSensor [] DataMeasured, err error) {
  id_user := UsernameToId(Id_usuario)
  listDato = dataMeasuredRequest(id_user,Tipo_sensor,Id_usr, dateinit, datefin, horainit, horafin, last)
  if listDato ==nil {
    fmt.Printf("\nNo se encontro Datos !\n\n")
    return nil, errors.New("Datos no existen")
  } else {
    return listDato, nil
  }
}
