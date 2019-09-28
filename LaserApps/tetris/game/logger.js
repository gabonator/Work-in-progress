class Logger
{
  constructor()
  {
    this.last = [];
    this.log = [];

    var elem = document.createElement("br");
    document.documentElement.appendChild(elem);

    var elem = document.createElement("input");
    elem.type = "button";
    elem.value = "Start";
    elem.onclick = () => {this.log = []; this.last = []; this.enabled = true};
    document.documentElement.appendChild(elem);

    var elem = document.createElement("input");
    elem.type = "button";
    elem.value = "Stop";
    elem.onclick = () => {this.enabled = false};
    document.documentElement.appendChild(elem);

    var elem = document.createElement("input");
    elem.type = "button";
    elem.value = "Get log";
    elem.onclick = () => this.Dump();
    document.documentElement.appendChild(elem);
  }

  Process(data, frame)
  {
    if (!this.enabled)
      return;

    if (this.last.join("") == data.join(""))
      return;
    this.last = data;
    this.log.push({f:frame, d:data});
  }

  Dump()
  {     
    console.log(JSON.stringify(this.log));
  }
}

var logger = new Logger();