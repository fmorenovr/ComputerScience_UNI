'use strict'

/**
 * Gmap initialization requires to load scripts asynchronously
 */
appDirectives.directive('snGmap', ['$rootScope', 'Consultas' , function($rootScope, Consultas){
/*
    if (!angular.isDefined(window.GMaps)){
        // loading google maps synamically to be able to use their callback method
        var script = document.createElement('script');
        script.type = 'text/javascript';
        script.src = 'https://maps.googleapis.com/maps/api/js?key=&libraries=visualization&sensor=true&callback=googleMapsLoaded';
        document.body.appendChild(script);

        // a small trick to ensure google api was loaded
        // googleMapsLoaded function gets called by google script script after
        $rootScope.gmapsLoaded = false;
        window.googleMapsLoaded = function(){
            var script = document.createElement('script');
            script.type = 'text/javascript';
            script.src = 'assets/dependencies/node_modules/gmaps/gmaps.js';
            script.onload = function(){
                $rootScope.$apply(function(){
                    $rootScope.gmapsLoaded = true;
                })
            };
            document.body.appendChild(script);
        };
    }
*/
    return {
        link: function(scope, $el, attrs){
            function render(){
              var map = new GMaps({
                el: $el[0],
                lat: -12.0166427,
                lng: -77.0499641,
                zoom: 17,
                mapTypeId: 'terrain',//'hybrid',
                zoomControl : false,
                panControl : false,
                streetViewControl : false,
                mapTypeControl: false,
                overviewMapControl: false
              });
              /*
              if (attrs.contextMenu){
                map.setContextMenu({
                  control: 'map',
                  options: [{
                    title: 'Add marker',
                    name: 'add_marker',
                    action: function(e){
                      this.addMarker({
                        lat: e.latLng.lat(),
                        lng: e.latLng.lng(),
                        animation: google.maps.Animation.DROP,
                        draggable:true,
                        title: 'New Marker'
                      });
                      this.hideContextMenu();
                    }
                  }, {
                    title: 'Center here',
                    name: 'center_here',
                    action: function(e){
                      this.setCenter(e.latLng.lat(), e.latLng.lng());
                    }
                  }]
                });
                map.setContextMenu({
                  control: 'marker',
                  options: [{
                    title: 'Center here',
                    name: 'center_here',
                    action: function(e){
                      this.setCenter(e.latLng.lat(), e.latLng.lng());
                    }
                  }]
                });
              }*/

              $("[data-gmap-zoom-in]").on('click', function() {
                map.zoomIn(1);
              });
              $("[data-gmap-zoom-out]").on('click', function() {
                map.zoomOut(1);
              });

              setTimeout( function(){
                var markers = [];
                var sensores = [];
                var auxSensores = "";
                var poligono = [];
                var polig = [];
                var contentString,contentSensores;
                Consultas.getCansatsLocation().then(function(dataResponse){
                  if (dataResponse != null){
                    markers = dataResponse;
                    angular.forEach(markers, function (value, key) {
                      poligono = []
                      auxSensores = "";
                      contentString = "";
                      contentSensores = "";
                      angular.forEach(value.sensores, function (valuesens, key) {
                        auxSensores = auxSensores + '<li>'+valuesens.type+'</li>';
                      });
                      angular.forEach(value.polygonos, function (valuepol, key) {
                        poligono.push([ valuepol.latitude, valuepol.longuitude ])
                      });
                      contentSensores = '<ul>'+auxSensores + '</ul>';
                      contentString = '<div>'+
                        '<b>IoTDevice</b><br>'+
                        'Id: '+value.id+'<br/>'+
                        'Lat: '+value.pos[0]+'<br/>'+
                        'Lon: '+value.pos[1]+'<br/>'+
                        'Zone: '+value.zona+'<br/>'+
                        'Sector: '+value.sector+'<br/>'+
                        'Lista de sensores: <br/>'+
                        contentSensores +
                        '</div>';
                      map.addMarker({
                        lat: value.pos[0],
                        lng: value.pos[1],
                        animation: google.maps.Animation.DROP,
                        draggable: false,
                        title: value.id,
                        click: function(e) {
                          //alert('You clicked in this marker');
                        },
                        infoWindow: {
                          content: contentString
                        }
                      })
                      map.drawPolygon({
                        paths: poligono,
                        strokeColor: '#5858FA',
                        strokeOpacity: 1,
                        strokeWeight: 3,
                        fillColor: '#0489B1',
                        fillOpacity: 0.6
                      });
                    });
                  }
                });
              }, 2000);
            }
            if ($rootScope.gmapsLoaded || angular.isDefined(window.GMaps)){
              render()
            } else {
              $rootScope.$watch('gmapsLoaded', function(val){
                (val == true) && render();
              });
            }
        }
    }
}]);

