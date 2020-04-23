'use strict'

/* ========================================================================
 * Flot Animator Chart wrapper
 * ========================================================================
 */

appDirectives.directive('flotChartAnimator', ['scriptLoader', function(scriptLoader){
    return {
        link: function (scope, $el, attrs){
            function render(){
                $.plotAnimator($el, scope[attrs.ngModel],{
                    xaxis: {
                        tickLength: 0,
                        tickDecimals: 0,
                        min:2,
                        font :{
                            lineHeight: 13,
                            weight: "bold",
                            color: scope.app.settings.colors['gray-semi-light']
                        }
                    },
                    yaxis: {
                        tickDecimals: 0,
                        tickColor: "#f3f3f3",
                        font :{
                            lineHeight: 13,
                            weight: "bold",
                            color: scope.app.settings.colors['gray-semi-light']
                        }
                    },
                    grid: {
                        backgroundColor: { colors: [ "#fff", "#fff" ] },
                        borderWidth:1,
                        borderColor:"#f0f0f0",
                        margin:0,
                        minBorderMargin:0,
                        labelMargin:20,
                        hoverable: true,
                        clickable: true,
                        mouseActiveRadius:6
                    },
                    legend: false
                });
            }

            scriptLoader.loadScripts([
                'assets/dependencies/node_modules/flot.animator/jquery.flot.animator.min.js',
                'assets/dependencies/node_modules/flot/jquery.flot.js'
            ])
                .then(function(){
                    scope.$watch(attrs.ngModel, function(data, oldData){
                        if (!angular.isDefined(data)) return;
                        render();
                        $(window).on('sn:resize', render);
                    })
                })
        }
    }
}]);


