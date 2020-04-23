package routers

import (
  "net/http";
  "mqttclient-go/conf";
  "github.com/gorilla/mux";
  "mqttclient-go/handlers";
)

func MqttClientServiceInit(methodhttp string, methodMqtt string){
  // router
  router := mux.NewRouter()
  //router.PathPrefix("/assets").Handler(AssetsDirHandler)
  router.HandleFunc("/", handlers.InfoConnectionHandler)
  router.NotFoundHandler = http.HandlerFunc(handlers.NotFoundHandler)
  
  muxHttp := http.NewServeMux()
  muxHttp.Handle("/", router)
  
  // directories
  muxHttp.Handle("/views/", conf.ViewsStrip)
  muxHttp.Handle("/assets/", conf.AssetsStrip)
  muxHttp.Handle("/mobile/", conf.MobileStrip)
  muxHttp.Handle("/angularJS-app/", conf.AJSStrip)
  muxHttp.Handle("/images/", conf.ImagesStrip)
  
  conf.MuxInitService(methodhttp, methodMqtt, muxHttp)
}

