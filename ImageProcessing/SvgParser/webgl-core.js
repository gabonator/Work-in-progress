window.onload = start;

var mvMatrix = mat4.create();
var pMatrix = mat4.create();

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
  initScene();
  initShaders();
  drawScene();
//  setInterval(drawScene, 1000);
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
  
  shaderProgram.vertexPositionAttribute = gl.getAttribLocation(shaderProgram, "aVertexPosition");
  gl.enableVertexAttribArray(shaderProgram.vertexPositionAttribute);

  shaderProgram.vertexNormalAttribute = gl.getAttribLocation(shaderProgram, "aVertexNormal");
  gl.enableVertexAttribArray(shaderProgram.vertexNormalAttribute);

  shaderProgram.pMatrixUniform = gl.getUniformLocation(shaderProgram, "uPMatrix");
  shaderProgram.mvMatrixUniform = gl.getUniformLocation(shaderProgram, "uMVMatrix");
  shaderProgram.nMatrixUniform = gl.getUniformLocation(shaderProgram, "uNMatrix");
  shaderProgram.samplerUniform = gl.getUniformLocation(shaderProgram, "uSampler");
  shaderProgram.useLightingUniform = gl.getUniformLocation(shaderProgram, "uUseLighting");
  shaderProgram.ambientColorUniform = gl.getUniformLocation(shaderProgram, "uAmbientColor");
  shaderProgram.lightingDirectionUniform = gl.getUniformLocation(shaderProgram, "uLightingDirection");
  shaderProgram.directionalColorUniform = gl.getUniformLocation(shaderProgram, "uDirectionalColor");
  shaderProgram.alphaUniform = gl.getUniformLocation(shaderProgram, "uAlpha");

  shaderProgram.materialColorUniform = gl.getUniformLocation(shaderProgram, "uMaterialColor");
  
//  vertexColorAttribute = gl.getAttribLocation(shaderProgram, "aVertexColor");
//  gl.enableVertexAttribArray(vertexColorAttribute);

//  textureCoordAttribute = gl.getAttribLocation(shaderProgram, "aTextureCoord");
//  gl.enableVertexAttribArray(textureCoordAttribute);
}

function getShader(gl, id) 
{
  var shader;
  if (id=="fragment")
  {
    shaderScript = {type:"x-shader/x-fragment"};
    theSource = 
  		"precision mediump float;\n"+

      "varying vec2 vTextureCoord;\n"+
      "varying vec3 vLightWeighting;\n"+
      "varying vec4 vMaterialColor;\n"+

      "uniform float uAlpha;\n"+

      "uniform sampler2D uSampler;\n"+

      "void main(void) {\n"+
      "    vec4 textureColor = vMaterialColor;\n"+ //texture2D(uSampler, vec2(vTextureCoord.s, vTextureCoord.t));\n"+
      "    gl_FragColor = vec4(textureColor.rgb * vLightWeighting, textureColor.a * uAlpha);\n"+
      "}\n";

    shader = gl.createShader(gl.FRAGMENT_SHADER);
  }
  if (id=="vertex")
  {
    shaderScript = {type:"x-shader/x-vertex"};
		theSource = 
  		"attribute vec3 aVertexPosition;\n"+
      "attribute vec3 aVertexNormal;\n"+
      "attribute vec2 aTextureCoord;\n"+

      "uniform mat4 uMVMatrix;\n"+
      "uniform mat4 uPMatrix;\n"+
      "uniform mat3 uNMatrix;\n"+

      "uniform vec3 uAmbientColor;\n"+

      "uniform vec3 uLightingDirection;\n"+
      "uniform vec3 uDirectionalColor;\n"+

      "uniform vec4 uMaterialColor;\n"+

      "uniform bool uUseLighting;\n"+

      "varying vec2 vTextureCoord;\n"+
      "varying vec3 vLightWeighting;\n"+
      "varying vec4 vMaterialColor;\n"+

      "void main(void) {\n"+
      "    gl_Position = uPMatrix * uMVMatrix * vec4(aVertexPosition, 1.0);\n"+
      "    vTextureCoord = aTextureCoord;\n"+
      "    vMaterialColor = uMaterialColor;\n"+
      
      "    if (!uUseLighting) {\n"+
      "        vLightWeighting = vec3(1.0, 1.0, 1.0);\n"+
      "    } else {\n"+
      "        vec3 transformedNormal = uNMatrix * aVertexNormal;\n"+
      "        float directionalLightWeighting = max(dot(transformedNormal, uLightingDirection), 0.0);\n"+
      "        vLightWeighting = uAmbientColor + uDirectionalColor * directionalLightWeighting;\n"+
      "    }\n"+
      "}\n";

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

// model view matrix
function setMatrixUniforms() 
{
  gl.uniformMatrix4fv(shaderProgram.pMatrixUniform, false, pMatrix);
  gl.uniformMatrix4fv(shaderProgram.mvMatrixUniform, false, mvMatrix);

  var normalMatrix = mat3.create();
  mat4.toInverseMat3(mvMatrix, normalMatrix);
  mat3.transpose(normalMatrix);
  gl.uniformMatrix3fv(shaderProgram.nMatrixUniform, false, normalMatrix);
}

// vbo
function vboBuild(data)
{
  var result = {};
  if ( data.vertexBuffer )
  {
    result.vertexBuffer = gl.createBuffer();
    gl.bindBuffer(gl.ARRAY_BUFFER, result.vertexBuffer);
    gl.bufferData(gl.ARRAY_BUFFER, new Float32Array(data.vertexBuffer), gl.STATIC_DRAW);
  }

  if ( data.normalBuffer )
  {
    result.normalBuffer = gl.createBuffer();
    gl.bindBuffer(gl.ARRAY_BUFFER, result.normalBuffer);
    gl.bufferData(gl.ARRAY_BUFFER, new Float32Array(data.normalBuffer), gl.STATIC_DRAW);
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

function vboDraw(buf)
{
  if ( !buf || !buf.vertexBuffer )
    return;

  if ( buf.vertexBuffer )
  {
    gl.bindBuffer(gl.ARRAY_BUFFER, buf.vertexBuffer);
    gl.vertexAttribPointer(shaderProgram.vertexPositionAttribute, 3, gl.FLOAT, false, 0, 0);
  }

  if ( buf.normalBuffer )
  {
    gl.bindBuffer(gl.ARRAY_BUFFER, buf.normalBuffer);
    gl.vertexAttribPointer(shaderProgram.vertexNormalAttribute, 3, gl.FLOAT, false, 0, 0);
  }

  if ( buf.colorBuffer )
  {
    gl.bindBuffer(gl.ARRAY_BUFFER, buf.colorBuffer);
    gl.vertexAttribPointer(shaderProgram.vertexColorAttribute, 4, gl.FLOAT, false, 0, 0);
  }

  if ( buf.coordBuffer )
  {
    gl.bindBuffer(gl.ARRAY_BUFFER, buf.coordBuffer);  
    gl.vertexAttribPointer(shaderProgram.textureCoordAttribute, 2, gl.FLOAT, false, 0, 0);
  }
    
  gl.bindBuffer(gl.ELEMENT_ARRAY_BUFFER, buf.indexBuffer);
  setMatrixUniforms();

  gl.drawElements(gl.TRIANGLES, buf.indices, gl.UNSIGNED_SHORT, 0);
}

