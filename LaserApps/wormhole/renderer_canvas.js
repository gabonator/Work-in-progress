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
  Clear()
  {
    this.data = [];
    this.elem.width = this.elem.width;
  }
  Poly(p)
  {
    this.data.push(p.map(t => [t.x, t.y, t.c]) ); //[p[0].x, p[0].y, p[1].x, p[1].y, p[0].c]);

    this.ctx.strokeStyle = ["#ff00ff", "#ff0000", "#00ff00", "#0000b0"][p[1].c];
    this.ctx.fillStyle = "#ff0000"; //"rgba(0, 0, 200, 0.3)";
    this.ctx.lineJoin = "round";
    this.ctx.lineWidth = 5;
    this.ctx.beginPath();

    for (var i=0; i<p.length; i++)
    {
      if (p[i].c == 0)
        this.ctx.moveTo(p[i].x, p[i].y);
      else
        this.ctx.lineTo(p[i].x, p[i].y);
    }
    this.ctx.closePath();
//    this.ctx.stroke();
    this.ctx.fill();
  }
  Finish()
  {
  }
  sortOrder()
  {
    return 1;
  }
  GetRenderData()
  {
    return this.data;
  }
}
