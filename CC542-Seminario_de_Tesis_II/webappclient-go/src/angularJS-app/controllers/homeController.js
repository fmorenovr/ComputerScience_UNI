'use strict';

appControllers.controller('HomeController',['$rootScope', '$scope', '$window', '$timeout', 'Consultas', 'reverseFilter', function($rootScope, $scope, $window, $timeout, Consultas) {
  $scope.usuarioactual = [];
  
  var dataResponse = Consultas.setInit()
  if($rootScope.redirect){
    console.log("caso 1, viene con redirect")
    Consultas.getUsuarioHome(app.username).then(function(dR){});
  } else {
    if(dataResponse.success){
    console.log("caso 2, no fue redirect")
      Consultas.getUsuarioHome(app.username).then(function(dR){});
    } else {
    console.log("caso 3, regresa login")
      $window.location.href = dataResponse.url;
      return
    }
  }
  
  $scope.passwdType     = "password";
  $scope.respuesta      = false;
  $scope.mostrar        = false;
  $scope.disablecheck   = false;
  $scope.email_error    = false;
  $scope.username_error = false;
  $scope.username
  var id_usuar, local_username

  $scope.checkboxSelected = [];
  Consultas.getInfoUsuario(app.username).then(function(dataResponse){
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
  
  $scope.ocultarPasswd = function (){
    if($scope.passwdType == "text") $scope.passwdType  = "password";
    else if ($scope.passwdType == "password") $scope.passwdType  = "text";
  }
  
  $scope.actualizar = function (){
    if (document.getElementById("username").value == ""){
      $scope.username_error = true
    } else {
      $scope.username_error = Consultas.existUsername(document.getElementById("username").value)
      if (app.username == document.getElementById("username").value)
        $scope.username_error=false
    }
    if ($scope.username_error){
      return
    }
    var datetime = app.getDateDashboard()
    $scope.f_registro = datetime.fecha
    $scope.h_registro = datetime.hora
    $scope.email_error = app.validarEmail(document.getElementById("email").value)
    if($scope.email_error){
      return
    }
    local_username = document.getElementById("username").value
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
    Consultas.updateInfoUsuario(id_usuar, local_username, data).then(function(dataResponse){
      $scope.respuesta = dataResponse;
      if ($scope.respuesta){
        $scope.mostrar = true;
        $timeout(function () {
          $scope.mostrar = false;
        }, 500);
      }
    });
    $scope.email_error = false
    $timeout(function () {
      $window.location.reload();
    }, 1000);
  }
}]);
