'use strict';

/* ========================================================================
 * Animate Progress Bars
 * ========================================================================
 */
appDirectives.directive('snProgressAnimate', ['$timeout', function($timeout){
    return {
        link: function (scope, $el){
            var value = $el.data('value'),
                $bar = $el.find('.progress-bar');
            $bar.css('opacity', 0);
            $timeout(function(){
                $bar.css({
                    transition: 'none',
                    width: 0,
                    opacity: 1
                });
                $timeout(function(){
                    $bar.css('transition', '').css('width', value + '%');
                })
            })
        }
    }
}]);
