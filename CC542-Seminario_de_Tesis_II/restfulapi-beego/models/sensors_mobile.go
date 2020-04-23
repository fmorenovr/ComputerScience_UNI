package models

import (
	"errors"
	"fmt"
)

type SensorArray struct{
  Array_json    []SensorMobile   `json:"array_json" bson:"array_json"`
}

type SensorMobile struct {
  Id_moduleiot    string   `json:"id_moduleiot" bson:"id_moduleiot"`
  Sensors       []Sensor   `json:"sensors"      bson:"sensors"`
}

// db.sensores.aggregate([{$unwind:"$tipo_sensor"},{$project:{_id:0,tipo_sensor:1,"prefijo":1}}])

var listSensoresMob SensorArray
//var listSensores []Sensor

func init() {}

func GetAllSensoresMobile() SensorArray {
//func GetAllSensores() []Sensor {
  listSensoresMob = sensorsMobileRequest("","")
	return listSensoresMob
}

func GetSensorMobileId(Id string, Tipo_sensor string) (sensor SensorArray, err error) {
  id_user := UsernameToId(Id)
//func GetSensorId(Tipo_sensor string) (sensor []Sensor, err error) {
  listSensoresMob = sensorsMobileRequest(id_user,Tipo_sensor)
  if listSensoresMob.Array_json ==nil {
    fmt.Printf("\nNo se encontro Sensores !\n\n")
    return listSensoresMob, errors.New("Sensor no existe")
  } else {
    return listSensoresMob, nil
  }
}
