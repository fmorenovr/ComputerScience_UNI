'use strict'

/* ========================================================================
 * Dropzone wrapper. credit: https://gist.github.com/compact/8118670
 * ========================================================================
 */
/**
 * An AngularJS directive for Dropzone.js, http://www.dropzonejs.com/
 *
 * Usage:
 *
 * <div ng-app="app" ng-controller="SomeCtrl">
 *   <button dropzone="dropzoneConfig">
 *     Drag and drop files here or click to upload
 *   </button>
 * </div>
 */

appDirectives.directive('dropzone', ['scriptLoader', function (scriptLoader) {
    return function (scope, element, attrs) {
        function render(){
            var config, dropzone;

            config = angular.extend({}, scope[attrs.dropzone]);

            // create a Dropzone for the element with the given options
            dropzone = new Dropzone(element[0], config.options);

            // bind the given event handlers
            angular.forEach(config.eventHandlers, function (handler, event) {
                dropzone.on(event, handler);
            });
        }

        scriptLoader.loadScripts(['assets/dependencies/node_modules/dropzone/dist/min/dropzone.min.js'])
            .then(render)
    };
}]);

