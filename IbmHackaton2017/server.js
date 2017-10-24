var express = require("express");
var app = express();
var bodyParser = require('body-parser')
var happy = require("./happyservice.js");
var logger = require("./logger.js");

var port = process.env.PORT || 8888;

app.use(bodyParser());

var TextToSpeechV1 = require('watson-developer-cloud/text-to-speech/v1');

var text_to_speech = new TextToSpeechV1({
  username: '69f584e2-a92d-46f8-a558-5f54f0c08042',
  password: '1EASEprEfebZ'
});

app.get("/", function(req, res) {
  logger.hostname(req.connection.remoteAddress, (hostname) => logger.mylog({visitor: hostname, ip:req.connection.remoteAddress, url:"index"}));
  res.sendFile(__dirname + "/index.html")
});

app.get("/log", function(req, res) {
  res.redirect("/logs/" + logger.datestamp()+".txt");
});

app.get('/speech', function (req, res) {
  var query = decodeURIComponent(req._parsedUrl.query);

  var params = {
    text: query,
    voice: 'en-US_AllisonVoice', // Optional voice
    accept: 'audio/wav'
  };

  text_to_speech.synthesize(params).pipe(res);  // res
});

app.get(/^(.+)$/, function(req, res){ 
  res.sendFile(__dirname + req.params[0]); 
});


app.listen(port, function() {
  console.log("running at localhost:" + port);
});

app.post('/connect', function(req, res){
  logger.hostname(req.connection.remoteAddress, (hostname) => logger.mylog({visitor: hostname, ip:req.connection.remoteAddress, user:req.body.name, url:"connect"}));

  var obj = {};
  console.log('connect: ' + JSON.stringify(req.body));

  happy.authenticate(req.body.name, req.body.password, req.body.server, function(success)
  {
    if (success)
    {
      if (happy.getSession(req.body.name))
        res.send(JSON.stringify({success:true, enabled:true}));
      else
        res.send(JSON.stringify({success:true, enabled:false}));
    } else
      res.send(JSON.stringify({success:false}));
  });
});

app.post('/enable', function(req, res){
  logger.hostname(req.connection.remoteAddress, (hostname) => logger.mylog({visitor: hostname, ip:req.connection.remoteAddress, user:req.body.name, url:"enable"}));

  var obj = {};
  console.log('enable: ' + JSON.stringify(req.body));

  happy.authenticate(req.body.name, req.body.password, req.body.server, function(success)
  {
    if (success)
    {
      if (happy.startSession(req.body.name, req.body.password, req.body.server, function(success)
      {
        res.send(JSON.stringify({success:success}));
      }));
    } else
      res.send(JSON.stringify({success:false}));
  });
});

app.post('/disable', function(req, res){
  var obj = {};
  console.log('disable: ' + JSON.stringify(req.body));

  happy.authenticate(req.body.name, req.body.password, req.body.server, function(success)
  {
    if (success)
    {
      if (happy.stopSession(req.body.name, req.body.password, req.body.server))
        res.send(JSON.stringify({success:true}));
      else
        res.send(JSON.stringify({success:false}));
    } else
      res.send(JSON.stringify({success:false}));
  });
});