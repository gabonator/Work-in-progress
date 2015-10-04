// TypoCarver
TypoCarver = function()
{
  this.toolDiameter = 25;
  this.toolOverlap = 0.25; // 0 -> 0%, 1 -> 100%
  this.maxPasses = 20;
  this.mainScale = 100;
}

TypoCarver.prototype.setToolDiameter = function (diameter)
{
  this.toolDiameter = diameter;
}

TypoCarver.prototype.setToolOverlapping = function (overlapping)
{
  this.toolOverlap = overlapping;
}

TypoCarver.prototype.process = function (xyPaths) 
{
  var result = [];

//  xyPaths = ClipperLib.JS.Clone(xyPaths);
//  ClipperLib.JS.ScaleUpPaths(xyPaths, this.mainScale);
  xyPaths = this.copyScaled(xyPaths, this.mainScale);

  var paths = this.expandPath(xyPaths, -this.toolDiameter * this.mainScale/2);

  for (var i = 0; i < this.maxPasses && paths.length; i++)
  {
    for (var j in paths)
      result.push(paths[j]);

    if ( this.toolOverlap > 0 )
      paths = this.expandPath(paths, this.toolDiameter * this.mainScale * this.toolOverlap);

    var pathOut = this.contourPath(paths, this.toolDiameter * this.mainScale/2);
    paths = this.subtractPath(paths, pathOut);
  }

//  ClipperLib.JS.ScaleUpPaths(result, 1/this.mainScale);
  return this.copyScaled(result, 1/this.mainScale);
};

TypoCarver.prototype.copyScaled = function(paths, scale)
{
  var n = [];
  for (var i=0; i<paths.length; i++)
  {
    var p = paths[i];
    n[i] = [];
    for (var j=0; j<p.length; j++)
      n[i][j] = {X:p[j].X * scale, Y:p[j].Y * scale};
  }
  return n;
}

TypoCarver.prototype.subtractPath = function(xyPaths1, xyPaths2)
{
  var subj_paths = ClipperLib.JS.Clone(xyPaths1);
  var clip_paths = ClipperLib.JS.Clone(xyPaths2);

  var cpr = new ClipperLib.Clipper();
  cpr.AddPaths(subj_paths, ClipperLib.PolyType.ptSubject, true);
  cpr.AddPaths(clip_paths, ClipperLib.PolyType.ptClip, true);

  var subject_fillType = ClipperLib.PolyFillType.pftNonZero;
  var clip_fillType = ClipperLib.PolyFillType.pftNonZero;

  solution_paths = new ClipperLib.Paths();
  cpr.Execute(ClipperLib.ClipType.ctDifference, solution_paths, subject_fillType, clip_fillType);

  return solution_paths;
}

TypoCarver.prototype.contourPath = function(xyPaths, r)
{
  var path = ClipperLib.JS.Clone(xyPaths);

  var co = new ClipperLib.ClipperOffset(); 
  var offsetted_paths = new ClipperLib.Paths();

  co.Clear();
  co.AddPaths( path, ClipperLib.JoinType.jtRound, ClipperLib.EndType.etClosedLine);
  co.MiterLimit = 1;
  co.ArcTolerance = 0.25*100;
  co.Execute(offsetted_paths, r);

  return offsetted_paths;
}

TypoCarver.prototype.expandPath = function(xyPaths, r)
{
  var path = ClipperLib.JS.Clone(xyPaths);
  var co = new ClipperLib.ClipperOffset(); 
  var offsetted_paths = new ClipperLib.Paths();

  co.Clear();
  co.AddPaths( path, ClipperLib.JoinType.jtRound, ClipperLib.EndType.etClosedPolygon);//(path, ClipperLib.PolyType.ptSubject, true);
  co.MiterLimit = 1;
  co.ArcTolerance = 0.25;
  co.Execute(offsetted_paths, r);

  return offsetted_paths;
}

// GCode
GCode = function ()
{
  this.transform = {scalex:1/50, scaley:1/50, translatex:0, translatey:0};
  this.cutFeedRate = 400;
  this.moveFeedRate = 600;
  this.safeZ = 2;
  this.drillZ = 0;
  this.returnToOrigin = false;
  // TODO: optimize shape order!
  // TODO: arc fitter!
}

GCode.prototype.build = function(xyPaths)
{
  var expcode = [];
  expcode.push("G00 Z" + this.safeZ);
  xyPaths.reverse(); 
  for ( var i in xyPaths )
  {
    var path = xyPaths[i];
    expcode.push("(path "+i+"/"+xyPaths.length+")");
    for ( var j=0; j<path.length; j++ )
    {
      var point = this.transformCoord(path[j]);
      if (j==0)
      {
        expcode.push("G00 X" + point.X + " Y" + point.Y + " F" + this.moveFeedRate);
        expcode.push("G01 Z" + this.drillZ);
      } else
      {
        expcode.push("G01 X" + point.X + " Y" + point.Y + " F" + this.cutFeedRate);
      }
    }
    // close
    if ( path[path.length-1] != path[0] )
    {
      var point = this.transformCoord(path[0]);
      expcode.push("G01 X" + point.X + " Y" + point.Y + " F" + this.cutFeedRate);
    }

    expcode.push("G00 Z" + this.safeZ);
  }
  if ( this.returnToOrigin )
  {
    expcode.push("(return home)");
    expcode.push("G00 X0 Y0 F" + this.moveFeedRate);
  }
  expcode.push("M02");
  expcode.push("(total " + expcode.length + " lines and " + xyPaths.length + " paths)");
  xyPaths.reverse();  // revert reverse

  return expcode.join("\n") + "\n";
}

GCode.prototype.format = function(code)
{
  var expcode = [];
  var prevG = -1;

  expcode.push("G00 Z" + this.safeZ + " F" + this.moveFeedRate);

  for ( var i in code )
  {
    var cmd = code[i];
    switch (cmd.G)
    {
      case 0: 
        var point = this.transformCoord(cmd);
        if ( prevG != 0 && prevG != -1 )
        {
          expcode.push("G00 Z" + this.safeZ + " F" + this.moveFeedRate);
        }
        expcode.push("G00 X" + point.X + " Y" + point.Y + " F" + this.moveFeedRate);
        expcode.push("G01 Z" + this.drillZ + " F" + this.cutFeedRate);
        break;

      case 1: 
        var point = this.transformCoord(cmd);
        expcode.push("G01 X" + point.X + " Y" + point.Y + " F" + this.cutFeedRate);
        break;
 
      case 2:
        var point = this.transformCoord(cmd);
        var ij = this.transformRelative({X:cmd.I, Y:cmd.J});
        expcode.push((this.transform.scaley > 0 ? "G02" : "G03") + " X" + point.X + " Y" + point.Y + " I" + ij.X + " J" + ij.Y + " F" + this.cutFeedRate);
        break;

      case 3:
        var point = this.transformCoord(cmd);
        var ij = this.transformRelative({X:cmd.I, Y:cmd.J});
        expcode.push((this.transform.scaley > 0 ? "G03" : "G02") + " X" + point.X + " Y" + point.Y + " I" + ij.X + " J" + ij.Y + " F" + this.cutFeedRate);
        break;
    }
    prevG = cmd.G;
  }
  expcode.push("G00 Z" + this.safeZ + " F" + this.moveFeedRate);
  expcode.push("M02");
  expcode.push("(total " + code.length + " commands in " + expcode.length + " lines)");
  return expcode.join("\n") + "\n";
}

GCode.prototype.transformCoord = function(coord)
{
  return {
    X: ((coord.X + this.transform.translatex) * this.transform.scalex).toFixed(2),
    Y: ((coord.Y + this.transform.translatey) * this.transform.scaley).toFixed(2)
  }
}

GCode.prototype.transformRelative = function(coord)
{
  return {
    X: (coord.X * this.transform.scalex).toFixed(2),
    Y: (coord.Y * this.transform.scaley).toFixed(2)
  }
}

// SVGImport
SVGImport = function ()
{
  this.transform = {scalex:17, scaley:17, translatex:0, translatey:-5};
  this.curvePrecision = .5;
}


SVGImport.prototype.svgToPaths = function(svgText)
{
  var i = 0;

  var aux = [];
  svgText = svgText.split("\n").join("");
  svgText = svgText.split(" ").join("");
  svgText = svgText.split("\t").join("");

  do 
  {
    var begin = svgText.indexOf("d=", i);
    if ( begin == -1 )
      break;

    var end = svgText.indexOf("\"", begin+3);
    if ( end == -1 )
    {
      console.log("End of string not matched!");
      break;
    }

    var pathToken = svgText.substr(begin+3, end-begin-3);
    i = end + 1;

    var paths = this.toXYPaths(this.transformPath(this.parsePath(pathToken)));
    aux = aux.concat(paths);
  } while (1)
  return aux;
}

SVGImport.prototype.toXYPaths = function(data)
{
  var paths = [];
  var aux = [];
  var lastAnchor;
  for ( var i in data )
  {
    var cmd = data[i];
    var args = cmd.attributes;
    if ( cmd.type == "M" )
    {
      position = this.makePos(args[0], args[1]);
      lastAnchor = {X:position.x, Y:position.y};
      aux.push(lastAnchor);
      continue;
    }
    if ( cmd.type == "l" )
    {
      position = this.addPos(position, this.makePos(args[0], args[1]));
      aux.push({X:position.x, Y:position.y});
      continue;
    }          
    if ( cmd.type == "L" )
    {
      position = this.makePos(args[0], args[1]);
      aux.push({X:position.x, Y:position.y});
      continue;        
    }          
    if ( cmd.type == "h" )
    {
      position = this.addPos(position, this.makePos(args[0], 0));
      aux.push({X:position.x, Y:position.y});
      continue;
    }
    if ( cmd.type == "v" )
    {
      position = this.addPos(position, this.makePos(0, args[0]));
      aux.push({X:position.x, Y:position.y});
      continue;
    }
    if ( cmd.type == "H" )
    {
      position = this.makePos(args[0], position.y);
      aux.push({X:position.x, Y:position.y});
      continue;
    }
    if ( cmd.type == "V" )
    {
      position = this.makePos(position.x, args[0]);
      aux.push({X:position.x, Y:position.y});
      continue;
    }          
    if ( cmd.type == "c" )
    {
      var p1 = this.addPos(position, this.makePos(args[0], args[1]));
      var p2 = this.addPos(position, this.makePos(args[2], args[3]));
      var pn = this.addPos(position, this.makePos(args[4], args[5]));
      var n = 8;//this.calcCurvePoints(position, pn); 

			for ( var j = 1; j<=n; j++)
      {
        var pt = this.calcBezier(position, p1, p2, pn, j/n);
        aux.push({X:pt.x, Y:pt.y});
      }
      position = pn;
      continue;
    }          
    if ( cmd.type == "C" )
    {
      var p1 = this.makePos(args[0], args[1]);
      var p2 = this.makePos(args[2], args[3]);
      var pn = this.makePos(args[4], args[5]);
      var n = 8;//this.calcCurvePoints(position, pn); 

			for ( var j = 1; j<=n; j++)
      {
        var pt = this.calcBezier(position, p1, p2, pn, j/n);
        aux.push({X:pt.x, Y:pt.y});
      }
      position = pn;
      continue;
    }          
    if ( cmd.type == "Q" )  // user quadratic
    {
      var p1 = this.makePos(args[0], args[1]);
      var pn = this.makePos(args[2], args[3]);
      var n = 8;//this.calcCurvePoints(position, pn);

			for ( var j = 1; j<=n; j++)
      {
        var pt = this.calcQuadratic(position, p1, pn, j/n);
        aux.push({X:pt.x, Y:pt.y});
      }
      position = pn;
      continue;
    }          
/*
    if ( cmd.type == "A" )  // user arc
    {
      var p1 = this.makePos(args[0], args[1]);
      var pn = this.makePos(args[2], args[3]);
      var n = 8;//this.calcCurvePoints(position, pn);

			for ( var j = 1; j<=n; j++)
      {
        var pt = this.calcArc(position, p1, pn, j/n);
        aux.push({X:pt.x, Y:pt.y});
      }
      position = pn;
      continue;
    }          
*/
    if ( cmd.type == "s" )
    {
      var p2 = this.addPos(position, this.makePos(args[0], args[1]));
      var pn = this.addPos(position, this.makePos(args[2], args[3]));
      var p1 = this.addPos(position, {x:-pn.x+p2.x, y:-pn.y+p2.y});
      var n = 8;//this.calcCurvePoints(position, pn); 

			for ( var j = 1; j<=n; j++)
      {
        var pt = this.calcBezier(position, p1, p2, pn, j/n);
        aux.push({X:pt.x, Y:pt.y});
      }
      position = pn;
      continue;
    }          
    if ( cmd.type == "z" || cmd.type == "Z" )
    {
      aux.push(lastAnchor);
      if ( aux.length > 2 ) // why!?
        paths.push(aux);
      aux = [];
      continue;
    }          
    console.log("Unknown command <" + cmd.type + ">");
  }
  return paths;
}

SVGImport.prototype.calcCurvePoints = function(p1, p2)
{
  var dist = Math.sqrt((p1.x - p2.x)*(p1.x - p2.x) + (p1.y - p2.y)*(p1.y - p2.y));
  var n = Math.floor(dist * this.curvePrecision);
  return Math.max(2, n);
}

SVGImport.prototype.linear = function(pt1, pt2, f)
{
  return {x:pt1.x + (pt2.x-pt1.x)*f, y:pt1.y + (pt2.y-pt1.y)*f};
}

SVGImport.prototype.calcBezier = function (pt1, c1, c2, pt2, f)
{
  var lineA1 = this.linear(pt1, c1, f);
  var lineA2 = this.linear(c1, c2, f);
  var lineA3 = this.linear(c2, pt2, f);
  var lineB1 = this.linear(lineA1, lineA2, f);
  var lineB2 = this.linear(lineA2, lineA3, f);
  return this.linear(lineB1, lineB2, f);
}

SVGImport.prototype.calcQuadratic = function (pt1, c, pt2, f)
{
  var lineA = this.linear(pt1, c, f);
  var lineB = this.linear(c, pt2, f);
  return this.linear(lineA, lineB, f);
}

SVGImport.prototype.parsePath = function (strSvg)
{
  var pos = 0, aux = [];
  while (pos < strSvg.length && 
         (token = this.getToken(strSvg.substr(pos), pos)) && 
         token.length > 0 )
  {
    if ( token.type )
      aux.push(token);
    pos += token.length;
  }
  return aux;
}

SVGImport.prototype.getToken = function(str, pos)
{
  var tests = [
    /^([M])([\-]?[\d\.]+)([\-|\,][\d\.]+)/,
    /^([l|L])([\-]?[\d\.]+)[\ \,]*([\-]?[\d\.]+)/,
    /^([h|v|H|V])([\-]?[\d\.]+)/,
    /^([c|C])([\-]?[\d\.]+)([\-|\,][\d\.]+)([\-|\,][\d\.]+)([\-|\,][\d\.]+)([\-|\,][\d\.]+)([\-|\,][\d\.]+)/,
    /^([s|S])([\-]?[\d\.]+)([\-|\,][\d\.]+)([\-|\,][\d\.]+)([\-|\,][\d\.]+)/,
    /^(z)/
  ];

  while ( str[0] == ' ' )
    return {length:1};

  for ( var i in tests )
  {
    var matches = tests[i].exec(str);
    if ( matches && matches.length > 0 )
    {
      var token = matches.splice(0, 1)[0];
      var type = matches.splice(0, 1)[0];
      for ( var i in matches )
      {
        if ( matches[i][0] == "," )
          matches[i] = matches[i].substr(1);
        matches[i] = parseFloat(matches[i]);
      }
      return {type:type, length:token.length, attributes:matches};
    }
  }
  console.log("Unknown command 1 <" + str[0] + ">" + str.substring(1));
} 

SVGImport.prototype.makePos = function(x, y)
{
  return {x:x, y:y};
}

SVGImport.prototype.scalePos = function(p)
{
  return {x:p.x*2+20, y:p.y*2+20};
}

SVGImport.prototype.scaleGPos = function(p)
{
  return {x:p.x*2+20, y:-p.y*2+20};
}

SVGImport.prototype.addPos = function(p1, p2)
{
  return {x:p1.x+p2.x, y:p1.y+p2.y};
}

SVGImport.prototype.transformPath = function (data)
{
  var aux = [];
  var t = this.transform;
  for ( var i in data )
  {
    var token = data[i];
    if ( typeof(token.type) == "undefined" )
      continue;

    if (token.attributes.length % 2 == 1 ) 
    {
      if (token.type == "H" )
        token.attributes[0] = token.attributes[0] * t.scalex + t.translatex;
      else
      if (token.type == "V" )
        token.attributes[0] = (token.attributes[0] + t.translatey) * t.scaley;
      else
      if (token.type == "h" )
        token.attributes[0] = token.attributes[0] * t.scalex;
      else
      if (token.type == "v" )
        token.attributes[0] = token.attributes[0] * t.scaley;
      else
        console.log("Unknown single argument token " + token.type);
    } else
    if ( token.type == token.type.toUpperCase() )
    {
      for (var j=0; j<token.attributes.length; j+=2)
      {
        token.attributes[j+0] = (token.attributes[j+0] + t.translatex) * t.scalex;
        token.attributes[j+1] = (token.attributes[j+1] + t.translatey) * t.scaley;
      }
    } else
    {
      for (var j=0; j<token.attributes.length; j+=2)
      {
        token.attributes[j+0] = token.attributes[j+0] * t.scalex;
        token.attributes[j+1] = token.attributes[j+1] * t.scaley;
      }
    }
    aux.push(token);
  }
  return aux;
}


// SVGExport
SVGExport = function ()
{
  this.transform = {translatex:0, translatey:0, scalex:1, scaley:1};
}

SVGExport.prototype.paths2string = function (paths) 
{
  var svgpath = "", i, j;
  for(i = 0; i < paths.length; i++) 
  {
    for(j = 0; j < paths[i].length; j++)
    {
      if (!j) svgpath += "M";
      else svgpath += "L";
      svgpath += (paths[i][j].X * this.transform.scalex + this.transform.translatex) + "," + (paths[i][j].Y * this.transform.scaley + this.transform.translatey) + " ";
    }
    svgpath += "Z\n";
  }
  if (svgpath=="") 
    svgpath = "M0,0";
  return svgpath;
}

SVGExport.prototype.build = function(paths)
{
  return ''+
    '<svg style="margin-top:10px; margin-right:10px;margin-bottom:10px;background-color:#dddddd" width="1200" height="400">\n' +
    paths.join("\n") +
    '</svg>'; 
}

SVGExport.prototype.path = function(paths, style)
{
  var svgstyle = style || {stroke:'black', strokeWidth:'2', fill:'yellow'};
  svgstyle = 'stroke="'+svgstyle.stroke+'" fill="'+svgstyle.fill+'" stroke-linecap="round" stroke-linejoin="round" stroke-width="'+svgstyle.strokeWidth+'"';
  var svgpath = '';
  for (var j in paths)
  {
    var path = paths[j];
    for (var i=0; i<path.length; i++)
    {
      svgpath += i ? 'L' : 'M';
      svgpath += (path[i].X * this.transform.scalex + this.transform.translatex).toFixed(2) + "," + (path[i].Y * this.transform.scaley + this.transform.translatey).toFixed(2) + " ";
    }
  }
  return '  <path '+svgstyle+' d="' + svgpath + '"/>\n';
}

SVGExport.prototype.linesToSvg = function(orig, path, d)
{
  var r = '<svg style="margin-top:10px; margin-right:10px;margin-bottom:10px;background-color:#dddddd" width="1200" height="400">' +
          '<path stroke="none" fill="rgba(255,255,0,0.8)" stroke-linecap="round" stroke-linejoin="round" stroke-width="1" d="' + this.paths2string(orig) + '"/>';
  for (var p in path)	
    r +=  '<path stroke="rgba(0,0,255,0.3)" fill="none" stroke-linecap="round" stroke-linejoin="round" stroke-width="'+d+'" d="' + this.paths2string([path[p]]) + '"/>' +
          '<path stroke="black" fill="none" stroke-linecap="round" stroke-linejoin="round" stroke-width="1" d="' + this.paths2string([path[p]]) + '"/>';
  r +=    '</svg>';
  return r;
}
