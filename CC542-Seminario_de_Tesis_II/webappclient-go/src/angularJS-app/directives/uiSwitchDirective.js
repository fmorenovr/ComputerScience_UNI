'use strict'

/* ========================================================================
 * Switchery wrapper. credit: https://github.com/servergrove/NgSwitchery
 * ========================================================================
 */

/**
 * Module to use Switchery as a directive for angular.
 * @TODO implement Switchery as a service, https://github.com/abpetkov/switchery/pull/11
 * Flatlogic: encanced to load js script dynamically
 */
appDirectives.directive('uiSwitch', ['$window', '$timeout','$log', '$parse', 'scriptLoader', function($window, $timeout, $log, $parse, scriptLoader) {

    /**
     * Initializes the HTML element as a Switchery switch.
     *
     * @TODO add a way to provide options for Switchery
     * $timeout is in place as a workaround to work within angular-ui tabs.
     *
     * @param scope
     * @param elem
     * @param attrs
     */
    function linkSwitchery(scope, elem, attrs, ngModel) {
        if(!ngModel) return false;
        var options = {};
        try {
            options = $parse(attrs.uiSwitch)(scope);
        }
        catch (e) {}
        $timeout(function() {
            var switcher = new $window.Switchery(elem[0], options);
            var element = switcher.element;
            element.checked = scope.initValue;
            switcher.setPosition(false);
            element.addEventListener('change',function(evt) {
                scope.$apply(function() {
                    ngModel.$setViewValue(element.checked);
                })
            })
        }, 0);
    }
    return {
        require: 'ngModel',
        restrict: 'AE',
        scope : {initValue : '=ngModel'},
        link: function(scope, elem, attrs, ngModel){
            // sing part. was straight linkSwitchery call
            scriptLoader.loadScripts(['static/dependencies/node_modules/switchery/dist/switchery.min.js'])
                .then(function(){
                    linkSwitchery(scope, elem, attrs, ngModel)
                })
        }
    }
}]);

