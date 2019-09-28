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
  Quad(p)
  {
if (!p[0] || !p[1] || !p[2] || !p[3]) 
  return;
        this.ctx.strokeStyle = "#ff0000";
        this.ctx.lineWidth = 5;
        this.ctx.fillStyle = "#0000b0";
        this.ctx.beginPath();
        this.ctx.moveTo(p[0].x, p[0].y);
        this.ctx.lineTo(p[1].x, p[1].y);
        this.ctx.lineTo(p[2].x, p[2].y);
        this.ctx.lineTo(p[3].x, p[3].y);
        this.ctx.lineTo(p[0].x, p[0].y);
        this.ctx.stroke();
        this.ctx.fill();
  }

}
var mapx = 
  "#####" + 
  "#   #" +
  "#   #" +
  "#   #" +
  "#   #";

var map = [];
for (var y=0; y<5; y++)
{
  var line = [];
  for (var x =0; x<5; x++)
    line.push(mapx.charAt(y*5+x) == "#" ? 1 : 0);
  map.push(line);
}

var px =0, py = 0, pa = 0;
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

function Mul(p, space)
{
  var p = { 
    x: p.o * space[3*4+0] + p.x * space[0*4+0] + p.y * space[1*4+0] + p.z * space[2*4+0],
    y: p.o * space[3*4+1] + p.x * space[0*4+1] + p.y * space[1*4+1] + p.z * space[2*4+1],
    z: p.o * space[3*4+2] + p.x * space[0*4+2] + p.y * space[1*4+2] + p.z * space[2*4+2],
  };

if (p.z <= 0) return;

    foc = 20;
    scale = foc / (foc + p.z)*30; // * 600*0.4;
    return { 
      x : 300 + p.x * scale,
      y : 300 + p.y * scale,
      z : p.z//-p.z
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
  space = Mul4(space, Translation(-3+px, -3+py, -0.5));
  space = Mul4(space, Scale(15, 15, 15));
  space = Mul4(space, Rotation(pa, 0, 0, 1));
  space = Mul4(space, Rotation(90, 1, 0, 0));
  return space;
}

function Quad(q)
{
  var space = GetProjection()
  q[0].o = 1;
  q[1].o = 1;
  q[2].o = 1;
  q[3].o = 1;
  renderer.Quad([Mul(q[0], space), Mul(q[1], space), Mul(q[2], space), Mul(q[3], space)]);
}
/*
  function rotate(p, x, y, z)
  {
    x *= 3.141592/180;
    y *= 3.141592/180;
    z *= 3.141592/180;

    var sx = x==0 ? 0 : Math.sin(x);
    var cx = x==0 ? 1 : Math.cos(x);
    var sy = y==0 ? 0 : Math.sin(y);
    var cy = y==0 ? 1 : Math.cos(y);
    var sz = z==0 ? 0 : Math.sin(z);
    var cz = z==0 ? 1 : Math.cos(z);

    // rotation around x
    xy = cx*p.y - sx*p.z;
    xz = sx*p.y + cx*p.z;
    // rotation around y
    yz = cy*xz - sy*p.x;
    yx = sy*xz + cy*p.x;
    // rotation around z
    zx = cz*yx - sz*xy;
    zy = sz*yx + cz*xy;

    return {x:zx, y:zy, z:yz};
  }

  function project(p)
  {
    foc = 10;
    scale = foc / (foc + p.z) * can.width*0.4; //
    return { 
      x : can.width/2 + p.x * scale,
      y : can.height/2 + p.y * scale,
      z : -p.z
    };
  }

*/
function Wall(x, y)
{
  return [
  [
    {x:x, y:y, z:0},
    {x:x+1, y:y, z:0},
    {x:x+1, y:y, z:1},
    {x:x, y:y, z:1},
  ],
  [
    {x:x, y:y, z:0},
    {x:x, y:y+1, z:0},
    {x:x, y:y+1, z:1},
    {x:x, y:y, z:1},
  ],
  [
    {x:x+1, y:y, z:0},
    {x:x+1, y:y+1, z:0},
    {x:x+1, y:y+1, z:1},
    {x:x+1, y:y, z:1},
  ],
  [
    {x:x, y:y+1, z:0},
    {x:x+1, y:y+1, z:0},
    {x:x+1, y:y+1, z:1},
    {x:x, y:y+1, z:1},
  ]];
}

function main()
{
  renderer.Clear();
  var sorted = [];
  var projection = GetProjection();

  for (var y=0; y<5; y++)
    for (var x =0; x<5; x++)
    {
      if (!map[y][x])
        continue;

      var faces = Wall(x, y);
      for (var i in faces)
      {
        var face = faces[i];
        var center = {
          x:(face[0].x + face[1].x + face[2].x + face[3].x)/4,
          y:(face[0].y + face[1].y + face[2].y + face[3].y)/4,
          z:(face[0].z + face[1].z + face[2].z + face[3].z)/4,
          o:1}

        var projected = Mul(center, projection);
        if (projected)
        {
          face[0].d = projected.z;
          sorted.push(face);
        }
      }
    }

  sorted.sort((a, b) => 
    {var d = b[0].d - a[0].d;
      if (d<0) return -1;
      if (d>0) return +1;
      return 0;
    });

var filter = ((new Date()).getTime()/100)%50;

  for (var i=0; i<sorted.length; i++)
    Quad(sorted[i]);
/*
  for (var y=0; y<5; y++)
  {
    for (var x =0; x<5; x++)
      if (map[y][x])
  {
        Wall(x, y);
//  return;
  }
  }*/
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


setInterval(()=>
{
  main();
  if (keys.left)
    pa -= 5;
  if (keys.right)
    pa += 5;
  if (keys.up)
  {
    py += Math.cos(pa*Math.PI/180)*0.3;
    px -= Math.sin(pa*Math.PI/180)*0.3;
  }
  if (keys.down)
  {
    py -= Math.cos(pa*Math.PI/180)*0.3;
    px += Math.sin(pa*Math.PI/180)*0.3;
  }
}, 100);
//renderer.Quad([{x:100, y:100}, {x:200, y:100}, {x:200, y:200}, {x:100, y:200}]);