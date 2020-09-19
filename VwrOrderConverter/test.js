var fs = require("fs");
var path = require("path");
var normalizedPath = path.join(__dirname, "test");
var converter = require("./converter");

function _toString(buffer)
{
  var textIn = "";
  for (var i=0; i<buffer.length; i++)
    textIn += String.fromCharCode(buffer[i]);
  return textIn;
}

var files = [];

fs.readdirSync(normalizedPath).forEach(function(file) 
{
  if (file.charAt(0) == "." || file.indexOf(".out") != -1)
    return;

//  if (file.indexOf("perf_") == -1)
//    return;
  if (file.substr(0,4) == "2020")
    return;
  if (file.indexOf(".pdf") == -1)
    return;

//  if (file.indexOf("3027") == -1)
//    return;

  var fileIn = path.join(normalizedPath, file);
  var fileOut = fileIn + ".out";
  files.push({file:file, fileIn:fileIn, fileOut:fileOut});
});

//console.log(files.map(f=>f.file));

function process(file, fileIn, fileOut)
{
console.log(file);
  var bufferIn = fs.readFileSync(fileIn);
  var dataIn = _toString(bufferIn);
  var dataVerify = fs.existsSync(fileOut) ? fs.readFileSync(fileOut).toString() : null;

  return converter.convert(dataIn, bufferIn)
  .then( (dataOut) => 
  {
    return {
      file:file, 
      parser:dataOut.parser + " / " + dataOut.format, 
      test:"not available",
      messages:dataOut.messages,
      items:dataOut.input.items.length,
      result:dataOut.result};
  }) 
  .catch( (r) => 
  {
    return {
      file:file, 
      parser:null, 
      test:"not available",
      messages:null,
      items:0};
  }) 
  .then( report => 
  {
    if (dataVerify && report.result)
    {
      report.test = (dataVerify == report.result) ? "OK" : "failed!"
      if (dataVerify != report.result)
      {
        fs.writeFileSync(fileOut+"_err", report.result);
  //      process.exit();
      }
    }
    if (!dataVerify && report.result)
    {
  //console.log("saving: " +fileOut+"_");
      fs.writeFileSync(fileOut+"_new", report.result);
    }
    delete report.result
    console.log(JSON.stringify(report));
  });
}

function processAll()
{
  if (files.length == 0)
 {
console.log("done");
    return;
}
  var file = files.shift();
  process(file.file, file.fileIn, file.fileOut)
  .then( () =>
  {
    processAll();
  })
  .catch( ()=>
  {
    console.log("cannot convert");
    processAll();
  });

}

processAll();
