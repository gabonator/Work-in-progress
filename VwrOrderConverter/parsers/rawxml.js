var xml2json = require('xml2json');
//var encoding = require("encoding");

function processXml(xmlData)
{
  if (xmlData.substr(0, 4) == "%PDF")
    return Promise.reject();

  return new Promise((resolve, reject) =>
  {
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
      return reject();
    }

    return resolve(json);
  });
}

module.exports = {parse:processXml, id:"rawxml"};