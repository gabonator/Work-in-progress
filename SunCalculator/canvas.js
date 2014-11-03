var can = document.createElement('canvas');
var w = 512;
var h = 512;
var ctx = can.getContext('2d');
can.width = w;
can.height = h;
ctx.lineWidth = 5;

var sunset = new Sunrise().Test();

sunset.sunset += sunset.timezone;
sunset.rise += sunset.timezone;

var r = w/2;
for (var a=0; a<360; a++)
{
  var r0 = r*0.6, r1 = r*0.9;
  var t = a/360*24;

  var c0 = circlePoint(a, r0*0.95);
  var c1 = circlePoint(a, r1*1.05);
  var p = phase(t, sunset.sunrise, sunset.sunset );
  ctx.strokeStyle = rgbcolor(interpolate([0, 0, 80], [255, 255, 0], p, 0.01));

  ctx.beginPath();
  ctx.moveTo( c0.x + w/2, c0.y + h/2);
  ctx.lineTo( c1.x + w/2, c1.y + h/2);
  ctx.stroke();

//continue;
  var c0 = circlePoint(a, r0);
  var c1 = circlePoint(a, r1);
  var p = phase(t, sunset.sunrise, sunset.sunset );
  ctx.strokeStyle = rgbcolor(interpolate([0, 0, 80], [255, 255, 0], p, 1));

  ctx.beginPath();
  ctx.moveTo( c0.x + w/2, c0.y + h/2);
  ctx.lineTo( c1.x + w/2, c1.y + h/2);
  ctx.stroke();

}

ctx.strokeStyle = "rgba(0, 0, 0, 0.5);";
ctx.lineWidth = 2;
for (var t=0; t<24; t++)
{
  var r0 = r*0.55, r1 = r*0.65;
  var a = t / 24 * 360;

  var c0 = circlePoint(a, r0);
  var c1 = circlePoint(a, r1);

  ctx.beginPath();
  ctx.moveTo( c0.x + w/2, c0.y + h/2);
  ctx.lineTo( c1.x + w/2, c1.y + h/2);
  ctx.stroke();
}

drawNumbers();

var sunpos = new SunPosition();
var days = sunset.time;
var pos = {long:17.733766, lat:48.286168}; 

var d = new Date();
var hours = d.getUTCHours() + (d.getUTCMinutes() + d.getUTCSeconds() / 60) / 60;
var p = sunpos.GetPosition({days:days, hours:hours}, pos);
var sunpositionnow = {t:i, zenith:p.zenithAngle, azimuth:p.azimuth};
var p = sunpos.GetPosition({days:days, hours:12}, pos);
var sunposition12 = {t:i, zenith:p.zenithAngle, azimuth:p.azimuth};

var hours = 0;
var sunpositions = [];
for ( var i=sunset.sunrise - 0*sunset.timezone; i<sunset.sunset - sunset.timezone*1; i+=0.25)
//for ( var i=2; i<=18; i+=0.1)
{
  hours = i;
  var p = sunpos.GetPosition({days:days, hours:hours}, pos);
  sunpositions[sunpositions.length] = {t:i, zenith:p.zenithAngle, azimuth:p.azimuth};
}
//var p = sunpos.GetPosition({days:days, hours:sunset.sunset}, pos);
//sunpositions[sunpositions.length] = {t:i, zenith:p.zenithAngle, azimuth:p.azimuth};

//console.log(sunpositions);
//console.log(JSON.stringify(sunpos.GetPosition({days:days, hours:hours}, pos)));


function drawNumbers()
{
  ctx.strokeStyle = rgbcolor([128, 128, 128]);
  ctx.fillStyle = rgbcolor([128, 128, 128]);
  drawCentered(circlePoint(12/24*360, r*0.75), "12");
  drawCentered(circlePoint(0/24*360, r*0.75), "0");
  drawCentered(circlePoint(6/24*360, r*0.75), "6");
  drawCentered(circlePoint(18/24*360, r*0.75), "18");
}

function drawCentered(pt, text)
{
  var size = {width:ctx.measureText(text).width, height:50};
  pt = {x:pt.x - size.width/2 + w/2, y:pt.y - size.height/2 + h/2};
  ctx.textBaseline="top";
  ctx.textAlignment="left";
  ctx.fillStyle = rgbcolor([0, 0, 0]);
//  ctx.fill = "rgb(255,0,0)";
//  ctx.stroke = "rgb(255,0,0)";
  ctx.font = "50px Arial";
  ctx.fillText(text, pt.x, pt.y);
}

function circlePoint(a, r)
{
  return {
    x: Math.cos((a+90)*Math.PI/180)*r,
    y: Math.sin((a+90)*Math.PI/180)*r
  };
}

function phase(v, min, max)
{
  var trans = 0.3;
  if ( v < min-trans )
    return 0;
  if ( v > max+trans )
    return 0;
  if ( v < min+trans)
    return ((v-min)/trans+1)/2;
  if ( v > max-trans)
    return 1-((v-max)/trans+1)/2;
  return 1;
}

function interpolate(a, b, f, t)
{
  return [a[0]*(1-f) + b[0]*f, a[1]*(1-f) + b[1]*f, a[2]*(1-f) + b[2]*f, t];  
}

function rgbcolor(c)
{
  if (c.length == 4)
    return "rgba("+Math.floor(c[0])+"," + Math.floor(c[1])+","+Math.floor(c[2])+", "+c[3].toFixed(2)+")";
  return "rgba("+Math.floor(c[0])+"," + Math.floor(c[1])+","+Math.floor(c[2])+", 0.9)";
}
