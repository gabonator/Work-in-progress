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

function cartesian(c, x, y)
{
  if (x < -2047 || x > 2047) 
    throw "wrong x " + x;
  if (y < -2047 || y > 2047) 
    throw "wrong y " + y;
  var radius = Math.sqrt(x*x+y*y);
  var color = c;
  var angle = Math.atan2(-y, x)/Math.PI*180;
  if (angle < 0)
    angle += 360;
  angle = angle/360*1024;
  if (radius < 0 || radius > 4095) 
    throw "wrong radius";
  if (angle < 0 || angle >= 1024)
    throw "wrong angle";
  if (c < 0 || c > 7)
    throw "wrong color";
  return {c:color, r:Math.floor(radius), a:Math.floor(angle), b:0};
}

function polar(c, radius, angle)
{
  var color = c;
  if (angle < 0)
    angle += 360;
  angle = angle/360*1024;
  if (radius < 0 || radius > 4095) 
    throw "wrong radius";
  if (angle < 0 || angle >= 1024)
    throw "wrong angle";
  if (c < 0 || c > 7)
    throw "wrong color";
  return {c:color, r:Math.floor(radius), a:Math.floor(angle), b:0};
}

module.exports = {TF1Writer:TF1Writer, Cartesian:cartesian, Polar:polar};
