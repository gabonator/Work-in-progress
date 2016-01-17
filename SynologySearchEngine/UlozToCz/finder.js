var query = "frankenweenie";


var decoderClass = require('./decoder.js').kapp;
var searchUrl = "http://ulozto.cz/hledej?q=";
var suggestUrl = "http://ulozto.cz/searchSuggest.php?term=";
var request = require("request");

request(suggestUrl + query, function(error, response, body) {
  console.log("Suggestions:");
  console.log(body);
});

request({
  url: searchUrl + query,
  method: "GET",
  headers: {"X-Requested-With": "XMLHttpRequest"}
}, function(error, response, body) {
  var data = JSON.parse(body.match("var kn = (\\{.*?\\});")[1]);
  var key = body.match("kapp\\(kn\\[\\\"(.*)\\\"")[1];
  decode(data, data[key]);
});

function trim(str)
{
  while ( str.length > 1 && str.charCodeAt(str.length-1) == 0 )
    str = str.substr(0, str.length-1);
  return str;
}

function decode(data, key)
{
	var decoder = new decoderClass(key); 

	var q = "Found items:\n", index = 0, name, img;
  for (var i in data)
  {
   if ( index % 7 == 0 )
     name = trim(decoder.decrypt(data[i]));

   if ( index % 7 == 6 )
   {
     var html = decoder.decrypt(data[i]);
     img = html.match("\\<img src=\\\"(.*?)\\\"");
     img = ( img && img.length > 1 ) ? "<img src='"+img[1]+"'>" : "";
   }
   
   if ( index % 7 == 6 )
     q += name + img + "<br>\n";

   index++;
  }

  console.log(q);
}
