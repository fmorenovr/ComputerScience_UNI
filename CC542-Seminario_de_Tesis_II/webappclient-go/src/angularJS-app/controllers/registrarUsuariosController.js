'use strict';

appControllers.controller('RegistrarUsuarioController',['$scope', '$window', '$timeout', 'Consultas', function($scope, $window, $timeout, Consultas) {
  $scope.respuesta = false;
  $scope.mostrar = false;
  $scope.usuarioactual = [];
  $scope.list_modules = [];
  
  var dataResponse = Consultas.setInit()
  if(!dataResponse.success){
    $window.location.href = dataResponse.url;
  } else {
    Consultas.getUsuarioHome(app.username).then(function(dataResponse){});
  }
  
  var datetime = app.getDateDashboard()
  $scope.f_registro = datetime.fecha
  $scope.h_registro = datetime.hora
  
  $scope.checkboxSelected = [];
  
  Consultas.getInfoUsuario(app.username).then(function(dataResponse){
    $scope.usuarioactual = dataResponse;
    angular.forEach($scope.usuarioactual, function (valueusr, key) {
      $scope.list_modules = valueusr.modules
    });
  });
  
  $scope.toggleSelection = function toggleSelection(gender) {
    var idx = $scope.checkboxSelected.indexOf(gender);
    if (idx > -1) {
      // is currently selected
      $scope.checkboxSelected.splice(idx, 1);
    } else {
      // is newly selected
      $scope.checkboxSelected.push(gender);
    }
  };
  
  $scope.registrar = function (){
    $scope.email_error = app.validarEmail($scope.email)
    if($scope.email_error){
      return
    }
    $scope.password = app.generarPassword(6)
    // use $.param jQuery function to serialize data from JSON 
    var data = $.param({
      name : $scope.nombres,
      lastname : $scope.apellidos,
      email : $scope.email,
      document : $scope.documento,
      username : $scope.username,
      password : $scope.password,
      registration_date : $scope.f_registro + " " + $scope.h_registro,
      modules: $scope.checkboxSelected
    })
    Consultas.registrarUsuario(data).then(function(dataResponse){
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
    $timeout(function () {
      $window.location.reload();
    }, 1000);
  }
}]);
