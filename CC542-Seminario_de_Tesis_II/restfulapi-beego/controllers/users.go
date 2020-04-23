package controllers

import (
  "time";
  "encoding/json";
  "restfulapi-beego/models";
  //"github.com/astaxie/beego";
)

// Operations about user
type UserController struct {
	//beego.Controller
	GoJwetoController
}

// @Title GetAll
// @Description Get all users
// @Success 200 {User} models.User
// @Failure 403 :Id_user is empty
// @router / [get]
func (o *UserController) GetAll() {
  start := time.Now()
	obs := models.GetAllUsers()
	o.Data["json"] = obs
  models.Logger.Debug("Completed [GET] users/ in %v\n", time.Since(start))
	o.ServeJSON()
}

// @Title Get User
// @Description find user by userid
// @Param	Username query string true "the id_user you want to get"
// @Success 200 {User} models.User
// @Failure 403 :Id_user is empty
// @router /:Username [get]
func (o *UserController) Get() {
  start := time.Now()
	Id_user := o.Ctx.Input.Param(":Username")
	if Id_user != "" {
		ob, err := models.GetUser(Id_user)
		if err != nil {
			o.Data["json"] = err.Error()
		} else {
			o.Data["json"] = ob
		}
	}
  models.Logger.Debug("Completed [GET] users/%s in %v\n", Id_user, time.Since(start))
	o.ServeJSON()
}

// @Title Create
// @Description create user
// @Param	body  body  models.User  true  "The object content"
// @Success 200 {user} models.User
// @Failure 403 body is empty
// @router / [post]
func (o *UserController) Post() {
  start := time.Now()
	var ob models.User
  var modules []string
  var alerts  []string
	json.Unmarshal(o.Ctx.Input.RequestBody, &ob)
  o.Ctx.Input.Bind(&ob.Name, "name")
  o.Ctx.Input.Bind(&ob.Lastname, "lastname")
  o.Ctx.Input.Bind(&ob.Document, "document")
  o.Ctx.Input.Bind(&ob.Email, "email")
  o.Ctx.Input.Bind(&ob.Username, "username")
  o.Ctx.Input.Bind(&ob.Password, "password")
  o.Ctx.Input.Bind(&ob.Registration_date, "registration_date")
  o.Ctx.Input.Bind(&ob.Last_modification, "registration_date")
  o.Ctx.Input.Bind(&modules, "modules")
  o.Ctx.Input.Bind(&alerts, "alerts")
	objectid, err := models.AddUser(ob, modules, alerts)
	if err != nil {
			o.Data["json"] = err.Error()
	} else {
			o.Data["json"] = objectid
	}
  models.Logger.Debug("Completed [POST] users/ in %v\n", time.Since(start))
	o.ServeJSON()
}

// @Title Update
// @Description update the user
// @Param	Id_usario	path 	string	true		"the id_user you want to get"
// @Param	body		body 	models.User	true		"The body"
// @Success 200 {user} models.User
// @Failure 403 :Id_usuario is empty
// @router /:Id_usuario [put]
func (o *UserController) Put() {
  start := time.Now()
  Id_user := o.Ctx.Input.Param(":Id_usuario")
  var ob models.User
  var modules []string
  var alerts  []string
  json.Unmarshal(o.Ctx.Input.RequestBody, &ob)
  o.Ctx.Input.Bind(&ob.Name, "name")
  o.Ctx.Input.Bind(&ob.Lastname, "lastname")
  o.Ctx.Input.Bind(&ob.Document, "document")
  o.Ctx.Input.Bind(&ob.Email, "email")
  o.Ctx.Input.Bind(&ob.Username, "username")
  o.Ctx.Input.Bind(&ob.Password, "password")
  o.Ctx.Input.Bind(&ob.Last_modification, "registration_date")
  o.Ctx.Input.Bind(&modules, "modules")
  o.Ctx.Input.Bind(&alerts, "alerts")
  err := models.UpdateUser(Id_user, ob, modules, alerts)
  if err != nil {
	  o.Data["json"] = err.Error()
  } else {
	  o.Data["json"] = "Update success!"
  }
  models.Logger.Debug("Completed [PUT] users/%s in %v\n", Id_user, time.Since(start))
  o.ServeJSON()
}

// @Title Update
// @Description update the user
// @Param	Id_user		path 	string	true		"the id_user you want to get"
// @Param	body		body 	models.User	true		"The body"
// @Success 200 {user} models.User
// @Failure 403 :Id_usuario is empty
// @router /:Id_usuario [delete]
func (o *UserController) Delete() {
  start := time.Now()
  Id_user := o.Ctx.Input.Param(":Id_usuario")

  err := models.DeleteUser(Id_user)
  if err != nil {
    o.Data["json"] = err.Error()
  } else {
    o.Data["json"] = "Delete success!"
  }
  models.Logger.Debug("Completed [DELETE] users/%s in %v\n", Id_user, time.Since(start))
  o.ServeJSON()
}
