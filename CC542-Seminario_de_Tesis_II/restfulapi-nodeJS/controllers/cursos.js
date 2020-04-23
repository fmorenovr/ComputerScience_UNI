var config = require('../models/config')
var pgClient = config.pgClient

/*const client = new pg.Client(connectionString);
client.connect();
const query = client.query(
  'CREATE TABLE items(id SERIAL PRIMARY KEY, text VARCHAR(40) not null, complete BOOLEAN)');
query.on('end', () => { client.end(); });*/

var datosCursos = "c.codigo, c.descripcion, c.credito, c.nota_maxima, c.nota_minima, c.nota_min_aprobatoria, c.fecha_inicio, c.fecha_fin, c.retiro, c.inasistencia_justificada, c.inasistencia_injustificada, c.inasistencia, v.nom_tabla as modalidad, v1.nom_tabla as tipo_nota, v2.nom_tabla as tipo_curso"

var resultJOIN = "curso c inner join variable v on c.modalidad = v.cod_tabla and c.tip_modalidad = v.tip_tabla inner join variable v1 on c.tipo_nota = v1.cod_tabla and c.tip_tipo_nota = v1.tip_tabla inner join variable v2 on c.tipo_curso = v2.cod_tabla and c.tip_tipo_curso = v2.tip_tabla"

var queryFindAllProgramas = 'select '+datosCursos+' from '+resultJOIN;

module.exports = function(app) {

  //GET - Return all padronrucs in the DB
  findAllCursos = function(req, res, next) {
    res.header('Access-Control-Allow-Origin', '*');
    res.header('Access-Control-Allow-Methods', 'GET,PUT,POST,DELETE');
    res.header('Access-Control-Allow-Headers', 'X-Requested-With, Content-Type, X-Auth-Token, Origin, Authorization');
    console.log('method GET: /posgrado/cursos')
  	pgClient.any(queryFindAllProgramas+' limit 10')
    .then(function (data) {
      res.status(200)
        .json(data);
    })
    .catch(function (err) {
      return next(err);
    });
  };
  
  findbyNumberCursos = function(req, res, next) {
    res.header('Access-Control-Allow-Origin', '*');
    res.header('Access-Control-Allow-Methods', 'GET,PUT,POST,DELETE');
    res.header('Access-Control-Allow-Headers', 'X-Requested-With, Content-Type, X-Auth-Token, Origin, Authorization');
    console.log('method GET: /posgrado/cursos/'+req.params.number)
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
  findByNameCursos = function(req, res, next) {
    res.header('Access-Control-Allow-Origin', '*');
    res.header('Access-Control-Allow-Methods', 'GET,PUT,POST,DELETE');
    res.header('Access-Control-Allow-Headers', 'X-Requested-With, Content-Type, X-Auth-Token, Origin, Authorization');
    console.log('method GET: /posgrado/curso/'+req.params.name)
    pgClient.any(queryFindAllProgramas+' where upper(c.descripcion) like upper($1) or upper(c.codigo) like upper($1)', [ '%'+req.params.name+'%' ])
    .then(function (data) {
      res.status(200)
        .json(data);
    })
    .catch(function (err) {
      return next(err);
    });
  };

  //Link routes and functions
  app.get('/posgrado/cursos', findAllCursos);
  app.get('/posgrado/cursos/:number', findbyNumberCursos);
  app.get('/posgrado/curso/:name', findByNameCursos);

}
