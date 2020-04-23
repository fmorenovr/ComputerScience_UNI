var app = angular.module('cifradoApp', ['app.Controllers']);

var appControllers = angular.module('app.Controllers',[])

appControllers.controller('cifradoController', ['$scope',function($scope) {
  
  $scope.abcdario = 'abcdefghijklmnñopqrstuvwxyzáéíóúÁÉÍÓÚABCDEFGHIJKLMNÑOPQRSTUVWXYZ'
  $scope.messageKey = "keyword"
  
  $scope.messageDec = 2
  $scope.messageDes = 5
  
  $scope.mod = ($scope.abcdario).length
  
  $scope.cifrar = function(){
    $scope.cifrarMensaje()
  }
  
  var Strings = {};
  Strings.orEmpty = function( entity ) {
    return entity || "";
  };
  
  $scope.encrypt = function(letter){
    var Enx = ($scope.saltodec*(($scope.abcdario).indexOf(letter)) + $scope.saltodes) % $scope.mod
    return $scope.abcdario[Enx]
  }
  
  $scope.decrypt = function(letter){
    var Enx
    var resta = ((($scope.abcdario).indexOf(letter)) - $scope.saltodes)/$scope.saltodec
    if (resta >=0){
      Enx = (resta) % $scope.mod
    } else {
      Enx = (resta + $scope.mod) % $scope.mod
    }
    return $scope.abcdario[Enx]
  }
  
  $scope.cifrarMensaje = function(){
    if ($scope.messageEncrypt != "" && $scope.messageEncrypt != undefined){
      if ($scope.messageDec == "" || $scope.messageDec == undefined) {
        $scope.saltodec = 3
      } else {
        $scope.saltodec = parseInt($scope.messageDec)
      }
      if ($scope.messageDes == "" || $scope.messageDes == undefined) {
        $scope.saltodes = 5
      } else {
        $scope.saltodes = parseInt($scope.messageDes)
      }
      if ($scope.saltodes <0) {
        return
      }
      if ($scope.messageKey == "" || $scope.messageKey == undefined){
        return
      } else {
        $scope.key = $scope.messageKey
      }
      if ($scope.messageMethod == "" || $scope.messageMethod == undefined){
        return
      } else {
        $scope.method = $scope.messageMethod
      }
      var i, ln = ($scope.messageEncrypt).length
      var text = ""
      for (i = 0; i < ln; i++) {
        if($scope.messageEncrypt[i] == " "){
          text += " "
        } else if ($scope.messageEncrypt[i] == "\n"){
          text += "\n"
        }
        else {
          text += (($scope.method == "1") ? Strings.orEmpty($scope.encrypt($scope.messageEncrypt[i])) : Strings.orEmpty($scope.decrypt($scope.messageEncrypt[i])))
        }
      }
      $scope.messageDecrypt = text
      $scope.messageEncrypt = text
      console.log("cifrado :"+text)
    }
  }
}]);
