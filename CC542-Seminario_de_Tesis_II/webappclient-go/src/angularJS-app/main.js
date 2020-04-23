'use strict';

//settings and state
var app = {
  name: 'BeaGons!',
  title: 'BeaGons! - Dashboard',
  version: '1.5.10',
  sensor: 'Sensores',
  usr: 'ModuleIoT',
  debug: true,
  views: 'views/',
  webapp: 'app',
  /**
  * Define funciones
  */
  Encrypt: Encrypt,
  DataFill: DataFill,
  getColor: getColor,
  colorBar: colorBar,
  getUnidad: getUnidad,
  getValores: getValores,
  setDatatoD3: setDatatoD3,
  validarEmail: validarEmail,
  verifyStatus: verifyStatus,
  addDataVector: addDataVector,
  getDatesSensors: getDatesSensors,
  getColorPolygon: getColorPolygon,
  generarPassword: generarPassword,
  getDateDashboard: getDateDashboard,
  getIndicadorValor: getIndicadorValor,
  generateRandomPositions: generateRandomPositions,
  generateCircularPositions: generateCircularPositions,
  /**
   * In-app constants
   */
  settings: {
    colors: {
      'white': '#fff',
      'black': '#000',
      'gray-light': '#999',
      'gray-lighter': '#eee',
      'gray': '#666',
      'gray-dark': '#343434',
      'gray-darker': '#222',
      'gray-semi-light': '#777',
      'gray-semi-lighter': '#ddd',
      'brand-primary': '#5d8fc2',
      'brand-success': '#64bd63',
      'brand-warning': '#f0b518',
      'brand-danger': '#dd5826',
      'brand-info': '#5dc4bf'
    },
    screens: {
      'xs-max': 767,
      'sm-min': 768,
      'sm-max': 991,
      'md-min': 992,
      'md-max': 1199,
      'lg-min': 1200
    },
    navCollapseTimeout: 2500
  },
  /**
   * Application state. May be changed when using.
   * Synced to Local Storage
   */
  state: {
    /**
     * whether navigation is static (prevent automatic collapsing)
     */
    'nav-static': false
  }
};


var Helpers = function(){
  this._initResizeEvent();
  this._initOnScreenSizeCallbacks();
};

Helpers.prototype = {
  _resizeCallbacks: [],
  _screenSizeCallbacks: {
    xs:{enter:[], exit:[]},
    sm:{enter:[], exit:[]},
    md:{enter:[], exit:[]},
    lg:{enter:[], exit:[]}
  },
  /**
  * Checks screen size according to Bootstrap default sizes
  * @param size screen size  ('xs','sm','md','lg')
  * @returns {boolean} whether screen is <code>size</code>
  */
  isScreen: function(size){
    var screenPx = window.innerWidth;
    return (screenPx >= app.settings.screens[size + '-min'] || size == 'xs') && (screenPx <= app.settings.screens[size + '-max'] || size == 'lg');
  },

  /**
  * Returns screen size Bootstrap-like string ('xs','sm','md','lg')
  * @returns {string}
  */
  getScreenSize: function(){
    var screenPx = window.innerWidth;
    if (screenPx <= app.settings.screens['xs-max']) return 'xs';
    if ((screenPx >= app.settings.screens['sm-min']) && (screenPx <= app.settings.screens['sm-max'])) return 'sm';
    if ((screenPx >= app.settings.screens['md-min']) && (screenPx <= app.settings.screens['md-max'])) return 'md';
    if (screenPx >= app.settings.screens['lg-min']) return 'lg';
  },

  /**
  * Specify a function to execute when window entered/exited particular size.
  * @param size ('xs','sm','md','lg')
  * @param fn callback(newScreenSize, prevScreenSize)
  * @param onEnter whether to run a callback when screen enters `size` or exits. true by default @optional
  */
  onScreenSize: function(size, fn, /**Boolean=*/ onEnter){
    onEnter = typeof onEnter !== 'undefined' ? onEnter : true;
    this._screenSizeCallbacks[size][onEnter ? 'enter' : 'exit'].push(fn)
  },

  /**
  * Change color brightness
  * @param color
  * @param ratio
  * @param darker
  * @returns {string}
  */
  //credit http://stackoverflow.com/questions/1507931/generate-lighter-darker-color-in-css-using-javascript
  changeColor: function(color, ratio, darker) {
    var pad = function(num, totalChars) {
      var pad = '0';
      num = num + '';
      while (num.length < totalChars) {
        num = pad + num;
      }
      return num;
    };
    // Trim trailing/leading whitespace
    color = color.replace(/^\s*|\s*$/, '');
    // Expand three-digit hex
    color = color.replace(
      /^#?([a-f0-9])([a-f0-9])([a-f0-9])$/i,'#$1$1$2$2$3$3'
    );
    // Calculate ratio
    var difference = Math.round(ratio * 256) * (darker ? -1 : 1),
    // Determine if input is RGB(A)
      rgb = color.match(new RegExp('^rgba?\\(\\s*' +
        '(\\d|[1-9]\\d|1\\d{2}|2[0-4][0-9]|25[0-5])' +
        '\\s*,\\s*' +
        '(\\d|[1-9]\\d|1\\d{2}|2[0-4][0-9]|25[0-5])' +
        '\\s*,\\s*' +
        '(\\d|[1-9]\\d|1\\d{2}|2[0-4][0-9]|25[0-5])' +
        '(?:\\s*,\\s*' +
        '(0|1|0?\\.\\d+))?' +
        '\\s*\\)$', 'i')),
        alpha = !!rgb && rgb[4] != null ? rgb[4] : null,
    // Convert hex to decimal
        decimal = !!rgb? [rgb[1], rgb[2], rgb[3]] : color.replace(
          /^#?([a-f0-9][a-f0-9])([a-f0-9][a-f0-9])([a-f0-9][a-f0-9])/i,
          function() {
            return parseInt(arguments[1], 16) + ',' +
              parseInt(arguments[2], 16) + ',' +
              parseInt(arguments[3], 16);
          }
        ).split(/,/),returnValue;
    // Return RGB(A)
    return !!rgb ?
      'rgb' + (alpha !== null ? 'a' : '') + '(' +
      Math[darker ? 'max' : 'min'](
        parseInt(decimal[0], 10) + difference, darker ? 0 : 255
      ) + ', ' +
      Math[darker ? 'max' : 'min'](
        parseInt(decimal[1], 10) + difference, darker ? 0 : 255
      ) + ', ' +
      Math[darker ? 'max' : 'min'](
        parseInt(decimal[2], 10) + difference, darker ? 0 : 255
      ) + (alpha !== null ? ', ' + alpha : '') + ')' :
        // Return hex
        [
          '#',
          pad(Math[darker ? 'max' : 'min'](
            parseInt(decimal[0], 10) + difference, darker ? 0 : 255
          ).toString(16), 2),
          pad(Math[darker ? 'max' : 'min'](
            parseInt(decimal[1], 10) + difference, darker ? 0 : 255
          ).toString(16), 2),
          pad(Math[darker ? 'max' : 'min'](
            parseInt(decimal[2], 10) + difference, darker ? 0 : 255
          ).toString(16), 2)
        ].join('');
  },
  lightenColor: function(color, ratio) {
    return this.changeColor(color, ratio, false);
  },
  darkenColor: function(color, ratio) {
    return this.changeColor(color, ratio, true);
  },
  max: function(array) {
    return Math.max.apply(null, array);
  },
  min: function(array) {
    return Math.min.apply(null, array);
  },
  /**
  * Triggers sn:resize event. sn:resize is a convenient way to handle both window resize event and
  * sidebar state change.
  * Fired maximum once in 100 millis
  * @private
  */
  _initResizeEvent: function(){
    var resizeTimeout;
    $(window).on('resize', function() {
      clearTimeout(resizeTimeout);
      resizeTimeout = setTimeout(function(){
        $(window).trigger('sn:resize');
      }, 100);
    });
  },
  /**
  * Initiates an array of throttle onScreenSize callbacks.
  * @private
  */
  _initOnScreenSizeCallbacks: function(){
    var resizeTimeout,
      helpers = this,
      prevSize = this.getScreenSize();
    $(window).resize(function() {
      clearTimeout(resizeTimeout);
      resizeTimeout = setTimeout(function(){
        var size = helpers.getScreenSize();
        if (size != prevSize){ //run only if something changed
          //run exit callbacks first
          helpers._screenSizeCallbacks[prevSize]['exit'].forEach(function(fn){
            fn(size, prevSize);
          });
          //run enter callbacks then
          helpers._screenSizeCallbacks[size]['enter'].forEach(function(fn){
            fn(size, prevSize);
          });
          console.log('screen changed. new: ' + size + ', old: ' + prevSize);
        }
        prevSize = size;
      }, 100);
    });
  }
};

app.helpers = new Helpers();

function verifyStatus(){
  
}

function setDatatoD3(value,datos,colorval) {
  var sinf = [];
  sinf = DataFill(datos);

  return [
    {
      values: sinf,
      key: value,
      color: colorval,
      area: true
    }/*,
    {
      values: cos,
      key: 'Cosine Wave',
      color: '#2ca02c'
    }*/
  ];
}

function getColor(tipo){
  var str
  if (tipo == "temperatura" || tipo == "Temperatura") {
    str = '#F7653F'
  } else if (tipo == "presion" || tipo == "Presion") {
    str = '#40FF00'
  } else if (tipo == "monoxido" || tipo == "Monoxido") {
    str = '#00BFFF'
  } else if (tipo == "dioxido" || tipo == "Dioxido") {
    str = '#DBA901'
  }
  return str
}

function getUnidad(tipo){
  var str = ""
  if (tipo == "temperatura" || tipo == "Temperatura") {
    str = "°C"
  } else if (tipo == "dioxido" || tipo == "Dioxido") {
    str = "ppm"
  } else if (tipo == "presion" || tipo == "Presion") {
    str = "Pa"
  } else if (tipo == "monoxido" || tipo == "Monoxido") {
    str = "ppm"
  }
  return str
}

function getDateDashboard(){
  var date = new Date();
  var a,b, f_registro, h_registro
  a = date.toJSON()
  f_registro = a.substr(0,10)
  b = date.toTimeString()
  h_registro = b.split(" ")[0]
  
  return {hora: h_registro, fecha: f_registro}
}

function Encrypt(str) {
  var x = str.length;
  var result = "";
  while (x>=0) {
    result = result + str.charAt(x);
    x--;
  }
  return result;
}

function getDatesSensors(str){
    var res = str.split(" ");
    return res
  }

function generarPassword(longitud){
  var i;
  var caracteres = "abcdefghijkmnpqrtuvwxyzABCDEFGHIJKLMNPQRTUVWXYZ2346789";
  var contraseña = "";
  for (i=0; i<longitud; i++) contraseña += caracteres.charAt(Math.floor(Math.random()*caracteres.length));
  return contraseña;
}

function DataFill(datosSen){
  var datos = [];
  angular.forEach(datosSen, function (value, key) {
    datos.push({x: new Date(value.date), y: value.value});
  });
  return datos;
};

function addDataVector(obj,datos){
  var datta, len;
  var i;
  for (i = 0; i < datos.length; i++) {
    if(datos[i].key == obj.id_moduleiot){
      if(obj.value== NaN) obj.value = 0;
      datos[i].values.push({x: new Date(obj.date), y: obj.value})
      len = (datos[i].values).length
      datos[i].values = (datos[i].values).subarray(len-10)
      break
    }
  }
  datta = datos
  return datta
}
// lat: lat, lon: lon, r: radio, num: # de posiciones random
function generateRandomPositions(lat,lon,rad,num){
  var positions = [];
  var i, u, v, w, t, r, x, lat1, lon1, newLat, newLon
  r = rad/111300 // r = 100, 100 metros
  for (i = 0; i<num; i++){
    u = Math.random()
    v = Math.random()
    w = r * Math.sqrt(u)
    t = 2 * Math.PI * v
    x = w * Math.cos(t)
    lat1 = w * Math.sin(t)
    lon1 = x / Math.cos(lat)
    newLat = lat + lat1
    newLon = lon + lon1
    positions.push([newLat,newLon])
  }
  return positions
}
// genera posiciones de manera circular basado en el lat, lon original
function generateCircularPositions(lat, lon, rad, lados){
  var a = 360/lados;
  var r = rad/111300
  var Xp, Yp
  // inicia la variable points
  //var points= (cx+r)+","+cy+" ";
  var points = [];
  // calcula el resto de los puntos
  for(var i=1;i <= lados;i++){
    var aRad=  (Math.PI / 180) * (a*i);
    Xp = lat+r * Math.cos(aRad);
    Yp = lon+r * Math.sin(aRad);
    points.push([Xp,Yp])
  }
  // devuelve la variable points			
  return points	
}

function getValores(tipo){
  if (tipo == "temperatura" || tipo == "Temperatura") {
    return [0,15, 27, 38];
  } else if (tipo == "dioxido" || tipo == "Dioxido") {
    return [0,15, 27, 38];
  } else if (tipo == "presion" || tipo == "Presion") {
    return [0,15, 27, 38];
  } else if (tipo == "monoxido" || tipo == "Monoxido") {
    return [0,15, 27, 38]; // de menor a mayor
  }
}
// devuelve el indicador para el mapa de calor
function getIndicadorValor(valor, tipo){
  var rango = getValores(tipo);
  var str
  if( valor >= rango[3]){
    str = "muy alto";
  } else if (valor >= rango[2]){
    str = "alto";
  } else if(valor >= rango[1]){
    str = "medio";
  } else if(valor >= rango[0]){
    str = "bajo";
  } else if(rango[0] >= valor){
    str = "muy bajo";
  }
  return str
}

function getColorPolygon(indicador){
  var fill, stroke
  if (indicador == "Muy alto" || indicador == "muy alto") {
    fill = '#FE2E2E';
    stroke = '#FA5858';
  } else if (indicador == "Alto" || indicador == "alto") {
    fill = '#FE2E2E';
    stroke = '#FF8000';
  } else if (indicador == "Medio" || indicador == "medio") {
    fill = '#FFBF00';
    stroke = '#3ADF00';
  } else if (indicador == "Bajo" || indicador == "bajo") {
    fill = '#00BFFF';
    stroke = '#0040FF';
  } else if (indicador == "Muy bajo" || indicador == "muy bajo") {
    fill = '#0040FF';
    stroke = '#2E64FE';
  }
  return {fillc: fill, strokec: stroke}

}

function colorBar(num) {
  var r = 255;
  var g = 0;
  var b = 0;

  while(r<255){
    r++;
    if(r%num==0){
      displayBar();
    }
  }
  while(b>0){
    b--;
    if(b%num==0){
      displayBar();
    }
  }
  while(g<255){
    g++;
    if(g%num==0){
      displayBar();
    }
  }
  while(r>0){
    r--;
    if(r%num==0){
      displayBar();
    }
  }
  while(b<255){
    b++;
    if(b%num==0){
      displayBar();
    }
  }
  while(g>0){
    g--;
    if(g%num==0){
      displayBar();
    }
  }
  function dechex(dec) {
    var hex = dec.toString(16);
    if (hex.length == 1)
      hex = '0' + hex;
    return hex;
  }
  function zoomColor(hex) {
    $('#zoom').css('background-color', '#' + hex);
  }
  function displayBar() {
    var hex = dechex(r) + dechex(g) + dechex(b);
    //$('#picker').append('<div id="' + hex + '" style="float:left;background-color:#' + hex + ';width:1px;height:20px;" onMouseover="$(\'#all\').css(\'background-color\',\'#\'+$(this).attr(\'id\'));$(\'#hex\').html(\'#\'+$(this).attr(\'id\')+\'<br/>\');"></div>');
    $('#picker').append('<div id="' + hex + '" style="float:left;background-color:#' + hex + ';width:1px;height:20px;"></div>');
  }
}

function validarEmail(valor) {
  if (/^(([^<>()[\]\.,;:\s@\"]+(\.[^<>()[\]\.,;:\s@\"]+)*)|(\".+\"))@(([^<>()[\]\.,;:\s@\"]+\.)+[^<>()[\]\.,;:\s@\"]{2,})$/i.test(valor)){
   return false
  } else {
   return true
  }
}

Array.prototype.subarray=function(start,end){
     if(!end){ end=-1;} 
    return this.slice(start, this.length+1-(end*-1));
}

Array.prototype.remove = function() {
    var what, a = arguments, L = a.length, ax;
    while (L && this.length) {
        what = a[--L];
        while ((ax = this.indexOf(what)) !== -1) {
            this.splice(ax, 1);
        }
    }
    return this;
}
