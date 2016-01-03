function start() 
{
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
  gl.enable(gl.BLEND);
  gl.blendFunc(gl.SRC_ALPHA, gl.ONE);
  
  initShaders();

  setInterval(drawScene, 50);
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

  textureCoordAttribute = gl.getAttribLocation(shaderProgram, "aTextureCoord");
  gl.enableVertexAttribArray(textureCoordAttribute);

  shaderProgram.enableFog = gl.getUniformLocation(shaderProgram, "uEnableFog");
}

function getShader(gl, id) 
{
  var shader;
  if (id=="fragment")
  {
    shaderScript = {type:"x-shader/x-fragment"};
/*
    theSource = "varying lowp vec4 vColor;\n"
    theSource+= "void main(void) {\n";
		theSource+= "gl_FragColor = vColor;\n";
		theSource+= "}";
*/
    theSource = 
      "#ifdef GL_ES\n"+
      "precision highp float;\n"+
      "#endif\n"+

      "uniform sampler2D uSampler;\n"+
//      "varying lowp vec4 vColor;\n" +
     	"varying vec2 vTextureCoord;\n"+
      "void main(void) {\n" +
//      "  mediump vec4 texelColor = texture2D(uSampler, vec2(vTextureCoord.s, vTextureCoord.t));\n" +
//  	  "  gl_FragColor = texelColor.rgb * vColor;\n" +
//      " gl_FragColor = texture2D(uSampler, vec2(vTextureCoord.s, vTextureCoord.t)) * vColor;\n" +
      " gl_FragColor = texture2D(uSampler, vec2(vTextureCoord.s, vTextureCoord.t));\n" +
		  "}";
/*

    theSource = 
  	"#ifdef GL_ES\n"+
  	"precision highp float;\n"+
    "#endif\n"+

  	"uniform sampler2D uSampler;\n"+

  	"varying vec4 vColor;\n"+
  	"varying vec2 vTextureCoord;\n"+
    "varying vec3 vLighting;\n"+
    "varying float vEnableFog;\n"+

    "float uAlpha;\n"+
    "float density = 0.25;\n"+

  	"void main(void) {\n"+
    "  uAlpha = 1.0;\n"+
    "  float z = gl_FragCoord.z / gl_FragCoord.w;\n"+
    "  float fogFactor = exp2( -density * density * z * z * 1.442695);\n"+
    "  fogFactor += 1.0 - vEnableFog;\n"+
    "  fogFactor = clamp(fogFactor, 0.0, 1.0);\n"+

    "  mediump vec4 texelColor = texture2D(uSampler, vec2(vTextureCoord.s, vTextureCoord.t));\n"+
  	"  gl_FragColor = vec4(texelColor.rgb * vLighting * fogFactor, texelColor.a * fogFactor) * vColor;\n"+
  	"}\n";
*/
    shader = gl.createShader(gl.FRAGMENT_SHADER);
  }
  if (id=="vertex")
  {
    shaderScript = {type:"x-shader/x-vertex"};
    theSource = "attribute vec3 aVertexPosition;\n";
    theSource+= "attribute vec4 aVertexColor;\n";
    theSource+= "attribute vec2 aTextureCoord;\n";
    theSource+= "uniform float uEnableFog;\n";

    theSource+= "uniform mat4 uMVMatrix;\n";
    theSource+= "uniform mat4 uPMatrix;\n";
		theSource+= "varying lowp vec4 vColor;\n";
		theSource+= "varying vec2 vTextureCoord;\n";
    theSource+= "varying vec3 vLighting;\n";
    theSource+= "varying float vEnableFog;\n";

    theSource+= "void main(void) {\n";
    theSource+= "  gl_Position = uPMatrix * uMVMatrix * vec4(aVertexPosition, 1.0);\n";
    theSource+= "  vColor = aVertexColor;\n";
    theSource+="   vTextureCoord = aTextureCoord;\n";
    theSource+="   vLighting = vec3(0.5, 0.5, 0.5);\n";
    theSource+="   vEnableFog = uEnableFog;\n";
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