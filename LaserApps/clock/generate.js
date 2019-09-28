var writer = require("../tools/tf1writer");
var fonts = require("../fonts/fonts");

function drawClock(h, m)
{
  var r = 1500;
  var cfg = {radius:r, tickSize:50, hourRadius:r*0.5, minRadius:r*0.75,
    tickColor:1, hourColor:1, minColor:1};

  var pat = [];
  for (var i=0; i<12; i++)
  {
    var a = 360*i/12;
    pat.push(writer.Polar(0, cfg.radius-cfg.tickSize, a-90));
    pat.push(writer.Polar(cfg.tickColor, cfg.radius, a-90));
  }

  pat.push(writer.Polar(0, 0, 0));
  pat.push(writer.Polar(cfg.hourColor, cfg.hourRadius, 90-(h%12)*360/12));
  pat.push(writer.Polar(cfg.hourColor, 0));
  pat.push(writer.Polar(cfg.hourColor, cfg.hourRadius, 90-(h%12)*360/12));
  pat.push(writer.Polar(cfg.hourColor, 0));
  pat.push(writer.Polar(cfg.minColor, cfg.minRadius, 90-(m%60)*360/60));
  return pat;
}

function drawTime(h, m, s)
{
  var txt = ("0"+h).substr(-2) + ":" + ("0"+m).substr(-2) + ":" + ("0"+s).substr(-2);
  return drawCentered(fonts["ROMANS.CHR"], 1500/100, txt, 4);
}

function drawDate(day, month, year)
{
  var txt = day + "." + month + "." + year;
  return drawCentered(fonts["ROMANS.CHR"], 1500/100, txt, 4);
}

function drawHello(p)
{
  switch (p)
  {
    case 0:
    case 1:
    case 2:
    case 3:
      return drawCentered(fonts["ROMANS.CHR"], 1500/80, "Ahoj!", 7);
    case 4:
    case 5: 
      return drawCentered(fonts["ROMANS.CHR"], 1500/60, "ako", 7);
    case 6:
    case 7: 
      return drawCentered(fonts["ROMANS.CHR"], 1500/50, "sa", 7);
    case 8:
    case 9: 
      return drawCentered(fonts["ROMANS.CHR"], 1500/45, "mas?", 7);
  }
  return [];
}

function getScene(d)
{
  var h = d.getHours();
  var m = d.getMinutes();
  var s = d.getSeconds();
  var scene = drawClock(h, m);

  switch (Math.floor(s/10))
  {
    case 0: scene = scene.concat(drawTime(h, m, s)); break;
    case 1: scene = scene.concat(drawDate(d.getDate(), d.getMonth()+1, d.getFullYear())); break;
    case 2: scene = scene.concat(drawTime(h, m, s)); break;
    case 3: scene = scene.concat(drawDate(d.getDate(), d.getMonth()+1, d.getFullYear())); break;
    case 4: scene = scene.concat(drawHello(s%10)); break;
    case 5: scene = scene.concat(drawTime(h, m, s)); break;
  }
  
  scene = scene.concat(writer.Polar(0, 0, 0));

  return scene;
}

function getCharExtent(font, scale, c)
{
  var symbol = font[c].g;
  var extent = false;

  for (var j in symbol)
  {
    var symbolpath = symbol[j];
    for (var k=0; k<symbolpath.length; k++)
    {
      var x = symbolpath[k][0]*scale;
      var y = -symbolpath[k][1]*scale;
      if (!extent)
        extent = {left:x, top:y, right:x, bottom:y}
      else
        extent = {
          left:Math.min(extent.left, x),
          top:Math.min(extent.top, y), 
          right:Math.max(extent.right, x), 
          bottom:Math.max(extent.bottom, y) };
    }
  }  
  extent.width = font[c].w*scale;
  return extent;
}

function getExtent(font, scale, text)
{
  var bounds = {left:0, top:0, right:0, bottom:0};
  var x = 0, y = 0;
  for (var i in text)
  {
    var c = text[i];
    if (c == " ")
      c = "A";

    var extent = getCharExtent(font, scale, c);
    extent.left += x;
    extent.top += y;
    extent.right += x;
    extent.bottom += y;
    bounds.left = Math.min(bounds.left, extent.left);
    bounds.top = Math.min(bounds.top, extent.top);
    bounds.right = Math.max(bounds.right, extent.right);
    bounds.bottom = Math.max(bounds.bottom, extent.bottom);
    x += extent.width;
  }
  bounds.width = bounds.right - bounds.left;
  bounds.height = bounds.bottom - bounds.top;
  return bounds;
}

function drawCentered(font, scale, text, color)
{
  var extent = getExtent(font, scale, text);
  var bx = -(extent.right + extent.left)/2;
  var by = -(extent.top + extent.bottom)/2;
  var pat = [];

  for (var i in text)
  {
    var c = text[i];
    if (c == " ")
    {
      bx += font["A"].w*scale;
      continue;
    }

    var symbol = font[c].g;

    for (var j in symbol)
    {
      var symbolpath = symbol[j];
      for (var k=0; k<symbolpath.length; k++)
      {
        var x = symbolpath[k][0];
        var y = symbolpath[k][1];
        pat.push(writer.Cartesian(k==0 ? 0 : color, bx+x*scale, by-y*scale));
      }
    }
    bx += font[c].w*scale;
  }
  return pat;
}

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

var count = 60;

var data = {
  patternsCount:count,
  sceneItemListCount:count,
  channelListCount:34,
  scenes:[]
};

var d = new Date();

// time needed for upload
d.setSeconds(d.getSeconds() + 38-11-6 + 23);
console.log("Generating clock for timestamp " + d);

for (var i=0; i<count; i++)
{
  var serialized = getScene(d);
  d.setSeconds(d.getSeconds() + 1);

  var dmx = new Array(34).fill(0);
  dmx[0] = 1;
  dmx[3] = data.scenes.length;

  data.scenes.push({playTime:1000, relationValue:0, channels:dmx, data: serialized});
}

var tf1 = new writer.TF1Writer();
tf1.Save("clock.tf1", data);

console.log("Finished!");
