'use strict';

appConstants.constant('infoServices',{
  rest: {
    port     : 6568,
    protocol : "http://",
    url      : "localhost",
    //url      : "beagons.uni.edu.pe",
  },
  broker: {
    port         : 1884,
    qos          : 0,
    protocol     : "WS",
    clientId     : "IdClient_WebApp",
    clientIdFree : "IdClient_WebAppFree",
    userWeb      : "Master",
    //userWeb      : "CTIC-SMARTCITY",
    url          : "localhost",
    //url          : "beagons.uni.edu.pe",
  },
  headerHTTP: {
    headers: {
      'Content-Type'     : 'application/x-www-form-urlencoded; charset=UTF-8;',
      'Accept'           : 'application/json;odata=verbose',
      'BeaGons-rest-JWT' : '',
    }
  },
  controllers: {
    users        : "users",
    login        : "login",
    modules      : "modules",
    sensors      : "sensors",
    usernames    : "usernames",
    sensorstype  : "sensorstype",
    datameasured : "datameasured",
  },
  namespaces: {
    webclient    : "Beagons",
    mobileclient : "BeagonsMobile"
  },
  urls: {
    login     : "#/login",
    dashboard : "#/"+app.webapp+"/home/"
  },
});

