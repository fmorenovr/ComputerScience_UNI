package conf

import (
  "os";
  "mqttclient-go/models"
)

// print topic and playload
func PrintTopicPayload(topic string, payload []uint8){
  models.Logger.Info("Topic: %s\n", topic)
  models.Logger.Info("Payload:%s \n", payload)
}

// encrypt passwd
func Encrypt(s string) (result string) {
  for _,v := range s {
    result = string(v) + result
  }
  return result
}

// verify errors
func VerifyErr(err error){
  if err != nil {
    models.Logger.Error("%s",err)
    os.Exit(1)
  }
}

func LogServer(method, path, name string){
  models.Logger.Info("Started %s %s", method, path)
  models.Logger.Info("Executing BeaGons "+name+" Handler")
}

// verifica si exite un elemento en una lista
func StringInSlice(a string, list []string) (bool) {
  for _, b:= range list {
    if b==a {
      return true
    }
  }
  return false
}
