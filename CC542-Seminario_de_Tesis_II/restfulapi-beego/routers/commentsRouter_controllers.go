package routers

import (
	"github.com/astaxie/beego"
	"github.com/astaxie/beego/context/param"
)

func init() {

	beego.GlobalControllerRouter["restfulapi-beego/controllers:AlertController"] = append(beego.GlobalControllerRouter["restfulapi-beego/controllers:AlertController"],
		beego.ControllerComments{
			Method: "GetAll",
			Router: `/`,
			AllowHTTPMethods: []string{"get"},
			MethodParams: param.Make(),
			Params: nil})

	beego.GlobalControllerRouter["restfulapi-beego/controllers:AlertController"] = append(beego.GlobalControllerRouter["restfulapi-beego/controllers:AlertController"],
		beego.ControllerComments{
			Method: "Post",
			Router: `/`,
			AllowHTTPMethods: []string{"post"},
			MethodParams: param.Make(),
			Params: nil})

	beego.GlobalControllerRouter["restfulapi-beego/controllers:AlertController"] = append(beego.GlobalControllerRouter["restfulapi-beego/controllers:AlertController"],
		beego.ControllerComments{
			Method: "Put",
			Router: `/:Id_cansat`,
			AllowHTTPMethods: []string{"put"},
			MethodParams: param.Make(),
			Params: nil})

	beego.GlobalControllerRouter["restfulapi-beego/controllers:AlertController"] = append(beego.GlobalControllerRouter["restfulapi-beego/controllers:AlertController"],
		beego.ControllerComments{
			Method: "Delete",
			Router: `/:Id_cansat`,
			AllowHTTPMethods: []string{"delete"},
			MethodParams: param.Make(),
			Params: nil})

	beego.GlobalControllerRouter["restfulapi-beego/controllers:AlertController"] = append(beego.GlobalControllerRouter["restfulapi-beego/controllers:AlertController"],
		beego.ControllerComments{
			Method: "Get",
			Router: `/:Id_usuario`,
			AllowHTTPMethods: []string{"get"},
			MethodParams: param.Make(),
			Params: nil})

	beego.GlobalControllerRouter["restfulapi-beego/controllers:AlertController"] = append(beego.GlobalControllerRouter["restfulapi-beego/controllers:AlertController"],
		beego.ControllerComments{
			Method: "GetIdAlert",
			Router: `/:Id_usuario/:Id_cansat`,
			AllowHTTPMethods: []string{"get"},
			MethodParams: param.Make(),
			Params: nil})

	beego.GlobalControllerRouter["restfulapi-beego/controllers:AlertMeasuredController"] = append(beego.GlobalControllerRouter["restfulapi-beego/controllers:AlertMeasuredController"],
		beego.ControllerComments{
			Method: "GetAll",
			Router: `/`,
			AllowHTTPMethods: []string{"get"},
			MethodParams: param.Make(),
			Params: nil})

	beego.GlobalControllerRouter["restfulapi-beego/controllers:AlertMeasuredController"] = append(beego.GlobalControllerRouter["restfulapi-beego/controllers:AlertMeasuredController"],
		beego.ControllerComments{
			Method: "GetUserTypes",
			Router: `/:Id_usuario`,
			AllowHTTPMethods: []string{"get"},
			MethodParams: param.Make(),
			Params: nil})

	beego.GlobalControllerRouter["restfulapi-beego/controllers:AlertMeasuredController"] = append(beego.GlobalControllerRouter["restfulapi-beego/controllers:AlertMeasuredController"],
		beego.ControllerComments{
			Method: "GetTypes",
			Router: `/:Id_usuario/:Id_alert`,
			AllowHTTPMethods: []string{"get"},
			MethodParams: param.Make(),
			Params: nil})

	beego.GlobalControllerRouter["restfulapi-beego/controllers:AlertMeasuredController"] = append(beego.GlobalControllerRouter["restfulapi-beego/controllers:AlertMeasuredController"],
		beego.ControllerComments{
			Method: "GetDateFilterItemsNoLast",
			Router: `/:Id_usuario/:Id_alert/:DateInit/:DateFin`,
			AllowHTTPMethods: []string{"get"},
			MethodParams: param.Make(),
			Params: nil})

	beego.GlobalControllerRouter["restfulapi-beego/controllers:AlertMeasuredController"] = append(beego.GlobalControllerRouter["restfulapi-beego/controllers:AlertMeasuredController"],
		beego.ControllerComments{
			Method: "GetDateFilterHoursNoLast",
			Router: `/:Id_usuario/:Id_alert/:DateInit/:DateFin/:HourInit/:HourFin`,
			AllowHTTPMethods: []string{"get"},
			MethodParams: param.Make(),
			Params: nil})

	beego.GlobalControllerRouter["restfulapi-beego/controllers:AlertMeasuredController"] = append(beego.GlobalControllerRouter["restfulapi-beego/controllers:AlertMeasuredController"],
		beego.ControllerComments{
			Method: "GetDateFilterHours",
			Router: `/:Id_usuario/:Id_alert/:DateInit/:DateFin/:HourInit/:HourFin/:Last`,
			AllowHTTPMethods: []string{"get"},
			MethodParams: param.Make(),
			Params: nil})

	beego.GlobalControllerRouter["restfulapi-beego/controllers:AlertMeasuredController"] = append(beego.GlobalControllerRouter["restfulapi-beego/controllers:AlertMeasuredController"],
		beego.ControllerComments{
			Method: "GetDateFilterItems",
			Router: `/:Id_usuario/:Id_alert/:DateInit/:DateFin/:Last`,
			AllowHTTPMethods: []string{"get"},
			MethodParams: param.Make(),
			Params: nil})

	beego.GlobalControllerRouter["restfulapi-beego/controllers:AlertMeasuredController"] = append(beego.GlobalControllerRouter["restfulapi-beego/controllers:AlertMeasuredController"],
		beego.ControllerComments{
			Method: "Get",
			Router: `/:Id_usuario/:Id_alert/:Last`,
			AllowHTTPMethods: []string{"get"},
			MethodParams: param.Make(),
			Params: nil})

	beego.GlobalControllerRouter["restfulapi-beego/controllers:DataMeasuredController"] = append(beego.GlobalControllerRouter["restfulapi-beego/controllers:DataMeasuredController"],
		beego.ControllerComments{
			Method: "GetAll",
			Router: `/`,
			AllowHTTPMethods: []string{"get"},
			MethodParams: param.Make(),
			Params: nil})

	beego.GlobalControllerRouter["restfulapi-beego/controllers:DataMeasuredController"] = append(beego.GlobalControllerRouter["restfulapi-beego/controllers:DataMeasuredController"],
		beego.ControllerComments{
			Method: "GetUserTypes",
			Router: `/:Id_usuario`,
			AllowHTTPMethods: []string{"get"},
			MethodParams: param.Make(),
			Params: nil})

	beego.GlobalControllerRouter["restfulapi-beego/controllers:DataMeasuredController"] = append(beego.GlobalControllerRouter["restfulapi-beego/controllers:DataMeasuredController"],
		beego.ControllerComments{
			Method: "GetTypes",
			Router: `/:Id_usuario/:Tipo_sensor`,
			AllowHTTPMethods: []string{"get"},
			MethodParams: param.Make(),
			Params: nil})

	beego.GlobalControllerRouter["restfulapi-beego/controllers:DataMeasuredController"] = append(beego.GlobalControllerRouter["restfulapi-beego/controllers:DataMeasuredController"],
		beego.ControllerComments{
			Method: "Get",
			Router: `/:Id_usuario/:Tipo_sensor/:Id_usr`,
			AllowHTTPMethods: []string{"get"},
			MethodParams: param.Make(),
			Params: nil})

	beego.GlobalControllerRouter["restfulapi-beego/controllers:DataMeasuredController"] = append(beego.GlobalControllerRouter["restfulapi-beego/controllers:DataMeasuredController"],
		beego.ControllerComments{
			Method: "GetDateFilterItemsNoLast",
			Router: `/:Id_usuario/:Tipo_sensor/:Id_usr/:DateInit/:DateFin`,
			AllowHTTPMethods: []string{"get"},
			MethodParams: param.Make(),
			Params: nil})

	beego.GlobalControllerRouter["restfulapi-beego/controllers:DataMeasuredController"] = append(beego.GlobalControllerRouter["restfulapi-beego/controllers:DataMeasuredController"],
		beego.ControllerComments{
			Method: "GetDateFilterHoursNoLast",
			Router: `/:Id_usuario/:Tipo_sensor/:Id_usr/:DateInit/:DateFin/:HourInit/:HourFin`,
			AllowHTTPMethods: []string{"get"},
			MethodParams: param.Make(),
			Params: nil})

	beego.GlobalControllerRouter["restfulapi-beego/controllers:DataMeasuredController"] = append(beego.GlobalControllerRouter["restfulapi-beego/controllers:DataMeasuredController"],
		beego.ControllerComments{
			Method: "GetDateFilterHours",
			Router: `/:Id_usuario/:Tipo_sensor/:Id_usr/:DateInit/:DateFin/:HourInit/:HourFin/:Last`,
			AllowHTTPMethods: []string{"get"},
			MethodParams: param.Make(),
			Params: nil})

	beego.GlobalControllerRouter["restfulapi-beego/controllers:DataMeasuredController"] = append(beego.GlobalControllerRouter["restfulapi-beego/controllers:DataMeasuredController"],
		beego.ControllerComments{
			Method: "GetDateFilterItems",
			Router: `/:Id_usuario/:Tipo_sensor/:Id_usr/:DateInit/:DateFin/:Last`,
			AllowHTTPMethods: []string{"get"},
			MethodParams: param.Make(),
			Params: nil})

	beego.GlobalControllerRouter["restfulapi-beego/controllers:DataMeasuredController"] = append(beego.GlobalControllerRouter["restfulapi-beego/controllers:DataMeasuredController"],
		beego.ControllerComments{
			Method: "GetLastItem",
			Router: `/:Id_usuario/:Tipo_sensor/:Id_usr/:Last`,
			AllowHTTPMethods: []string{"get"},
			MethodParams: param.Make(),
			Params: nil})

	beego.GlobalControllerRouter["restfulapi-beego/controllers:DataMeasuredMobileController"] = append(beego.GlobalControllerRouter["restfulapi-beego/controllers:DataMeasuredMobileController"],
		beego.ControllerComments{
			Method: "GetAll",
			Router: `/`,
			AllowHTTPMethods: []string{"get"},
			MethodParams: param.Make(),
			Params: nil})

	beego.GlobalControllerRouter["restfulapi-beego/controllers:DataMeasuredMobileController"] = append(beego.GlobalControllerRouter["restfulapi-beego/controllers:DataMeasuredMobileController"],
		beego.ControllerComments{
			Method: "GetUserTypes",
			Router: `/:Id_usuario`,
			AllowHTTPMethods: []string{"get"},
			MethodParams: param.Make(),
			Params: nil})

	beego.GlobalControllerRouter["restfulapi-beego/controllers:DataMeasuredMobileController"] = append(beego.GlobalControllerRouter["restfulapi-beego/controllers:DataMeasuredMobileController"],
		beego.ControllerComments{
			Method: "GetTypes",
			Router: `/:Id_usuario/:Tipo_sensor`,
			AllowHTTPMethods: []string{"get"},
			MethodParams: param.Make(),
			Params: nil})

	beego.GlobalControllerRouter["restfulapi-beego/controllers:DataMeasuredMobileController"] = append(beego.GlobalControllerRouter["restfulapi-beego/controllers:DataMeasuredMobileController"],
		beego.ControllerComments{
			Method: "Get",
			Router: `/:Id_usuario/:Tipo_sensor/:Id_usr`,
			AllowHTTPMethods: []string{"get"},
			MethodParams: param.Make(),
			Params: nil})

	beego.GlobalControllerRouter["restfulapi-beego/controllers:DataMeasuredMobileController"] = append(beego.GlobalControllerRouter["restfulapi-beego/controllers:DataMeasuredMobileController"],
		beego.ControllerComments{
			Method: "GetDateFilterItemsNoLast",
			Router: `/:Id_usuario/:Tipo_sensor/:Id_usr/:DateInit/:DateFin`,
			AllowHTTPMethods: []string{"get"},
			MethodParams: param.Make(),
			Params: nil})

	beego.GlobalControllerRouter["restfulapi-beego/controllers:DataMeasuredMobileController"] = append(beego.GlobalControllerRouter["restfulapi-beego/controllers:DataMeasuredMobileController"],
		beego.ControllerComments{
			Method: "GetDateFilterHoursNoLast",
			Router: `/:Id_usuario/:Tipo_sensor/:Id_usr/:DateInit/:DateFin/:HourInit/:HourFin`,
			AllowHTTPMethods: []string{"get"},
			MethodParams: param.Make(),
			Params: nil})

	beego.GlobalControllerRouter["restfulapi-beego/controllers:DataMeasuredMobileController"] = append(beego.GlobalControllerRouter["restfulapi-beego/controllers:DataMeasuredMobileController"],
		beego.ControllerComments{
			Method: "GetDateFilterHours",
			Router: `/:Id_usuario/:Tipo_sensor/:Id_usr/:DateInit/:DateFin/:HourInit/:HourFin/:Last`,
			AllowHTTPMethods: []string{"get"},
			MethodParams: param.Make(),
			Params: nil})

	beego.GlobalControllerRouter["restfulapi-beego/controllers:DataMeasuredMobileController"] = append(beego.GlobalControllerRouter["restfulapi-beego/controllers:DataMeasuredMobileController"],
		beego.ControllerComments{
			Method: "GetDateFilterItems",
			Router: `/:Id_usuario/:Tipo_sensor/:Id_usr/:DateInit/:DateFin/:Last`,
			AllowHTTPMethods: []string{"get"},
			MethodParams: param.Make(),
			Params: nil})

	beego.GlobalControllerRouter["restfulapi-beego/controllers:DataMeasuredMobileController"] = append(beego.GlobalControllerRouter["restfulapi-beego/controllers:DataMeasuredMobileController"],
		beego.ControllerComments{
			Method: "GetLastItem",
			Router: `/:Id_usuario/:Tipo_sensor/:Id_usr/:Last`,
			AllowHTTPMethods: []string{"get"},
			MethodParams: param.Make(),
			Params: nil})

	beego.GlobalControllerRouter["restfulapi-beego/controllers:FogNodeController"] = append(beego.GlobalControllerRouter["restfulapi-beego/controllers:FogNodeController"],
		beego.ControllerComments{
			Method: "GetAll",
			Router: `/`,
			AllowHTTPMethods: []string{"get"},
			MethodParams: param.Make(),
			Params: nil})

	beego.GlobalControllerRouter["restfulapi-beego/controllers:FogNodeController"] = append(beego.GlobalControllerRouter["restfulapi-beego/controllers:FogNodeController"],
		beego.ControllerComments{
			Method: "Get",
			Router: `/:Id_usuario`,
			AllowHTTPMethods: []string{"get"},
			MethodParams: param.Make(),
			Params: nil})

	beego.GlobalControllerRouter["restfulapi-beego/controllers:FogNodeController"] = append(beego.GlobalControllerRouter["restfulapi-beego/controllers:FogNodeController"],
		beego.ControllerComments{
			Method: "GetAllFog",
			Router: `/users/`,
			AllowHTTPMethods: []string{"get"},
			MethodParams: param.Make(),
			Params: nil})

	beego.GlobalControllerRouter["restfulapi-beego/controllers:FogNodeController"] = append(beego.GlobalControllerRouter["restfulapi-beego/controllers:FogNodeController"],
		beego.ControllerComments{
			Method: "GetFog",
			Router: `/users/:Id_usuario`,
			AllowHTTPMethods: []string{"get"},
			MethodParams: param.Make(),
			Params: nil})

	beego.GlobalControllerRouter["restfulapi-beego/controllers:LoginController"] = append(beego.GlobalControllerRouter["restfulapi-beego/controllers:LoginController"],
		beego.ControllerComments{
			Method: "Post",
			Router: `/`,
			AllowHTTPMethods: []string{"post"},
			MethodParams: param.Make(),
			Params: nil})

	beego.GlobalControllerRouter["restfulapi-beego/controllers:ModuleController"] = append(beego.GlobalControllerRouter["restfulapi-beego/controllers:ModuleController"],
		beego.ControllerComments{
			Method: "GetAll",
			Router: `/`,
			AllowHTTPMethods: []string{"get"},
			MethodParams: param.Make(),
			Params: nil})

	beego.GlobalControllerRouter["restfulapi-beego/controllers:ModuleController"] = append(beego.GlobalControllerRouter["restfulapi-beego/controllers:ModuleController"],
		beego.ControllerComments{
			Method: "Post",
			Router: `/`,
			AllowHTTPMethods: []string{"post"},
			MethodParams: param.Make(),
			Params: nil})

	beego.GlobalControllerRouter["restfulapi-beego/controllers:ModuleController"] = append(beego.GlobalControllerRouter["restfulapi-beego/controllers:ModuleController"],
		beego.ControllerComments{
			Method: "Put",
			Router: `/:Id_cansat`,
			AllowHTTPMethods: []string{"put"},
			MethodParams: param.Make(),
			Params: nil})

	beego.GlobalControllerRouter["restfulapi-beego/controllers:ModuleController"] = append(beego.GlobalControllerRouter["restfulapi-beego/controllers:ModuleController"],
		beego.ControllerComments{
			Method: "Delete",
			Router: `/:Id_cansat`,
			AllowHTTPMethods: []string{"delete"},
			MethodParams: param.Make(),
			Params: nil})

	beego.GlobalControllerRouter["restfulapi-beego/controllers:ModuleController"] = append(beego.GlobalControllerRouter["restfulapi-beego/controllers:ModuleController"],
		beego.ControllerComments{
			Method: "Get",
			Router: `/:Id_usuario`,
			AllowHTTPMethods: []string{"get"},
			MethodParams: param.Make(),
			Params: nil})

	beego.GlobalControllerRouter["restfulapi-beego/controllers:ModuleController"] = append(beego.GlobalControllerRouter["restfulapi-beego/controllers:ModuleController"],
		beego.ControllerComments{
			Method: "GetIdModule",
			Router: `/:Id_usuario/:Id_cansat`,
			AllowHTTPMethods: []string{"get"},
			MethodParams: param.Make(),
			Params: nil})

	beego.GlobalControllerRouter["restfulapi-beego/controllers:ModuleMobileController"] = append(beego.GlobalControllerRouter["restfulapi-beego/controllers:ModuleMobileController"],
		beego.ControllerComments{
			Method: "GetAll",
			Router: `/`,
			AllowHTTPMethods: []string{"get"},
			MethodParams: param.Make(),
			Params: nil})

	beego.GlobalControllerRouter["restfulapi-beego/controllers:ModuleMobileController"] = append(beego.GlobalControllerRouter["restfulapi-beego/controllers:ModuleMobileController"],
		beego.ControllerComments{
			Method: "Get",
			Router: `/:Id_usuario`,
			AllowHTTPMethods: []string{"get"},
			MethodParams: param.Make(),
			Params: nil})

	beego.GlobalControllerRouter["restfulapi-beego/controllers:ModuleMobileController"] = append(beego.GlobalControllerRouter["restfulapi-beego/controllers:ModuleMobileController"],
		beego.ControllerComments{
			Method: "GetIdModule",
			Router: `/:Id_usuario/:Id_cansat`,
			AllowHTTPMethods: []string{"get"},
			MethodParams: param.Make(),
			Params: nil})

	beego.GlobalControllerRouter["restfulapi-beego/controllers:SensorController"] = append(beego.GlobalControllerRouter["restfulapi-beego/controllers:SensorController"],
		beego.ControllerComments{
			Method: "GetAll",
			Router: `/`,
			AllowHTTPMethods: []string{"get"},
			MethodParams: param.Make(),
			Params: nil})

	beego.GlobalControllerRouter["restfulapi-beego/controllers:SensorController"] = append(beego.GlobalControllerRouter["restfulapi-beego/controllers:SensorController"],
		beego.ControllerComments{
			Method: "Get",
			Router: `/:Id_usuario`,
			AllowHTTPMethods: []string{"get"},
			MethodParams: param.Make(),
			Params: nil})

	beego.GlobalControllerRouter["restfulapi-beego/controllers:SensorController"] = append(beego.GlobalControllerRouter["restfulapi-beego/controllers:SensorController"],
		beego.ControllerComments{
			Method: "GetIdSensor",
			Router: `/:Id_usuario/:Tipo_sensor`,
			AllowHTTPMethods: []string{"get"},
			MethodParams: param.Make(),
			Params: nil})

	beego.GlobalControllerRouter["restfulapi-beego/controllers:SensorMobileController"] = append(beego.GlobalControllerRouter["restfulapi-beego/controllers:SensorMobileController"],
		beego.ControllerComments{
			Method: "GetAll",
			Router: `/`,
			AllowHTTPMethods: []string{"get"},
			MethodParams: param.Make(),
			Params: nil})

	beego.GlobalControllerRouter["restfulapi-beego/controllers:SensorMobileController"] = append(beego.GlobalControllerRouter["restfulapi-beego/controllers:SensorMobileController"],
		beego.ControllerComments{
			Method: "Get",
			Router: `/:Id_usuario`,
			AllowHTTPMethods: []string{"get"},
			MethodParams: param.Make(),
			Params: nil})

	beego.GlobalControllerRouter["restfulapi-beego/controllers:SensorMobileController"] = append(beego.GlobalControllerRouter["restfulapi-beego/controllers:SensorMobileController"],
		beego.ControllerComments{
			Method: "GetIdSensor",
			Router: `/:Id_usuario/:Tipo_sensor`,
			AllowHTTPMethods: []string{"get"},
			MethodParams: param.Make(),
			Params: nil})

	beego.GlobalControllerRouter["restfulapi-beego/controllers:SensorsTypeController"] = append(beego.GlobalControllerRouter["restfulapi-beego/controllers:SensorsTypeController"],
		beego.ControllerComments{
			Method: "GetAll",
			Router: `/`,
			AllowHTTPMethods: []string{"get"},
			MethodParams: param.Make(),
			Params: nil})

	beego.GlobalControllerRouter["restfulapi-beego/controllers:SensorsTypeController"] = append(beego.GlobalControllerRouter["restfulapi-beego/controllers:SensorsTypeController"],
		beego.ControllerComments{
			Method: "Get",
			Router: `/:Id_usuario`,
			AllowHTTPMethods: []string{"get"},
			MethodParams: param.Make(),
			Params: nil})

	beego.GlobalControllerRouter["restfulapi-beego/controllers:UserController"] = append(beego.GlobalControllerRouter["restfulapi-beego/controllers:UserController"],
		beego.ControllerComments{
			Method: "GetAll",
			Router: `/`,
			AllowHTTPMethods: []string{"get"},
			MethodParams: param.Make(),
			Params: nil})

	beego.GlobalControllerRouter["restfulapi-beego/controllers:UserController"] = append(beego.GlobalControllerRouter["restfulapi-beego/controllers:UserController"],
		beego.ControllerComments{
			Method: "Post",
			Router: `/`,
			AllowHTTPMethods: []string{"post"},
			MethodParams: param.Make(),
			Params: nil})

	beego.GlobalControllerRouter["restfulapi-beego/controllers:UserController"] = append(beego.GlobalControllerRouter["restfulapi-beego/controllers:UserController"],
		beego.ControllerComments{
			Method: "Put",
			Router: `/:Id_usuario`,
			AllowHTTPMethods: []string{"put"},
			MethodParams: param.Make(),
			Params: nil})

	beego.GlobalControllerRouter["restfulapi-beego/controllers:UserController"] = append(beego.GlobalControllerRouter["restfulapi-beego/controllers:UserController"],
		beego.ControllerComments{
			Method: "Delete",
			Router: `/:Id_usuario`,
			AllowHTTPMethods: []string{"delete"},
			MethodParams: param.Make(),
			Params: nil})

	beego.GlobalControllerRouter["restfulapi-beego/controllers:UserController"] = append(beego.GlobalControllerRouter["restfulapi-beego/controllers:UserController"],
		beego.ControllerComments{
			Method: "Get",
			Router: `/:Username`,
			AllowHTTPMethods: []string{"get"},
			MethodParams: param.Make(),
			Params: nil})

	beego.GlobalControllerRouter["restfulapi-beego/controllers:UsernameController"] = append(beego.GlobalControllerRouter["restfulapi-beego/controllers:UsernameController"],
		beego.ControllerComments{
			Method: "Get",
			Router: `/:Id_usuario`,
			AllowHTTPMethods: []string{"get"},
			MethodParams: param.Make(),
			Params: nil})

	beego.GlobalControllerRouter["restfulapi-beego/controllers:ZoneController"] = append(beego.GlobalControllerRouter["restfulapi-beego/controllers:ZoneController"],
		beego.ControllerComments{
			Method: "GetAll",
			Router: `/`,
			AllowHTTPMethods: []string{"get"},
			MethodParams: param.Make(),
			Params: nil})

	beego.GlobalControllerRouter["restfulapi-beego/controllers:ZoneController"] = append(beego.GlobalControllerRouter["restfulapi-beego/controllers:ZoneController"],
		beego.ControllerComments{
			Method: "Get",
			Router: `/:Id_usuario`,
			AllowHTTPMethods: []string{"get"},
			MethodParams: param.Make(),
			Params: nil})

}
