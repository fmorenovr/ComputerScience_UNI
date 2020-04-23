'use strict'

var beagonsDashboard = angular.module('beagonsDashboard', [
  // common essential modules
  'ngMap',
  'ngAnimate',
  'ngStorage',
  'ngCookies',
  'ui.router',
  'ngResource',
  'ui.router.util',
  'ui.jq',
  'ui.event',
  'ui.bootstrap',
  //'chart.js',
  //'ngRoute',

  // page-specific and demo. may be removed
  'angular-bootstrap-select',
  'datatables',
  'datatables.bootstrap',
  'ui.calendar',
  // JWT
  'angular-jwt',

  // application libs
  'app.constants',
  'app.controllers',
  'app.directives',
  'app.factories',
  'app.filters',
  'app.values',
])
.run(function($rootScope){
  $rootScope.redirect = false;
});
