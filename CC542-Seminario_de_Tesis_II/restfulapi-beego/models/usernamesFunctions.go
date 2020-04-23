package models

import(
  "fmt";
  "encoding/json";
  "gopkg.in/mgo.v2/bson";
)

// devuelve el Id por cada Username
func UsernameToId(Id_user string) string {
  var userToEval []User
  var err error
  ses, c := accessDB(users_collection)
  defer ses.Close()
  err = c.Find(bson.M{"username":Id_user}).All(&userToEval)
  verifyErr(err)
  js, __ := json.Marshal(userToEval)
  verifyErr(__)
  fmt.Printf("\nel usuario es: \n%s\n\n",js)
  if userToEval != nil {
    return userToEval[0].Id_user
  } else {
    return "No existe"
  }
}
// verifica que exista el username
func usernameRequest(Id_user string) (bool){
  var listUsername []string
  var exist = false
  var err error
  ses, c := accessDB(users_collection)
  defer ses.Close()
  err = c.Find(bson.M{ }).Distinct("username",&listUsername)
  //verifyErr(err)
  fmt.Println(err)
  if Id_user != ""{
    for _, v := range listUsername {
      if v == Id_user {
        fmt.Printf("\n encontrado ! : %s \n\n",v)
        exist = true
        break
      }
    }
  }
  
  js , __ := json.Marshal(listUsername)
  verifyErr(__)
  fmt.Printf("\nlista de las usernames:\n%s\n\n",js)
  return exist
}
