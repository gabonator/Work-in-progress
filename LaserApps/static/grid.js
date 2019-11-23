var writer = require("../tools/tf1writer");
var Preview = require("../tools/preview").Preview;
var preview = new Preview;

function calcPattern()
{
  // grid
  var pattern = [];
  var c = 0;
  for (var x=-2000; x<=2000; x+=800)
  {
    pattern.push(writer.Cartesian(0, x, -2000));
    pattern.push(writer.Cartesian([1, 2, 4][c++%3], x, 2000));
  }

  for (var x=-2000; x<=2000; x+=800)
  {
    pattern.push(writer.Cartesian(0, -2000, x));
    pattern.push(writer.Cartesian([1, 2, 4][c++%3], 2000, x));
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
  .then( () => preview.dmx(sqOn) )
  .then( () => preview.disconnect() )
