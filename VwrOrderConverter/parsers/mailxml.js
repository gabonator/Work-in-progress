var xml2json = require('xml2json');
var encoding = require("encoding");

function processXml(xmlData)
{
  return new Promise((resolve, reject) =>
  {
    if (xmlData.substr(0, 4) == "%PDF")
      return reject();

    var lines = xmlData.split("\r\n");
    xmlData = "";
    for (var i in lines)
    {
      var line = lines[i];
      if (line.length > 74)
        return reject();
      if (line.length == 74)
        xmlData += line;
      else
        xmlData += line + " ";
    }

    // TODO: autoiso
    xmlData = encoding.convert(xmlData, "UTF-8", "1250").toString();

    var json;
    try 
    {
      json = JSON.parse(xml2json.toJson(xmlData));
    }
    catch (e)
    {
      return reject();
    }
    return resolve(json);
  });
}

module.exports = {parse:processXml, id:"mailxml"};