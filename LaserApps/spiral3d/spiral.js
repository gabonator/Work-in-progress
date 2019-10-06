var scene = new Scene();
var frame = 0;
var frames = 140;
setInterval( ()=>
{
  frame++;
  scene.pax = 360*1*(frame%frames)/frames; //(new Date()).getTime()/20;
  scene.pay = 360*1*(frame%frames)/frames; //(new Date()).getTime()/50;
  scene.Begin();

  var n = 60;
  var line = [];
  var first = Math.max(0, ((frame%frames)-frames)*2+n);
  var last = Math.min(frame*2, n);
  for (var i=first; i<=last; i++)
  {
/*
    var x = Math.cos(i/n*Math.PI*2*1 + Math.PI/3) + Math.cos(i/n*Math.PI*2*8)*0.3;
    var y = Math.cos(i/n*Math.PI*2*3 + Math.PI*0.7) + Math.sin(i/n*Math.PI*2*8)*0.3;
    var z = Math.cos(i/n*Math.PI*2*3);
*/
/*
    var x = Math.cos(i/n*Math.PI*2*1) - Math.cos(i/n*Math.PI*2*8)*0.5;
    var y = Math.sin(i/n*Math.PI*2*1);
    var z = Math.cos(i/n*Math.PI*2*1 + Math.PI*0.777) + Math.sin(i/n*Math.PI*2*8)*0.5;
*/
    var x = Math.cos(i/n*Math.PI*2*1);
    var y = Math.sin(i/n*Math.PI*2*4 + Math.PI*0.7);
    var z = Math.cos(i/n*Math.PI*2*3 + Math.PI*0.777);
    line.push({x:x, y:y, z:z, c:((i==0) ? 0 : 1)});
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