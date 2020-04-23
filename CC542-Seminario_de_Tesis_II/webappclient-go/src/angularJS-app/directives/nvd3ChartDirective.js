'use strict'

/* ========================================================================
 * Nvd3 Chart wrapper.
 * ========================================================================
 * Simple self-written solution that requires controller to initialize chart & data.
 * If you're looking for full scale support of nvd3 options and more angulary way of
 * initializing nvd3 charts please check https://github.com/cmaurer/angularjs-nvd3-directives
 */

appDirectives.directive('nvd3Chart', ['scriptLoader', function(scriptLoader){
    return {
        link: function (scope, $el, attrs){
            function render(){
                nv.addGraph(function() {
                    var chart = scope[attrs.chart];
                    d3.select($el.find('svg')[0])
                        .style('height', attrs.height || '300px')
                        .datum(scope[attrs.datum])
                        .transition().duration(500)
                        .call(chart)
                    ;

                    $(window).on('sn:resize', chart.update);

                    return chart;
                });
            }

            scriptLoader.loadScripts([
                'assets/dependencies/node_modules/d3/d3.min.js',
                'assets/dependencies/node_modules/nvd3/build/nv.d3.min.js'
            ])
                .then(function(){
                    scope.$watch(attrs.datum, function(data, oldData){
                        if (!angular.isDefined(data)) return;
                        render();
                    })
                })
        }
    }
}]);

