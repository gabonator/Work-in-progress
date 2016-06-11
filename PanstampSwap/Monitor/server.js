
// http://ejohn.org/blog/ecmascript-5-strict-mode-json-and-more/
"use strict";
process.title = 'node-serial-ws';

// Serial port
var SerialBinding = require("serialport").SerialPortBinding;
var SerialPort = require("serialport").SerialPort;
//var portName = 'COM59'; 

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

    onRequestPortList();

    // user sent some message
    connection.on('message', function(message) {
      onReceive(message.utf8Data);
    });

    // user disconnected
    connection.on('close', function(connection) {
            onClosePort();
            console.log((new Date()) + " Peer "
                + connection.remoteAddress + " disconnected.");
            // remove user from the list of connected clients
            clients.splice(index, 1);
    });

});

function onReceive(msg)
{
  console.log("ws msg:" + msg.replace("\n", ""));
  eval(msg);
//  serialPort.write(msg + "\n");
}

function onSerial(msg)
{
  console.log("uart msg:" + msg.replace("\n", ""));
  for (var i=0; i < clients.length; i++) 
    clients[i].sendUTF(msg);
}

var buffer = "";
var serialPort;


function onRequestPortList()
{
    SerialBinding.list(function(err, data)
    {
      var result = [];

      if (err)
        console.log("Error: "+err);

      if ( typeof(data) == "object" && data.length )
      {
        for (var i in data)
        {
          if ( data[i].pnpId.indexOf("BTHENUM\\") != -1 )
            continue;
          result.push(data[i]);
  //        console.log(data[i]);
        }
      }
      onSerial("onPorts("+JSON.stringify(result)+");\n");
    });
}

function onClosePort()
{
  if ( serialPort )
    serialPort.close();
  // there must be some delay between calling onClosePort and onOpenPort
}

function replaceAll(str, find, replace) {
  return str.replace(new RegExp(find, 'g'), replace);
}

function onOpenPort(portName)
{

  serialPort = new SerialPort(portName, {
    baudrate: 9600,
    // defaults for Arduino serial communication
     dataBits: 8,
     parity: 'none',
     stopBits: 1,
     flowControl: false
  });

  serialPort.on("open", function () 
  {
    console.log('open serial communication');
    serialPort.write("hello\n");

          // Listens to incoming data
    serialPort.on('data', function(data) 
    {
      buffer += new String(data);
      var lines = buffer.split("\r\n");
      while ( lines.length > 1 )
        onSerial( "onRx('"+replaceAll(lines.shift(), "'", "\\\'") +"');\n" );
      buffer = lines.join("\n");
    });
   
  });  
}

function onTransmit(packet)
{
  // TX:B5,01,00,AB,01,B5,07
  console.log("transmit: "+packet);
  serialPort.write("TX:"+packet+"\n");
}

setInterval(function(){}, 1000);
