# MQTT Client Service using Go language

Implementación de un Mqtt client utilizando el lenguaje de programación Go.

Este proyecto implementa un cliente mqtt que envia data en tiempo real hacia el [restfulAPI-BeeGo][rest-url], el cual almacena información para luego ser consumida por [webAppClient-Go][webs-url].

# Requisitos

## Go language

Revisar [Golang](https://golang.org/dl/) para instalar Go language en tu maquina.

## MQTT Paho Golang

Driver del protocolo MQTT para golang, para mayor información revisar [Paho Golang](https://github.com/eclipse/paho.mqtt.golang), instalar:

    go get github.com/eclipse/paho.mqtt.golang

## Mango (mgo)

Driver de MongoDB para el lenguaje Go, para mayor información consultar la web de [mgo](https://labix.org/mgo), instalar:

    go get gopkg.in/mgo.v2
    go get gopkg.in/check.v1

### Otra referencia sobre golang (personal)

Revisar el repositorio [developConfig/Golang](https://github.com/Jenazad/developConfig/tree/master/Go) para ver como instalar go language y demas drivers.

### Preparando el TLS/SSL

Copiar los archivos en:

    bash smartech-ca.sh broker
    bash smartech-ca.sh client beagons-mqtt

    sudo cp ca.crt   /etc/mosquitto/ca_certificates
    sudo cp broker.* /etc/mosquitto/certs

### Levantar el Mqtt Client Service

    go run main.go

[rest-url]: https://bitbucket.org/Jenazads/restfulapi-beego
[mqtt-url]: https://bitbucket.org/Jenazads/mqttclientservice-go
[webs-url]: https://bitbucket.org/Jenazads/webappclient-go
