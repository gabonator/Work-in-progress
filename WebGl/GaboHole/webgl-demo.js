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

var nBuffers = 4;
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
  var r = Math.cos(q*2)*0.3+0.4;
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
  var w = 40, h = _to - _from;

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

function createBall(radius) 
{
  var vertices = [];
  var colors = [];
  var indices = [];
  var coords = [];
  var normals = [];
  
  var latitudeBands = 30;
  var longitudeBands = 30;

  for (var latNumber = 0; latNumber <= latitudeBands; latNumber++) 
  {
    var theta = latNumber * Math.PI / latitudeBands;
    var sinTheta = Math.sin(theta);
    var cosTheta = Math.cos(theta);

    for (var longNumber = 0; longNumber <= longitudeBands; longNumber++) 
    {
      var phi = longNumber * 2 * Math.PI / longitudeBands;
      var sinPhi = Math.sin(phi);
      var cosPhi = Math.cos(phi);

      var x = cosPhi * sinTheta;
      var y = cosTheta;
      var z = sinPhi * sinTheta;
      var u = 1- (longNumber / longitudeBands);
      var v = latNumber / latitudeBands;

      normals = normals.concat([x, y, z]); 
      coords = coords.concat([u, v]);
      vertices = vertices.concat([radius * x, radius * y, radius * z]);
      colors = colors.concat([3, 1, 1, 1]);
    }
  }

  for (var latNumber = 0; latNumber < latitudeBands; latNumber++) 
  {
    for (var longNumber = 0; longNumber < longitudeBands; longNumber++) 
    {
      var first = (latNumber * (longitudeBands + 1)) + longNumber;
      var second = first + longitudeBands + 1;
      indices = indices.concat([first, second, first+1]);
      indices = indices.concat([second, second+1, first+1]);
    }
  }

  return buildVbo({
    vertexBuffer:vertices, 
    colorBuffer:colors, 
    indexBuffer:indices, 
    coordBuffer:coords,
  });
}

function createPlane(radius) 
{
  var vertices = [
    -5, -5, 0,
    -5, 5, 0,
    5, 5, 0,
    5, -5, 0];
  var colors = [
    5, 5, 5, 0.1,
    5, 5, 5, 0.1,
    5, 5, 5, 0.1,
    5, 5, 5, 0.1 ];
  var indices = [0, 1, 2, 0, 2, 3];
  var coords = [0, 0, 0, 0, 0, 0, 0, 0];
  
  return buildVbo({
    vertexBuffer:vertices, 
    colorBuffer:colors, 
    indexBuffer:indices, 
    coordBuffer:coords,
  });
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
    t += 0.01;
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
    tunnelTexture.image.src = textureUrl; //"texture.jpg"; shitty firefox disallows using textures from rawgit

    gl.uniform1f(shaderProgram.enableFog, 0*1.0);

    vboBall = createBall(0.05);
    vboBigBall = createBall(1);
    vboPlane = createPlane();
  }
  currentTime -= baseTime;

  gl.clear(gl.COLOR_BUFFER_BIT | gl.DEPTH_BUFFER_BIT);
  perspectiveMatrix = makePerspective(45, 640.0/480.0, 0.1, 100.0);
  loadIdentity();

  // generate VBOs
  var speed = 1/150;
  var t = currentTime*speed;
  var len = bufLength * 8;

  while ( buffers.length < nBuffers )
  {
    var last = (buffers.length == 0) ? Math.floor(t) : buffers[buffers.length-1].range.to-1;
    buffers[buffers.length] = createBuffer(last, last+len+1);
  }

  while ( buffers.length > 0 && buffers[0].range.to < t )
    buffers.shift();

  if ( mode == 2 )
  {
    mvPushMatrix();
    mvTranslate([0.0, 0.0, -30.0]);
    mvRotate(currentTime/70, [1, 0, 0]);
    mvRotate(currentTime/90, [0, 1, 0]);
    mvRotate(currentTime/130, [0, 0, 1]);
		for ( buf in buffers )
	    drawBuffer(buffers[buf]);

    var pt1 = trajectory(t);

    mvTranslate([pt1.v.e(1), pt1.v.e(2), pt1.v.e(3)]);
    drawBuffer(vboBigBall);

    mvPopMatrix();
  } else
  {

    var pt0 = trajectory(t);
    var pt1 = traceForward(t, 1);
    var pt2 = traceForward(t, 2);
    var maxup = (pt1.v.subtract(pt0.v).subtract(pt2.v.subtract(pt1.v))).toUnitVector().multiply(-1); 
    var up = pt0.v.cross(pt2.v).toUnitVector();
 

    mvPushMatrix();
    multMatrix(makeLookAt(
      pt0.v.e(1), pt0.v.e(2), pt0.v.e(3), 
      pt1.v.e(1), pt1.v.e(2), pt1.v.e(3),
      up.e(1), up.e(2), up.e(3)));

		for ( buf in buffers )
	    drawBuffer(buffers[buf]);

    if ( mode == 1 )
    {
      var direction = pt1.v.subtract(pt0.v);
      var xaxis = maxup.cross(direction).toUnitVector();
      var yaxis = direction.cross(xaxis).toUnitVector();
      var m = $M([
        [xaxis.e(1), yaxis.e(1), direction.e(1), 0],
        [xaxis.e(2), yaxis.e(2), direction.e(2), 0],
        [xaxis.e(3), yaxis.e(3), direction.e(3), 0],
        [0, 0, 0, 1]]);// Matrix.Rotation(inRadians, $V([v[0], v[1], v[2]])).ensure4x4();


      pt1.v = pt1.v.add(yaxis.multiply(-pt1.r+0.05)); //(maxup.multiply(-pt1.r*(1.05)));
      mvTranslate([pt1.v.e(1), pt1.v.e(2), pt1.v.e(3)]);

      drawBuffer(vboBall);

      multMatrix(m);
      drawBuffer(vboPlane);
      mvPopMatrix();
    }
  }

}

document.onkeypress=function(e){
  var e=window.event || e
  if ( ++mode >= 3 ) mode = 0;
  gl.uniform1f(shaderProgram.enableFog, mode == 2 ? 0 : 1);
}