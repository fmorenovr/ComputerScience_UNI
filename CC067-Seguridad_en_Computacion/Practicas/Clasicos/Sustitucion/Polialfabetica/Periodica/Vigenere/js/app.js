var app = angular.module('cifradoApp', ['app.Controllers']);

var appControllers = angular.module('app.Controllers',[])

appControllers.controller('cifradoController', ['$scope',function($scope) {
  
  $scope.abcdario = 'abcdefghijklmnñopqrstuvwxyzáéíóúÁÉÍÓÚABCDEFGHIJKLMNÑOPQRSTUVWXYZ'
  
  $scope.mod = ($scope.abcdario).length
  
  $scope.cifrar = function(){
    $scope.cifrarMensaje()
  }
  
  var Strings = {};
  Strings.orEmpty = function( entity ) {
    return entity || "";
  };
  
  $scope.encrypt = function(letter, lttr){
    var Enx = (($scope.abcdario).indexOf(letter) + ($scope.abcdario).indexOf(lttr)) % $scope.mod
    return $scope.abcdario[Enx]
  }
  
  $scope.decrypt = function(letter, lttr){
    var Enx
    var resta = ($scope.abcdario).indexOf(letter) - ($scope.abcdario).indexOf(lttr)
    if (resta >=0){
      Enx = (resta) % $scope.mod
    } else {
      Enx = (resta + $scope.mod) % $scope.mod
    }
    return $scope.abcdario[Enx]
  }
  
  $scope.cifrarMensaje = function(){
    if ($scope.messageEncrypt != "" && $scope.messageEncrypt != undefined){
      if ($scope.messageKey == "" || $scope.messageKey == undefined) {
        $scope.wordkey = "Meow"
      } else {
        $scope.wordkey = $scope.messageKey
      }
      if ($scope.messageMethod == "" || $scope.messageMethod == undefined){
        return
      } else {
        $scope.method = $scope.messageMethod
      }
      var i, j=0, ln = ($scope.messageEncrypt).length
      var text = ""
      for (i = 0; i < ln; i++) {
        if($scope.messageEncrypt[i] == " "){
          text += " "
        } else if ($scope.messageEncrypt[i] == "\n"){
          text += "\n"
        }
        else {
          text += (($scope.method == "1") ? Strings.orEmpty($scope.encrypt($scope.messageEncrypt[i],$scope.wordkey[j])) : Strings.orEmpty($scope.decrypt($scope.messageEncrypt[i],$scope.wordkey[j])))
          j +=1
        }
        if(j==($scope.wordkey).length){
          j=0
        }
      }
      $scope.messageDecrypt = text
      console.log("cifrado :"+text)
    }
  }
    
  // paris vaut bien une messe
  // loup
  // aolxd juje pcty iht xsmhp
}]);
