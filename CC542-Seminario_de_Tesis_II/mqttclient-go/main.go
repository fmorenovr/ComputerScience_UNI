package main

import (
  mqttservice "mqttclient-go/routers"
)

func main() {
  mqttservice.MqttClientServiceInit("HTTP","TCP")
}

