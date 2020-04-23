package conf

import (
  "net/http";
  "crypto/tls";
)

func MuxInitService(method string, muxHttp *http.ServeMux){
  if method == "HTTP" {
    server := &http.Server{
      Addr   : ListenHTTP,
      Handler: muxHttp,
    }
    Logger.Info("webAppClient-Go Service Start")
    Logger.Info("listening on %s%s%s",Httpprotocol,Hostname,ListenHTTP)
    err := server.ListenAndServe()
    //err := http.ListenAndServe(ListenHTTP, nil)
    VerifyError(err)
  } else if method == "HTTPS" {
    serverTLS := &http.Server{
      Addr        : ListenHTTPS,
      Handler     : muxHttp,
      TLSConfig   : NewTLSHTTPConfig(),
      TLSNextProto: make(map[string]func(*http.Server, *tls.Conn, http.Handler), 0),
    }
    Logger.Info("webAppClient-Go with TLS/SSL Service Start")
    Logger.Info("listening on %s%s%s",Httpsprotocol,Hostname,ListenHTTPS)
    err := serverTLS.ListenAndServeTLS(HttpCrtpath, HttpKeypath)
    //err := http.ListenAndServeTLS(ListenHTTPS, Crtpath, Keypath, nil)
    VerifyError(err)
  } else if method == "Redirect" {
    Logger.Info("webAppClient-Go Service Start")
    Logger.Info("listening on %s%s%s",Httpprotocol,Hostname,ListenHTTP)
    server := &http.Server{
      Addr   : ListenHTTP,
      Handler: http.HandlerFunc(RedirectHandler),
    }
    
	  Logger.Info("webAppClient-Go with TLS/SSL Service Start")
    Logger.Info("listening on %s%s%s",Httpsprotocol,Hostname,ListenHTTPS)
    serverTLS := &http.Server{
      Addr        : ListenHTTPS,
      Handler     : muxHttp,
      TLSConfig   : NewTLSHTTPConfig(),
      TLSNextProto: make(map[string]func(*http.Server, *tls.Conn, http.Handler), 0),
    }
    
    go serverTLS.ListenAndServeTLS(HttpCrtpath, HttpKeypath)
    err := server.ListenAndServe()
    //err := http.ListenAndServe(ListenHTTP, http.HandlerFunc(RedirectHandler))
    VerifyError(err)
  }
}

// redirect to another page
func RedirectHandler(w http.ResponseWriter, r *http.Request) {
  Logger.Info("Redirecting from %s to %s", ListenHTTP, ListenHTTPS)
  http.Redirect(w, r, Httpsprotocol+Hostname+r.RequestURI, http.StatusMovedPermanently)
}

// tls ssl keys
func NewTLSHTTPConfig() (*tls.Config) {
	return &tls.Config{
    MinVersion:               tls.VersionTLS12,
    CurvePreferences:         []tls.CurveID{tls.CurveP521, tls.CurveP384, tls.CurveP256},
    PreferServerCipherSuites: true,
    CipherSuites: []uint16{
        tls.TLS_ECDHE_RSA_WITH_AES_256_GCM_SHA384,
        tls.TLS_ECDHE_RSA_WITH_AES_256_CBC_SHA,
        tls.TLS_RSA_WITH_AES_256_GCM_SHA384,
        tls.TLS_RSA_WITH_AES_256_CBC_SHA,
    },
  }
}
