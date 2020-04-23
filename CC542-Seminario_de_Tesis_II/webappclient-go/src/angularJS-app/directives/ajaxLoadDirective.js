'use strict'

/* ========================================================================
 * Ajax Load micro-plugin
 * ========================================================================
 */

appDirectives.directive('ajaxLoad', function(){
    return {
        restrict: 'A',
        link: function(scope, $el, attrs){
            $el.on('click change', function(e){
                var $this = $(this),
                    $target = $($this.data('ajax-target'));
                if ($target.length > 0 ){
                    e = $.Event('ajax-load:start', {originalEvent: e});
                    $this.trigger(e);

                    !e.isDefaultPrevented() && $target.load($this.data('ajax-load'), function(){
                        $this.trigger('ajax-load:end');
                    });
                }
                return false;
            });

            /**
             * Change to loading state if loading text present
             */
            if (attrs.loadingText){
                $el.on('ajax-load:start', function (e) {
                    $el.button('loading');
                });
                $el.on('ajax-load:end', function () {
                    $el.button('reset');
                });
            }

            $(document).on('click', '[data-toggle^=button]', function (e) {
                return $(e.target).find('input').data('ajax-trigger') != 'change';
            });
        }
    }
});
