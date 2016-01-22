"use strict";
process.title = 'Ulozto.cz interface';

// Web server ==============================================================
var request = require("request");
var http = require('http');
var url = require('url');
var fs = require('fs');
var webbase = ".";

console.log("  - Webserver at localhost running ");

var currentResponse;

http.createServer(function (request, response) {
  var parsedUrl = url.parse(request.url);
  var uri = parsedUrl.pathname;
  var query = parsedUrl.query;
  if ( !query )
  {
    if ( uri == "/" )
      uri = "/index.html";

    var file = webbase + uri;
    fs.exists( file, function(exists)
    { 
      if(!exists) 
      {
        response.writeHead(404, {"Content-Type": "text/plain"});
        response.write("404 Not Found\n");
        response.end();
        return;
      }

      if ( file.substr(-5) == ".html" )
        response.writeHead(200, {'Content-Type': 'text/html'}); 
      else
        response.writeHead(200, {'Content-Type': 'text/plain'}); 

      response.end(fs.readFileSync(file));
    });
  } else
  {
    query = unescape(query);
    console.log("query='" +query+"'");
    currentResponse = response;
    eval(query);
    currentResponse = null;
  }
}).listen(80);


// search api
var decoderClass = require('./engine/decoder.js').kapp;
var getDownloadLink = require('./engine/loader.js').getDownloadLink;
var transcribe = require('./captcha/voicerecognition/transcribe.js').transcribe;
var matcher = require('./captcha/voicerecognition/matcher.js').matcher;

function getSuggestion(term)
{
  var safeResponse = currentResponse;
  var suggestUrl = "http://ulozto.cz/searchSuggest.php?term=";

  request(suggestUrl + term, function(error, response, body) {
    safeResponse.end(body);
  });

}

function doSearch(term)
{
  var safeResponse = currentResponse;
  var searchUrl = "http://ulozto.cz/hledej?q=";

  var trim = function (str)
  {
    while ( str.length > 1 && str.charCodeAt(str.length-1) == 0 )
      str = str.substr(0, str.length-1);
    return str;
  }

  var decode = function(data, key)
  {
  	var decoder = new decoderClass(key); 
    var result = [];
    var subdata = [];

  	var index = 0;
    for (var i in data)
    {
     subdata[index % 7] = trim(decoder.decrypt(data[i]));
     if ( index % 7 == 6 )
     {
       var url = subdata[0];
       var mainInfo = subdata[6].split("\n").join("");
       var img = mainInfo.match("\\<img src=\\\"(.*?)\\\"");
       img = ( img && img.length > 1 ) ? "<img src='"+img[1]+"'>" : "";
       var rating = mainInfo.match("fileRating.*?em>(.*?)<");
       rating = ( rating && rating.length > 1 ) ? rating[1] : "";
       var name = mainInfo.match("class=\"name.*?\">(.*?)<");
       name = ( name && name.length > 1 ) ? name[1] : "";
       var size = mainInfo.match("fileSize\">(.*?)<");
       size = ( size && size.length > 1 ) ? size[1] : "";
       var time = mainInfo.match("fileTime\">(.*?)<");
       time = ( time && time.length > 1 ) ? time[1] : "";

       result.push({url:url, img:img, rating:rating, name:name, size:size, time:time, data:subdata});
     }
     index++;
    }
    return result;
  }

  request({
    url: searchUrl + term,
    method: "GET",
    headers: {"X-Requested-With": "XMLHttpRequest"}
  }, function(error, response, body) {
    var data = JSON.parse(body.match("var kn = (\\{.*?\\});")[1]);
    var key = body.match("kapp\\(kn\\[\\\"(.*)\\\"")[1];
    var result = decode(data, data[key]);
    safeResponse.end( JSON.stringify(result) );
  });
}

function getLink(lnk)
{
  var safeResponse = currentResponse;
  getDownloadLink(lnk, captchaHelper, function(url)
  {
    safeResponse.end( "{\"url\":\""+url+"\"}" );
  });
}

function captchaHelper(json, onResult)
{
  // json.sound. json.image

  console.log("Cracking captcha: "+json.sound);
  request({
      url : json.sound,
      encoding : "binary"
  }, function(error, response, body) {
    var q = (new Buffer(body, 'binary')).toString('hex');
    q = q.substr(48*2, (body.length-48-4)*2);

    var result = matcher(transcribe(q, {}));
    console.log("Found captcha: "+result);
    onResult(result);
  }); 
}