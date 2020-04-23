'use strict'

/* ========================================================================
 * Animate Number jQuery plugin customized wrapper
 * ========================================================================
 */
appDirectives.directive('animateNumber', ['scriptLoader', function(scriptLoader){
    return {
        link: function (scope, $el){
            function render(){
                $el.animateNumber({
                    number: $el.text().replace(/ /gi, ''),
                    numberStep: $.animateNumber.numberStepFactories.separator(' '),
                    easing: 'easeInQuad'
                }, 1000);
            }

            scriptLoader.loadScripts(['assets/dependencies/node_modules/jquery-animateNumber/jquery.animateNumber.min.js'])
                .then(render)
        }
    }
}]);


