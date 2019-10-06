var writer = require("../../tools/tf1writer");
var log = require("./log");

var bx = 0;
var by = 0;
var scale = 7;
var pal = [0, 1, 4, 5];

var viewport = {left:0, right:600, top:0, bottom:600};

function cartesian(c, x, y)
{
//  console.log([x, y, c]);
  return writer.Cartesian(pal[c], bx+(x-300)*scale, by+(y-300)*scale);
}

function calcPattern(geometry)
{
  var pattern = [];
  for (var j in geometry)
  {
    var g = geometry[j];
    for (var i=0; i<g.length; i++)
    {
      var pt = g[i];
      pattern.push(cartesian(pt[2], pt[0], pt[1]));
    }
//    pattern.push(cartesian(0, geometry[0][0], geometry[0][1]));
  }
  return pattern;
}

// log.length = 20; 

var data = {
  patternsCount:log.length,
  sceneItemListCount:log.length,
  channelListCount:34,
  scenes:[]
};

for (var i=0; i<log.length; i++)
{
  var serialized = calcPattern(log[i]);
  
  var dmx = new Array(data.channelListCount).fill(0);
  dmx[0] = 1;         
  dmx[3] = data.scenes.length;
  
  data.scenes.push({playTime:50, relationValue:0, channels:dmx, data: serialized});
}

var tf1 = new writer.TF1Writer();
tf1.Save("box.tf1", data);
