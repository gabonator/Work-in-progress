'use strict';
var query = "/xkf17YX8/frankenweenie-2012-1080p-bluray-x264-sparks-mkv";


var request = require("request");
var mainurl = "http://ulozto.cz" + query; 
var captchaurl = "http://ulozto.cz/reloadXapca.php?rnd=" + (new Date).getTime();

var form = {};
var keepCookie = "";
var stdin;

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

function doCaptcha(onFinish)
{
  myRequest(captchaurl, function(data)
  {
    var json = JSON.parse(data);
    var image = json.image;
    form.timestamp = json.timestamp;
    form.hash = json.hash;
    form.salt = json.salt;
    myDownload("http:" + json.image, "captcha.gif");
    onFinish();
  })
}

function requestCaptcha()
{
  console.log("Enter captcha: ");
  
  stdin = process.openStdin();
  stdin.addListener("data", function(d) {
    finishCaptcha(d.toString().trim());
  });
}

function finishCaptcha(code)
{
//  stdin.destroy();
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
    
    myDownload("http:"+json.new_captcha_data.image, "captcha.gif");
    requestCaptcha();
  }

  if ( json.status == "ok" )
  {
    console.log("\n\nGot LINK !!!!\n" + json.url)
  }
}

doMainRequest(function()
{
  doCaptcha(requestCaptcha);
});
