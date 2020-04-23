# RESTful API using NodeJS with Javascript

Implementación de un rest API utilizando el lenguaje de programación Javascript, el driver para MongoDB de Go y el Express framework.

Este proyecto implementa un restful API consumida en NodeJS.

# Requisitos

## NodeJS language

Interprete de codigo javascript, además tambien instalará npm.

    curl -sL https://deb.nodesource.com/setup_6.x -o nodesource_setup.sh
    nano nodesource_setup.sh 
    sudo bash nodesource_setup.sh 
    sudo apt-get install nodejs
    sudo apt-get install npm
    sudo npm install -g bower

## Mongo driver

Sirve para las conexiones a una base de datos MongoDB

    npm install mongodb --save 

## Mongo Instance interact

Sirve para interactar con la DB

    npm install mongoose --save
    
## body parser

Sirve para que pueda leer informacion desde los templates

    npm install body-parser --save

## ExpressJS

Libreria que proporciona aplicaciones Server-Side en javascript.

    npm install express --save

## nodemon

Sirve para que cada vez que modifiquemos un archivo, se actualice

    npm install nodemon --save-dev

ejecutar:

    ./node_modules/.bin/nodemon server.js

Nota:  
Una manera rápida de hacerlo, es usando el `package.json`.

    npm install

## PostgreSQL

    npm install pg-promise@5 --save

## import db mongoDB

    mongoimport --db dbname --collection colname --file outputfile

## run forever

    sudo npm install -g forever
    forever start main.js &

### Levantar el Restful API Web Services

    node main.js

