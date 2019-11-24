var Preview = require("../tools/preview").Preview;
var preview = new Preview;

preview.connect("00:18:E4:35:5F:2A", 1)
  .then( () => preview.dmx([0]) )
  .then( () => preview.disconnect() )
