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
var mode = 0;

var nBuffers = 3;
var buffers = [];
var bufLength = 2;
var tunnelTexture;
var tfrom = -1, tto = -1;

function trajectory(t)
{
  var q = t/200*Math.PI*2;
  var mul = 1.5;
  q /= mul;

  var x = Math.cos(q)*4;
  var y = Math.sin(q)*4+Math.cos(q*2)*2;
  var z = Math.cos(q*3)*5;
  var r = Math.cos(q*2)*0.2+0.5;
  return {v:$V([x*mul, y*mul, z*mul]), r:r};
}

function dvec(v) { return !v? "NULL" : (v.e(1).toFixed(2) + " " + v.e(2).toFixed(2) + " " + v.e(3).toFixed(2));}

function buildWormhole(detail, y0, y1, func)
{
  var data = [];
  if ( typeof(globCircle) == "undefined" || globCircle.length != detail )
  {
    console.log("Calculating circle");
    globCircle = new Array(detail);
    for ( var x=0; x<detail; x++)
      globCircle[x] = [Math.cos(x/detail*2*Math.PI), Math.sin(x/detail*2*Math.PI)];
  }

  var prev = func(y0);
  for (var y=y0; y<y1; y++)
  {
    var center = prev; //func(y);
    var newCenter = func(y+1);
    prev = newCenter;

    var vect = newCenter.v.subtract(center.v);

    vect1 = center.v.cross(newCenter.v).toUnitVector();
    vect2 = vect.cross(vect1).toUnitVector();

    data[y-y0] = [];
    for (var x=0; x<detail; x++)
    {
      var _cos = globCircle[x][0]*center.r;
      var _sin = globCircle[x][1]*center.r;
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
  var w = 8, h = _to - _from;

  var wormhole = buildWormhole(w, _from, _to, trajectory);

  var vertices = new Array(h*w*3);
  var colors = new Array(h*w*4);
  var indices = new Array((h-1)*w*6);
  var coords = new Array(h*w*2);

  var vertexi = 0, colori = 0, indexi = 0, coordi = 0;

  for (var y=0; y<h; y++)
    for (var x=0; x<w; x++) 
    {
      var vertex = wormhole[y][x];
      vertices[vertexi++] = vertex.e(1);
      vertices[vertexi++] = vertex.e(2);
      vertices[vertexi++] = vertex.e(3);

      var color = [0.8 + Math.random(), 0.8 + Math.random(), 0.8 + Math.random(), 1];
      if ( x == 0 ) color = [0, 1, 0, 1];
      if ( x == Math.floor(w/2) ) color = [0, 0, 1, 1];

      colors[colori++] = color[0];
      colors[colori++] = color[1];
      colors[colori++] = color[2];
      colors[colori++] = color[3];

      coords[coordi++] = x/w;
      coords[coordi++] = y/8;
    }

  for ( var y=0; y<h-1; y++)
  {
    var base0 = y*w;
    var base1 = y*w+w;
    for ( var x=0; x<w; x++)
    {
      indices[indexi++] = base0 + x;
      indices[indexi++] = base0 + (x+1)%w;
      indices[indexi++] = base1 + x;

      indices[indexi++] = base1 + x;
      indices[indexi++] = base0 + (x+1)%w;
      indices[indexi++] = base1 + (x+1)%w;
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

function buildVbo(data)
{
  var result = {};
  if ( data.vertexBuffer )
  {
    result.vertexBuffer = gl.createBuffer();
    gl.bindBuffer(gl.ARRAY_BUFFER, result.vertexBuffer);
    gl.bufferData(gl.ARRAY_BUFFER, new Float32Array(data.vertexBuffer), gl.STATIC_DRAW);
  }

  if ( data.colorBuffer )
  {
    result.colorBuffer = gl.createBuffer();
    gl.bindBuffer(gl.ARRAY_BUFFER, result.colorBuffer);
    gl.bufferData(gl.ARRAY_BUFFER, new Float32Array(data.colorBuffer), gl.STATIC_DRAW);
  }

  if ( data.indexBuffer )
  {
    result.indices = data.indexBuffer.length;
    result.indexBuffer = gl.createBuffer();
    gl.bindBuffer(gl.ELEMENT_ARRAY_BUFFER, result.indexBuffer);
    gl.bufferData(gl.ELEMENT_ARRAY_BUFFER, new Uint16Array(data.indexBuffer), gl.STATIC_DRAW);
  }

  if ( data.coordBuffer )
  {
    result.coordBuffer = gl.createBuffer();
    gl.bindBuffer(gl.ARRAY_BUFFER, result.coordBuffer);
    gl.bufferData(gl.ARRAY_BUFFER, new Float32Array(data.coordBuffer), gl.STATIC_DRAW);
  }
  return result;
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

function traceForward(base, dist)
{
  // todo: optimize!
  var len = 0, t = 0;
  var cur = trajectory(base);
  do {
    t += 0.1;
    var next = trajectory(base+t);
    var curdist = cur.v.distanceFrom(next.v);
    len += curdist;
    cur = next;
  } while (len < dist);
  return cur;
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
    tunnelTexture.image.src = "texture.jpg"; // NOTE: chrome, firefox won't load local textures!

    gl.uniform1f(shaderProgram.enableFog, 1*1.0);

    vboBall = createBall(0.05);
    vboBigBall = createBall(1);
    vboPlane = createPlane();
  }
  currentTime -= baseTime;


  gl.clear(gl.COLOR_BUFFER_BIT | gl.DEPTH_BUFFER_BIT);
  perspectiveMatrix = makePerspective(45, 960.0/540.0, 0.1, 100.0);
  loadIdentity();

//  gl.enable(gl.SCISSOR_TEST);

  // generate VBOs
  var speed = 1/250/2;
  var t = currentTime*speed;
  var len = bufLength * 8;

  while ( buffers.length < nBuffers )
  {
    var last = (buffers.length == 0) ? Math.floor(t) : buffers[buffers.length-1].range.to-1;
    buffers[buffers.length] = createBuffer(last, last+len+1);
  }

  while ( buffers.length > 0 && buffers[0].range.to < t )
    buffers.shift();


    var pt0 = trajectory(t);
    var pt1 = traceForward(t, 1);
    var pt2 = traceForward(t, 2);
    var maxup = (pt1.v.subtract(pt0.v).subtract(pt2.v.subtract(pt1.v))).toUnitVector().multiply(-1); 
    var up = pt0.v.cross(pt2.v).toUnitVector();
 
    var forw = pt1.v.subtract(pt2.v).toUnitVector();
    var stra1 = forw.cross(up).multiply(+0.05);
    var stra2 = forw.cross(up).multiply(-0.05);

    mvPushMatrix();
    multMatrix(makeLookAt(
      pt0.v.e(1), pt0.v.e(2), pt0.v.e(3), 
      pt1.v.e(1), pt1.v.e(2), pt1.v.e(3),
      up.e(1), up.e(2), up.e(3)));

  mvTranslate([stra1.e(1), stra1.e(2), stra1.e(3)]);
 

//  gl.scissor(0,0,960/2,540);
  gl.viewport(0,0,960,540/2);

  for ( buf in buffers )
    drawBuffer(buffers[buf]);

  mvTranslate([-stra1.e(1), -stra1.e(2), -stra1.e(3)]);
  mvTranslate([stra2.e(1), stra2.e(2), stra2.e(3)]);

//  gl.scissor(960/2,0,960/2,540);
  gl.viewport(0,540/2,960,540/2);

  for ( buf in buffers )
    drawBuffer(buffers[buf]);

}

document.onkeypress=function(e){
  var e=window.event || e
  if ( ++mode >= 3 ) mode = 0;
  gl.uniform1f(shaderProgram.enableFog, mode == 2 ? 0 : 1);
}