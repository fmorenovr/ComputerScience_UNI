'use strict'

/* ========================================================================
 * Bootstrap calendar predefined wrapper
 * ========================================================================
 */

appDirectives.directive('bootstrapCalendar', ['scriptLoader',function(scriptLoader){
    return {
        restrict: 'A',
        link: function(scope, $el, attrs){
            function render(){
                var monthNames = ["January", "February", "March", "April", "May", "June",  "July", "August", "September", "October", "November", "December"];

                var dayNames = ["S", "M", "T", "W", "T", "F", "S"];

                var events = scope.$eval(attrs.events);
                var $calendar = $el;
                $calendar.calendar({
                    months: monthNames,
                    days: dayNames,
                    events: events,
                    popover_options:{
                        placement: 'top',
                        html: true
                    }
                });
                $calendar.find('.icon-arrow-left').addClass('fa fa-arrow-left');
                $calendar.find('.icon-arrow-right').addClass('fa fa-arrow-right');
                function restyleCalendar(){
                    $calendar.find('.event').each(function(){
                        var $this = $(this),
                            $eventIndicator = $('<span></span>');
                        $eventIndicator.css('background-color', $this.css('background-color')).appendTo($this.find('a'));
                        $this.css('background-color', '');
                    })
                }
                $calendar.find('.icon-arrow-left, .icon-arrow-right').parent().on('click', restyleCalendar);
                restyleCalendar();
            }

            scriptLoader.loadScripts([
                'assets/dependencies/node_modules/bootstrap_calendar/bootstrap_calendar/js/bootstrap_calendar.min.js'
            ])
                .then(function(){
                    attrs.$observe('events', function(){
                        render();
                    })
                })
        }
    }
}]);

