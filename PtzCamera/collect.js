var request = require('request'),
    username = "*****",
    password = "*****",
    url = "http://192.168.1.91", 
    auth = "Basic " + new Buffer(username + ":" + password).toString("base64");

var fs = require("fs");

function getPosition(handler)
{
  request(
    { url : url+"/cgi/ptdc.cgi?command=get_pos",
      headers : {"Authorization" : auth }
    },
    function (error, response, body) 
    {
      var parsed = body.split("\r\n").join("").match("<posX>(.*?)</posX>.*<posY>(.*?)</posY>");
      if ( parsed.length != 3 )
        handler();
      else
        handler(parseInt(parsed[1]), parseInt(parsed[2]));
    }
  );
}

function goRelative(relx, rely, handler)
{
  relx *= -1;
  rely *= -1;

  request(
    { url : url+"/cgi/ptdc.cgi?command=set_relative_pos&posX="+relx+"&posY="+rely,
      headers : {"Authorization" : auth }
    },
    function (error, response, body) 
    {
      var parsed = body.split("\r\n").join("").match("<code>(.*?)</code>");
      if ( parsed.length != 2 )
        handler();
      else
        handler(parsed[1]);
    }
  );
}

function sendCommand(command, handler)
{
  request(
    { url : url+"/cgi/ptdc.cgi?command="+command,
      headers : {"Authorization" : auth }
    },
    function (error, response, body) 
    {
      if (handler)
        handler(body);
    }
  );
}

function takeScreenshot(path, handler)
{
  request(
    { url : url+"/image.jpg",
      headers : {"Authorization" : auth },
      encoding:"binary"
    },
    function (error, response, body) 
    {
      if ( typeof(body) != "undefined" )
        fs.writeFile(path, body, "binary", handler);
      else
        takeScreenshot(path, handler);
    }
  );
}

function goAbsolute(tx, ty, handler)
{
  getPosition(function(x, y) { 
    //console.log("at "+x+","+y + " going "+(tx-x)+","+(ty-y));
    goRelative(tx-x, ty-y, function(result)
    {
      var distance = Math.floor(Math.sqrt((tx-x)*(tx-x), (ty-y)*(ty-y))); // max 358
      setTimeout(function()
      {
        handler(result);
      }, 4000 + distance*60); //6s pre wifi

    });
  });
}


var list = [];
for ( var y = 0; y <= 80; y+=20)
  for ( var x = 250; x >= 50; x-=20)//25)
    list.push([x, y]);
list.reverse();

function tri(num)
{
  return ("000" + num.toString(10)).substr(-3);
}

function doit()
{
  if ( list.length == 0 )
    return;

  var target = list.pop();
  console.log("going "+target[0]+", "+target[1]);
  goAbsolute(target[0], target[1], function(){
    var path = "shots/img"+tri(target[0])+"_"+tri(target[1])+".jpg";
    console.log("taking shot" + path);

    takeScreenshot(path, function()
    {
      doit();
    });
  });
}


doit();

