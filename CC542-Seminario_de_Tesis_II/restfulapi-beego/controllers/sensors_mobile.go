package controllers

import (
  "restfulapi-beego/models";
  "github.com/astaxie/beego";
)

// Operations about sensor
type SensorMobileController struct {
	beego.Controller
	//GoJwetoController
}

// @Title GetAll
// @Description get all sensors
// @Success 200 {sensor} models.sensor
// @Failure 403 :Id_sensor is empty
// @router / [get]
func (o *SensorMobileController) GetAll() {
	obs := models.GetAllSensoresMobile()
	o.Data["json"] = obs
	o.ServeJSON()
}

// @Title Get
// @Description find sensor by sensorid
// @Param	Id_sensor		path 	string	true		"the id_sensor you want to get"
// @Success 200 {sensor} models.Sensor
// @Failure 403 :Id_sensor is empty
// @router /:Id_usuario [get]
func (o *SensorMobileController) Get() {
	Id_usuario := o.Ctx.Input.Param(":Id_usuario")
	if Id_usuario != "" {
		ob, err := models.GetSensorMobileId(Id_usuario,"")
		if err != nil {
			o.Data["json"] = err.Error()
		} else {
			o.Data["json"] = ob
		}
	}
	o.ServeJSON()
}

// @Title Get
// @Description find sensor by sensorid
// @Param	Id_sensor		path 	string	true		"the id_sensor you want to get"
// @Success 200 {sensor} models.Sensor
// @Failure 403 :Id_sensor is empty
// @router /:Id_usuario/:Tipo_sensor [get]
func (o *SensorMobileController) GetIdSensor() {
	Id_usuario := o.Ctx.Input.Param(":Id_usuario")
	Tipo_sensor := o.Ctx.Input.Param(":Tipo_sensor")
	if Id_usuario != "" {
		ob, err := models.GetSensorMobileId(Id_usuario,Tipo_sensor)
		if err != nil {
			o.Data["json"] = err.Error()
		} else {
			o.Data["json"] = ob
		}
	}
	o.ServeJSON()
}
