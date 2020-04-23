package conf

import(
  "net/http";
)

// metodo tcp, tcps
var Protocol string;

const(
// mqtt clients
//var rootclient = "CTIC-SMARTCITY"
  Rootclient   = "Master"
  Idrootclient = "IdClient_CloudMaster"
  Freeclient   = "freeuser"
  Idfreeclient = "IdClient_CloudMasterFree"
// hostnames
  Ipbroker = "localhost"
  Ipdb     = "localhost"
  Hostname = "localhost"
// http
  ListenHTTP   = ":1885"
  Httpprotocol = "http://"
// https
  ListenHTTPS   = ":1886"
  Httpsprotocol = "https://"
  HttpKeypath   = "tls-ssl/https/beagons-mqtt.key"
  HttpCrtpath   = "tls-ssl/https/beagons-mqtt.crt"
// mqtt
  Portbroker = "1883"
// mqtts
  Portssl     = "2883"
  MqttCaPath  = "tls-ssl/mqtts/ca.crt"
  MqttCrtPath = "tls-ssl/mqtts/mqttclient.crt"
  MqttKeyPath = "tls-ssl/mqtts/mqttclient.key"
// topics
  FreeTopic = "free"
  Qos byte  = 0
// collections
  Alerts_collection        = "alerts"
  Modules_collection       = "modulesiot"
  Datameasured_collection  = "datameasured"
  Alertmeasured_collection = "alertmeasured"
// templates
  Template_index          = "src/index.html"
  Template_notFound       = "src/templates/notFound.html"
  Template_infoConnection = "src/templates/infoConnection.html"
// directory paths
  aJSPath     = "src/angularJS-app"
  assetsPath  = "src/assets"
  viewsPath   = "src/views"
  tplsPath    = "src/templates"
  mobilePath  = "src/mobile"
  PhotosPath  = "src/assets/images/profile_photos"
// directory file system
  AJSDir     = http.Dir(aJSPath)
  AssetsDir  = http.Dir(assetsPath)
  ViewsDir   = http.Dir(viewsPath)
  TplsDir    = http.Dir(tplsPath)
  MobileDir  = http.Dir(mobilePath)
  ImagesDir  = http.Dir(PhotosPath)
)

var (
// fileserver
  AJSDirHandler    = http.FileServer(AJSDir)
  AssetsDirHandler = http.FileServer(AssetsDir)
  ViewsDirHandler  = http.FileServer(ViewsDir)
  TplsDirHandler   = http.FileServer(TplsDir)
  MobileDirHandler = http.FileServer(MobileDir)
  ImagesDirHandler = http.FileServer(ImagesDir)
// stripPrefix
  ViewsStrip  = http.StripPrefix("/views/",ViewsDirHandler)
  AssetsStrip = http.StripPrefix("/assets/",AssetsDirHandler)
  MobileStrip = http.StripPrefix("/mobile/",MobileDirHandler)
  AJSStrip    = http.StripPrefix("/angularJS-app/",AJSDirHandler)
  ImagesStrip = http.StripPrefix("/images/",ImagesDirHandler)
)

// info to show
type InfoConnection struct {
  Host        string
  Path        string
  Addr        string
  Port        string
}
