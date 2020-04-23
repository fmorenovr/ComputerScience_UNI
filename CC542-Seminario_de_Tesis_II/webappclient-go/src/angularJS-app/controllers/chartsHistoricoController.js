'use strict';

appControllers.controller('chartsHistoricoController',['$scope', '$window', 'Consultas', function($scope, $window, Consultas) {
  
  var dataResponse = Consultas.setInit()
  if(!dataResponse.success){
    $window.location.href = dataResponse.url;
  } else {
    Consultas.getUsuarioHome(app.username).then(function(dataResponse){});
  }
  
  $scope.cansats = [];
  $scope.sensorestipo = [];

  $scope.tempShow     = false;
  $scope.presionShow  = false;
  $scope.dioxidoShow  = false;
  $scope.monoxidoShow = false;
  $scope.numSens      = 4;
  
  $scope.emptyData    = false;

  $scope.tempColor     = '#F7653F';
  $scope.presionColor   = '#40FF00';
  $scope.dioxidoColor  = '#00BFFF';
  $scope.monoxidoColor = '#DBA901';
  
  $scope.graphicsOK = 0;

  $scope.ultimos = false;
  $scope.dias = false;
  $scope.horas = false;
  
  $scope.horas = app.time_hours;

  $scope.dispositivo = '';
  $scope.ultimodato = '';
  $scope.diaInicial = '';
  $scope.diaFinal = '';
  $scope.horaInicial = '';
  $scope.horaFinal = '';

  Consultas.getInfoCansats(app.username).then(function(dataResponse){
    $scope.cansats = dataResponse;
  });
    
  Consultas.getTipoSensores().then(function(dataResponse){
    $scope.sensorestipo = dataResponse;
  });

  $scope.$watch('diaInicial', function() {
    console.log($scope.diaInicial)
  });
  
  $scope.$watch('diaFinal', function() {
    console.log($scope.diaFinal)
  });
  
  $scope.$watch('horaInicial', function() {
    console.log($scope.horaInicial)
  });
  
  $scope.$watch('horaFinal', function() {
    console.log($scope.horaFinal)
  });

  $scope.$watch('ultimodato', function() {
    $scope.graphicsOK = 0;
    $scope.tempShow = false;
    $scope.presionShow = false;
    $scope.dioxidoShow = false;
    $scope.monoxidoShow = false;
    $scope.emptyData    = false;
    if($scope.diaInicial == "" && $scope.diaFinal == "" && $scope.horaInicial == "" && $scope.horaFinal == ""){
      $scope.DataSensorFillLastNumber();
    } else if ($scope.diaInicial != "" && $scope.diaFinal != "" && $scope.horaInicial == "" && $scope.horaFinal == ""){
      $scope.DataSensorFillDates();
    } else if ($scope.diaInicial != "" && $scope.diaFinal != "" && $scope.horaInicial != "" && $scope.horaFinal != ""){
      $scope.DataSensorFillHours();
    }
  });

  $scope.$watch('dispositivo', function() {
    $scope.resetData();
  });
  
  $scope.DataSensorFillDates = function (){
    if ($scope.dispositivo !=''){
      var auxdin = $scope.diaInicial.split("/")//$scope.diaInicial.replace(/[/]/g,"-")
      var auxdfn = $scope.diaFinal.split("/")//$scope.diaFinal.replace(/[/]/g,"-")
      var dIn = auxdin[2] + '-' + auxdin[0] + '-' + auxdin[1]
      var dFn = auxdfn[2] + '-' + auxdfn[0] + '-' + auxdfn[1]
      angular.forEach($scope.sensorestipo, function (value, key) {
        Consultas.getDatosSensadosTS_Dates(value,$scope.dispositivo,dIn,dFn,$scope.ultimodato).then(function(dataResponse){
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
  }
  
  $scope.DataSensorFillHours = function (){
    if ($scope.dispositivo !=''){
      var auxdin = $scope.diaInicial.split("/")//$scope.diaInicial.replace(/[/]/g,"-")
      var auxdfn = $scope.diaFinal.split("/")//$scope.diaFinal.replace(/[/]/g,"-")
      var dIn = auxdin[2] + '-' + auxdin[0] + '-' + auxdin[1]
      var dFn = auxdfn[2] + '-' + auxdfn[0] + '-' + auxdfn[1]
      angular.forEach($scope.sensorestipo, function (value, key) {
        Consultas.getDatosSensadosTS_Hours(value,$scope.dispositivo,dIn,dFn,$scope.horaInicial,$scope.horaFinal,$scope.ultimodato).then(function(dataResponse){
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
  }
  
  $scope.DataSensorFillLastNumber = function (){
    if ($scope.dispositivo !=''){
      angular.forEach($scope.sensorestipo, function (value, key) {
        Consultas.getDatosSensadosTS_D(value,$scope.dispositivo,$scope.ultimodato).then(function(dataResponse){
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
    $scope.emptyData    = false;
    $scope.sensores = [];
    $scope.sensoresdato = [];
    $scope.graphicsOK = 0;
  }
  
  $scope.setDataSensorList = function(value,datos){
    if(value == "Temperatura"){
      $scope.tempData = datos
      $scope.setChartD3(value,'#tempChartHistorico svg',$scope.tempData,$scope.tempColor);
      $scope.tempShow = true;
    } else if(value == "Presion"){
      $scope.presionData = datos
      $scope.setChartD3(value,'#presionChartHistorico svg',$scope.presionData,$scope.presionColor);
      $scope.presionShow = true;
    } else if(value == "Monoxido"){
      $scope.monoxidoData = datos
      $scope.setChartD3(value,'#monoxidoChartHistorico svg',$scope.monoxidoData,$scope.monoxidoColor);
      $scope.monoxidoShow = true;
    } else if(value == "Dioxido"){
      $scope.dioxidoData = datos
      $scope.setChartD3(value,'#dioxidoChartHistorico svg',$scope.dioxidoData,$scope.dioxidoColor);
      $scope.dioxidoShow = true;
    }
  }
  
  $scope.setChartD3 = function(value,divSVG,datos,colorval){
    nv.addGraph(function() {
      var chart = nv.models.multiBarChart()
          //.useInteractiveGuideline(true)
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
  
  var $input = $('#clockInit').clockpicker({
    default:          'now',
    placement:        'bottom', 
    align:            'left',
    donetext:         'Listo',
    autoclose:        true,
    vibrate:          true,
    fromnow:          0,
  });
  var $last = $('#clockFinal').clockpicker({
    default:          'now',
    placement:        'bottom', 
    align:            'left',
    donetext:         'Listo',
    autoclose:        true,
    vibrate:          true,
    fromnow:          0,
  });
  $("#datepickerInit").datepicker();  
  $("#datepickerFin").datepicker();
}]);
