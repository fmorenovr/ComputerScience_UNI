'use strict';

var appValues = angular.module('app.values', []);

/*

Values: are great for pieces of data that can and will change. As shown above user data or anything else where you simply want to keep a reference to a changing value stored globally without creating a messy global variable.

Value differs from constant in that value can not be injected into configurations, but it can be intercepted by decorators.

*/
