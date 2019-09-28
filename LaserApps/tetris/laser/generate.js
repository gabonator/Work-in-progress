var writer = require("../../tools/tf1writer");
var gameplay = require("../log/gameplay");

var map = {w:8, h:14};
var pal = [0, 1, 5, 4];
var bx = -400, by = -1800, scale = 150;

function cartesian(c, x, y)
{
//console.log([x, y, c]);
  return writer.Cartesian(pal[c], bx+x*scale, by+y*scale);
}

function calcPattern(geometry)
{
  var pattern = [];
  var last = [-1, -1, -1];
  var base = 0;
  // horizontal lines
  for (var y=0; y<=map.h; y++)
  {
    last = [-1, -1, -1];
    for (var x=0; x<map.w; x++)
    {
      var c = geometry[base + y*map.w+x];
      if (!c)  
        continue;

      if (last[0] != x || last[1] != y)
        pattern.push(cartesian(0, x, y)); //writer.Cartesian(0, bx+x*scale, by+y*scale));
      else if (last[2] == c)
        pattern.pop();

      pattern.push(cartesian(c, x+1, y)); //writer.Cartesian(pal[c], bx+(x+1)*scale, by+y*scale));
      last = [x+1, y, c];
    }
  }
  base = map.w * (map.h+1);
  // vertical lines
  for (var x=0; x<=map.w; x++)
  {
    last = [-1, -1, -1];
    for (var y=0; y<map.h; y++)
    {
      var c = geometry[base+y*(map.w+1)+x];
      if (!c)  
        continue;

      if (last[0] != x || last[1] != y)
        pattern.push(cartesian(0, x, y))
      else if (last[2] == c)
        pattern.pop();

      pattern.push(cartesian(c, x, y+1));
      last = [x, y+1, c];
    }
  }
  base += map.h*(map.w+1);

  for (var y=0; y<map.h; y++)
    for (var x=0; x<map.w; x++)
    {
      var c = geometry[base + y*map.w + x];
      if (!c)
        continue;

      var k = scale/4;

      pattern = pattern.concat(writer.Cartesian(0, bx+x*scale+scale/2-k, by+y*scale+scale/2-k));
      pattern = pattern.concat(writer.Cartesian(pal[c], bx+x*scale+scale/2+k, by+y*scale+scale/2+k));
      pattern = pattern.concat(writer.Cartesian(0, bx+x*scale+scale/2+k, by+y*scale+scale/2-k));
      pattern = pattern.concat(writer.Cartesian(pal[c], bx+x*scale+scale/2-k, by+y*scale+scale/2+k));
    }
  return pattern;
}
// 180 - 46kb err
// 160 - 40kb ok
// 165 - err
gameplay.length = 160; 

var data = {
  patternsCount:gameplay.length,
  sceneItemListCount:gameplay.length,
  channelListCount:34,
  scenes:[]
};

var lastf = 0;
var i;
for (var i=0; i<gameplay.length; i++)
{
  var serialized = calcPattern(gameplay[i].d);
  
  var dmx = new Array(data.channelListCount).fill(0);
  dmx[0] = 1;         
  dmx[3] = data.scenes.length;
  
  var newf = (i < gameplay.length-1) ? gameplay[i+1].f : gameplay[i].f + 20;
  data.scenes.push({playTime:(newf-lastf)*100/2, relationValue:0, channels:dmx, data: serialized});
  lastf = newf;
}

var tf1 = new writer.TF1Writer();
tf1.Save("tetris.tf1", data);
