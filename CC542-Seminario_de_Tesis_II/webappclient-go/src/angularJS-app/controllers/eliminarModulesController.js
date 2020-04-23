'use strict';

appControllers.controller('EliminarModuleController',['$scope', '$window', '$timeout', 'Consultas', function($scope, $window, $timeout, Consultas) {
  $scope.listcansats = [];
  $scope.cansatactual = [];
  
  var dataResponse = Consultas.setInit()
  if(!dataResponse.success){
    $window.location.href = dataResponse.url;
  } else {
    Consultas.getUsuarioHome(app.username).then(function(dataResponse){});
  }
  
  Consultas.getInfoCansats(app.username).then(function(dataResponse){
    if (dataResponse != null){
      $scope.listcansats = dataResponse;
    }
  });
  
  $scope.respuesta = false;
  $scope.mostrar = false;
  var id_canst;
  $scope.list_sensores=[];
  
  $scope.$watch('cansat_watch',function(){
    if ($scope.cansat_watch != undefined){
      Consultas.getEspecificCansat($scope.cansat_watch).then(function(dataResponse){
        $scope.cansatactual = dataResponse;
          angular.forEach($scope.cansatactual, function (valueusr, key) {
            document.getElementById("modelo").value = valueusr.model
            document.getElementById("longuitud").value = valueusr.longuitude
            document.getElementById("latitud").value = valueusr.latitude
            document.getElementById("zona").value = valueusr.zone
            document.getElementById("sector").value = valueusr.sector
            var str = valueusr.installation_date
            var res = str.split(" ");
            document.getElementById("fecha").value = res[0]
            document.getElementById("hora").value = res[1]
            $scope.list_sensores = valueusr.sensors
            id_canst = valueusr.id_moduleiot
          });
      });
    }
  })
  
  $scope.eliminar = function (){
    Consultas.eliminarCansat(id_canst).then(function(dataResponse){
      $scope.respuesta = dataResponse;
      if ($scope.respuesta){
        $scope.mostrar = true;
        $timeout(function () {
          $scope.mostrar = false;
        }, 500);
      }
    });
    document.getElementById("goform").reset();
    $scope.list_sensores = [];
    //$scope.listcansats.remove($scope.cansats_watch)
    $scope.listcansats = [];
    Consultas.getInfoCansats(app.user_id).then(function(dataResponse){
      if (dataResponse != null){
        $scope.listcansats = dataResponse;
      }
    });
    $timeout(function () {
      $window.location.reload();
    }, 1000);
  }
}]);
