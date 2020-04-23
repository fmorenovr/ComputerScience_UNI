'use strict';

/* ========================================================================
 * Sing Demo functions directive. Demo-only functions. Does not affect the core Sing functionality.
 * Should be removed when used in real app.
 * ========================================================================
 */
appDirectives.directive('snDemo', function($rootScope){
    return {
        link: function(scope, $el){
            $(document).on('ajax-load:end', '#load-notifications-btn', function () {
                setTimeout(function(){
                    $('#notifications-list').find('.bg-attention').removeClass('bg-attention');
                }, 10000)
            });
            $(document).on('ajax-load:end', '#notifications-toggle input', function(){
                $('#notifications-list').find('[data-toggle=tooltip]').tooltip();
            });

            setTimeout(function(){
                var $chatNotification = $('#chat-notification');
                $chatNotification.removeClass('hide').addClass('animated fadeIn')
                    .one('webkitAnimationEnd mozAnimationEnd MSAnimationEnd oanimationend animationend', function(){
                        $chatNotification.removeClass('animated fadeIn');
                        setTimeout(function(){
                            $chatNotification.addClass('animated fadeOut')
                                .one('webkitAnimationEnd mozAnimationEnd MSAnimationEnd oanimationend animationend', function(){
                                    $chatNotification.addClass('hide');
                                });
                        }, 4000);
                    });
                $chatNotification.siblings('[data-sn-action="toggle-chat-sidebar-state"]').append('<i class="chat-notification-sing animated bounceIn"></i>')
            }, 4000)
        }
    }
});

