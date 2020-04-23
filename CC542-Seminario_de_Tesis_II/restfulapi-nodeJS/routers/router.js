var express   = require("express"),
    app       = express(),
    http      = require("http"),
    server    = http.createServer(app);

var port = 3560,
    host = "localhost";

var allowCrossDomain = function(req, res, next) {
    res.header('Access-Control-Allow-Origin', '*');
    res.header('Access-Control-Allow-Methods', 'GET,PUT,POST,DELETE');
    res.header('Access-Control-Allow-Headers', 'Content-Type, Authorization');

    // intercept OPTIONS method
    if ('OPTIONS' == req.method) {
      res.send(200);
    }
    else {
      next();
    }
}

app.configure(function () {
  app.use(express.bodyParser());
  app.use(express.methodOverride());
  app.use(allowCrossDomain);
  app.use(app.router);
});

app.get('/', function(req, res) {
  res.send("Hello world REST Service :D !");
});

// MongoDB
require('../controllers/padronruc')(app);

// postgreSQL
require('../controllers/cursos')(app);
require('../controllers/mallas')(app);
require('../controllers/alumnos')(app);
require('../controllers/unidades')(app);
require('../controllers/programas')(app);
require('../controllers/planestudios')(app);
require('../controllers/datospersonas')(app);

module.exports = {
  app   : app,
  server: server,
  port  : port,
  url   : host+":"+port,
}
