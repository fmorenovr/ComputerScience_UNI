'use strict';

/* ========================================================================
 * Sing App actions. Shortcuts available via data-sn-action attribute
 * ========================================================================
 */
appDirectives.directive('snAction', function($rootScope){
    var singActions = {
        'toggle-navigation-state': function(e, scope){
            scope.app.state['nav-static'] = !scope.app.state['nav-static'];
        },
        'toggle-navigation-collapse-state': function(e, scope){
            $rootScope.toggleNavigationCollapseState();
        },
        'toggle-chat-sidebar-state': function(){
            //remove notification sign on a first click
            $(this).find('.chat-notification-sing').remove();
            $rootScope.toggleChatSidebarState();


            //todo demo-only stuff. TO-REMOVE in real app!
            setTimeout(function(){
                // demo: add class & badge to indicate incoming messages from contact
                // .js-notification-added ensures notification added only once
                $('.chat-sidebar-user-group:first-of-type .list-group-item:first-child:not(.js-notification-added)').addClass('active js-notification-added')
                    .find('.fa-circle').after('<span class="badge badge-danger pull-right animated bounceInDown">3</span>');
            }, 1000)
        }
    };
    return {
        restrict: 'A',
        link: function (scope, $el, attrs){
            if (angular.isDefined(attrs.snAction) && attrs.snAction != '') {
                $el.on('click', function(e) {
                    scope.$apply(function(){
                        singActions[attrs.snAction].call($el[0], e, scope);
                    });
                    e.preventDefault();
                });
            }

            if (angular.isDefined(attrs.tooltip) && attrs.snAction != ''){
                $el.tooltip();
            }
        }
    }
});
