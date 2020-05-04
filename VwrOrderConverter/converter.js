var par = [require("./parsers/rawxml.js"),
           require("./parsers/mailxml.js"),
           require("./parsers/csv.js")];
var imp = [require("./imports/helago.js"),
           require("./imports/pharmos.js"),
           require("./imports/perfect.js"),
           require("./imports/bamed.js"),
           require("./imports/spol.js")];
var exp = [require("./exports/csv.js")];

function convert(data)
{
  var json, input, output;
  var par_id;

  if (!par.find(p => { par_id = p.id; return json = p.parse(data)}))
    return null;

  if (!imp.find(i => input = i.import(json)))
    return null;

  if (!exp.find(e => output = e.export(input)))
    return null;

  if (input.errors && input.errors.length)
  {       
    console.log("========= error report begin ========");
    console.log("Input format: " + par_id + " Parser: " + input.id);
    console.log("");
    for (var i in input.errors)
      console.log(input.errors[i]);
    console.log("========= error report end ========");
    throw "parsing error";
  }

  return {
    input:input, 
    json:json, 
    result:output, 
    messages:input ? input.messages : null, 
    parser:input ? input.id : null,
    format:par_id ? par_id : null
  };
}

module.exports = {convert:convert};