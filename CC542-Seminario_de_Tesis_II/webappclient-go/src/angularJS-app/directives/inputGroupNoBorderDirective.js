'use strict';

/* ========================================================================
 * Handle no-border input groups focus
 * ========================================================================
 */
appDirectives.directive('inputGroupNoBorder', function(){
    return {
        restrict: 'C',
        link: function (scope, el){
            $(el).find('.input-group-addon + .form-control').on('blur focus', function(e){
                $(this).parents('.input-group')[e.type=='focus' ? 'addClass' : 'removeClass']('focus');
            });
        }
    }
});
