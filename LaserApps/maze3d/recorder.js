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
    console.log("log="+JSON.stringify(this.log));
  }
}

var recorder = new Recorder();