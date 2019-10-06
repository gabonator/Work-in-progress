var writer = require("../../tools/tf1writer");
var log = require("./log");
var lineclip = require("./lineclip");

var bx = 0;
var by = 0;
var scale = 5;
var pal = [0, 1, 4, 5];

var viewport = {left:0, right:600, top:0, bottom:600};

function clipLine(l)
{
  var r = lineclip(
    [[l[0], l[1]], [l[2], l[3]]], // line
    [viewport.left, viewport.top, viewport.right, viewport.bottom]); // bbox
  if (!r || r.length == 0)
    return false;
  l[0] = Math.floor(r[0][0][0]);
  l[1] = Math.floor(r[0][0][1]);
  l[2] = Math.floor(r[0][1][0]);
  l[3] = Math.floor(r[0][1][1]);
  return l;   
}

function cartesian(c, x, y)
{
//  console.log([x, y, c]);
  return writer.Cartesian(pal[c], bx+(x-300)*scale, by+(y-300)*scale);
}

function calcPattern(geometry)
{
  var pattern = [];
  for (var i in geometry)
  {
    var line = geometry[i];
    line = clipLine(line);
    if (!line)
      continue;
    pattern.push(cartesian(0, line[0], line[1]));
    pattern.push(cartesian(line[4], line[2], line[3]));
  }
  pattern.push(cartesian(0, 300, 300));

  return pattern;
}
// 180 - 46kb err
// 160 - 40kb ok
// 165 - err
// log.length = 20; 

//log.length = 150;
var len = 140;
var data = {
  patternsCount:len,
  sceneItemListCount:len,
  channelListCount:34,
  scenes:[]
};

for (var i=0; i<len; i++)
{
  var serialized = calcPattern(log[Math.floor(i*log.length/len)]);
  
  var dmx = new Array(data.channelListCount).fill(0);
  dmx[0] = 1;         
  dmx[3] = data.scenes.length;
  
  data.scenes.push({playTime:50, relationValue:0, channels:dmx, data: serialized});
}

var tf1 = new writer.TF1Writer();
tf1.Save("maze.tf1", data);
