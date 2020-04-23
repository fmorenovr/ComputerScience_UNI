'use strict';

/* ========================================================================
 * Table head check all checkboxes
 * ========================================================================
 */
appDirectives.directive('checkAll', function(){
    return {
        restrict: 'A',
        link: function (scope, $el){
            $el.on('click', function() {
                $el.closest('table').find('input[type=checkbox]')
                    .not(this).prop('checked', $(this).prop('checked'));
            });
        }
    }
});
