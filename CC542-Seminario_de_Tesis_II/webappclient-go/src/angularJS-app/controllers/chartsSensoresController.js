'use strict';

appControllers.controller('chartsSensoresController',['infoServices', '$scope', '$window', 'Consultas', 'MQTTWebClient',function(infoServices, $scope, $window, Consultas, MQTTWebClient) {
  var len;
  var brokerInfo = infoServices.broker
  var dataResponse = Consultas.setInit()
  if(!dataResponse.success){
    $window.location.href = dataResponse.url;
  } else {
    Consultas.getUsuarioHome(app.username).then(function(dataResponse){});
  }
  
  $scope.sensorestipo = [];
  
  Consultas.getTipoSensores().then(function(dataResponse){
    $scope.sensorestipo = dataResponse;
  });
  
  $scope.dispositivo     = ""
  $scope.sensoresdato    = [];  
  $scope.dispositivos    = [];
  $scope.simpleData      = [];
  $scope.datos           = [];
  $scope.dataVector      = [];
  $scope.dispsensShow    = false;
  $scope.dispsensShowAll = false;
  $scope.emptyData       = false;

  var tipo, disp, mqttclient, mqttoptions, local_clientMQTTPaho
  
  mqttclient = MQTTWebClient.NewWebAppClient(brokerInfo.clientIdFree, "", "#");
  mqttoptions = mqttclient[1];
  
  local_clientMQTTPaho = mqttclient[0];
  local_clientMQTTPaho.connect(mqttoptions);
  
  // Buscamos los dispositivos que tiene un tipo de sensor especifico
  $scope.$watch('tipo_sensor', function() {
    $scope.resetData();
    $scope.dispositivo = ""
    Consultas.getTipoSensoresEspec($scope.tipo_sensor).then(function(dataResponse){
      $scope.dispositivos = dataResponse;
    });
  });

  $scope.$watch('dispositivo', function() {
    if($scope.dispositivo != '' && $scope.dispositivo != undefined){
      tipo = $scope.tipo_sensor;
      disp = (($scope.dispositivo == "todos")?'+' : $scope.dispositivo);
      if(disp == "+"){
      
      } else {
        local_clientMQTTPaho.disconnect(); // desconecta

        mqttclient = MQTTWebClient.NewWebAppClient(brokerInfo.clientId, disp, disp+'/'+tipo);
        mqttoptions = mqttclient[1];
        
        local_clientMQTTPaho = mqttclient[0];
        $scope.mqttClientInitFunc(mqttoptions);
      }
      $scope.resetData();
      $scope.DataSensorFill();
    }
  });

  $scope.DataSensorFill = function(){
    if ($scope.dispositivo !== '' && $scope.dispositivo !== 'todos' && $scope.tipo_sensor!==''){
      Consultas.getDatosSensadosTS_D($scope.tipo_sensor,$scope.dispositivo,"last").then(function(dataResponse){
        if(dataResponse !== "Datos no existen"){
          $scope.sensoresdato = dataResponse;
          $scope.simpleData = dataResponse;
          $scope.setDataSensorList($scope.tipo_sensor,$scope.simpleData,$scope.tipo_sensor);
          $scope.emptyData = false
        } else {
          $scope.emptyData = true
        }
      });
    }
    if ($scope.dispositivo == "todos" && $scope.tipo_sensor!==''){
      angular.forEach($scope.dispositivos, function (value, key) {
        Consultas.getDatosSensadosTS_D($scope.tipo_sensor,value.id_moduleiot,"last").then(function(dataResponse){
          if(dataResponse !== "Datos no existen"){
            $scope.sensoresdato = dataResponse;
            // recolectar datos
            $scope.datos = app.DataFill($scope.sensoresdato);
            $scope.dataVector.push({ values: $scope.datos, key: value.id_moduleiot, area: true});
            console.log($scope.dataVector)
          }
        });
      });
      $scope.setDataSensorListVector($scope.tipo_sensor,$scope.dataVector);
    }
  };
  
  $scope.resetData = function(){
    $scope.simpleData = [];
    $scope.dispsensShow = false;
    $scope.dispsensShowAll = false;
    $scope.emptyData = false;
    $scope.sensoresdato = [];
    $scope.dataVector = [];
    $scope.datos = [];
  }

  $scope.mqttClientInitFunc = function(opciones){
    local_clientMQTTPaho.onMessageArrived = function (message) {
      console.log(message.destinationName);
      console.log(message.payloadString);
      var jsonString = JSON.stringify(message.payloadString);
      var obj = JSON.parse(message.payloadString);
      console.log('valor: '+obj.value+", id_moduleiot: "+obj.id_moduleiot + ", tipo: "+obj.type)
      $scope.updateDataSensorList(obj,tipo,disp);
    };
    local_clientMQTTPaho.connect(opciones);
  }

  $scope.updateDataSensorList = function(obj,tipo, disp){
    if (obj.type == tipo && obj.id_moduleiot == disp){
      $scope.simpleData.push(obj)
      len = ($scope.simpleData).length
      $scope.simpleData = ($scope.simpleData).subarray(len-10)
      $scope.setDataSensorList(tipo,$scope.simpleData, tipo)
    } else if (obj.type == tipo && "+" == disp){
      $scope.dataVector = app.addDataVector(obj,$scope.dataVector);
      $scope.setDataSensorListVector(tipo,$scope.dataVector);
    }
  }
  
  $scope.setDataSensorList = function(value,datos,tipo){
    $scope.setChartD3(value,'#dispsensChart svg',datos, app.getColor(tipo));
    $scope.dispsensShow = true;
  }
  
  $scope.setDataSensorListVector = function(value,datos){
    $scope.setChartD3Vector(value,'#dispsensChartAll svg',datos);
    $scope.dispsensShowAll = true;
  }
  
  $scope.setChartD3Vector = function(value,divSVG,datos){
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
        .tickFormat(function(d) { return d3.time.format('%x - %X %p')(new Date(d)) });
        //.tickFormat(d3.format(',r'));

      chart.yAxis
        .showMaxMin(true)
        .axisLabel($scope.tipo_sensor)
        .ticks(0)
        .tickFormat(d3.format(',r'));

      d3.select(divSVG)
        .datum(datos)
        .transition().duration(500)
        .call(chart);

      nv.utils.windowResize(chart.update);
      return chart;
    });
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
