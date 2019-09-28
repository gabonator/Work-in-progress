'use strict';

var fs = require('fs');
var BTSP = require('bluetooth-serial-port');
var serial = new BTSP.BluetoothSerialPort();
var dns = require("dns");

// bluetooth
const address = "00:18:E4:35:5F:2A";
const channel = 1;
var reconnect = false;
var connected = false;

serial.on('data', function(data) {
   logData(data);
});

serial.on('closed', function() { 
  connected= false;
  if (reconnect)
    clearTimeout(reconnect);

  console.log("bt: connection closed, reconnecting...");
  reconnect = setTimeout(btReconnect, 10000);
});

function btReconnect()
{
  if (reconnect)
    clearTimeout(reconnect);

  console.log("bt: connecting...");

  serial.connect(address, channel, function() {
    console.log('bt: connected');
    connected = true;
  }, function () {
    if (reconnect)
      clearTimeout(reconnect);

    console.log("bt: cannot connect, reconnecting...");
    reconnect = setTimeout(btReconnect, 10000);
  });
}

btReconnect();
  
// data logger
var logBuffer = "";
var logBufferCollect = [];
var logLastData = null;
var logBufferAccess = [];
var logLastLine = null;

function logData(msg)
{
  console.log(msg);
}

function shortArrayToBytes(arr)
{
  var out = [];
  for (var i in arr)
  {
    var x = arr[i];
    out.push(x & 0xff);
    out.push(x >> 8);
  }
  return out;
}


var f = null;
var block = 0;
var done = false;
function getFileBuffer()
{            
  if (done)
    return [];
  if (!f) 
  {
    f = require("fs").readFileSync("tetris.tf1");
    var len = f.length;
    var getReadyFileBytes = [256-86, 17, 0, 90, 16, 0, 0, 0, "t".charCodeAt(0), "f".charCodeAt(0), "1".charCodeAt(0), 0, len & 255, (len >> 8) & 255, (len >> 16)&255, (len >> 24)&255];
    block = 0;
     console.log(new Buffer(getReadyFileBytes));
    return new Buffer(getReadyFileBytes);
  }

  var block_len_max = 512-12;
  var block_ofs = block*block_len_max;
  var block_len = f.length - block*block_len_max;
  if (block_len > block_len_max)
    block_len = block_len_max;
  var block_id = block+1;
  console.log("sending block "+block);
  var prefix = [256-86, 18, 0, 90, (block_len+12) & 255, ((block_len+12) >> 8) & 255, block_id & 255, (block_id >> 8) & 255, "t".charCodeAt(0), "f".charCodeAt(0), "1".charCodeAt(0), 0];
  for (var i = block_ofs; i<block_ofs + block_len; i++)
     prefix.push(f[i]); 
  console.log(new Buffer(prefix));

  if (block_len < block_len_max)
  {
    // set channel to 0/15!
    done = true;
    console.log("Done!!!");
  }
  block++;
  return new Buffer(prefix);
}

setInterval(() =>
{
  if (connected)
  {
    var buf = getFileBuffer();
    if (buf.length > 0)
    {
      console.log("Sending: " + buf.length);
      serial.write(buf, () => 0); 
    }
  }
}, 500);
