var writer = require("../tools/tf1writer");
var Preview = require("../tools/preview").Preview;
var preview = new Preview;

function calcPattern()
{
  var pattern = [];

  var N = 120; // 750 max
  var color = 4; // 1..7
  for (var i=0; i<N+1; i++)
  {
    var radius = 1000 + Math.cos(i*8/N*2*Math.PI)*500;
    var angle = 360*i/N;
    pattern.push(writer.Polar(color, radius, angle));
  }

  return pattern;
}

var sqOn = [1, 0, 0, 0, 0, 0, 0, 0, 0, 0];
var sqOff = [0];
var sqRotate = [1, 0, 0, 0, 0, 70];
//var sqRotate = [1, 0, 0, 0, 32, 0];

var geometry = new writer.TF1Writer().buildGeometry(calcPattern());

preview.connect("00:18:E4:35:5F:2A", 1)
  .then( () => preview.send(geometry) )
  .then( () => preview.dmx(sqRotate) )
  .then( () => preview.disconnect() )
