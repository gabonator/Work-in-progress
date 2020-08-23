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

    if (err) {
      handler(false, "");
    } else 
    if (resp.statusCode != 200)
    {
      handler(false, body);
    } else
      handler(true, body);
  });
  var form = req.form();
  form.append('sampleFile', data, {
    filename: 'file.txt',
    contentType: 'text/plain'
  });
}

mailget.setHandler( message => {
  console.log("======");
  console.log(message.fromName);
  console.log(message.fromEmail);
  console.log(message.attachmentName);
  console.log(message.attachmentBody.toString().substr(0,64) + "...");

  if (message.subject.substr(0, 4) != "vwr:")
    return;
  
  service(message.attachmentBody, (ok, resp) =>
  {
    var info = {
        from: 'gtest20171011@gmail.com',
        to: message.fromEmail, 
        subject: 'Re: ' + message.subject
    };

    if (!ok)
    {
      info.text = 'Failed to convert!\n' + resp;
      console.log("Failed to convert");
    } else {
      info.text = 'Conversion ok';
      info.attachments = [{
       filename: message.attachmentName + '.txt',
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
})

mailsend.startSession(credentials, success =>
{
  if (!success)
    throw "TX: error";

  var info = {from: 'gtest20171011@gmail.com', to: 'gabriel@valky.eu', subject: 'VWR daemon started', html: 'Daemon started now'}

  mailsend.sendMail(info, (success, msg) =>
  {
    if (success)
      console.log("TX: Mail send ok! " + msg);
    else
      console.log("TX: Mail send failed!!! " + msg);
  });
  mailget.startSession(credentials, (success) =>
  {
    if (success)
    {
      console.log("RX: Connected and ready!")
    } else
      console.log("RX: Connection failed!")
  });
});


