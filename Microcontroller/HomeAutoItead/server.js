var PORT = 2000;
var HOST = '0.0.0.0';

var dgram = require('dgram');
var server = dgram.createSocket('udp4');

server.on('listening', function () {
    var address = server.address();
    console.log('UDP Server listening on ' + address.address + ":" + address.port);
});

server.on('message', function (message, remote) {
    console.log(remote.address + ':' + remote.port +' - ' + message);
  
//    remote.send(new Buffer("reply"));
//server.send(new Buffer('reply'), 0, 5, remote.port, remote.address, function(err, bytes) {} );

});

server.bind(PORT, HOST);
