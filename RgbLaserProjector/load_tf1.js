class Reader {  
  constructor(data)
  {
    this.data = data;
    this.ofs = 0;
  }
  GetByte()
  {
    return this.data[this.ofs++];
  }
  GetDword()
  {
    return this.GetByte() | (this.GetByte() << 8) | (this.GetByte() << 16) | (this.GetByte() << 24);
  }
  GetWord()
  {
    return this.GetByte() | (this.GetByte() << 8);
  }
  GetBuffer(n)
  {
    var b = [];
    for (var i =0;i<n;i++)
      b.push(this.GetByte());
    return new Buffer(b);
  }
  Skip(n)
  {
    this.ofs += n;
  }
}

class TF1
{
  constructor(name)
  {
    var data = require("fs").readFileSync(name);
    this.r = new Reader(data);

    // header
    this.r.Skip(16); // 16x 0
    this.r.GetDword(); // 48
    this.patternsCount = (this.r.GetDword()-48-4)/4;
    this.r.GetWord(); // 1
    this.channelListCount = this.r.GetWord()-3;
    this.sceneItemListCount = this.r.GetWord();
    this.patternsCount = this.r.GetWord();
    this.r.GetWord(); // 3
    this.r.Skip(14); // 16x 0

    this.scenes = [];
    for (var i=0; i<this.sceneItemListCount; i++)
    {
      var scene = {};
      scene.offset = this.r.GetDword();
      this.scenes.push(scene);
//      scene.playTime = this.r.GetWord()*10;
    }
    this.offsetEnd = this.r.GetDword(); // filesize-1
    for (var i=0; i<this.sceneItemListCount; i++)
    {
      this.scenes[i].playTime = this.r.GetWord()*10;
      this.scenes[i].relationValue = this.r.GetByte();
      this.scenes[i].channels = this.r.GetBuffer(this.channelListCount);
    }
   
    for (var i=0; i<this.sceneItemListCount; i++)
    {
      if (this.r.ofs != this.scenes[i].offset)
        throw "read error";
      var len = i < this.sceneItemListCount-1 ? this.scenes[i+1].offset - this.scenes[i].offset : this.offsetEnd - this.scenes[i].offset;
      this.scenes[i].data = this.parseGeometry(this.r.GetBuffer(len));
    }

  }

    parseGeometry(buf)
    {
      if ((buf.length % 4) != 0)
        throw "wrong size!"
      var g = [];
      for (var i=0; i<buf.length; i+=4)
      {
        var a = buf[i]+buf[i+1]*256;
        var b = buf[i+2]+buf[i+3]*256;
        // c - color, r - radius 0..8191, a - angle, b - some extra angle?
        g.push({c:a>>13, r:a%8192, a:b&1024, b:b>>10});
      }
      return g;
    }
}


var tf1 = new TF1("purplemantra.tf1");
console.log(JSON.stringify(tf1));

