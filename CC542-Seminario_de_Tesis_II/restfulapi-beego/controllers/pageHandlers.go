package controllers

import (
  "time";
  "net/http";
  "html/template";
  "restfulapi-beego/models";
)
// NotFound
func NotFoundHandler(w http.ResponseWriter, r *http.Request) {
  start := time.Now()
  t, _ := template.ParseFiles(models.Template_notFound)
  t.Execute(w, nil)
  models.Logger.Error("Page Not Found. Completed %s in %v\n", r.URL.Path, time.Since(start))
}

// NoAuth
func NoAuthHandler(w http.ResponseWriter, r *http.Request) {
  start := time.Now()
  t, _ := template.ParseFiles(models.Template_noAuth)
  t.Execute(w, nil)
  models.Logger.Warn("You don't have access to see this page. Completed %s in %v\n", r.URL.Path, time.Since(start))
}
