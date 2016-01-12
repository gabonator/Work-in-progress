"use strict";
process.title = 'Tuneller server';

var os = require( 'os' );
console.log( "  - Network interfaces: \n" + os.networkInterfaces( ) );
// Web server ==============================================================

var http = require('http');
var url = require('url');
var fs = require('fs');
var webbase = "../nacl/build";
//var index = fs.readFileSync('../nacl/build/index.html');

console.log("  - Webserver at localhost running ");

http.createServer(function (request, response) {
  var uri = url.parse(request.url).pathname
  if ( uri == "/" )
    uri = "/index.html";

  var file = webbase + uri;
  fs.exists( file, function(exists)
  { 
    if(!exists) 
    {
      response.writeHead(404, {"Content-Type": "text/plain"});
      response.write("404 Not Found\n");
      response.end();
      return;
    }

    if ( file.substr(-5) == ".html" )
      response.writeHead(200, {'Content-Type': 'text/html'}); 
    else
      response.writeHead(200, {'Content-Type': 'text/plain'}); 

    response.end(fs.readFileSync(file));
  });
}).listen(80);


// Websocket server ==============================================================

// User globals
var globalMessage = null;
var globalWorldId = null;
var globalClient = null;

// Websocket
var webSocketsServerPort = 1337;
var webSocketServer = require('websocket').server;
var http = require('http');
var server = http.createServer(function(request, response) {
  // Not important for us. We're writing WebSocket server, not HTTP server
});
var clients = [];

server.listen(webSocketsServerPort, function() {
  console.log("  - Server is listening on port " + webSocketsServerPort);
});

var wsServer = new webSocketServer({
  // WebSocket server is tied to a HTTP server. WebSocket request is just
  // an enhanced HTTP request. For more info http://tools.ietf.org/html/rfc6455#page-6
  httpServer: server
});

wsServer.on('request', function(request) {
  var connection = request.accept(null, request.origin); 
  connection.id = getUniqueId();
  connection.lastComm = getTs();
  connection.lastRequest = 0;

  if ( clients.length == 0 )
  {
    globalWorldId = Math.floor(Math.random()*10000);
  }

  clients.push(connection);

  console.log("  - Connection from " + connection.id + " accepted.");

  // user sent some message
  connection.on('message', function(message) {
    this.lastComm = getTs();
    globalClient = this;
    globalMessage = message.utf8Data;
    console.log(this.id + " > " + globalMessage.replace("\n", ""));
    eval(globalMessage);
    globalMessage = null;
    globalClient = null;
  });

  connection.on('pong', function() {
    this.lastComm = getTs();
    this.lastRequest = 0;
    console.log(this.id + " > pong");
  });

  // user disconnected
  connection.on('close', function(connection) {
    onDisconnect(this);
    console.log("  - Peer " + this.id + " disconnected.");
    // remove user from the list of connected clients
    removeUniqueId(this.id);
    removeClientById(this.id);
  });
});

setInterval(function()
{
  // TODO: replace with WebSocketConnection.prototype.setKeepaliveTimer
  var ts = getTs();  

//  var x = "";
  for ( var i in clients )
  {
//    x += " " + clients[i].id;
    var client = clients[i];
    if ( (ts - client.lastComm >= 5000)  )
    {
      // wait for pong
      if ( client.lastRequest == 0 )
      {
        client.lastRequest = ts;
        console.log(client.id + " < ping");
        client.ping();
      } else
      {
        console.log(client.id + " - Forced disconnection!");
        client.close();

        removeUniqueId(this.id);
        removeClientById(this.id);
      }
    }
  }
//  console.log("clients:"+x);
}, 1000);

function removeClientById(id)
{
  for ( var i in clients )
    if ( clients[i].id == id )
    {
      clients.splice(i, 1);
    }
}
// user
var startupTs = (new Date()).getTime();
var tanks = [];

function getUniqueId()
{
  var tankId;
  for (tankId=0; tankId<tanks.length; tankId++)
    if ( tanks[tankId] == 0 )
    {
      tanks[tankId] = 1;
      return tankId
    }

  tanks.push(1);
  return tanks.length-1;
}

function removeUniqueId(id)
{
  tanks[id] = 0;
}

function onDisconnect(client)
{
  for (var i=0; i < clients.length; i++) 
    if ( clients[i] == client)
    {
      globalClient = client;
      globalMessage = "notifyDead({id:"+client.id+"});";
      forward();
      globalClient = null;
      globalMessage = null;
      removeUniqueId(client.id);
      return;
    }
}

function forward()
{
  for (var i=0; i < clients.length; i++) 
    if ( clients[i] != globalClient )
      sendClient(clients[i], globalMessage);
}

function sendClient(client, msg)
{
  console.log(client.id + " < " + msg.replace("\n", ""));
  client.sendUTF(msg);
}

function getTs()
{
  return (new Date()).getTime() - startupTs;
}

// handlers

function requestTime(json)
{
  sendClient(globalClient, "replyTime({n:"+json.n+", ts:"+getTs()+"});");
}

function requestStart()
{
  var tankId = globalClient.id;
  var x = 70 + tankId*100;
  var y = 70;

  sendClient(globalClient, "replyStart({id:"+tankId+", ts:"+getTs()+", world:"+globalWorldId+", x:"+x+", y:"+y+"});");

  for (var i=0; i < clients.length; i++) 
    if ( clients[i] != globalClient )
      sendClient(clients[i], "requestInfo();");
}

var notifyMove = forward;
var notifyInfo = forward;
var notifyFire = forward;
