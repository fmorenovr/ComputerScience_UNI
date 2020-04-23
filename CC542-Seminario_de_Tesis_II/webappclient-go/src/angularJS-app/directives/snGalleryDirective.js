'use strict'

appDirectives.directive('snGallery', ['$timeout', 'scriptLoader', function($timeout, scriptLoader){
    return {
        link: function(scope, $el, attrs){
            function render(){
                var $sizer = $el.find('.js-shuffle-sizer');

                $timeout(function() {
                    // instantiate the plugin
                    $el.shuffle(angular.extend({ sizer: $sizer }, scope.$eval(attrs.options)));
                    $timeout(function(){
                        $el.shuffle( 'shuffle', 'all' );
                    })
                });

                $(window).on('sn:resize', function(){
                    $el.shuffle('update');
                });

                scope.$grid = $el;
            }

            scriptLoader.loadScripts(['assets/dependencies/node_modules/shufflejs/dist/jquery.shuffle.modernizr.min.js'])
                .then(render)
        }
    }
}]);
