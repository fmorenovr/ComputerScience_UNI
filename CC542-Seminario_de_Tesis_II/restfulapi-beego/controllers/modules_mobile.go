package controllers

import (
  "restfulapi-beego/models";
  "github.com/astaxie/beego";
)

type ModuleMobileController struct {
	beego.Controller
	//GoJwetoController
}

// @Title GetAll
// @Description get all modules
// @Success 200 {module} models.Module
// @Failure 403 :Id_module is empty
// @router / [get]
func (o *ModuleMobileController) GetAll() {
	obs := models.GetAllModulesMobile()
	o.Data["json"] = obs
	o.ServeJSON()
}

// @Title Get
// @Description find module by id_module
// @Param	Id_module		path 	string	true		"the id_module you want to get"
// @Success 200 {module} models.module
// @Failure 403 :Id_module is empty
// @router /:Id_usuario/:Id_cansat [get]
func (o *ModuleMobileController) GetIdModule() {
	Id_usuario := o.Ctx.Input.Param(":Id_usuario")
	Id_cansat := o.Ctx.Input.Param(":Id_cansat")
	if Id_usuario != "" {
		ob, err := models.GetModuleMobile(Id_usuario,Id_cansat)
		if err != nil {
			o.Data["json"] = err.Error()
		} else {
			o.Data["json"] = ob
		}
	}
	o.ServeJSON()
}

// @Title Get
// @Description find module by id_module
// @Param	Id_module		path 	string	true		"the id_module you want to get"
// @Success 200 {module} models.Module
// @Failure 403 :Id_module is empty
// @router /:Id_usuario [get]
func (o *ModuleMobileController) Get() {
	Id_usuario := o.Ctx.Input.Param(":Id_usuario")
	if Id_usuario != "" {
		ob, err := models.GetModuleMobile(Id_usuario,"")
		if err != nil {
			o.Data["json"] = err.Error()
		} else {
			o.Data["json"] = ob
		}
	}
	o.ServeJSON()
}
