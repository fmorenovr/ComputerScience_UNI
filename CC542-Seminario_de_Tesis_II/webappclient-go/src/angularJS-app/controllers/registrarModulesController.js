'use strict';

appControllers.controller('RegistrarModuleController',['$scope', '$window', '$timeout', 'Consultas', function($scope, $window, $timeout, Consultas) {
  $scope.respuesta = false;
  $scope.mostrar = false;
  
  var dataResponse = Consultas.setInit()
  if(!dataResponse.success){
    $window.location.href = dataResponse.url;
  } else {
    Consultas.getUsuarioHome(app.username).then(function(dataResponse){});
  }
  
  /*
  Consultas.getTipoSensoresEspec(tipo_sensor).then(function(dataResponse){
    $scope.sensoresunidad = dataResponse;
  });
  */
  var datetime = app.getDateDashboard()
  $scope.f_registro = datetime.fecha
  $scope.h_registro = datetime.hora
  
  $scope.iotdevices = [{ date_installed: datetime.fecha + " " + datetime.hora }];
  $scope.pospolygons = [{ latitude: 0, longuitude: 0 }];
  
  $scope.addNewPos = function() {
    var newItemNo = $scope.pospolygons.length+1;
    $scope.pospolygons.push({ latitude: 0, longuitude: 0 });
  };
  
  $scope.removePos = function() {
    var lastItem = $scope.pospolygons.length-1;
    $scope.pospolygons.splice(lastItem);
  };
  
  $scope.addNewIoTDevice = function() {
    var newItemNo = $scope.iotdevices.length+1;
    var dateaux = app.getDateDashboard()
    if (newItemNo > 1){
      $scope.iotdevices[(newItemNo-2)].unit     = app.getUnidad($scope.iotdevices[(newItemNo-2)].type)
      if ($scope.iotdevices[(newItemNo-2)].state !="free" && $scope.iotdevices[(newItemNo-2)].state !="private"){
        $scope.iotdevices[(newItemNo-2)].error_state=true;
        return
      } else {
        $scope.iotdevices[(newItemNo-2)].error_state=false;
      }
      if ($scope.iotdevices[(newItemNo-2)].unit ==""){
        $scope.iotdevices[(newItemNo-2)].error_tipo=true;
      } else {
        $scope.iotdevices[(newItemNo-2)].error_tipo=false;
        $scope.iotdevices.push({ date_installed: dateaux.fecha + " " + dateaux.hora });
      }
    } else {
      $scope.iotdevices.push({ date_installed: dateaux.fecha + " " + dateaux.hora });
    }
  };
    
  $scope.removeIoTDevice = function() {
    var lastItem = $scope.iotdevices.length-1;
    $scope.iotdevices.splice(lastItem);
  };
  
  $scope.registrar = function (){
    var newItemNo = $scope.iotdevices.length+1;
    if ($scope.iotdevices.length >= 1){
      $scope.iotdevices[(newItemNo-2)].unit = app.getUnidad($scope.iotdevices[(newItemNo-2)].type)
      if ($scope.iotdevices[(newItemNo-2)].unit ==""){
        $scope.iotdevices[(newItemNo-2)].error_tipo=true;
        return
      }
      if ($scope.iotdevices[(newItemNo-2)].state !="free" && $scope.iotdevices[(newItemNo-2)].state !="private"){
        $scope.iotdevices[(newItemNo-2)].error_state=true;
        return
      }
    }
    /*if(typeof($scope.latitud)!='number' || typeof($scope.longuitud)!='number'){
      $scope.pos_error = true
      return
    }*/
    // use $.param jQuery function to serialize data from JSON
    $scope.password = app.generarPassword(6)
    var data = $.param({
      model             :    $scope.modelo,
      longuitude        : $scope.longuitud,
      latitude          :   $scope.latitud,
      zone              :     $scope.zona,
      sector            :     $scope.sector,
      installation_date : $scope.f_registro + " " + $scope.h_registro,
      polygons          :  $scope.pospolygons,
      sensors           :   $scope.iotdevices
    })
    Consultas.registrarCansat(data).then(function(dataResponse){
      $scope.respuesta = dataResponse;
      if ($scope.respuesta){
        $scope.mostrar = true;
        $timeout(function () {
          $scope.mostrar = false;
        }, 500);
      }
    });
    document.getElementById("goform").reset();
    $scope.iotdevices = [];
    $scope.pos_error = false
    $timeout(function () {
      $window.location.reload();
    }, 1000);
  }
}]);
