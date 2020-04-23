'use strict'

/**
 * Prevent default links behaviour so it won't cause unwanted url changes for angular
 */
appDirectives.directive('body', function() {
    return {
        restrict: 'E',
        link: function(scope, $element) {
            // prevent unwanted navigation
            $element.on('click', 'a[href=#]', function(e) {
                e.preventDefault();
            })
        }
    }
});
