var app = angular.module('cifradoApp', ['app.Controllers']);

var appControllers = angular.module('app.Controllers',[])

appControllers.controller('cifradoController', ['$scope',function($scope) {
  $scope.mod = 100
  $scope.cifrar = function(){
    $scope.cifrarMensaje()
  }
  
  var Strings = {};
  Strings.orEmpty = function( entity ) {
    return entity || "";
  };
  
  $scope.verifyEnter = function(enter){
    if(enter == '\r')
      enter = '\n'
    return enter
  }
  $scope.verifyEnterTxt = function(txt){
    var i=0,ln = txt.length
    for(i=0;i<ln;i++){
      txt[i] = $scope.verifyEnter(txt[i])
    }
    return txt
  }
  
  $scope.generarChars = function(messageEncrypt, wordKey){
    var total_len = (messageEncrypt).length
    var semi_len  = (wordKey).length
    var i=0, j=0, count=0
    var S_generado = ""
    var aux = ""
    for(i=0; i < semi_len; i++){
      S_generado += Strings.orEmpty(wordKey[i])
    }
    for(i=semi_len; i < total_len; i=i+semi_len){
      for(j=count;j < semi_len+count; j++){
        if(j==semi_len+count-1){
          aux += Strings.orEmpty(String.fromCharCode(((S_generado[j]).charCodeAt())%$scope.mod))
        } else {
          aux += Strings.orEmpty(String.fromCharCode(((S_generado[j]).charCodeAt() + (S_generado[j+1]).charCodeAt())%$scope.mod))
        }
      }
      S_generado = S_generado.concat(Strings.orEmpty(aux))
      count += semi_len
      aux = ""
    }
    return S_generado
  }
  
  $scope.cifrarMensaje = function(){
    var xor_encrypt, S_generado
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
      var wd_ln = ($scope.wordkey).length
      
      if(wd_ln > ln){
        return ""
      }
      if($scope.method == "1"){
        S_generado = $scope.generarChars($scope.messageEncrypt, $scope.wordkey)
        console.log(S_generado)
        if (S_generado == ""){
          return
        }
        for (i = 0; i < ln; i++) {
          xor_encrypt = (($scope.messageEncrypt[i]).charCodeAt()) ^ (S_generado[i].charCodeAt())
          text += Strings.orEmpty(String.fromCharCode(xor_encrypt))
        }
      }
      else if($scope.method == "2"){
        for (i = 0; i < ln; i++) {
          xor_encrypt = (($scope.messageEncrypt[i]).charCodeAt()) ^ ($scope.wordkey[j].charCodeAt())
          text += Strings.orEmpty(String.fromCharCode(xor_encrypt))
          j +=1
          if(j==wd_ln){
            j=0
          }
        }
      }
      $scope.messageDecrypt = text
      console.log(text)
    }
  }
}]);
