var par = [require("./parsers/rawxml.js"),
           require("./parsers/mailxml.js"),
           require("./parsers/csv.js"),
           require("./parsers/pdf.js")];
var imp = [require("./imports/helago.js"),
           require("./imports/pharmos.js"),
           require("./imports/perfect.js"),
           require("./imports/bamed.js"),
           require("./imports/spol.js"),
           require("./imports/oncomed.js")];
var exp = [require("./exports/csv.js")];

function findParser(data, binary)
{
  return new Promise((resolve, reject) =>
  {
    var tryParsers = [... par];
    var findParserSub = () =>
    {
      if (tryParsers.length == 0)
      {
        return reject();
      }  
      var parser = tryParsers.shift();
      parser.parse(data, binary)
      .then( (aux) =>
      {
        if (!aux)
          throw "wrong response";
        return resolve({id:parser.id, data:aux});
      })
      .catch( () => {
        findParserSub();
      });

    }
    findParserSub();
  });
}

function convert(data, binary)
{
  var json, input, output;
  var par_id;

  return findParser(data, binary)
  .then(aux => {
    par_id = aux.id;
    json = aux.data;
  })
  .then( () =>
  {

  //  if (!par.find(p => { par_id = p.id; return json = p.parse(data)}))  // async
  //    return null;

    if (!imp.find(i => input = i.import(json)))
      return Promise.reject();

    if (!exp.find(e => output = e.export(input)))
      return Promise.reject();

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
    return Promise.resolve({
      input:input, 
      json:json, 
      result:output, 
      messages:input ? input.messages : null, 
      parser:input ? input.id : null,
      format:par_id ? par_id : null
    });
  });
}

module.exports = {convert:convert};