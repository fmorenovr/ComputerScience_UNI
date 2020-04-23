var mongoose = require('mongoose'),
    Schema = mongoose.Schema;

var padronRucSchema = new Schema({
  id: {
    type: String
  }, ruc: {
    type: String
  }, razon_social: {
    type: String
  }, estado_contribuyente: {
    type: String
  }, condicion_domicilio: {
    type: String
  }, ubigeo: {
    type: String,
  }, tipo_via: {
    type: String
  }, nombre_via: {
    type: String
  }, codigo_zona: {
    type: String
  }, tipo_zona: {
    type: String
  }, numero: {
    type: String
  }, interior: {
    type: String
  }, lote: {
    type: String
  }, departamento: {
    type: String
  }, manzana: {
    type: String
  }, kilometro: {
    type: String
  }, prueba: {
    type: String
  }, 
}, {
  versionKey: false,
  toObject: { virtuals: true },
  toJSON: { virtuals: true }
});

padronRucSchema.virtual('ubicacion').get(function(){
  return this.tipo_via+" "+this.nombre_via+" "+this.codigo_zona + " " + this.tipo_zona +" " + this.numero;
});

padronRucSchema.index({ ruc: 'text', razon_social: 'text' });

module.exports = mongoose.model('PadronRuc', padronRucSchema, 'padronrucs');

