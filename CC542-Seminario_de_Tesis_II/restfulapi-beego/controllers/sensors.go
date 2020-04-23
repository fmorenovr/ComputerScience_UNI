package controllers

import (
  "time";
  "restfulapi-beego/models";
  "github.com/astaxie/beego";
)

// Operations about sensor
type SensorController struct {
	beego.Controller
	//GoJwetoController
}

// @Title GetAll
// @Description get all sensors
// @Success 200 {sensor} models.sensor
// @Failure 403 :Id_sensor is empty
// @router / [get]
func (o *SensorController) GetAll() {
  start := time.Now()
  obs := models.GetAllSensores()
  o.Data["json"] = obs
  models.Logger.Debug("Completed [GET] sensors/ in %v\n", time.Since(start))
  o.ServeJSON()
}

// @Title Get
// @Description find sensor by sensorid
// @Param	Id_sensor		path 	string	true		"the id_sensor you want to get"
// @Success 200 {sensor} models.Sensor
// @Failure 403 :Id_sensor is empty
// @router /:Id_usuario [get]
func (o *SensorController) Get() {
  start := time.Now()
  Id_usuario := o.Ctx.Input.Param(":Id_usuario")
  if Id_usuario != "" {
    ob, err := models.GetSensorId(Id_usuario,"")
    if err != nil {
      o.Data["json"] = err.Error()
    } else {
      o.Data["json"] = ob
    }
  }
  models.Logger.Debug("Completed [GET] sensors/%s in %v\n", Id_usuario, time.Since(start))
  o.ServeJSON()
}

// @Title Get
// @Description find sensor by sensorid
// @Param	Id_sensor		path 	string	true		"the id_sensor you want to get"
// @Success 200 {sensor} models.Sensor
// @Failure 403 :Id_sensor is empty
// @router /:Id_usuario/:Tipo_sensor [get]
func (o *SensorController) GetIdSensor() {
  start := time.Now()
	Id_usuario := o.Ctx.Input.Param(":Id_usuario")
	Tipo_sensor := o.Ctx.Input.Param(":Tipo_sensor")
	if Id_usuario != "" {
		ob, err := models.GetSensorId(Id_usuario,Tipo_sensor)
		if err != nil {
			o.Data["json"] = err.Error()
		} else {
			o.Data["json"] = ob
		}
	}
  models.Logger.Debug("Completed [GET] sensors/%s/%s in %v\n", Id_usuario, Tipo_sensor, time.Since(start))
	o.ServeJSON()
}
