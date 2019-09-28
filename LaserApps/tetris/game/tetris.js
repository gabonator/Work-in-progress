class Map
{
  constructor(w, h)
  {
    this.w = w;
    this.h = h;
    this.a = new Array(w*h).fill(0);
  }
  Set(x, y, c)
  {
    this.a[y*this.w+x] = c;
  }
  Get(x, y)
  {
    if (x<0 || y<0 || x>=this.w || y>=this.h)
      return 0;
    return this.a[y*this.w+x];
  }
  IsFree(x, y)
  {
    if (x<0 || y<0 || x>=this.w || y>=this.h)
      return false;
    return this.a[y*this.w+x] == 0;
  }
  RenderData()
  {
    var d = [];

    // horizontal lines
    for (var y=0; y<this.h; y++)
      for (var x=0; x<this.w; x++)
        d.push(this.Get(x, y) ? this.Get(x, y) : this.Get(x, y-1));

    for (var x=0; x<this.w; x++)
      d.push(this.Get(x, this.h-1));

    // vertical lines
    for (var y=0; y<this.h; y++)
      for (var x=0; x<=this.w; x++)
          d.push(this.Get(x, y) ? this.Get(x, y) : this.Get(x-1, y));

    for (var y=0; y<this.h; y++)
      for (var x=0; x<this.w; x++)
        if (this.Get(x, y) == 0 & this.Get(x-1, y) != 0 && this.Get(x+1, y) != 0 && this.Get(x, y-1) != 0)
          d.push(this.Get(x-1, y));
        else
          d.push(0);

    return d;
  }
}

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
    var d = map.RenderData();
    var palette = ["#202020", "#ff0000", "#00ff00", "#0000ff"];
    this.ctx.lineWidth = 2;
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

        this.ctx.strokeStyle = !c ? "#000000" : palette[c];
        this.ctx.beginPath();
        this.ctx.moveTo(x*w+w/2-4, y*w+w/2-4);
        this.ctx.lineTo(x*w+w/2+4, y*w+w/2+4);
        this.ctx.moveTo(x*w+w/2+4, y*w+w/2-4);
        this.ctx.lineTo(x*w+w/2-4, y*w+w/2+4);
        this.ctx.stroke();
      }
  }
}

class Dice
{
  constructor(p1, p2, p3, p4)
  {
    var count = p1.length/4;
    this.patterns = [];
    for (var i=0; i<count; i++)
    {
      var pat = p1.substr(i*4, 4) + p2.substr(i*4, 4) + p3.substr(i*4, 4) + p4.substr(i*4, 4);
      this.patterns.push(pat.split("").map(c => c == "#" ? 1 : 0));
    }
  }

  Try(map, bx, by, r)
  {
    for (var x=0; x<4; x++)
      for (var y=0; y<4; y++)
        if (this.patterns[r % this.patterns.length][x+y*4])
          if (!map.IsFree(bx+x, by+y))
            return false;
    return true;
  }

  Draw(map, bx, by, r, c)
  {
    for (var x=0; x<4; x++)
      for (var y=0; y<4; y++)
      {
        if (this.patterns[r % this.patterns.length][x+y*4])
          map.Set(bx+x, by+y, c);
      }
  }
}

class Tetris
{
  constructor(map)
  {
    this.map = map;
    this.eraseLineAnim = -1;

    this.dices = [
      new Dice(
        "    ..#.",
        "####..#.",
        "    ..#.",
        "    ..#."),
      new Dice(
        "##  ",
        "##  ",
        "    ",
        "    "),
      new Dice(
        " #  .#.. #  ....",
        " ## ###.##  ###.",
        " #  .... #  .#..",
        "    ....    ...."),
      new Dice(
        " #  ....##  ..#.",
        " #  ###. #  ###.",
        " ## #... #  ....",
        "    ....    ...."),
      new Dice(
        "##  ..#. #  ....",
        " #  ###. #  ###.",
        " #  .... ## #...",
        "    ....    ...."),
      new Dice(
        "##  .#..",
        " ## ##..",
        "    #...",
        "    ...."),
      new Dice(
        " ## #...",
        "##  ##..",
        "    .#..",
        "    ...."),
    ];
  }


  Do(keys)
  {
    if (this.eraseLineAnim != -1)
    {
      for (var x=0; x<this.map.w; x++)
        this.map.Set(x, this.eraseLineAnim, 1+(this.eraseLinePhase)%3);

      if (this.eraseLinePhase-- == 0)
      {
        // scroll
        if (this.eraseLineAnim == 0)
        {
          for (var x=0; x<this.map.w; x++)
            this.map.Set(x, this.eraseLineAnim, 0);   
        }

        for (var y=this.eraseLineAnim; y>0; y--)
          for (var x=0; x<this.map.w; x++)
            this.map.Set(x, y, this.map.Get(x, y-1));

        // another one?
        this.CheckErasedLine();

        // game over animation finished
        if (this.gameOver && this.eraseLineAnim == -1)
          this.gameOver = false;
      }
      return;
    }

    if (this.gameOver)
      return;

    if (!this.current)
    {
      var dice = this.dices[Math.floor(Math.random()*this.dices.length)];
      this.current = {x:3, y:0, dice:dice, r:0, c:Math.floor(1+Math.random()*3)};
      if (!this.current.dice.Try(this.map, this.current.x, this.current.y, this.current.r, this.current.c))
      {
        // cant place new dice
        this.current.dice.Draw(this.map, this.current.x, this.current.y, this.current.r, this.current.c);
        this.gameOver = true;
        this.CheckErasedLine();
        return;
      }
      this.current.dice.Draw(this.map, this.current.x, this.current.y, this.current.r, this.current.c);
      return;
    }

    var dy = keys.down ? 1 : 0;
    var dx = (keys.left ? -1 : 0) + (keys.right ? +1 : 0);
    var dr = keys.up ? 1 : 0;
    if (dy) {dx = 0; dr = 0;}
    
    if (dx != 0 || dy != 0 || dr != 0)
    {
      this.current.dice.Draw(this.map, this.current.x, this.current.y, this.current.r, 0);
      if (this.current.dice.Try(this.map, this.current.x+dx, this.current.y+dy, this.current.r+dr))
      {
        this.current.x += dx;
        this.current.y += dy;
        this.current.r += dr;
        this.current.dice.Draw(this.map, this.current.x, this.current.y, this.current.r, this.current.c);
      } else
      {
        this.current.dice.Draw(this.map, this.current.x, this.current.y, this.current.r, this.current.c);
        if (dy==1)
        {
          delete this.current;
          this.CheckErasedLine();
        }
      }
    }
  }

  CheckErasedLine()
  {
    this.eraseLineAnim = -1;
    if (this.gameOver)
    {
      // find first non empty
      for (var y = 0; y < this.map.h; y++)
      {
        for (var x=0; x<this.map.w; x++)
          if (!this.map.IsFree(x, y))
          {
            this.eraseLineAnim = y;
            this.eraseLinePhase = 3;
            return;
          }
      }
      return;
    }

    // find full line
    for (var y = this.map.h-1; y>0; y--)
    {
      var full = true;
      for (var x=0; x<this.map.w; x++)
        if (this.map.IsFree(x, y))
        {
          full = false;
          break;
        }
      if (full)
      {
        this.eraseLineAnim = y;
        this.eraseLinePhase = 10;
        return;
      }
    }
  }
}

var map = new Map(8, 14);
var renderer = new Renderer(300, 600);
var tetris = new Tetris(map);
var keys = {};

document.onkeydown = (e) =>
{
  e = e || window.event;

  if (e.keyCode == 38)
  {
    keys.up = true;
    e.preventDefault();
  }
  if (e.keyCode == 40)
  {
    keys.down = true;
    e.preventDefault();
  }
  if (e.keyCode == 37)
    keys.left = true;
  if (e.keyCode == 39)
    keys.right = true;
};

var counter = 0;
setInterval(() =>
{
  if (++counter % 10 == 0)
  {
    tetris.Do({down:true});
  } else
  {
    tetris.Do(keys);
    keys = {};
  }
  renderer.Render(map);
  typeof(logger) != "undefined" && logger.Process(map.RenderData(), counter);
}, 100);
