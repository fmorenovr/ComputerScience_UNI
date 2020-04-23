'use strict';

/* ========================================================================
 * Widgster Wrapper. Triggered for all .widget's
 * ========================================================================
 */

appDirectives.directive('widget', function(){
    /**
     * Setting Widgster's body selector to theme specific
     * @type {string}
     */
    $.fn.widgster.Constructor.DEFAULTS.bodySelector = '.widget-body';

    /*
     When widget is closed remove its parent if it is .col-*
     */
    $(document).on('close.widgster', function(e){
        var $colWrap = $(e.target).closest('.content > .row > [class*="col-"]:not(.widget-container)');

        // remove colWrap only if there are no more widgets inside
        if (!$colWrap.find('.widget').not(e.target).length){
            $colWrap.remove();
        }
    });
    return {
        restrict: 'CEA',
        link: function(scope, $el, attrs){
            if (attrs.postProcessing == 'true') return;
            $el.widgster();
        }
    }
});
