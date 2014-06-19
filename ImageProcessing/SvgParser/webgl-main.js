function createModel(inpath, top, bottom)
{
  paths = expandPath([inpath]);

  var vertices = [], indices = [], normals = [];

  // walls
  //var top = 0.0, bottom = -50.0;
  var base = 0;
  for ( var j=0; j<paths.length; j++ )
  { 
    var path = paths[j];
    for ( var i=0; i<path.length; i++, base+=4)
    {
      var i0 = i;
      var i1 = (i+1)%path.length;

      vertices = vertices.concat([path[i0].X, path[i0].Y, top]);
      vertices = vertices.concat([path[i0].X, path[i0].Y, bottom]);
      vertices = vertices.concat([path[i1].X, path[i1].Y, top]);
      vertices = vertices.concat([path[i1].X, path[i1].Y, bottom]);

      var vx = path[i1].X - path[i0].X;
      var vy = path[i1].Y - path[i0].Y;
      var normal = normalize(vy, -vx, 0);
      normals = normals.concat(normal);
      normals = normals.concat(normal);
      normals = normals.concat(normal);
      normals = normals.concat(normal);

      indices = indices.concat([base+0, base+2, base+1]);
      indices = indices.concat([base+1, base+2, base+3]);
    }
  }

	var paths = triangulate(paths);

  // top
  for ( var i=0; i<paths.length; i++, base+=3)
  {
    var p = paths[i];
    vertices = vertices.concat([p[0].X, p[0].Y, top]);
    vertices = vertices.concat([p[1].X, p[1].Y, top]);
    vertices = vertices.concat([p[2].X, p[2].Y, top]);

    normals = normals.concat([0, 0, -1]);
    normals = normals.concat([0, 0, -1]);
    normals = normals.concat([0, 0, -1]);

    indices = indices.concat([base+0, base+2, base+1]);
  }

  // bottom
  for ( var i=0; i<paths.length; i++, base+=3)
  {
    var p = paths[i];
    vertices = vertices.concat([p[0].X, p[0].Y, bottom]);
    vertices = vertices.concat([p[1].X, p[1].Y, bottom]);
    vertices = vertices.concat([p[2].X, p[2].Y, bottom]);

    normals = normals.concat([0, 0, 1]);
    normals = normals.concat([0, 0, 1]);
    normals = normals.concat([0, 0, 1]);

    indices = indices.concat([base+0, base+2, base+1]);
  }

  return vboBuild({
    vertexBuffer:vertices, 
    normalBuffer:normals,
    indexBuffer:indices
  });
}

function normalize(x, y, z)
{
  var f = 1/Math.sqrt(x*x+y*y+z*z);
  return [x*f, y*f, z*f];
}

function initScene()
{
  gl.clearColor(0.0, 0.0, 0.0, 1.0);  // Clear to black, fully opaque
  gl.clearDepth(1.0);                 // Clear everything
//  gl.enable(gl.DEPTH_TEST);           // Enable depth testing
  gl.depthFunc(gl.LEQUAL);            // Near things obscure far things
  gl.enable(gl.BLEND);
  gl.blendFunc(gl.SRC_ALPHA, gl.ONE);
}
function degToRad(degrees) 
{
  return degrees * Math.PI / 180;
}
function drawScene() 
{         

  gl.clear(gl.COLOR_BUFFER_BIT | gl.DEPTH_BUFFER_BIT);

//  mat4.perspective(45, gl.viewportWidth / gl.viewportHeight, 100, 1000.0, pMatrix);
  mat4.perspective(45, 640/480, 100, 1000.0, pMatrix);

  gl.blendFunc(gl.SRC_ALPHA, gl.ONE);
  gl.enable(gl.BLEND);
  gl.disable(gl.DEPTH_TEST);
  gl.uniform1f(shaderProgram.alphaUniform, 0.7);
	gl.uniform1i(shaderProgram.useLightingUniform, 1);
  // {{{
  gl.uniform3f( shaderProgram.ambientColorUniform, 0.2, 0.2, 0.2 );
  var lightingDirection = normalize(0.1, -0.7, -0.25);
  gl.uniform3fv(shaderProgram.lightingDirectionUniform, lightingDirection);
  gl.uniform3fv(shaderProgram.directionalColorUniform, [0.8, 0.8, 0.8]);
  // }}}

  mat4.identity(mvMatrix);
  mat4.translate(mvMatrix, [-140, -80, -400]);
  mat4.rotate(mvMatrix, degToRad(-70), [1, 0, 0]);

  for (var i in paths)
  {
    var color = colors[i];
    color = [color[0]/255, color[1]/255, color[2]/255, 1.0];
    gl.uniform4fv(shaderProgram.materialColorUniform, color);
    vboDraw(createModel(toXYPath(parsePath(paths[i])), i*20, -20));
  }
}
