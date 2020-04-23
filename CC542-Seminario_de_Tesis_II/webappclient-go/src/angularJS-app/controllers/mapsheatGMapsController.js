'use strict';

appControllers.controller('heatGMapsController',['infoServices', '$scope','$timeout', '$window','Consultas', 'MQTTWebClient' ,function(infoServices, $scope, $window, $timeout, Consultas, MQTTWebClient) {

  var brokerInfo = infoServices.broker
  var dataResponse = Consultas.setInit()
  if(!dataResponse.success){
    $window.location.href = dataResponse.url;
  } else {
    Consultas.getUsuarioHome(app.username).then(function(dataResponse){});
  }

  app.colorBar(3)
  $scope.sensorestipo = [];
  $scope.heightBar = 346;
  $scope.widthBar = 26;
  $scope.borderBar = 3;
  
  var i, r = 15, numVer = 6; // 5 puntos distanciados 10 metros del centro
  var positionCansat = [];    // obtiene las posiciones de los cansats de cada tipo sensor
  var poligonosCreados = [];  // poligonos creados por cada tipo sensor
  var map = new GMaps({
    el: '#heatmap',
    lat: -12.0166427,
    lng: -77.0499641,
    zoom: 17,
    mapTypeId: 'satellite',
    zoomControl : false,
    panControl : false,
    streetViewControl : false,
    mapTypeControl: false,
    overviewMapControl: false
  });
  
  Consultas.getTipoSensores().then(function(dataResponse){
    $scope.sensorestipo = dataResponse;
  });

  var tipo, create, mqttclient, mqttoptions, local_clientMQTTPaho
  
  mqttclient = MQTTWebClient.NewWebAppClient(brokerInfo.clientIdFree, "", "#");
  mqttoptions = mqttclient[1];
  
  local_clientMQTTPaho = mqttclient[0];
  local_clientMQTTPaho.connect(mqttoptions);
  
  $scope.resetData = function(){
    map.removePolygons();
    map.removeMarkers();
    positionCansat = [];
    poligonosCreados = [];
    create = false;
  }
  
  $scope.$watch('tipo_sensor', function() {
    if ($scope.tipo_sensor!="" && $scope.tipo_sensor!=undefined){
      tipo = $scope.tipo_sensor;
      
      local_clientMQTTPaho.disconnect(); // desconecta
      
      mqttclient = MQTTWebClient.NewWebAppClient(brokerInfo.clientId, brokerInfo.userWeb, "+/"+String(tipo));
      mqttoptions = mqttclient[1];
      
      local_clientMQTTPaho = mqttclient[0];
      
      $scope.mqttClientInitFunc(mqttoptions);
      
      $scope.resetData();
      
      Consultas.setHeatMapsPos($scope.tipo_sensor).then(function(dataResponse){
        angular.forEach(dataResponse, function (value, key) {
          positionCansat.push({id: value.id, lat: value.lat, lon: value.lon, id: value.id, sensores: value.sensores, sector:value.sector, zona:value.zona, polygonos: value.polygonos});
        });
        for(i=0; i<positionCansat.length;i++){
          var path = []
          angular.forEach(positionCansat[i].polygonos, function (valuepol, key) {
            path.push([ valuepol.latitude, valuepol.longuitude ])
          });
          var auxSensores = "";
          var contentString,contentSensores;
          var indicador = app.getIndicadorValor(14, ($scope.tipo_sensor))
          var colors = app.getColorPolygon(indicador)

          angular.forEach(positionCansat[i].sensores, function (valuesens, key) {
            auxSensores = auxSensores + '<li>'+valuesens.type+'</li>';
          });
          contentSensores = '<ul>'+auxSensores + '</ul>';
          contentString = '<div>'+
            '<b>IoTDevice</b><br>'+
            'Id: '+positionCansat[i].id+'<br/>'+
            'Lat: '+positionCansat[i].lat+'<br/>'+
            'Lon: '+positionCansat[i].lon+'<br/>'+
            'Zone: '+positionCansat[i].zona+'<br/>'+
            'Sector: '+positionCansat[i].sector+'<br/>'+
            'Lista de sensores: <br/>'+
            contentSensores +
            '</div>';
          var poliactual = map.drawPolygon({
            paths: path,
            strokeColor: colors.strokec,
            strokeOpacity: 0.5,
            strokeWeight: 5,
            fillColor: colors.fillc,
            fillOpacity: 0.5
          });
          var markactual = map.addMarker({
            lat: positionCansat[i].lat,
            lng: positionCansat[i].lon,
            animation: google.maps.Animation.DROP,
            draggable: false,
            title: positionCansat[i].id,
            click: function(e) {
            },
            infoWindow: {
              content: contentString
            }
          });
          poligonosCreados.push({id_moduleiot: positionCansat[i].id, tipo: $scope.tipo_sensor,poli: poliactual, lat: positionCansat[i].lat, lon: positionCansat[i].lon, path: path})
        }
        create = true;
      });
    }
  });
  
  $scope.mqttClientInitFunc = function(opciones){
    local_clientMQTTPaho.onMessageArrived = function (message) {
      console.log(message.destinationName);
      console.log(message.payloadString);
      var jsonString = JSON.stringify(message.payloadString);
      var obj = JSON.parse(message.payloadString);
      console.log('valor: '+obj.value+", id_moduleiot: "+obj.id_moduleiot + ", tipo: "+obj.type)
      if(($scope.tipo_sensor)==obj.type && create){
        $scope.addPoligono(poligonosCreados,obj);
      }
    };
    local_clientMQTTPaho.connect(opciones);
  }
  
  $scope.addPoligono = function(polis, obj){
    var indica = app.getIndicadorValor(obj.value, obj.type)
    var col = app.getColorPolygon(indica)
    var leng = polis.length
    var index
    for(i=0;i<leng;i++){
      if(obj.id_moduleiot == polis[i].id_moduleiot){
        index = i;
        break;
      }
    }
    if(polis[index] != undefined){
      map.removePolygon(polis[index].poli)
      var polig = map.drawPolygon({
        paths: polis[index].path,
        strokeColor: col.strokec,
        strokeOpacity: 0.5,
        strokeWeight: 5,
        fillColor: col.fillc,
        fillOpacity: 0.5
      });
      polis[index].poli= polig
    }
  }
}]);
