package models

import(
  "fmt";
  "time";
  "math/rand";
  "gopkg.in/mgo.v2";
  "github.com/astaxie/beego/logs";
  patterns "restfulapi-beego/patterns";
)

func init(){
  Logger.SetLogger(logs.AdapterMultiFile, `{"filename":"beagonsLogs/beagonsRequest.log","separate":["emergency", "alert", "critical", "error", "warning", "notice", "info", "debug"]}`)
}

// acceso a la DB por cada consulta
func accessDB(collection string)(*mgo.Session, *mgo.Collection){
  session, errDial = patterns.GetSessErrMongoDBSession("Dial")
  verifyErr(errDial)
  session.SetMode(mgo.Monotonic, true)
  sessionCopy := session.Copy()
  col := session.DB(patterns.Dbname).C(collection)
  return sessionCopy, col;
}

// verifica el error
func verifyErr(err error){
  if err != nil {
    fmt.Printf("\nError: %s\n",err)
    Logger.Critical("Error founded: %s", err)
  }
}

// genera un password aleatoriamente
func generarPassword(longitud int) (cad string){
  rand.Seed(time.Now().UTC().UnixNano())
  caracteres := "abcdefghijkmnpqrtuvwxyzABCDEFGHIJKLMNPQRTUVWXYZ2346789";
  contraseña := "";
  for i:=0; i<longitud; i++{
    ln := rand.Intn(len(caracteres))
    contraseña += string(caracteres[ln]);
  }
  return contraseña;
}

// verifica si exite un elemento en una lista
func stringInSlice(a string, list []string) (bool) {
  for _, b:= range list {
    if b==a {
      return true
    }
  }
  return false
}

// invierte un string
func Encrypt(s string) (result string) {
  for _,v := range s {
    result = string(v) + result
  }
  return result
}
