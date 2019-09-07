var xml2json = require('xml2json');
//var encoding = require("encoding");

function processXml(xmlData)
{
  // TODO auto iso?
//  xmlData = encoding.convert(xmlData, "UTF-8", "ISO-8859-2").toString();
  if (xmlData.charCodeAt(0) == 0xef && xmlData.charCodeAt(1) == 0xbb && xmlData.charCodeAt(2) == 0xbf)
  {
    xmlData = xmlData.substr(3);
    var buf = Buffer.alloc(xmlData.length);
    for (var i=0; i<xmlData.length; i++)
      buf[i] = xmlData.charCodeAt(i);
    xmlData = buf.toString();
  }

  var json;
  try 
  {
    json = JSON.parse(xml2json.toJson(xmlData));
  }
  catch (e)
  {
  }
//console.log(json);
//require("fs").writeFileSync("out", JSON.stringify(json), "utf-8")
//console.log(JSON.stringify(json));

  return json;
}

module.exports = {parse:processXml};