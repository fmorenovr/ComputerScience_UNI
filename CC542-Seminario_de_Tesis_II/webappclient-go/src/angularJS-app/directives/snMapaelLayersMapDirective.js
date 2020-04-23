'use strict'

/* ========================================================================
 * Mapael Layers Map
 * ========================================================================
 */

appDirectives.directive('snMapaelLayersMap', ['scriptLoader', function (scriptLoader) {
    return {
        require: 'ngModel',
        link: function (scope, $el, attrs, ngModel) {
            function render(){
                scope.$watch(attrs.ngModel, function(data, oldData){
                    if (!angular.isDefined(data)) return;
                    var $map = $el;
                    $map.css('height', attrs.height || 394).css('margin-bottom', attrs.marginBottom || (-15));
                    if ($map.parents('.widget')[0]){
                        $map.find('.map').css('height', parseInt($map.parents('.widget').css('height')) - 40);
                    }
                    $map.mapael(data);

                    if (scope[attrs.zoom]){
                        $map.trigger('zoom', scope[attrs.zoom]);
                    }

                    scope.$map = $map;
                })
            }

            scriptLoader.loadScripts([
                'assets/dependencies/node_modules/raphael/raphael-min.js',
                'assets/dependencies/node_modules/jQuery-Mapael/js/jquery.mapael.js',
                'assets/dependencies/node_modules/jQuery-Mapael/js/maps/world_countries.js'
            ])
                .then(render)
        }
    }
}]);


