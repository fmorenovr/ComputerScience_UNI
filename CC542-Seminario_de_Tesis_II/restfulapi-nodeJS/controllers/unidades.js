var config = require('../models/config')
var pgClient = config.pgClient

var datosUnidades = "u.codigo, u.responsable, u.nombre, u.abreviatura, u.descripcion, u.tipo, u.tipo, u.direccion, u.anexo, u.email, u.website"

var datosInstitucion = "i.nombre as nombre_institucion"

var datosQuery = datosUnidades+', '+datosInstitucion

var resultJOIN = "unidad u inner join institucion i on u.id_institucion = i.id";

var queryFindAllProgramas = 'select '+datosQuery+' from '+resultJOIN;

module.exports = function(app) {

  //GET - Return all padronrucs in the DB
  findAllUnidades = function(req, res, next) {
    res.header('Access-Control-Allow-Origin', '*');
    res.header('Access-Control-Allow-Methods', 'GET,PUT,POST,DELETE');
    res.header('Access-Control-Allow-Headers', 'X-Requested-With, Content-Type, X-Auth-Token, Origin, Authorization');
    console.log('method GET: /posgrado/unidades')
  	pgClient.any(queryFindAllProgramas+' limit 10')
    .then(function (data) {
      res.status(200)
        .json(data);
    })
    .catch(function (err) {
      return next(err);
    });
  };
  
  findbyNumberUnidades = function(req, res, next) {
    res.header('Access-Control-Allow-Origin', '*');
    res.header('Access-Control-Allow-Methods', 'GET,PUT,POST,DELETE');
    res.header('Access-Control-Allow-Headers', 'X-Requested-With, Content-Type, X-Auth-Token, Origin, Authorization');
    console.log('method GET: /posgrado/unidades/'+req.params.number)
    if(req.params.number !="all"){
    	pgClient.any(queryFindAllProgramas+' limit $1', req.params.number)
      .then(function (data) {
        res.status(200)
          .json(data);
      })
      .catch(function (err) {
        return next(err);
      });
    } else {
      pgClient.any(queryFindAllProgramas)
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
  findByNameUnidades = function(req, res, next) {
    res.header('Access-Control-Allow-Origin', '*');
    res.header('Access-Control-Allow-Methods', 'GET,PUT,POST,DELETE');
    res.header('Access-Control-Allow-Headers', 'X-Requested-With, Content-Type, X-Auth-Token, Origin, Authorization');
    console.log('method GET: /posgrado/unidad/'+req.params.name)
    pgClient.any(queryFindAllProgramas+' where upper(u.nombre) like upper($1) or upper(u.codigo) like upper($1)', [ '%'+req.params.name+'%' ])
    .then(function (data) {
      res.status(200)
        .json(data);
    })
    .catch(function (err) {
      return next(err);
    });
  };

  //Link routes and functions
  app.get('/posgrado/unidades', findAllUnidades);
  app.get('/posgrado/unidades/:number', findbyNumberUnidades);
  app.get('/posgrado/unidad/:name', findByNameUnidades);

}
