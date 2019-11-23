class Renderer
{
  constructor(w, h)
  {
    this.elem = document.createElement("canvas");
    this.elem.style = "border:1px gray solid;";
    this.elem.width = w;
    this.elem.height = h;
    document.documentElement.style.background = "#000000";
    document.documentElement.appendChild(this.elem);
    this.ctx = this.elem.getContext("2d");
    this.memory = [];
    this.lines = [];
    this.anim = 0;
    this.test = {};
  }

  sortOrder()
  {
    return -1;
  }

  Clear()
  {
    this.elem.width = this.elem.width;
    this.memory = [];
    this.lines = [];
    this.cacheLines = {};
    this.test = {};
  }

  toClipPoly(p)
  {
    return [p.map(pt => ({X: Math.floor(pt.x), Y:Math.floor(pt.y), id:pt.id}))];
  }

  subtractPath(xyPaths1, xyPaths2)
  {
    var subj_paths = ClipperLib.JS.Clone(xyPaths1);
    var clip_paths = ClipperLib.JS.Clone(xyPaths2);

    var cpr = new ClipperLib.Clipper();
    cpr.AddPaths(subj_paths, ClipperLib.PolyType.ptSubject, true);
    cpr.AddPaths(clip_paths, ClipperLib.PolyType.ptClip, true);

    var subject_fillType = ClipperLib.PolyFillType.pftNonZero;
    var clip_fillType = ClipperLib.PolyFillType.pftNonZero;

    var solution_paths = new ClipperLib.Paths();
    cpr.Execute(ClipperLib.ClipType.ctDifference, solution_paths, subject_fillType, clip_fillType);

    return solution_paths;
  }
                 
  addPath(xyPaths1, xyPaths2)
  {
    var subj_paths = ClipperLib.JS.Clone(xyPaths1);
    var clip_paths = ClipperLib.JS.Clone(xyPaths2);

    var cpr = new ClipperLib.Clipper();
    cpr.AddPaths(subj_paths, ClipperLib.PolyType.ptSubject, true);
    cpr.AddPaths(clip_paths, ClipperLib.PolyType.ptClip, true);

    var subject_fillType = ClipperLib.PolyFillType.pftNonZero;
    var clip_fillType = ClipperLib.PolyFillType.pftNonZero;

    var solution_paths = new ClipperLib.Paths();
    cpr.Execute(ClipperLib.ClipType.ctUnion, solution_paths, subject_fillType, clip_fillType);

    return solution_paths;
  }

  Finish(groups)
  {
//    console.log(this.lines.length);
    this.ctx.lineWidth = 3;
    this.anim ++;
//console.log(this.lines[0]);
//    this.lines.sort( (a, b) => ((a.id > b.id) - (a.id < b.id))*1000 + (a) );

    for (var i=0; i < Math.min(this.lines.length, 1000); i++)
    {
      var l = this.lines[i];
      var c = l[4];
      this.ctx.strokeStyle = ["#ff00ff", "rgba(255, 0, 0, 0.7)", "rgba(0, 255, 0, 0.7)", "rgba(0, 0, 255, 0.5)"][c];
      this.ctx.beginPath();
      this.ctx.moveTo(l[0], l[1]);
      this.ctx.lineTo(l[2], l[3]);
      this.ctx.stroke();
    }
  }

  clipLine(l, extView)
  {
    var viewport = {left:0, right:600, top:0, bottom:600};
//    if (extView)
//      viewport = {left:-600, right:600+600, top:-600, bottom:600+600};

    var r = lineclip(
      [[l[0], l[1]], [l[2], l[3]]], // line
      [viewport.left, viewport.top, viewport.right, viewport.bottom]); // bbox

    if (!r || r.length == 0)
      return false;

    l[0] = Math.floor(r[0][0][0]);
    l[1] = Math.floor(r[0][0][1]);
    l[2] = Math.floor(r[0][1][0]);
    l[3] = Math.floor(r[0][1][1]);
    l[4] = l[4];
    return l;   
  }

  checkLine(l)
  {
    var w = 600, h = 600;
    if (l[0] < 0 && l[2] < 0) return;
    if (l[1] < 0 && l[3] < 0) return;
    if (l[0] > w && l[2] > w) return;
    if (l[1] > h && l[3] > h) return;

    var hash = Math.floor(Math.min(l[0], l[2])) + "," + Math.floor(Math.min(l[1], l[3])) + "," + 
        Math.floor(Math.max(l[2], l[0])) + "," + Math.floor(Math.max(l[3], l[1]));

    if (this.cacheLines[hash])
      return;

    this.cacheLines[hash] = 1;

    l = this.clipLine(l);
    if (l)
      this.lines.push(l);
  }

  Poly(poly)
  {  
/*
    var ppoly = []
    for (var i =0; i<4; i++)
    {
      var l = this.clipLine([poly[i].x, poly[i].y, poly[(i+1)%poly.length].x, poly[(i+1)%poly.length].y], true);
      if (!l)
        return;
      ppoly.push({x:l[0], y:l[1], id:poly[0].id});
    }
*/
    var clipPath = this.toClipPoly(poly);
    var newPath = this.subtractPath(clipPath, this.memory);

    if (newPath.length == 0)
      return;

    var pathPoints = {};
    for (var i in clipPath[0])
      pathPoints[clipPath[0][i].X + "_" + clipPath[0][i].Y] = clipPath[0][i].id;
//console.log(pathPoints);
    for (var i in newPath[0])
        newPath[0][i].id = pathPoints[newPath[0][i].X + "_" + newPath[0][i].Y];

    // match clipPath attributes to newPath
    var rid = poly[0].id;
    for (var j in newPath)
    {
      var p = newPath[j];
      for (var i=0; i<p.length-1; i++)
{

var clr = 0;

if (typeof(p[i].id) != "undefined")
{
  if (p[i].id.substr(0,4) == "ring")
    clr = 1;
  if (p[i].id.substr(0,4) == "line")
    clr = 3;
  if (p[i].id.substr(0,5) == "line0")
    clr = 2;
}
/*
else if (typeof(p[i+1].id) != "undefined")
{
  if (p[i+1].id.substr(0,4) == "ring")
    clr = 2;
  if (p[i+1].id.substr(0,4) == "line")
    clr = 1;
} */
//if (clr != 0) clr = 3;
//clr = clr == 1 ? 3 : 1
var clr = 1;
        this.checkLine([p[i].X, p[i].Y, p[i+1].X, p[i+1].Y, clr]);
}
    }

    this.memory = this.addPath(this.memory, newPath);
  }

  GetRenderData()
  {
    //this.lines.sort((a, b) => a.id - b.id)??
    this.lines.sort((a, b) => a[1] - b[1]);
    return this.lines;
  }
}
