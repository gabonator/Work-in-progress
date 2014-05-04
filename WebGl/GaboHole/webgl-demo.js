var canvas;
var gl;

var mvMatrix;
var shaderProgram;
var vertexPositionAttribute;
var vertexColorAttribute;
var textureCoordAttribute;
var perspectiveMatrix;
var _totalIndices;

var baseTime = false;
var mode = false;

var bufferCurrent, bufferNext;
var tunnelTexture;
var tfrom = -1, tto = -1;

function trajectory(t)
{
  var q = t/200*Math.PI*2;

  var x = Math.cos(q)*4;
  var y = Math.sin(q)*4+Math.cos(q*2)*2;
  var z = Math.cos(q*3)*5;
  var r = Math.cos(q*2)*0.3+0.4;
  return {v:$V([x, y, z]), r:r};
}

function dvec(v) { return !v? "NULL" : (v.e(1).toFixed(2) + " " + v.e(2).toFixed(2) + " " + v.e(3).toFixed(2));}

function buildWormhole(detail, y0, y1, func)
{
  var data = [];
  for (var y=y0; y<y1; y++)
  {
    var center = func(y);
    var newCenter = func(y+1);
    var vect = newCenter.v.subtract(center.v);

    vect1 = center.v.cross(newCenter.v).toUnitVector();
    vect2 = vect.cross(vect1).toUnitVector();

    data[y-y0] = [];
    for (var x=0; x<detail; x++)
    {
      var _cos = Math.cos(x/detail*2*Math.PI)*center.r;
      var _sin = Math.sin(x/detail*2*Math.PI)*center.r;
      var pt = $V([
        vect1.e(1)*_cos + vect2.e(1)*_sin,
        vect1.e(2)*_cos + vect2.e(2)*_sin,
        vect1.e(3)*_cos + vect2.e(3)*_sin
      ]);
      data[y-y0][x] = center.v.add(pt);//{x: center.x + pt.e(1), y: center.y + pt.e(2), z: center.z + pt.e(3)};
    }
  }
  return data;
}

function createBuffer(_from, _to) 
{
  var w = 15, h = _to - _from;

  var wormhole = buildWormhole(w, _from, _to, trajectory);

  var vertices = [];
  var colors = [];
  var indices = [];
  var coords = [];

  for (var y=0; y<h; y++)
    for (var x=0; x<w; x++) 
    {
      var vertex = wormhole[y][x];
      vertices = vertices.concat( [vertex.e(1), vertex.e(2), vertex.e(3)] );
      var color = [0.8 + Math.random(), 0.8 + Math.random(), 0.8 + Math.random(), 1];
      if ( x == 0 ) color = [0, 1, 0, 1];
      if ( x == Math.floor(w/2) ) color = [0, 0, 1, 1];
      colors = colors.concat(color);
      coords = coords.concat([x/w, y/8]);
    }

  for ( var y=0; y<h-1; y++)
  {
    var base0 = y*w;
    var base1 = y*w+w;
    for ( var x=0; x<w; x++)
    {
      indices = indices.concat([base0 + x, base0 + (x+1)%w, base1 + x]);
      indices = indices.concat([base1 + x, base0 + (x+1)%w, base1 + (x+1)%w]);
    }
  }

  var cubeVerticesBuffer = gl.createBuffer();
  gl.bindBuffer(gl.ARRAY_BUFFER, cubeVerticesBuffer);
  gl.bufferData(gl.ARRAY_BUFFER, new Float32Array(vertices), gl.STATIC_DRAW);

  var cubeVerticesColorBuffer = gl.createBuffer();
  gl.bindBuffer(gl.ARRAY_BUFFER, cubeVerticesColorBuffer);
  gl.bufferData(gl.ARRAY_BUFFER, new Float32Array(colors), gl.STATIC_DRAW);

  var cubeVerticesIndexBuffer = gl.createBuffer();
  gl.bindBuffer(gl.ELEMENT_ARRAY_BUFFER, cubeVerticesIndexBuffer);
  gl.bufferData(gl.ELEMENT_ARRAY_BUFFER, new Uint16Array(indices), gl.STATIC_DRAW);

  var cubeVertexTextureCoordBuffer = gl.createBuffer();
  gl.bindBuffer(gl.ARRAY_BUFFER, cubeVertexTextureCoordBuffer);
  gl.bufferData(gl.ARRAY_BUFFER, new Float32Array(coords), gl.STATIC_DRAW);

  return {
    vertexBuffer:cubeVerticesBuffer, 
    colorBuffer:cubeVerticesColorBuffer, 
    indexBuffer:cubeVerticesIndexBuffer, 
    coordBuffer:cubeVertexTextureCoordBuffer,
    indices:indices.length,
    range:{from:_from, to:_to}
  };
}

function drawBuffer(buf)
{
  if ( !buf || !buf.vertexBuffer )
    return;

  gl.bindBuffer(gl.ARRAY_BUFFER, buf.vertexBuffer);
  gl.vertexAttribPointer(vertexPositionAttribute, 3, gl.FLOAT, false, 0, 0);

  gl.bindBuffer(gl.ARRAY_BUFFER, buf.colorBuffer);
  gl.vertexAttribPointer(vertexColorAttribute, 4, gl.FLOAT, false, 0, 0);

  gl.bindBuffer(gl.ARRAY_BUFFER, buf.coordBuffer);
  gl.vertexAttribPointer(textureCoordAttribute, 2, gl.FLOAT, false, 0, 0);
    
  gl.activeTexture(gl.TEXTURE0);
  gl.bindTexture(gl.TEXTURE_2D, tunnelTexture);
  gl.uniform1i(shaderProgram.samplerUniform, 0);

  gl.bindBuffer(gl.ELEMENT_ARRAY_BUFFER, buf.indexBuffer);
  setMatrixUniforms();

  gl.drawElements(gl.TRIANGLES, buf.indices, gl.UNSIGNED_SHORT, 0);
}

function handleTextureLoad(image, texture)
{
  gl.bindTexture(gl.TEXTURE_2D, texture);
  gl.texImage2D(gl.TEXTURE_2D, 0, gl.RGBA, gl.RGBA, gl.UNSIGNED_BYTE, image);
  gl.texParameteri(gl.TEXTURE_2D, gl.TEXTURE_MAG_FILTER, gl.LINEAR);
  gl.texParameteri(gl.TEXTURE_2D, gl.TEXTURE_MIN_FILTER, gl.LINEAR_MIPMAP_NEAREST);
  gl.generateMipmap(gl.TEXTURE_2D);
  gl.bindTexture(gl.TEXTURE_2D, null);
}

function isInRange(buf, t)
{
  if ( !buf || !buf.range )
    return false;
  return ( t <= buf.range.to );
}

function drawScene() 
{         
  var currentTime = (new Date).getTime();
  if ( !baseTime )
  {
    baseTime = currentTime;

    tunnelTexture = gl.createTexture();
    tunnelTexture.image = new Image();
    tunnelTexture.image.onload = function() { handleTextureLoad(tunnelTexture.image, tunnelTexture); }
    tunnelTexture.image.src = textureUrl; //"texture.jpg"; shitty firefox disallows using textures from rawgit

    gl.uniform1f(shaderProgram.enableFog, 1.0);
  }
  currentTime -= baseTime;

  gl.clear(gl.COLOR_BUFFER_BIT | gl.DEPTH_BUFFER_BIT);
  perspectiveMatrix = makePerspective(45, 640.0/480.0, 0.1, 100.0);
  loadIdentity();

  // generate VBOs
  var speed = 1/150;
  var t = currentTime*speed;
  if ( !isInRange(bufferNext, t+30) )
  {
    console.log("Updating buffer, was " +(bufferNext ?bufferNext.range.to : 0) + " need "+(t+30).toFixed(1));
    bufferCurrent = bufferNext;

    tfrom = bufferCurrent ? bufferCurrent.range.to-1 : 0;
    tto = tfrom + 8*5;

    bufferNext = createBuffer(tfrom, tto+1);
  }

  mvPushMatrix();
  if ( mode )
  {
    mvTranslate([0.0, 0.0, -20.0]);
    mvRotate(currentTime/10, [1, 0, 0]);
    mvRotate(currentTime/30, [0, 1, 0]);
    mvRotate(currentTime/70, [0, 0, 1]);
  } else
  {

    var pt0 = trajectory(t);
    var pt1 = trajectory(t+4);
    var pt2 = trajectory(t+20);
    var up = pt0.v.cross(pt2.v);
    multMatrix(makeLookAt(
      pt0.v.e(1), pt0.v.e(2), pt0.v.e(3), 
      pt1.v.e(1), pt1.v.e(2), pt1.v.e(3),
      up.e(1), up.e(2), up.e(3)));
  }

  drawBuffer(bufferCurrent);
  drawBuffer(bufferNext);
  mvPopMatrix();
}

document.onkeypress=function(e){
  var e=window.event || e
  mode = !mode;
  gl.uniform1f(shaderProgram.enableFog, mode ? 0 : 1);
}