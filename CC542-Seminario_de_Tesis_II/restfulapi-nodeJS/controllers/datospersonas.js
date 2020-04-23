var config = require('../models/config')
var pgClient = config.pgClient

var datosPersonasPersonal = "p.nombre, p.segundo_nombre, p.apellido_paterno, p.apellido_materno, concat(p.nombre,' ', p.segundo_nombre, ' ', p.apellido_paterno, ' ', p.apellido_materno) as nombre_completo, p.fecha_nacimiento, p.correo_institucion, p.numero_documento, v.nom_tabla as tipo_documento, v1.nom_tabla as estado_civil"

var resultJOINPersonales = "persona p inner join variable v on p.tipo_documento = v.cod_tabla and p.tip_tipo_documento = v.tip_tabla inner join variable v1 on p.estado_civil = v1.cod_tabla and p.tip_estado_civil = v1.tip_tabla";

var datosPersonasContactoDireccion = "c.descripcion as direccion"//, v.nom_tabla as telefono, v.nom_tabla as celular"

var resultJOINContactosDireccion = "persona p inner join contacto c on c.id_persona = p.id inner join variable v on c.id_tipo_contacto = v.cod_tabla and c.tip_tipo_contacto = v.tip_tabla"
//inner join contacto c1 on c1.id_tipo_contacto = v.cod_tabla and c1.tip_tipo_contacto = v.tip_tabla and c1.id_tipo_contacto = '2'" //inner join contacto c2 on c2.id_tipo_contacto = v.cod_tabla and c2.tip_tipo_contacto = v.tip_tabla and c.id_tipo_contacto = '3'"

var datosPersonasContactoDomicilio = "c.descripcion as telf_domicilio"//, v.nom_tabla as telefono, v.nom_tabla as celular"

var resultJOINContactosDomicilio = "contacto c inner join variable v on c.id_tipo_contacto = v.cod_tabla and c.tip_tipo_contacto = v.tip_tabla where c.id_tipo_contacto = '2'"

var datosPersonasContactoCelular = "c.descripcion as telf_celular"//, v.nom_tabla as telefono, v.nom_tabla as celular"

var resultJOINContactosCelular = "contacto c inner join variable v on c.id_tipo_contacto = v.cod_tabla and c.tip_tipo_contacto = v.tip_tabla where c.id_tipo_contacto = '3'"

var queryFindAllPersonasPersonales = 'select '+ datosPersonasPersonal+' from '+ resultJOINPersonales

var queryFindAllPersonasContactosDireccion = 'select '+ datosPersonasContactoDireccion+' from '+ resultJOINContactosDireccion
var queryFindAllPersonasContactosDomicilio = 'select '+ datosPersonasContactoDomicilio+' from '+ resultJOINContactosDomicilio
var queryFindAllPersonasContactosCelular   = 'select '+ datosPersonasContactoCelular+' from '+ resultJOINContactosCelular

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
    pgClient.any(queryFindAllPersonasPersonales+' where upper(p.correo_institucion) = upper($1)', [ req.params.name ])
    .then(function (data) {
      res.status(200)
        .json(data);
    })
    .catch(function (err) {
      return next(err);
    });
  };
  
  findAllPersonasContactos = function(req, res, next) {
    var dataDireccion
    res.header('Access-Control-Allow-Origin', '*');
    res.header('Access-Control-Allow-Methods', 'GET,PUT,POST,DELETE');
    res.header('Access-Control-Allow-Headers', 'X-Requested-With, Content-Type, X-Auth-Token, Origin, Authorization');
    console.log('method GET: /posgrado/datospersonas/contactos/')
  	pgClient.any(queryFindAllPersonasContactosDireccion+' limit 10')
    .then(function (data) {
      dataDireccion = data
      res.status(200).json(data);
      //console.log("despues de la consulta xd", json(dataDireccion))
    })
    .catch(function (err) {
      return next(err);
    });
    console.log("despues de la consulta xd", dataDireccion)
  };
  
  findbyNumberPersonasContactos = function(req, res, next) {
    res.header('Access-Control-Allow-Origin', '*');
    res.header('Access-Control-Allow-Methods', 'GET,PUT,POST,DELETE');
    res.header('Access-Control-Allow-Headers', 'X-Requested-With, Content-Type, X-Auth-Token, Origin, Authorization');
    console.log('method GET: /posgrado/datospersonas/contactos/'+req.params.number)
    if(req.params.number !="all"){
    	pgClient.any(queryFindAllPersonasContactosDireccion+' limit $1', req.params.number)
      .then(function (data) {
        res.status(200)
          .json(data);
      })
      .catch(function (err) {
        return next(err);
      });
    } else {
      pgClient.any(queryFindAllPersonasContactosDireccion)
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
    pgClient.any(queryFindAllPersonasContactosDireccion+" where upper(p.correo_institucion) = upper($1)", [ req.params.name ])
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
