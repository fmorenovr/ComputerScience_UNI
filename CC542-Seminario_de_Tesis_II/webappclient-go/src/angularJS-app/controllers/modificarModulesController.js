'use strict';

appControllers.controller('ModificarModuleController',['$scope', '$window', '$timeout', 'Consultas', function($scope, $window, $timeout, Consultas) {
  $scope.listcansats = [];
  $scope.cansatactual = [];
  
  var dataResponse = Consultas.setInit()
  if(!dataResponse.success){
    $window.location.href = dataResponse.url;
  } else {
    Consultas.getUsuarioHome(app.username).then(function(dataResponse){});
  }
  
  Consultas.getInfoCansats(app.username).then(function(dataResponse){
    $scope.listcansats = dataResponse;
  });
  
  $scope.respuesta = false;
  $scope.mostrar = false;
  var id_canst;
  $scope.iotdevices=[];
  $scope.pospolygons = [];
  
  $scope.$watch('cansat_watch',function(){
    if ($scope.cansat_watch != undefined){
      Consultas.getEspecificCansat($scope.cansat_watch).then(function(dataResponse){
        $scope.cansatactual = dataResponse;
          angular.forEach($scope.cansatactual, function (valueusr, key) {
            $scope.modelo = valueusr.model
            $scope.longuitud = valueusr.longuitude
            $scope.latitud = valueusr.latitude
            $scope.zona = valueusr.zone
            $scope.sector = valueusr.sector
            /*var str = valueusr.installation_date
            var res = str.split(" ");
            document.getElementById("fecha").value = res[0]
            document.getElementById("hora").value = res[1]*/
            $scope.iotdevices = valueusr.sensors
            $scope.pospolygons = valueusr.polygon
            id_canst = valueusr.id_moduleiot
          });
      });
    }
  });
  
  $scope.addNewPos = function() {
    var newItemNo = $scope.pospolygons.length+1;
    $scope.pospolygons.push({ latitude: 0, longuitude: 0 });
  };
  
  $scope.removePos = function() {
    var lastItem = $scope.pospolygons.length-1;
    $scope.pospolygons.splice(lastItem);
  };
  
  $scope.addNewIoTDevice = function() {
    var dateaux = app.getDateDashboard()
    var newItemNo = $scope.iotdevices.length+1;
    if (newItemNo > 1){
      $scope.iotdevices[(newItemNo-2)].unit = app.getUnidad($scope.iotdevices[(newItemNo-2)].type)
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
  
  $scope.actualizar = function (){
    var datetime = app.getDateDashboard()
    $scope.f_registro = datetime.fecha
    $scope.h_registro = datetime.hora
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
      console.log(typeof($scope.latitud))
      console.log(typeof($scope.longuitud))
      console.log($scope.pos_error)
      return
    }*/
    // use $.param jQuery function to serialize data from JSON 
    var data = $.param({
      model             : $scope.modelo,
      latitude          : $scope.latitud,
      longuitude        : $scope.longuitud,
      zone              : $scope.zona,
      sector            : $scope.sector,
      installation_date : $scope.f_registro + " "+ $scope.h_registro,
      polygons          :  $scope.pospolygons,
      sensors           :   $scope.iotdevices
    })
    Consultas.actualizarCansat(id_canst, data).then(function(dataResponse){
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
