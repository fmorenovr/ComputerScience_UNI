var config = require('../models/config')
var pgClient = config.pgClient

var datosAlumnos = "per.correo_institucion, a.codigo as cod_alumno, \
un.nombre as nom_unidad, p.codigo as cod_periodo, p.nombre as nom_periodo, \
pl.codigo as cod_planestudio, pl.nombre as nom_planestudio, \
pro.codigo as cod_programa, pro.codigo_sunedu as cod_sunedu_programa, pro.nombre as nom_programa, \
v.nom_tabla as estado_persona, v1.nom_tabla as estado_alumno, \
p.fecha_inicio, p.fecha_fin";

var resultJOIN = "alumno a \
inner join variable v on a.estado_persona = v.cod_tabla and a.tip_estado_persona = v.tip_tabla \
inner join variable v1 on a.estado_alumno = v1.cod_tabla and a.tip_estado_alumno = v1.tip_tabla \
inner join periodo p on a.id_periodo = p.id \
inner join persona per on per.id = a.id_persona \
inner join plan_estudio pl on a.id_plan_estudio = pl.id \
inner join programa pro on pl.id_programa = pro.id \
inner join unidad un on pro.id_unidad = un.id";

var datosQuery = datosAlumnos

var queryFindAllProgramas = 'select '+datosQuery+' from '+resultJOIN;

module.exports = function(app) {

  //GET - Return all padronrucs in the DB
  findAllAlumnos = function(req, res, next) {
    res.header('Access-Control-Allow-Origin', '*');
    res.header('Access-Control-Allow-Methods', 'GET,PUT,POST,DELETE');
    res.header('Access-Control-Allow-Headers', 'X-Requested-With, Content-Type, X-Auth-Token, Origin, Authorization');
    console.log('method GET: /posgrado/alumnos')
  	pgClient.any(queryFindAllProgramas+' limit 10')
    .then(function (data) {
      res.status(200)
        .json(data);
    })
    .catch(function (err) {
      return next(err);
    });
  };
  
  findByNumberAlumnos = function(req, res, next) {
    res.header('Access-Control-Allow-Origin', '*');
    res.header('Access-Control-Allow-Methods', 'GET,PUT,POST,DELETE');
    res.header('Access-Control-Allow-Headers', 'X-Requested-With, Content-Type, X-Auth-Token, Origin, Authorization');
    console.log('method GET: /posgrado/alumnos/'+req.params.number)
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
  findByNameAlumnos = function(req, res, next) {
    res.header('Access-Control-Allow-Origin', '*');
    res.header('Access-Control-Allow-Methods', 'GET,PUT,POST,DELETE');
    res.header('Access-Control-Allow-Headers', 'X-Requested-With, Content-Type, X-Auth-Token, Origin, Authorization');
    console.log('method GET: /posgrado/alumno/'+req.params.name)
    pgClient.any(queryFindAllProgramas+' where upper(per.correo_institucion) = upper($1)', [ req.params.name ])
    .then(function (data) {
      res.status(200)
        .json(data);
    })
    .catch(function (err) {
      return next(err);
    });
  };
  
  //Link routes and functions
  app.get('/posgrado/alumnos', findAllAlumnos);
  app.get('/posgrado/alumnos/:number', findByNumberAlumnos);
  app.get('/posgrado/alumno/:name', findByNameAlumnos);

}
