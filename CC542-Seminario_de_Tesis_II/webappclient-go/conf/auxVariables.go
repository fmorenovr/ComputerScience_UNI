package conf

import(
  "net/http";
  "github.com/jenazads/gojwt";
  "github.com/astaxie/beego/logs";
)

// logger
var Logger = logs.NewLogger(10000)

// jwt
var GojwtObject, _ = gojwt.NewGojwt()

const(
// hostnames
  Hostname = "localhost"
// https
  HttpKeypath   = "tls-ssl/https/beagons-web.key"
  HttpCrtpath   = "tls-ssl/https/beagons-web.crt"
  Httpsprotocol = "https://"
  ListenHTTPS   = ":443"
// http
  Httpprotocol   = "http://"
  ListenHTTP     = ":80"
// smtp
  ServerMail     = "beagons@uni.edu.pe"
  ServerPassword = "beagons2016"
  Mailport       = ":465"
  Mailhost       = "smtp.gmail.com"
  Mailprotocol   = "tcp"
  MailDomain     = Mailhost + Mailport
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

//alumno uni app
var Template_alumnouni  = "src/templates/alumnouni.html"

// templates
const(
  Template_index          = "src/index.html"
  Template_app            = "src/templates/app.html"
  Template_noAuth         = "src/templates/noAuth.html"
  Template_withAuth       = "src/templates/withAuth.html"
  Template_notFound       = "src/templates/notFound.html"
  Template_contacted      = "src/templates/contacted.html"
  Template_contactUs      = "src/templates/contactUs.html"
  Template_dashboard      = "src/templates/dashboard.html"
  Template_mailToUser     = "src/templates/mailToUser.html"
  Template_mailToServer   = "src/templates/mailToServer.html"
  Template_sessionExpired = "src/templates/sessionExpired.html"
  Template_infoConnection = "src/templates/infoConnection.html"
)

// mail destinatio
type MailDest struct {
  Name      string
  Last      string
  Telefono  string
  Email     string
  Message   string
}

// info to show
type InfoConnection struct {
  Host        string
  Path        string
  Addr        string
  Port        string
}

// verifiy email
type IsMail struct {
  Correct string
}

// page struct
type Page struct {
  Title   string
  Body  []byte
}
