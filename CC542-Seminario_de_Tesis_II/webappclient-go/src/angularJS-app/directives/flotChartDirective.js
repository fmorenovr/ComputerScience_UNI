'use strict'

/* ========================================================================
 * Flot Chart wrapper
 * ========================================================================
 */

appDirectives.directive('flotChart', ['scriptLoader', '$timeout', function(scriptLoader, $timeout){
    return {
        link: function (scope, $el, attrs){
            function render(){
                $.plot($el, scope[attrs.ngModel], scope[attrs.options] || {
                    series: {
                        lines: {
                            show: true,
                            lineWidth: 1,
                            fill: false,
                            fillColor: { colors: [{ opacity: .001 }, { opacity: .5}] }
                        },
                        points: {
                            show: false,
                            fill: true
                        },
                        shadowSize: 0
                    },
                    legend: false,
                    grid: {
                        show:false,
                        margin: 0,
                        labelMargin: 0,
                        axisMargin: 0,
                        hoverable: true,
                        clickable: true,
                        tickColor: "rgba(255,255,255,1)",
                        borderWidth: 0
                    }
                });
            }

            var coreScripts = ['assets/dependencies/node_modules/flot/jquery.flot.js'],
                flotPlugins = scope.$eval(attrs.plugins) || [],
                scriptsToLoad = coreScripts.concat(flotPlugins);
            scriptLoader.loadScripts(scriptsToLoad)
                .then(function(){
                    scope.$watch(attrs.ngModel, function(data, oldData){
                        if (!angular.isDefined(data)) return;
                        render();
                        $(window).on('sn:resize', function(){
                            $timeout(render);
                        });
                    })
                })
        }
    }
}]);


