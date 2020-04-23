package patterns

import(
  "time";
  "gopkg.in/mgo.v2";
)

const(
  dbip                     = "localhost"
  dbport                   = "27017"
  Dbname                   = "Beagons"
  AdminId                  = "U0000"
  Users_collection         = "users"
  Alerts_collection        = "alerts"
  Modules_collection       = "modulesiot"
  Alertmeasured_collection = "alertmeasured"
  Datameasured_collection  = "datameasured"
  Fognodes_collection      = "fognodes"
  urldb                    = dbip+":"+dbport
  authUserName             = "beagons-admin"
  authPassword             = "smrtct"
)

var mongoDBDialInfo = &mgo.DialInfo{
  Addrs:    []string{urldb},
  Timeout:  60 * time.Second,
  Database: Dbname,
  Username: authUserName,
  Password: authPassword,
}
