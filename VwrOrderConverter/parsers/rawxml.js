var xml2json = require('xml2json');
var encoding = require("encoding");

function processXml(xmlData)
{
  // TODO auto iso?
  xmlData = encoding.convert(xmlData, "UTF-8", "ISO-8859-2").toString();
  var json;

  try 
  {
    json = JSON.parse(xml2json.toJson(xmlData));
  }
  catch (e)
  {
  }

  return json;
}

module.exports = {parse:processXml};