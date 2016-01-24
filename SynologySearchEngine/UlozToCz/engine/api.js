'option strict';

module.exports = {getDownloadLink:getDownloadLink, getSuggestions:getSuggestions, getSearchResults:getSearchResults};

var request = require("request");

// download link

var mainurl;
var captchaurl = "http://ulozto.cz/reloadXapca.php?rnd=";
var form = {};
var keepCookie = "";
var onSuccess;
var processCaptcha;

function getDownloadLink(lnk, captcha, handler)
{
  onSuccess = handler;
  processCaptcha = captcha;
  mainurl = "http://ulozto.cz" + lnk; 

  doMainRequest(function()
  {
    doCaptcha();
  });
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
  var syscall = 'curl "'+url+'" -H "Cookie: '+keepCookie+'; uloztoid='+form.cid+'" -H "X-Requested-With: XMLHttpRequest"';

  if ( typeof(data) != "undefined" )
  {
    var q = "";
    for ( var i in form )
    {
      if ( q != "" ) q += "&"
      q += i + "="+ encodeURIComponent(form[i]);
    }

    q = q.split('%').join('"%"');
    q = '--data "'+q+'"'
    syscall += " " + q;
  }

  var exec = require('child_process').exec;
                                            
  exec(syscall, function(error, stdout, stderr) {
    handler(stdout);
  });
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

  request(mainurl, function(error, response, body) {
    var cookies = response.headers["set-cookie"].join(";");
    keepCookie = cookies.match("(ULOSESSID=.*?);")[1];

    body = body.split("\n").join("");
    var formhtml = body.match("id=\"frm-downloadDialog-freeDownloadForm\"(.*)</form>")[1];

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
  myRequest(captchaurl + (new Date).getTime(), function(data)
  {
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
  myRequest(mainurl, function(data)
  {
    onResponse(data);
  }, form);
}

function processResponse(data)
{
  var json = JSON.parse(data);

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
    onSuccess(json.url);
  }
}

// suggestions
function getSuggestions(term, onResponse)
{
  var suggestUrl = "http://ulozto.cz/searchSuggest.php?term=" + escape(term);

  request(suggestUrl, function(error, response, body) {
    onResponse(body);
  });
}

// search result
var decoderClass = require('./blowfish.js').blowfish;

function getSearchResults(term, onResponse)
{
  var searchUrl = "http://ulozto.cz/hledej?q=" + escape(term);

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

