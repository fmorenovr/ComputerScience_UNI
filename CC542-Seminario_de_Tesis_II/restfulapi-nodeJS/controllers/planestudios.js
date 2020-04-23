var config = require('../models/config')
var pgClient = config.pgClient

var datosPlan = "p.codigo as cod_plan, p.nombre as nom_plan, p.descripcion as descripcion_plan, pro.nombre as nom_programa, pro.codigo as cod_programa, p.total_ciclo as num_ciclos, p.grado as grado_obtenido, p.creditos_obligatorios as min_creditos_obligatorios, p.creditos_electivos as min_creditos_electivos, p.creditos as min_creditos";

var datosVariable = "v.nom_tabla as jornada_estudio, v1.nom_tabla as metodologia, v2.nom_tabla as formacion, p.vigencia_inicio, p.vigencia_fin";

var datosQuery = datosPlan +', '+datosVariable

var resultJOIN = "plan_estudio p inner join variable v on p.jornada_estudio = v.cod_tabla and p.tip_jornada_estudio = v.tip_tabla inner join variable v1 on p.metodologia = v1.cod_tabla and p.tip_metodologia = v1.tip_tabla inner join variable v2 on p.formacion = v2.cod_tabla and p.tip_formacion = v2.tip_tabla inner join programa pro on p.id_programa = pro.id";

var queryFindAllProgramas = 'select '+datosQuery+' from '+resultJOIN;

module.exports = function(app) {

  //GET - Return all padronrucs in the DB
  findAllPlanes = function(req, res, next) {
    res.header('Access-Control-Allow-Origin', '*');
    res.header('Access-Control-Allow-Methods', 'GET,PUT,POST,DELETE');
    res.header('Access-Control-Allow-Headers', 'X-Requested-With, Content-Type, X-Auth-Token, Origin, Authorization');
    console.log('method GET: /posgrado/planestudios')
  	pgClient.any(queryFindAllProgramas+' limit 10')
    .then(function (data) {
      res.status(200)
        .json(data);
    })
    .catch(function (err) {
      return next(err);
    });
  };
  
  findByNumberPlanes = function(req, res, next) {
    res.header('Access-Control-Allow-Origin', '*');
    res.header('Access-Control-Allow-Methods', 'GET,PUT,POST,DELETE');
    res.header('Access-Control-Allow-Headers', 'X-Requested-With, Content-Type, X-Auth-Token, Origin, Authorization');
    console.log('method GET: /posgrado/planestudios/'+req.params.number)
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
  findByNamePlanes = function(req, res, next) {
    res.header('Access-Control-Allow-Origin', '*');
    res.header('Access-Control-Allow-Methods', 'GET,PUT,POST,DELETE');
    res.header('Access-Control-Allow-Headers', 'X-Requested-With, Content-Type, X-Auth-Token, Origin, Authorization');
    console.log('method GET: /posgrado/planestudio/'+req.params.name)
    pgClient.any(queryFindAllProgramas+' where upper(p.nombre) like upper($1) or upper(p.codigo) like upper($1)', [ '%'+req.params.name+'%' ])
    .then(function (data) {
      res.status(200)
        .json(data);
    })
    .catch(function (err) {
      return next(err);
    });
  };
  
  //Link routes and functions
  app.get('/posgrado/planestudios', findAllPlanes);
  app.get('/posgrado/planestudios/:number', findByNumberPlanes);
  app.get('/posgrado/planestudio/:name', findByNamePlanes);

}
