module.exports = function(app) {

  var PadronRuc = require('../models/padronruc');

  var countRucs;
  
  PadronRuc.count()
  .exec(function(err,count){
    console.log("Nro de datos: "+count);
    countRucs = count;
  });
  
  //GET - Return all padronrucs in the DB
  findAllPadronRucs = function(req, res) {
    res.header('Access-Control-Allow-Origin', '*');
    res.header('Access-Control-Allow-Methods', 'GET,PUT,POST,DELETE');
    res.header('Access-Control-Allow-Headers', 'X-Requested-With, Content-Type, X-Auth-Token, Origin, Authorization');
  	PadronRuc.find()
  	.skip(countRucs - 10)
  	.exec(function(err, padronrucs) {
  		if(!err) {
        console.log('method GET: /padronrucs')
  			res.send(padronrucs);
  		} else {
  			console.log('ERROR: ' + err);
  		}
  	});
  };

  //GET - Return a PadronRuc with specified ID
  findById = function(req, res) {
    res.header('Access-Control-Allow-Origin', '*');
    res.header('Access-Control-Allow-Methods', 'GET,PUT,POST,DELETE');
    res.header('Access-Control-Allow-Headers', 'X-Requested-With, Content-Type, X-Auth-Token, Origin, Authorization');
    PadronRuc.findById(req.params.id)
    .exec(function(err, padronruc) {
  		if(!err) {
        console.log('method GET: /padronruc/' + req.params.id);
  			res.send(padronruc);
  		} else {
  			console.log('ERROR: ' + err);
  		}
  	});
  };

  //GET - Return a PadronRuc with number
  findByNumber = function(req, res) {
    res.header('Access-Control-Allow-Origin', '*');
    res.header('Access-Control-Allow-Methods', 'GET,PUT,POST,DELETE');
    res.header('Access-Control-Allow-Headers', 'X-Requested-With, Content-Type, X-Auth-Token, Origin, Authorization');
    PadronRuc.find()
  	.skip(countRucs - req.params.number)
  	.exec(function(err, padronrucs) {
  		if(!err) {
        console.log('method GET: /padronrucs/' + req.params.number)
  			res.send(padronrucs);
  		} else {
  			console.log('ERROR: ' + err);
  		}
  	});
  };

  //GET - Return a PadronRuc with specified Ruc
  findByRuc = function(req, res) {
    res.header('Access-Control-Allow-Origin', '*');
    res.header('Access-Control-Allow-Methods', 'GET,PUT,POST,DELETE');
    res.header('Access-Control-Allow-Headers', 'X-Requested-With, Content-Type, X-Auth-Token, Origin, Authorization');
    var ruc_reg   = new RegExp(req.params.ruc, 'i');
  	PadronRuc.find(
  	  {
  	    //$or: [
  	    //{ $text: { $search: req.params.ruc } },
  	    $text: { $search: "\""+req.params.ruc+"\"" }
  	    //{'ruc': { $regex: ruc_reg } }
  	    //]
  	  }, {
  	    score : {
  	      $meta: "textScore" 
  	    } 
  	  })/*
  	  { $or:[
  	    {'ruc': req.params.ruc},
  	    {'ruc': { $regex: ruc_reg } },
  	    {'razon_social': req.params.ruc},
  	    {'razon_social': { $regex: ruc_reg } },
  	    //db.users.find({name: /a/})  //like '%a%'
        //db.users.find({name: /^pa/}) //like 'pa%' 
        //db.users.find({name: /ro$/}) //like '%ro'
  	  ]})*/
  	  /*.aggregate({ubicacion:{ $concat: ['$tipo_via', ' ', '$nombre_via', ' ', '$codigo_zona', ' ', '$tipo_zona', ' ', '$numero'] }})*/
  	  .select({_id:0, tipo_via:1, nombre_via:1, codigo_zona:1, tipo_zona:1, numero: 1, ruc:1, razon_social:1, ubicacion:1, score:{$meta: "textScore" } })
  	  //.select('-_id tipo_via nombre_via codigo_zona tipo_zona numero ruc razon_social ubicacion')
  	  /*
  	  .where('field1').gte(25)
      .where().in([])
      .skip(20)
      .limit(10)
      .asc('field1')
      */
//      .sort("score")
  	  .exec(function(err, padronruc) {
  		if(!err) {
        console.log('method GET: /padronruc/' + req.params.ruc);
        /*var prc = []
        for (i = 0; i < padronruc.length; i++) {
          prc.push({
            ruc: padronruc[i].ruc,
            razon_social: padronruc[i].razon_social,
            ubicacion: padronruc[i].ubicacion
          })
        }*/
        //res.send(prc);
        console.log("founded :"+padronruc.length)
  			res.send(padronruc);
  		} else {
  			console.log('ERROR: ' + err);
  		}
  	});
  };

  //POST - Insert a new PadronRuc in the DB
  addPadronRuc = function(req, res) {
    res.header('Access-Control-Allow-Origin', '*');
    res.header('Access-Control-Allow-Methods', 'GET,PUT,POST,DELETE');
    res.header('Access-Control-Allow-Headers', 'X-Requested-With, Content-Type, X-Auth-Token, Origin, Authorization');
  	console.log('method POST:');
  	console.log(req.body);

  	var padronruc = new PadronRuc({
  		ruc:                  req.body.ruc,
      razon_social:         req.body.razon_social,
      estado_contribuyente: req.body.estado_contribuyente,
      condicion_domicilio:  req.body.condicion_domicilio,
      ubigeo:               req.body.ubigeo,
      tipo_via:             req.body.tipo_via,
      nombre_via:           req.body.nombre_via,
      codigo_zona:          req.body.codigo_zona,
      tipo_zona:            req.body.tipo_zona,
      numero:               req.body.numero,
      interior:             req.body.interior,
      lote:                 req.body.lote,
      departamento:         req.body.departamento,
      manzana:              req.body.manzana,
      kilometro:            req.body.kilometro,
      prueba:               req.body.prueba
  	});

  	padronruc.save(function(err) {
  		if(!err) {
  			console.log('Created');
  		} else {
  			console.log('ERROR: ' + err);
  		}
  	});

  	res.send(padronruc);
  };

  //PUT - Update a register already exists
  updatePadronRuc = function(req, res) {
    res.header('Access-Control-Allow-Origin', '*');
    res.header('Access-Control-Allow-Methods', 'GET,PUT,POST,DELETE');
    res.header('Access-Control-Allow-Headers', 'X-Requested-With, Content-Type, X-Auth-Token, Origin, Authorization');
  	PadronRuc.findById(req.params.id, function(err, padronruc) {
  		ruc                   = req.body.ruc;
      razon_social          = req.body.razon_social;
      estado_contribuyente  = req.body.estado_contribuyente;
      condicion_domicilio   = req.body.condicion_domicilio;
      ubigeo                = req.body.ubigeo;
      tipo_via              = req.body.tipo_via;
      nombre_via            = req.body.nombre_via;
      codigo_zona           = req.body.codigo_zona;
      tipo_zona             = req.body.tipo_zona;
      numero                = req.body.numero;
      interior              = req.body.interior;
      lote                  = req.body.lote;
      departamento          = req.body.departamento;
      manzana               = req.body.manzana;
      kilometro             = req.body.kilometro;
      prueba                = req.body.prueba;

  		padronruc.save(function(err) {
  			if(!err) {
  				console.log('Updated');
  			} else {
  				console.log('ERROR: ' + err);
  			}
  			res.send(padronruc);
  		});
  	});
  }

  //DELETE - Delete a PadronRuc with specified ID
  deletePadronRuc = function(req, res) {
    res.header('Access-Control-Allow-Origin', '*');
    res.header('Access-Control-Allow-Methods', 'GET,PUT,POST,DELETE');
    res.header('Access-Control-Allow-Headers', 'X-Requested-With, Content-Type, X-Auth-Token, Origin, Authorization');
  	PadronRuc.findById(req.params.id, function(err, padronruc) {
  		padronruc.remove(function(err) {
  			if(!err) {
  				console.log('Removed');
  			} else {
  				console.log('ERROR: ' + err);
  			}
  		})
  	});
  }

  //Link routes and functions
  app.get('/posgrado/padronrucs', findAllPadronRucs);
  app.get('/posgrado/padronrucs/:number', findByNumber);
  app.get('/posgrado/padronruc/:ruc', findByRuc);
  //app.post('/padronruc', addPadronRuc);
  //app.put('/padronruc/:id', updatePadronRuc);
  //app.delete('/padronruc/:id', deletePadronRuc);

}
