package routers

import (
  "github.com/astaxie/beego";
  "restfulapi-beego/controllers";
)

func init() {
  // namespaces
  var namespaces []string = []string {"Beagons", "BeagonsMobile"}
  // controllers
  var ctrllers []string = []string{"users", "modules", "sensors", "sensorstype", "datameasured", "zones", "alerts", "alertmeasured", "fognodes", "login", "usernames"}

  restfulRouter := beego.NewNamespace("/"+namespaces[0],
    beego.NSNamespace("/"+ctrllers[0],
      beego.NSInclude(
        &controllers.UserController{},
      ),
    ),
    beego.NSNamespace("/"+ctrllers[1],
      beego.NSInclude(
        &controllers.ModuleController{},
      ),
    ),
    beego.NSNamespace("/"+ctrllers[2],
      beego.NSInclude(
        &controllers.SensorController{},
      ),
    ),
    beego.NSNamespace("/"+ctrllers[3],
      beego.NSInclude(
        &controllers.SensorsTypeController{},
      ),
    ),
    beego.NSNamespace("/"+ctrllers[4],
      beego.NSInclude(
        &controllers.DataMeasuredController{},
      ),
    ),
    beego.NSNamespace("/"+ctrllers[5],
      beego.NSInclude(
        &controllers.ZoneController{},
      ),
    ),
    beego.NSNamespace("/"+ctrllers[6],
      beego.NSInclude(
        &controllers.AlertController{},
      ),
    ),
    beego.NSNamespace("/"+ctrllers[7],
      beego.NSInclude(
        &controllers.AlertMeasuredController{},
      ),
    ),
    beego.NSNamespace("/"+ctrllers[8],
      beego.NSInclude(
        &controllers.FogNodeController{},
      ),
    ),
    beego.NSNamespace("/"+ctrllers[9],
      beego.NSInclude(
        &controllers.LoginController{},
      ),
    ),
    beego.NSNamespace("/"+ctrllers[10],
      beego.NSInclude(
        &controllers.UsernameController{},
      ),
    ),
  )
  restfulMobileRouter := beego.NewNamespace("/"+namespaces[1],
    beego.NSNamespace("/"+ctrllers[1],
      beego.NSInclude(
        &controllers.ModuleMobileController{},
      ),
    ),
    beego.NSNamespace("/"+ctrllers[2],
      beego.NSInclude(
        &controllers.SensorMobileController{},
      ),
    ),
    beego.NSNamespace("/"+ctrllers[4],
      beego.NSInclude(
        &controllers.DataMeasuredMobileController{},
      ),
    ),
  )
  beego.AddNamespace(restfulRouter)
  beego.AddNamespace(restfulMobileRouter)
  
  beego.ErrorHandler("401", controllers.NoAuthHandler)
  beego.ErrorHandler("404", controllers.NotFoundHandler)
}
