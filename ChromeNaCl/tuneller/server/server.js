"use strict";
process.title = 'Tuneller server';

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
  var index = clients.push(connection) - 1;
  connection.index = index;

  console.log("  - Connection from " + connection.index + " accepted.");

  // user sent some message
  connection.on('message', function(message) {
    globalClient = this;
    onReceive(message.utf8Data);
    globalClient = null;
  });

  // user disconnected
  connection.on('close', function(connection) {
    onDisconnect(this);
    console.log("  - Peer " + this.index + " disconnected.");
    // remove user from the list of connected clients
    clients.splice(index, 1);
  });
});

// user
function onReceive(msg)
{
  console.log(globalClient.index + " > " + msg.replace("\n", ""));
  eval(msg);
}

function replaceAll(str, find, replace) {
  return str.replace(new RegExp(find, 'g'), replace);
}

setInterval(function(){}, 1000);

// handlers
var globalClient = null;
var worldId = Math.floor(Math.random()*10000);
var tanks = [];

function onDisconnect(client)
{
  for (var i=0; i < clients.length; i++) 
    if ( clients[i] == client)
    {
      tanks[i] = 0;
      return;
    }
}

function requestStart()
{
  var tankId;
  for (tankId=0; tankId<tanks.length; tankId++)
    if ( tanks[tankId] == 0 )
      break;

  var x = 70 + tankId*100;
  var y = 70;

  sendClient(globalClient, "replyStart({id:"+tankId+", ts:"+getTs()+", world:"+worldId+", x:"+x+", y:"+y+"});");

  for (var i=0; i < clients.length; i++) 
    if ( clients[i] != globalClient )
      sendClient(clients[i], "requestInfo();");

  tanks[tankId] = 1;
}


function notifyMove(json)
{
  for (var i=0; i < clients.length; i++) 
    if ( clients[i] != globalClient )
      sendClient(clients[i], replaceAll("notifyMove("+JSON.stringify(json)+");", "\"", ""));
}

function notifyInfo(json)
{
  for (var i=0; i < clients.length; i++) 
    if ( clients[i] != globalClient )
      sendClient(clients[i], replaceAll("notifyInfo("+JSON.stringify(json)+");", "\"", ""));
}

function notifyFire(json)
{
  for (var i=0; i < clients.length; i++) 
    if ( clients[i] != globalClient )
      sendClient(clients[i], replaceAll("notifyFire("+JSON.stringify(json)+");", "\"", ""));
}

function sendClient(client, msg)
{
  console.log(client.index + " < " + msg);
  client.sendUTF(msg);
}

function getTs()
{
  return (new Date()).getTime() - (new Date(2015, 0, 1)).getTime();
}
