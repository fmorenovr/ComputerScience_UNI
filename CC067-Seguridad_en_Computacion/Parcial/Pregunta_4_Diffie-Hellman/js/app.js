var app = angular.module('cifradoApp', ['app.Controllers']);

var appControllers = angular.module('app.Controllers',[])

appControllers.controller('cifradoController', ['$scope',function($scope) {
  
  $scope.Prim = "179769313486231590770839156793787453197860296048756011706444423684197180216158519368947833795864925541502180565485980503646440548199239100050792877003355816639229553136239076508735759914822574862575007425302077447712589550957937778424442426617334727629299387668709205606050270810842907692932019128194467627007"
  //$scope.Prim = "ffffffffffffffffc90fdaa22168c234c4c6628b80dc1cd129024e088a67cc74020bbea63b139b22514a08798e3404ddef9519b3cd3a431b302b0a6df25f14374fe1356d6d51c245e485b576625e7ec6f44c42e9a637ed6b0bff5cb6f406b7edee386bfb5a899fa5ae9f24117c4b1fe649286651ece65381ffffffffffffffff"
  

  $scope.messageEncrypt = "Hola mi nombre es juan cachaporras y se que por ahi me andan diciendo que yo soy la muerte la destructora de mundos portadora de desastres y del caos inminente ... Ademas de eso, me llaman el demonio de la ciudad gris, sediento y hambriento"

  $scope.primo = bigInt($scope.Prim)
  $scope.Gen = "7"
  $scope.generador = bigInt($scope.Gen)
  $scope.X_a = "0"
  $scope.Xa = bigInt($scope.X_a)
  $scope.Y_a = "1"
  $scope.Ya = bigInt($scope.Y_a)
  $scope.Y_b = "1"
  $scope.Yb = bigInt($scope.Y_b)
  $scope.Y_s = "1"
  $scope.Ys = bigInt($scope.Y_s)
  $scope.X_s = "0"
  $scope.Xs = bigInt($scope.X_s)
  $scope.messageS = "0"
  $scope.S = bigInt($scope.messageS)
  
  var Strings = {};
  Strings.orEmpty = function( entity ) {
    return entity || "";
  };
  
  $scope.rc4Encrypt = function (key, str) {
    /* init */
	  var s = [], j = 0, x, res = '';
	  for (var i = 0; i < 256; i++) {
		  s[i] = i;
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
  
  var hex = 0, hexS = 0
  $scope.BaseS = function () {
    hexS = !hexS
    if (hexS) {
      console.log("Hexadecimal")
      $scope.Y_b = ($scope.Yb).toString(16)
      $scope.X_s = ($scope.Xs).toString(16)
      $scope.Y_s = ($scope.Ys).toString(16)
      $scope.messageS = ($scope.S).toString(16)
    }
    else {
      console.log("Decimal")
      $scope.Y_b = ($scope.Yb).toString()
      $scope.X_s = ($scope.Xs).toString()
      $scope.Y_s = ($scope.Ys).toString()
      $scope.messageS = ($scope.S).toString()
    }
  }
  $scope.initSDiffieHellman = function () {
    if ($scope.generador == undefined){
      $scope.generador = bigInt($scope.Gen)
    }
    if ($scope.primo == undefined){
      $scope.primo = bigInt($scope.Prim)
    }
    $scope.auxYb = bigInt($scope.Y_b,16).toString()
    $scope.Y_b = $scope.auxYb
    $scope.Yb = bigInt($scope.auxYb)
    //$scope.Yb = bigInt($scope.Y_b)
    $scope.Xs = bigInt($scope.X_s)
    $scope.S  = ($scope.Yb).modPow($scope.Xs,$scope.primo)
    $scope.messageS = ($scope.S).toString()
  }
  $scope.EncryptS = function () {
    $scope.initSDiffieHellman()
    console.log("#################################")
    console.log("Yb       : "+($scope.Yb).toString())
    console.log("Yb_h     : "+($scope.Yb).toString(16))
    console.log("Xs       : "+($scope.Xs).toString())
    console.log("Xs_h     : "+($scope.Xs).toString(16))
    $scope.Ys = ($scope.generador).modPow($scope.Xs,$scope.primo)
    $scope.Y_s = ($scope.Ys).toString()
    console.log("Ys       : "+($scope.Ys).toString())
    console.log("Ys_h     : "+($scope.Ys).toString(16))
    console.log("S        : "+($scope.S).toString())
    console.log("S_h      : "+($scope.S).toString(16))
  }
  
  $scope.Base = function () {
    hex = !hex
    if (hex) {
      console.log("Hexadecimal")
      $scope.Y_a = ($scope.Ya).toString(16)
      $scope.X_a = ($scope.Xa).toString(16)
      $scope.Gen = ($scope.generador).toString(16)
      $scope.Prim = ($scope.primo).toString(16)
    }
    else {
      console.log("Decimal")
      $scope.Y_a = ($scope.Ya).toString()
      $scope.X_a = ($scope.Xa).toString()
      $scope.Gen = ($scope.generador).toString()
      $scope.Prim = ($scope.primo).toString()
    }
  }
  $scope.initDiffieHellman = function () {
    if ($scope.Gen == undefined || $scope.Gen == ""){
      return
    }
    if ($scope.Prim == undefined || $scope.Prim == ""){
      return
    }
    $scope.generador = bigInt($scope.Gen)
    $scope.primo = bigInt($scope.Prim)
    $scope.Xa = bigInt($scope.X_a)
  }
  $scope.Encrypt = function () {
    $scope.initDiffieHellman()
    console.log("#################################")
    console.log("Primo    : "+($scope.primo).toString())
    console.log("Primo_h  : "+($scope.primo).toString(16))
    console.log("Gen      : "+($scope.generador).toString())
    console.log("Gen_h    : "+($scope.generador).toString(16))
    console.log("Xa       : "+($scope.Xa).toString())
    console.log("Xa_h     : "+($scope.Xa).toString(16))
    /*$scope.gxa = ($scope.generador).pow($scope.Xa)
    console.log("G^Xa     : "+($scope.gxa).toString())
    $scope.Ya = ($scope.gxa).mod($scope.primo)*/
    $scope.Ya = ($scope.generador).modPow($scope.Xa,$scope.primo)
    $scope.Y_a = ($scope.Ya).toString()
    console.log("Ya       : "+($scope.Ya).toString())
    console.log("Ya_h     : "+($scope.Ya).toString(16))
  }
  
  $scope.cifrar = function(){
    var lenS, messagLen, Stext = "", j=0, messageAux;
    if ($scope.messageMethod == "" || $scope.messageMethod == undefined){
      return;
    } else {
      $scope.method = $scope.messageMethod;
    }
    if ($scope.messageEncrypt == "" && $scope.messageEncrypt == undefined){
      return
    }
    console.log("#################################")
    console.log("Mensaje   : "+ $scope.messageEncrypt)
    if ($scope.method == "1") { // encrypt
      if ($scope.S == undefined || $scope.S == ""){
        return;
      }
      //$scope.S_encrypt = $scope.HexToString(($scope.S).toString(16))
      $scope.S_encrypt = ($scope.S).toString(16)
      lenS = ($scope.S_encrypt).length
      messageLen = ($scope.messageEncrypt).length
      for(var i =0; i < messageLen; i++){
        Stext += Strings.orEmpty($scope.S_encrypt[j])
        j +=1
        if(j==lenS){
          j=0
        }
      }
      messageAux = $scope.rc4Encrypt($scope.S_encrypt, $scope.messageEncrypt)
      $scope.messageDecrypt = $scope.StringToHex(messageAux)
      console.log("Cifrado   : "+ messageAux)
      console.log("Cifrado_h : "+ $scope.messageDecrypt)
    }
    if ($scope.method == "2") { // decrypt
      if($scope.Y_sdecrypt == undefined || $scope.Y_sdecrypt == ""){
        return
      }
      messageAux = $scope.HexToString($scope.messageEncrypt)
      $scope.auxYs_decrypt = bigInt($scope.Y_sdecrypt,16).toString()
      $scope.Ys_decrypt = bigInt($scope.auxYs_decrypt)
      console.log($scope.Ys_decrypt)
      $scope.S_decrypt = ($scope.Ys_decrypt).modPow($scope.Xa,$scope.primo)
      $scope.messageDecrypt = $scope.rc4Encrypt(($scope.S_decrypt).toString(16), messageAux)
      console.log("Cifrado   : "+ messageAux)
      console.log("Cifrado_h : "+ $scope.messageDecrypt)
    }
  }
}]);
