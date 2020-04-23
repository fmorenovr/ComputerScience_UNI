'use strict';

/* ========================================================================
 * Skycon weather icons wrapper
 * ========================================================================
 */

appDirectives.directive('skyCon', ['scriptLoader', function(scriptLoader){
    return {
        link: function (scope, $el, attrs){
            function render(){
                var icons = new Skycons({"color": scope.$eval(attrs.color)});
                icons.set($el[0], attrs.skyCon);
                icons.play();
            }

            scriptLoader.loadScripts(['assets/dependencies/node_modules/skycons/skycons.js'])
                .then(render)
        }
    }
}]);

