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
}

var mapx = 
 ["#####   ",
  "# H #   ",
  "#   #   ",
  "#   #   ",
  "### #   ", 
  "        ",
  "        ",
  "        "];

var map = [];
for (var y=0; y<mapx.length; y++)
{
  var line = [];
  for (var x =0; x<mapx[0].length; x++)
    line.push(mapx[y].charAt(x));
  map.push(line);
}

var px = 3.5, py = 6, pa = 0;
var renderer = new Renderer(600, 600);

function Mul4(a, b)
{
  var resultingArray = new Array(16).fill(0);
  for (var i = 0; i < 4; i++) {
        for (var j = 0; j < 4; j++) {
            resultingArray[i*4+j] = 0;
            for (k = 0; k < 4; k++) {
                resultingArray[i*4+j] += a[i*4+k] * b[k*4+j];
            }
        }
    }
    return resultingArray;
}

function Project(p, space)
{
  var p = { 
    x: p.o * space[3*4+0] + p.x * space[0*4+0] + p.y * space[1*4+0] + p.z * space[2*4+0],
    y: p.o * space[3*4+1] + p.x * space[0*4+1] + p.y * space[1*4+1] + p.z * space[2*4+1],
    z: p.o * space[3*4+2] + p.x * space[0*4+2] + p.y * space[1*4+2] + p.z * space[2*4+2],
  };

  foc = 20;
  scale = foc / (foc + p.z)*30;
  if (scale < 0) return;

  return { 
    x : 300 + p.x * scale,
    y : 300 + p.y * scale,
    z : p.z
  };
}

function Rotation(angle, x, y, z)
{
  var c = Math.cos(angle*Math.PI/180);
  var s = Math.sin(angle*Math.PI/180);
  return [
    x*x*(1-c)+c, x*y*(1-c)-z*s, x*z*(1-c)+y*s, 0,
    x*y*(1-c)+z*s, y*y*(1-c)+c, y*z*(1-c)-x*s, 0,
    x*z*(1-c)-y*s, y*z*(1-c)+x*s, z*z*(1-c)+c, 0,
    0, 0, 0, 1
  ];
}

function Translation(x, y, z)
{                  
  return [1, 0, 0, 0,
          0, 1, 0, 0,
          0, 0, 1, 0,
          x, y, z, 1];
}

function Scale(x, y, z)
{                  
  return [x, 0, 0, 0,
          0, y, 0, 0,
          0, 0, z, 0,
          0, 0, 0, 1];
}

function Identity()
{
  return [1, 0, 0, 0,
          0, 1, 0, 0,
          0, 0, 1, 0,
          0, 0, 0, 1];
}

function GetProjection()
{
  var space = Identity();
  space = Mul4(space, Translation(-px, -py, -0.2));
  space = Mul4(space, Translation(-Math.sin(pa*Math.PI/180)*1, Math.cos(pa*Math.PI/180)*1, 0.05));
  space = Mul4(space, Scale(15, 15, 15));
  space = Mul4(space, Rotation(pa, 0, 0, 1));
  space = Mul4(space, Rotation(90, 1, 0, 0));
  return space;
}

function ProjectPoly(projection, q)
{
  var screenPoly = [];
  for (var i in q)
  {
    var pt = q[i];
    pt.o = 1;
    var screenPt = Project(pt, projection);
    if (!screenPt)
      return;
    screenPoly.push(screenPt);
  }
  screenPoly[0].c = q[0].c;
  return screenPoly;
}

function Floor(x, y)
{
  return [
  [
    {c:3, zIndex:+100, x:x, y:y, z:1},
    {x:x+1, y:y, z:1},
    {x:x+1, y:y+1, z:1},
    {x:x, y:y+1, z:1},
  ]];
}

function Heart(x, y)
{
  x += 0.5;
  y += 0.5;
  z = 0.8;
  var a = new Date().getTime()/1000*1.5;
  var vx = 0.3*Math.cos(a);
  var vy = 0.3*Math.sin(a);
  var vz = 0.3;
  var heart = 
    [[0, 0], [3, 3], [4, 6], [2.5, 7], [1, 6.5], [0, 5],
     [-1, 6.5], [-2.5, 7], [-4, 6], [-3, 3]];

  var k = 1/4;
  var heart3d = [];
  for (var i in heart)
    heart3d.push({c:2, x:x+vx*heart[i][0]*k, y:y+vy*heart[i][0]*k, z:z-vz*heart[i][1]*k});

  return [heart3d];
}

function Wall(x, y)
{
  return [
  [
    {c:1, x:x, y:y, z:0},
    {x:x+1, y:y, z:0},
    {x:x+1, y:y, z:1},
    {x:x, y:y, z:1},
  ],
  [
    {c:1, x:x, y:y, z:0},
    {x:x, y:y+1, z:0},
    {x:x, y:y+1, z:1},
    {x:x, y:y, z:1},
  ],
  [
    {c:1, x:x+1, y:y, z:0},
    {x:x+1, y:y+1, z:0},
    {x:x+1, y:y+1, z:1},
    {x:x+1, y:y, z:1},
  ],
  [
    {c:1, x:x, y:y+1, z:0},
    {x:x+1, y:y+1, z:0},
    {x:x+1, y:y+1, z:1},
    {x:x, y:y+1, z:1},
  ]];
}

function main()
{
  var sorted = [];
  var projection = GetProjection();
  var faces = [];

  for (var y=0; y<map.length; y++)
    for (var x =0; x<map[y].length; x++)
    {
      if (map[y][x] == " ")
        faces = faces.concat(Floor(x, y));
      if (map[y][x] == "#")
        faces = faces.concat(Wall(x, y));
      if (map[y][x] == "H")
        faces = faces.concat(Heart(x, y));
    }

  for (var i in faces)
  {
    var face = faces[i];
    var center = {
      x:(face[0].x + face[1].x + face[2].x + face[3].x)/4,
      y:(face[0].y + face[1].y + face[2].y + face[3].y)/4,
      z:(face[0].z + face[1].z + face[2].z + face[3].z)/4,
      o:1}

    var projected = Project(center, projection);
    if (projected)
    {
      face[0].d = projected.z;
      if (typeof(face[0].zIndex) != "undefined")
        face[0].d += face[0].zIndex;
      sorted.push(face);
    }
  }

  sorted.sort((a, b) => Math.sign(b[0].d - a[0].d));

  renderer.Clear();
  for (var i=0; i<sorted.length; i++)
      renderer.Poly(ProjectPoly(projection, sorted[i]));
}  

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

document.onkeyup = (e) =>
{
  e = e || window.event;

  if (e.keyCode == 38)
  {
    keys.up = false;
    e.preventDefault();
  }
  if (e.keyCode == 40)
  {
    keys.down = false;
    e.preventDefault();
  }
  if (e.keyCode == 37)
    keys.left = false;
  if (e.keyCode == 39)
    keys.right = false;
};

function check(x, y)
{                 
  x = Math.floor(x+1000)-1000;
  y = Math.floor(y+1000)-1000;

  if (x < 0 || x >= map[0].length)
    return true;
  if (y < 0 || y >= map.length)
    return true;

  return map[y][x] != "#";
}

setInterval(()=>
{
  main();
  if (keys.left)
    pa -= 5;
  if (keys.right)
    pa += 5;

  var dx = 0, dy = 0;
  if (keys.down)
  {
    dy = Math.cos(pa*Math.PI/180)*0.1;
    dx =-Math.sin(pa*Math.PI/180)*0.1;
  }
  if (keys.up)
  {
    dy =-Math.cos(pa*Math.PI/180)*0.1;
    dx = Math.sin(pa*Math.PI/180)*0.1;
  }
  if (dx != 0 && check(px+dx, py))
    px += dx;
  if (dy != 0 && check(px, py+dy))
    py += dy;
}, 30);

