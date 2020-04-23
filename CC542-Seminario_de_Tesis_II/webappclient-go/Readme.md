# Web Application Client using Go language

Implementación de un Web Client utilizando el lenguaje de programación Go y el framework MVW AngularJS.

Este proyecto implementa un cliente web que consume información de [restfulAPI-BeeGo][rest-url], el cual almacena data que recibe en tiempo real del broker [mqttClient-Go][mqtt-url]

# Requisitos

## Go language

Revisar [Golang](https://golang.org/dl/) para instalar Go language en tu maquina.

### Gorilla

Gorilla es un framework Web para Go. Puedes ver la doc oficial apretando [aqui](http://www.gorillatoolkit.org/).  

    go get github.com/gorilla/mux

## Gomail

Libreria SMTP para envio de mensajeria con emisor gmail, para mayor información revisar [GoMail](https://godoc.org/gopkg.in/gomail.v2).

    go get gopkg.in/gomail.v2

## Httpscerts

First, creates keys and crts using `smartech-ca.sh` script.

    bash smartech-ca.sh beagons-web
    mv ca.crt beagons-ca.crt
    cp beagons-web.key beagons-rest.key
    cp beagons-web.crt beagons-rest.crt

Luego mover los beagons-rest.* hacia la carpeta del servicio rest.

### Otra referencia sobre golang (personal)

Revisar el repositorio [developConfig/Golang](https://github.com/Jenazad/developConfig/tree/master/Go) para ver como instalar go language y demas drivers.

### Levantar el Web Application Client

    go build main.go
    sudo ./main

[rest-url]: https://bitbucket.org/Jenazads/restfulapi-beego
[mqtt-url]: https://bitbucket.org/Jenazads/mqttclient-go
[webs-url]: https://bitbucket.org/Jenazads/webappclient-go
