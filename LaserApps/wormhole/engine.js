class Engine
{
  Mul(a, b)
  {
    var resultingArray = new Array(16).fill(0);
    for (var i = 0; i < 4; i++) {
          for (var j = 0; j < 4; j++) {
              resultingArray[i*4+j] = 0;
              for (var k = 0; k < 4; k++) {
                  resultingArray[i*4+j] += a[i*4+k] * b[k*4+j];
              }
          }
      }
      return resultingArray;
  }

  Subtract(a, b)
  {
    return {
      x:a.x-b.x,
      y:a.y-b.y,
      z:a.z-b.z
    };
  }

  Length(v)
  {
    return Math.sqrt(v.x*v.x + v.y*v.y + v.z*v.z);
  }

  Normalize(v)
  {
    var l = 1/this.Length(v);
    return {x: v.x * l, y: v.y * l, z: v.z*l};
  }

  Cross(a, b)
  {
    return {
      x: (a.y * b.z) - (a.z * b.y),
      y: (a.z * b.x) - (a.x * b.z),
      z: (a.x * b.y) - (a.y * b.x)
    }
  }

  Project(p, space)
  {
    var p = { 
      x: p.o * space[3*4+0] + p.x * space[0*4+0] + p.y * space[1*4+0] + p.z * space[2*4+0],
      y: p.o * space[3*4+1] + p.x * space[0*4+1] + p.y * space[1*4+1] + p.z * space[2*4+1],
      z: p.o * space[3*4+2] + p.x * space[0*4+2] + p.y * space[1*4+2] + p.z * space[2*4+2],
      c: p.c
    };

    var foc = 20;
    var scale = foc / (foc + p.z)*30;
    if (scale < 0) return;

    return { 
      x : Math.floor(300 + p.x * scale),
      y : Math.floor(300 + p.y * scale),
      z : Math.floor(p.z),
      c : p.c
    };
  }

  Rotation(angle, x, y, z)
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

  Translation(x, y, z)
  {                  
    return [1, 0, 0, 0,
            0, 1, 0, 0,
            0, 0, 1, 0,
            x, y, z, 1];
  }

  Scale(x, y, z)
  {                  
    return [x, 0, 0, 0,
            0, y, 0, 0,
            0, 0, z, 0,
            0, 0, 0, 1];
  }

  Identity()
  {
    return [1, 0, 0, 0,
            0, 1, 0, 0,
            0, 0, 1, 0,
            0, 0, 0, 1];
  }
}

class Scene
{
  constructor()
  {
    this.engine = new Engine();
    this.renderer = new Renderer(600, 600);
    this.px = 0;
    this.py = 0;
    this.pz = 0;
    this.pax = 0;    
    this.pay = 0;    
    this.paz = 0;    
  }

  GetProjection()
  {
    var space = this.engine.Identity();
    space = this.engine.Mul(space, this.engine.Translation(-this.px, -this.py, -this.pz));
    space = this.engine.Mul(space, this.engine.Rotation(this.pax, 0, 0, 1));
    space = this.engine.Mul(space, this.engine.Rotation(this.pay, 0, 1, 0));
    space = this.engine.Mul(space, this.engine.Rotation(this.paz, 1, 0, 0));
//    space = this.engine.Mul(space, this.engine.Translation(-Math.sin(this.pa*Math.PI/180)*10, Math.cos(this.pa*Math.PI/180)*10, 0.05));
    space = this.engine.Mul(space, this.engine.Scale(15, 15, 15));
//    space = this.engine.Mul(space, this.engine.Rotation(90, 0, 0, 1));
    return space; 
  }

  Begin()
  {
    this.projection = this.GetProjection();
    this.elements = [];
  }

  FinishQuads(groups)
  {
    this.renderer.Clear();

    for (var i=0; i<this.elements.length; i++)
    {
       var poly = this.ProjectPoly(this.projection, this.elements[i]);
       if (poly && poly.length > 0)
         this.renderer.Poly(poly);
    }
    this.renderer.Finish(groups);
  }

  FinishLines()
  {
    this.renderer.Clear();
    for (var i=0; i<this.elements.length; i++)
    {
       var poly = this.ProjectPoly(this.projection, this.elements[i]);
       if (poly && poly.length > 0)
         this.renderer.Poly(poly);
    }
    this.renderer.Finish();
  }

  ProjectPoly(projection, q)
  {
    var screenPoly = [];
    for (var i=0; i<q.length; i++)
    {
      var pt = q[i];
      pt.o = 1;
      var screenPt = this.engine.Project(pt, projection);
     
      if (!screenPt)
          return;
      screenPt.id = pt.id;
      screenPoly.push(screenPt);
    }
    return screenPoly;
  }

  DrawLines(q)
  {
    //this.elements.push(this.ProjectPoly(q));
    this.elements.push(q);
  }
  DrawQuads(q)
  {
    //this.elements.push(this.ProjectPoly(q));
    this.elements = q;
  }
}
