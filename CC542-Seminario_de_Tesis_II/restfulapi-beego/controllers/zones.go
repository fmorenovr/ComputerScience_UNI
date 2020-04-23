package controllers

import (
  "time";
  "restfulapi-beego/models";
  "github.com/astaxie/beego";
)

// Operations about usuario
type ZoneController struct {
	beego.Controller
	//GoJwetoController
}

// @Title GetAll
// @Description get all zones
// @Success 200 {zone} models.Zone
// @Failure 403 :Id_usuario is empty
// @router / [get]
func (o *ZoneController) GetAll() {
  start := time.Now()
  obs := models.GetAllZones()
  o.Data["json"] = obs
  models.Logger.Debug("Completed [GET] zones/ in %v\n", time.Since(start))
  o.ServeJSON()
}

// @Title Get
// @Description find usuario by usuarioid
// @Param	Id_usuario	path 	string	true		"the id_usuario you want to get"
// @Success 200 {zone} models.Zone
// @Failure 403 :Id_usuario is empty
// @router /:Id_usuario [get]
func (o *ZoneController) Get() {
  start := time.Now()
  Id_usuario := o.Ctx.Input.Param(":Id_usuario")
  if Id_usuario != "" {
    ob, err := models.GetZone(Id_usuario)
    if err != nil {
      o.Data["json"] = err.Error()
    } else {
      o.Data["json"] = ob
    }
  }
  models.Logger.Debug("Completed [GET] zones/%s in %v\n", Id_usuario, time.Since(start))
  o.ServeJSON()
}
