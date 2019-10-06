var scene = new Scene();
var frame = 0;
var frames = 140;
setInterval( ()=>
{
  frame++;
  scene.pax = 360*2*(frame%frames)/frames; //(new Date()).getTime()/20;
  scene.pay = 360*1*(frame%frames)/frames; //(new Date()).getTime()/50;
  scene.Begin();


  scene.Draw([{x:-1, y:-1, z:-1, c:0}, {x:+1, y:-1, z:-1, c:1}]);
  scene.Draw([{x:+1, y:-1, z:-1, c:0}, {x:+1, y:+1, z:-1, c:1}]);
  scene.Draw([{x:+1, y:+1, z:-1, c:0}, {x:-1, y:+1, z:-1, c:1}]);
  scene.Draw([{x:-1, y:+1, z:-1, c:0}, {x:-1, y:-1, z:-1, c:1}]);

  scene.Draw([{x:-1, y:-1, z:+1, c:0}, {x:+1, y:-1, z:+1, c:1}]);
  scene.Draw([{x:+1, y:-1, z:+1, c:0}, {x:+1, y:+1, z:+1, c:1}]);
  scene.Draw([{x:+1, y:+1, z:+1, c:0}, {x:-1, y:+1, z:+1, c:1}]);
  scene.Draw([{x:-1, y:+1, z:+1, c:0}, {x:-1, y:-1, z:+1, c:1}]);

  scene.Draw([{x:-1, y:-1, z:-1, c:0}, {x:-1, y:-1, z:+1, c:1}]);
  scene.Draw([{x:+1, y:-1, z:-1, c:0}, {x:+1, y:-1, z:+1, c:1}]);
  scene.Draw([{x:+1, y:+1, z:-1, c:0}, {x:+1, y:+1, z:+1, c:1}]);
  scene.Draw([{x:-1, y:+1, z:-1, c:0}, {x:-1, y:+1, z:+1, c:1}]);


  scene.Draw([{x:-1/2, z:-1/2, y:-1, c:0}, {x:+1/2, z:-1/2, y:-1, c:2}]);
  scene.Draw([{x:+1/2, z:-1/2, y:-1, c:0}, {x:+1/2, z:+1/2, y:-1, c:2}]);
  scene.Draw([{x:+1/2, z:+1/2, y:-1, c:0}, {x:-1/2, z:+1/2, y:-1, c:2}]);
  scene.Draw([{x:-1/2, z:+1/2, y:-1, c:0}, {x:-1/2, z:-1/2, y:-1, c:2}]);


  scene.Draw([{x:-1/2, z:-1/2, y:+1, c:0}, {x:+1/2, z:-1/2, y:+1, c:2}]);
  scene.Draw([{x:+1/2, z:-1/2, y:+1, c:0}, {x:+1/2, z:+1/2, y:+1, c:2}]);
  scene.Draw([{x:+1/2, z:+1/2, y:+1, c:0}, {x:-1/2, z:+1/2, y:+1, c:2}]);
  scene.Draw([{x:-1/2, z:+1/2, y:+1, c:0}, {x:-1/2, z:-1/2, y:+1, c:2}]);
/*
  scene.Draw([{x:-1/2, y:-1/2, z:+1, c:0}, {x:+1/2, y:-1/2, z:+1, c:2}]);
  scene.Draw([{x:+1/2, y:-1/2, z:+1, c:0}, {x:+1/2, y:+1/2, z:+1, c:2}]);
  scene.Draw([{x:+1/2, y:+1/2, z:+1, c:0}, {x:-1/2, y:+1/2, z:+1, c:2}]);
  scene.Draw([{x:-1/2, y:+1/2, z:+1, c:0}, {x:-1/2, y:-1/2, z:+1, c:2}]);
 */
  scene.Finish();


  if (typeof(recorder) != "undefined")
  {
    if (frame <= frames)
      recorder.record(scene.renderer.GetRenderData());
    if (frame == frames-1)
      recorder.finish();
  }
}, 50);