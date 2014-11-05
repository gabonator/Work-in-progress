var mouseX = 0, mouseY = 0;
var windowHalfX = window.innerWidth / 2;
var windowHalfY = window.innerHeight / 2;
var degToRad = Math.PI/180;

init();
animate();

var motionHeading = 0;
var motionTilt = 0;

window.mobilecheck = function() {
  var check = false;
  (function(a,b){if(/(android|bb\d+|meego).+mobile|avantgo|bada\/|blackberry|blazer|compal|elaine|fennec|hiptop|iemobile|ip(hone|od)|iris|kindle|lge |maemo|midp|mmp|mobile.+firefox|netfront|opera m(ob|in)i|palm( os)?|phone|p(ixi|re)\/|plucker|pocket|psp|series(4|6)0|symbian|treo|up\.(browser|link)|vodafone|wap|windows ce|xda|xiino/i.test(a)||/1207|6310|6590|3gso|4thp|50[1-6]i|770s|802s|a wa|abac|ac(er|oo|s\-)|ai(ko|rn)|al(av|ca|co)|amoi|an(ex|ny|yw)|aptu|ar(ch|go)|as(te|us)|attw|au(di|\-m|r |s )|avan|be(ck|ll|nq)|bi(lb|rd)|bl(ac|az)|br(e|v)w|bumb|bw\-(n|u)|c55\/|capi|ccwa|cdm\-|cell|chtm|cldc|cmd\-|co(mp|nd)|craw|da(it|ll|ng)|dbte|dc\-s|devi|dica|dmob|do(c|p)o|ds(12|\-d)|el(49|ai)|em(l2|ul)|er(ic|k0)|esl8|ez([4-7]0|os|wa|ze)|fetc|fly(\-|_)|g1 u|g560|gene|gf\-5|g\-mo|go(\.w|od)|gr(ad|un)|haie|hcit|hd\-(m|p|t)|hei\-|hi(pt|ta)|hp( i|ip)|hs\-c|ht(c(\-| |_|a|g|p|s|t)|tp)|hu(aw|tc)|i\-(20|go|ma)|i230|iac( |\-|\/)|ibro|idea|ig01|ikom|im1k|inno|ipaq|iris|ja(t|v)a|jbro|jemu|jigs|kddi|keji|kgt( |\/)|klon|kpt |kwc\-|kyo(c|k)|le(no|xi)|lg( g|\/(k|l|u)|50|54|\-[a-w])|libw|lynx|m1\-w|m3ga|m50\/|ma(te|ui|xo)|mc(01|21|ca)|m\-cr|me(rc|ri)|mi(o8|oa|ts)|mmef|mo(01|02|bi|de|do|t(\-| |o|v)|zz)|mt(50|p1|v )|mwbp|mywa|n10[0-2]|n20[2-3]|n30(0|2)|n50(0|2|5)|n7(0(0|1)|10)|ne((c|m)\-|on|tf|wf|wg|wt)|nok(6|i)|nzph|o2im|op(ti|wv)|oran|owg1|p800|pan(a|d|t)|pdxg|pg(13|\-([1-8]|c))|phil|pire|pl(ay|uc)|pn\-2|po(ck|rt|se)|prox|psio|pt\-g|qa\-a|qc(07|12|21|32|60|\-[2-7]|i\-)|qtek|r380|r600|raks|rim9|ro(ve|zo)|s55\/|sa(ge|ma|mm|ms|ny|va)|sc(01|h\-|oo|p\-)|sdk\/|se(c(\-|0|1)|47|mc|nd|ri)|sgh\-|shar|sie(\-|m)|sk\-0|sl(45|id)|sm(al|ar|b3|it|t5)|so(ft|ny)|sp(01|h\-|v\-|v )|sy(01|mb)|t2(18|50)|t6(00|10|18)|ta(gt|lk)|tcl\-|tdg\-|tel(i|m)|tim\-|t\-mo|to(pl|sh)|ts(70|m\-|m3|m5)|tx\-9|up(\.b|g1|si)|utst|v400|v750|veri|vi(rg|te)|vk(40|5[0-3]|\-v)|vm40|voda|vulc|vx(52|53|60|61|70|80|81|83|85|98)|w3c(\-| )|webc|whit|wi(g |nc|nw)|wmlb|wonu|x700|yas\-|your|zeto|zte\-/i.test(a.substr(0,4)))check = true})(navigator.userAgent||navigator.vendor||window.opera);
  return check;
}

if(window.DeviceOrientationEvent && window.mobilecheck() ) 
{
  window.addEventListener('deviceorientation', function(event) 
  {
    motionTilt = Math.max(0.01, event.beta);
    motionHeading = typeof(event.webkitCompassHeading) != "undefined" ? -event.webkitCompassHeading : event.alpha;
  }, false);
} else
{
  document.addEventListener( 'mousemove', onDocumentMouseMove, false );
}

function init() {

	container = document.createElement( 'div' );
	document.body.appendChild( container );

	camera = new THREE.PerspectiveCamera( 60, window.innerWidth / window.innerHeight, 1, 10000 );
	camera.position.z = 3200;

	// scenes
	scene = new THREE.Scene();

  // light
  var light = new THREE.AmbientLight( 0x303030 ); // soft white light
  scene.add( light );

	var light = new THREE.PointLight(0xffffff, 1.5);
	light.position.set(0,20000,10000);
	scene.add(light);

  var spotLight = new THREE.SpotLight( 0xffffff, 2 );
//  spotLight.shadowCameraVisible = true;
  spotLight.position.set( 0, 2000, 0 );
  spotLight.target.position.set( 0, 0, 0 );
  spotLight.castShadow = true;
  spotLight.shadowCameraNear = 1000;
  spotLight.shadowCameraFar = 6000;
  spotLight.shadowCameraFov = 50;

  scene.add( spotLight );
  lightSpot = spotLight;

	// sphere
	var geometry = new THREE.SphereGeometry( 2000, 32*2, 16*2/*, 0, 2*Math.PI, 0, Math.PI/2*/ );

	var shader = THREE.FresnelShader;
	var uniforms = THREE.UniformsUtils.clone( shader.uniforms );

	var parameters = { fragmentShader: shader.fragmentShader, vertexShader: shader.vertexShader, uniforms: uniforms, transparent:true };
	var material = new THREE.ShaderMaterial( parameters );
	var mesh = new THREE.Mesh( geometry, material );

	scene.add( mesh );
	scene.matrixAutoUpdate = false;

	// plane
  var squareGeometry = new THREE.Geometry();

  r = 2200;
  var coords = [];
  for (var i=0; i<64; i++)
  {        
    squareGeometry.vertices.push(new THREE.Vector3(Math.cos(i/64*Math.PI*2)*r, 0, Math.sin(i/64*Math.PI*2)*r));
    coords.push( new THREE.Vector2(Math.cos(i/64*Math.PI*2)*0.5+0.5, -Math.sin(i/64*Math.PI*2)*0.5+0.5) );
  }

  squareGeometry.vertices.push(new THREE.Vector3(0, 0, 0));
  coords.push( new THREE.Vector2(0.5, 0.5) );

  for (var i=0; i<64; i++)
  {
    squareGeometry.faces.push(new THREE.Face3(i, (i+1)%64, 64));
    squareGeometry.faceVertexUvs[ 0 ].push([coords[i], coords[(i+1)%64], coords[64]]);
  }

  squareGeometry.computeFaceNormals();
  squareGeometry.computeVertexNormals();

  var texture = new THREE.Texture(can); 
  texture.needsUpdate = true;

  var material = new THREE.MeshBasicMaterial( {map: texture, side:THREE.DoubleSide, transparent:true } );

  var plane = new THREE.Mesh( squareGeometry, material );
  plane.receiveShadow = true;
  scene.add( plane );
  squareMesh = plane;

	// sun trace
  r = 2000;

  // TODO: http://www.satellite-calculations.com/Satellite/suncalc.htm
  var rad = Math.PI/180;

  celestialPosition = function(azimuth, zenith)
  {
    var vSunLightDir = {}
    vSunLightDir.x = -Math.cos((90-zenith)*degToRad) * Math.sin(azimuth*degToRad);
    vSunLightDir.y = -Math.sin((90-zenith)*degToRad);
    vSunLightDir.z =  Math.cos((90-zenith)*degToRad) * Math.cos(azimuth*degToRad);

    return new THREE.Vector3(-vSunLightDir.x, -vSunLightDir.y, -vSunLightDir.z);
  }

  var SunPath = THREE.Curve.create(
      function () {},

      function ( t ) { //getPoint: t is between 0-1
        var i = (t*(sunpositions.length-1));
        var di = Math.floor(i);
        var fi = i-di;
        var p0 = {rot:sunpositions[di].azimuth, elev:sunpositions[di].zenith};
        var p1 = {rot:sunpositions[(di+1)%sunpositions.length].azimuth, elev:sunpositions[(di+1)%sunpositions.length].zenith};
        var p = {rot:p0.rot + (p1.rot-p0.rot)*fi, elev:p0.elev + (p1.elev-p0.elev)*fi};
        var r = 2000;
        return celestialPosition(p.rot, p.elev).multiplyScalar(r);
      }
  );

  var material = new THREE.MeshBasicMaterial( { color: 0xb0b000, transparent: true, opacity: 0.5 } );
  var path = new SunPath( 10 );
  var geometry = new THREE.TubeGeometry(
      path,  //path
      40,    //segments
      30,     //radius
      8,     //radiusSegments
      false  //closed
  );
  meshSunPath = new THREE.Mesh(geometry, material);
  scene.add(meshSunPath);

  // moon
  var MoonPath = THREE.Curve.create(
    function () {},

    function ( t ) { //getPoint: t is between 0-1
        var i = (t*(sunpositions.length-1));
        var di = Math.floor(i);
        var fi = i-di;
        var p0 = {rot:sunpositions[di].azimuth, elev:sunpositions[di].zenith};
        var p1 = {rot:sunpositions[(di+1)%sunpositions.length].azimuth, elev:sunpositions[(di+1)%sunpositions.length].zenith};
        var p = {rot:p0.rot + (p1.rot-p0.rot)*fi, elev:p0.elev + (p1.elev-p0.elev)*fi};
        var r = 2000;
        var p3 = celestialPosition(p.rot, p.elev).multiplyScalar(r);
        return new THREE.Vector3(p3.x, p3.y, -p3.z);
    }
  );

  var material =new THREE.MeshBasicMaterial( { color: 0x0000b0, transparent: true, opacity: 0.5 } );
  var path = new MoonPath( 10 );
  var geometry = new THREE.TubeGeometry(
      path,  //path
      30,    //segments
      30,     //radius
      8,     //radiusSegments
      false  //closed
  );
  meshMoonPath = new THREE.Mesh(geometry, material);
//  scene.add(meshMoonPath);

  // north
  var geometry = new THREE.Geometry();
 
  var t = {w:489, h:687, s:1.3};
  var coords = [[-t.w/2*t.s, -t.h/2*t.s], [t.w/2*t.s, -t.h/2*t.s], [t.w/2*t.s, t.h/2*t.s], [-t.w/2*t.s, t.h/2*t.s]];
  var textco = [[0, 0], [1, 0], [1, 1], [0, 1]];
  var tc = [];
  for (var i = 0; i < 4; i++)
  {
    geometry.vertices.push(new THREE.Vector3(coords[i][0], 0, coords[i][1]));
    tc[i] = new THREE.Vector2(1-textco[i][0], textco[i][1]);
  }

  geometry.faces.push(new THREE.Face3(0, 1, 2));
  geometry.faces.push(new THREE.Face3(0, 2, 3));
  geometry.faceVertexUvs[ 0 ].push([tc[0], tc[1], tc[2]]);
  geometry.faceVertexUvs[ 0 ].push([tc[0], tc[2], tc[3]]);

  geometry.computeFaceNormals();
  geometry.computeVertexNormals();

  var texture = new THREE.ImageUtils.loadTexture('north.png');
  var material = new THREE.MeshBasicMaterial( {map: texture, side:THREE.DoubleSide, transparent:true, alphaTest:0.5  } );

  var northarrow = new THREE.Mesh(geometry, material);
  northarrow.rotation.y = 180*degToRad;
  northarrow.position.z = -1800;
  northarrow.position.x = 0;
  northarrow.position.y = 100;
  northarrow.updateMatrix();
  scene.add(northarrow);
  meshCylinder = northarrow;

/*
  var material =new THREE.MeshBasicMaterial( { color: 0xff0000, transparent: false, opacity: 1.0 } );
  var cylinder = new THREE.Mesh(new THREE.CylinderGeometry(0, 200, 400, 50, 50, false), material);
  cylinder.rotation.x = -90*degToRad;
  cylinder.position.z = -2000;
  cylinder.position.y = 0;
  cylinder.scale.z = 0.3;
  scene.add(cylinder);

  meshCylinder = cylinder;
  meshCylinder.updateMatrix();
*/

  // clock
/*
  var material = new THREE.MeshBasicMaterial( { color: 0x909090, transparent: false, opacity: 1.0 } );
  var cylinder = new THREE.Mesh(new THREE.CylinderGeometry(0, 100, 300, 50, 50, false), material);
  cylinder.rotation.x = 90*degToRad;
  cylinder.position.z = 1300;
  cylinder.position.y = 0;
  cylinder.scale.z = 0.3;
  scene.add(cylinder);

  meshClock = cylinder;
  meshClock.updateMatrix();
*/

  var texture = new THREE.ImageUtils.loadTexture('clock.png');
  var material = new THREE.MeshBasicMaterial( {map: texture, side:THREE.DoubleSide, transparent:true, alphaTest:0.5  } );

  var clockarrow= new THREE.Mesh(geometry, material);
  clockarrow.rotation.y = 0*degToRad;
  clockarrow.position.z = 1200;
  clockarrow.position.x = 0;
  clockarrow.position.y = 50;
  clockarrow.scale.x = clockarrow.scale.y = clockarrow.scale.z = 0.75;
  clockarrow.updateMatrix();
  scene.add(clockarrow);
  meshClock = clockarrow;

  // sun
  var material =new THREE.MeshBasicMaterial( { color: 0xffff00, transparent: false, opacity: 1.0 } );
	var geometry = new THREE.SphereGeometry( 200, 32, 16 );
  var sun = new THREE.Mesh(geometry, material);
  var sunpos = 0 ? sunposition12 : sunpositionnow;
  var p = celestialPosition(sunpos.azimuth, sunpos.zenith).multiplyScalar(r);
  sun.position.x = p.x;
  sun.position.y = p.y;
  sun.position.z = p.z;
  scene.add(sun);

  meshSun = sun;
  meshSun.updateMatrix();

  // model
  var jsonLoader = new THREE.JSONLoader();
	jsonLoader.load( "model.js", function ( geometry, materials ) 
  {
  	var material = new THREE.MeshFaceMaterial( materials );
  	model = new THREE.Mesh( geometry, material );
  	model.scale.set(100,100,100);
    model.rotation.y = 180*degToRad;
    model.castShadow = true;
  	scene.add( model );
  });

  // renderer
	renderer = new THREE.WebGLRenderer( { antialias: false } );
	renderer.setSize( window.innerWidth, window.innerHeight );
	renderer.autoClear = false;
  renderer.setClearColor( 0xf0f0f0, 1);
	container.appendChild( renderer.domElement );

  renderer.sortObjects = false;
	renderer.shadowMapEnabled = true;
	renderer.shadowMapType = THREE.PCFShadowMap;
//  renderer.shadowMapType = THREE.PCFSoftShadowMap;

	window.addEventListener( 'resize', onWindowResize, false );
}

function render() {
	var timer = 0.0001 * Date.now();

  var matNorth = new THREE.Matrix4();
  matNorth.copy( meshCylinder.matrix );

  var matClock = new THREE.Matrix4();
  matClock.copy( meshClock.matrix );

  var matSun = new THREE.Matrix4();
  matSun.copy( meshSun.matrix );

  meshSunPath.rotation.y = -motionHeading*degToRad;
  meshMoonPath.rotation.y = -motionHeading*degToRad;
  meshCylinder.applyMatrix(new THREE.Matrix4().makeRotationY( -motionHeading*degToRad ) );
  meshClock.applyMatrix(new THREE.Matrix4().makeRotationY( -myTime()/24*360*degToRad) );
  meshSun.applyMatrix(new THREE.Matrix4().makeRotationY( -motionHeading*degToRad ) );

  camera.position.x = 0;
  camera.position.y = 7000*Math.cos(motionTilt*degToRad);
  camera.position.z = 7000*Math.sin(motionTilt*degToRad);
	camera.lookAt( scene.position );

  // update light
  //scene.updateMatrixWorld(true);

  var sunPosition = new THREE.Vector3();
  sunPosition.setFromMatrixPosition( meshSun.matrixWorld );
  lightSpot.position.set(sunPosition.x, sunPosition.y*3, sunPosition.z); 

	renderer.clear();
	renderer.render( scene, camera );

  meshCylinder.matrix.copy(matNorth);
  meshClock.matrix.copy(matClock);
  meshSun.matrix.copy(matSun);
}

// utils
function onWindowResize() {
	windowHalfX = window.innerWidth / 2;
	windowHalfY = window.innerHeight / 2;

	camera.aspect = window.innerWidth / window.innerHeight;
	camera.updateProjectionMatrix();

	renderer.setSize( window.innerWidth, window.innerHeight );
}

function onDocumentMouseMove( event ) {
	mouseX = ( event.clientX - windowHalfX ) * 10;
	mouseY = Math.max(0.1,( event.clientY - windowHalfY*0 )-50);
  motionTilt = mouseY/4;
  motionHeading = mouseX/20;
}

function animate() {
  setTimeout( function() {
    requestAnimationFrame( animate );
  }, 1000 / 30 );
	render();
}

// utils

function myTime()
{
  var d = new Date();
  return d.getHours() + d.getMinutes()/60 + d.getSeconds()/3600;
}