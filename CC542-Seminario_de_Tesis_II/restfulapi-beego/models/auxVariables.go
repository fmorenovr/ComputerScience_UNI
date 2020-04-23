package models

import(
  "gopkg.in/mgo.v2";
  "github.com/jenazads/gojwt";
  "github.com/jenazads/logs";
  patterns "restfulapi-beego/patterns";
)

// logger
var Logger = logs.NewLogger(10000)

// pub/priv keys
const (
  privRSAKeyPath    = "/tls-ssl/jwtkeys/rsakey.pem"
  pubRSAKeyPath     = "/tls-ssl/jwtkeys/rsakey.pem.pub"
  privECDSAKeyPath  = "/tls-ssl/jwtkeys/ecdsakey.pem"
  pubECDSAKeyPath   = "/tls-ssl/jwtkeys/ecdsakey.pem.pub"
  BeagonsAuthHeader = "BeaGons-rest-JWT"
  BeagonsNameServer = "beagonsServer"
)

// gojweto: path of priv, pub, nameServer, secretKey, headerAuth, method, bytesmethod, time exp (hours)
//var GojwtObject, _ = gojwt.NewGojwtHMAC_SHA(BeagonsNameServer, "beagons-rest", BeagonsAuthHeader, "512", 24)
//var GojwtObject, _ = gojwt.NewGojwtRSA(BeagonsNameServer, BeagonsAuthHeader, privRSAKeyPath, pubRSAKeyPath, "256", 24)
var GojwtObject, _ = gojwt.NewGojwtECDSA(BeagonsNameServer, BeagonsAuthHeader, privECDSAKeyPath, pubECDSAKeyPath, "384", 24)

// info to show
type InfoConnection struct {
  Host        string
  Path        string
  Addr        string
  Port        string
}

// templates
const(
  Template_index        = "src/templates/index.html"
  Template_noAuth       = "src/templates/noAuth.html"
  Template_withAuth     = "src/templates/withAuth.html"
  Template_notFound     = "src/templates/notFound.html"
  Template_infoConnect  = "src/templates/infoConnection.html"
)

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

