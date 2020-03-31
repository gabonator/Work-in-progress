var xml2json = require('xml2json');
var encoding = require("encoding");

function processXml(xmlData)
{
  var lines = xmlData.split("\r\n");
  xmlData = "";
  for (var i in lines)
  {
    var line = lines[i];
    if (line.length > 74)
      return false;
    if (line.length == 74)
      xmlData += line;
    else
      xmlData += line + " ";
  }
  // TODO: autoiso
  xmlData = encoding.convert(xmlData, "UTF-8", "1250").toString();

  try 
  {
    json = JSON.parse(xml2json.toJson(xmlData));
  }
  catch (e)
  {
  }
  return json;
}

module.exports = {parse:processXml, id:"mailxml"};