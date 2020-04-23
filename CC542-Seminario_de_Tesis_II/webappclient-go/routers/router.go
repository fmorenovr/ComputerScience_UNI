package routers

import (
  "net/http";
  "webappclient-go/conf";
  "github.com/gorilla/mux";
  "github.com/gorilla/handlers";
  bghandlers "webappclient-go/handlers";
  "github.com/jenazads/gojwt";
)

func HttpListenerServiceInit(method string){
  // router
  router := mux.NewRouter()
  //router.PathPrefix("/assets").Handler(AssetsDirHandler)
  router.HandleFunc("/", bghandlers.IndexHandler)
  router.HandleFunc("/app", bghandlers.AppHandler)
  router.HandleFunc("/app/", bghandlers.AppHandler)
  router.HandleFunc("/contactUs", bghandlers.ContactUsHandler)
  router.HandleFunc("/contactUs/", bghandlers.ContactUsHandler)
  router.HandleFunc("/contacted", bghandlers.ContactedHandler)
  router.HandleFunc("/uploadImages", bghandlers.UploadImagesHandler)
  router.HandleFunc("/sessionExpired", bghandlers.SessionExpiredHandler)
  router.HandleFunc("/dashboard", bghandlers.DashboardHandler)
  router.HandleFunc("/infoConnection", bghandlers.InfoConnectionHandler)
  router.NotFoundHandler = http.HandlerFunc(bghandlers.NotFoundHandler)
  
  routerCorsHttp := handlers.CORS(
    handlers.AllowedOrigins([]string{"*"}),
    handlers.AllowedMethods([]string{"PUT", "PATCH", "GET", "POST", "OPTIONS", "DELETE"}),
    handlers.AllowedHeaders([]string{"Origin", "X-requested-with", "Content-Type",
      "Accept", "Authorization", "X-csrftoken"}),
    handlers.ExposedHeaders([]string{"Content-Length"}),
    handlers.AllowCredentials(),
  )(router)

  muxHttp := http.NewServeMux()
  
  muxHttp.Handle("/", routerCorsHttp)
  
  /* example for gojwt */
  muxHttp.HandleFunc("/setToken", bghandlers.SetTokenHandler)
  muxHttp.HandleFunc("/login", bghandlers.LoginHandler)
  muxHttp.HandleFunc("/profile", gojwt.MiddlewareGojwtHeaders(bghandlers.WithAuthHandler, bghandlers.NoAuthHandler, conf.GojwtObject))
  
  // directories
  muxHttp.Handle("/views/", conf.ViewsStrip)
  muxHttp.Handle("/assets/", conf.AssetsStrip)
  muxHttp.Handle("/mobile/", conf.MobileStrip)
  muxHttp.Handle("/angularJS-app/", conf.AJSStrip)
  muxHttp.Handle("/images/", conf.ImagesStrip)
  
  conf.MuxInitService(method, muxHttp)
}

