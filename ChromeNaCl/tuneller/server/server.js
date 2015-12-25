
// http://ejohn.org/blog/ecmascript-5-strict-mode-json-and-more/
"use strict";
process.title = 'node-serial-ws';

// Websocket
var webSocketsServerPort = 1337;
var webSocketServer = require('websocket').server;
var http = require('http');
var server = http.createServer(function(request, response) {
    // Not important for us. We're writing WebSocket server, not HTTP server
});
var clients = [];

server.listen(webSocketsServerPort, function() {
    console.log((new Date()) + " Server is listening on port " + webSocketsServerPort);
});

var wsServer = new webSocketServer({
    // WebSocket server is tied to a HTTP server. WebSocket request is just
    // an enhanced HTTP request. For more info http://tools.ietf.org/html/rfc6455#page-6
    httpServer: server
});

wsServer.on('request', function(request) {
    console.log((new Date()) + ' Connection from origin ' + request.origin + '.');
    var connection = request.accept(null, request.origin); 
    console.log((new Date()) + ' Connection accepted.');

    var index = clients.push(connection) - 1;

    // user sent some message
    connection.on('message', function(message) {
      onReceive(message.utf8Data);
    });

    // user disconnected
    connection.on('close', function(connection) {
            //onClosePort();
            console.log((new Date()) + " Peer "
                + connection.remoteAddress + " disconnected.");
            // remove user from the list of connected clients
            clients.splice(index, 1);
    });

});

function onReceive(msg)
{
  console.log("ws msg:" + msg.replace("\n", ""));
//  eval(msg);
//  serialPort.write(msg + "\n");
}

function onSerial(msg)
{
  console.log("uart msg:" + msg.replace("\n", ""));
  for (var i=0; i < clients.length; i++) 
    clients[i].sendUTF(msg);
}

var buffer = "";


function replaceAll(str, find, replace) {
  return str.replace(new RegExp(find, 'g'), replace);
}

function onTransmit(packet)
{
  // TX:B5,01,00,AB,01,B5,07
  console.log("transmit: "+packet);
  serialPort.write("TX:"+packet+"\n");
}

setInterval(function(){onSerial('ok');}, 1000);
