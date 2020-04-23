package models

import (
	"errors"
	"fmt"
)

type ModuleArray struct{
  Array_json  []ModuleMobile `json:"array_json" bson:"array_json"`
}

type SensorModuleMobile struct {
  Id_sensor        string  `json:"id_sensor" bson:"id_sensor"`
}

type ModuleMobile struct{
  Id_moduleiot        string                `json:"id_moduleiot"      bson:"id_moduleiot"`
  Passwd              string                `json:"passwd"            bson:"passwd"`
  Model               string                `json:"model"             bson:"model"`
  Latitude            float64               `json:"latitude"          bson:"latitude"`
  Longuitude          float64               `json:"longuitude"        bson:"longuitude"`
  Zone                string                `json:"zone"              bson:"zone"`
  Sector              string                `json:"sector"            bson:"sector"`
  Installation_date   string                `json:"installation_date" bson:"installation_date"`
  Polygons          []Polygon               `json:"polygons"          bson:"polygons"`
  Sensors           []SensorModuleMobile    `json:"sensors"           bson:"sensors"`
}

var listModulesMob ModuleArray

func init() {}

func GetAllModulesMobile() ModuleArray {
  listModulesMob = moduleMobileRequest("","")
	return listModulesMob
}

func GetModuleMobile(Id_user string, Id_module string) (module ModuleArray, err error) {
  id_user := UsernameToId(Id_user)
  listModulesMob = moduleMobileRequest(id_user, Id_module)
  if listModulesMob.Array_json == nil {
    fmt.Printf("\nNo se encontro IoTDevice !\n\n")
    return listModulesMob, errors.New("IotDevice no existe")
  } else {
    return listModulesMob, nil
  }
}
