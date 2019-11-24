var font = require("./font");
var writer = require("../tools/tf1writer");
var Preview = require("../tools/preview").Preview;
var preview = new Preview;

function calcPattern()
{
  return font.drawCentered("Ahoj!!!", 2, 25, "ROMANS.CHR", 0, -1000);
}

var sqSpin = [1, 0, 0, 0, 0, 0*64, 1*64+32+32+5, 0, 0, 0];

var geometry = new writer.TF1Writer().buildGeometry(calcPattern());

preview.connect("00:18:E4:35:5F:2A", 1)
  .then( () => preview.send(geometry) )
  .then( () => preview.dmx(sqSpin) )
  .then( () => preview.disconnect() )
