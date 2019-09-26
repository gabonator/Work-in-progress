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

class TF1Reader
{
  Load(name)
  {
    var data = require("fs").readFileSync(name);
    this.r = new Reader(data);
    var object = this.Parse();
    delete this.r;
    return object;
  }

  Parse()
  {
    // header
    this.r.Skip(16); // 16x 0
    this.r.GetDword(); // 48
    this.patternsCount = (this.r.GetDword()-48-4)/4;
    this.r.GetWord(); // 1
    this.channelListCount = this.r.GetWord()-3; //bytes per scene info
    this.sceneItemListCount = this.r.GetWord();
    this.patternsCount = this.r.GetWord();
    this.r.GetWord(); // 3
    this.r.Skip(14); // 16x 0

    console.log({patCount:this.patternsCount, channels:this.channelListCount, scenes:this.sceneItemListCount});

    this.scenes = [];
    for (var i=0; i<this.sceneItemListCount; i++)
    {
      var scene = {};
      scene.offset = this.r.GetDword();
      this.scenes.push(scene);
    }
    var bufToArray = (b) => {var n = []; for (var i=0;i<b.length; i++) n.push(b[i]); return n};
    this.offsetEnd = this.r.GetDword(); // filesize-1
    for (var i=0; i<this.sceneItemListCount; i++)
    {
      // scene info
      this.scenes[i].playTime = this.r.GetWord()*10;
      this.scenes[i].relationValue = this.r.GetByte();
      this.scenes[i].channels = bufToArray(this.r.GetBuffer(this.channelListCount));
      console.log({relVal:this.scenes[i].relationValue, playTime:this.scenes[i].playTime/1000, dmx:JSON.stringify(this.scenes[i].channels)});
    }
   
    for (var i=0; i<this.sceneItemListCount; i++)
    {
      if (this.r.ofs != this.scenes[i].offset)
        throw "read error";
      var len = i < this.sceneItemListCount-1 ? this.scenes[i+1].offset - this.scenes[i].offset : this.offsetEnd - this.scenes[i].offset;
      this.scenes[i].data = this.parseGeometry(this.r.GetBuffer(len));
    }
    return this;
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
        g.push({c:a>>13, r:a%4096, a:b%1024, b:b>>10});
      }
      return g;
    }
}

class Writer
{
  constructor()
  {
    this.buf = [];
  }
  Write(arr)
  {
    this.buf = this.buf.concat(arr);
  }
  WriteDword(i)
  {
    this.Write([i & 255, (i >> 8) & 255, (i >> 16) & 255, (i >> 24) & 255]);
  }
  WriteWord(i)
  {
    this.Write([i & 255, (i >> 8) & 255]);
  }
  WriteByte(i)
  {
    this.Write([i]);
  }
  Append(buf)
  {
    this.buf = this.buf.concat(buf.buf);
  }
  GetBuffer()
  {
    return new Buffer(this.buf);
  }
  GetSize()
  {
    return this.buf.length;
  }
}

class TF1Writer
{
  GenerateBuffer()
  {
    var buf = new Writer();
    buf.Write(new Array(16).fill(0));
    buf.WriteDword(48);
    buf.WriteDword(this.data.patternsCount*4 + 52);
    buf.WriteWord(1);
    buf.WriteWord(this.data.channelListCount+3);
    buf.WriteWord(this.data.sceneItemListCount);
    buf.WriteWord(this.data.patternsCount);
    buf.WriteWord(3);
    buf.Write(new Array(14).fill(0));

    var buf1 = new Writer();
    var buf2 = new Writer();

    var tableOfsEnd = buf.GetSize() + (this.data.sceneItemListCount+1)*4;

    for (var i=0; i<this.data.sceneItemListCount; i++)
    {
      buf1.WriteWord(this.data.scenes[i].playTime / 10);
      buf1.WriteByte(this.data.scenes[i].relationValue);
      buf1.Write(this.data.scenes[i].channels);
    }

    for (var i=0; i<this.data.sceneItemListCount; i++)
    {
      buf.WriteDword(tableOfsEnd + buf1.GetSize() + buf2.GetSize());
      buf2.Write(this.buildGeometry(this.data.scenes[i].data));
    }
    buf.WriteDword(tableOfsEnd + buf1.GetSize() + buf2.GetSize());

    buf.Append(buf1);
    buf.Append(buf2);
    buf.WriteByte(0);
    return buf.GetBuffer();
  }

  buildGeometry(scene)
  {
    var data = [];
    for (var i=0; i<scene.length; i++)
    {
      var p = scene[i];
/*
p.c = p.c ? 1 : 0;
p.b = 0;
p.r /= 2;
p.a = (p.a + 300)%1024;
//console.log(p);
*/
      var a = p.r | (p.c<<13);
      var b = p.a | (p.b<<10);
      data.push(a & 255);
      data.push(a >> 8);
      data.push(b & 255);
      data.push(b >> 8);
    }
    return data;
  }

  Save(name, data)
  {
    this.data = data;
    require("fs").writeFileSync(name, this.GenerateBuffer());
  }
}

var tf1 = new TF1Reader();
var data = tf1.Load("purplemantra.tf1");
console.log("---");
var writer = new TF1Writer();
writer.Save("test.tf1", data);
