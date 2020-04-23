var app = angular.module('cifradoApp', ['app.Controllers']);

var appControllers = angular.module('app.Controllers',[])

appControllers.controller('cifradoController', ['$scope',function($scope) {
  
  $scope.messageEncrypt = "Hola mi nombre es juan cachaporras y se que por ahi me andan diciendo que yo soy la muerte la destructora de mundos portadora de desastres y del caos inminente ... Ademas de eso, me llaman el demonio de la ciudad gris, sediento y hambriento"
  
  /* swap */
  $scope.swap = function(s,i,j){
    var x;
    x = s[i];
	  s[i] = s[j];
	  s[j] = x;
	  return s
  }
  
  /* Key Scheduling Algorithm */
  $scope.rc4_init = function(key){
    var s = [], j = 0;
	  for (var i = 0; i < 256; i++) {
		  s[i] = i;
	  }
	  for (i = 0; i < 256; i++) {
		  j = (j + s[i] + key.charCodeAt(i % key.length)) % 256;
		  s = $scope.swap(s,i,j)
	  }
	  i = 0; j = 0;
	  return [s,i,j]
  }
  
  /* Pseudo-Random Generation Algorithm  */
  $scope.rc4_output = function(s,i,j){
    var ss;
    i = (i + 1) % 256;
    j = (j + s[i]) % 256;
    s = $scope.swap(s,i,j)
    ss = s[(s[i] + s[j]) % 256]
    return [s,ss,i,j]
  }
  
  $scope.rc4Encrypt = function (key, str) {
    var res = '', RC4;
	  RC4 = $scope.rc4_init(key)
	  s = RC4[0]
	  i = RC4[1]
	  j = RC4[2]
	  for (var y = 0; y < str.length; y++) {
	    if(y%256==0){
	      RC4 = $scope.rc4_init(res.substring(res.length-16))
	      s = RC4[0]
	      i = RC4[1]
	      j = RC4[2]
	    }
      SS = $scope.rc4_output(s,i,j)
      s = SS[0]
      i = SS[2]
      j = SS[3]
		  res += String.fromCharCode(str.charCodeAt(y) ^ SS[1]);
	  }
	  return res;
  }
  
  $scope.StringToHex = function (str){
    var hex = '';
    var temp;
    for (var n = 0; n < str.length; n ++) {
      temp = str.charCodeAt(n);
      if(temp.toString(16).length<2) temp = '0'+temp.toString(16);
      hex += temp.toString(16);
    }
    return hex;
  }
  
  $scope.HexToString = function (hex) {
    var str = '';
    for (var i = 0; i < hex.length; i += 2) {
      var v = parseInt(hex.substr(i, 2), 16);
      if (v) str += String.fromCharCode(v);
    }
    return str;
  }
  
  $scope.key = ""
  
  $scope.cifrar = function(){
    $scope.cifrarMensaje()
  }
  
  $scope.cifrarMensaje = function(){
    if ($scope.messageEncrypt != "" && $scope.messageEncrypt != undefined){
      if ($scope.messageKey == "" || $scope.messageKey == undefined) {
        $scope.key = "Meow"
      } else {
        $scope.key = $scope.messageKey
      }
      if ($scope.messageMethod == "" || $scope.messageMethod == undefined){
        return
      } else {
        $scope.method = $scope.messageMethod
      }
      console.log("#############")
      console.log("mensaje:   "+$scope.messageEncrypt)
      if ($scope.method == "1"){ //encrypt
        $scope.messageDecrypt = $scope.StringToHex($scope.rc4Encrypt($scope.key, $scope.messageEncrypt))
        console.log("mensaje_h: "+$scope.StringToHex($scope.messageEncrypt))
        console.log("cifrado:   "+$scope.HexToString($scope.messageDecrypt))
        console.log("cifrado_h: "+$scope.messageDecrypt)
      } else if ($scope.method == "2"){ // decrypt
        $scope.messageDecrypt = $scope.rc4Encrypt($scope.key, $scope.HexToString($scope.messageEncrypt))
        console.log("mensaje_h: "+$scope.HexToString($scope.messageEncrypt))
        console.log("cifrado:   "+$scope.messageDecrypt)
        console.log("cifrado_h: "+$scope.StringToHex($scope.messageDecrypt))
      }
    }
  }
}]);
