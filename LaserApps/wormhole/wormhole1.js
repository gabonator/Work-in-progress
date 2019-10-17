function vector(z)
{
  return {x:0, y:0, z:1};
}
function cylinder(i, z, c)
{
  var r=4;
  return {x:Math.cos(i*2*Math.PI/8)*r, y:Math.sin(i*2*Math.PI/8)*r, z:z*4, c:c};
}



var scene = new Scene();
var frame = 0;
var frames = 140;
setInterval( ()=>
{
  frame++;
  scene.pax = 360*1*(frame%frames)/frames; //(new Date()).getTime()/20;
  scene.pz = (((new Date()).getTime()*2)%1000)/1000*4;
  scene.Begin();

  var n = 60;
  var line = [];
  var first = Math.max(0, ((frame%frames)-frames)*2+n);
  var last = Math.min(frame*2, n);
  for (var y=0; y<12; y++)
  {
    for (var x=0; x<8; x++)
    {
      line.push(cylinder(x, y, 0));
      line.push(cylinder(x+1, y, 1));
    }
  }
  for (var x=0; x<8; x++)
  {
    for (var y=0; y<12-1; y++)
    {
      line.push(cylinder(x, y, 0));
      line.push(cylinder(x, y+1, 1));
    }
  }

  scene.Draw(line);
  scene.Finish();


  if (typeof(recorder) != "undefined")
  {
    if (frame <= frames)
      recorder.record(scene.renderer.GetRenderData());
    if (frame == frames-1)
      recorder.finish();
  }
}, 50);