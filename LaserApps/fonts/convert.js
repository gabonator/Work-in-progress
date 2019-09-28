var d = require("fs").readFileSync(process.argv[2]).toString().split("\r\n");

var font = {};

for (var i in d)
{
  if (d[i].length == 0)
    continue;
  var tokens = d[i].split(";");
  var idw = tokens.shift().split(" ");
  var id = "0x" + idw[0].substr(4);
  var w = parseInt(idw[1]);
  var letter = [];
  
  while (tokens.length)
  {
    var path = tokens.shift().split(" ");
    var xypath = [];
    for (var ixy in path)
    {
      if (path[ixy] == "")
        continue;

      var xy = path[ixy].split(",");
      xy = [parseFloat(xy[0]), parseFloat(xy[1])];
      xypath.push(xy);
    }
    letter.push(xypath);
  }
  font[String.fromCharCode(parseInt(id))] = {w:w, g:letter};
}

console.log("fonts[\""+process.argv[2]+"\"]="+JSON.stringify(font));

