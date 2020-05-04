// npm install express
// npm install express-fileupload
// npm install xml2json
// npm install encoding

process.title = "vierka vwr";

const express = require('express');
const fileUpload = require('express-fileupload');
const app = express();

var converter = require("../converter.js");

app.use(fileUpload());

function _toString(buffer)
{
  var textIn = "";
  for (var i=0; i<buffer.length; i++)
    textIn += String.fromCharCode(buffer[i]);
  return textIn;
}

app.post('/', function(req, res) 
{
  if (!req.files)
    return res.status(400).send('No files were uploaded.');

  let sampleFile = req.files.sampleFile;
  var fileName = sampleFile.name.replace(".xml", ".txt");
  if (fileName.indexOf(".txt") == -1)
    fileName += ".txt";
  var buffer = sampleFile.data;
  var textIn = _toString(buffer);
  var out = converter.convert(textIn);
  var textXml = JSON.stringify(out.json);
  var textOut = out.result;
  var newBuffer = new Buffer(textOut, "UTF-8");
                       
  console.log(textOut);

  if(req.body && typeof(req.body.debug) != "undefined" && req.body.debug == "on")
  {
    res.end(`<html>
<head>
  <meta charset="UTF-8">
    <link rel="stylesheet" type="text/css" href="http://warfares.github.io/pretty-json/css/pretty-json.css"/>
    <script src="http://warfares.github.io/pretty-json/libs/jquery-1.11.1.min.js"></script>
    <script src="http://warfares.github.io/pretty-json/libs/underscore-min.js"></script>
    <script src="http://warfares.github.io/pretty-json/libs/backbone-min.js"></script>
    <script src="http://warfares.github.io/pretty-json/pretty-json-min.js"></script>
</head>

<pre id="out">${textOut}</pre>
<span id="json">${textXml}</span>
<script>new PrettyJSON.view.Node({ el:document.getElementById("json"), 
  data:JSON.parse(document.getElementById("json").innerHTML)}).expandAll()</script>
</html>`);
  } else
  {
    res.writeHead(200, {
        'Content-Type': "text/plain",
        'Content-disposition': 'attachment;filename*=UTF-8\'\''+encodeURIComponent(fileName),
        'Content-Length': newBuffer.length
    });
    res.end(newBuffer);
  }
});

app.get("/", function(req, res) {
  res.end(`<html>
    <body>
      <h1>ver200504</h1><br>Skonvertuj xml to csv
      <form ref='uploadForm' 
        id='uploadForm' 
        method='post' 
        encType="multipart/form-data">
          <input type="file" name="sampleFile" />
          <input type='submit' value='Upload!' />
          <input type='checkbox' name="debug"/>debug
      </form>     
    </body>
  </html>`);
});

app.listen(8082, function() {
  console.log("Server started at localhost:8082");
});
