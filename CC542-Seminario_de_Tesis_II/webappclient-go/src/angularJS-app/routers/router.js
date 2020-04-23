'use strict';

beagonsDashboard.config(function($stateProvider, $urlRouterProvider){
  // For any unmatched url, send to /dashboard
  //$urlRouterProvider.otherwise("/dashboard/home/");
  $urlRouterProvider.otherwise("/login");
  $stateProvider.state(app.webapp, {
    abstract: true,
    url: '/'+app.webapp,
    templateUrl: app.views+app.webapp+'.html'
  })
  .state(app.webapp+'.page', {
    url: '/:page/:child',
    params: {
      page: {},
      child: { value: null }
    },
    resolve: {
      deps: ['scriptLoader', function(scriptLoader){
        return scriptLoader;
      }]
    },
    templateProvider: function ($http, $stateParams, scriptLoader) {
      return $http.get(app.views + $stateParams.page + ( $stateParams.child ? "_" + $stateParams.child : "") + '.html')
      .then(function(response) {
        return scriptLoader.loadScriptTagsFromData(response.data);
      }).then(function(responseData){
        return responseData;
      });
    }
  })
  .state('login', {
    url: '/login',
    templateUrl: app.views+'login.html',
    access: {
      isFree: true
    }
  })
});

