var encoding = require("encoding");

function processCsv(xmlData)
{
  var lines = xmlData.split("\r\n");
  if (lines.length <= 1)
    return false;

  var aux = [];
  for (var i in lines)
  {
    var line = lines[i];
    if (line == "")
      continue;
    var tokens = line.split("|");

    if (tokens.length < 10)
      return false;

    aux.push(tokens);
  }
  return aux;
}

function processTab(xmlData)
{
  if (xmlData.charCodeAt(0) == 0xff && xmlData.charCodeAt(1) == 0xfe)
  {
    xmlData = encoding.convert(xmlData, "UTF8", "UTF16").toString();
  }

  var lines = xmlData.split("\r\n");
  if (lines.length <= 1)
    return false;

  var aux = [];
  for (var i in lines)
  {
    var line = lines[i];

    if (line == "")
      continue;
    var tokens = line.split("\x09");

    if (tokens.length < 5)
      return false;

    aux.push(tokens);
  }
  return aux;
}

function process(xmlData)
{
  var csv = processCsv(xmlData);
  if (csv)
    return csv;

  var tab = processTab(xmlData);
  if (tab)
    return tab;
}

module.exports = {parse:process};