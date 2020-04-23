package models

import (
	"errors"
	"fmt"
)

/*type Zone struct{
  Zone []string `json:"zones"`
}

var listZone Zone*/

var listZone []string

func init(){}

func GetAllZones() []string{ //Zone{
  listZone = zoneRequest("")
  return listZone
}

func GetZone(id string) (sensor []string, err error) { //(sensor Zone, err error) {
  id_user := UsernameToId(id)
  listZone = zoneRequest(id_user)
  if listZone == nil {
    fmt.Printf("\nNo se encontro Zonas !\n\n")
    return listZone, errors.New("Zona no existe")
  } else {
    return listZone, nil
  }
}
