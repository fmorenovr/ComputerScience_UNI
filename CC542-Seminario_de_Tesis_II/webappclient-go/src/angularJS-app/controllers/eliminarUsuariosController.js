'use strict';

appControllers.controller('EliminarUsuarioController',['$scope', '$window', '$timeout', 'Consultas', function($scope, $window, $timeout, Consultas) {
  $scope.listusuarios = [];
  $scope.usuarioactual = [];
  
  var dataResponse = Consultas.setInit()
  if(!dataResponse.success){
    $window.location.href = dataResponse.url;
  } else {
    Consultas.getUsuarioHome(app.username).then(function(dataResponse){});
  }
  
  Consultas.getInfoUsuarios(true).then(function(dataResponse){
    $scope.listusuarios = dataResponse;
  });
  
  $scope.respuesta = false;
  $scope.mostrar = false;
  var id_usuar

  $scope.list_modules = [];
  $scope.checkboxSelected = [];
  
  Consultas.getInfoUsuario(app.username).then(function(dataResponse){
    $scope.usuarioactual = dataResponse;
    angular.forEach($scope.usuarioactual, function (valueusr, key) {
      $scope.list_modules = valueusr.modules
    });
  });
  
  $scope.$watch('usuario_watch',function(){
    if ($scope.usuario_watch != undefined){
      $scope.checkboxSelected = [];
      Consultas.getInfoUsuario($scope.usuario_watch).then(function(dataResponse){
        $scope.usuarioactual = dataResponse;
        angular.forEach($scope.usuarioactual, function (valueusr, key) {
          document.getElementById("nombre").value = valueusr.name
          document.getElementById("apellido").value = valueusr.lastname
          document.getElementById("username").value = valueusr.username
          document.getElementById("password").value = valueusr.password
          document.getElementById("documento").value = valueusr.document
          document.getElementById("email").value = valueusr.email
          id_usuar = valueusr.id_user
          var str = valueusr.registration_date
          var res = str.split(" ");
          document.getElementById("fecha").value = res[0]
          document.getElementById("hora").value = res[1]
          angular.forEach(valueusr.modules, function (valuemod, key) {
            $scope.checkboxSelected.push(valuemod.id_moduleiot)
          });
        });
      });
    }
  });
  
  $scope.eliminar = function (){
    Consultas.eliminarUsuario(id_usuar).then(function(dataResponse){
      $scope.respuesta = dataResponse;
      if ($scope.respuesta){
        $scope.mostrar = true;
        $timeout(function () {
          $scope.mostrar = false;
        }, 500);
      }
    });
    document.getElementById("goform").reset();
    //$scope.listusuarios.remove($scope.usuario_watch)
    $scope.listusuarios = []
    Consultas.getInfoUsuarios(true).then(function(dataResponse){
      if (dataResponse != null){
        $scope.listusuarios = dataResponse;
      }
    });
    $timeout(function () {
      $window.location.reload();
    }, 1000);
  }
}]);
