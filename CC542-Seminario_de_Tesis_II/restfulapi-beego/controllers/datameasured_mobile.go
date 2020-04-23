package controllers

import (
  "restfulapi-beego/models";
  "github.com/astaxie/beego";
)

// Operations about sensor
type DataMeasuredMobileController struct {
	beego.Controller
	//GoJwetoController
}

// @Title GetAll
// @Description get all sensors
// @Success 200 {sensor} models.sensor
// @Failure 403 :Id_sensor is empty
// @router / [get]
func (o *DataMeasuredMobileController) GetAll() {
	obs := models.GetAllDataMeasuredMobile()
	o.Data["json"] = obs
	o.ServeJSON()
}

// @Title Get
// @Description find sensor by sensorid
// @Param	Tipo_sensor		path 	string	true		"the id_sensor you want to get"
// @Success 200 {sensor} models.Sensor
// @Failure 403 :Id_sensor is empty
// @router /:Id_usuario [get]
func (o *DataMeasuredMobileController) GetUserTypes() {
	Id_usuario := o.Ctx.Input.Param(":Id_usuario")
	if Id_usuario !=""{
		ob, err := models.GetDataMeasuredMobile(Id_usuario,"","","","","","","")
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
// @Param	Tipo_sensor		path 	string	true		"the id_sensor you want to get"
// @Success 200 {sensor} models.Sensor
// @Failure 403 :Id_sensor is empty
// @router /:Id_usuario/:Tipo_sensor [get]
func (o *DataMeasuredMobileController) GetTypes() {
	Id_usuario := o.Ctx.Input.Param(":Id_usuario")
	Tipo_sensor := o.Ctx.Input.Param(":Tipo_sensor")
	if Id_usuario !="" && Tipo_sensor != ""{
		ob, err := models.GetDataMeasuredMobile(Id_usuario,Tipo_sensor,"","","","","","")
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
// @Param	Tipo_sensor		path 	string	true		"the id_sensor you want to get"
// @Success 200 {sensor} models.Sensor
// @Failure 403 :Id_sensor is empty
// @router /:Id_usuario/:Tipo_sensor/:Id_usr [get]
func (o *DataMeasuredMobileController) Get() {
	Id_usuario := o.Ctx.Input.Param(":Id_usuario")
	Tipo_sensor := o.Ctx.Input.Param(":Tipo_sensor")
	Id_usr := o.Ctx.Input.Param(":Id_usr")
	if Id_usuario != ""{
		ob, err := models.GetDataMeasuredMobile(Id_usuario,Tipo_sensor,Id_usr, "","","","","")
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
// @Param	Tipo_sensor		path 	string	true		"the id_sensor you want to get"
// @Success 200 {sensor} models.Sensor
// @Failure 403 :Id_sensor is empty
// @router /:Id_usuario/:Tipo_sensor/:Id_usr/:Last [get]
func (o *DataMeasuredMobileController) GetLastItem() {
	Id_usuario := o.Ctx.Input.Param(":Id_usuario")
	Tipo_sensor := o.Ctx.Input.Param(":Tipo_sensor")
	Id_usr := o.Ctx.Input.Param(":Id_usr")
	Last := o.Ctx.Input.Param(":Last")
	if Id_usuario != ""{
		ob, err := models.GetDataMeasuredMobile(Id_usuario,Tipo_sensor,Id_usr,"","","","",Last)
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
// @Param	Tipo_sensor		path 	string	true		"the id_sensor you want to get"
// @Success 200 {sensor} models.Sensor
// @Failure 403 :Id_sensor is empty
// @router /:Id_usuario/:Tipo_sensor/:Id_usr/:DateInit/:DateFin [get]
func (o *DataMeasuredMobileController) GetDateFilterItemsNoLast() {
	Id_usuario := o.Ctx.Input.Param(":Id_usuario")
	Tipo_sensor := o.Ctx.Input.Param(":Tipo_sensor")
	Id_usr := o.Ctx.Input.Param(":Id_usr")
	Date_init := o.Ctx.Input.Param(":DateInit")
	Date_fin := o.Ctx.Input.Param(":DateFin")
	if Id_usuario != ""{
		ob, err := models.GetDataMeasuredMobile(Id_usuario,Tipo_sensor,Id_usr,Date_init,Date_fin,"","","")
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
// @Param	Tipo_sensor		path 	string	true		"the id_sensor you want to get"
// @Success 200 {sensor} models.Sensor
// @Failure 403 :Id_sensor is empty
// @router /:Id_usuario/:Tipo_sensor/:Id_usr/:DateInit/:DateFin/:Last [get]
func (o *DataMeasuredMobileController) GetDateFilterItems() {
	Id_usuario := o.Ctx.Input.Param(":Id_usuario")
	Tipo_sensor := o.Ctx.Input.Param(":Tipo_sensor")
	Id_usr := o.Ctx.Input.Param(":Id_usr")
	Date_init := o.Ctx.Input.Param(":DateInit")
	Date_fin := o.Ctx.Input.Param(":DateFin")
	Last := o.Ctx.Input.Param(":Last")
	if Id_usuario != ""{
		ob, err := models.GetDataMeasuredMobile(Id_usuario,Tipo_sensor,Id_usr,Date_init,Date_fin,"","",Last)
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
// @Param	Tipo_sensor		path 	string	true		"the id_sensor you want to get"
// @Success 200 {sensor} models.Sensor
// @Failure 403 :Id_sensor is empty
// @router /:Id_usuario/:Tipo_sensor/:Id_usr/:DateInit/:DateFin/:HourInit/:HourFin [get]
func (o *DataMeasuredMobileController) GetDateFilterHoursNoLast() {
	Id_usuario := o.Ctx.Input.Param(":Id_usuario")
	Tipo_sensor := o.Ctx.Input.Param(":Tipo_sensor")
	Id_usr := o.Ctx.Input.Param(":Id_usr")
	Date_init := o.Ctx.Input.Param(":DateInit")
	Date_fin := o.Ctx.Input.Param(":DateFin")
	Hour_init := o.Ctx.Input.Param(":HourInit")
	Hour_fin := o.Ctx.Input.Param(":HourFin")
	if Id_usuario != ""{
		ob, err := models.GetDataMeasuredMobile(Id_usuario,Tipo_sensor,Id_usr,Date_init,Date_fin,Hour_init,Hour_fin,"")
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
// @Param	Tipo_sensor		path 	string	true		"the id_sensor you want to get"
// @Success 200 {sensor} models.Sensor
// @Failure 403 :Id_sensor is empty
// @router /:Id_usuario/:Tipo_sensor/:Id_usr/:DateInit/:DateFin/:HourInit/:HourFin/:Last [get]
func (o *DataMeasuredMobileController) GetDateFilterHours() {
	Id_usuario := o.Ctx.Input.Param(":Id_usuario")
	Tipo_sensor := o.Ctx.Input.Param(":Tipo_sensor")
	Id_usr := o.Ctx.Input.Param(":Id_usr")
	Date_init := o.Ctx.Input.Param(":DateInit")
	Date_fin := o.Ctx.Input.Param(":DateFin")
	Hour_init := o.Ctx.Input.Param(":HourInit")
	Hour_fin := o.Ctx.Input.Param(":HourFin")
	Last := o.Ctx.Input.Param(":Last")
	if Id_usuario != ""{
		ob, err := models.GetDataMeasuredMobile(Id_usuario,Tipo_sensor,Id_usr,Date_init,Date_fin,Hour_init,Hour_fin,Last)
		if err != nil {
			o.Data["json"] = err.Error()
		} else {
			o.Data["json"] = ob
		}
	}
	o.ServeJSON()
}
