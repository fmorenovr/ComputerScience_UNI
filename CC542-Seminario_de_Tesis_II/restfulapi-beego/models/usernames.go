package models

import (
	"fmt"
)

/*type Username struct{
  Username []string `json:"usernames"`
}

var listUsernames Username*/

var listUsernames bool

func init(){}

func GetAllUsernames() bool{
  listUsernames = usernameRequest("")
  return listUsernames
}

func GetUsername(id string) (sensor bool, err error) {
  listUsernames = usernameRequest(id)
  if listUsernames == false {
    fmt.Printf("\nNo se encontro ese username !\n\n")
    return listUsernames, nil
  } else {
    return listUsernames, nil
  }
}
