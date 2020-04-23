'use strict';

appControllers.controller('infoModulesController',['$scope', '$window','Consultas',function($scope, $window, Consultas) {
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
}]);
