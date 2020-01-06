// Ether dream 2 test

var Parser = require("binary-parser").Parser;

handler = () => 0;
var phase = 0;

function buildBuffer()
{
  var n = 5000;
  var buf = Array(n*18+3);
  var j = 0;
  buf[j++] = 'd'.charCodeAt(0);
  buf[j++] = n%256;
  buf[j++] = Math.floor(n/256);

//  var buf = ['d'.charCodeAt(0), 1, 0];
  for (var i=0; i<n; i++)
  {
    var rx = Math.cos(phase/10)*0.8;
    var ry = Math.sin(phase/10)*0.8;
    phase++;
    var x = Math.floor(rx*32767);
    var y = Math.floor(ry*32767);
    x = Math.min(Math.max(-32767, x), 32767);
    y = Math.min(Math.max(-32767, y), 32767);

    var r = (i & 1) ? 65535 : 0;
    var g = 0*65535;
    var b = (i & 2) ? 65535 : 0;
    var u = 0;
    var v = 0;

    j += 2;
    buf[j++] = x%256; buf[j++] = Math.floor(x/256);
    buf[j++] = y%256; buf[j++] = Math.floor(y/256);
    buf[j++] = Math.floor(r/256); buf[j++] = r%256;
    buf[j++] = Math.floor(g/256); buf[j++] = g%256;
    buf[j++] = Math.floor(b/256); buf[j++] = b%256;
    j += 6;
  }
//  console.log(buf);
  return buf;
}

function parseAck(buffer)
{
  var ack = new Parser()
    .endianess("little")
    .uint8("response")
    .uint8("command")
    .uint8("protocol")
    .uint8("light_engine_state")
    .uint8("playback_state")
    .uint8("source")
    .uint16("light_engine_flags")
    .uint16("playback_flags")
    .uint16("source_flags")
    .uint16("buffer_fullness")
    .uint32("point_rate")
    .uint32("point_count")
  return ack.parse(buffer);
}

var net = require('net');

var client = new net.Socket();
client.connect(7765, '192.168.1.109', function() {
	console.log('Connected');

if (1)

setTimeout(() => {
console.log("prep");
	client.write(new Buffer(['p'.charCodeAt(0)]));
}, 500);
/*
setTimeout(() => {
console.log("config");
	client.write(new Buffer(['b'.charCodeAt(0),  0, 0,   0, 0, 1, 0]));
}, 1000);

setTimeout(() => {
console.log("queue");
	client.write(new Buffer(['q'.charCodeAt(0),  0, 1, 0, 0]));
}, 1500);
*/
setTimeout(() => {
console.log("buffer");
	client.write(new Buffer(buildBuffer()));

setTimeout(() => {
console.log("play");
	client.write(new Buffer(['b'.charCodeAt(0),  0, 0,   0, 4, 0, 0]));
}, 100);


  setInterval(() => {

handler = (json) => {
  if (json.playback_state == 2 && json.buffer_fullness < 1000)
  {   
    console.log("refill");
	client.write(new Buffer(buildBuffer()));
  }
};

console.log("ping");
  	client.write(new Buffer(['?'.charCodeAt(0)]));
  }, 300);

}, 2000);


});

client.on('data', function(data) {
var flag = "????";
if (data[0] == 0x61) flag = ("Accepted");
if (data[0] == 0x46) flag = ("Full");
if (data[0] == 0x49) flag = ("Invalid");
if (data[0] == 0x21) flag = ("Emergency");

var parsed = parseAck(data);
console.log(flag + ": " + data.length + " " + JSON.stringify(parsed));

if (flag == "Accepted")
  handler(parsed);
});

client.on('close', function() {
	console.log('Connection closed');
});
