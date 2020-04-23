'use strict'

appFilters.filter('decorate', ['decoration', function(decoration) {

  function decorateFilter(input) {
    return decoration.symbol + input + decoration.symbol;
  }
  decorateFilter.$stateful = true;

  return decorateFilter;
}])
