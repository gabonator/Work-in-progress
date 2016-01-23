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
var api = require('./engine/api.js');
//var imageCaptcha = require('./captcha/ocr/ocr.js').captchaByImageHash;
var voiceCaptcha = require('./captcha/voicerecognition/voice.js').captchaByVoice;

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

function getLink(lnk)
{
  var safeResponse = currentResponse;
  api.getDownloadLink(lnk, captchaHelper, function(url)
  {
    safeResponse.end( "{\"url\":\""+url+"\"}" );
  });
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

/*
  console.log("Cracking visual captcha: "+json.image);
  request({
      url : json.image,
      encoding : "binary"
  }, function(error, response, body) {

var crypto = require('crypto');
    var md5sum = crypto.createHash('md5');
    md5sum.update(body.substr(body, body.length-16));
    var hash = md5sum.digest('hex');
    console.log("hash: " +hash);

    var result = imageCaptcha(hash);
    console.log("Found captcha: "+result);
    onResult(result);
  }); 
*/
}