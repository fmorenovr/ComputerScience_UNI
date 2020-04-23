package main
import (
    "fmt"
    "net/http"
    "gopkg.in/mgo.v2"
    "encoding/json"
    "gopkg.in/mgo.v2/bson"
)
/* en mongo escribir:
// use tesis
// db.prueba.insert({"meow":"primera_prueba"})
// db.prueba.insert({"_id":ObjectId("52ffc33cd85242f436000001"),"meow":"primera_prueba"})
// db.prueba.update({"_id":ObjectId("52ffc33cd85242f436000001")},{"meow":"primera_xd"})
// db.prueba.find()
// session, err := mgo.Dial(url)
// c := session.DB(database).C(collection)
// err := c.Find(query).One(&result)
*/

type Meow struct{
    Meow string `json:"meow"`
}

type Meows struct{
   Todo_Meow [] Meow `json:"array_json"`
}
var resultado []Meow
func consultaInfo(w http.ResponseWriter, r *http.Request) {
    session, err := mgo.Dial("localhost:27017")
    if err != nil {
            panic(err)
    }
    defer session.Close()
    session.SetMode(mgo.Monotonic, true)
    c := session.DB("tesis").C("prueba")
    
//    var resultado Meows
//    err = c.Find(bson.M{ }).All(&resultado.Todo_Meow)
    err = c.Find(bson.M{ }).All(&resultado)
    
    js, err := json.Marshal(resultado)
    if err != nil {
      http.Error(w, err.Error(), http.StatusInternalServerError)
      return
    }
    w.Header().Set("Content-Type", "application/json")
    fmt.Printf("%s\n",js)
    w.Write(js)
}

func main() {   
    http.HandleFunc("/", consultaInfo)
    http.ListenAndServe(":8082", nil)
}
