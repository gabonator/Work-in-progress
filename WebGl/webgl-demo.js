var canvas;
var gl;

var mvMatrix;
var shaderProgram;
var vertexPositionAttribute;
var vertexColorAttribute;
var perspectiveMatrix;
var _totalIndices;

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

function buildWormhole(detail, depth, func)
{
  var data = [];
  for (var y=0; y<depth; y++)
  {
    var center = func(y);
    var newCenter = func(y+1);
//    var vx = newCenter.x - center.x;
//    var vy = newCenter.y - center.y;
//    var vz = newCenter.z - center.z;
    var vect = newCenter.v.subtract(center.v);// $V([vx, vy, vz]);
/*
    var arr =  [[vz,vz,-vx-vy], [-vx-vz, vx,vx]];
		var i = ((vz != 0) && (-vx != vx));
    var vect1 = $V(arr[i ? 1 : 0]).toUnitVector();
    var vect2 = vect.cross(vect1).toUnitVector();
*/
    vect1 = center.v.cross(newCenter.v).toUnitVector();
    vect2 = vect.cross(vect1).toUnitVector();

    data[y] = [];
    for (var x=0; x<detail; x++)
    {
      var _cos = Math.cos(x/detail*2*Math.PI)*center.r;
      var _sin = Math.sin(x/detail*2*Math.PI)*center.r;
      var pt = $V([
        vect1.e(1)*_cos + vect2.e(1)*_sin,
        vect1.e(2)*_cos + vect2.e(2)*_sin,
        vect1.e(3)*_cos + vect2.e(3)*_sin
      ]);
      data[y][x] = center.v.add(pt);//{x: center.x + pt.e(1), y: center.y + pt.e(2), z: center.z + pt.e(3)};
    }
  }
  return data;
}


function initBuffers() 
{
  var w = 15, h = 201;

  var wormhole = buildWormhole(w, h, trajectory);

  var vertices = [];
  var colors = [];
  var indices = [];

  for (var y=0; y<h; y++)
    for (var x=0; x<w; x++) 
    {
      var vertex = wormhole[y][x];
      vertices = vertices.concat( [vertex.e(1), vertex.e(2), vertex.e(3)] );
      var color = [Math.random(), Math.random(), Math.random(), 1];
      if ( x == 0 ) color = [1, 1, 1, 1];
      if ( x == Math.floor(w/2) ) color = [0, 0, 1, 1];
      colors = colors.concat(color);
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

  _totalIndices = indices.length;
  
  cubeVerticesBuffer = gl.createBuffer();
  gl.bindBuffer(gl.ARRAY_BUFFER, cubeVerticesBuffer);
  gl.bufferData(gl.ARRAY_BUFFER, new Float32Array(vertices), gl.STATIC_DRAW);

  cubeVerticesColorBuffer = gl.createBuffer();
  gl.bindBuffer(gl.ARRAY_BUFFER, cubeVerticesColorBuffer);
  gl.bufferData(gl.ARRAY_BUFFER, new Float32Array(colors), gl.STATIC_DRAW);

  cubeVerticesIndexBuffer = gl.createBuffer();
  gl.bindBuffer(gl.ELEMENT_ARRAY_BUFFER, cubeVerticesIndexBuffer);
  gl.bufferData(gl.ELEMENT_ARRAY_BUFFER, new Uint16Array(indices), gl.STATIC_DRAW);
}

var baseTime = false;
var mode = false;
function drawScene() 
{         
  var currentTime = (new Date).getTime();
  if ( !baseTime )
    baseTime = currentTime;
  currentTime -= baseTime;

  gl.clear(gl.COLOR_BUFFER_BIT | gl.DEPTH_BUFFER_BIT);
  perspectiveMatrix = makePerspective(45, 640.0/480.0, 0.1, 100.0);
  loadIdentity();

  mvPushMatrix();
  if ( mode )
  {
    mvTranslate([0.0, 0.0, -20.0]);
    mvRotate(currentTime/10, [1, 0, 0]);
    mvRotate(currentTime/30, [0, 1, 0]);
    mvRotate(currentTime/70, [0, 0, 1]);
  } else
  {
    var speed = 1/150;
    var pt0 = trajectory(currentTime*speed);
    var pt1 = trajectory(currentTime*speed+4);
    var pt2 = trajectory(currentTime*speed+20);
    var up = pt0.v.cross(pt2.v);
    multMatrix(makeLookAt(
      pt0.v.e(1), pt0.v.e(2), pt0.v.e(3), 
      pt1.v.e(1), pt1.v.e(2), pt1.v.e(3),
      up.e(1), up.e(2), up.e(3)));
  }

//  mvRotate(cubeRotation, [1, 0, 1]);
//  mvTranslate([cubeXOffset, cubeYOffset, cubeZOffset]);
  
  gl.bindBuffer(gl.ARRAY_BUFFER, cubeVerticesBuffer);
  gl.vertexAttribPointer(vertexPositionAttribute, 3, gl.FLOAT, false, 0, 0);

  gl.bindBuffer(gl.ARRAY_BUFFER, cubeVerticesColorBuffer);
  gl.vertexAttribPointer(vertexColorAttribute, 4, gl.FLOAT, false, 0, 0);

  gl.bindBuffer(gl.ELEMENT_ARRAY_BUFFER, cubeVerticesIndexBuffer);
  setMatrixUniforms();
  gl.drawElements(gl.TRIANGLES, _totalIndices, gl.UNSIGNED_SHORT, 0);
  mvPopMatrix();
}

document.onkeypress=function(e){
 var e=window.event || e
// if (e.charCode == " ")
   mode = !mode;
}