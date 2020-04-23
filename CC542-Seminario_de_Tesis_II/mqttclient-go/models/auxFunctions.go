package models

import(
  "os";
  "gopkg.in/mgo.v2";
  patterns "mqttclient-go/patterns";
)

// acceso a la DB por cada consulta
func accessDB(collection string)(*mgo.Session, *mgo.Collection){
  session, errDial = patterns.GetSessErrMongoDBSession("Dial")
  VerifyErr(errDial)
  session.SetMode(mgo.Monotonic, true)
  sessionCopy := session.Copy()
  col := session.DB(patterns.Dbname).C(collection)
  return sessionCopy, col;
}

// verify errors
func VerifyErr(err error){
  if err != nil {
    Logger.Error("%s",err)
    os.Exit(1)
  }
}
