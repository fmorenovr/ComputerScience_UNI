package controllers

import (
  "time";
  "restfulapi-beego/models";
  "github.com/astaxie/beego";
)

// Operations about sensor
type SensorsTypeController struct {
	beego.Controller
	//GoJwetoController
}

// @Title GetAll
// @Description get all sensors
// @Success 200 {sensor} models.sensor
// @Failure 403 :Id_sensor is empty
// @router / [get]
func (o *SensorsTypeController) GetAll() {
  start := time.Now()
  obs := models.GetAllTypeSensor()
  o.Data["json"] = obs
  models.Logger.Debug("Completed [GET] sensorstype/ in %v\n", time.Since(start))
  o.ServeJSON()
}

// @Title Get
// @Description find sensor by sensorid
// @Param	Tipo_sensor		path 	string	true		"the tipo_sensor you want to get"
// @Success 200 {sensor} models.Sensor
// @Failure 403 :Tipo_sensor is empty
// @router /:Id_usuario [get]
func (o *SensorsTypeController) Get() {
  start := time.Now()
  Id_usuario := o.Ctx.Input.Param(":Id_usuario")
  if Id_usuario != "" {
    ob, err := models.GetTipoSensores(Id_usuario)
    if err != nil {
      o.Data["json"] = err.Error()
    } else {
      o.Data["json"] = ob
    }
  }
  models.Logger.Debug("Completed [GET] sensorstype/%s in %v\n", Id_usuario, time.Since(start))
  o.ServeJSON()
}
