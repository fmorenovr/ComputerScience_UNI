package conf

import (
	"os";
  "strings";
  "io/ioutil";
  "crypto/tls";
  "crypto/x509";
  "mqttclient-go/models";
  MQTT "github.com/eclipse/paho.mqtt.golang";
)

// id modules-alerts
var Idmodules = models.AllModuleRequest()
var Idalerts  = models.AllAlertRequest()
// TLS/SSL
var TlsMqttConfig = NewTLSMQTTConfig()

var callBackFunc MQTT.MessageHandler = func(client MQTT.Client, msg MQTT.Message) {
  wildcardsTopic := strings.Split(string(msg.Topic()),"/")
  if StringInSlice(wildcardsTopic[0], Idmodules){
    if wildcardsTopic[0] != FreeTopic {
      PrintTopicPayload(msg.Topic(), msg.Payload())
      go models.DataMeasuredAddRequest(msg)
      //modules := ModulesRequest(wildcardsTopic[0])
      //mqttPublishFreeData(modules, wildcardsTopic[1], msg)
    }
  }
  if StringInSlice(wildcardsTopic[0], Idalerts){
    if wildcardsTopic[0] != FreeTopic {
      PrintTopicPayload(msg.Topic(), msg.Payload())
      //go AlertMeasuredAddRequest(msg)
      //alerts := AlertsRequest(wildcardsTopic[0])
      //mqttPublishFreeAlert(alerts, wildcardsTopic[1], msg)
    }
  }
}

func mqttPublishFreeData(modules models.Module, topic string, msg MQTT.Message) {
  for i:=0; i<len(modules.Sensors);i++ {
    if modules.Sensors[i].State == "free" && modules.Sensors[i].Type == topic{
      topicFree := FreeTopic+"/data/"+msg.Topic()
      freeuser := NewCloudMasterClient( Idfreeclient, Freeclient)
      mensaje := string(msg.Payload())
      mqttPublish(freeuser, topicFree, mensaje)
      if Protocol == "TCP" {
        models.Logger.Info("Publicado en: %s\nmensaje: %s\n", topicFree, mensaje)
      } else if Protocol == "TCPS" {
        models.Logger.Info("Publicado con TLS/SSL en: %s\nmensaje: %s\n", topicFree, mensaje)
      }
    }
  }
}

func mqttPublishFreeAlert(alerts models.Alert, topic string, msg MQTT.Message) {
  /*
  for i:=0; i<len(alerts.Modules_associated);i++ {
    if alerts.Modules_associated[i].State == "free" && alerts.Modules_associated[i].Id_moduleiot == topic{
      topicFree := FreeTopic+"/alert/"+msg.Topic()
      freeuser := NewCloudMasterClient(idfreeclient,freeclient)
      mensaje := string(msg.Payload())
      mqttPublish(freeuser, topicFree, mensaje)
      if Protocol == "TCP" {
        models.Logger.Info("Publicado en: %s\nmensaje: %s\n", topicFree, mensaje)
      } else if Protocol == "TCPS" {
        models.Logger.Info("Publicado con TLS/SSL en: %s\nmensaje: %s\n", topicFree, mensaje)
      }
    }
  }
  */
}

func NewCloudMasterClient(Idclient string, userclient string) (*MQTT.ClientOptions) {
  cloudmaster := MQTT.NewClientOptions()
  if Protocol == "TCP" {
    cloudmaster.AddBroker("tcp://" + Ipbroker + ":" + Portbroker)
  } else if Protocol == "TCPS" {
    cloudmaster.SetTLSConfig(TlsMqttConfig)
    cloudmaster.AddBroker("tcps://" + Ipbroker + ":" + Portssl)
  }
  cloudmaster.SetClientID(Idclient).SetCleanSession(true)
  cloudmaster.SetUsername(userclient).SetPassword(Encrypt(userclient))
  return cloudmaster
}

func mqttPublish(user *MQTT.ClientOptions, topicFree string, mensaje string){
  client := MQTT.NewClient(user)
  if token := client.Connect(); token.Wait() && token.Error() != nil {
    models.Logger.Error("Error autentificacion %s",token.Error())
    panic(token.Error())
  }
  token := client.Publish(topicFree, Qos, false, mensaje)
  token.Wait()
  client.Disconnect(250)
}

func mqttSubscribe(user *MQTT.ClientOptions){
  client := MQTT.NewClient(user)
  if token := client.Connect(); token.Wait() && token.Error() != nil {
    models.Logger.Error("Error autentificacion %s",token.Error())
    panic(token.Error())
  }

  if token := client.Subscribe("#", Qos, callBackFunc); token.Wait() && token.Error() != nil {
    models.Logger.Error("Error de suscripcion en %s",token.Error())
    os.Exit(1)
  }
}

func NewTLSMQTTConfig() (*tls.Config) {
  // Import trusted certificates from ca certificate
  certpool := x509.NewCertPool()
  pemCerts, err := ioutil.ReadFile(MqttCaPath)
  if err == nil {
	  certpool.AppendCertsFromPEM(pemCerts)
  }
  // Import client certificate/key pair
  cert, err := tls.LoadX509KeyPair(MqttCrtPath, MqttKeyPath)
  VerifyErr(err)
  // Just to print out the client certificate..
  /*cert.Leaf, err = x509.ParseCertificate(cert.Certificate[0])
  if err != nil {
	  panic(err)
  }*/
  // Create tls.Config with desired tls properties
  return &tls.Config{
	  RootCAs: certpool,
	  // ClientAuth = whether to request cert from server.
	  // Since the server is set up for SSL, this happens
	  // anyways.
	  ClientAuth: tls.NoClientCert,
	  // ClientCAs = certs used to validate client cert.
	  ClientCAs: nil,
	  // InsecureSkipVerify = verify that cert contents
	  // match server. IP matches what is in cert etc.
	  InsecureSkipVerify: true,
	  // Certificates = list of certs client sends to server.
	  Certificates: []tls.Certificate{cert},
  }
}
