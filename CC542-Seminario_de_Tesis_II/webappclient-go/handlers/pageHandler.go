package handlers

import (
  "io";
  "os";
  "time";
  "strings";
  "net/http";
  "html/template";
  "webappclient-go/conf";
)
// SessionExpired
func SessionExpiredHandler(w http.ResponseWriter, r *http.Request) {
  start := time.Now()
  conf.LogServer(r.Method, r.URL.Path,"SessionExpired")
  t, _ := template.ParseFiles(conf.Template_sessionExpired)
  t.Execute(w, nil)
  conf.Logger.Info("Completed %s in %v\n", r.URL.Path, time.Since(start))
}

// NotFound
func NotFoundHandler(w http.ResponseWriter, r *http.Request) {
  start := time.Now()
  conf.LogServer(r.Method, r.URL.Path,"NotFound")
  t, _ := template.ParseFiles(conf.Template_notFound)
  t.Execute(w, nil)
  conf.Logger.Info("Completed %s in %v\n", r.URL.Path, time.Since(start))
}

// NoAuth
func NoAuthHandler(w http.ResponseWriter, r *http.Request) {
  start := time.Now()
  conf.LogServer(r.Method, r.URL.Path,"NoAuth")
  t, _ := template.ParseFiles(conf.Template_noAuth)
  t.Execute(w, nil)
  conf.Logger.Info("Completed %s in %v\n", r.URL.Path, time.Since(start))
}

// WithAuth
func WithAuthHandler(w http.ResponseWriter, r *http.Request) {
  start := time.Now()
  conf.LogServer(r.Method, r.URL.Path,"WithAuth")
  t, _ := template.ParseFiles(conf.Template_withAuth)
  t.Execute(w, nil)
  conf.Logger.Info("Completed %s in %v\n", r.URL.Path, time.Since(start))
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
  conf.Logger.Info("Completed %s in %v\n", path, time.Since(start))
}

// index
func IndexHandler(w http.ResponseWriter, r *http.Request) {
  start := time.Now()
  conf.LogServer(r.Method, r.URL.Path,"Index")
  p, _ := conf.LoadPage(conf.Template_index)
  w.Write(p.Body)
  conf.Logger.Info("Completed %s in %v\n", r.URL.Path, time.Since(start))
}

// dashboard
func DashboardHandler(w http.ResponseWriter, r *http.Request) {
  start := time.Now()
  conf.LogServer(r.Method, r.URL.Path,"Dashboard")
  t, _ := template.ParseFiles(conf.Template_dashboard)
  t.Execute(w, nil)
  conf.Logger.Info("Completed %s in %v\n", r.URL.Path, time.Since(start))
}

// contactUs
func ContactUsHandler(w http.ResponseWriter, r *http.Request) {
  r.ParseForm()
  start := time.Now()
  conf.LogServer(r.Method, r.URL.Path,"ContactUs")
  conf.Logger.Info("method: %s", r.Method)
  if r.Method == "GET" {
    t, _ := template.ParseFiles(conf.Template_contactUs)
    t.Execute(w, conf.IsMail{Correct: "none"})
  } else {
    if conf.VerifyEmail(r.Form["email"][0]){
      conf.SentEmails(r, conf.Template_mailToServer, conf.Template_mailToUser)
      http.Redirect(w, r, "/contacted/", http.StatusMovedPermanently)
      //t, _ := template.ParseFiles(conf.Template_contacted)
      //t.Execute(w, nil)
    } else {
      t, _ := template.ParseFiles(conf.Template_contactUs)
      t.Execute(w, conf.IsMail{Correct: "block"})
    }
  }
  conf.Logger.Info("Completed %s in %v\n", r.URL.Path, time.Since(start))
}

// contacted
func ContactedHandler(w http.ResponseWriter, r *http.Request) {
  r.ParseForm()
  start := time.Now()
  conf.LogServer(r.Method, r.URL.Path,"Contacted")
  t, _ := template.ParseFiles(conf.Template_contacted)
  t.Execute(w, nil)
  conf.Logger.Info("Completed %s in %v\n", r.URL.Path, time.Since(start))
}

// app
func AppHandler(w http.ResponseWriter, r *http.Request) {
  start := time.Now()
  conf.LogServer(r.Method, r.URL.Path,"App")
  t, _ := template.ParseFiles(conf.Template_app)
  t.Execute(w, nil)
  conf.Logger.Info("Completed %s in %v\n", r.URL.Path, time.Since(start))
}

// alunoUNI
func AlumnoUNIHandler(w http.ResponseWriter, r *http.Request) {
  start := time.Now()
  conf.LogServer(r.Method, r.URL.Path,"Alumno UNI App")
  t, _ := template.ParseFiles(conf.Template_alumnouni)
  t.Execute(w, nil)
  conf.Logger.Info("Completed %s in %v\n", r.URL.Path, time.Since(start))
}

// upload images
func UploadImagesHandler(w http.ResponseWriter, r *http.Request) {
  start := time.Now()
  conf.LogServer(r.Method, r.URL.Path,"Upload Images")
  if r.Method == "POST" {
    // opening file uploaded from client
    r.ParseMultipartForm(32 << 20)
    file, handler, err := r.FormFile("uploadfile")
    defer file.Close()
    conf.VerifyError(err)
    usernameFile := r.Form["id_user"][0]
    
    // Creating a new file to copy in server
    conf.Logger.Info("The header message is: %v", handler.Header)
    newFileName := conf.GenerateFileName(handler.Filename, usernameFile)
    newfile, err := os.OpenFile(conf.PhotosPath+"/"+newFileName, os.O_WRONLY|os.O_CREATE, 0666)
    defer newfile.Close()
    conf.VerifyError(err)
    io.Copy(newfile, file)
  }
  http.Redirect(w, r, "/dashboard", http.StatusMovedPermanently)
  conf.Logger.Info("Completed %s in %v\n", r.URL.Path, time.Since(start))
}
