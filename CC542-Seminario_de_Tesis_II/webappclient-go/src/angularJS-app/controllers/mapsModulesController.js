'use strict';

appControllers.controller('mapsModulesController',['Consultas', '$window', function(Consultas, $window) {

  var dataResponse = Consultas.setInit()
  if(!dataResponse.success){
    $window.location.href = dataResponse.url;
  } else {
    Consultas.getUsuarioHome(app.username).then(function(dataResponse){});
  }
}]);
