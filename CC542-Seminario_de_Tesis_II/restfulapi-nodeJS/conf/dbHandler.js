var mongoose = require('mongoose');
var config = require('../models/config')

module.exports = {
  mongoDBInitService: function(){
    mongoose.connect(config.urlmongoDB, function(err, res) {
      if(err) {
        console.log('ERROR: connecting to Database. ' + err);
      } else {
        console.log('Connected to Database');
      }
    });
  },
}
