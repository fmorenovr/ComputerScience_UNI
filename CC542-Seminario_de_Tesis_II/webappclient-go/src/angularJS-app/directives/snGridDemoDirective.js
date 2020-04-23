'use strict'

/**
 * Demo Sign directives. Is not a core Sign framework and may be removed if not needed.
 */

appDirectives.directive('snGridDemo', ['scriptLoader', function(scriptLoader){
    return {
        link: function(scope, $el){
            function render(){
                var $widgets = $('.widget'),
                    $newsWidget = $('#news-widget'),
                    $sharesWidget = $('#shares-widget'),
                    $autoloadWidget = $('#autoload-widget');

                /**
                 * turn off .content-wrap transforms & disable sorting when widget fullscreened
                 */
                $widgets.on("fullscreen.widgster", function(){
                    $('.content-wrap').css({
                        '-webkit-transform': 'none',
                        '-ms-transform': 'none',
                        transform: 'none',
                        'margin': 0,
                        'z-index': 2
                    });
                    //prevent widget from dragging when fullscreened
                    $(".widget-container").sortable( "option", "disabled", true );
                }).on("restore.widgster closed.widgster", function(){
                    $('.content-wrap').css({
                        '-webkit-transform': '',
                        '-ms-transform': '',
                        transform: '',
                        margin: '',
                        'z-index': ''
                    });
                    //allow dragging back
                    $(".widget-container").sortable( "option", "disabled", false );
                });

                /**
                 * Make refresh button spin when loading
                 */
                $newsWidget.on("load.widgster", function(){
                    $(this).find('[data-widgster="load"] > i').addClass('fa-spin')
                }).on("loaded.widgster", function(){
                    $(this).find('[data-widgster="load"] > i').removeClass('fa-spin')
                });

                /**
                 * Custom close prompt for news widget
                 */
                $newsWidget.widgster({
                    showLoader: false,
                    closePrompt: function(callback){
                        $('#news-close-modal').modal('show');
                        $('#news-widget-remove').on('click', function(){
                            $('#news-close-modal').on('hidden.bs.modal', callback).modal('hide');
                        });
                    }
                });

                /**
                 * Use custom loader template
                 */
                $sharesWidget.widgster({
                    loaderTemplate: '<div class="loader animated fadeIn">' +
                        '   <span class="spinner"><i class="fa fa-spinner fa-spin"></i></span>' +
                        '</div>'
                });

                /**
                 * Make hidden spinner appear & spin when loading
                 */
                $autoloadWidget.on("load.widgster", function(){
                    $(this).find('.fa-spinner').addClass('fa-spin in');
                }).on("loaded.widgster", function(){
                    $(this).find('.fa-spinner').removeClass('fa-spin in')
                }).on('load.widgster fullscreen.widgster restore.widgster', function(){
                    $(this).find('.dropdown.open > .dropdown-toggle').dropdown('toggle');
                });

                /**
                 * Init all other widgets with default settings & settings retrieved from data-* attributes
                 */
                $widgets.widgster();

                /**
                 * Init tooltips for all widget controls on page
                 */
                $('.widget-controls > a').tooltip({placement: 'bottom'});
            }

            scriptLoader.loadScripts([
                'assets/dependencies/node_modules/jquery-ui/ui/core.js',
                'assets/dependencies/node_modules/jquery-ui/ui/widget.js',
                'assets/dependencies/node_modules/jquery-ui/ui/mouse.js',
                'assets/dependencies/node_modules/jquery-ui/ui/sortable.js',
                'assets/dependencies/node_modules/jquery-ui-touch-punch/jquery.ui.touch-punch.min.js'
            ])
                .then(render);
        }
    }
}]);


