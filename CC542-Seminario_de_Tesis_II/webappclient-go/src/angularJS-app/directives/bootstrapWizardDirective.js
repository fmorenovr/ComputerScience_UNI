'use strict'

/* ========================================================================
 * Bootstrap Wizard wrapper
 * ========================================================================
 */

appDirectives.directive('bootstrapWizard', ['scriptLoader', function(scriptLoader){
    return {
        link: function (scope, $el, attrs){

            function render(){
                $el.bootstrapWizard({
                    onTabShow: function($activeTab, $navigation, index) {
                        var $total = $navigation.find('li').length;
                        var $current = index + 1;
                        var $percent = ($current/$total) * 100;
                        var $wizard = $el;
                        $wizard.find('.progress-bar').css({width: $percent + '%'});

                        if($current >= $total) {
                            $wizard.find('.pager .next').hide();
                            $wizard.find('.pager .finish').show();
                            $wizard.find('.pager .finish').removeClass('disabled');
                        } else {
                            $wizard.find('.pager .next').show();
                            $wizard.find('.pager .finish').hide();
                        }

                        //setting done class
                        $navigation.find('li').removeClass('done');
                        $activeTab.prevAll().addClass('done');
                    },

                    // validate on tab change
                    onNext: function($activeTab, $navigation, nextIndex){
                        var $activeTabPane = $($activeTab.find('a[data-toggle=tab]').attr('href')),
                            $form = $activeTabPane.find('form');

                        // validate form in casa there is form
                        if ($form.length){
                            return $form.parsley().validate();
                        }
                    },
                    //diable tab clicking
                    onTabClick: function($activeTab, $navigation, currentIndex, clickedIndex){
                        return $navigation.find('li:eq(' + clickedIndex + ')').is('.done');
                    }
                });
                if (attrs.height){
                    //setting fixed height so wizard won't jump
                    $el.find('.tab-pane').css({height: attrs.height});
                }
            }

            scriptLoader.loadScripts([
                'assets/dependencies/node_modules/parsleyjs/dist/parsley.min.js',
                'assets/dependencies/node_modules/twitter-bootstrap-wizard/jquery.bootstrap.wizard.min.js'
            ])
                .then(render)
        }
    }
}]);


