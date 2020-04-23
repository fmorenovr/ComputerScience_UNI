package controllers

import (
  "time";
  "restfulapi-beego/models";
  "github.com/astaxie/beego";
)

// Operations about sensor
type AlertMeasuredController struct {
	beego.Controller
	//GoJwetoController
}

// @Title GetAll
// @Description get all alertmeasured
// @Success 200 {alertmeasured} models.alertmeasured
// @Failure 403 :Id_sensor is empty
// @router / [get]
func (o *AlertMeasuredController) GetAll() {
  start := time.Now()
	obs := models.GetAllAlertMeasured()
	o.Data["json"] = obs
	models.Logger.Debug("Completed [GET] alertmeasured/ in %v\n", time.Since(start))
	o.ServeJSON()
}

// @Title Get
// @Description find sensor by sensorid
// @Param	Id_alert		path 	string	true		"the id_sensor you want to get"
// @Success 200 {sensor} models.Sensor
// @Failure 403 :Id_sensor is empty
// @router /:Id_usuario [get]
func (o *AlertMeasuredController) GetUserTypes() {
  start := time.Now()
	Id_usuario := o.Ctx.Input.Param(":Id_usuario")
	if Id_usuario !=""{
		ob, err := models.GetAlertMeasured(Id_usuario,"","","","","","")
		if err != nil {
			o.Data["json"] = err.Error()
		} else {
			o.Data["json"] = ob
		}
	}
	models.Logger.Debug("Completed [GET] alertmeasured/%s in %v\n", Id_usuario, time.Since(start))
	o.ServeJSON()
}

// @Title Get
// @Description find sensor by sensorid
// @Param	Id_alert		path 	string	true		"the id_sensor you want to get"
// @Success 200 {sensor} models.Sensor
// @Failure 403 :Id_sensor is empty
// @router /:Id_usuario/:Id_alert [get]
func (o *AlertMeasuredController) GetTypes() {
  start := time.Now()
	Id_usuario := o.Ctx.Input.Param(":Id_usuario")
	Tipo_alert := o.Ctx.Input.Param(":Id_alert")
	if Id_usuario !="" && Tipo_alert != ""{
		ob, err := models.GetAlertMeasured(Id_usuario,Tipo_alert,"","","","","")
		if err != nil {
			o.Data["json"] = err.Error()
		} else {
			o.Data["json"] = ob
		}
	}
	models.Logger.Debug("Completed [GET] alertmeasured/%s/%s in %v\n", Id_usuario, Tipo_alert, time.Since(start))
	o.ServeJSON()
}

// @Title Get
// @Description find sensor by sensorid
// @Param	Id_alert		path 	string	true		"the id_sensor you want to get"
// @Success 200 {sensor} models.Sensor
// @Failure 403 :Id_sensor is empty
// @router /:Id_usuario/:Id_alert/:Last [get]
func (o *AlertMeasuredController) Get() {
  start := time.Now()
	Id_usuario := o.Ctx.Input.Param(":Id_usuario")
	Tipo_alert := o.Ctx.Input.Param(":Id_alert")
	Last := o.Ctx.Input.Param(":Last")
	if Id_usuario != ""{
		ob, err := models.GetAlertMeasured(Id_usuario,Tipo_alert,"", "","","",Last)
		if err != nil {
			o.Data["json"] = err.Error()
		} else {
			o.Data["json"] = ob
		}
	}
	models.Logger.Debug("Completed [GET] alertmeasured/%s/%s/%s in %v\n", Id_usuario, Tipo_alert, Last, time.Since(start))
	o.ServeJSON()
}

// @Title Get
// @Description find sensor by sensorid
// @Param	Id_alert		path 	string	true		"the id_sensor you want to get"
// @Success 200 {sensor} models.Sensor
// @Failure 403 :Id_sensor is empty
// @router /:Id_usuario/:Id_alert/:DateInit/:DateFin [get]
func (o *AlertMeasuredController) GetDateFilterItemsNoLast() {
  start := time.Now()
	Id_usuario := o.Ctx.Input.Param(":Id_usuario")
	Tipo_alert := o.Ctx.Input.Param(":Id_alert")
	Date_init := o.Ctx.Input.Param(":DateInit")
	Date_fin := o.Ctx.Input.Param(":DateFin")
	if Id_usuario != ""{
		ob, err := models.GetAlertMeasured(Id_usuario,Tipo_alert,Date_init,Date_fin,"","","")
		if err != nil {
			o.Data["json"] = err.Error()
		} else {
			o.Data["json"] = ob
		}
	}
	models.Logger.Debug("Completed [GET] alertmeasured/%s/%s/%s/%s in %v\n", Id_usuario, Tipo_alert, Date_init, Date_fin, time.Since(start))
	o.ServeJSON()
}

// @Title Get
// @Description find sensor by sensorid
// @Param	Id_alert		path 	string	true		"the id_sensor you want to get"
// @Success 200 {sensor} models.Sensor
// @Failure 403 :Id_sensor is empty
// @router /:Id_usuario/:Id_alert/:DateInit/:DateFin/:Last [get]
func (o *AlertMeasuredController) GetDateFilterItems() {
  start := time.Now()
	Id_usuario := o.Ctx.Input.Param(":Id_usuario")
	Tipo_alert := o.Ctx.Input.Param(":Id_alert")
	Date_init := o.Ctx.Input.Param(":DateInit")
	Date_fin := o.Ctx.Input.Param(":DateFin")
	Last := o.Ctx.Input.Param(":Last")
	if Id_usuario != ""{
		ob, err := models.GetAlertMeasured(Id_usuario,Tipo_alert,Date_init,Date_fin,"","",Last)
		if err != nil {
			o.Data["json"] = err.Error()
		} else {
			o.Data["json"] = ob
		}
	}
	models.Logger.Debug("Completed [GET] alertmeasured/%s/%s/%s/%s/%s in %v\n", Id_usuario, Tipo_alert, Date_init, Date_fin, Last, time.Since(start))
	o.ServeJSON()
}

// @Title Get
// @Description find sensor by sensorid
// @Param	Id_alert		path 	string	true		"the id_sensor you want to get"
// @Success 200 {sensor} models.Sensor
// @Failure 403 :Id_sensor is empty
// @router /:Id_usuario/:Id_alert/:DateInit/:DateFin/:HourInit/:HourFin [get]
func (o *AlertMeasuredController) GetDateFilterHoursNoLast() {
  start := time.Now()
	Id_usuario := o.Ctx.Input.Param(":Id_usuario")
	Tipo_alert := o.Ctx.Input.Param(":Id_alert")
	Date_init := o.Ctx.Input.Param(":DateInit")
	Date_fin := o.Ctx.Input.Param(":DateFin")
	Hour_init := o.Ctx.Input.Param(":HourInit")
	Hour_fin := o.Ctx.Input.Param(":HourFin")
	if Id_usuario != ""{
		ob, err := models.GetAlertMeasured(Id_usuario,Tipo_alert,Date_init,Date_fin,Hour_init,Hour_fin,"")
		if err != nil {
			o.Data["json"] = err.Error()
		} else {
			o.Data["json"] = ob
		}
	}
	models.Logger.Debug("Completed [GET] alertmeasured/%s/%s/%s/%s/%s/%s in %v\n", Id_usuario, Tipo_alert, Date_init, Date_fin, Hour_init, Hour_fin, time.Since(start))
	o.ServeJSON()
}

// @Title Get
// @Description find sensor by sensorid
// @Param	Id_alert		path 	string	true		"the id_sensor you want to get"
// @Success 200 {sensor} models.Sensor
// @Failure 403 :Id_sensor is empty
// @router /:Id_usuario/:Id_alert/:DateInit/:DateFin/:HourInit/:HourFin/:Last [get]
func (o *AlertMeasuredController) GetDateFilterHours() {
  start := time.Now()
	Id_usuario := o.Ctx.Input.Param(":Id_usuario")
	Tipo_alert := o.Ctx.Input.Param(":Id_alert")
	Date_init := o.Ctx.Input.Param(":DateInit")
	Date_fin := o.Ctx.Input.Param(":DateFin")
	Hour_init := o.Ctx.Input.Param(":HourInit")
	Hour_fin := o.Ctx.Input.Param(":HourFin")
	Last := o.Ctx.Input.Param(":Last")
	if Id_usuario != ""{
		ob, err := models.GetAlertMeasured(Id_usuario,Tipo_alert,Date_init,Date_fin,Hour_init,Hour_fin,Last)
		if err != nil {
			o.Data["json"] = err.Error()
		} else {
			o.Data["json"] = ob
		}
	}
	models.Logger.Debug("Completed [GET] alertmeasured/%s/%s/%s/%s/%s/%s/%s in %v\n", Id_usuario, Tipo_alert, Date_init, Date_fin, Hour_init, Hour_fin, Last, time.Since(start))
	o.ServeJSON()
}
