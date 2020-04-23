package models

import (
	"errors"
	"strconv"
	"fmt"
)

type Module struct{
  Id_moduleiot        string   `json:"id_moduleiot"      bson:"id_moduleiot"`
  Passwd              string   `json:"passwd"            bson:"passwd"`
  Model               string   `json:"model"             bson:"model"`
  Latitude            float64  `json:"latitude"          bson:"latitude"`
  Longuitude          float64  `json:"longuitude"        bson:"longuitude"`
  Zone                string   `json:"zone"              bson:"zone"`
  Sector              string   `json:"sector"            bson:"sector"`
  Installation_date   string   `json:"installation_date" bson:"installation_date"`
  Last_modification   string   `json:"last_modification" bson:"last_modification"`
  Polygons          []Polygon  `json:"polygons"          bson:"polygons"`
  Sensors           []Sensor   `json:"sensors"           bson:"sensors"`
}

type Sensor struct {
  Id_sensor        string  `json:"id_sensor"      bson:"id_sensor"`
  Type             string  `json:"type"           bson:"type"`
  State            string  `json:"state"          bson:"state"`
  Unit             string  `json:"unit"           bson:"unit"`
  Model            string  `json:"model"          bson:"model"`
  Date_installed   string  `json:"date_installed" bson:"date_installed"`
}

type Polygon struct{
  Latitude     float64  `json:"latitude"   bson:"latitude"`
  Longuitude   float64  `json:"longuitude" bson:"longuitude"`
}

// db.cansats.aggregate([{$unwind:"$id_sensores"},{$project:{_id:0,id_sensores:1}}])
// db.cansats.aggregate([{$unwind:"$id_sensores"},{$match:{"id_cansat":"C1001"}},{$project:{_id:0,id_sensores:1}}])

var listModules []Module

func init(){}

func GetAllModules() []Module {
  listModules = moduleRequest("","")
	return listModules
}

func GetModule(Id_user string, Id_module string) (module []Module, err error) {
  id_user := UsernameToId(Id_user)
  listModules = moduleRequest(id_user, Id_module)
  if listModules == nil {
    fmt.Printf("\nNo se encontro IoTDevice !\n\n")
    return nil, errors.New("IotDevice no existe")
  } else {
    return listModules, nil
  }
}

func createIDModule() (cad string){
  var str string
  var leng = moduleLength()
  if leng < 9 {
    str = "C00" + strconv.Itoa(leng+1)
  } else {
    if leng < 99 {
      str = "C0" + strconv.Itoa(leng+1)
    } else {
      if leng < 999 {
        str = "C" + strconv.Itoa(leng+1)
      }
    }
  }
  return str
}

/* curl -d "id_usuario=U0004&nombre=Frank&apellido=Moreno&documento=72972154&username=can&password=123456&f_registro=2017-01-31&h_registro=07:11:00" http://localhost:6568/beagons/usuarios
	*/
func AddIoTDevice(object Module, polys []map[string]string, sens []map[string]string) (ObjectId string, err error) {
	object.Id_moduleiot = createIDModule()
	var polen = len(polys)
  var senslen = len(sens)
  polsObj := make([]Polygon,polen)
	sensObj := make([]Sensor,senslen)
	for i:=0; i<polen;i++ {
    polsObj[i].Latitude, err = strconv.ParseFloat(polys[i]["latitude"],64)
    polsObj[i].Longuitude, err = strconv.ParseFloat(polys[i]["longuitude"],64)
  }
  for i:=0; i<senslen;i++ {
    sensObj[i].Type = sens[i]["type"]
    sensObj[i].State = sens[i]["state"]
    sensObj[i].Unit = sens[i]["unit"]
    sensObj[i].Model = sens[i]["model"]
    sensObj[i].Date_installed = sens[i]["date_installed"]
  }
  object.Sensors = sensObj
  object.Polygons = polsObj
  moduleAdd(object)
	return object.Id_moduleiot, nil
}

func UpdateIoTDevice(Id_iot string, obj Module, polys []map[string]string, sens []map[string]string) (err error) {
  var polen = len(polys)
  var senslen = len(sens)
  polsObj := make([]Polygon,polen)
	sensObj := make([]Sensor,senslen)
	for i:=0; i<polen;i++ {
    polsObj[i].Latitude, err = strconv.ParseFloat(polys[i]["latitude"],64)
    polsObj[i].Longuitude, err = strconv.ParseFloat(polys[i]["longuitude"],64)
  }
  for i:=0; i<senslen;i++ {
    sensObj[i].Type = sens[i]["type"]
    sensObj[i].State = sens[i]["state"]
    sensObj[i].Unit = sens[i]["unit"]
    sensObj[i].Model = sens[i]["model"]
    sensObj[i].Date_installed = sens[i]["date_installed"]
  }
  obj.Sensors = sensObj
  obj.Polygons = polsObj
  err = moduleUpdate(Id_iot, obj)
	return err
}

func DeleteIoTDevice(Id string) (err error){
	err = moduleDelete(Id)
	return err
}
