package controllers

import (
  "time";
  "restfulapi-beego/models";
  "github.com/astaxie/beego";
)

// Operations about usuario
type FogNodeController struct {
	beego.Controller
	//GoJwetoController
}

// @Title GetAll
// @Description get all zones
// @Success 200 {zone} models.Zone
// @Failure 403 :Id_usuario is empty
// @router / [get]
func (o *FogNodeController) GetAll() {
  start := time.Now()
  obs := models.GetAllFogNodes()
  o.Data["json"] = obs
  models.Logger.Debug("Completed [GET] fognodes/ in %v\n", time.Since(start))
  o.ServeJSON()
}

// @Title Get
// @Description find usuario by usuarioid
// @Param	Id_usuario	path 	string	true		"the id_usuario you want to get"
// @Success 200 {zone} models.FogNode
// @Failure 403 :Id_usuario is empty
// @router /:Id_usuario [get]
func (o *FogNodeController) Get() {
  start := time.Now()
	Id_fognode := o.Ctx.Input.Param(":Id_usuario")
	if Id_fognode != "" {
		ob, err := models.GetFogNode(Id_fognode)
		if err != nil {
			o.Data["json"] = err.Error()
		} else {
			o.Data["json"] = ob
		}
	}
	models.Logger.Debug("Completed [GET] fognodes/%s in %v\n", Id_fognode, time.Since(start))
	o.ServeJSON()
}

// @Title Get
// @Description find usuario by usuarioid
// @Param	Id_usuario	path 	string	true		"the id_usuario you want to get"
// @Success 200 {zone} models.FogNode
// @Failure 403 :Id_usuario is empty
// @router /users/ [get]
func (o *FogNodeController) GetAllFog() {
  start := time.Now()
	ob, err := models.GetFogNodeByUser("")
	if err != nil {
		o.Data["json"] = err.Error()
	} else {
		o.Data["json"] = ob
	}
	models.Logger.Debug("Completed [GET] fognodes/users/ in %v\n", time.Since(start))
	o.ServeJSON()
}

// @Title Get
// @Description find usuario by usuarioid
// @Param	Id_usuario	path 	string	true		"the id_usuario you want to get"
// @Success 200 {zone} models.FogNode
// @Failure 403 :Id_usuario is empty
// @router /users/:Id_usuario [get]
func (o *FogNodeController) GetFog() {
  start := time.Now()
	Id_foguser := o.Ctx.Input.Param(":Id_usuario")
	if Id_foguser != "" {
		ob, err := models.GetFogNodeByUser(Id_foguser)
		if err != nil {
			o.Data["json"] = err.Error()
		} else {
			o.Data["json"] = ob
		}
	}
	models.Logger.Debug("Completed [GET] fognodes/users/%s in %v\n", Id_foguser, time.Since(start))
	o.ServeJSON()
}
