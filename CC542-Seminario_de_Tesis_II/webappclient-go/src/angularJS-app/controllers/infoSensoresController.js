'use strict';

appControllers.controller('infoSensoresController',['$scope','$window', 'Consultas',function($scope, $window, Consultas) {
  $scope.sensores = [];
  $scope.list_modulos = [];
  
  $scope.modulo_watch = '';
  
  var dataResponse = Consultas.setInit()
  if(!dataResponse.success){
    $window.location.href = dataResponse.url;
  } else {
    Consultas.getUsuarioHome(app.username).then(function(dataResponse){});
  }
  
  Consultas.getInfoSensores(app.username).then(function(dataResponse){
    $scope.sensores = dataResponse;
  });

  Consultas.getInfoCansats(app.username).then(function(dataResponse){
    $scope.list_modulos = dataResponse;
  });

  $scope.$watch('modulo_watch',function(){
    $scope.dataSensores();
  });
  
  $scope.dataSensores = function (){
    $scope.sensores = [];
    if($scope.modulo_watch !== ''){
      Consultas.getInfoCansats_Sensors(app.username,$scope.modulo_watch).then(function(dataResponse){
        $scope.sensores = dataResponse;
        //console.log($scope.sensores)
      });
    }
  }

}]);
