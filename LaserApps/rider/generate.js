var writer = require("./tf1writer");
var archive = require("./archive");

function calcPattern(color, geometry, bx, by, scale)
{
  var pattern = [];
  for (var i=0; i<geometry.length; i++)
  {
    var path = geometry[i];
    for (var j=0; j<path.length; j+=2)
    {
      var x = path[j];
      var y = path[j+1];
      pattern = pattern.concat(writer.Cartesian(j==0 ? 0 : color, bx+x*scale, by-y*scale));
    }
  }
  return pattern;
}

var count = 0;
for (var i in archive)
  count++;

var data = {
  patternsCount:count,
  sceneItemListCount:count,
  channelListCount:34,
  scenes:[]
};

for (var i in archive)
{
  var geometry = archive[i];
  var serialized = calcPattern(1, geometry, -1800, +400, 10);
  
  var dmx = new Array(34).fill(0);
  dmx[0] = 1;
  dmx[3] = data.scenes.length;

  data.scenes.push({playTime:80, relationValue:0, channels:dmx, data: serialized});
}

var tf1 = new writer.TF1Writer();
tf1.Save("linerider.tf1", data);
