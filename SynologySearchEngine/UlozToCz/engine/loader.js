'option strict';

module.exports = {getDownloadLink:getDownloadLink};

var request = require("request");
var mainurl;
var captchaurl = "http://ulozto.cz/reloadXapca.php?rnd=" + (new Date).getTime();
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
  myRequest(captchaurl, function(data)
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
