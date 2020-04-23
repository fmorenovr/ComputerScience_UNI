'use strict';

var appControllers = angular.module('app.controllers',[]);

appControllers.controller('dashboardAppController', ['$scope','$localStorage',function ($scope, $localStorage){

  $scope.app = app;
  if (angular.isDefined($localStorage.state)){
    $scope.app.state = $localStorage.state;
  } else {
    $localStorage.state = $scope.app.state;
  }
  $scope.print = function(){
    window.print();
  };
  
  $scope.$on('$stateChangeSuccess', function(event, toState, toParams, fromState, fromParams){
    $scope.loginPage = toState.name == 'login';
    $scope.errorPage = toState.name == 'error';
    $(document).trigger('sn:loaded', [event, toState, toParams, fromState, fromParams]);
  });
}]);
