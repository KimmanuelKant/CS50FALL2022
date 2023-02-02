var carousel = document.getElementById("carousel");
var images = carousel.querySelectorAll("img");
var current = 0;

// Hide all images except the first one
setInterval(function() {
  for (var i = 0; i < images.length; i++) {
    images[i].style.display = "none";
  }
  // Show the next image
  current = (current + 1) % images.length;
  images[current].style.display = "block";
}, 2000);
