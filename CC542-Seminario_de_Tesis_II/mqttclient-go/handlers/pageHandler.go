package handlers

import (
  "time";
  "strings";
  "net/http";
  "html/template";
  "mqttclient-go/conf";
  "mqttclient-go/models";
)
// NotFound
func NotFoundHandler(w http.ResponseWriter, r *http.Request) {
  start := time.Now()
  conf.LogServer(r.Method, r.URL.Path,"NotFound")
  t, _ := template.ParseFiles(conf.Template_notFound)
  t.Execute(w, nil)
  models.Logger.Info("Completed %s in %v\n", r.URL.Path, time.Since(start))
}

// index
func IndexHandler(w http.ResponseWriter, r *http.Request) {
  start := time.Now()
  conf.LogServer(r.Method, r.URL.Path,"Index")
  t, _ := template.ParseFiles(conf.Template_index)
  t.Execute(w,nil)
  models.Logger.Info("Completed %s in %v\n", r.URL.Path, time.Since(start))
}

// infoConnection
func InfoConnectionHandler(w http.ResponseWriter, r *http.Request) {
  start := time.Now()
  conf.LogServer(r.Method, r.URL.Path,"InfoConnection")
  s := strings.Split(r.RemoteAddr, ":")
  host := r.URL.Host
  path := r.URL.Path
  addr, port := s[0], s[1]
  t, _ := template.ParseFiles(conf.Template_infoConnection)
  t.Execute(w, conf.InfoConnection{Host: host, Path: path, Addr: addr, Port: port})
  models.Logger.Info("Completed %s in %v\n", path, time.Since(start))
}
