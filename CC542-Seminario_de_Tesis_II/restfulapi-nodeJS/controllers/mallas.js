var config = require('../models/config')
var pgClient = config.pgClient

var datosMallas = "m.descripcion as descripcion_malla, c.codigo as cod_curso, c.descripcion as nombre_curso, ci.nombre as ciclo_curso, \
m.credito, m.hora_teoria, m.hora_practica, hora_asesoria, \
m.nota_maxima, m.nota_minima, m.nota_min_aprobatoria, \
m.inasistencia_justificada, m.inasistencia_injustificada, \
m.inasistencia, m.electivo as es_electivo, v.nom_tabla as metodologia, \
v1.nom_tabla as tipo_nota, v2.nom_tabla as tipo_curso, \
m.retiro, m.fecha_inicio, m.fecha_fin"

var resultJOIN = "malla m \
inner join curso c on c.id = m.id_curso \
inner join ciclo ci on m.id_ciclo = ci.id \
inner join variable v on m.metodologia = v.cod_tabla and m.tip_metodologia = v.tip_tabla \
inner join variable v1 on m.tipo_nota = v1.cod_tabla and m.tip_tipo_nota = v1.tip_tabla \
inner join variable v2 on m.tipo_curso = v2.cod_tabla and m.tip_tipo_curso = v2.tip_tabla"

var queryFindAllMallas = 'select '+datosMallas+' from '+resultJOIN;

module.exports = function(app) {

  //GET - Return all padronrucs in the DB
  findAllMallas = function(req, res, next) {
    res.header('Access-Control-Allow-Origin', '*');
    res.header('Access-Control-Allow-Methods', 'GET,PUT,POST,DELETE');
    res.header('Access-Control-Allow-Headers', 'X-Requested-With, Content-Type, X-Auth-Token, Origin, Authorization');
    console.log('method GET: /posgrado/mallas')
  	pgClient.any(queryFindAllMallas+' limit 10')
    .then(function (data) {
      res.status(200)
        .json(data);
    })
    .catch(function (err) {
      return next(err);
    });
  };
  
  findbyNumberMallas = function(req, res, next) {
    res.header('Access-Control-Allow-Origin', '*');
    res.header('Access-Control-Allow-Methods', 'GET,PUT,POST,DELETE');
    res.header('Access-Control-Allow-Headers', 'X-Requested-With, Content-Type, X-Auth-Token, Origin, Authorization');
    console.log('method GET: /posgrado/mallas/'+req.params.number)
    if(req.params.number !="all"){
    	pgClient.any(queryFindAllMallas+' limit $1', req.params.number)
      .then(function (data) {
        res.status(200)
          .json(data);
      })
      .catch(function (err) {
        return next(err);
      });
    } else {
      pgClient.any(queryFindAllMallas)
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
  findByNameMallas = function(req, res, next) {
    res.header('Access-Control-Allow-Origin', '*');
    res.header('Access-Control-Allow-Methods', 'GET,PUT,POST,DELETE');
    res.header('Access-Control-Allow-Headers', 'X-Requested-With, Content-Type, X-Auth-Token, Origin, Authorization');
    console.log('method GET: /posgrado/curso/'+req.params.name)
    pgClient.any(queryFindAllMallas+' where upper(m.descripcion) like upper($1) or upper(c.codigo) like upper($1)', [ '%'+req.params.name+'%' ])
    .then(function (data) {
      res.status(200)
        .json(data);
    })
    .catch(function (err) {
      return next(err);
    });
  };

  //Link routes and functions
  app.get('/posgrado/mallas', findAllMallas);
  app.get('/posgrado/mallas/:number', findbyNumberMallas);
  app.get('/posgrado/malla/:name', findByNameMallas);

}
