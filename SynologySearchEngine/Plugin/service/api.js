'option strict';

module.exports = {getDownloadLink:getDownloadLink, getSuggestions:getSuggestions, getSearchResults:getSearchResults};

var request = require("request");

// download link

var mainurl;
var captchaurl = "https://ulozto.cz/reloadXapca.php?rnd=";
var form = {};
var keepCookie = "";
var onSuccess;
var processCaptcha;

var currentRequest = "";
var lastRequest = "";
var lastResponse = "";

function getDownloadLink(lnk, captcha, handler)
{
  if ( lnk == lastRequest )
  {
    handler(lastResponse);
    return;
  }

  keepCookie = ""; // TODO!!!
  currentRequest = lnk;
  onSuccess = handler;
  processCaptcha = captcha;
  mainurl = "https://ulozto.cz" + lnk;

  doMainRequest(function()
  {
    doCaptcha();
  });
}

function mySpawn(command, args, handler)
{
  var cmdline = command;
  for (var i = 0; i < args.length; i++)
  {
    if ( args[i].indexOf(' ') != -1 || args[i].indexOf('?') != -1 || args[i].indexOf('&') != -1 )
      cmdline += " \"" + args[i] + "\"";
    else
      cmdline += " " + args[i];
  }

  console.log("spawn: " + cmdline);

  const spawn = require('child_process').spawn;
  const proc = spawn('curl', args);

  var response = "";

  proc.stdout.on('data', function(data) {
    response += data;
  });

  proc.stderr.on('data', function (data) {
    console.log('stderr: ' + data);
  });

  proc.on('close', function(code) {
    handler(response);
  });

  return proc;
}

function myDownload(url, filename)
{
  request({url:url, encoding:"binary"}, function(error, response, body) {
    var fs = require('fs');
    fs.writeFile(filename, body, "binary");
  });
}

function myRequest(url, handler, data)
{
  var args = [url, "-s", "-D", "-"];
  if ( keepCookie != "" )
  {
    args.push("-H");
    args.push("Cookie: "+keepCookie+"; uloztoid="+form.cid);
    args.push("-H");
    args.push("X-Requested-With: XMLHttpRequest");
  }

  if ( typeof(data) != "undefined" )
  {
    var q = "";
    for ( var i in form )
    {
      if ( q != "" ) q += "&"
      q += i + "="+ encodeURIComponent(form[i]);
    }
    args.push("--data");
    args.push(q);
  }

  mySpawn('curl', args, handler);
}

function doMainRequest(onFinish)
{
  var getvar = function (html, key)
  {
    var regex = "name=\""+key+"\".*?value=\"(.*?)\"";
    var result = html.match(regex);
    if (result && result.length > 1)
      return result[1] + "";
    return "?";
  }

  //console.log("*********DOMAINREQUEST***********");
  myRequest(mainurl, function(body) {

    body = body.split("\n").join("");

    var keepCookieMatch = body.match("(ULOSESSID=.*?);");
    if ( !keepCookieMatch || keepCookieMatch.length != 2 )
    {
      console.log("ERROR: ULOSESSID not found: <<<"+body+">>>");
      return;
    }
    keepCookie = keepCookieMatch[1];

    var formhtmlMatch = body.match("id=\"frm-downloadDialog-freeDownloadForm\"(.*)</form>");
    if ( !formhtmlMatch || formhtmlMatch.length != 2 )
    {
      console.log("ERROR: FORM DATA not found: <<<"+body+">>>");
      return;
    }

    var formhtml = formhtmlMatch[1];

    form._token_ = getvar(formhtml, "_token_");
    form.ts = getvar(formhtml, "ts");
    form.cid = getvar(formhtml, "cid");
    form.adi = getvar(formhtml, "adi");
    form.sign_a = getvar(formhtml, "sign_a");
    form.sign = getvar(formhtml, "sign");
    form.captcha_type = "xapca";
    form.do = "downloadDialog-freeDownloadForm-submit";

    onFinish();
  })
}

function doCaptcha()
{
  //console.log("*********DOCAPTCHA***********");

  myRequest(captchaurl + (new Date).getTime(), function(data)
  {
    data = data.substr(data.indexOf("\r\n\r\n")+4);
    var json = JSON.parse(data);
    var image = json.image;
    form.timestamp = json.timestamp;
    form.hash = json.hash;
    form.salt = json.salt;
    processCaptcha({image:"http:"+json.image, sound:"http:"+json.sound}, tryCaptcha);
  })
}

function tryCaptcha(code)
{
  form.captcha_value = code;
  requestDownload(processResponse);
}

function requestDownload(onResponse)
{
  //console.log("*********REQUESTDOWNLOAD***********");

  myRequest(mainurl, function(data)
  {
    data = data.substr(data.indexOf("\r\n\r\n")+4);
    onResponse(data);
  }, form);
}

function processResponse(data)
{
  var json = JSON.parse(data);
  //console.log("Got response status:"+json.status);

  if ( json.status == "error" )
  {
    console.log(json.errors);

    form.ts = json.new_form_values.ts;
    form.cid = json.new_form_values.cid;
    form.sign = json.new_form_values.sign;
    form._token_ = json.new_form_values._token_;

    form.hash = json.new_form_values.xapca_hash;
    form.salt = json.new_form_values.xapca_salt;
    form.timestamp = json.new_form_values.xapca_timestamp;

    processCaptcha({image:"http:"+json.new_captcha_data.image, sound:"http:"+json.new_captcha_data.sound}, tryCaptcha);
  }

  if ( json.status == "ok" )
  {
    lastRequest = currentRequest;
    lastResponse = json.url;
    onSuccess(json.url);
  }
}

// suggestions
function getSuggestions(term, onResponse)
{
  var suggestUrl = "https://ulozto.cz/searchSuggest.php?term=" + escape(term);

  request(suggestUrl, function(error, response, body) {
    onResponse(body);
  });
}

// search result
var decoderClass = require('./blowfish.js').blowfish;

function getSearchResults(term, onResponse)
{
  var searchUrl = "https://ulozto.cz/hledej?q=" + escape(term);

  var trim = function (str)
  {
    while ( str.length > 1 && str.charCodeAt(str.length-1) == 0 )
      str = str.substr(0, str.length-1);
    return new Buffer(str, "binary").toString("utf8");
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
    url: searchUrl,
    method: "GET",
    headers: {"X-Requested-With": "XMLHttpRequest"}
  }, function(error, response, body) {
    var data = JSON.parse(body.match("var kn = (\\{.*?\\});")[1]);
    var key = body.match("kapp\\(kn\\[\\\"(.*)\\\"")[1];
    var result = decode(data, data[key]);
    onResponse(result);
  });
}
