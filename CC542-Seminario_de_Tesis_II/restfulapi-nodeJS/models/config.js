var portmongoDB  = 27017,
    portpostgres = 5432,
    hostmongoDB  = "matricula.proyectoposgrado.uni.edu.pe",
    hostpostgres = "matricula.proyectoposgrado.uni.edu.pe";

var pgp = require('pg-promise')({promiseLib: require('bluebird')});

var postgresConf = {
  host     : hostpostgres,
  port     : portpostgres,
  database : 'sacad_db_ultimo',
  user     : 'locomatico',
  password : '1QAZXSW2'
}

var mongoDBConf = {
  host     : hostmongoDB,
  port     : portmongoDB,
  database : "posgrado",
  col_ruc  : "padronrucs",
}

var pgClient = pgp(postgresConf)

module.exports = {
  pgClient : pgClient,
  mongoDBConf  : mongoDBConf,
  postgresConf : postgresConf,
  urlpostgres : 'postgres://'+hostpostgres+':'+portpostgres+'/sacad_db_ultimo',
  urlmongoDB  : 'mongodb://'+hostmongoDB+':'+portmongoDB+'/posgrado'
}
