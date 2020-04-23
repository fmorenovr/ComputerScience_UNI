package models

import (
  "fmt";
  "errors";
  "strconv";
)

type FogNode struct{
  Id_fognode         string       `json:"id_fognode"        bson:"id_fognode"`
  Name               string       `json:"name"              bson:"name"`
  AccessPoint        string       `json:"accessPoint"         bson:"accessPoint"`
  Private_ip         string       `json:"private_ip"        bson:"private_ip"`
  Latitude           float64      `json:"latitude"          bson:"latitude"`
  Longuitude         float64      `json:"longuitude"        bson:"longuitude"`
  Modules            []string     `json:"modules"           bson:"modules"`
  Alerts             []string     `json:"alerts"            bson:"alerts"`
  Registration_date  string       `json:"registration_date" bson:"registration_date"`
  Last_modification  string       `json:"last_modification" bson:"last_modification"`
}

type UserFog struct{
  Id_user            string       `json:"id_user"           bson:"id_user"`
  Name               string       `json:"name"              bson:"name"`
  Lastname           string       `json:"lastname"          bson:"lastname"`
  Document           string       `json:"document"          bson:"document"`
  Email              string       `json:"email"             bson:"email"`
  Username           string       `json:"username"          bson:"username"`
  Password           string       `json:"password"          bson:"password"`
  Registration_date  string       `json:"registration_date" bson:"registration_date"`
  Last_modification  string       `json:"last_modification" bson:"last_modification"`
  FogNodes           []FogNode    `json:"fognodes"           bson:"fognodes"`
  Is_admin           bool         `json:"is_admin"          bson:"is_admin"`
}

var listFogs []FogNode

func init(){}

func GetAllFogNodes() []FogNode{
  listFogs = fogNodeRequest("")
  return listFogs
}

func GetFogNode(name_fognode string) ([]FogNode, error){
  listFogs = fogNodeRequest(name_fognode)
  if listFogs == nil {
    fmt.Printf("\nNo se encontro Fog Node !\n\n")
    return nil, errors.New("Fog Node no existe")
  }
  return listFogs, nil
}

func GetFogNodeByUser(username string) ([]UserFog, error){
  if usernameRequest(username){
    usersFog := groupFogNodesByUsersRequest(username)
    return usersFog, nil
  } else {
    fmt.Printf("\nNo Entro\n\n")
    return nil, errors.New("usuario no existe")
  }
}

func createIDFogNode() (cad string){
  var str string
  var leng = fogNodesLength()
  if leng < 9 {
    str = "FN000" + strconv.Itoa(leng+1)
  } else {
    if leng < 99 {
      str = "FN00" + strconv.Itoa(leng+1)
    } else {
      if leng < 999 {
        str = "FN0" + strconv.Itoa(leng+1)
      } else {
        if leng < 9999 {
        str = "FN"+strconv.Itoa(leng+1)
        }
      }
    }
  }
  return str
}

func AddFogNode(object FogNode, modules []string, alerts []string) (ObjectId string, err error) {
  object.Id_fognode = createIDFogNode()
  fogNodeAdd(object, modules, alerts)
  return object.Id_fognode, nil
}

func UpdateFogNode(Id_fognode string, obj FogNode, modules []string, alerts []string) (err error) {
  err = fogNodeUpdate(Id_fognode, obj, modules, alerts)
  return err
}

func DeleteFogNode(Id string) (err error){
  err = fogNodeDelete(Id)
  return err
}
