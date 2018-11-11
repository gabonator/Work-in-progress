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

module.exports = {parse:processCsv};