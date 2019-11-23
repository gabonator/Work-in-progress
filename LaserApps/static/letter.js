var writer = require("../tools/tf1writer");
var Preview = require("../tools/preview").Preview;
var preview = new Preview;

function calcPattern()
{
  // letter
  var k = 10;
  var pattern = [];
  pattern.push(writer.Cartesian(2, -100*k, 100*k));
  pattern.push(writer.Cartesian(2, 0*k, -100*k));
  pattern.push(writer.Cartesian(2, 100*k, 100*k));

  pattern.push(writer.Cartesian(1, 50*k, 0));
  pattern.push(writer.Cartesian(1, -50*k, 0));
  pattern.push(writer.Cartesian(1, -100*k, 100*k));
  
//  pattern.push(writer.Cartesian(0, -100*k, 100*k));
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
