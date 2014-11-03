/**
 * @author alteredq / http://alteredqualia.com/
 *
 * Based on Nvidia Cg tutorial
 */

THREE.FresnelShader = {

	uniforms: {

		"mRefractionRatio": { type: "f", value: 1.02 },
		"mFresnelBias": { type: "f", value: 0.1 },
		"mFresnelPower": { type: "f", value: 2.0 },
		"mFresnelScale": { type: "f", value: 1.0 },

	},

	vertexShader: [

		"uniform float mRefractionRatio;",
		"uniform float mFresnelBias;",
		"uniform float mFresnelScale;",
		"uniform float mFresnelPower;",

		"varying vec3 vReflect;",
		"varying vec3 vRefract[3];",
		"varying float vReflectionFactor;",
    "varying vec3 vNormal;",

		"void main() {",
		  "vNormal = normal;",
			"vec4 mvPosition = modelViewMatrix * vec4( position, 1.0 );",
			"vec4 worldPosition = modelMatrix * vec4( position, 1.0 );",
			"vec3 worldNormal = normalize( mat3( modelMatrix[0].xyz, modelMatrix[1].xyz, modelMatrix[2].xyz ) * normal );",
			"vec3 I = worldPosition.xyz - cameraPosition;",
			"vReflectionFactor = (mFresnelBias + mFresnelScale * pow( 1.0 + dot( normalize( I ), worldNormal ), mFresnelPower ));",
			"gl_Position = projectionMatrix * mvPosition;",
		"}"

	].join("\n"),

	fragmentShader: [

		"uniform samplerCube tCube;",

		"varying vec3 vReflect;",
		"varying vec3 vRefract[3];",
    "varying vec3 vNormal;",
		"varying float vReflectionFactor;",
    "uniform sampler2D tex;",

		"void main() {",
			"vec4 refractedColor = vec4( 1.0 );",
      "vec4 reflectedColor = vec4( 0.0 );",
			"gl_FragColor = mix( refractedColor, reflectedColor, clamp( vReflectionFactor, 0.0, 1.0 ) );",
			"gl_FragColor = vec4(vec3(gl_FragColor), 0.3);",

      "vec3 light = vec3(0.5, 0.2, -1.0);",
      "light = normalize(light);",
      "float dProd = max(0.0, dot(vNormal, light)+1.0);",
      "dProd = clamp(dProd, 0.0, 1.0);",
      "gl_FragColor = mix(vec4(1, 1, 1, gl_FragColor.a), gl_FragColor, dProd);",
		"}"

	].join("\n")

};

/*
  vec3 light = vec3(0.5, 0.2, 1.0);
  light = normalize(light);
  float dProd = max(0.0, dot(vNormal, light));
  gl_FragColor = vec4(dProd, dProd, dProd, 1.0);
*/