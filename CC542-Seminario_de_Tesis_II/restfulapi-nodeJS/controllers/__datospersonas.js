var config = require('../models/config')
var pgClient = config.pgClient

var datosPersonasPersonal = "dp.nombres, dp.apellido_paterno, dp.apellido_materno, concat(dp.nombres,' ', dp.apellido_paterno, ' ', dp.apellido_materno) as nombre_completo, dp.fecha_nacimiento, dp.email, dp.numero_documento, dp.tipo_documento, dp.estado_civil"

var resultJOINPersonales = "dato_personal dp";

var datosPersonasContacto = "dp.email, dp.telefono_fijo, dp.telefono_celular, concat(dp.direccion_tipo, ' ', dp.direccion_detalle, ' ', dp.distrito_residencia,' ', dp.provincia_residencia, ' ', dp.pais_residencia) as direccion"

var resultJOINContactos = "dato_personal dp"

var queryFindAllPersonasPersonales = 'select '+ datosPersonasPersonal+' from '+ resultJOINPersonales

var queryFindAllPersonasContactos = 'select '+ datosPersonasContacto+' from '+ resultJOINContactos

module.exports = function(app) {

  //GET - Return all padronrucs in the DB
  findAllPersonasPersonales = function(req, res, next) {
    res.header('Access-Control-Allow-Origin', '*');
    res.header('Access-Control-Allow-Methods', 'GET,PUT,POST,DELETE');
    res.header('Access-Control-Allow-Headers', 'X-Requested-With, Content-Type, X-Auth-Token, Origin, Authorization');
    console.log('method GET: /posgrado/datospersonas/personales/')
  	pgClient.any(queryFindAllPersonasPersonales+' limit 10')
    .then(function (data) {
      res.status(200)
        .json(data);
    })
    .catch(function (err) {
      return next(err);
    });
  };
  
  findbyNumberPersonasPersonales = function(req, res, next) {
    res.header('Access-Control-Allow-Origin', '*');
    res.header('Access-Control-Allow-Methods', 'GET,PUT,POST,DELETE');
    res.header('Access-Control-Allow-Headers', 'X-Requested-With, Content-Type, X-Auth-Token, Origin, Authorization');
    console.log('method GET: /posgrado/datospersonas/personales/'+req.params.number)
    if(req.params.number !="all"){
    	pgClient.any(queryFindAllPersonasPersonales+' limit $1', req.params.number)
      .then(function (data) {
        res.status(200)
          .json(data);
      })
      .catch(function (err) {
        return next(err);
      });
    } else {
      pgClient.any(queryFindAllPersonasPersonales)
      .then(function (data) {
        res.status(200)
          .json(data);
      })
      .catch(function (err) {
        return next(err);
      });
    }
  };


  //GET - Return a PadronRuc with number
  findByNamePersonasPersonales = function(req, res, next) {
    res.header('Access-Control-Allow-Origin', '*');
    res.header('Access-Control-Allow-Methods', 'GET,PUT,POST,DELETE');
    res.header('Access-Control-Allow-Headers', 'X-Requested-With, Content-Type, X-Auth-Token, Origin, Authorization');
    console.log('method GET: /posgrado/datospersonas/personal/'+req.params.name)
    pgClient.any(queryFindAllPersonasPersonales+' where upper(dp.email) = upper($1)', [ req.params.name ])
    .then(function (data) {
      res.status(200)
        .json(data);
    })
    .catch(function (err) {
      return next(err);
    });
  };
  
  findAllPersonasContactos = function(req, res, next) {
    res.header('Access-Control-Allow-Origin', '*');
    res.header('Access-Control-Allow-Methods', 'GET,PUT,POST,DELETE');
    res.header('Access-Control-Allow-Headers', 'X-Requested-With, Content-Type, X-Auth-Token, Origin, Authorization');
    console.log('method GET: /posgrado/datospersonas/contactos/')
  	pgClient.any(queryFindAllPersonasContactos+' limit 10')
    .then(function (data) {
      res.status(200)
        .json(data);
    })
    .catch(function (err) {
      return next(err);
    });
  };
  
  findbyNumberPersonasContactos = function(req, res, next) {
    res.header('Access-Control-Allow-Origin', '*');
    res.header('Access-Control-Allow-Methods', 'GET,PUT,POST,DELETE');
    res.header('Access-Control-Allow-Headers', 'X-Requested-With, Content-Type, X-Auth-Token, Origin, Authorization');
    console.log('method GET: /posgrado/datospersonas/contactos/'+req.params.number)
    if(req.params.number !="all"){
    	pgClient.any(queryFindAllPersonasContactos+' limit $1', req.params.number)
      .then(function (data) {
        res.status(200)
          .json(data);
      })
      .catch(function (err) {
        return next(err);
      });
    } else {
      pgClient.any(queryFindAllPersonasContactos)
      .then(function (data) {
        res.status(200)
          .json(data);
      })
      .catch(function (err) {
        return next(err);
      });
    }
  };
  
  //GET - Return a PadronRuc with number
  findByNamePersonasContactos = function(req, res, next) {
    res.header('Access-Control-Allow-Origin', '*');
    res.header('Access-Control-Allow-Methods', 'GET,PUT,POST,DELETE');
    res.header('Access-Control-Allow-Headers', 'X-Requested-With, Content-Type, X-Auth-Token, Origin, Authorization');
    console.log('method GET: /posgrado/datospersonas/contacto/'+req.params.name)
    pgClient.any(queryFindAllPersonasContactos+' where upper(dp.email) = upper($1)', [ req.params.name ])
    .then(function (data) {
      res.status(200)
        .json(data);
    })
    .catch(function (err) {
      return next(err);
    });
  };

  //Link routes and functions
  app.get('/posgrado/datospersonas/personales', findAllPersonasPersonales);
  app.get('/posgrado/datospersonas/personales/:number', findbyNumberPersonasPersonales);
  app.get('/posgrado/datospersonas/personal/:name', findByNamePersonasPersonales);
  
  app.get('/posgrado/datospersonas/contactos', findAllPersonasContactos);
  app.get('/posgrado/datospersonas/contactos/:number', findbyNumberPersonasContactos);
  app.get('/posgrado/datospersonas/contacto/:name', findByNamePersonasContactos);

}
