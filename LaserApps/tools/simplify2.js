class SvgExtractor
{
  convert(d)
  {
    var q = d.split("M").join("M ").split("m").join("m ").split("c").join("c ").split("z").join(" z ").split("l").join("l ").split("\n").join(" ").split("  ").join(" ").split(" "); //.map(i=>parseInt(i));
    var g = [];

    //console.log(g);
    var r = "";
    var x = 0, y = 0, lx=0, ly=0;
    var bez= false;
  var dbg = false;
var exit = false;
    for (var i =0; i<q.length && !exit; i+=2) 
    {
  if (dbg)
    console.log([q[i], q[i+1], x, y, r]);
  //  if (i>20) break;
      if (q[i] == "c" || q[i] == "l" || q[i] == "z" || q[i] == "m" || q[i] == "M")
      {
  //console.log([i, q[i]]);
        if (x != lx || y != ly)
          r += x + " " + y + " ";

         if (q[i] == "M")
         {
           x = parseInt(q[i+1]);
           y = parseInt(q[i+2]);
           r += q[i] + " " + x + " " + y + " ";
           lx = x; ly = y;
           i+= 2;
         } else
         if (q[i] == "c")
         { 
           r += "L ";
     bez = true; } else
         {
           bez = false;
    if (q[i] == "m")
    {
  //console.log("<<<<");
      x += parseInt(q[i+1]); y += parseInt(q[i+2]); lx = x; ly = y;
      r += "M " + x + " " + y + " ";
      i += 2;
    } else {
      if (q[i] == "l")
      r += "L ";
      else if (q[i] == "z")
  {
  //r = ""; dbg = true;
      r += "z ";
  lx = x; ly = y;
exit = true; // hole
  }
      else throw "nepoznam " + q[i];
     }
         }
        i--;
        continue;
      }
      if (bez)
       {
         i+= 4;
       }
      x += parseInt(q[i]);
      y += parseInt(q[i+1]);
  //console.log([lx, ly, x, y]);
      if ((x-lx)*(x-lx)+(y-ly)*(y-ly) > 20)
      {
        r += x + " " + y + " ";
        lx = x;
        ly = y;
      }
    }
    return r;
  }

  optimizeSvg(svg)
  {
    svg = svg.split("\n").join(" ");
    var regex = new RegExp("path d=\"(.*?)\"", "g");
    var myArray;
    var res = "";
    while ((myArray = regex.exec(svg)) != null)  
    {  
      var d = myArray[1];
      res += "<path d=\""+this.convert(d)+"\"/>\n";
    } 
    return res;
  }

  extractRawGeometry(res)
  {
    var geom = [];
    var regex = new RegExp("path d=\"(.*?)\"", "g");
    var myArray;
    while ((myArray = regex.exec(res)) != null)  
    {  
      var d = myArray[1];
      var ar = d.split(" ");
      var poly = [];
      for (var i =0; i< ar.length; i++)
      {
        if (ar[i] == "z")
        {            
          if (poly.length) {geom.push(poly); poly = [];}
        } else
        if (ar[i] == "M")
        {
          if (poly.length) {geom.push(poly); poly = [];}
          poly.push(parseInt(ar[i+1]), parseInt(ar[i+2])); i+=2;
        } else
        if (ar[i] == "L")
        {
        } else
        {
          poly.push(parseInt(ar[i]), parseInt(ar[i+1])); i++;
        }
      }
    } 
    return geom;
  }

  extractRawGeometryXY(res)
  {
    var geom = [];
    var regex = new RegExp("path d=\"(.*?)\"", "g");
    var myArray;
    while ((myArray = regex.exec(res)) != null)  
    {  
      var d = myArray[1];
      var ar = d.split(" ");
      var poly = [];
      for (var i =0; i< ar.length; i++)
      {
        if (ar[i] == "z")
        {            
          if (poly.length) {geom.push(poly); poly = [];}
        } else
        if (ar[i] == "M")
        {
          if (poly.length) {geom.push(poly); poly = [];}
          poly.push({X:parseInt(ar[i+1]), Y:parseInt(ar[i+2])}); i+=2;
        } else
        if (ar[i] == "L")
        {
        } else
        {
          poly.push({X:parseInt(ar[i]), Y:parseInt(ar[i+1])}); i++;
        }
      }
    } 
    return geom;
  }

  getLinesFromGeometryXY(g)
  {
    var allLines = [];
    for (var i in g)
    {
      var lines = [];
      var path = g[i];

      for (var j=0; j<path.length-1; j++)
        lines.push([path[j].X, path[j].Y, path[j+1].X, path[j+1].Y]);
      var j = path.length-1;
      lines.push([path[j].X, path[j].Y, path[0].X, path[0].Y]);
      allLines.push(lines);
    }
    return allLines;
  }

  svgFromGeometryXY(g)
  {
    var r = "<path d=\"";
    for (var i in g)
    {
      var path = g[i];
      r += "M"+path[0].X+","+path[0].Y+" ";

      for (var j=1; j<path.length; j++)
      {
        if (j==1)
          r += "L";
        r += path[j].X+","+path[j].Y+" ";
      }
      r += "z ";
    }
    r += "\"/>";
    return r;
  }

  svgFromLines(lines)
  {
    var r = "<path d=\"";
    var last = [-9999, -9999];
    for (var i in lines)
    {
      var line = lines[i];
      if (last[0] == line[0] && last[1] == line[1])
        r += line[2]+" "+line[3] + " ";
      else
        r += "M "+line[0]+" "+line[1]+" L "+line[2]+" "+line[3]+" ";
      last = [line[2], line[3]]
    }
    r += "z\"/>";
    return r;
  }

  Transform(fin, fout)
  {
    var f = require("fs").readFileSync(fin).toString();
    var a = this.optimizeSvg(f);
    var b = this.extractRawGeometry(a);
    require("fs").writeFileSync(fout, JSON.stringify(b));
  }
}


var svg = new SvgExtractor();
//svg.Transform("thumb0133.svg", "t133");
//if (process.argv.length > 3)
//  svg.Transform(process.argv[2], process.argv[3]);


var svg = new SvgExtractor();
var fin = "thumb0147.svg";
var fout = "";
if (process.argv.length > 3)
{
  fin = process.argv[2];
  fout = process.argv[3];
}

var f = require("fs").readFileSync(fin).toString();
var a = svg.optimizeSvg(f);
//console.log(a)

var ClipperLib = require("./clipper.js");

var xyPaths = svg.extractRawGeometryXY(a);
r = 5;

var expandPath = function(xyPaths, r)
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

  var offsetted_paths = xyPaths; //expandPath(xyPaths, -2);

//  console.log( svg.svgFromGeometryXY(offsetted_paths));
//return 1;
  var all = svg.getLinesFromGeometryXY(offsetted_paths);

  var filter = 10;
   var result = "";
  for (var j in all)
  {
    var used = [];
    var l = all[j];
    var prefer = false;
    var score = filter;
    for (var i in l)
    {
      prefer = hasLine(used, l[i], score <= filter/2);

      if (!prefer)
         score++;
      else
         score--;

      if (score>filter) score = filter;
      if (score<0) score = 0;

      if (score >= filter/2)
      {
        used.push(l[i]);
      }
//      else 
//        break;
    }
    result += svg.svgFromLines(used) + "\n";
  }
//  console.log(l.length + " / " + used.length);

if (fout != "")
{
  var b = svg.extractRawGeometry(result);
  require("fs").writeFileSync(fout, JSON.stringify(b));
} else
  console.log(result);

function distance(x, y, x1, y1, x2, y2, prefer) 
{
  var A = x - x1;
  var B = y - y1;
  var C = x2 - x1;
  var D = y2 - y1;

  var dot = A * C + B * D;
  var len_sq = C * C + D * D;
  var param = -1;
  if (len_sq != 0) //in case of 0 length line
      param = dot / len_sq;
  else
    return 1000;

  var xx, yy;
  if (prefer)
  {
    if (param < 0-0.5) {
      return 1000;
    }
    else if (param > 1+0.5) {
      return 1000;
    }
  } else
  {
    if (param < 0) {
      return 1000;
    }
    else if (param > 1) {
      return 1000;
    }
  }

    xx = x1 + param * C;
    yy = y1 + param * D;

  var dx = x - xx;
  var dy = y - yy;
  return {d: Math.sqrt(dx * dx + dy * dy), k:param};
}

function nearestProjection(cache, x, y, prefer)
{
  var best = {d: 1000};
  for (var i in cache)
  {
    var t = distance(x, y, cache[i][0], cache[i][1], cache[i][2], cache[i][3], prefer);
    if (t.d < best.d)
    {
      best.d = t.d;
      best.k = t.k;
      best.i = i;
      best.j = i + (1-t.k);
//      if (d<10) // !
//        return d;
    }
  }
  return best;
}

function hasLine(cache, line, prefer)
{
prefer = false;
  var k1 = nearestProjection(cache, line[0], line[1], prefer);
  var k2 = nearestProjection(cache, line[2], line[3], prefer);
  if (prefer)
  {
    if (k1.d < 60 && k2.d < 60)
    {
      return true; //Math.abs(k1.d-k2.d) < 15;//k1.j < k2.j;
    }
  } else
  {
    if (k1.d < 5 && k2.d < 5)
    {
      return true; //Math.abs(k1.d-k2.d) < 15;//k1.j < k2.j;
    }
  }
  return false;

//  return (nearestProjection(cache, line[0], line[1]) < 100 &&
//    nearestProjection(cache, line[2], line[3]) < 100);
/*
  if (nearestProjection(cache, line[0], line[1]) > 300)
    return false;
  if (nearestProjection(cache, line[2], line[3]) > 300)
    return false;
  return true;
*/
}
