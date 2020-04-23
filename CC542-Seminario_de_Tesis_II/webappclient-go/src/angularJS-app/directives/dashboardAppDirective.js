'use strict';

var appDirectives = angular.module('app.directives', []);

/**
 * Flatlogic comment:
 * Here goes an extension to jQuery Passthrough(http://angular-ui.github.io/ui-utils/) plugin.
 * Sing extension allows to dynamically load library used by ui-jq directive.
 * So for example in this case:
 * @example <input ui-jq="datepicker" ui-options="{showOn:'click'},secondParameter,thirdParameter" ui-refresh="iChange">
 *
 * datepicker library will be loaded dynamically and plugin initialization will take place only after datepicker exists
 * in jQuery scope.
 * There is a global value - uiJqDependencies which is defined in app.js. It's a map of jquery plugin name and it's dependencies.
 * It's also possible to pass dependencies via ui-preload attribute. See mapael example in index.html
 */
/**
 * General-purpose jQuery wrapper. Simply pass the plugin name as the expression.
 *
 * It is possible to specify a default set of parameters for each jQuery plugin.
 * Under the jq key, namespace each plugin by that which will be passed to ui-jq.
 * Unfortunately, at this time you can only pre-define the first parameter.
 * @example { jq : { datepicker : { showOn:'click' } } }
 *
 * @param ui-jq {string} The $elm.[pluginName]() to call.
 * @param [ui-options] {mixed} Expression to be evaluated and passed as options to the function
 *     Multiple parameters can be separated by commas
 * @param [ui-refresh] {expression} Watch expression and refire plugin on changes
 *
 * @example <input ui-jq="datepicker" ui-options="{showOn:'click'},secondParameter,thirdParameter" ui-refresh="iChange">
 */
angular.module('ui.jq',[]).
    value('uiJqConfig',{}).
    value('uiJqDependencies',{}).
    directive('uiJq', ['uiJqConfig', '$timeout', 'uiJqDependencies', 'scriptLoader',
        function uiJqInjectingFunction(uiJqConfig, $timeout, uiJqDependencies, scriptLoader) {

        return {
            restrict: 'A',
            compile: function uiJqCompilingFunction(tElm, tAttrs) {

                if (!(angular.isFunction(tElm[tAttrs.uiJq]) || angular.isArray(uiJqDependencies[tAttrs.uiJq]))) {
                    throw new Error('ui-jq: The "' + tAttrs.uiJq + '" function does not exist');
                }
                var options = uiJqConfig && uiJqConfig[tAttrs.uiJq];

                return function uiJqLinkingFunction(scope, elm, attrs) {

                    // If change compatibility is enabled, the form input's "change" event will trigger an "input" event
                    if (attrs.ngModel && elm.is('select,input,textarea')) {
                        elm.bind('change', function() {
                            elm.trigger('input');
                        });
                    }

                    // Call jQuery method and pass relevant options
                    function callPlugin() {
                        $timeout(function() {
                            var linkOptions = [];

                            // If ui-options are passed, merge (or override) them onto global defaults and pass to the jQuery method
                            if (attrs.uiOptions) {
                                linkOptions = scope.$eval('[' + attrs.uiOptions + ']');
                                if (angular.isObject(options) && angular.isObject(linkOptions[0])) {
                                    linkOptions[0] = angular.extend({}, options, linkOptions[0]);
                                }
                            } else if (options) {
                                linkOptions = [options];
                            }
                            elm[attrs.uiJq].apply(elm, linkOptions);
                        }, 0, false);
                    }

                    // If ui-refresh is used, re-fire the the method upon every change
                    if (attrs.uiRefresh) {
                        scope.$watch(attrs.uiRefresh, function() {
                            callPlugin();
                        });
                    }

                    // Sing addition. If there jQuery functions is defined, then just calling plugin
                    // if there is no jQuery function, then loading it first from uiJqDependencies object
                    // defined in app.js
                    var scriptsFromOptions = scope.$eval(tAttrs.uiPreload) || [];
                    if (angular.isFunction(tElm[tAttrs.uiJq])){
                        if (scriptsFromOptions.length > 0){
                            scriptLoader.loadScripts(scriptsFromOptions)
                                .then(callPlugin);
                        } else {
                            callPlugin();
                        }
                    } else {
                        var scriptsToLoad = uiJqDependencies[tAttrs.uiJq].concat(scriptsFromOptions);
                        scriptLoader.loadScripts(scriptsToLoad)
                            .then(callPlugin);
                    }
                };
            }
        };
    }]);
