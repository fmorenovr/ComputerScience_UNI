'use strict'

/* ========================================================================
 * Morris Chart wrapper.
 * ========================================================================
 */

appDirectives.directive('morrisChart', ['scriptLoader', function(scriptLoader){
    return {
        link: function (scope, $el, attrs){
            function capitalise(string) {
                return string.charAt(0).toUpperCase() + string.slice(1).toLowerCase();
            }
            function render(){
                $el.css({height: attrs.height}); //safari svg height fix
                Morris[capitalise(attrs.type)](angular.extend({
                    element: $el[0]
                }, scope[attrs.options]));
            }

            scriptLoader.loadScripts([
                'assets/dependencies/node_modules/raphael/raphael-min.js',
                'assets/dependencies/node_modules/morris.js/morris.min.js'
            ])
                .then(function(){
                    scope.$watch(attrs.options, function(data){
                        if (!angular.isDefined(data)) return;
                        render();
                    })
                })
        }
    }
}]);

