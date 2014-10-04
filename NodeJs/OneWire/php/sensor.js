var url = "/mnt/1wire/2D.54594D454B00/pages/page.0";

var fs = require('fs')
var http = require('http');

var lastTime = -1;

function load()
{
  fs.readFile(url, 'ascii', function (err,data) {
    if (err) {
      return console.log(err);
    }
    var raw = parseInt(data.substr(20,6));
    var second = parseInt(data.substr(16,3));
    var heat = parseInt(data.substr(29,1));
    if ( lastTime != second )
    {
      lastTime = second;
      processData(second, raw, heat);
    }
  });
}

var lastHeat = 0, lastValue = 0;
function processData(second, raw, heat)
{
  if ( lastHeat == 1 && heat == 0 )
  {
    console.log(" ===== " + lastValue.toString(16) + " === ");
    upload("addraw="+lastValue);
  }

  lastHeat = heat;
  lastValue = raw;
  //console.log(second + "/" + raw.toString(16) + "/" + heat );
}

function upload(data)
{
  var options = {
    host: 'agro.valky.eu',
    path: '/sensor/co2/?'+data
  };

  callback = function(response) {
    var str = '';

    //another chunk of data has been recieved, so append it to `str`
    response.on('data', function (chunk) {
      str += chunk;
    });

    //the whole response has been recieved, so we just print it out here
    response.on('end', function () {
      console.log("Server reply: " + str);
    });
  }

  http.request(options, callback).end();
}

setInterval(load, 300);