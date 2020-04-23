'use strict';

/* ========================================================================
 * Handle transparent input groups focus
 * ========================================================================
 */
appDirectives.directive('inputGroupTransparent', function(){
    return {
        restrict: 'C',
        link: function (scope, el){
            $(el).find('.input-group-addon + .form-control').on('blur focus', function(e){
                $(this).parents('.input-group')[e.type=='focus' ? 'addClass' : 'removeClass']('focus');
            });
        }
    }
});
