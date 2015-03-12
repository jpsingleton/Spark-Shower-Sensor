var Blinky = require('./blinky.js');
var spark = require('spark');

spark.login({accessToken: ''}); // PUT YOUR ACCESS TOKEN HERE (or you can use a username and password)

var bt = new Blinky('/dev/ttyACM0');

bt.on('ready', function() {

  var r, g, b = 0;

  spark.getEventStream('shower', 'mine', function(data) {
    console.log('Event:', data);
    if(!data) return;
    if(data.data === 'busy') {
      r = 254;
      g = 0;
      setColour();
    } else {
      r = 0;
      g = 254;
      setColour();
    }
  });

  function setColour() {
    for (var y = 0; y < 60; y++) {
      bt.setPixel(y, r, g, b);
    }
    bt.show();
  }

  setInterval(setColour, 1000);

});


