var router    = require('../routers/router'),
    db        = require('./dbHandler');

module.exports = {
  RestfulAPIServiceInit: function (method){
    db.mongoDBInitService();
    if(method=="HTTP"){
      router.server.listen(router.port, function() {
        console.log("Node server running on http://"+ router.url);
      });
    }
  }
}
