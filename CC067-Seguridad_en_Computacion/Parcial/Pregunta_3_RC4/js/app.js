var app = angular.module('cifradoApp', ['app.Controllers']);

var appControllers = angular.module('app.Controllers',[])

appControllers.controller('cifradoController', ['$scope',function($scope) {
  
  $scope.rc4Encrypt = function (key, str) {
    /* init */
	  var s = [], j = 0, x, res = '';
	  for (var i = 1025; i < (1025+256); i++) {
		  s[i-1025] = i;
	  }
	  for (i = 0; i < 256; i++) {
		  j = (j + s[i] + key.charCodeAt(i % key.length)) % 256;
		  /* swap */
		  x = s[i];
		  s[i] = s[j];
		  s[j] = x;
	  }
	  i = 0; j = 0;
	  for (var y = 0; y < str.length; y++) {
	  /* propagation */
		  i = (i + 1) % 256;
		  j = (j + s[i]) % 256;
		  x = s[i];
		  s[i] = s[j];
		  s[j] = x;
		  res += String.fromCharCode(str.charCodeAt(y) ^ s[(s[i] + s[j]) % 256]);
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
