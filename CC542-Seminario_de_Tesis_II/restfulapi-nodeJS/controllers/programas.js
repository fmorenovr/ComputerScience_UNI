var config = require('../models/config')
var pgClient = config.pgClient

var datosPrograma = "p.codigo, p.codigo_sunedu, p.nombre, p.descripcion, p.duracion, p.grado, p.titulo";

var datosUnidad = "u.nombre as nombre_unidad, u.codigo as codigo_unidad";

var datosVariable = "v.nom_tabla as periodo, v1.nom_tabla as metodologia, v2.nom_tabla as formacion, v3.nom_tabla as modalidad, p.fecha_inicio, p.fecha_fin";

var datosQuery = datosPrograma +', '+datosUnidad+', '+datosVariable

var resultJOIN = "programa p inner join unidad u on p.id_unidad = u.id inner join variable v on p.tipo_periodo = v.cod_tabla and p.tip_tipo_periodo = v.tip_tabla inner join variable v1 on p.metodologia = v1.cod_tabla and p.tip_metodologia = v1.tip_tabla inner join variable v2 on p.formacion = v2.cod_tabla and p.tip_formacion = v2.tip_tabla inner join variable v3 on p.modalidad = v3.cod_tabla and p.tip_modalidad = v3.tip_tabla";

var queryFindAllProgramas = 'select '+datosQuery+' from '+resultJOIN;

module.exports = function(app) {

  //GET - Return all padronrucs in the DB
  findAllProgramas = function(req, res, next) {
    res.header('Access-Control-Allow-Origin', '*');
    res.header('Access-Control-Allow-Methods', 'GET,PUT,POST,DELETE');
    res.header('Access-Control-Allow-Headers', 'X-Requested-With, Content-Type, X-Auth-Token, Origin, Authorization');
    console.log('method GET: /posgrado/programas')
  	pgClient.any(queryFindAllProgramas+' limit 10')
    .then(function (data) {
      res.status(200)
        .json(data);
    })
    .catch(function (err) {
      return next(err);
    });
  };
  
  findByNumberProgramas = function(req, res, next) {
    res.header('Access-Control-Allow-Origin', '*');
    res.header('Access-Control-Allow-Methods', 'GET,PUT,POST,DELETE');
    res.header('Access-Control-Allow-Headers', 'X-Requested-With, Content-Type, X-Auth-Token, Origin, Authorization');
    console.log('method GET: /posgrado/programas/'+req.params.number)
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
  findByNameProgramas = function(req, res, next) {
    res.header('Access-Control-Allow-Origin', '*');
    res.header('Access-Control-Allow-Methods', 'GET,PUT,POST,DELETE');
    res.header('Access-Control-Allow-Headers', 'X-Requested-With, Content-Type, X-Auth-Token, Origin, Authorization');
    console.log('method GET: /posgrado/programa/'+req.params.name)
    pgClient.any(queryFindAllProgramas+' where upper(p.nombre) like upper($1) or upper(p.codigo) like upper($1)', [ '%'+req.params.name+'%' ])
    .then(function (data) {
      res.status(200)
        .json(data);
    })
    .catch(function (err) {
      return next(err);
    });
  };
  
  //GET - Return a PadronRuc with number
  findByNamePrograUni = function(req, res, next) {
    res.header('Access-Control-Allow-Origin', '*');
    res.header('Access-Control-Allow-Methods', 'GET,PUT,POST,DELETE');
    res.header('Access-Control-Allow-Headers', 'X-Requested-With, Content-Type, X-Auth-Token, Origin, Authorization');
    console.log('method GET: /posgrado/programaunidad/'+req.params.name)
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
  app.get('/posgrado/programas', findAllProgramas);
  app.get('/posgrado/programas/:number', findByNumberProgramas);
  app.get('/posgrado/programa/:name', findByNameProgramas);
  app.get('/posgrado/programaunidad/:name', findByNamePrograUni);

}
