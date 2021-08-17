# TODO

Preparación del entorno

RASPBERRY - FOG NODE

## SSL/TLS

* Al crear, crear ca y certs, y tambien el de un cliente.

* mover ca.crt a /etc/mosquitto/ca_certificates y hostname.key, hostname.crt a /etc/mosquitto/certs

* copiar ca.crt en cafog.crt

* mover el cliente.crt, cliente.key y cafog.crt hacia /mqttclient-python/ssl-tls/fognode/

## Broker

* mosquitto.conf - Definir los puertos por donde se va a publicar (mqtt y ws).

* aclfile - Definir los usuarios y permisos para publicar en respectivos topicos

* passwd - Definir los usuarios

* añadir en el fichero `/etc/hosts` el nombre y el ip del cloud

## DB

* Traer y almacenar los datos del respectivo Fog y los modulos con stados de sus sensores.

* Almacenamiento cuando no haya wifi

* Una vez modificado la mini db, volver a generar una consulta para tener los datos estaticos y evaluar segun eso.

UBUNTU - CLOUD MASTER

## Rest

* Cuando haya modificacion de modulos, o sectores, se envia un MQTT hacia el fog node correspondiente con la información modificada segun el formato establecido.

* Al crear nuevo FogNode, crear nuevo mqtt client, crearle credenciales de cliente certs, copiar ca.crt en cacloud.crt y enviarselos al fognode (podria ser mediante scp a la carpeta /ssl-tls/cloudmaster/).

* Reiniciar el servicio mosquitto

* Añadir en el fichero `/etc/hosts` el nombre y el ip del fog

## webApp

* configurar para aceptar WSS.

