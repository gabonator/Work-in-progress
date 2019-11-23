
function trajectory(t)
{
//  return {x:0, y:Math.cos(Math.PI*2*t/4)*0.3, z:t*1};
//  return {x:Math.cos(Math.PI*2*t/4)*0.3, y:0, z:t*1};
//  return {x:Math.cos(Math.PI*2*t/8)*1, y:Math.cos(Math.PI*2*t/13)*1.5, z:t*2};
 // t = 0..10
  return {x:Math.cos(Math.PI*2*t/10)*1, y:Math.cos(Math.PI*2*t/10 + Math.PI/2)*1.8, z:t*2};
}

function cylinder(i, z, c, id)
{
  var r = 1.2;
  v1 = {x:0, y:1, z:0};

  var v2 = e.Cross(v1, e.Subtract(trajectory(z), trajectory(z-1)));
  if (e.Length(v2) < 0.001)
    v2 = {x:0, y:1, z:0};

  v1 = e.Normalize(v1);
  v2 = e.Normalize(v2);

  var dx = Math.cos(i*2*Math.PI)*r;
  var dy = Math.sin(i*2*Math.PI)*r;
  var p = trajectory(z);

  var r = {
    x:p.x + v1.x*dx + v2.x*dy, 
    y:p.y + v1.y*dx + v2.y*dy, 
    z:p.z + v1.z*dx + v2.z*dy, 
    c:c, id:id};

  return r;
}

var scene = new Scene();
var e = scene.engine;
var frame = 0;
var frames = 70;

setInterval( ()=>
{
//  frame++;
//  frame = (frame + 1)%100;
  var f = frame/frames*10;

  var v = e.Subtract(trajectory(f+2), trajectory(f));
  scene.pay = Math.atan2(v.x, v.z)/Math.PI*180;
  scene.paz = Math.atan2(-v.y, v.z)/Math.PI*180;

  var ofs = 0;
  scene.px = trajectory(f+ofs).x;
  scene.py = trajectory(f+ofs).y;
  scene.pz = trajectory(f+ofs).z;
  scene.Begin();

  var n = 60;
  var f0 = Math.floor(f);
  var quads = [];
//  var groups = [[]];
//  for (var y=10; y>=0; y--)
  for (var y=0; y<=6; y++)
  {
    var x = 0;
//    groups[0].push([cylinder(x, y+f0, 0), cylinder(x, y+1+f0, 0)]);
    for (var x=0; x<7; x++)
    {
      var id = x+"_"+y+"_";
      quads.push([
        cylinder(x/7, y+f0,     0, ""), 
        cylinder((x+1)/7, y+f0,   1, "ring"+y+"_"+x), 
        cylinder((x+1)/7, y+1+f0, 1, "line"+(x+1)+"_"+y),   
        cylinder(x/7, y+1+f0,   1, "ring"+(y+1)+"_"+x),
        cylinder(x/7, y+f0,     1, "line"+x+"_"+y)]);
    }
  }
  scene.DrawQuads(quads);
  scene.FinishQuads();

  if (typeof(recorder) != "undefined")
  {
    if (frame <= frames)
      recorder.record(scene.renderer.GetRenderData());
    if (frame == frames-1)
      recorder.finish();
  }
  frame++;
}, 80);