var app = angular.module('cifradoApp', ['app.Controllers']);

var appControllers = angular.module('app.Controllers',[])

appControllers.controller('cifradoController', ['$scope',function($scope) {
  
  $scope.caras = 3 // numero de filas
  
  // orden de las filas influye
  // En un lugar de la Mancha, de cuyo nombre no quiero acordarme
  
  $scope.cifrar = function(){
    $scope.cifrarMensaje()
  }
  
  var Strings = {};
  Strings.orEmpty = function( entity ) {
    return entity || "";
  };
  
  $scope.encrypt = function (messageEncrypt, caras) {
    // Construye la matriz
    var i, j
    var ln = (messageEncrypt).length
    var text = ""
    var nblanks = 0
    var tabla = [], subtabla = []
    for(i = 0; i < ln; i=i+caras) {
      text = ""
      subtabla = [];
      for(j = 0; j < caras; j++){
        if (messageEncrypt[i+j] == undefined){
          nblanks +=1
          subtabla.push(" ")
        } else {
          subtabla.push(messageEncrypt[i+j]);
        }
      }
      tabla.push(subtabla)
    }
    nfilas = tabla.length    // filas
    ncolms = tabla[0].length // columnas
    // imprime la conversion a matriz
    for(i = 0; i < nfilas; i++) {
      console.log(Strings.orEmpty(tabla[i]))
    }
    // transpuesta de la matriz y contruir el mensaje
    text = ""
    console.log('Filas :' + nfilas)
    console.log('Columnas :'+ncolms)
    console.log("Blancos :"+nblanks)
    for(i = 0; i < ncolms; i++) {
      for(j = 0; j < nfilas; j++){
        //console.log(Strings.orEmpty(tabla[i][j]))
        text += Strings.orEmpty(tabla[j][i])
      }
    }
    console.log(messageEncrypt)
    console.log(text)
    return text
  }
  
  $scope.cifrarMensaje = function(){
    if ($scope.messageEncrypt != "" && $scope.messageEncrypt != undefined){
      if ($scope.messageCaras == "" || $scope.messageCaras == undefined) {
        $scope.caras = 10
      } else {
        $scope.caras = parseInt($scope.messageCaras)
      }
      /*if ($scope.messageMethod == "" || $scope.messageMethod == undefined){
        $scope.method = "1"
      } else {
        $scope.method = $scope.messageMethod
      }*/
      $scope.messageDecrypt = $scope.encrypt($scope.messageEncrypt, $scope.caras)
    }
  }
}]);
