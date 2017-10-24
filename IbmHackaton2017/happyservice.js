//'option strict';

module.exports = {authenticate:authenticate, getSession:getSession, stopSession:stopSession, startSession:startSession};

var inbox = require("inbox"),
    util = require("util");

var Stream = require("stream").Stream;
var concat = require('concat-stream');
var Promise = require('bluebird');
var mylog = require("./logger.js").mylog;

var sessions = [];

var ToneAnalyzerV3 = require('watson-developer-cloud/tone-analyzer/v3');
 
var tone_analyzer = new ToneAnalyzerV3({
  username: 'cc703b4c-1bf9-4a86-add9-799c56827e68',
  password: 'EtHcXpx6qLso',
  version_date: '2016-05-19'
});
 
function proGetTone(text)
{
    var args = Array.prototype.slice.call(arguments);
    
    return new Promise(function(resolve, reject) {
        tone_analyzer.tone({ text: text},
          function(err, tone) {
            if (err)
            {
              console.log(err);
              reject(err);
            }
            else
            {
                var attitude = 0;
                var mapping = {"anger" : -1.0, "fear" : -0.3, "disgust" : -0.2, "sadness" : -0.6, "joy" : 3.0};
                var tones = tone["document_tone"]["tone_categories"].find(t => t.category_id == "emotion_tone").tones;
//                var tones = tone["document_tone"]["tone_categories"].find(function(t) { return t.category_id == "emotion_tone";}).tones;        

                for (var i in tones)
                {
                    var c = mapping[tones[i]["tone_id"]] || 0;
                    attitude += tones[i].score * (mapping[tones[i]["tone_id"]] || 0);
                }

	        mylog({attitude_tones:tones, attitude_result:attitude});
                
                args[0] = attitude;
                resolve(args);
            }
        });
    });
}

inbox.IMAPClient.prototype.createMessageStream = function(uid, section){
    var stream = new Stream();
    
    section = section || "";
    uid = Number(uid) || 0;

    if(!uid){
        process.nextTick(this.emit.bind(this, new Error("Invalid UID value")));
        return;
    }

    if(this._currentState != this.states.SELECTED){
        process.nextTick(this.emit.bind(this, new Error("No inbox selected")));
        return;
    }

    this._send("UID FETCH " + uid + " BODY.PEEK["+section+"]", (function(status){
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
    return attachments.find(att => att.type === "text/plain");
//    return attachments.find(function(att) { return att.type === "text/plain" });
}

function decodeMessageData(buf, encoding)
{
    var dataString = buf.toString();
    if (encoding != "base64")
        return dataString;
    
    var rawString = new Buffer(dataString, 'base64').toString();
    return rawString;
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

function startSession(email, password, server, handler)
{
  mylog({login_email:email, status:"start session"});
  proConnect({
  	server: server,
  	secure: true,
  	user: email,
  	pass: password
  })
  .then(function(client) {
      mylog({login_email:email, login_server:server, status:"connected"});
      console.log("Connected");
      return proGetMailboxes(client);    
  })
  .spread(function(client, inboxes) {
      client.goodNewsPath = findMailbox(inboxes, "Good news");
      if (client.goodNewsPath)
          return [client, inboxes];
      
      return proCreateMailbox(client, "Good news", inboxes);
  })
  .spread(function(client, inboxes) {
      client.badNewsPath = findMailbox(inboxes, "Bad news");
      if (client.badNewsPath)
          return [client, inboxes];
      
      return proCreateMailbox(client, "Bad news", inboxes);
  })
  .spread(function(client) {
      if (client.goodNewsPath && client.badNewsPath)
          return client;

      return proGetMailboxes(client).spread(function(client, inboxes) {
          client.goodNewsPath = findMailbox(inboxes, "Good news");
          client.badNewsPath = findMailbox(inboxes, "Bad news");
      
          if (client.goodNewsPath && client.badNewsPath)
              return client;

          mylog({error:"Cant access target mailboxes"});
          
          throw "Cant access target mailboxes";
      });
  })
  .then(function(client) {
      return proOpenMailbox(client, "INBOX");
  })
  .spread(function(client, mailbox) {
    mylog({user:email, status:"Ready"});

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

        HandleMessage(client, message, body);

      }), {
      	end: true
      });
    });
  })
  .catch(function(error){
     mylog({login_email:email, login_server:server, status:"failed"});
     console.log("Rejection: " + error);     
     handler(false);
  });
}

function HandleMessage(client, message, body)
{
    const thresholdPositive = 0.5;
    const thresholdNegative = -0.5;
    
    console.log("------------------ ");
    console.log(client.email + ": New message title: " + message.title + " from: " + message.from.name);
    console.log("------------------");
    console.log(body);
    console.log("------------------");
    console.log("");

    proGetTone(body, client, message)
    .spread(function(attitude, client, message)
    {
	mylog({user:client.email, msg:body, from:message.from.name, attitude:attitude});

        console.log("Attitude of message: " + attitude.toFixed(1))

        if (message.title.indexOf("dobra sprava") != -1 || attitude >= thresholdPositive)
        {
            console.log("Positive message");
            
            client.moveMessage(message.UID, client.goodNewsPath, function(err) {
                console.log(err || "moved to " + client.goodNewsPath + " ok!");
            });
        }
        
        if (message.title.indexOf("zla sprava") != -1 || attitude <= thresholdNegative)
        {
            console.log("Negative message");
            
            client.moveMessage(message.UID, client.badNewsPath, function(err) {
                console.log(err || "moved to " + client.badNewsPath + " ok!");
            });
        }
    });
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
