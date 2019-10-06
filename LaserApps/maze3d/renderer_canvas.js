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
    this.elem.width = this.elem.width;
  }
  Poly(p)
  {
    this.ctx.strokeStyle = ["#ff00ff", "#ff0000", "#00ff00", "#0000b0"][p[0].c];
    this.ctx.lineJoin="round";
    this.ctx.lineWidth = 5;
    this.ctx.beginPath();

    this.ctx.moveTo(p[0].x, p[0].y);
    for (var i=0; i<p.length; i++)
      this.ctx.lineTo(p[i].x, p[i].y);
    this.ctx.lineTo(p[0].x, p[0].y);
    this.ctx.stroke();
    this.ctx.fill();
  }
  Finish()
  {
  }
  sortOrder()
  {
    return 1;
  }
}
