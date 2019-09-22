'use strict';

var fs = require('fs');
var BTSP = require('bluetooth-serial-port');
var serial = new BTSP.BluetoothSerialPort();
var dns = require("dns");

// bluetooth
const address = "00:18:E4:35:5F:2A";
const channel = 1;
var reconnect = false;
var connected = false;

serial.on('data', function(data) {
   logData(data);
});

serial.on('closed', function() { 
  connected= false;
  if (reconnect)
    clearTimeout(reconnect);

  console.log("bt: connection closed, reconnecting...");
  reconnect = setTimeout(btReconnect, 10000);
});

function btReconnect()
{
  if (reconnect)
    clearTimeout(reconnect);

  console.log("bt: connecting...");

  serial.connect(address, channel, function() {
    console.log('bt: connected');
    connected = true;
  }, function () {
    if (reconnect)
      clearTimeout(reconnect);

    console.log("bt: cannot connect, reconnecting...");
    reconnect = setTimeout(btReconnect, 10000);
  });
}

btReconnect();
  
// data logger
var logBuffer = "";
var logBufferCollect = [];
var logLastData = null;
var logBufferAccess = [];
var logLastLine = null;

function logData(msg)
{
  console.log(msg);
}

function shortArrayToBytes(arr)
{
  var out = [];
  for (var i in arr)
  {
    var x = arr[i];
    out.push(x & 0xff);
    out.push(x >> 8);
  }
  return out;
}

var pattern;

function cartesian(c, x, y)
{
  if (x < -2047 || x > 2047) 
    throw "wrong x";
  if (y < -2047 || y > 2047) 
    throw "wrong y";
  var radius = Math.sqrt(x*x+y*y);
  var color = c;
  var angle = Math.atan2(-y, x)/Math.PI*180;
  if (angle < 0)
    angle += 360;
  angle = angle/360*1024;
  if (radius < 0 || radius > 4095) 
    throw "wrong radius";
  if (angle < 0 || angle >= 1024)
    throw "wrong angle";
  if (c < 0 || c > 7)
    throw "wrong color";
  return [(color << 13) + Math.floor(radius), Math.floor(angle)];
}
/*
 1 = *cervena
 2 = *zelena
 3 = oranzova
 4 = *modra
 5 = fialova
 6 = svetlo modra
 7 = svetlo fialova
*/

var linewalk = [[233,204,232,198,231,193,230,187,225,185,220,186,213,186,206,187,200,186,195,185,190,183,185,181,180,178,176,175,172,172,169,168,166,163,165,158,166,152,169,148,173,145,177,141,182,138,187,135,192,134,198,132,203,132,211,132,217,132,222,133,227,135,233,137,239,140,243,143,247,146,250,150,251,155,252,161,251,166,248,171,245,175,241,178,237,181,232,183,234,188,235,193,235,198,234,203,233,204],[207,183,212,183,218,182,223,182,228,180,234,178,238,175,242,172,246,168,249,163,249,158,247,153,244,148,240,144,236,141,231,139,226,137,220,136,214,135,207,135,202,135,201,135,196,136,191,137,186,140,181,142,177,146,173,149,170,153,168,158,170,163,174,169,178,172,182,175,187,178,193,180,199,182,204,183,207,183],[232,164,231,159,232,154,234,159,233,164,232,164],[159,130,154,128,149,125,144,122,139,118,135,114,132,110,128,106,126,101,123,97,121,92,119,87,118,82,117,76,116,71,115,65,108,61,103,60,98,58,95,53,95,48,96,43,99,38,92,36,85,35,76,35,71,35,64,35,58,35,50,35,45,35,40,35,35,35,29,35,24,35,19,35,12,35,7,36,2,35,6,32,11,31,21,31,26,31,33,32,38,31,43,32,48,32,53,32,58,32,64,32,73,31,79,32,84,31,91,32,99,32,104,32,105,37,102,41,99,47,98,50,98,52,102,56,109,58,113,58,115,58,116,58,118,62,118,68,120,74,121,80,122,85,124,90,126,95,129,100,132,105,135,109,139,112,142,116,146,119,150,122,155,124,161,125,166,124,171,124,167,119,164,115,161,111,158,107,156,102,155,99,155,96,155,91,156,86,159,81,163,77,167,74,172,71,177,69,183,68,191,68,197,68,202,68,208,69,214,70,215,76,215,82,215,87,218,92,222,95,228,94,232,91,234,85,235,78,235,73,233,68,230,64,224,63,219,66,214,65,208,63,203,62,198,61,192,60,186,59,180,57,175,56,168,55,163,54,157,53,152,53,147,52,142,52,136,51,131,50,125,50,127,45,131,42,132,37,129,33,134,31,140,31,147,31,155,31,160,31,168,31,174,31,182,31,187,31,195,31,202,30,207,31,214,31,222,30,228,31,233,31,240,31,247,30,253,30,259,31,264,31,270,31,277,31,284,31,290,30,295,30,300,30,305,31,310,30,316,30,321,30,326,30,331,30,340,30,345,30,351,30,357,30,363,30,369,30,376,30,381,31,384,31,384,35,383,35,376,35,370,34,365,34,359,34,353,34,348,34,343,34,337,34,325,34,315,34,307,34,301,34,296,35,291,35,285,35,279,35,272,35,265,35,259,35,252,35,245,35,240,35,235,35,230,35,223,35,218,35,213,35,208,35,202,35,195,35,189,35,184,35,179,35,174,35,169,35,162,35,157,35,151,35,144,35,138,35,136,40,134,45,139,48,145,48,151,49,156,49,163,50,169,51,176,52,181,53,186,54,191,55,196,57,201,58,207,59,212,61,218,62,222,59,228,59,232,62,235,66,238,71,239,77,238,83,236,88,234,93,230,97,223,99,218,98,214,94,212,88,211,82,212,77,210,72,205,72,194,71,188,71,183,72,178,73,172,75,167,78,163,81,160,86,158,92,158,97,159,102,161,107,165,112,170,117,174,120,178,123,173,127,167,128,161,129,159,130]];

var pattern = [];
var phase = 0;
var bufGetReady = [];
var bufSendPat = [];
function calcPattern()
{
  // triangle
  pattern = [32768*0 + 2000, 0, 
               16384   + 2000, Math.floor(1024/3), 
               8192    + 2000, Math.floor(1024*2/3),
               32768   + 2000, 0];

  // flower
  pattern = [];

  var N = 120; // 750 max
  var color = 2; // 1..7
  for (var i=0; i<N+1; i++)
  {
    color = 4; //(((i + N/8/2) /(N/8))%7)+1;
    var radius = 1000 + Math.cos((i+phase)*8/N*2*Math.PI)*500;
    var angle = 1024*i/N;
    pattern.push((i>0 ? (color<<13) : 0) + Math.floor(radius));
    pattern.push(Math.floor(angle));
  }

/*
  // grid
  var c = 0;
  for (var x=-2000; x<=2000; x+=800)
  {
//    pattern = pattern.concat(cartesian(c++ & 1 ? 0 : 4, x, Math.cos(x/2000*6*4)*400));
    pattern = pattern.concat(cartesian(0, x, -2000));
    pattern = pattern.concat(cartesian([1, 2, 4][c++%3], x, 2000));
  }

  for (var x=-2000; x<=2000; x+=800)
  {
    pattern = pattern.concat(cartesian(0, -2000, x));
    pattern = pattern.concat(cartesian([1, 2, 4][c++%3], 2000, x));
  }   
*/

/*
  // line rider
  for (var i in linewalk)
  {
    var poly = linewalk[i];
    for (var j=0; j<poly.length; j+=2)
    {
      var x = (poly[j] / 384)*4000-2000;
      var y = (poly[j+1] / 384)*4000-2000+1050;    // 0..216
      pattern = pattern.concat(cartesian(j==0 ? 0 : 4, x, -y));
    }
  }
*/

  pattern = shortArrayToBytes(pattern);
  bufGetReady = [256-86, 5, 0, 90].concat(shortArrayToBytes([8, pattern.length+10]));
  bufSendPat =  [256-86, 6, 0, 90].concat(shortArrayToBytes([pattern.length+10, pattern.length-1, pattern.length-1]));
}

var sqOn = [1];
var sqOff = [0];
var sqRotate = [1, 0, 0, 0, 0, 70];
var seq = 0;              
setInterval(() =>
{
  if (connected)
  {
    var buf = [];
    switch (seq++)
    {
     case 1: 
       calcPattern();
       buf = bufGetReady; 
     break;

     case 2: 
       buf = bufSendPat.concat(pattern); 
     break;

     case 3: 
       buf = [170, 4, 0, 90].concat(shortArrayToBytes([6+sqRotate.length])).concat(sqRotate);
     break;
    }
    if (buf.length > 0)
    {
      console.log("Sending: " + buf.length);
      serial.write(new Buffer(buf), () => 0); 
    }
  }
}, 1000);
