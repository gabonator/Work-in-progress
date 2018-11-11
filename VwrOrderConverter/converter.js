var par = [require("./parsers/rawxml.js").parse,
           require("./parsers/mailxml.js").parse,
           require("./parsers/csv.js").parse];
var imp = [require("./imports/helago.js").import,
           require("./imports/pharmos.js").import,
           require("./imports/perfect.js").import];
var exp = [require("./exports/csv.js").export];

function convert(data)
{
  var json, input, output;

  if (!par.find(p => json = p(data)))
    return null;

  if (!imp.find(i => input = i(json)))
    return null;

  if (!exp.find(e => output = e(input)))
    return null;

  return {
    input:input, 
    json:json, 
    result:output, 
    messages:input ? input.messages : null, 
    parser:input ? input.id : null
  };
}

module.exports = {convert:convert};