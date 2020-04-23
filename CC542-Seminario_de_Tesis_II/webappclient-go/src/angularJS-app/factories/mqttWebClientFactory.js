'use strict'

appFactories.factory('MQTTWebClient', [ 'infoServices','Consultas', function(infoServices, Consultas){
  var broker = infoServices.broker.protocol+infoServices.broker.url+":"+infoServices.broker.port+"/"
  var brokerInfo = infoServices.broker
  var factory = {
    dataResponse: null,
    mqttPublish: mqttPublish,
    mqttSubscribe: mqttSubscribe,
    NewWebAppClient: NewWebAppClient
  }
  return factory;

  function onSuccessConnect(){
    if(brokerInfo.protocol == "WS"){
      console.log("New WS Client on BeaGons! Mqtt Web Socket Service ...");
    } else if (brokerInfo == "WSS"){
      console.log('New WSS Client on BeaGons! Mqtt Web Socket Service ...');
    }
  }
  
  function onFailureConnect(message){
    console.log("Failed connection: " + message.errorMessage);
  }
  
  function onConnectionLostClient(response){
    console.log("Connection lost or disconnected: " + response.errorMessage);
  }
  
  function NewClientOptions(userClient){
    var options;
    if (userClient == '' && userClient == ""){
      options = {
        onFailure: onFailureConnect,
      }
    } else {
      options = {
        userName: userClient,
        password: app.Encrypt(userClient),
        onFailure: onFailureConnect,
      }
    }
    if(brokerInfo.protocol == "WS"){
      options.useSSL = false
    } else if (brokerInfo.protocol == "WSS"){
      options.useSSL = true
    }
    return options;
  }
  
  function NewWebAppClient(idClient, userClient, topic){
    var idClientAux = idClient + "_" + Math.random().toString(16).substr(2, 8);
    var client = new Paho.MQTT.Client(brokerInfo.url, brokerInfo.port, idClientAux)
    client.onConnectionLost = onConnectionLostClient
    
    var options = NewClientOptions(userClient)
    options.onSuccess = function (){
      onSuccessConnect()
      mqttSubscribe(client,topic);
    }
    
    return [client,options];
  }
  
  function mqttPublish(mqttClient, topic, payload) {
    var message = new Paho.MQTT.Message(payload);
    message.destinationName = topic;
    message.qos = brokerInfo.qos;
    mqttClient.send(message);
  }
  
  function mqttSubscribe(mqttClient, topic){
    mqttClient.subscribe(topic, {qos:brokerInfo.qos})
  }
  
  // a partir de aqui, matar
  
  function NewWebAppClient_1(method){
    if(method == "WS"){
      factory.dataResponse = mqtt.connect(broker);
    } else if (method == "WSS"){
      factory.dataResponse = mqtt.connect(sslOptions);
    }
    onConnect(method, "");
    return factory.dataResponse;
  }

  function newMQTTClientAuthModule(IdModule,topic){
    var options = {
      //clientId: "beagons_" + IdModule,// + "_" + Math.random().toString(16).substr(2, 8),
      username: IdModule,
      password: app.Encrypt(IdModule)
    }
    var client = mqtt.connect(broker,options);
    onConnect(options.clientId);
    console.log('subscribe at /'+IdModule+'/'+topic)
    factory.dataResponse = client;
    return factory.dataResponse;
  }
  
}]);
