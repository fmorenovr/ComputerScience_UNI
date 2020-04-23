package controllers

import (
  "time";
  "encoding/json";
  "restfulapi-beego/models";
  "github.com/astaxie/beego";
)

type ModuleController struct {
	beego.Controller
	//GoJwetoController
}

// @Title GetAll
// @Description get all modules
// @Success 200 {module} models.Module
// @Failure 403 :Id_module is empty
// @router / [get]
func (o *ModuleController) GetAll() {
  start := time.Now()
	obs := models.GetAllModules()
	o.Data["json"] = obs
	models.Logger.Debug("Completed [GET] modules/ in %v\n", time.Since(start))
	o.ServeJSON()
}

// @Title Get
// @Description find module by id_module
// @Param	Id_module		path 	string	true		"the id_module you want to get"
// @Success 200 {module} models.Module
// @Failure 403 :Id_module is empty
// @router /:Id_usuario [get]
func (o *ModuleController) Get() {
  start := time.Now()
	Id_usuario := o.Ctx.Input.Param(":Id_usuario")
	if Id_usuario != "" {
		ob, err := models.GetModule(Id_usuario,"")
		if err != nil {
			o.Data["json"] = err.Error()
		} else {
			o.Data["json"] = ob
		}
	}
	models.Logger.Debug("Completed [GET] modules/%s in %v\n", Id_usuario, time.Since(start))
	o.ServeJSON()
}

// @Title Get
// @Description find module by id_module
// @Param	Id_module		path 	string	true		"the id_module you want to get"
// @Success 200 {module} models.module
// @Failure 403 :Id_module is empty
// @router /:Id_usuario/:Id_cansat [get]
func (o *ModuleController) GetIdModule() {
  start := time.Now()
	Id_usuario := o.Ctx.Input.Param(":Id_usuario")
	Id_cansat := o.Ctx.Input.Param(":Id_cansat")
	if Id_usuario != "" {
		ob, err := models.GetModule(Id_usuario,Id_cansat)
		if err != nil {
			o.Data["json"] = err.Error()
		} else {
			o.Data["json"] = ob
		}
	}
	models.Logger.Debug("Completed [GET] modules/%s/%s in %v\n", Id_usuario, Id_cansat, time.Since(start))
	o.ServeJSON()
}

// @Title Create
// @Description create module
// @Param	body		body 	models.Module	true		"The module content"
// @Success 200 {module} models.Module
// @Failure 403 body is empty
// @router / [post]
func (o *ModuleController) Post() {
  start := time.Now()
	var ob models.Module
	var sens  []map[string]string//[]models.Sensor
	var polys []map[string]string//[]models.Polygon
	json.Unmarshal(o.Ctx.Input.RequestBody, &ob)
  o.Ctx.Input.Bind(&ob.Model, "model")
  o.Ctx.Input.Bind(&ob.Longuitude, "longuitude")
  o.Ctx.Input.Bind(&ob.Latitude, "latitude")
  o.Ctx.Input.Bind(&ob.Zone, "zone")
  o.Ctx.Input.Bind(&ob.Sector, "sector")
  o.Ctx.Input.Bind(&ob.Installation_date, "installation_date")
  o.Ctx.Input.Bind(&ob.Last_modification, "installation_date")
  o.Ctx.Input.Bind(&polys, "polygons")
  o.Ctx.Input.Bind(&sens, "sensors")
  
	objectid, err := models.AddIoTDevice(ob,polys,sens)
	if err != nil {
			o.Data["json"] = err.Error()
	} else {
			o.Data["json"] = objectid
	}
	models.Logger.Debug("Completed [POST] modules/ in %v\n", time.Since(start))
	o.ServeJSON()
}

// @Title Update
// @Description update the sensor
// @Param	Id_cansat		path 	string	true		"The id_cansat you want to update"
// @Param	body		body 	models.Module	true		"The body"
// @Success 200 {module} models.Module
// @Failure 403 :Id_cansat is empty
// @router /:Id_cansat [put]
func (o *ModuleController) Put() {
  start := time.Now()
	Id_module := o.Ctx.Input.Param(":Id_cansat")
	var ob models.Module
	var sens  []map[string]string//[]models.Sensor
	var polys []map[string]string //[]models.Polygon
	json.Unmarshal(o.Ctx.Input.RequestBody, &ob)
  o.Ctx.Input.Bind(&ob.Model, "model")
  o.Ctx.Input.Bind(&ob.Longuitude, "longuitude")
  o.Ctx.Input.Bind(&ob.Latitude, "latitude")
  o.Ctx.Input.Bind(&ob.Zone, "zone")
  o.Ctx.Input.Bind(&ob.Sector, "sector")
  o.Ctx.Input.Bind(&ob.Last_modification, "installation_date")
  o.Ctx.Input.Bind(&polys, "polygons")
  o.Ctx.Input.Bind(&sens, "sensors")
  
	err := models.UpdateIoTDevice(Id_module,ob,polys,sens)
	if err != nil {
		o.Data["json"] = err.Error()
	} else {
		o.Data["json"] = "Upload Success"
	}
	models.Logger.Debug("Completed [PUT] modules/%s in %v\n", Id_module, time.Since(start))
	o.ServeJSON()
}

// @Title Update
// @Description update the sensor
// @Param	Id_cansat		path 	string	true		"The id_cansat you want to update"
// @Param	body		body 	models.Module	true		"The body"
// @Success 200 {module} models.Module
// @Failure 403 :Id_cansat is empty
// @router /:Id_cansat [delete]
func (o *ModuleController) Delete() {
  start := time.Now()
  Id_module := o.Ctx.Input.Param(":Id_cansat")
  
  err := models.DeleteIoTDevice(Id_module)
  if err != nil {
    o.Data["json"] = err.Error()
  } else {
    o.Data["json"] = "Delete Success"
  }
  models.Logger.Debug("Completed [DELETE] modules/%s in %v\n", Id_module, time.Since(start))
  o.ServeJSON()
}
