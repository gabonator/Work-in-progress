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
  }
  Render(map)
  {
    var w = 30;
    var i = 0;
    var palette = ["#202020", "#ff0000", "#00ff00", "#0000ff"];
    this.ctx.lineWidth = 2;
    var d = map.data;
    for (var y=0; y<=map.h; y++)
    {
      // horizontal lines
      for (var x=0; x<map.w; x++)
      {
        this.ctx.strokeStyle = palette[d[i++]];
        this.ctx.beginPath();
        this.ctx.moveTo(x*w, y*w);
        this.ctx.lineTo((x+1)*w, y*w);
        this.ctx.stroke();
      }
    }
    // vertical lines
    for (var y=0; y<map.h; y++)
      for (var x=0; x<=map.w; x++)
      {
        this.ctx.strokeStyle = palette[d[i++]];
        this.ctx.beginPath();
        this.ctx.moveTo(x*w, y*w);
        this.ctx.lineTo(x*w, (y+1)*w);
        this.ctx.stroke();
      }

    for (var y=0; y<map.h; y++)
      for (var x=0; x<map.w; x++)
      {
        var c = d[i++];
        this.ctx.strokeStyle = c == 0 ? "#000000" : palette[c];
        this.ctx.beginPath();
        this.ctx.moveTo(x*w+w/2-4, y*w+w/2-4);
        this.ctx.lineTo(x*w+w/2+4, y*w+w/2+4);
        this.ctx.moveTo(x*w+w/2+4, y*w+w/2-4);
        this.ctx.lineTo(x*w+w/2-4, y*w+w/2+4);
        this.ctx.stroke();
      }
  }
}

var renderer = new Renderer(300, 600);

var frame = 0;
var i = 0;
setInterval(() =>
{
  if (frame++ < gameplay[i].f)
    return;
  renderer.Render({w:8, h:14, data:gameplay[i++].d});
}, 50);
