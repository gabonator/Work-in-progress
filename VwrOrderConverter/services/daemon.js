process.title = "vierka mailer";

var mailget = require("./mail/mailget.js");
var mailsend = require("./mail/mailsend.js");
var credentials = require("./private.js").credentials;
var request = require("request");

// https://stackoverflow.com/questions/20337040/getting-error-while-sending-email-through-gmail-smtp-please-log-in-via-your-w
// https://accounts.google.com/DisplayUnlockCaptcha


function service(data, handler)
{
  var url = credentials.serviceurl;
  var req = request.post(url, function (err, resp, body) {
    var info = resp.headers["gabo-service"];

    if (err) {
      console.log(data.toString().substr(0, 16) + " -> " + body.substr(0,16) + ": Conv err");
      handler(false, "");
    } else 
    if (resp.statusCode != 200)
    {
      console.log(data.toString().substr(0, 16) + " -> " + body.substr(0,16) + ": Conv unsupported");
      handler(false, body);
    } else
      console.log(data.toString().substr(0, 16) + " -> " + body.substr(0,16) + ": Conv ok ("+info+")");

    handler(true, body, info);
  });
  var form = req.form();
  form.append('file', data, {
    filename: 'file.txt',
    contentType: 'text/plain'
  });
}

mailget.setHandler( message => {
  if (!message.attachmentName)
    message.attachmentName = "unnamed";

  console.log("======");
  console.log(message.fromName + " <" + message.fromEmail + ">");
  for (var i=0; i<message.attachments.length; i++) 
  {
    console.log(i + ": " + message.attachments[i].name);
    console.log(i + ": " + message.attachments[i].body.toString().substr(0,64) + "...");
  }

  if (message.attachments.length < 1 || message.subject.substr(0, 4) != "vwr:")
    return;
  
  var attachments = [];

  for (var i=0; i<message.attachments.length; i++) 
  {
    var _i = i;
    attachments.push(new Promise((resolve, reject) => {
      var name = message.attachments[_i].name;
      var body = message.attachments[_i].body;

      service(body, (ok, resp, info) =>
      {
        resolve({status:ok, resp:resp, name:name, info:info});
      });

    }));
  }

  Promise.all(attachments).then(attachments =>
  {
    var info = {
        from: 'Converter service <gtest20171011@gmail.com>',
        to: message.fromEmail, 
        subject: 'Re: ' + message.subject,
        attachments: []
    };

    var resp = "Conversion report:\n\n";

    for (var i in attachments)
    {
      if (attachments[i].status)
      {
        resp += "File: " + attachments[i].name + " Result: Ok. ";
        if (attachments[i].info) 
          resp += " (" + attachments[i].info + ")";
        resp += "\n";

        info.attachments.push({                       
          filename: attachments[i].name + '.txt',
          content: attachments[i].resp
        });  
      }
      else
      {
        resp += "File: " + attachments[i].name + " Result: Failed.\n"
      }
    }

    resp += "\n\n";

    info.text = resp;

    mailsend.sendMail(info, (success, msg) =>
    {
      if (success)
        console.log("TX: Mail send ok! " + msg);
      else
        console.log("TX: Mail send failed!!! " + msg);
    });

  });
/*
  service(message.attachments[0].body, (ok, resp) =>
  {
    var info = {
        from: 'Converter service <gtest20171011@gmail.com>',
        to: message.fromEmail, 
        subject: 'Re: ' + message.subject
    };

    if (!ok)
    {
      info.text = 'Failed to convert!\n' + resp;
      console.log("Failed to convert");
    } else {
      info.text = 'Conversion ok\n';
      info.attachments = [{
       filename: message.attachments[0].name + '.txt',
       content: resp
      }]
    }

    mailsend.sendMail(info, (success, msg) =>
    {
      if (success)
        console.log("TX: Mail send ok! " + msg);
      else
        console.log("TX: Mail send failed!!! " + msg);
    });

  });
*/
})

function _startSession()
{
  mailget.startSession(credentials, (success) =>
  {
    if (success)
    {
      console.log("RX: Connected and ready!")
    } else
      console.log("RX: Connection failed!")
  });
  setTimeout(() =>
  {
    console.log("RX: Forcing close after 100 minutes")
    mailget.stopSession(credentials.login);
    _startSession();
  }, 1000*60*100);
}

mailsend.startSession(credentials, success =>
{
  if (!success)
    throw "TX: error";

  var info = {from: 'Converter service <gtest20171011@gmail.com>', to: 'gabriel@valky.eu', subject: 'VWR daemon started', html: 'Daemon started now'}

  mailsend.sendMail(info, (success, msg) =>
  {
    if (success)
      console.log("TX: Mail send ok! " + msg);
    else
      console.log("TX: Mail send failed!!! " + msg);
  });

  _startSession();
});


