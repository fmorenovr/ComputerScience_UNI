'use strict';

appControllers.controller('LoginController',['$rootScope','$scope','$window','$timeout','Consultas', function($rootScope, $scope, $window, $timeout, Consultas) {

  $scope.error = false;
  $scope.ingreso = false;
  $scope.dataLoading = false;
  
  var dataRes = Consultas.setInit()
  if(dataRes.success){
    console.log("dataResponse-login es true")
    $window.location.href = dataRes.url;
    $rootScope.redirect = true;
    return
  } else {
    console.log("dataResponse-login es false")
    $rootScope.redirect = false;
  }
  
  $scope.loguear = function (){
    $scope.error = false;
    $scope.ingreso = false;
    $scope.dataLoading = false;
    Consultas.loginUsuario($scope.id_usuario,$scope.id_password).then(function(dataResponse){
      if(dataResponse.success == false){
        $scope.error = true;
      } else {
        $scope.ingreso = true;
      }
      $scope.dataLoading = true;
      $timeout(function () {
        $window.location.href = dataResponse.url;
        $scope.dataLoading = false;
      }, 500);
    });
  };
}]);
