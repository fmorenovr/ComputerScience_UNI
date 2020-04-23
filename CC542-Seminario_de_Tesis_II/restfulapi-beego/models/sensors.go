package models

import (
	"errors"
	"fmt"
)

type SensorModule struct {
  Id_moduleiot    string   `json:"id_moduleiot" bson:"id_moduleiot"`
  Latitude        float64  `json:"latitude"     bson:"latitude"`
  Longuitude      float64  `json:"longuitude"   bson:"longuitude"`
  Zone            string   `json:"zone"         bson:"zone"`
  Sector          string   `json:"sector"       bson:"sector"`
  Polygons      []Polygon  `json:"polygons"     bson:"polygons"`
  Sensors       []Sensor   `json:"sensors"      bson:"sensors"`
}

// db.sensores.aggregate([{$unwind:"$tipo_sensor"},{$project:{_id:0,tipo_sensor:1,"prefijo":1}}])

var listSensores []SensorModule

func init() {}

func GetAllSensores() []SensorModule {
  listSensores = sensorsRequest("","")
	return listSensores
}

func GetSensorId(Id string, Tipo_sensor string) (sensor []SensorModule, err error) {
  id_user := UsernameToId(Id)
  listSensores = sensorsRequest(id_user,Tipo_sensor)
  if listSensores ==nil {
    fmt.Printf("\nNo se encontro Sensores !\n\n")
    return nil, errors.New("Sensor no existe")
  } else {
    return listSensores, nil
  }
}

