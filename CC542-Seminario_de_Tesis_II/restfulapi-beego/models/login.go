package models

import (
  "fmt";
)

// db.sensores.aggregate([{$unwind:"$tipo_sensor"},{$project:{_id:0,tipo_sensor:1,"prefijo":1}}])
// db.users.find({},{_id:0,id_user:1}).pretty()

type Login struct{
  Username    string  `json:"username" bson:"username"`
  Password    string  `json:"password" bson:"password"`
}

var login Login

func init(){}

/* curl -d "id_usuario=U0004&nombre=Frank&apellido=Moreno&documento=72972154&username=can&password=123456&f_registro=2017-01-31&h_registro=07:11:00" http://localhost:6568/beagons/users
	*/
func VerifyLogin(object Login) (ObjectId bool, err error) {
  objlogin := loginRequest(object)
	if objlogin == (Login{}) {
    fmt.Printf("\nNo se encontro Usuario !\n\n")
    return false, nil
  } else {
    return true, nil
  }
}
