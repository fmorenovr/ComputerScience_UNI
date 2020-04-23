'use strict';

appControllers.controller('infoUsuariosController',['$scope', '$window','Consultas',function($scope, $window, Consultas) {
  $scope.usuarios = [];
  
  var dataResponse = Consultas.setInit()
  if(!dataResponse.success){
    $window.location.href = dataResponse.url;
  } else {
    Consultas.getUsuarioHome(app.username).then(function(dataResponse){});
  }
  
  Consultas.getInfoUsuarios(false).then(function(dataResponse){
    $scope.usuarios = dataResponse;
  });
}]);
