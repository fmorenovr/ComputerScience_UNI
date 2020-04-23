package conf

import (
  _ "restfulapi-beego/routers";
  "github.com/astaxie/beego";
  "github.com/astaxie/beego/plugins/cors";
)

func RestfulAPIServiceInit(method string){

  beego.InsertFilter("*", beego.BeforeRouter, cors.Allow(&cors.Options{
    AllowOrigins:  []string{"*"},
    AllowMethods:  []string{"PUT", "PATCH", "GET", "POST", "OPTIONS", "DELETE"},
    AllowHeaders:  []string{"Origin", "X-requested-with", "Content-Type",
      "Accept", "Authorization", "BeaGons-rest-JWT", "X-csrftoken"},
    ExposeHeaders: []string{"Content-Length"},
    AllowCredentials: true,
  }));

  beego.SetStaticPath("assets", "src/assets")

  beego.BConfig.RunMode = "dev" 
  beego.BConfig.WebConfig.AutoRender = false
  beego.BConfig.WebConfig.EnableDocs = true
  beego.BConfig.WebConfig.DirectoryIndex = true
  beego.BConfig.CopyRequestBody = true
  beego.BConfig.Listen.HTTPSCertFile = "tls-ssl/https/beagons-rest.crt"
  beego.BConfig.Listen.HTTPSKeyFile = "tls-ssl/https/beagons-rest.key"
  beego.BConfig.Listen.HTTPPort = 6568
  beego.BConfig.Listen.HTTPSPort = 6568
  if method == "HTTP" {
    beego.BConfig.Listen.EnableHTTP = true
    beego.BConfig.Listen.EnableHTTPS = false
  } else if method == "HTTPS" {
    beego.BConfig.Listen.EnableHTTP = false
    beego.BConfig.Listen.EnableHTTPS = true
  }
  beego.Run()
}

