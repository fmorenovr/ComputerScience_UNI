'use strict';

/* ========================================================================
 * Sing App Navigation (Sidebar)
 * ========================================================================
 */
appDirectives.directive('snNavigation', function($timeout, $rootScope, $state){
    var SnNavigationDirective = function($el, scope){
        this.$el = $el;
        this.scope = scope;
        this.helpers = scope.app.helpers;

        // publish method to global scope to allow navigation collapsing via api
        $rootScope.toggleNavigationCollapseState = $.proxy(this.toggleNavigationCollapseState, this);
    };
    SnNavigationDirective.prototype = { // a set of reusable directive private functions
        expandNavigation: function(){
            //this method only makes sense for non-static navigation state
            if (this.isNavigationStatic() && (this.helpers.isScreen('md') || this.helpers.isScreen('lg'))) return;

            $('body').removeClass('nav-collapsed');
            this.$el.find('.active .active').closest('.collapse').collapse('show')
                .siblings('[data-toggle=collapse]').removeClass('collapsed');
        },

        collapseNavigation: function(){
            //this method only makes sense for non-static navigation state
            if (this.isNavigationStatic() && (this.helpers.isScreen('md') || this.helpers.isScreen('lg'))) return;

            $('body').addClass('nav-collapsed');
            this.$el.find('.collapse.in').collapse('hide')
                .siblings('[data-toggle=collapse]').addClass('collapsed');
        },


        /**
         * Check and set navigation collapse according to screen size and navigation state
         */
        checkNavigationState: function(){
            if (this.isNavigationStatic()){
                if (this.helpers.isScreen('sm') || this.helpers.isScreen('xs')){
                    this.collapseNavigation();
                }
            } else {
                if (this.helpers.isScreen('md') || this.helpers.isScreen('lg')){
                    var view = this;
                    $timeout(function(){
                        view.collapseNavigation();
                    }, this.scope.app.settings.navCollapseTimeout);
                } else {
                    this.collapseNavigation();
                }
            }
        },

        isNavigationStatic: function(){
            return this.scope.app.state['nav-static'] === true;
        },

        changeActiveNavigationItem: function(event, toState, toParams){
            var $newActiveLink = this.$el.find('a[href="' + $state.href(toState, toParams) + '"]');

            // collapse .collapse only if new and old active links belong to different .collapse
            if (!$newActiveLink.is('.active > .collapse > li > a')){
                this.$el.find('.active .active').closest('.collapse').collapse('hide');
            }
            this.$el.find('.sidebar-nav .active').removeClass('active');

            $newActiveLink.closest('li').addClass('active')
                .parents('li').addClass('active');

            // uncollapse parent
            $newActiveLink.closest('.collapse').addClass('in').siblings('a[data-toggle=collapse]').removeClass('collapsed');
        },

        toggleNavigationCollapseState: function(){
            if ($('body').is('.nav-collapsed')){
                this.expandNavigation();
            } else {
                this.collapseNavigation();
            }
        },

        enableSwipeCollapsing: function(){
            var d = this;
            $('.content-wrap').swipe({
                swipeLeft: function(){
                    //this method only makes sense for small screens + ipad
                    if (d.helpers.isScreen('lg')) return;

                    if (!$('body').is('.nav-collapsed')){
                        d.collapseNavigation();
                    }
                },
                swipeRight: function(){
                    //this method only makes sense for small screens + ipad
                    if (d.helpers.isScreen('lg')) return;

                    // check if navigation is collapsing. exiting if true
                    if ($('body').is('.nav-busy')) return;

                    if ($('body').is('.nav-collapsed')){
                        d.expandNavigation();
                    }
                },
                threshold: this.helpers.isScreen('xs') ? 100 : 200
            });
        },

        collapseNavIfSmallScreen: function(){
            if (this.helpers.isScreen('xs') || this.helpers.isScreen('sm')){
                this.collapseNavigation();
            }
        },

        _sidebarMouseEnter: function(){
            if (this.helpers.isScreen('md') || this.helpers.isScreen('lg')){
                this.expandNavigation();
            }
        },
        _sidebarMouseLeave: function(){
            if (this.helpers.isScreen('md') || this.helpers.isScreen('lg')){
                this.collapseNavigation();
            }
        }
    };
    return {
        link: function (scope, $el){
            var d = new SnNavigationDirective($el, scope);

            $el.on('mouseenter', $.proxy(d._sidebarMouseEnter, d));
            $el.on('mouseleave', $.proxy(d._sidebarMouseLeave, d));

            // wait untill all includes included
            $timeout(function(){
                // set active navigation item
                d.changeActiveNavigationItem({}, $state.$current, $state.params);

                d.checkNavigationState();
            });

            /**
             * open navigation if collapsed sidebar clicked
             */
            $el.on('click', function(){
                if ($('body').is('.nav-collapsed')){
                    d.expandNavigation();
                }
            });

            scope.$watch('app.state["nav-static"]', function(newVal, oldVal){
                if (newVal == oldVal) return; // shouldn't they fix it?
                if (!newVal){ // if navigation state is collapsing
                    d.collapseNavigation();
                }

                // let angular finish doing its stuff so all animation are applied to trigger an event on a ready DOM
                $timeout(function(){
                    $(window).trigger('sn:resize');
                })
            });

            // change active navigation item when state change
            $rootScope.$on('$stateChangeStart', $.proxy(d.changeActiveNavigationItem, d));
            $rootScope.$on('$stateChangeSuccess', $.proxy(d.collapseNavIfSmallScreen, d));

            // scroll to top manually after page change. seems that it doesn't work out of the box because
            // the actual app state is not changed - it remain app.page - only params changed.
            $rootScope.$on('$stateChangeSuccess', function(){
                window.scrollTo(0, 0);
            });

            // enable swipe navigation collapsing
            ('ontouchstart' in window) && d.enableSwipeCollapsing();

            /* reimplementing bs.collapse data-parent here as we don't want to use BS .panel*/
            $el.find('.collapse').on('show.bs.collapse', function(e){
                // execute only if we're actually the .collapse element initiated event
                // return for bubbled events
                if (e.target != e.currentTarget) return;

                var $triggerLink = $(this).prev('[data-toggle=collapse]');
                $($triggerLink.data('parent')).find('.collapse.in').not($(this)).collapse('hide');
            })
                /* adding additional classes to navigation link li-parent for several purposes. see navigation styles */
                .on('show.bs.collapse', function(e){
                    // execute only if we're actually the .collapse element initiated event
                    // return for bubbled events
                    if (e.target != e.currentTarget) return;

                    $(this).closest('li').addClass('open');
                }).on('hide.bs.collapse', function(e){
                    // execute only if we're actually the .collapse element initiated event
                    // return for bubbled events
                    if (e.target != e.currentTarget) return;

                    $(this).closest('li').removeClass('open');
                });

            function initSidebarScroll(){
                var $sidebarContent = $el.find('.js-sidebar-content');
                if ($el.find('.slimScrollDiv').length != 0){
                    $sidebarContent.slimscroll({
                        destroy: true
                    })
                }
                $sidebarContent.slimscroll({
                    height: window.innerHeight,
                    size: '4px'
                });
            }

            $(window).on('sn:resize', initSidebarScroll);
            initSidebarScroll();
        }
    }
});
