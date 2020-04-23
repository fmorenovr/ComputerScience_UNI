'use strict';

appControllers.controller('chartsModulesController', ['infoServices', '$scope', '$window', 'Consultas', 'MQTTWebClient', function(infoServices, $scope, $window, Consultas, MQTTWebClient) {
  var len;
  var brokerInfo = infoServices.broker
  var dataResponse = Consultas.setInit()
  if(!dataResponse.success){
    $window.location.href = dataResponse.url;
  } else {
    Consultas.getUsuarioHome(app.username).then(function(dataResponse){});
  }
  
  $scope.cansats = [];
  $scope.sensorestipo = [];

  $scope.tempShow = false;
  $scope.presionShow = false;
  $scope.dioxidoShow = false;
  $scope.monoxidoShow = false;
  
  $scope.numSens = 4;
  $scope.emptyData = false;
  
  $scope.graphicsOK = 0;

  $scope.tempColor     = '#F7653F';
  $scope.presionColor   = '#40FF00';
  $scope.dioxidoColor  = '#00BFFF';
  $scope.monoxidoColor = '#DBA901';

  Consultas.getInfoCansats(app.username).then(function(dataResponse){
    $scope.cansats = dataResponse;
  });

  Consultas.getTipoSensores().then(function(dataResponse){
    $scope.sensorestipo = dataResponse;
  });

  var id_cans, mqttclient, mqttoptions, local_clientMQTTPaho
  
  mqttclient = MQTTWebClient.NewWebAppClient(brokerInfo.clientIdFree, "", "#");
  mqttoptions = mqttclient[1];
  
  local_clientMQTTPaho = mqttclient[0];
  local_clientMQTTPaho.connect(mqttoptions);
  
  $scope.$watch('dispositivo', function() {
    if($scope.dispositivo != '' && $scope.dispositivo != undefined){
      id_cans = $scope.dispositivo;

      local_clientMQTTPaho.disconnect(); // desconecta
      
      mqttclient = MQTTWebClient.NewWebAppClient(brokerInfo.clientId, id_cans, "#");
      mqttoptions = mqttclient[1];
      
      local_clientMQTTPaho = mqttclient[0];
      
      $scope.mqttClientInitFunc(mqttoptions);
      
      $scope.resetData();
      $scope.DataSensorFill();
    }
  });

  $scope.DataSensorFill = function (){
    if ($scope.dispositivo !=''){
      angular.forEach($scope.cansats, function (value, key) {
        if (value.id_moduleiot == $scope.dispositivo) {
          angular.forEach(value.sensors, function (valuecansat, key) {
            $scope.sensores.push({id_sensor: valuecansat.id_sensor, tipo_sensor: valuecansat.type, unidad: valuecansat.unit, modelo: valuecansat.model});
          });
        }
      });
      angular.forEach($scope.sensorestipo, function (value, key) {
        Consultas.getDatosSensadosTS_D(value,$scope.dispositivo,"last").then(function(dataResponse){
          if(dataResponse != "Datos no existen"){
            $scope.sensoresdato = dataResponse;
            $scope.setDataSensorList(value,$scope.sensoresdato);
          } else {
            $scope.graphicsOK +=1;
            if($scope.graphicsOK == $scope.numSens){
              $scope.emptyData = true;
            } else {
              $scope.emptyData = false;
            }
          }
        });
      });
    }
  };
  
  $scope.resetData = function(){
    $scope.tempData = [];
    $scope.presionData = [];
    $scope.monoxidoData = [];
    $scope.dioxidoData = [];
    $scope.tempShow = false;
    $scope.presionShow = false;
    $scope.dioxidoShow = false;
    $scope.monoxidoShow = false;
    $scope.emptyData = false;
    $scope.sensores = [];
    $scope.sensoresdato = [];
    $scope.graphicsOK = 0;
  }
  
  $scope.mqttClientInitFunc = function(opciones){
    local_clientMQTTPaho.onMessageArrived = function (message) {
      console.log(message.destinationName);
      console.log(message.payloadString);
      var jsonString = JSON.stringify(message.payloadString);
      var obj = JSON.parse(message.payloadString);
      console.log('valor: '+obj.value+", id_moduleiot: "+obj.id_moduleiot + ", tipo: "+obj.type)
      $scope.updateDataSensorList(obj,id_cans);
    };
    local_clientMQTTPaho.connect(opciones);
  }
  
  $scope.updateDataSensorList = function(obj,idcans){
    if (obj.type == "Temperatura" && obj.id_moduleiot == idcans){
      $scope.tempData.push(obj)
      len = ($scope.tempData).length
      $scope.tempData = ($scope.tempData).subarray(len-10)
      $scope.setDataSensorList("Temperatura",$scope.tempData)
    } else if(obj.type == "Presion" && obj.id_moduleiot == idcans){
      $scope.presionData.push(obj)
      len = ($scope.presionData).length
      $scope.presionData = ($scope.presionData).subarray(len-10)
      $scope.setDataSensorList("Presion",$scope.presionData)
    } else if(obj.type == "Monoxido" && obj.id_moduleiot == idcans){
      $scope.monoxidoData.push(obj)
      len = ($scope.monoxidoData).length
      $scope.monoxidoData = ($scope.monoxidoData).subarray(len-10)
      $scope.setDataSensorList("Monoxido",$scope.monoxidoData)
    } else if(obj.type == "Dioxido" && obj.id_moduleiot == idcans){
      $scope.dioxidoData.push(obj)
      len = ($scope.dioxidoData).length
      $scope.dioxidoData = ($scope.dioxidoData).subarray(len-10)
      $scope.setDataSensorList("Dioxido",$scope.dioxidoData)
    }
  }
  
  $scope.setDataSensorList = function(value,datos){
    if(value == "Temperatura"){
      $scope.tempData = datos
      $scope.setChartD3(value,'#tempChart svg',$scope.tempData,$scope.tempColor);
      $scope.tempShow = true;
    } else if(value == "Presion"){
      $scope.presionData = datos
      $scope.setChartD3(value,'#presionChart svg',$scope.presionData,$scope.presionColor);
      $scope.presionShow = true;
    } else if(value == "Monoxido"){
      $scope.monoxidoData = datos
      $scope.setChartD3(value,'#monoxidoChart svg',$scope.monoxidoData,$scope.monoxidoColor);
      $scope.monoxidoShow = true;
    } else if(value == "Dioxido"){
      $scope.dioxidoData = datos
      $scope.setChartD3(value,'#dioxidoChart svg',$scope.dioxidoData,$scope.dioxidoColor);
      $scope.dioxidoShow = true;
    }
  }
  
  $scope.setChartD3 = function(value,divSVG,datos,colorval){
    nv.addGraph(function() {
      var chart = nv.models.lineChart()
          .useInteractiveGuideline(true)
          //.margin({left: 28, bottom: 30, right: 0})
          .showXAxis(true)
          .showYAxis(true);

      chart.xAxis
        .showMaxMin(true)
        .axisLabel('Fecha')
        .ticks(1000)
        .tickFormat(function(d) { return d3.time.format('%X %p')(new Date(d)) });
        //.tickFormat(d3.format(',r'));

      chart.yAxis
        .showMaxMin(true)
        .axisLabel(value)
        .ticks(0)
        .tickFormat(d3.format(',r'));

      d3.select(divSVG)
        .datum(app.setDatatoD3(value,datos,colorval))
        .transition().duration(500)
        .call(chart);

      nv.utils.windowResize(chart.update);
      return chart;
    });
  }
}]);
