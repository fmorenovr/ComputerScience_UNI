'use strict';

/* ========================================================================
 * Sing Chat Sidebar
 * ========================================================================
 * todo: rewrite in a more angulary way with models and controllers. This code may change in the next release
 */

appDirectives.directive('snChatSidebar', function($rootScope){
    return {
        link: function(scope, $el){
            //.chat-sidebar-container contains all needed styles so we don't pollute body{ }
            var $chatContainer = $('body').addClass('chat-sidebar-container');
            $rootScope.toggleChatSidebarState = function(){
                $chatContainer.toggleClass('chat-sidebar-opened');
            };

            /*
             * Open chat on swipe left but first check if navigation is collapsed
             * otherwise do nothing
             */
            $(document).on('swipeLeft','.content-wrap', function(e){
                if ($chatContainer.is('.nav-collapsed')){
                    $chatContainer.addClass('chat-sidebar-opened');
                }
            })
                /*
                 * Hide chat on swipe right but first check if navigation is collapsed
                 * otherwise do nothing
                 */
                .on('swipeRight', function(e){
                    if ($chatContainer.is('.nav-collapsed.chat-sidebar-opened')){
                        $chatContainer.removeClass('chat-sidebar-opened')
                            // as there is no way to cancel swipeLeft handlers attached to
                            // .content making this hack with temporary class which will be
                            // used by snNavigation directive to check whether it is permitted to open navigation
                            // on swipeRight
                            .addClass('nav-busy').one($.support.transition.end, function () {
                                $('body').removeClass('nav-busy');
                            }).emulateTransitionEnd(300);
                    }
                });

            /**
             * Show chat view when contact clicked
             */
            $el.on('click', '.chat-sidebar-user-group > a', function(){
                var $this = $(this),
                    $target = $($this.attr('href')),
                    $targetTitle = $target.find('.title');
                $this.removeClass('active').find('.badge').remove();
                $target.addClass('open');
                $el.find('.chat-sidebar-contacts').removeClass('open');
                $el.find('.chat-sidebar-footer').addClass('open');
                $el.find('.message-list', $target).slimscroll({
                    height: $target.height() - $targetTitle.height()
                        - parseInt($targetTitle.css('margin-top'))
                        - parseInt($targetTitle.css('margin-bottom')),
                    width: '',
                    size: '4px'
                });
                return false;
            });

            /**
             * Go back to contacts view when back clicked
             */
            $el.on('click', '.chat-sidebar-chat .js-back', function(){
                var $chat = $(this).closest('.chat-sidebar-chat').removeClass('open');
                var $sidebarContacts = $('.chat-sidebar-contacts').addClass('open');
                $el.find('.chat-sidebar-footer').removeClass('open');

                return false;
            });

            $el.find('[data-sn-chat-sidebar-input]').keyup(function(e){
                if(e.keyCode != 13) return;
                var val;
                if ((val = $(this).val().trim()) == '') return;

                var $currentMessageList = $el.find('.chat-sidebar-chat.open .message-list'),
                    $message = $('<li class="message from-me">' +
                        '<span class="thumb-sm"><img class="img-circle" src="img/avatar.png" alt="..."></span>' +
                        '<div class="message-body"></div>' +
                        '</li>');
                $message.appendTo($currentMessageList).find('.message-body').text(val);
                $(this).val('');
            });

            $el.find('[data-sn-chat-sidebar-search]').keyup(function(){
                var $contacts = $('.chat-sidebar-contacts.open'),
                    $chat = $('.chat-sidebar-chat.open'),
                    val = $(this).val().trim().toUpperCase();
                if ($contacts.length){
                    $('.chat-sidebar-user-group .list-group-item').addClass('hide').filter(function(){
                        return val == '' ? true : ($(this).find('.message-sender').text().toUpperCase().indexOf(val) != -1)
                    }).removeClass('hide');
                }
                if ($chat.length){
                    $('.chat-sidebar-chat.open .message-list .message').addClass('hide').filter(function(){
                        return val == '' ? true : ($(this).find('.message-body').text().toUpperCase().indexOf(val) != -1)
                    }).removeClass('hide');
                }
            });

            function initChatSidebarScroll(){
                var $sidebarContent = $('.chat-sidebar-contacts', $el);
                if ($el.find('.slimScrollDiv').length != 0){
                    $sidebarContent.slimscroll({
                        destroy: true
                    })
                }
                $sidebarContent.slimscroll({
                    height: window.innerHeight,
                    width: '',
                    size: '4px'
                });
            }

            $(window).on('sn:resize', initChatSidebarScroll);
            initChatSidebarScroll();
        }
    }
});
