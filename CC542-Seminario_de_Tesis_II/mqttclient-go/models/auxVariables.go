package models

import(
  "gopkg.in/mgo.v2";
  "github.com/astaxie/beego/logs";
  patterns "mqttclient-go/patterns";
)

// logger
var Logger = logs.NewLogger(10000)

// collections
const(
  adminId                  = patterns.AdminId
  users_collection         = patterns.Users_collection
  alerts_collection        = patterns.Alerts_collection
  modules_collection       = patterns.Modules_collection
  alertmeasured_collection = patterns.Alertmeasured_collection
  datameasured_collection  = patterns.Datameasured_collection
  fognodes_collection      = patterns.Fognodes_collection
)

var session *mgo.Session
var errDial error

