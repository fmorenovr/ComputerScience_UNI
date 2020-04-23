// jQuery to collapse the navbar on scroll
function collapseNavbar() {
  if ($(".navbar").offset().top > 50) {
    $(".navbar-fixed-top").addClass("top-nav-collapse");
  } else {
    $(".navbar-fixed-top").removeClass("top-nav-collapse");
  }
}

$(window).scroll(collapseNavbar);
$(document).ready(collapseNavbar);

// jQuery for page scrolling feature - requires jQuery Easing plugin
$(function() {
  $('a.page-scroll').bind('click', function(event) {
    var $anchor = $(this);
    $('html, body').stop().animate({
      scrollTop: $($anchor.attr('href')).offset().top
    }, 1500, 'easeInOutExpo');
    event.preventDefault();
  });
});

// Closes the Responsive Menu on Menu Item Click
$('.navbar-collapse ul li a').click(function() {
  $(this).closest('.collapse').collapse('toggle');
});

var officeGPS = [-12.0166427,-77.0499641]
var officeName = "SmartCity Lab"
var officeURL = "http://smartcityperu.org"

// Google Maps Scripts
var map = null;
// When the window has finished loading create our google map below
google.maps.event.addDomListener(window, 'load', init);
google.maps.event.addDomListener(window, 'resize', function() {
  map.setCenter(new google.maps.LatLng(officeGPS[0], officeGPS[1]));
});
var beachMarker, infowindow;
function viewSensor() {
  infowindow.open(map, beachMarker);
}
function init() {
  var mapOptions = {
    zoom: 16,
    center: new google.maps.LatLng(officeGPS[0], officeGPS[1]),
    // Disables the default Google Maps UI components
    disableDefaultUI: true,
    scrollwheel: false,
    draggable: true,
    styles: [{
      "featureType": "water",
      "elementType": "geometry",
      "stylers": [{
          "color": "#000000"
      }, {
          "lightness": 17
      }]
    }, {
      "featureType": "landscape",
      "elementType": "geometry",
      "stylers": [{
          "color": "#000000"
      }, {
          "lightness": 20
      }]
    }, {
      "featureType": "road.highway",
      "elementType": "geometry.fill",
      "stylers": [{
          "color": "#000000"
      }, {
          "lightness": 17
      }]
    }, {
      "featureType": "road.highway",
      "elementType": "geometry.stroke",
      "stylers": [{
          "color": "#000000"
      }, {
          "lightness": 29
      }, {
          "weight": 0.2
      }]
    }, {
      "featureType": "road.arterial",
      "elementType": "geometry",
      "stylers": [{
          "color": "#000000"
      }, {
          "lightness": 18
      }]
    }, {
      "featureType": "road.local",
      "elementType": "geometry",
      "stylers": [{
          "color": "#000000"
      }, {
          "lightness": 16
      }]
    }, {
      "featureType": "poi",
      "elementType": "geometry",
      "stylers": [{
          "color": "#000000"
      }, {
          "lightness": 21
      }]
    }, {
      "elementType": "labels.text.stroke",
      "stylers": [{
          "visibility": "on"
      }, {
          "color": "#000000"
      }, {
          "lightness": 16
      }]
    }, {
      "elementType": "labels.text.fill",
      "stylers": [{
          "saturation": 36
      }, {
          "color": "#000000"
      }, {
          "lightness": 40
      }]
    }, {
      "elementType": "labels.icon",
      "stylers": [{
          "visibility": "off"
      }]
    }, {
      "featureType": "transit",
      "elementType": "geometry",
      "stylers": [{
          "color": "#000000"
      }, {
          "lightness": 19
      }]
    }, {
      "featureType": "administrative",
      "elementType": "geometry.fill",
      "stylers": [{
          "color": "#000000"
      }, {
          "lightness": 20
      }]
    }, {
      "featureType": "administrative",
      "elementType": "geometry.stroke",
      "stylers": [{
          "color": "#000000"
      }, {
          "lightness": 17
      }, {
          "weight": 1.2
      }]
    }]
  };

  // Get the HTML DOM element that will contain your map 
  // We are using a div with id="map" seen below in the <body>
  var mapElement = document.getElementById('map');

  // Create the Google Map using out element and options defined above
  map = new google.maps.Map(mapElement, mapOptions);

  // Custom Map Marker Icon - Customize the map-marker.png file to customize your icon
  var image = '/assets/images/icons/map-marker.png';
  var contentString = '<div style="color:black;">'+
  '<a href="'+officeURL+'"><b>'+officeName+'</b><a/>'+
  '<br></div>';
  infowindow = new google.maps.InfoWindow({
    content: contentString,
    maxWidth: 400
  });
  var myLatLng = new google.maps.LatLng(officeGPS[0], officeGPS[1]);
  beachMarker = new google.maps.Marker({
    position: myLatLng,
    map: map,
    icon: image
  });
  beachMarker.addListener('click', function() {
    viewSensor();
  });
}
