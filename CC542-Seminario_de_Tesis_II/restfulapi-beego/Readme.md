# RESTful API using Bee-Go Framework with Go language

Implementación de un rest API utilizando el lenguaje de programación Go, el driver para MongoDB de Go y el HTTP framework MVC BeeGo.

Este proyecto implementa un restful API consumida por [webAppClient-Go][webs-url], el cual actualiza información en tiempo real con la data recibida del broker [mqttClient-Go][mqtt-url].

# Requisitos

## Go language

Revisar [Golang](https://golang.org/dl/) para instalar Go language en tu maquina.

## BeeGo

WebFramework para el lenguaje Go, para mayor información consultar la web [Beego](http://beego.me/quickstart), instalar:

    go get github.com/astaxie/beego
    go get github.com/beego/bee

## Mango (mgo)

Driver de MongoDB para el lenguaje Go, para mayor información consultar la web de [mgo](https://labix.org/mgo), instalar:

    go get gopkg.in/mgo.v2
    go get gopkg.in/check.v1

## JWT

JWT means JSON Web Tokens.  
* First, Generate Key pairs:

    cd jwt/keys
    openssl genrsa -out rsakey.pem 2048
    openssl rsa -in rsakey.pem -pubout > rsakey.pem.pub

* You should download my library:

        go get github.com/jenazads/gojweto

### Otra referencia sobre golang (personal)

Revisar el repositorio [developConfig/Go](https://github.com/Jenazad/developConfig/tree/master/Go) para ver como instalar go language y demas drivers.

### Levantar el Restful API Web Services

    bee run

[rest-url]: https://bitbucket.org/Jenazads/restfulapi-beego
[mqtt-url]: https://bitbucket.org/Jenazads/mqttclient-go
[webs-url]: https://bitbucket.org/Jenazads/webappclient-go
