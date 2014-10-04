var fs = require('fs')
var http = require('http');

var owfspath = "/mnt/1wire/";
var devices = ["2D474142233030", "2D54594D454B00", "2D474142233000"];
//pages/page.0", "/mnt/1wire/2D.54594D454B00/pages/page.0"];


console.log("Logger started!");

//setInterval(timer, 5000);

function timer()
{
  for (var i in devices)
    readDevice(devices[i]);
}

function owid2path(owid)
{
  return owfspath + owid.substr(0, 2) + "." + owid.substr(2) + "/pages/page.0";
}

function readDevice(devpath)
{
  var curdev = devpath;
  fs.readFile(owid2path(devpath), 'ascii', function (err,data) {
    if (err) {
      return console.log(curdev + ": error " + err);
    }
    data = data.replace("\n", "");
    var cls = data.substr(0,16).split(",")[1];
    console.log(curdev + ": [" + cls + "] " + data.substr(15, 16));
  });                       
}


var lastCo2T = -1;
var lastCo2H = -1;
var lastCo2A = [];
var valueCo2 = [];
setInterval(readCo2, 400);

function readCo2()
{
  var curdev = devices[1];
  fs.readFile(owid2path(curdev), 'ascii', function (err,data) {
    if (err) {
      return console.log(curdev + ": error " + err);
    }
//console.log(data);
//return;
    data = data.substr(16, 16);
    var t = parseInt(data.substr(0,3));
    var h = parseInt(data.substr(13, 1));
    var a = parseInt(data.substr(4, 6));
    var x = data.substr(10, 3);
    if (x != ",h=")
    {
      console.log("co2sens - Invalid data! " /*+ data.split("\n").join(" ")*/);
      return;
    }
    if ( t == lastCo2T )
      return; 
    lastCo2T = t;
//console.log(t + "/" + h + "/" + a + " -- " + data.split("\n").join(" "));
    if (h == 0 && lastCo2H == 1)
    {
      valueCo2.push(avg(lastCo2A));
      console.log("New value! " + avg(lastCo2A));
    }
    lastCo2H = h;
    lastCo2A.push(a);
    if ( lastCo2A.length > 3 )
      lastCo2A.shift();
//    lastCo2A = a;
//    console.log(curdev + ": " + t + "/" + h + "/" + a);
  });                       
}


var valueLight = [];
var valueWind = [];
setInterval(readSomfy, 2000);

function somfyCrcPush(remainder, data)
{
  remainder ^= data;

  for (var b = 8; b > 0; b--)
  {
      if (remainder & 0x80)
          remainder = (remainder << 1) ^ 0x47;
      else
          remainder = (remainder << 1);
  }
  return remainder;
}

function readSomfy()
{
  var curdev = devices[0];
  fs.readFile(owid2path(curdev), 'ascii', function (err,data) {
    if (err) {
      return console.log(curdev + ": error " + err);
    }
    data = data.substr(16, 16);
    // integrity check

    var crc = 0;
    for (i=0; i<15; i++)
      crc = somfyCrcPush( crc, data.charCodeAt(i) );

    if ( data.charCodeAt(15) != (0x40 + (crc&63)) )
    {
      console.log("somfy - Invalid data!" /*+ data*/);
      return;
    }
    var t = parseInt(data.substr(1, 2));
    var l = parseFloat(data.substr(4, 4));
    var w = parseFloat(data.substr(9, 5));
    valueLight.push(l);
    valueWind.push(w);
  });
}

var valueHygro = [];
var valueTemp = [];
setInterval(readDht, 5000);

function readDht()
{
  //S1T+20.6H56.2 #n
  var curdev = devices[2];
  fs.readFile(owid2path(curdev), 'ascii', function (err,data) {
    if (err) {
      return console.log(curdev + ": error " + err);
    }
    data = data.substr(16, 16);
    // integrity check

    var crc = 0;
    for (i=0; i<15; i++)
      crc = somfyCrcPush( crc, data.charCodeAt(i) );

    if ( data.charCodeAt(15) != (0x40 + (crc&63)) )
    {
      console.log("dht - Data integrity check failed! '" + data + "'");
      return;
    }
    var s = data.substr(1, 1);
    var t = parseFloat(data.substr(3, 5));
    var h = parseFloat(data.substr(9, 4));
    if ( /*isNaN(s) ||*/ isNaN(t) || isNaN(h) )
    {
      console.log("dht - Invalid data! '" + data + "'");
      return;
    }
//    console.log("Dht: "+t+" C, " + h + "%");
    valueHygro.push(h);
    valueTemp.push(t);
  });
}

setInterval(upload, 4*60000);

function avg(a)
{
  if ( a.length == 0 )
    return -1;

  if ( a.length == 1 )
    return a[0];

  var sum = 0;
  for ( var i=0; i<a.length; i++)
    sum += a[i];

  return Math.floor((sum/a.length)*10)/10;
}
function upload()
{             
//  var data = {co2:avg(valueCo2), light:avg(valueLight), wind:avg(valueWind), hygro:avg(valueHygro), temp:avg(valueTemp)};
  var data = {};
  if ( valueCo2.length > 0 )
  {
    data.co2 = avg(valueCo2);
    valueCo2 = [];
  }
  if ( valueLight.length > 0 )
  {
    data.light = avg(valueLight);
    valueLight = [];
  }
  if ( valueWind.length > 0 )
  {
    data.wind = avg(valueWind);
    valueWind = [];
  }
  if ( valueHygro.length > 0 )
  {
    data.hygro = avg(valueHygro);
    valueHygro = [];
  }
  if ( valueTemp.length > 0 )
  {
    data.temp = avg(valueTemp);
    valueTemp = [];
  }

  console.log("Upload " +JSON.stringify(data));

  var urlarg = "";
  for (var i in data)
    urlarg += "&"+i+"="+data[i];

//  console.log("Upload " + urlarg);    
  var options = {
    host: 'agro.valky.eu',
    path: '/sensor/co2/?addraw=1'+urlarg
  };

  callback = function(response) {
    var str = '';
    response.on('data', function (chunk) {
      str += chunk;
    });

    response.on('end', function () {
      console.log("Server response: " + str);
    });
  }  
  http.request(options, callback).end();
}
