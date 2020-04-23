package controllers

import (
  "time";
  "encoding/json";
  "github.com/astaxie/beego";
  "restfulapi-beego/models";
)

type AlertController struct {
	beego.Controller
	//GoJwetoController
}

// @Title GetAll
// @Description get all alerts
// @Success 200 {alert} models.Alert
// @Failure 403 :Id_alert is empty
// @router / [get]
func (o *AlertController) GetAll() {
  start := time.Now()
	obs := models.GetAllAlerts()
	o.Data["json"] = obs
	models.Logger.Debug("Completed [GET] alerts/ in %v\n", time.Since(start))
	o.ServeJSON()
}

// @Title Get
// @Description find alert by id_alert
// @Param	Id_alert		path 	string	true		"the id_alert you want to get"
// @Success 200 {alert} models.Alert
// @Failure 403 :Id_alert is empty
// @router /:Id_usuario [get]
func (o *AlertController) Get() {
  start := time.Now()
	Id_usuario := o.Ctx.Input.Param(":Id_usuario")
	if Id_usuario != "" {
		ob, err := models.GetAlert(Id_usuario,"")
		if err != nil {
			o.Data["json"] = err.Error()
		} else {
			o.Data["json"] = ob
		}
	}
	models.Logger.Debug("Completed [GET] alerts/%s in %v\n", Id_usuario, time.Since(start))
	o.ServeJSON()
}

// @Title Get
// @Description find alert by id_alert
// @Param	Id_alert		path 	string	true		"the id_alert you want to get"
// @Success 200 {alert} models.alert
// @Failure 403 :Id_alert is empty
// @router /:Id_usuario/:Id_cansat [get]
func (o *AlertController) GetIdAlert() {
  start := time.Now()
	Id_usuario := o.Ctx.Input.Param(":Id_usuario")
	Id_cansat := o.Ctx.Input.Param(":Id_cansat")
	if Id_usuario != "" {
		ob, err := models.GetAlert(Id_usuario,Id_cansat)
		if err != nil {
			o.Data["json"] = err.Error()
		} else {
			o.Data["json"] = ob
		}
	}
	models.Logger.Debug("Completed [GET] alerts/%s/%s in %v\n", Id_usuario, Id_cansat, time.Since(start))
	o.ServeJSON()
}

// @Title Create
// @Description create alert
// @Param	body		body 	models.Alert	true		"The alert content"
// @Success 200 {alert} models.Alert
// @Failure 403 body is empty
// @router / [post]
func (o *AlertController) Post() {
  start := time.Now()
	var ob models.Alert
	var parameters  []map[string]string
	json.Unmarshal(o.Ctx.Input.RequestBody, &ob)
  o.Ctx.Input.Bind(&ob.Type, "type")
  o.Ctx.Input.Bind(&ob.Creation_date, "creation_date")
  o.Ctx.Input.Bind(&ob.Last_modification, "installation_date")
  o.Ctx.Input.Bind(&parameters, "parameters")
  
	objectid, err := models.AddAlert(ob,parameters)
	if err != nil {
			o.Data["json"] = err.Error()
	} else {
			o.Data["json"] = objectid
	}
	models.Logger.Debug("Completed [POST] alerts/ in %v\n", time.Since(start))
	o.ServeJSON()
}

// @Title Update
// @Description update the sensor
// @Param	Id_cansat		path 	string	true		"The id_cansat you want to update"
// @Param	body		body 	models.Alert	true		"The body"
// @Success 200 {alert} models.Alert
// @Failure 403 :Id_cansat is empty
// @router /:Id_cansat [put]
func (o *AlertController) Put() {
  start := time.Now()
	Id_alert := o.Ctx.Input.Param(":Id_cansat")
	var ob models.Alert
	var parameters  []map[string]string
	json.Unmarshal(o.Ctx.Input.RequestBody, &ob)
  o.Ctx.Input.Bind(&ob.Type, "type")
  o.Ctx.Input.Bind(&ob.Last_modification, "installation_date")
  o.Ctx.Input.Bind(&parameters, "parameters")
  
	err := models.UpdateAlert(Id_alert,ob,parameters)
	if err != nil {
		o.Data["json"] = err.Error()
	} else {
		o.Data["json"] = "Update success!"
	}
	models.Logger.Debug("Completed [PUT] alerts/%s in %v\n", Id_alert, time.Since(start))
	o.ServeJSON()
}

// @Title Update
// @Description update the sensor
// @Param	Id_cansat		path 	string	true		"The id_cansat you want to update"
// @Param	body		body 	models.Alert	true		"The body"
// @Success 200 {alert} models.Alert
// @Failure 403 :Id_cansat is empty
// @router /:Id_cansat [delete]
func (o *AlertController) Delete() {
  start := time.Now()
	Id_alert := o.Ctx.Input.Param(":Id_cansat")
  
  err := models.DeleteAlert(Id_alert)
  if err != nil {
	  o.Data["json"] = err.Error()
  } else {
	  o.Data["json"] = "Delete Success"
  }
	models.Logger.Debug("Completed [DELETE] alerts/%s in %v\n", Id_alert, time.Since(start))
  o.ServeJSON()
}
