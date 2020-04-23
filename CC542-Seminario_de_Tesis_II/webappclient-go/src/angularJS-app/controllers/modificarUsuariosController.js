'use strict';

appControllers.controller('ModificarUsuarioController',['$scope', '$window', '$timeout', 'Consultas', function($scope, $window, $timeout, Consultas) {
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
    $scope.email_error = false
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
          angular.forEach(valueusr.modules, function (valuemod, key) {
            $scope.checkboxSelected.push(valuemod.id_moduleiot)
          });
        });
      });
    }
  });
  
  $scope.toggleSelection = function toggleSelection(gender) {
    var idx = $scope.checkboxSelected.indexOf(gender);
    if (idx > -1) {
      $scope.checkboxSelected.splice(idx, 1);
    } else {
      $scope.checkboxSelected.push(gender);
    }
  };
  
  $scope.actualizar = function (){
    var datetime = app.getDateDashboard()
    $scope.f_registro = datetime.fecha
    $scope.h_registro = datetime.hora
    $scope.email_error = app.validarEmail(document.getElementById("email").value)
    if($scope.email_error){
      return
    }
    // use $.param jQuery function to serialize data from JSON 
    var data = $.param({
      name     : document.getElementById("nombre").value,
      lastname : document.getElementById("apellido").value,
      document : document.getElementById("documento").value,
      email    : document.getElementById("email").value,
      username : document.getElementById("username").value,
      password : document.getElementById("password").value,
      registration_date : $scope.f_registro + " "+$scope.h_registro,
      modules: $scope.checkboxSelected
    })
    Consultas.actualizarUsuario(id_usuar, data).then(function(dataResponse){
      $scope.respuesta = dataResponse;
      if ($scope.respuesta){
        $scope.mostrar = true;
        $timeout(function () {
          $scope.mostrar = false;
        }, 500);
      }
    });
    document.getElementById("goform").reset();
    $scope.checkboxSelected = [];
    $scope.email_error = false
    Consultas.getInfoUsuarios(true).then(function(dataResponse){
      $scope.listusuarios = dataResponse;
    });
    $timeout(function () {
      $window.location.reload();
    }, 1000);
  }
}]);
