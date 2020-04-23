'use strict';

appControllers.controller('LogoutController',['$scope','$window','$timeout','Consultas', function($scope, $window, $timeout, Consultas) {
  $scope.logout = function (){
    var dataResponse = Consultas.logoutUsuario()
    $timeout(function () {
      $window.location.href = dataResponse.url;
    }, 500);
  };
}]);
