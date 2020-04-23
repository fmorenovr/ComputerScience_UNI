package controllers

import (
  "time";
  "restfulapi-beego/models";
  "github.com/astaxie/beego";
)

// Operations about sensor
type DataMeasuredController struct {
	beego.Controller
	//GoJwetoController
}

// @Title GetAll
// @Description get all sensors
// @Success 200 {sensor} models.sensor
// @Failure 403 :Id_sensor is empty
// @router / [get]
func (o *DataMeasuredController) GetAll() {
  start := time.Now()
	obs := models.GetAllDataMeasured()
	o.Data["json"] = obs
	models.Logger.Debug("Completed [GET] datameasured/ in %v\n", time.Since(start))
	o.ServeJSON()
}

// @Title Get
// @Description find sensor by sensorid
// @Param	Tipo_sensor		path 	string	true		"the id_sensor you want to get"
// @Success 200 {sensor} models.Sensor
// @Failure 403 :Id_sensor is empty
// @router /:Id_usuario [get]
func (o *DataMeasuredController) GetUserTypes() {
  start := time.Now()
	Id_usuario := o.Ctx.Input.Param(":Id_usuario")
	if Id_usuario !=""{
		ob, err := models.GetDataMeasured(Id_usuario,"","","","","","","")
		if err != nil {
			o.Data["json"] = err.Error()
		} else {
			o.Data["json"] = ob
		}
	}
	models.Logger.Debug("Completed [GET] datameasured/%s in %v\n", Id_usuario, time.Since(start))
	o.ServeJSON()
}

// @Title Get
// @Description find sensor by sensorid
// @Param	Tipo_sensor		path 	string	true		"the id_sensor you want to get"
// @Success 200 {sensor} models.Sensor
// @Failure 403 :Id_sensor is empty
// @router /:Id_usuario/:Tipo_sensor [get]
func (o *DataMeasuredController) GetTypes() {
  start := time.Now()
	Id_usuario := o.Ctx.Input.Param(":Id_usuario")
	Tipo_sensor := o.Ctx.Input.Param(":Tipo_sensor")
	if Id_usuario !="" && Tipo_sensor != ""{
		ob, err := models.GetDataMeasured(Id_usuario,Tipo_sensor,"","","","","","")
		if err != nil {
			o.Data["json"] = err.Error()
		} else {
			o.Data["json"] = ob
		}
	}
	models.Logger.Debug("Completed [GET] datameasured/%s/%s in %v\n", Id_usuario, Tipo_sensor, time.Since(start))
	o.ServeJSON()
}

// @Title Get
// @Description find sensor by sensorid
// @Param	Tipo_sensor		path 	string	true		"the id_sensor you want to get"
// @Success 200 {sensor} models.Sensor
// @Failure 403 :Id_sensor is empty
// @router /:Id_usuario/:Tipo_sensor/:Id_usr [get]
func (o *DataMeasuredController) Get() {
  start := time.Now()
	Id_usuario := o.Ctx.Input.Param(":Id_usuario")
	Tipo_sensor := o.Ctx.Input.Param(":Tipo_sensor")
	Id_usr := o.Ctx.Input.Param(":Id_usr")
	if Id_usuario != ""{
		ob, err := models.GetDataMeasured(Id_usuario,Tipo_sensor,Id_usr, "","","","","")
		if err != nil {
			o.Data["json"] = err.Error()
		} else {
			o.Data["json"] = ob
		}
	}
	models.Logger.Debug("Completed [GET] datameasured/%s/%s/%s in %v\n", Id_usuario, Tipo_sensor, Id_usr, time.Since(start))
	o.ServeJSON()
}

// @Title Get
// @Description find sensor by sensorid
// @Param	Tipo_sensor		path 	string	true		"the id_sensor you want to get"
// @Success 200 {sensor} models.Sensor
// @Failure 403 :Id_sensor is empty
// @router /:Id_usuario/:Tipo_sensor/:Id_usr/:Last [get]
func (o *DataMeasuredController) GetLastItem() {
  start := time.Now()
	Id_usuario := o.Ctx.Input.Param(":Id_usuario")
	Tipo_sensor := o.Ctx.Input.Param(":Tipo_sensor")
	Id_usr := o.Ctx.Input.Param(":Id_usr")
	Last := o.Ctx.Input.Param(":Last")
	if Id_usuario != ""{
		ob, err := models.GetDataMeasured(Id_usuario,Tipo_sensor,Id_usr,"","","","",Last)
		if err != nil {
			o.Data["json"] = err.Error()
		} else {
			o.Data["json"] = ob
		}
	}
	models.Logger.Debug("Completed [GET] datameasured/%s/%s/%s/%s in %v\n", Id_usuario, Tipo_sensor, Id_usr, Last, time.Since(start))
	o.ServeJSON()
}

// @Title Get
// @Description find sensor by sensorid
// @Param	Tipo_sensor		path 	string	true		"the id_sensor you want to get"
// @Success 200 {sensor} models.Sensor
// @Failure 403 :Id_sensor is empty
// @router /:Id_usuario/:Tipo_sensor/:Id_usr/:DateInit/:DateFin [get]
func (o *DataMeasuredController) GetDateFilterItemsNoLast() {
  start := time.Now()
	Id_usuario := o.Ctx.Input.Param(":Id_usuario")
	Tipo_sensor := o.Ctx.Input.Param(":Tipo_sensor")
	Id_usr := o.Ctx.Input.Param(":Id_usr")
	Date_init := o.Ctx.Input.Param(":DateInit")
	Date_fin := o.Ctx.Input.Param(":DateFin")
	if Id_usuario != ""{
		ob, err := models.GetDataMeasured(Id_usuario,Tipo_sensor,Id_usr,Date_init,Date_fin,"","","")
		if err != nil {
			o.Data["json"] = err.Error()
		} else {
			o.Data["json"] = ob
		}
	}
	models.Logger.Debug("Completed [GET] datameasured/%s/%s/%s/%s/%s in %v\n", Id_usuario, Tipo_sensor, Id_usr, Date_init, Date_fin, time.Since(start))
	o.ServeJSON()
}

// @Title Get
// @Description find sensor by sensorid
// @Param	Tipo_sensor		path 	string	true		"the id_sensor you want to get"
// @Success 200 {sensor} models.Sensor
// @Failure 403 :Id_sensor is empty
// @router /:Id_usuario/:Tipo_sensor/:Id_usr/:DateInit/:DateFin/:Last [get]
func (o *DataMeasuredController) GetDateFilterItems() {
  start := time.Now()
	Id_usuario := o.Ctx.Input.Param(":Id_usuario")
	Tipo_sensor := o.Ctx.Input.Param(":Tipo_sensor")
	Id_usr := o.Ctx.Input.Param(":Id_usr")
	Date_init := o.Ctx.Input.Param(":DateInit")
	Date_fin := o.Ctx.Input.Param(":DateFin")
	Last := o.Ctx.Input.Param(":Last")
	if Id_usuario != ""{
		ob, err := models.GetDataMeasured(Id_usuario,Tipo_sensor,Id_usr,Date_init,Date_fin,"","",Last)
		if err != nil {
			o.Data["json"] = err.Error()
		} else {
			o.Data["json"] = ob
		}
	}
	models.Logger.Debug("Completed [GET] datameasured/%s/%s/%s/%s/%s/%s in %v\n", Id_usuario, Tipo_sensor, Id_usr, Date_init, Date_fin, Last, time.Since(start))
	o.ServeJSON()
}

// @Title Get
// @Description find sensor by sensorid
// @Param	Tipo_sensor		path 	string	true		"the id_sensor you want to get"
// @Success 200 {sensor} models.Sensor
// @Failure 403 :Id_sensor is empty
// @router /:Id_usuario/:Tipo_sensor/:Id_usr/:DateInit/:DateFin/:HourInit/:HourFin [get]
func (o *DataMeasuredController) GetDateFilterHoursNoLast() {
  start := time.Now()
	Id_usuario := o.Ctx.Input.Param(":Id_usuario")
	Tipo_sensor := o.Ctx.Input.Param(":Tipo_sensor")
	Id_usr := o.Ctx.Input.Param(":Id_usr")
	Date_init := o.Ctx.Input.Param(":DateInit")
	Date_fin := o.Ctx.Input.Param(":DateFin")
	Hour_init := o.Ctx.Input.Param(":HourInit")
	Hour_fin := o.Ctx.Input.Param(":HourFin")
	if Id_usuario != ""{
		ob, err := models.GetDataMeasured(Id_usuario,Tipo_sensor,Id_usr,Date_init,Date_fin,Hour_init,Hour_fin,"")
		if err != nil {
			o.Data["json"] = err.Error()
		} else {
			o.Data["json"] = ob
		}
	}
	models.Logger.Debug("Completed [GET] datameasured/%s/%s/%s/%s/%s/%s/%s in %v\n", Id_usuario, Tipo_sensor, Id_usr, Date_init, Date_fin, Hour_init, Hour_fin, time.Since(start))
	o.ServeJSON()
}

// @Title Get
// @Description find sensor by sensorid
// @Param	Tipo_sensor		path 	string	true		"the id_sensor you want to get"
// @Success 200 {sensor} models.Sensor
// @Failure 403 :Id_sensor is empty
// @router /:Id_usuario/:Tipo_sensor/:Id_usr/:DateInit/:DateFin/:HourInit/:HourFin/:Last [get]
func (o *DataMeasuredController) GetDateFilterHours() {
  start := time.Now()
  Id_usuario := o.Ctx.Input.Param(":Id_usuario")
  Tipo_sensor := o.Ctx.Input.Param(":Tipo_sensor")
  Id_usr := o.Ctx.Input.Param(":Id_usr")
  Date_init := o.Ctx.Input.Param(":DateInit")
  Date_fin := o.Ctx.Input.Param(":DateFin")
  Hour_init := o.Ctx.Input.Param(":HourInit")
  Hour_fin := o.Ctx.Input.Param(":HourFin")
  Last := o.Ctx.Input.Param(":Last")
  if Id_usuario != ""{
    ob, err := models.GetDataMeasured(Id_usuario,Tipo_sensor,Id_usr,Date_init,Date_fin,Hour_init,Hour_fin,Last)
		if err != nil {
			o.Data["json"] = err.Error()
		} else {
      o.Data["json"] = ob
    }
  }
  models.Logger.Debug("Completed [GET] datameasured/%s/%s/%s/%s/%s/%s/%s/%s in %v\n", Id_usuario, Tipo_sensor, Id_usr, Date_init, Date_fin, Hour_init, Hour_fin, Last, time.Since(start))
  o.ServeJSON()
}
