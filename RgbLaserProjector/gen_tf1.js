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

var font = {"0":{"w":20,"g":[[[9,21],[6,20],[4,17],[3,12],[3,9],[4,4],[6,1],[9,0],[11,0],[14,1],[16,4],[17,9],[17,12],[16,17],[14,20],[11,21],[9,21]],[[9,21],[7,20],[6,19],[5,17],[4,12],[4,9],[5,4],[6,2],[7,1],[9,0]],[[11,0],[13,1],[14,2],[15,4],[16,9],[16,12],[15,17],[14,19],[13,20],[11,21]]]},"1":{"w":20,"g":[[[6,17],[8,18],[11,21],[11,0]],[[10,20],[10,0]],[[6,0],[15,0]]]},"2":{"w":20,"g":[[[4,17],[5,16],[4,15],[3,16],[3,17],[4,19],[5,20],[8,21],[12,21],[15,20],[16,19],[17,17],[17,15],[16,13],[13,11],[8,9],[6,8],[4,6],[3,3],[3,0]],[[12,21],[14,20],[15,19],[16,17],[16,15],[15,13],[12,11],[8,9]],[[3,2],[4,3],[6,3],[11,1],[14,1],[16,2],[17,3]],[[6,3],[11,0],[15,0],[16,1],[17,3],[17,5]]]},"3":{"w":20,"g":[[[4,17],[5,16],[4,15],[3,16],[3,17],[4,19],[5,20],[8,21],[12,21],[15,20],[16,18],[16,15],[15,13],[12,12],[9,12]],[[12,21],[14,20],[15,18],[15,15],[14,13],[12,12]],[[12,12],[14,11],[16,9],[17,7],[17,4],[16,2],[15,1],[12,0],[8,0],[5,1],[4,2],[3,4],[3,5],[4,6],[5,5],[4,4]],[[15,10],[16,7],[16,4],[15,2],[14,1],[12,0]]]},"4":{"w":20,"g":[[[12,19],[12,0]],[[13,21],[13,0]],[[13,21],[2,6],[18,6]],[[9,0],[16,0]]]},"5":{"w":20,"g":[[[5,21],[3,11]],[[3,11],[5,13],[8,14],[11,14],[14,13],[16,11],[17,8],[17,6],[16,3],[14,1],[11,0],[8,0],[5,1],[4,2],[3,4],[3,5],[4,6],[5,5],[4,4]],[[11,14],[13,13],[15,11],[16,8],[16,6],[15,3],[13,1],[11,0]],[[5,21],[15,21]],[[5,20],[10,20],[15,21]]]},"6":{"w":20,"g":[[[15,18],[14,17],[15,16],[16,17],[16,18],[15,20],[13,21],[10,21],[7,20],[5,18],[4,16],[3,12],[3,6],[4,3],[6,1],[9,0],[11,0],[14,1],[16,3],[17,6],[17,7],[16,10],[14,12],[11,13],[10,13],[7,12],[5,10],[4,7]],[[10,21],[8,20],[6,18],[5,16],[4,12],[4,6],[5,3],[7,1],[9,0]],[[11,0],[13,1],[15,3],[16,6],[16,7],[15,10],[13,12],[11,13]]]},"7":{"w":20,"g":[[[3,21],[3,15]],[[3,17],[4,19],[6,21],[8,21],[13,18],[15,18],[16,19],[17,21]],[[4,19],[6,20],[8,20],[13,18]],[[17,21],[17,18],[16,15],[12,10],[11,8],[10,5],[10,0]],[[16,15],[11,10],[10,8],[9,5],[9,0]]]},"8":{"w":20,"g":[[[8,21],[5,20],[4,18],[4,15],[5,13],[8,12],[12,12],[15,13],[16,15],[16,18],[15,20],[12,21],[8,21]],[[8,21],[6,20],[5,18],[5,15],[6,13],[8,12]],[[12,12],[14,13],[15,15],[15,18],[14,20],[12,21]],[[8,12],[5,11],[4,10],[3,8],[3,4],[4,2],[5,1],[8,0],[12,0],[15,1],[16,2],[17,4],[17,8],[16,10],[15,11],[12,12]],[[8,12],[6,11],[5,10],[4,8],[4,4],[5,2],[6,1],[8,0]],[[12,0],[14,1],[15,2],[16,4],[16,8],[15,10],[14,11],[12,12]]]},"9":{"w":20,"g":[[[16,14],[15,11],[13,9],[10,8],[9,8],[6,9],[4,11],[3,14],[3,15],[4,18],[6,20],[9,21],[11,21],[14,20],[16,18],[17,15],[17,9],[16,5],[15,3],[13,1],[10,0],[7,0],[5,1],[4,3],[4,4],[5,5],[6,4],[5,3]],[[9,8],[7,9],[5,11],[4,14],[4,15],[5,18],[7,20],[9,21]],[[11,21],[13,20],[15,18],[16,15],[16,9],[15,5],[14,3],[12,1],[10,0]]]},"!":{"w":10,"g":[[[5,21],[4,19],[5,7],[6,19],[5,21]],[[5,19],[5,13]],[[5,2],[4,1],[5,0],[6,1],[5,2]]]},"\"":{"w":10,"g":[[[5,14],[4,13],[5,12],[6,13],[5,14]],[[5,0],[4,1],[5,2],[6,1],[6,-1],[5,-3],[4,-4]]]},"#":{"w":21,"g":[[[11.5,21],[4.5,-7]],[[17.5,21],[10.5,-7]],[[4.5,10],[18.5,10]],[[3.5,4],[17.5,4]]]},"$":{"w":20,"g":[[[8,25],[8,-4]],[[12,25],[12,-4]],[[16,18],[15,17],[16,16],[17,17],[17,18],[15,20],[12,21],[8,21],[5,20],[3,18],[3,16],[4,14],[5,13],[7,12],[13,10],[15,9],[17,7]],[[3,16],[5,14],[7,13],[13,11],[15,10],[16,9],[17,7],[17,3],[15,1],[12,0],[8,0],[5,1],[3,3],[3,4],[4,5],[5,4],[4,3]]]},"%":{"w":24,"g":[[[21,21],[3,0]],[[8,21],[10,19],[10,17],[9,15],[7,14],[5,14],[3,16],[3,18],[4,20],[6,21],[8,21],[10,20],[13,19],[16,19],[19,20],[21,21]],[[17,7],[15,6],[14,4],[14,2],[16,0],[18,0],[20,1],[21,3],[21,5],[19,7],[17,7]]]},"&":{"w":25,"g":[[[21.5,13],[20.5,12],[21.5,11],[22.5,12],[22.5,13],[21.5,14],[20.5,14],[19.5,13],[18.5,11],[16.5,6],[14.5,3],[12.5,1],[10.5,0],[7.5,0],[4.5,1],[3.5,3],[3.5,6],[4.5,8],[10.5,12],[12.5,14],[13.5,16],[13.5,18],[12.5,20],[10.5,21],[8.5,20],[7.5,18],[7.5,16],[8.5,13],[10.5,10],[15.5,3],[17.5,1],[20.5,0],[21.5,0],[22.5,1],[22.5,2]],[[7.5,0],[5.5,1],[4.5,3],[4.5,6],[5.5,8],[7.5,10]],[[7.5,16],[8.5,14],[16.5,3],[18.5,1],[20.5,0]]]},"'":{"w":10,"g":[[[5,19],[4,20],[5,21],[6,20],[6,18],[5,16],[4,15]]]},"(":{"w":14,"g":[[[11,25],[9,23],[7,20],[5,16],[4,11],[4,7],[5,2],[7,-2],[9,-5],[11,-7]],[[9,23],[7,19],[6,16],[5,11],[5,7],[6,2],[7,-1],[9,-5]]]},")":{"w":14,"g":[[[3,25],[5,23],[7,20],[9,16],[10,11],[10,7],[9,2],[7,-2],[5,-5],[3,-7]],[[5,23],[7,19],[8,16],[9,11],[9,7],[8,2],[7,-1],[5,-5]]]},"*":{"w":16,"g":[[[8,21],[8,9]],[[3,18],[13,12]],[[13,18],[3,12]]]},"+":{"w":26,"g":[[[13,18],[13,0]],[[4,9],[22,9]]]},",":{"w":10,"g":[[[5,0],[4,1],[5,2],[6,1],[6,-1],[5,-3],[4,-4]]]},"-":{"w":26,"g":[[[4,9],[22,9]]]},".":{"w":10,"g":[[[5,2],[4,1],[5,0],[6,1],[5,2]]]},"/":{"w":22,"g":[[[20,25],[2,-7]]]},":":{"w":10,"g":[[[5,14],[4,13],[5,12],[6,13],[5,14]],[[5,2],[4,1],[5,0],[6,1],[5,2]]]},";":{"w":10,"g":[[[5,14],[4,13],[5,12],[6,13],[5,14]],[[5,0],[4,1],[5,2],[6,1],[6,-1],[5,-3],[4,-4]]]},"<":{"w":24,"g":[[[20,18],[4,9],[20,0]]]},"=":{"w":26,"g":[[[4,12],[22,12]],[[4,6],[22,6]]]},">":{"w":24,"g":[[[4,18],[20,9],[4,0]]]},"?":{"w":18,"g":[[[4,17],[5,16],[4,15],[3,16],[3,17],[4,19],[5,20],[7,21],[10,21],[13,20],[14,19],[15,17],[15,15],[14,13],[13,12],[9,10],[9,7]],[[10,21],[12,20],[13,19],[14,17],[14,15],[13,13],[11,11]],[[9,2],[8,1],[9,0],[10,1],[9,2]]]},"@":{"w":27,"g":[[[18.5,13],[17.5,15],[15.5,16],[12.5,16],[10.5,15],[9.5,14],[8.5,11],[8.5,8],[9.5,6],[11.5,5],[14.5,5],[16.5,6],[17.5,8]],[[12.5,16],[10.5,14],[9.5,11],[9.5,8],[10.5,6],[11.5,5]],[[18.5,16],[17.5,8],[17.5,6],[19.5,5],[21.5,5],[23.5,7],[24.5,10],[24.5,12],[23.5,15],[22.5,17],[20.5,19],[18.5,20],[15.5,21],[12.5,21],[9.5,20],[7.5,19],[5.5,17],[4.5,15],[3.5,12],[3.5,9],[4.5,6],[5.5,4],[7.5,2],[9.5,1],[12.5,0],[15.5,0],[18.5,1],[20.5,2],[21.5,3]],[[19.5,16],[18.5,8],[18.5,6],[19.5,5]]]},"A":{"w":20,"g":[[[10,21],[3,0]],[[10,21],[17,0]],[[10,18],[16,0]],[[5,6],[14,6]],[[1,0],[7,0]],[[13,0],[19,0]]]},"B":{"w":22,"g":[[[5,21],[5,0]],[[6,21],[6,0]],[[2,21],[14,21],[17,20],[18,19],[19,17],[19,15],[18,13],[17,12],[14,11]],[[14,21],[16,20],[17,19],[18,17],[18,15],[17,13],[16,12],[14,11]],[[6,11],[14,11],[17,10],[18,9],[19,7],[19,4],[18,2],[17,1],[14,0],[2,0]],[[14,11],[16,10],[17,9],[18,7],[18,4],[17,2],[16,1],[14,0]]]},"C":{"w":21,"g":[[[16.5,18],[17.5,15],[17.5,21],[16.5,18],[14.5,20],[11.5,21],[9.5,21],[6.5,20],[4.5,18],[3.5,16],[2.5,13],[2.5,8],[3.5,5],[4.5,3],[6.5,1],[9.5,0],[11.5,0],[14.5,1],[16.5,3],[17.5,5]],[[9.5,21],[7.5,20],[5.5,18],[4.5,16],[3.5,13],[3.5,8],[4.5,5],[5.5,3],[7.5,1],[9.5,0]]]},"D":{"w":22,"g":[[[5,21],[5,0]],[[6,21],[6,0]],[[2,21],[12,21],[15,20],[17,18],[18,16],[19,13],[19,8],[18,5],[17,3],[15,1],[12,0],[2,0]],[[12,21],[14,20],[16,18],[17,16],[18,13],[18,8],[17,5],[16,3],[14,1],[12,0]]]},"E":{"w":21,"g":[[[4.5,21],[4.5,0]],[[5.5,21],[5.5,0]],[[11.5,15],[11.5,7]],[[1.5,21],[17.5,21],[17.5,15],[16.5,21]],[[5.5,11],[11.5,11]],[[1.5,0],[17.5,0],[17.5,6],[16.5,0]]]},"F":{"w":20,"g":[[[4,21],[4,0]],[[5,21],[5,0]],[[11,15],[11,7]],[[1,21],[17,21],[17,15],[16,21]],[[5,11],[11,11]],[[1,0],[8,0]]]},"G":{"w":23,"g":[[[17.5,18],[18.5,15],[18.5,21],[17.5,18],[15.5,20],[12.5,21],[10.5,21],[7.5,20],[5.5,18],[4.5,16],[3.5,13],[3.5,8],[4.5,5],[5.5,3],[7.5,1],[10.5,0],[12.5,0],[15.5,1],[17.5,3]],[[10.5,21],[8.5,20],[6.5,18],[5.5,16],[4.5,13],[4.5,8],[5.5,5],[6.5,3],[8.5,1],[10.5,0]],[[17.5,8],[17.5,0]],[[18.5,8],[18.5,0]],[[14.5,8],[21.5,8]]]},"H":{"w":24,"g":[[[5,21],[5,0]],[[6,21],[6,0]],[[18,21],[18,0]],[[19,21],[19,0]],[[2,21],[9,21]],[[15,21],[22,21]],[[6,11],[18,11]],[[2,0],[9,0]],[[15,0],[22,0]]]},"I":{"w":11,"g":[[[5.5,21],[5.5,0]],[[6.5,21],[6.5,0]],[[2.5,21],[9.5,21]],[[2.5,0],[9.5,0]]]},"J":{"w":15,"g":[[[10.5,21],[10.5,4],[9.5,1],[7.5,0],[5.5,0],[3.5,1],[2.5,3],[2.5,5],[3.5,6],[4.5,5],[3.5,4]],[[9.5,21],[9.5,4],[8.5,1],[7.5,0]],[[6.5,21],[13.5,21]]]},"K":{"w":22,"g":[[[4,21],[4,0]],[[5,21],[5,0]],[[18,21],[5,8]],[[10,12],[18,0]],[[9,12],[17,0]],[[1,21],[8,21]],[[14,21],[20,21]],[[1,0],[8,0]],[[14,0],[20,0]]]},"L":{"w":18,"g":[[[5,21],[5,0]],[[6,21],[6,0]],[[2,21],[9,21]],[[2,0],[17,0],[17,6],[16,0]]]},"M":{"w":25,"g":[[[5.5,21],[5.5,0]],[[6.5,21],[12.5,3]],[[5.5,21],[12.5,0]],[[19.5,21],[12.5,0]],[[19.5,21],[19.5,0]],[[20.5,21],[20.5,0]],[[2.5,21],[6.5,21]],[[19.5,21],[23.5,21]],[[2.5,0],[8.5,0]],[[16.5,0],[23.5,0]]]},"N":{"w":23,"g":[[[5.5,21],[5.5,0]],[[6.5,21],[18.5,2]],[[6.5,19],[18.5,0]],[[18.5,21],[18.5,0]],[[2.5,21],[6.5,21]],[[15.5,21],[21.5,21]],[[2.5,0],[8.5,0]]]},"O":{"w":22,"g":[[[10,21],[7,20],[5,18],[4,16],[3,12],[3,9],[4,5],[5,3],[7,1],[10,0],[12,0],[15,1],[17,3],[18,5],[19,9],[19,12],[18,16],[17,18],[15,20],[12,21],[10,21]],[[10,21],[8,20],[6,18],[5,16],[4,12],[4,9],[5,5],[6,3],[8,1],[10,0]],[[12,0],[14,1],[16,3],[17,5],[18,9],[18,12],[17,16],[16,18],[14,20],[12,21]]]},"P":{"w":22,"g":[[[5,21],[5,0]],[[6,21],[6,0]],[[2,21],[14,21],[17,20],[18,19],[19,17],[19,14],[18,12],[17,11],[14,10],[6,10]],[[14,21],[16,20],[17,19],[18,17],[18,14],[17,12],[16,11],[14,10]],[[2,0],[9,0]]]},"Q":{"w":22,"g":[[[10,21],[7,20],[5,18],[4,16],[3,12],[3,9],[4,5],[5,3],[7,1],[10,0],[12,0],[15,1],[17,3],[18,5],[19,9],[19,12],[18,16],[17,18],[15,20],[12,21],[10,21]],[[10,21],[8,20],[6,18],[5,16],[4,12],[4,9],[5,5],[6,3],[8,1],[10,0]],[[12,0],[14,1],[16,3],[17,5],[18,9],[18,12],[17,16],[16,18],[14,20],[12,21]],[[7,2],[7,3],[8,5],[10,6],[11,6],[13,5],[14,3],[15,-4],[16,-5],[18,-5],[19,-3],[19,-2]],[[14,3],[15,-1],[16,-3],[17,-4],[18,-4],[19,-3]]]},"R":{"w":22,"g":[[[5,21],[5,0]],[[6,21],[6,0]],[[2,21],[14,21],[17,20],[18,19],[19,17],[19,15],[18,13],[17,12],[14,11],[6,11]],[[14,21],[16,20],[17,19],[18,17],[18,15],[17,13],[16,12],[14,11]],[[2,0],[9,0]],[[11,11],[13,10],[14,9],[17,2],[18,1],[19,1],[20,2]],[[13,10],[14,8],[16,1],[17,0],[19,0],[20,2],[20,3]]]},"S":{"w":20,"g":[[[16,18],[17,21],[17,15],[16,18],[14,20],[11,21],[8,21],[5,20],[3,18],[3,16],[4,14],[5,13],[7,12],[13,10],[15,9],[17,7]],[[3,16],[5,14],[7,13],[13,11],[15,10],[16,9],[17,7],[17,3],[15,1],[12,0],[9,0],[6,1],[4,3],[3,6],[3,0],[4,3]]]},"T":{"w":19,"g":[[[9.5,21],[9.5,0]],[[10.5,21],[10.5,0]],[[3.5,21],[2.5,15],[2.5,21],[17.5,21],[17.5,15],[16.5,21]],[[6.5,0],[13.5,0]]]},"U":{"w":24,"g":[[[5,21],[5,6],[6,3],[8,1],[11,0],[13,0],[16,1],[18,3],[19,6],[19,21]],[[6,21],[6,6],[7,3],[9,1],[11,0]],[[2,21],[9,21]],[[16,21],[22,21]]]},"V":{"w":20,"g":[[[3,21],[10,0]],[[4,21],[10,3]],[[17,21],[10,0]],[[1,21],[7,21]],[[13,21],[19,21]]]},"W":{"w":24,"g":[[[4,21],[8,0]],[[5,21],[8,5]],[[12,21],[8,0]],[[12,21],[16,0]],[[13,21],[16,5]],[[20,21],[16,0]],[[1,21],[8,21]],[[17,21],[23,21]]]},"X":{"w":20,"g":[[[3,21],[16,0]],[[4,21],[17,0]],[[17,21],[3,0]],[[1,21],[7,21]],[[13,21],[19,21]],[[1,0],[7,0]],[[13,0],[19,0]]]},"Y":{"w":21,"g":[[[3.5,21],[10.5,10],[10.5,0]],[[4.5,21],[11.5,10],[11.5,0]],[[18.5,21],[11.5,10]],[[1.5,21],[7.5,21]],[[14.5,21],[20.5,21]],[[7.5,0],[14.5,0]]]},"Z":{"w":20,"g":[[[16,21],[3,0]],[[17,21],[4,0]],[[4,21],[3,15],[3,21],[17,21]],[[3,0],[17,0],[17,6],[16,0]]]},"[":{"w":14,"g":[[[4,25],[4,-7]],[[5,25],[5,-7]],[[4,25],[11,25]],[[4,-7],[11,-7]]]},"\\":{"w":14,"g":[[[0,21],[14,-3]]]},"]":{"w":14,"g":[[[9,25],[9,-7]],[[10,25],[10,-7]],[[3,25],[10,25]],[[3,-7],[10,-7]]]},"^":{"w":16,"g":[[[6,15],[8,18],[10,15]],[[3,12],[8,17],[13,12]],[[8,17],[8,0]]]},"_":{"w":16,"g":[[[0,-2],[16,-2]]]},"`":{"w":10,"g":[[[6,21],[5,20],[4,18],[4,16],[5,15],[6,16],[5,17]]]},"a":{"w":20,"g":[[[6,12],[6,11],[5,11],[5,12],[6,13],[8,14],[12,14],[14,13],[15,12],[16,10],[16,3],[17,1],[18,0]],[[15,12],[15,3],[16,1],[18,0],[19,0]],[[15,10],[14,9],[8,8],[5,7],[4,5],[4,3],[5,1],[8,0],[11,0],[13,1],[15,3]],[[8,8],[6,7],[5,5],[5,3],[6,1],[8,0]]]},"b":{"w":21,"g":[[[4.5,21],[4.5,0]],[[5.5,21],[5.5,0]],[[5.5,11],[7.5,13],[9.5,14],[11.5,14],[14.5,13],[16.5,11],[17.5,8],[17.5,6],[16.5,3],[14.5,1],[11.5,0],[9.5,0],[7.5,1],[5.5,3]],[[11.5,14],[13.5,13],[15.5,11],[16.5,8],[16.5,6],[15.5,3],[13.5,1],[11.5,0]],[[1.5,21],[5.5,21]]]},"c":{"w":19,"g":[[[14.5,11],[13.5,10],[14.5,9],[15.5,10],[15.5,11],[13.5,13],[11.5,14],[8.5,14],[5.5,13],[3.5,11],[2.5,8],[2.5,6],[3.5,3],[5.5,1],[8.5,0],[10.5,0],[13.5,1],[15.5,3]],[[8.5,14],[6.5,13],[4.5,11],[3.5,8],[3.5,6],[4.5,3],[6.5,1],[8.5,0]]]},"d":{"w":21,"g":[[[15.5,21],[15.5,0]],[[16.5,21],[16.5,0]],[[15.5,11],[13.5,13],[11.5,14],[9.5,14],[6.5,13],[4.5,11],[3.5,8],[3.5,6],[4.5,3],[6.5,1],[9.5,0],[11.5,0],[13.5,1],[15.5,3]],[[9.5,14],[7.5,13],[5.5,11],[4.5,8],[4.5,6],[5.5,3],[7.5,1],[9.5,0]],[[12.5,21],[16.5,21]],[[15.5,0],[19.5,0]]]},"e":{"w":19,"g":[[[3.5,8],[15.5,8],[15.5,10],[14.5,12],[13.5,13],[11.5,14],[8.5,14],[5.5,13],[3.5,11],[2.5,8],[2.5,6],[3.5,3],[5.5,1],[8.5,0],[10.5,0],[13.5,1],[15.5,3]],[[14.5,8],[14.5,11],[13.5,13]],[[8.5,14],[6.5,13],[4.5,11],[3.5,8],[3.5,6],[4.5,3],[6.5,1],[8.5,0]]]},"f":{"w":13,"g":[[[9.5,20],[8.5,19],[9.5,18],[10.5,19],[10.5,20],[9.5,21],[7.5,21],[5.5,20],[4.5,18],[4.5,0]],[[7.5,21],[6.5,20],[5.5,18],[5.5,0]],[[1.5,14],[9.5,14]],[[1.5,0],[8.5,0]]]},"g":{"w":19,"g":[[[8.5,14],[6.5,13],[5.5,12],[4.5,10],[4.5,8],[5.5,6],[6.5,5],[8.5,4],[10.5,4],[12.5,5],[13.5,6],[14.5,8],[14.5,10],[13.5,12],[12.5,13],[10.5,14],[8.5,14]],[[6.5,13],[5.5,11],[5.5,7],[6.5,5]],[[12.5,5],[13.5,7],[13.5,11],[12.5,13]],[[13.5,12],[14.5,13],[16.5,14],[16.5,13],[14.5,13]],[[5.5,6],[4.5,5],[3.5,3],[3.5,2],[4.5,0],[7.5,-1],[12.5,-1],[15.5,-2],[16.5,-3]],[[3.5,2],[4.5,1],[7.5,0],[12.5,0],[15.5,-1],[16.5,-3],[16.5,-4],[15.5,-6],[12.5,-7],[6.5,-7],[3.5,-6],[2.5,-4],[2.5,-3],[3.5,-1],[6.5,0]]]},"h":{"w":22,"g":[[[5,21],[5,0]],[[6,21],[6,0]],[[6,11],[8,13],[11,14],[13,14],[16,13],[17,11],[17,0]],[[13,14],[15,13],[16,11],[16,0]],[[2,21],[6,21]],[[2,0],[9,0]],[[13,0],[20,0]]]},"i":{"w":11,"g":[[[5.5,21],[4.5,20],[5.5,19],[6.5,20],[5.5,21]],[[5.5,14],[5.5,0]],[[6.5,14],[6.5,0]],[[2.5,14],[6.5,14]],[[2.5,0],[9.5,0]]]},"j":{"w":11,"g":[[[6.5,21],[5.5,20],[6.5,19],[7.5,20],[6.5,21]],[[7.5,14],[7.5,-4],[6.5,-6],[4.5,-7],[2.5,-7],[1.5,-6],[1.5,-5],[2.5,-4],[3.5,-5],[2.5,-6]],[[6.5,14],[6.5,-4],[5.5,-6],[4.5,-7]],[[3.5,14],[7.5,14]]]},"k":{"w":21,"g":[[[4.5,21],[4.5,0]],[[5.5,21],[5.5,0]],[[15.5,14],[5.5,4]],[[10.5,8],[16.5,0]],[[9.5,8],[15.5,0]],[[1.5,21],[5.5,21]],[[12.5,14],[18.5,14]],[[1.5,0],[8.5,0]],[[12.5,0],[18.5,0]]]},"l":{"w":11,"g":[[[5.5,21],[5.5,0]],[[6.5,21],[6.5,0]],[[2.5,21],[6.5,21]],[[2.5,0],[9.5,0]]]},"m":{"w":33,"g":[[[5.5,14],[5.5,0]],[[6.5,14],[6.5,0]],[[6.5,11],[8.5,13],[11.5,14],[13.5,14],[16.5,13],[17.5,11],[17.5,0]],[[13.5,14],[15.5,13],[16.5,11],[16.5,0]],[[17.5,11],[19.5,13],[22.5,14],[24.5,14],[27.5,13],[28.5,11],[28.5,0]],[[24.5,14],[26.5,13],[27.5,11],[27.5,0]],[[2.5,14],[6.5,14]],[[2.5,0],[9.5,0]],[[13.5,0],[20.5,0]],[[24.5,0],[31.5,0]]]},"n":{"w":22,"g":[[[5,14],[5,0]],[[6,14],[6,0]],[[6,11],[8,13],[11,14],[13,14],[16,13],[17,11],[17,0]],[[13,14],[15,13],[16,11],[16,0]],[[2,14],[6,14]],[[2,0],[9,0]],[[13,0],[20,0]]]},"o":{"w":20,"g":[[[9,14],[6,13],[4,11],[3,8],[3,6],[4,3],[6,1],[9,0],[11,0],[14,1],[16,3],[17,6],[17,8],[16,11],[14,13],[11,14],[9,14]],[[9,14],[7,13],[5,11],[4,8],[4,6],[5,3],[7,1],[9,0]],[[11,0],[13,1],[15,3],[16,6],[16,8],[15,11],[13,13],[11,14]]]},"p":{"w":21,"g":[[[4.5,14],[4.5,-7]],[[5.5,14],[5.5,-7]],[[5.5,11],[7.5,13],[9.5,14],[11.5,14],[14.5,13],[16.5,11],[17.5,8],[17.5,6],[16.5,3],[14.5,1],[11.5,0],[9.5,0],[7.5,1],[5.5,3]],[[11.5,14],[13.5,13],[15.5,11],[16.5,8],[16.5,6],[15.5,3],[13.5,1],[11.5,0]],[[1.5,14],[5.5,14]],[[1.5,-7],[8.5,-7]]]},"q":{"w":20,"g":[[[15,14],[15,-7]],[[16,14],[16,-7]],[[15,11],[13,13],[11,14],[9,14],[6,13],[4,11],[3,8],[3,6],[4,3],[6,1],[9,0],[11,0],[13,1],[15,3]],[[9,14],[7,13],[5,11],[4,8],[4,6],[5,3],[7,1],[9,0]],[[12,-7],[19,-7]]]},"r":{"w":17,"g":[[[4.5,14],[4.5,0]],[[5.5,14],[5.5,0]],[[5.5,8],[6.5,11],[8.5,13],[10.5,14],[13.5,14],[14.5,13],[14.5,12],[13.5,11],[12.5,12],[13.5,13]],[[1.5,14],[5.5,14]],[[1.5,0],[8.5,0]]]},"s":{"w":17,"g":[[[13.5,12],[14.5,14],[14.5,10],[13.5,12],[12.5,13],[10.5,14],[6.5,14],[4.5,13],[3.5,12],[3.5,10],[4.5,9],[6.5,8],[11.5,6],[13.5,5],[14.5,4]],[[3.5,11],[4.5,10],[6.5,9],[11.5,7],[13.5,6],[14.5,5],[14.5,2],[13.5,1],[11.5,0],[7.5,0],[5.5,1],[4.5,2],[3.5,4],[3.5,0],[4.5,2]]]},"t":{"w":15,"g":[[[5.5,21],[5.5,4],[6.5,1],[8.5,0],[10.5,0],[12.5,1],[13.5,3]],[[6.5,21],[6.5,4],[7.5,1],[8.5,0]],[[2.5,14],[10.5,14]]]},"u":{"w":22,"g":[[[5,14],[5,3],[6,1],[9,0],[11,0],[14,1],[16,3]],[[6,14],[6,3],[7,1],[9,0]],[[16,14],[16,0]],[[17,14],[17,0]],[[2,14],[6,14]],[[13,14],[17,14]],[[16,0],[20,0]]]},"v":{"w":18,"g":[[[3,14],[9,0]],[[4,14],[9,2]],[[15,14],[9,0]],[[1,14],[7,14]],[[11,14],[17,14]]]},"w":{"w":24,"g":[[[4,14],[8,0]],[[5,14],[8,3]],[[12,14],[8,0]],[[12,14],[16,0]],[[13,14],[16,3]],[[20,14],[16,0]],[[1,14],[8,14]],[[17,14],[23,14]]]},"x":{"w":20,"g":[[[4,14],[15,0]],[[5,14],[16,0]],[[16,14],[4,0]],[[2,14],[8,14]],[[12,14],[18,14]],[[2,0],[8,0]],[[12,0],[18,0]]]},"y":{"w":19,"g":[[[3.5,14],[9.5,0]],[[4.5,14],[9.5,2]],[[15.5,14],[9.5,0],[7.5,-4],[5.5,-6],[3.5,-7],[2.5,-7],[1.5,-6],[2.5,-5],[3.5,-6]],[[1.5,14],[7.5,14]],[[11.5,14],[17.5,14]]]},"z":{"w":18,"g":[[[14,14],[3,0]],[[15,14],[4,0]],[[4,14],[3,10],[3,14],[15,14]],[[3,0],[15,0],[15,4],[14,0]]]},"{":{"w":14,"g":[[[9,25],[7,24],[6,23],[5,21],[5,19],[6,17],[7,16],[8,14],[8,12],[6,10]],[[7,24],[6,22],[6,20],[7,18],[8,17],[9,15],[9,13],[8,11],[4,9],[8,7],[9,5],[9,3],[8,1],[7,0],[6,-2],[6,-4],[7,-6]],[[6,8],[8,6],[8,4],[7,2],[6,1],[5,-1],[5,-3],[6,-5],[7,-6],[9,-7]]]},"|":{"w":8,"g":[[[4,25],[4,-7]]]},"}":{"w":14,"g":[[[5,25],[7,24],[8,23],[9,21],[9,19],[8,17],[7,16],[6,14],[6,12],[8,10]],[[7,24],[8,22],[8,20],[7,18],[6,17],[5,15],[5,13],[6,11],[10,9],[6,7],[5,5],[5,3],[6,1],[7,0],[8,-2],[8,-4],[7,-6]],[[8,8],[6,6],[6,4],[7,2],[8,1],[9,-1],[9,-3],[8,-5],[7,-6],[5,-7]]]},"~":{"w":24,"g":[[[3,6],[3,8],[4,11],[6,12],[8,12],[10,11],[14,8],[16,7],[18,7],[20,8],[21,10]],[[3,8],[4,10],[6,11],[8,11],[10,10],[14,7],[16,6],[18,6],[20,7],[21,10],[21,12]]]},"":{"w":14,"g":[[[6,21],[4,20],[3,18],[3,16],[4,14],[6,13],[8,13],[10,14],[11,16],[11,18],[10,20],[8,21],[6,21]]]}}

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
  return {c:color, r:Math.floor(radius), a:Math.floor(angle), b:0}; //[(color << 13) + Math.floor(radius), Math.floor(angle)];
}

function calcPattern(clr, str, x, y, size)
{
  var pattern = [];
  var bx = x, by = y, kx = size, ky = size;
  var lx, ly;
  for (var i in str)
  { 
    var l = str[i];
    if (l == " ")
    {
      bx += 20*kx;
      continue;
    }          
    var symbol = font[str[i]].g;
    for (var j in symbol)
    {
      var symbolpath = symbol[j];
      for (var k=0; k<symbolpath.length; k++)
      {
        var x = symbolpath[k][0];
        var y = symbolpath[k][1];
        lx = bx+x*kx;
        ly = by+y*ky;
        pattern = pattern.concat(cartesian(k==0 ? 0 : clr, bx+x*kx, by-y*ky));
      }
    }
    bx += font[str[i]].w*kx;
  }
  pattern = pattern.concat(cartesian(0, lx, lx)).concat(cartesian(0, x, y));
  return pattern;
}

function dmx(i)
{
  var d = new Array(34).fill(0);
  d[0] = 1;
  d[3] = i;
  return d;
}

var data = {
  patternsCount:4,
  sceneItemListCount:4,
  channelListCount:34,
  scenes:[
    {playTime:2000, relationValue:0, channels:dmx(0), data: calcPattern(4, "Ahoj!", -1500, -100, 10)},
    {playTime:2000, relationValue:0, channels:dmx(1), data: calcPattern(1, "toto", -1500, -100, 10)},
    {playTime:2000, relationValue:0, channels:dmx(2), data: calcPattern(1, "je", -1500, -100, 10)},
    {playTime:2000, relationValue:0, channels:dmx(3), data: calcPattern(5, "pokus", -1500, -100, 10)},
  ]
};

var writer = new TF1Writer();
writer.Save("test.tf1", data);