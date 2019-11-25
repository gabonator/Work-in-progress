function _ASSERT(e)	
{
  if (e) 
    return;

  st2 = function(f) {
    return !f ? [] : 
        st2(f.caller).concat([f.toString().split('(')[0].substring(9) + '(' + f.arguments.join(',') + ')']);
  }
	
  alert("ASSERTION FAILED: " + st2(arguments.callee.caller));
}

function Sunrise()
{
}

Sunrise.prototype.Sunrise = function(date, pos)
{
  var days, lambda, obliq, alpha, delta, equation, hourAngle, sunLong, sunLong2, anomaly;
  var RADS = Math.PI/180.0;
  var DEGS = 180.0/Math.PI;

  days = this.SunriseDay(date.year, date.month, date.day) + 0.5;
  //   mean longitude of the Sun
  sunLong = this.SunriseNormalize(280.461 * RADS + .9856474 * RADS * days);
  //   mean anomaly of the Sun
  anomaly = this.SunriseNormalize(357.528 * RADS + .9856003 * RADS * days);
  //   Find the ecliptic longitude of the Sun
  lambda = this.SunriseNormalize(sunLong + 1.915 * RADS * Math.sin(anomaly) + .02 * RADS * Math.sin(2.0 * anomaly));
  //   Obliquity of the ecliptic
  obliq = 23.439 * RADS - .0000004 * RADS * days;
  //   Find the RA and DEC of the Sun

  alpha = Math.atan2( Math.cos(obliq) * Math.sin(lambda), Math.cos(lambda) );
  delta = Math.asin( Math.sin(obliq) * Math.sin(lambda) );
  // Find the Equation of Time in minutes
  sunLong2 = sunLong - alpha;
  if (sunLong < Math.PI) sunLong2 += Math.PI * 2;
  equation = 1440.0 * (1.0 - sunLong2 / Math.PI / 2.0);

  hourAngle = this.SunriseHourangle( pos.lat, delta );
  // Compute sunrise / sunset times
  dbSunrise = 12.0 - 12.0 * hourAngle / Math.PI - pos.long / 15.0 + equation / 60.0;
  dbSunset  = 12.0 + 12.0 * hourAngle / Math.PI - pos.long / 15.0 + equation / 60.0;

if (isNaN(dbSunrise))
{
//console.log([pos.lat, delta]);
}

  if ( dbSunrise > 24.0 ) dbSunrise -= 24.0;
  if ( dbSunset > 24.0 )  dbSunset  -= 24.0;

  if ( dbSunrise < 0.0 ) dbSunrise += 24.0;
  if ( dbSunset < 0.0 )  dbSunset  += 24.0;

  // Conversion of angle to hours and minutes
  return {daylen:DEGS * hourAngle / 7.5, sunrise:dbSunrise, sunset:dbSunset, time:days - 0.5};
}

Sunrise.prototype.SunriseDay = function ( y, m, d )
{ 
  // get count of days relative to Year 2000
  _ASSERT( y >= 1901 && y <= 2099 );
  var luku = Math.floor(- 7 * (y + (m + 9) / 12) / 4 + 275 * m / 9 + d);
  // avoid overflow
  luku += y * 367;
  return luku - 730531;
}

Sunrise.prototype.SunriseNormalize = function ( x )
{ // returns angle in range <0..2*Pi>
  var b = 0.5 * x / Math.PI;
  var a = 2 * Math.PI * ( b - Math.floor( b ) );
  if ( a < 0 ) a += 2*Math.PI;
  return a;
}

Sunrise.prototype.SunriseHourangle = function ( dbLat, dbDeclin )
{ // Calculate the hourangle
  var RADS = Math.PI/180.0;
  var fo, dfo;
  dfo = RADS * (0.5 * /*SunDia*/ 0.53 + /*Air Refraction*/ 34.0 / 60.0 ); 
  if ( dbLat < 0.0 ) dfo = -dfo;
  fo = Math.tan( dbDeclin + dfo ) * Math.tan( dbLat * RADS );
//  if ( fo > 0.99999 ) fo = 1.0; // avoid overflow
//  if ( fo < -0.99999 ) fo = -1.0; // avoid overflow
//var pfo=fo;
  fo = Math.asin( fo ) + Math.PI / 2.0;
/*
if (isNaN(fo))
{
console.log([pfo, dbDeclin, dfo]);
} */
  return fo;
}

Sunrise.prototype.Test = function()
{
  var d = new Date();

//  var pos = {long:17.733766, lat:48.286168}; 
  var pos = {long:100.324, lat:5.427}; 
  var date = {day:d.getUTCDate(), month:d.getUTCMonth()+1, year:d.getUTCFullYear()};
  var time = {hour:d.getUTCHours(), minute:d.getUTCMinutes()};

  var sunrise = this.Sunrise(date, pos);
  sunrise.timezone = -d.getTimezoneOffset()/60;
  toHours = function(n) {return Math.floor(n) + "h "+Math.floor((n-Math.floor(n))*60)};
  var local = {daylen:toHours(sunrise.daylen), sunrise:toHours(sunrise.sunrise + sunrise.timezone), 
    sunset:toHours(sunrise.sunset + sunrise.timezone)};

  console.log(JSON.stringify(local));

  if ( sunrise.daylen < 0.0001 )
    sunrise.current = "polar night";
  else if ( sunrise.daylen > 23.999 )
    sunrise.current = "polar day";

  var dbCurrentTime = time.hour + time.minute / 60.0;
  sunrise.currentTime = dbCurrentTime + sunrise.timezone;

  if ( sunrise.sunset > sunrise.sunrise )
  {
    if ( dbCurrentTime > sunrise.sunrise && dbCurrentTime <= sunrise.sunset)
      sunrise.current = "SunStateDay";
    else
      sunrise.current = "SunStateNight";
  } 
  else
  {
    if ( dbCurrentTime > sunrise.sunset && dbCurrentTime <= sunrise.sunrise)
      sunrise.current = "SunStateNight";
    else
      sunrise.current = "SunStateDay";
  }
  return sunrise;
};