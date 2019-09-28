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
    for (var i =0; i<q.length; i+=2) 
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

  Transform(fin, fout)
  {
    var f = require("fs").readFileSync(fin).toString();
    var a = this.optimizeSvg(f);
    var b = this.extractRawGeometry(a);
    require("fs").writeFileSync(fout, JSON.stringify(b));
  }
}


var svg = new SvgExtractor();
if (process.argv.length > 3)
  svg.Transform(process.argv[2], process.argv[3]);
