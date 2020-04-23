'use strict';

appControllers.controller('infoModulesAdminController',['$scope', '$window','Consultas',function($scope, $window, Consultas) {
  $scope.cansats = [];
  $scope.list_usuarios = [];
  
  $scope.usuario_watch = '';
  
  var dataResponse = Consultas.setInit()
  if(!dataResponse.success){
    $window.location.href = dataResponse.url;
  } else {
    Consultas.getUsuarioHome(app.username).then(function(dataResponse){});
  }
  
  Consultas.getInfoCansats(app.username).then(function(dataResponse){
    $scope.cansats = dataResponse;
  });
  
  Consultas.getInfoUsuarios(false).then(function(dataResponse){
    $scope.list_usuarios = dataResponse;
  });
  
  $scope.$watch('usuario_watch',function(){
    $scope.dataUsuario();
  });
  
  $scope.dataUsuario = function (){
    $scope.cansats = [];
    if($scope.usuario_watch !== ''){
      Consultas.getInfoCansats($scope.usuario_watch).then(function(dataResponse){
        $scope.cansats = dataResponse;
      });
    }
  }
}]);
