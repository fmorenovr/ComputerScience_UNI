package models

import (
	"errors"
	"fmt"
)

/*type TypeSensor struct{
  Type_sensor []string `json:"type_sensor"`
}

var listTipo TypeSensor*/

var listTipo []string

func init(){}

func GetAllTypeSensor() []string{
  listTipo = typeSensorRequest("")
  return listTipo
}

func GetTipoSensores(Id string) (sensor []string, err error) {
  id_user := UsernameToId(Id)
  listTipo = typeSensorRequest(id_user)
  if listTipo == nil {
    fmt.Printf("\nNo se encontro Sensores !\n\n")
    return listTipo, errors.New("Sensor no existe")
  } else {
    return listTipo, nil
  }
}

