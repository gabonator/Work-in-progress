class Preview
{
  constructor()
  {
    this.verbose = false;
  }

  connect(address, channel)
  {
    return new Promise((resolve, reject) =>
    {
      var BTSP = require('bluetooth-serial-port');
      var serial = new BTSP.BluetoothSerialPort();
      this.serial = serial;
      this.rx = Buffer.alloc(0);
      this.rxFinished = null;

      serial.on('data', (function(data) {
         if (data.length == 0)
           return;

         this.rx = Buffer.concat([this.rx, data]);
         if (this.verbose)
           console.log("BT RX: " + [...this.rx]);
         if (this.rx[0] != 0x5a)
           throw "wrong protocol";
         if (this.rx.length > 4 && this.rx.length == 2+this.rx[4])
         {
           this.rx = Buffer.alloc(0);
           if (this.rxFinished)
           {
             this.rxFinished();
             this.rxFinished = null;
           }
         }
      }).bind(this));

      serial.on('closed', function() { 
         console.log("BT CLOSED");
      });

      serial.connect(address, channel, function() {
        console.log("BT: Connected");
        resolve();
      }, function () {
        console.log("BT: Failed to connect");
        reject();
      });
    });
  }

  disconnect()
  {
    this.serial.close();
  }

  send(buffer)
  {
     var preamble = [256-86, 5, 0, 90].concat(this.shortArrayToBytes([8, buffer.length+10]));
     var geometry = [256-86, 6, 0, 90].concat(this.shortArrayToBytes([buffer.length+10, buffer.length-1, buffer.length-1]));
     geometry = geometry.concat(buffer);

     return Promise.resolve()
       .then( () => this.transfer(preamble) )
       .then( () => this.transfer(geometry) )
  }

  transfer(buffer)
  {
    return new Promise((resolve, reject) =>
    {
      var buf = new Buffer(buffer);

      if (this.verbose)
        console.log("TX: " + buffer.join(","));

      this.serial.write(buf, (e) => { if (e) reject(e); }); 
      this.rxFinished = resolve;
    });
  }

  dmx(buffer)
  {
    var dmxBuffer = [170, 4, 0, 90].concat(this.shortArrayToBytes([6+buffer.length])).concat(buffer);
    return this.transfer(dmxBuffer);
  }

  shortArrayToBytes(arr)
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
}

module.exports = {Preview:Preview};