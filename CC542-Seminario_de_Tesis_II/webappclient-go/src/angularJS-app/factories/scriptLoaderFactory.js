'use strict'

/**
 * Sing Script loader. Loads script tags asynchronously and in order defined in a page
 */
appFactories.factory('scriptLoader', ['$q', '$timeout', function($q, $timeout) {
  var processedScripts = [];
  return {
    /**
     * Parses 'data' in order to find & execute script tags asynchronously as defined.
     * Called for partial views.
     * @param data
     * @returns {*} promise that will be resolved when all scripts are loaded
     */
    loadScriptTagsFromData: function(data) {
      var deferred = $q.defer();
      var $contents = $($.parseHTML(data, document, true)),
          $scripts = $contents.filter('script[data-src][type="text/javascript-lazy"]').add($contents.find('script[data-src][type="text/javascript-lazy"]')),
          scriptLoader = this;

      scriptLoader.loadScripts($scripts.map(function(){ return $(this).attr('data-src')}).get())
          .then(function(){
              deferred.resolve(data);
          });

      return deferred.promise;
    },
      /**
       * Sequentially and asynchronously loads scripts (without blocking) if not already loaded
       * @param scripts an array of url to create script tags from
       * @returns {*} promise that will be resolved when all scripts are loaded
       */
      loadScripts: function(scripts) {
        var previousDefer = $q.defer();
        previousDefer.resolve();
        scripts.forEach(function(script){
          if (processedScripts[script]){
            if (processedScripts[script].processing){
              previousDefer = processedScripts[script];
            }
            return
          }

          var scriptTag = document.createElement('script'),
              $scriptTag = $(scriptTag),
              defer = $q.defer();
          scriptTag.src = script;
          defer.processing = true;

          $scriptTag.load(function(){
            $timeout(function(){
              defer.resolve();
              defer.processing = false;
              Pace.restart();
            })
          });
          previousDefer.promise.then(function(){
            document.body.appendChild(scriptTag);
          });
          processedScripts[script] = previousDefer = defer;
        });
        return previousDefer.promise;
      }
  }
}]);
