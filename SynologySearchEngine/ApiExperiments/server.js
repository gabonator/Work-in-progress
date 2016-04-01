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

http.createServer(function (_request, _response) {
  var parsedUrl = url.parse(_request.url);
  var uri = parsedUrl.pathname;
  var query = parsedUrl.query;
  var full = parsedUrl.href;

  if ( full.indexOf("/webapi/") == 0 )
  {
    request({url:"http://localhost:5000" + full}, function(error, response, body) {
      _response.end(body);
    });
  } else
  if ( !query )
  {
    if ( uri == "/" )
      uri = "/index.html";

    var file = webbase + uri;
    fs.exists( file, function(exists)
    { 
      if(!exists) 
      {
        _response.writeHead(404, {"Content-Type": "text/plain"});
        _response.write("404 Not Found\n");
        _response.end();
        return;
      }

      if ( file.substr(-5) == ".html" )
        _response.writeHead(200, {'Content-Type': 'text/html'}); 
      else
        _response.writeHead(200, {'Content-Type': 'text/plain'}); 

      _response.end(fs.readFileSync(file));
    });
  } else
  {
    query = unescape(query);
    console.log("query='" +query+"'");
    currentResponse = _response;
    eval(query);
    currentResponse = null;
  }
}).listen(8034);


// search api
var api = require('./api.js');
var voiceCaptcha = require('./voice.js').captchaByVoice;

function getSuggestion(term)
{
  var safeResponse = currentResponse;
  api.getSuggestions(term, function(data)
  { 
    safeResponse.end(data);
  });
}

function doSearch(term)
{
  var safeResponse = currentResponse;
  api.getSearchResults(term, function(json)
  {
    safeResponse.end( JSON.stringify(json) );
  });
}

function getDownload(lnk)
{
  lnk = lnk.replace("http://ulozto.cz", "");
  lnk = lnk.replace("http://ulozto.sk", "");

  var safeResponse = currentResponse;
  api.getDownloadLink(lnk, captchaHelper, function(url)
  { 
    var ind = url.lastIndexOf("-");
    if ( ind != -1 )
      url = url.substr(0, ind) + '.' + url.substr(ind+1);

    safeResponse.end(url);
  });
}

function getLink(lnk)
{
  var safeResponse = currentResponse;
  api.getDownloadLink(lnk, captchaHelper, function(url)
  { 
    var ind = url.lastIndexOf("-");
    if ( ind != -1 )
      url = url.substr(0, ind) + '.' + url.substr(ind+1);

    safeResponse.end( "{\"url\":\""+url+"\"}" );
  });
}

function getVlcLink(url)
{
  var name = url.match(".*/(.*?)\\?")[1]
  var ind = name.lastIndexOf("-");
  if ( ind != -1 )
    name = name.substr(0, ind) + '.' + name.substr(ind+1);

  currentResponse.setHeader('Content-disposition', 'attachment; filename=' + name + ".m3u");
  currentResponse.setHeader('Content-type', "text/plain");
  currentResponse.end(
    '#EXTM3U\n' +
    '#EXTINF:-1,' + name + '\n' +
    url
  );
}

function getLocalVlcLink(url)
{
  var name = url.match(".*/(.*?)$")[1]

  url = url.replace("http://", "\\\\");
  url = url.replace(new RegExp("/", 'g'), '\\');

  var ind = name.lastIndexOf("-");
  if ( ind != -1 )
    name = name.substr(0, ind) + '.' + name.substr(ind+1);

  currentResponse.setHeader('Content-disposition', 'attachment; filename=' + name + ".m3u");
  currentResponse.setHeader('Content-type', "text/plain");
  currentResponse.end(
    '#EXTM3U\n' +
    '#EXTINF:-1,' + name + '\n' +
    url
  );
}

function captchaHelper(json, onResult)
{
  console.log("Cracking voice captcha: "+json.sound);
  request({
      url : json.sound,
      encoding : "binary"
  }, function(error, response, body) {
    var result = voiceCaptcha(body);
    console.log("Found captcha: "+result);
    onResult(result);
  }); 
}
