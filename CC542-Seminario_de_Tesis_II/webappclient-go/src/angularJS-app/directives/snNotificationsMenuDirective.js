'use strict';

/* ========================================================================
 * Sing Notifications Menu. Moved to a sidebar for small screens
 * ========================================================================
 */
appDirectives.directive('snNotificationsMenu', function($rootScope){
    return {
        link: function(scope, $el){
            /**
             * Move notifications dropdown to sidebar when/if screen is xs
             * and back when leaves xs
             */
            function moveNotificationsDropdown(){
                // todo extract selectors to scope attributes probably for more flexibility?
                $('.sidebar-status .dropdown-toggle').after($el.detach());
            }

            function moveBackNotificationsDropdown(){
                $('#notifications-dropdown-toggle').after($el.detach());
            }
            scope.app.helpers.onScreenSize('xs', moveNotificationsDropdown);
            scope.app.helpers.onScreenSize('xs', moveBackNotificationsDropdown, false);

            scope.app.helpers.isScreen('xs') && moveNotificationsDropdown();

            /**
             * Set Sidebar zindex higher than .content and .page-controls so the notifications dropdown is seen
             */
            $('.sidebar-status').on('show.bs.dropdown', function(){
                $('#sidebar').css('z-index', 2);
            }).on('hidden.bs.dropdown', function(){
                $('#sidebar').css('z-index', '');
            });
        }
    }
});
