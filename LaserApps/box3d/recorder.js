class Recorder
{
  constructor()
  {
    this.log = [];
  }
  record(renderData)
  {
    this.log.push(renderData);
  }
  finish()
  {
    console.log("module.exports="+JSON.stringify(this.log));
  }
}

var recorder = new Recorder();