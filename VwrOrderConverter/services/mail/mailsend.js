'option strict';

module.exports = {startSession:startSession, sendMail:sendMail};

var nodemailer = require('nodemailer');
var mail;

function startSession(credentials, handler)
{
  mail = nodemailer.createTransport({
    service: 'gmail',
    auth: {
      user: credentials.login, 
      pass: credentials.password
    }
  });
  handler(true);
}

function sendMail(mailOptions, handler)
{
  mail.sendMail(mailOptions, function(error, info){
      if (error) {
        handler(false, error);
      } else {
        handler(true, info.response);
      }
  });
}
