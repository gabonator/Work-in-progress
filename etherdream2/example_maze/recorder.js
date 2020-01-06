module = {exports: {}};

class Recorder
{
  constructor()
  {
    this.socket = new WebSocket("ws://localhost:6699/index.html");
    this.viewport = {left:0, right:600, top:0, bottom:600};
  }

  clipLine(l)
  {
    var r = lineclip(
      [[l[0], l[1]], [l[2], l[3]]], // line
      [this.viewport.left, this.viewport.top, this.viewport.right, this.viewport.bottom]); // bbox
    if (!r || r.length == 0)
      return false;
    l[0] = Math.floor(r[0][0][0]);
    l[1] = Math.floor(r[0][0][1]);
    l[2] = Math.floor(r[0][1][0]);
    l[3] = Math.floor(r[0][1][1]);
    return l;   
  }

  record(renderData)
  {
    var projectx = x => Math.floor((300-x)/300*30000);
    var projecty = y => Math.floor((-y+300)/300*30000+15000);
    var projectc = c => [0, 1, 5, 4, 5, 5, 5, 5][c];
    var geom = [];
    for (var i=0; i<renderData.length; i++)
    {
      var line = this.clipLine(renderData[i]);
      if (!line) 
        continue;
      geom.push([projectx(line[0]), projecty(line[1]), 0]);
      geom.push([projectx(line[2]), projecty(line[3]), projectc(line[4])]);
      geom.push([projectx(line[2]), projecty(line[3]), 0]);
    }
 
    var buf = JSON.stringify(geom);
    this.socket.send(buf);
  }

  finish()
  {
  }
}

var recorder = new Recorder();