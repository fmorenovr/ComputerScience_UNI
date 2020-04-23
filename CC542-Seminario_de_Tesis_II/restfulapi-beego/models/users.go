package models

import (
  "fmt";
  "errors";
  "strconv";
)

// db.sensores.aggregate([{$unwind:"$tipo_sensor"},{$project:{_id:0,tipo_sensor:1,"prefijo":1}}])
// db.users.find({},{_id:0,id_user:1}).pretty()

type User struct{
  Id_user            string       `json:"id_user"           bson:"id_user"`
  Name               string       `json:"name"              bson:"name"`
  Lastname           string       `json:"lastname"          bson:"lastname"`
  Document           string       `json:"document"          bson:"document"`
  Email              string       `json:"email"             bson:"email"`
  Username           string       `json:"username"          bson:"username"`
  Password           string       `json:"password"          bson:"password"`
  Registration_date  string       `json:"registration_date" bson:"registration_date"`
  Last_modification  string       `json:"last_modification" bson:"last_modification"`
  Modules            []ModuleAuth `json:"modules"           bson:"modules"`
  Alerts             []AlertAuth  `json:"alerts"            bson:"alerts"`
  Is_admin           bool         `json:"is_admin"          bson:"is_admin"`
}

// lista de alertas por usuario
type AlertAuth struct{
  Id_alert     string   `json:"id_alert" bson:"id_alert"`
  Passwd       string   `json:"passwd"   bson:"passwd"`
}

// lista de modules por usuario
type ModuleAuth struct {
  Id_moduleiot string   `json:"id_moduleiot" bson:"id_moduleiot"`
  Passwd       string   `json:"passwd"       bson:"passwd"`
}

// almacena los modules y alerts por usuario (evitando data extra)
type UsersModAl struct {
  Modules  []ModuleAuth
  Alerts   []AlertAuth
}

var listUser []User

func init(){}

func GetAllUsers() []User{
  listUser = userRequest("")
  return listUser
}

func GetUser(Id_usr string) ([]User, error){
  listUser = userRequest(Id_usr)
  if listUser == nil {
    fmt.Printf("\nNo se encontro Users !\n\n")
    return nil, errors.New("User doesn't exist")
  } else {
    if listUser[0].Id_user == "U0000" {
      listUser[0].Is_admin = true
    } else {
      listUser[0].Is_admin = false
    }
  }
  return listUser, nil
}

func createIDUser() (cad string){
  var str string
  var leng = userLength()
  if leng < 9 {
    str = "U000" + strconv.Itoa(leng+1)
  } else {
    if leng < 99 {
      str = "U00" + strconv.Itoa(leng+1)
    } else {
      if leng < 999 {
        str = "U0" + strconv.Itoa(leng+1)
      } else {
        if leng < 9999 {
        str = "U"+strconv.Itoa(leng+1)
        }
      }
    }
  }
  return str
}

/* curl -d "id_usuario=U0004&nombre=Frank&apellido=Moreno&documento=72972154&username=can&password=123456&f_registro=2017-01-31&h_registro=07:11:00" http://localhost:6568/beagons/users
	*/
func AddUser(object User, modules []string, alerts []string) (ObjectId string, err error) {
	object.Id_user = createIDUser()
  userAdd(object,modules, alerts)
	return object.Id_user, nil
}

func UpdateUser(Id_user string, obj User, modules []string, alerts []string) (err error) {
  err = userUpdate(Id_user, obj, modules, alerts)
	return err
}

func DeleteUser(Id string) (err error){
	err = userDelete(Id)
	return err
}
