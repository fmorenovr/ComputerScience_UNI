package controllers

import (
	"encoding/json";
  "restfulapi-beego/models";
  "github.com/astaxie/beego";
  "github.com/jenazads/gojwt";
)

// Operations about user
type LoginController struct {
	beego.Controller
}

/*
// @Title Create
// @Description login
// @Param	body  body  models.Login  true  "The object content"
// @Success 200 {user} models.Login
// @Failure 403 body is empty
// @router /:username/:password [get]
func (o *LoginController) Get() {
  o.Ctx.ResponseWriter.Header().Add("Access-Control-Allow-Origin", "*")
  o.Ctx.ResponseWriter.Header().Add("Access-Control-Allow-Methods","POST, GET, OPTIONS, PUT, DELETE")
  o.Ctx.ResponseWriter.Header().Add("Access-Control-Allow-Headers", "Origin, X-Requested-With, Content-Type, Accept")
  var ob models.Login
  tokenString := ""
  ob.Username = o.Ctx.Input.Param(":username")
  ob.Password = o.Ctx.Input.Param(":password")
  objectid, err := models.VerifyLogin(ob)
  if err != nil {
    o.Data["json"] = err.Error()
  } else {
    if objectid {
      tokenString, _ = gojweto.CreateRS256Token(ob.Username)
      o.Data["json"] = gojweto.Credentials{Token: tokenString, Logged: objectid}
    } else {
      o.Data["json"] = map[string]bool{"Logged": objectid}
    }
  }
  o.ServeJSON()
}
*/

// @Title Create
// @Description login
// @Param	body  body  models.Login  true  "The object content"
// @Success 200 {user} models.Login
// @Failure 403 body is empty
// @router / [post]
func (o *LoginController) Post() {
  var ob models.Login
  json.Unmarshal(o.Ctx.Input.RequestBody, &ob)
  o.Ctx.Input.Bind(&ob.Username, "username")
  o.Ctx.Input.Bind(&ob.Password, "password")
  objectid, err := models.VerifyLogin(ob)
  
  if err != nil {
    o.Data["json"] = err.Error()
	} else {
    if objectid {
	    tokenString, _ := models.GojwtObject.CreateToken(ob.Username)
	    o.Data["json"] = gojwt.CredentialsAuth{Token: tokenString, Logged: objectid}
    } else {
      o.Data["json"] = gojwt.CredentialsNoAuth{Logged: objectid}
    }
  }
  o.ServeJSON()
}

