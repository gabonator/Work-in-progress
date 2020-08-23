//'option strict';

module.exports = {authenticate:authenticate, getSession:getSession, stopSession:stopSession, startSession:startSession, setHandler:setHandler};

var inbox = require("inbox"),
    util = require("util");
var Promise = require('bluebird');
var Stream = require("stream").Stream;
var concat = require('concat-stream');
var quotedPrintable = require('quoted-printable');

var sessions = [];
var mylog = console.log
var messageHandler;

inbox.IMAPClient.prototype.createMessageStream = function(uid, section){
    var stream = new Stream();

    uid = Number(uid) || 0;
    section = section || "";

    if(!uid){
        process.nextTick(this.emit.bind(this, new Error("Invalid UID value")));
        return;
    }

    if(this._currentState != this.states.SELECTED){
        process.nextTick(this.emit.bind(this, new Error("No inbox selected")));
        return;
    }

    this._send("UID FETCH " + uid + " BODY.PEEK[" + section + "]", (function(status){
        this._collectMailList = false;
        this._literalStreaming = false;

        if(!this._mailList.length){
            if(status == "OK"){
                stream.emit("error", new Error("Selected message not found: "+uid+"; "+this.port+"; "+this.host+"; "+JSON.stringify(this._selectedMailbox)));
            }else{
                stream.emit("error", new Error("Error fetching message: "+uid+"; "+this.port+"; "+this.host+"; "+JSON.stringify(this._selectedMailbox)));
            }
        }

        this._messageStream.emit("end");
        this._messageStream.removeAllListeners();

        this._messageStream = null;

    }).bind(this),
    (function(){
        this._collectMailList = true;
        this._literalStreaming = true;
        this._mailList = [];
        this._messageStream = stream;
    }).bind(this));

    return stream;
};

function findMailbox(arr, id)
{
    return arr.find(item => item.indexOf("/" + id) != -1);
//    return arr.find(function(item) { return item.indexOf("/" + id) != -1 });
}

function recursiveScan(obj, attachments)
{
    if (obj.hasOwnProperty("part"))
        return [obj];
    
    var joined = [];
    for (var i in obj)
        if (typeof(obj[i]) == "object")
            joined = joined.concat(recursiveScan(obj[i]));
            
    return joined;
}

function findTextAttachment(m)
{
    var attachments = recursiveScan(m.bodystructure);    


    for (var i in attachments)
    {
      console.log("{{{{{{{");
      console.log(attachments[i]);
      console.log("}}}}}}}");
    }
/*
    {
      part: '1',
      type: 'text/plain',
      parameters: { charset: 'us-ascii' },
      encoding: '7bit',
      size: 8,
      lines: 1
    }
    {
      part: '2',
      type: 'text/plain',
      parameters: { name: 'samplemessage.txt', 'x-unix-mode': '0644' },
      encoding: '7bit',
      size: 15,
      lines: 1,
      disposition: [ { type: 'attachment', filename: 'samplemessage.txt' } ]
    }
*/
    return attachments.find(att => att.disposition && 
      att.disposition.length > 0 && 
      att.disposition[0].type == "attachment");
}

function decodeMessageData(buf, encoding)
{
//console.log("decoding: " + encoding);

    if (encoding == "7bit")
    {
        return buf;
    }

    if (encoding == "base64")
    {
      return new Buffer(buf, 'base64');
    }

    if (encoding == "quoted-printable")
    {
      var quo = quotedPrintable.decode(buf.toString());
      return new Buffer(quo, 'ascii');
    }

    throw "unknown encoding " + encoding;
    return new Buffer();
}

function proConnect(config)
{
    return new Promise(function(resolve, reject) {
        var client = inbox.createConnection(false, config.server, {
            secureConnection: true,
            auth:{
                user: config.user,
                pass: config.pass
            },
            debug: false
        });
        
        client.connect();
        client.on("connect", function(){
            client.email = config.user;
            console.log('client connected: '+this.email);
            resolve(client);
        });
        
        client.on('error', function (err){
            console.log('Error');
            console.log(err);
            reject(err);
        });

        client.on('close', function (err){
            console.log('client closed: '+this.email);
        });
    });
}

function proGetMailboxes(client)
{
    return new Promise(function(resolve, reject) {        
        client.listMailboxes(function(error, mailboxes){
            var all = [];
            var requests = 0, handled = 0;
            for(var i=0, len = mailboxes.length; i<len; i++){
                all.push(mailboxes[i].path);
                
                if(mailboxes[i].hasChildren){
                    requests++;
                    mailboxes[i].listChildren(function(error, children){
                        for (var j in children)
                            all.push(children[j].path);
                            
                        if (++handled == requests)
                            resolve([client, all]);
                    });
                }
            }
            if (requests == 0)
                reject();
        });    
        
    });
}

function proOpenMailbox(client, name)
{
    return new Promise(function(resolve, reject) {        
        client.openMailbox(name, {
            readOnly: true
        }, function(error, mailbox) {
            if (error)
                reject(error);
            else
                resolve([client, mailbox]);
        });
    });    
}

function proCreateMailbox(client, id, arg)
{
    return new Promise(function(resolve, reject) {        
        client.listMailboxes(function(error, mailboxes){
            mailboxes[0].createChild(id, function(error, mailbox) {
                if (error)                
                {
                    console.log("Error creating mailbox");
                    console.log(e);
                    reject(error);
                    return;
                }
                resolve([client, arg]);
            });
        });
    });

}

function authenticate(email, password, server, handler)
{
  var options = {
  	server: server,
  	secure: true,
  	user: email,
  	pass: password
  };
  proConnect(options)
  .then(function(client) {
      handler(true);
      client.close();
  })
  .catch(function(error){
     console.log("Rejection: " + error);     
     handler(false);
  });
}

function startSession(credentials, handler)
{
  mylog({login_email:credentials.login, status:"start session"});
  proConnect({
  	server: credentials.server,
  	secure: true,
  	user: credentials.login,
  	pass: credentials.password
  })
  .then(function(client) {
      mylog({login_email:credentials.login, login_server:credentials.server, status:"connected"});
      console.log("Connected");
      return proGetMailboxes(client);    
  })
  .then(function(client) {
      return proOpenMailbox(client[0], "INBOX");
  })
  .spread(function(client, mailbox) {

    console.log(client.email + ": Waiting for email...");
    sessions.push(client);    
    handler(true);

    client.on("new", function(message) {
      var textAttachment = findTextAttachment(message);
      if (!textAttachment) {
        mylog({error:"No text attachment"});
      	console.log("Cant find text attachment!");
      	return;
      }

      var readStream = client.createMessageStream(message.UID, textAttachment.part);
      readStream.pipe(concat(function(data) {
      	var body = decodeMessageData(data, textAttachment.encoding);
      	var filename = textAttachment.disposition[0].filename
        HandleMessage(client, message, body, filename);

      }), {
      	end: true
      });
    });
  })
  .catch(function(error){
     mylog({login_email:credentials.login, login_server:credentials.server, status:"failed"});
     console.log("Rejection: " + error);     
     handler(false);
  });
}

function HandleMessage(client, message, body, filename)
{
  if (!messageHandler)
  {
    console.log("------------------ ");
    console.log(client.email + ": New message title: " + message.title + 
      " from: " + message.from.name + " / " + message.from.address + " attachment: " + filename);
    console.log("------------------");
    console.log(body);
    console.log("------------------");
    console.log("");
  } else
  {
    messageHandler({
      fromName: message.from.name,
      fromEmail: message.from.address,
      toEmail: client.email,
      subject: message.title,
      attachmentName: filename,
      attachmentBody: body});
  }
}

function getSession(email)
{
  for (var i in sessions)
  {
    if ( sessions[i].email == email )
    {
      mylog({user:email, status:"Get session - TRUE"});
    }
  }
  mylog({user:email, status:"Get session - FALSE"});
  return false;
}

function stopSession(email)
{
  for (var i in sessions)
    if ( sessions[i].email == email )
    {
      console.log("Stopping session for " + sessions[i].email);
      sessions[i].close();
      sessions.splice(i, 1);
      var sess = sessions.map(function(s){return s.email;});
      console.log("Remaining users: " + sess.join(","));
 
      mylog({user:email, status:"Stopping session ok"});

      return;
    }
  mylog({user:email, status:"Stopping session failed"});
}

function setHandler(h)
{
  messageHandler = h;
}
