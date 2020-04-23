'use strict'

/* ========================================================================
 * Live Tile directive
 * ========================================================================
 */

appDirectives.directive('liveTile', ['scriptLoader', function(scriptLoader){
    return {
        restrict: 'C',
        link: function (scope, $el, attrs){
            function render(){
                $el.css('height', attrs.height).liveTile();

                // remove onResize timeouts if present
                scope.$on('$stateChangeStart', function(){
                    $el.liveTile("destroy", true);
                });
            }

            scriptLoader.loadScripts(['assets/dependencies/node_modules/MetroJS/release/MetroJs.Full/MetroJs.js'])
                .then(render)
        }
    }
}]);


