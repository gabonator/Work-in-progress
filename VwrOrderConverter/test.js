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

fs.readdirSync(normalizedPath).forEach(function(file) 
{
  if (file.indexOf(".out") != -1)
    return;

//  if (file.indexOf("perf") == -1)
//    return;

  var fileIn = path.join(normalizedPath, file);
  var fileOut = fileIn + ".out";

  var dataIn = _toString(fs.readFileSync(fileIn));
  var dataVerify = fs.existsSync(fileOut) ? fs.readFileSync(fileOut).toString() : null;
  var dataOut = converter.convert(dataIn);
  var report = {
    file:file, 
    parser:(dataOut ? dataOut.parser : null), 
    test:"not available",
    messages:dataOut ? dataOut.messages : null};

  if (dataVerify && dataOut)
  {
    report.test = (dataVerify == dataOut.result) ? "OK" : "failed!"
//    fs.writeFileSync(fileOut+"_err", dataOut.result);
  }
  if (!dataVerify && dataOut)
  {
//console.log("saving: " +fileOut+"_");
    fs.writeFileSync(fileOut+"_new", dataOut.result);
  }
  console.log(JSON.stringify(report));
});