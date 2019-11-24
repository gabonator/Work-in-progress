var fonts = require("../fonts/fonts");
var writer = require("../tools/tf1writer");

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

function drawCentered(text, color, scale, fontname, cx, cy)
{
  var font = fonts[fontname ? fontname : "ROMANS.CHR"];
  var extent = getExtent(font, scale, text);
  var bx = -(extent.right + extent.left)/2 + (cx ? cx : 0);
  var by = -(extent.top + extent.bottom)/2 + (cy ? cy : 0);
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

module.exports = {drawCentered:drawCentered};