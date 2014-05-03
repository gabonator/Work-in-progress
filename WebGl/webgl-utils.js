function start() {
  canvas = document.getElementById("glcanvas");

  gl = null;
  
  try {
    gl = canvas.getContext("experimental-webgl");
  }
  catch(e) {
  }
  if (!gl)
  {
    alert("Unable to initialize WebGL. Your browser may not support it.");
    return;
  }
  
  gl.clearColor(0.0, 0.0, 0.0, 1.0);  // Clear to black, fully opaque
  gl.clearDepth(1.0);                 // Clear everything
  gl.enable(gl.DEPTH_TEST);           // Enable depth testing
  gl.depthFunc(gl.LEQUAL);            // Near things obscure far things
  
  initShaders();
  initBuffers();

  setInterval(drawScene, 20);
}

function initShaders() 
{
  var fragmentShader = getShader(gl, "fragment");
  var vertexShader = getShader(gl, "vertex");
  
  shaderProgram = gl.createProgram();
  gl.attachShader(shaderProgram, vertexShader);
  gl.attachShader(shaderProgram, fragmentShader);
  gl.linkProgram(shaderProgram);
  
  if (!gl.getProgramParameter(shaderProgram, gl.LINK_STATUS))
    alert("Unable to initialize the shader program.");
  
  gl.useProgram(shaderProgram);
  vertexPositionAttribute = gl.getAttribLocation(shaderProgram, "aVertexPosition");
  gl.enableVertexAttribArray(vertexPositionAttribute);
  
  vertexColorAttribute = gl.getAttribLocation(shaderProgram, "aVertexColor");
  gl.enableVertexAttribArray(vertexColorAttribute);
}

function getShader(gl, id) 
{
  var shader;
  if (id=="fragment")
  {
    shaderScript = {type:"x-shader/x-fragment"};
    theSource = "varying lowp vec4 vColor;\n"
    theSource+= "void main(void) {\n";
		theSource+= "gl_FragColor = vColor;\n";
		theSource+= "}";
    shader = gl.createShader(gl.FRAGMENT_SHADER);
  }
  if (id=="vertex")
  {
    shaderScript = {type:"x-shader/x-vertex"};
    theSource = "attribute vec3 aVertexPosition;\n";
    theSource+= "attribute vec4 aVertexColor;\n";
    theSource+= "uniform mat4 uMVMatrix;\n";
    theSource+= "uniform mat4 uPMatrix;\n";
		theSource+= "varying lowp vec4 vColor;\n";
    theSource+= "void main(void) {\n";
    theSource+= "  gl_Position = uPMatrix * uMVMatrix * vec4(aVertexPosition, 1.0);\n";
    theSource+= "  vColor = aVertexColor;\n";
    theSource+= "}\n";
    shader = gl.createShader(gl.VERTEX_SHADER);
  }  
  gl.shaderSource(shader, theSource);
  gl.compileShader(shader);
  if (!gl.getShaderParameter(shader, gl.COMPILE_STATUS)) 
  {
    alert("An error occurred compiling the shaders: " + gl.getShaderInfoLog(shader));
    return null;
  }
  return shader;
}

function loadIdentity() {
  mvMatrix = Matrix.I(4);
}

function multMatrix(m) {
  mvMatrix = mvMatrix.x(m);
}

function mvTranslate(v) {
  multMatrix(Matrix.Translation($V([v[0], v[1], v[2]])).ensure4x4());
}

function setMatrixUniforms() {
  var pUniform = gl.getUniformLocation(shaderProgram, "uPMatrix");
  gl.uniformMatrix4fv(pUniform, false, new Float32Array(perspectiveMatrix.flatten()));

  var mvUniform = gl.getUniformLocation(shaderProgram, "uMVMatrix");
  gl.uniformMatrix4fv(mvUniform, false, new Float32Array(mvMatrix.flatten()));
}

var mvMatrixStack = [];

function mvPushMatrix(m) {
  if (m) {
    mvMatrixStack.push(m.dup());
    mvMatrix = m.dup();
  } else {
    mvMatrixStack.push(mvMatrix.dup());
  }
}

function mvPopMatrix() {
  if (!mvMatrixStack.length) {
    throw("Can't pop from an empty matrix stack.");
  }
  
  mvMatrix = mvMatrixStack.pop();
  return mvMatrix;
}

function mvRotate(angle, v) {
  var inRadians = angle * Math.PI / 180.0;
  
  var m = Matrix.Rotation(inRadians, $V([v[0], v[1], v[2]])).ensure4x4();
  multMatrix(m);
}