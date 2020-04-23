'use strict'

app.issuperuser = false

appFactories.factory('Consultas', ['jwtHelper', 'infoServices', '$window', '$http', function(jwtHelper, infoServices, $window, $http) {
  var rest = infoServices.rest.protocol+infoServices.rest.url+":"+infoServices.rest.port+"/"
  var restwebclient = rest+infoServices.namespaces.webclient+"/"
  
  var restusers   = restwebclient+infoServices.controllers.users+"/"
  var restmodules = restwebclient+infoServices.controllers.modules+"/"
  var restsensors = restwebclient+infoServices.controllers.sensors+"/"
  var restsensorstype  = restwebclient+infoServices.controllers.sensorstype+"/"
  var restdatameasured = restwebclient+infoServices.controllers.datameasured+"/"
  var restlogin     = restwebclient+infoServices.controllers.login+"/"
  var restusernames = restwebclient+infoServices.controllers.usernames+"/"
  
  var factory = {
    dataResponse: null,
    setInit: setInit,
    logoutUsuario: logoutUsuario,
    loginUsuario: loginUsuario,
    getUsuarioHome: getUsuarioHome,
    getEspecificCansat: getEspecificCansat,
    existUsername: existUsername,
    registrarUsuario: registrarUsuario,
    actualizarUsuario: actualizarUsuario,
    eliminarUsuario: eliminarUsuario,
    registrarCansat: registrarCansat,
    actualizarCansat: actualizarCansat,
    eliminarCansat: eliminarCansat,
    getInfoUsuarios: getInfoUsuarios,
    getInfoUsuario: getInfoUsuario,
    updateInfoUsuario: updateInfoUsuario,
    getDatosSensadosTS_D: getDatosSensadosTS_D,
    getInfoCansats: getInfoCansats,
    getInfoCansats_Sensors: getInfoCansats_Sensors,
    getInfoSensores: getInfoSensores,
    getCansatsLocation: getCansatsLocation,
    getTipoSensores: getTipoSensores,
    getTipoSensoresEspec: getTipoSensoresEspec,
    setHeatMapsPos: setHeatMapsPos,
    getDatosSensadosTS_Hours: getDatosSensadosTS_Hours,
    getDatosSensadosTS_Dates: getDatosSensadosTS_Dates
  };
  return factory;

  function setInit(){
    if (localStorage.getItem('username') == null){
      factory.dataResponse = {url:infoServices.urls.login, success: false};
    } else {
      if (localStorage.getItem('tokenString') == null){
        factory.dataResponse = {url:infoServices.urls.login, success: false};
      } else {
        var isExpired = jwtHelper.isTokenExpired(localStorage.getItem('tokenString'))
        var dateExpires = jwtHelper.getTokenExpirationDate(localStorage.getItem('tokenString'))
        if(isExpired){
          factory.dataResponse = {url:infoServices.urls.login, success: false};
        } else {
          infoServices.headerHTTP.headers['BeaGons-rest-JWT'] = localStorage.getItem("tokenString")
          app.dateLogin = localStorage.getItem('dateLogin')
          app.issuperuser = localStorage.getItem('issuperuser');
          app.user_id = localStorage.getItem('user_id');
          app.username = localStorage.getItem('username');
          factory.dataResponse = {url:infoServices.urls.dashboard, success: true};
        }
      }
    }
    return factory.dataResponse;
  }
  
  function logoutUsuario(){
    localStorage.removeItem('issuperuser');
    localStorage.clear();
    factory.dataResponse = {url:infoServices.urls.login};
    return factory.dataResponse;
  }

  function loginUsuario(usuario_username,passwd){
    var respuesta, tokenString;
    var data = $.param({
      username : usuario_username,
      password : passwd
    })
    //var data = usuario_username+"/"+passwd
    //return $http.get(restlogin+data, infoServices.headerHTTP).then(function(response){
    return $http.post(restlogin, data, infoServices.headerHTTP).then(function(response){
      respuesta   = response.data.Logged
      if(respuesta){
        app.tokenString = response.data.Token
        app.username = usuario_username
        localStorage.setItem('username', app.username);
        localStorage.setItem('tokenString', app.tokenString)
        infoServices.headerHTTP.headers['BeaGons-rest-JWT'] = localStorage.getItem("tokenString")
        factory.dataResponse = {url:infoServices.urls.dashboard, success: true};
      } else {
        factory.dataResponse = {url:infoServices.urls.login, success: false};
      }
      return factory.dataResponse;
    }, function(response){
      console.log("error haciendo login")
      if (response.status == 401){
        localStorage.removeItem('issuperuser');
        localStorage.clear();
        $window.location.href = "/sessionExpired";
        return
      }
      factory.dataResponse = {url:infoServices.urls.login, success: false};
      return factory.dataResponse;
    });
  }

  function getUsuarioHome(username){
    var respuesta = [];
    var datetime = app.getDateDashboard();
    var datelogin = datetime.fecha + ' ' + datetime.hora;
    var issuperuser, username, user_id;
    localStorage.removeItem('issuperuser')
    return $http.get(restusers+username, infoServices.headerHTTP).then(function(response){
      respuesta = response.data[0];
      issuperuser = respuesta.is_admin
      app.issuperuser = String(issuperuser)
      //username = respuesta.user[0].username;
      user_id = respuesta.id_user;
      if(localStorage.getItem('dateLogin')==null){
        localStorage.setItem('dateLogin',datelogin);
        app.dateLogin = datelogin
      }
      localStorage.setItem('issuperuser',issuperuser);
      localStorage.setItem('user_id',user_id);
      //localStorage.setItem('username',username);
      factory.dataResponse = {url:infoServices.urls.dashboard, success: true};
      return factory.dataResponse;
    }, function(response){
      console.log('Error consultando los usuarios');
      if (response.status == 401){
        localStorage.removeItem('issuperuser');
        localStorage.clear();
        $window.location.href = "/sessionExpired";
        return
      }
      return;
    });
  }
  
  function getEspecificCansat(id){
    return $http.get(restmodules+app.username+"/"+id, infoServices.headerHTTP).then(function(response){
      factory.dataResponse = response.data;
      return factory.dataResponse;
    }, function(response){
      console.log('Error consultando la información de los dispositivos');
      if (response.status == 401){
        localStorage.removeItem('issuperuser');
        localStorage.clear();
        $window.location.href = "/sessionExpired";
        return
      }
      return;
    });
  }
  
  function getInfoUsuario(username){
    var respuesta = [];
    return $http.get(restusers+username, infoServices.headerHTTP).then(function(response){
      if (response.data !== 'Usuario no existe'){
        respuesta = response.data;
        factory.dataResponse = respuesta;
        return factory.dataResponse;
      }
    }, function(response){
      console.log('Error consultando la informacion de usuario');
      if (response.status == 401){
        localStorage.removeItem('issuperuser');
        localStorage.clear();
        $window.location.href = "/sessionExpired";
        return
      }
      return;
    });
  }

  function updateInfoUsuario(usuario, username, data){
    localStorage.setItem('username', username);
    return $http.put(restusers+usuario, data, infoServices.headerHTTP).then(function(response){
      factory.dataResponse = true;
      return factory.dataResponse;
    }, function(response){
      if (response.status == 401){
        localStorage.removeItem('issuperuser');
        localStorage.clear();
        $window.location.href = "/sessionExpired";
        return
      }
      factory.dataResponse = false;
      return factory.dataResponse;
    });
  }

  function getInfoUsuarios(logical){
    var usuarios = [];
    var users = [];
    return $http.get(restusers, infoServices.headerHTTP).then(function(response){
      usuarios = response.data;
      angular.forEach(usuarios, function (value, key) {
        if(logical){
          if(value.username !== app.username){
            users.push({username: value.username, id_usuario: value.id_user, nombre: value.name, apellido: value.lastname, doc: value.document, mail: value.email, f_registro: value.f_registro, h_registro: value.h_registro});
          }
        } else {
          users.push({id_usuario: value.id_user, nombre: value.name, apellido: value.lastname, doc: value.document, mail: value.email, username: value.username, registration_date: value.registration_date});
        }
      });
      factory.dataResponse = users;
      return factory.dataResponse;
    }, function(response){
      console.log('Error consultando la información de los dispositivos');
      if (response.status == 401){
        localStorage.removeItem('issuperuser');
        localStorage.clear();
        $window.location.href = "/sessionExpired";
        return
      }
      return;
    });
  }
  
  function existUsername(username){
    $http.get(restusernames+username, infoServices.headerHTTP).then(function(response){
      factory.dataResponse = response.data;
    }, function(response){
      factory.dataResponse = false;
      if (response.status == 401){
        localStorage.removeItem('issuperuser');
        localStorage.clear();
        $window.location.href = "/sessionExpired";
        return
      }
      return
    });
    return factory.dataResponse;
  }
  
  function registrarUsuario(data){
    return $http.post(restusers, data, infoServices.headerHTTP).then(function(response){
      factory.dataResponse = true;
      return factory.dataResponse;
    }, function(response){
      factory.dataResponse = false;
      if (response.status == 401){
        localStorage.removeItem('issuperuser');
        localStorage.clear();
        $window.location.href = "/sessionExpired";
        return
      }
      return factory.dataResponse;
    });
  }
  
  function actualizarUsuario(usuario, data){
    return $http.put(restusers+usuario, data, infoServices.headerHTTP).then(function(response){
      factory.dataResponse = true;
      return factory.dataResponse;
    }, function(response){
      factory.dataResponse = false;
      if (response.status == 401){
        localStorage.removeItem('issuperuser');
        localStorage.clear();
        $window.location.href = "/sessionExpired";
        return
      }
      return factory.dataResponse;
    });
  }
  
  function eliminarUsuario(id_usuario){
    return $http.delete(restusers+id_usuario, infoServices.headerHTTP).then(function(response){
      factory.dataResponse = true;
      return factory.dataResponse;
    }, function(response){
      factory.dataResponse = false;
      if (response.status == 401){
        localStorage.removeItem('issuperuser');
        localStorage.clear();
        $window.location.href = "/sessionExpired";
        return
      }
      return factory.dataResponse;
    });
  }
  
  function registrarCansat(data){
    return $http.post(restmodules, data, infoServices.headerHTTP).then(function(response){
      factory.dataResponse = true;
      return factory.dataResponse;
    }, function(response){
      factory.dataResponse = false;
      if (response.status == 401){
        localStorage.removeItem('issuperuser');
        localStorage.clear();
        $window.location.href = "/sessionExpired";
        return
      }
      return factory.dataResponse;
    });
  }
  
  function actualizarCansat(module,data){
    return $http.put(restmodules+module, data, infoServices.headerHTTP).then(function(response){
      factory.dataResponse = true;
      return factory.dataResponse;
    }, function(response){
      factory.dataResponse = false;
      if (response.status == 401){
        localStorage.removeItem('issuperuser');
        localStorage.clear();
        $window.location.href = "/sessionExpired";
        return
      }
      return factory.dataResponse;
    });
  }
  
  function eliminarCansat(id_module){
    return $http.delete(restmodules+id_module, infoServices.headerHTTP).then(function(response){
      factory.dataResponse = true;
      return factory.dataResponse;
    }, function(response){
      factory.dataResponse = false;
      if (response.status == 401){
        localStorage.removeItem('issuperuser');
        localStorage.clear();
        $window.location.href = "/sessionExpired";
        return
      }
      return factory.dataResponse;
    });
  }

  function getDatosSensadosTS_D(tipo_sensor,dispositivo,last){ // tipo sensor por dispositivo
    var sensoresdato = [];
    return $http.get(restdatameasured+app.username+"/"+ tipo_sensor+"/"+dispositivo+"/"+last, infoServices.headerHTTP).then(function(response){
      if (response.data !=="Sensor no existe"){
        sensoresdato = response.data;
        factory.dataResponse = sensoresdato;
      } else {
        factory.dataResponse = 'incorrecto';
      }
      return factory.dataResponse;
    }, function(response){
      console.log('Error en Sensores Datos');
      if (response.status == 401){
        localStorage.removeItem('issuperuser');
        localStorage.clear();
        $window.location.href = "/sessionExpired";
        return
      }
      return;
    });
  }
  
  function getDatosSensadosTS_Dates(tipo_sensor,dispositivo,dateinit,datefin,last){
    var sensoresdato = [];
    return $http.get(restdatameasured+app.username+"/"+ tipo_sensor+"/"+dispositivo+"/"+dateinit+"/"+datefin+"/"+last, infoServices.headerHTTP).then(function(response){
      if (response.data !=="Sensor no existe"){
        sensoresdato = response.data;
        factory.dataResponse = sensoresdato;
      } else {
        factory.dataResponse = 'incorrecto';
      }
      return factory.dataResponse;
    }, function(response){
      console.log('Error en Sensores Datos');
      if (response.status == 401){
        localStorage.removeItem('issuperuser');
        localStorage.clear();
        $window.location.href = "/sessionExpired";
        return
      }
      return;
    });
  }
  
  function getDatosSensadosTS_Hours(tipo_sensor,dispositivo,dateinit,datefin,horainit,horafin,last){
    var sensoresdato = [];
    return $http.get(restdatameasured+app.username+"/"+ tipo_sensor+"/"+dispositivo+"/"+dateinit+"/"+datefin+"/"+horainit+"/"+horafin+"/"+last, infoServices.headerHTTP).then(function(response){
      if (response.data !=="Sensor no existe"){
        sensoresdato = response.data;
        factory.dataResponse = sensoresdato;
      } else {
        factory.dataResponse = 'incorrecto';
      }
      return factory.dataResponse;
    }, function(response){
      console.log('Error en Sensores Datos');
      if (response.status == 401){
        localStorage.removeItem('issuperuser');
        localStorage.clear();
        $window.location.href = "/sessionExpired";
        return
      }
      return;
    });
  }

  function getInfoCansats(usuarioId){
    return $http.get(restmodules+usuarioId, infoServices.headerHTTP).then(function(response){
      if (response.data != "IotDevice no existe"){
        factory.dataResponse = response.data;
      } else {
        factory.dataResponse = null
      }
      return factory.dataResponse;
    }, function(response){
      console.log('Error consultando la información de los dispositivos');
      if (response.status == 401){
        localStorage.removeItem('issuperuser');
        localStorage.clear();
        $window.location.href = "/sessionExpired";
        return
      }
      return;
    });
  }
  
  function getInfoCansats_Sensors(usuarioId,id_cans){
    var sensorResponse = [];
    var sensorData = [];
    return $http.get(restmodules+usuarioId+"/"+id_cans, infoServices.headerHTTP).then(function(response){
      sensorResponse = response.data;
      angular.forEach(sensorResponse, function (value, key) {
        var Id_moduleiot = value.id_moduleiot;
        angular.forEach(value.sensors, function (value, key) {
          sensorData.push({id_cansat: Id_moduleiot, id_sensor: value.id_sensor,tipo_sensor: value.type, unidad: value.unit, modelo: value.model, date_installed: value.date_installed});
        });
      });
      factory.dataResponse = sensorData;
      return factory.dataResponse;
    }, function(response){
      console.log('Error consultando la información de los dispositivos');
      if (response.status == 401){
        localStorage.removeItem('issuperuser');
        localStorage.clear();
        $window.location.href = "/sessionExpired";
      }
      return;
    });
  }

  function getInfoSensores(usuarioId){
    var sensorResponse = [];
    var sensorData = [];
    return $http.get(restmodules+usuarioId, infoServices.headerHTTP).then(function(response){
      sensorResponse = response.data;
      angular.forEach(sensorResponse, function (value, key) {
        var Id_moduleiot = value.id_moduleiot;
        angular.forEach(value.sensors, function (value, key) {
          sensorData.push({id_cansat: Id_moduleiot, id_sensor: value.id_sensor,tipo_sensor: value.type, unidad: value.unit, modelo: value.model, date_installed: value.date_installed});
        });
      });
      factory.dataResponse = sensorData;
      return factory.dataResponse;
    }, function(response){
      console.log('Error consultando la información de los sensores');
      if (response.status == 401){
        localStorage.removeItem('issuperuser');
        localStorage.clear();
        $window.location.href = "/sessionExpired";
      }
      return;
    });
  }

  function getCansatsLocation(){
    var cansats = [];
    var markers = [];
    return $http.get(restmodules+app.username, infoServices.headerHTTP).then(function(response){
      cansats = response.data;
      if (cansats != "IotDevice no existe"){
        angular.forEach(cansats, function (value, key) {
          markers.push({pos: [value.latitude, value.longuitude], id: value.id_moduleiot, sensores: value.sensors, sector:value.sector, zona:value.zone, polygonos: value.polygons });
        });
        factory.dataResponse = markers;
      }
      else {
        factory.dataResponse = null;
      }
      return factory.dataResponse;
    }, function(response){
      console.log('Error en la consulta de las posiciones de dispositivos');
      if (response.status == 401){
        localStorage.removeItem('issuperuser');
        localStorage.clear();
        $window.location.href = "/sessionExpired";
        return
      }
      return;
    });
  }
  
  function getTipoSensores(){
    return $http.get(restsensorstype+app.username, infoServices.headerHTTP).then(function(response){
     factory.dataResponse = response.data;
     return factory.dataResponse
    }, function(response){
      console.log('Error en la consulta de tipos de sensores');
      if (response.status == 401){
        localStorage.removeItem('issuperuser');
        localStorage.clear();
        $window.location.href = "/sessionExpired";
        return
      }
      return;
    });
  }

  function getTipoSensoresEspec(tipo_sensor){
    var dispositivosData = [];
    var dispositivos = [];
    return $http.get(restsensors+app.username+"/"+tipo_sensor, infoServices.headerHTTP).then(function(response){
      if (response.data !== 'Sensor no existe'){
        dispositivosData = response.data;
        angular.forEach(dispositivosData, function (value,key){
          if(value.sensors != null){
            dispositivos.push(value);
          }
        });
        factory.dataResponse = dispositivos;
        return factory.dataResponse;
      }
    }, function(response){
      console.log('Error en Dispositivos');
      if (response.status == 401){
        localStorage.removeItem('issuperuser');
        localStorage.clear();
        $window.location.href = "/sessionExpired";
        return
      }
      return;
    });
  }

  function setHeatMapsPos(tipo_sensor){
    var heatCansat =[];
    var heatDataPosAux = [];
    return $http.get(restsensors+app.username+"/"+tipo_sensor, infoServices.headerHTTP).then(function(response){
      heatCansat = response.data;
      angular.forEach(heatCansat, function (value,key){
        if(value.sensors != null){
          heatDataPosAux.push({lat: value.latitude, lon: value.longuitude, id: value.id_moduleiot, sensores: value.sensors, sector:value.sector, zona:value.zone, polygonos: value.polygons})
        }
      });
      factory.dataResponse = heatDataPosAux;
      return factory.dataResponse;
    }, function(response){
      console.log('Error en las coordenadas de los heatmaps');
      if (response.status == 401){
        localStorage.removeItem('issuperuser');
        localStorage.clear();
        $window.location.href = "/sessionExpired";
        return
      }
      return;
    });
  }
}]);

