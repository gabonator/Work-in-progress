sokoban = 
{
  surface:null,
  player:null,
  x:0,
  y:0,

  currentLevel:0,
  currentx:0,
  currenty:0,
  targetx:0,
  targety:0,

  history:[],

  // public
  onLoad:function()
  {
    var iDiv = document.createElement('div');
    iDiv.style.position = "absolute";
    iDiv.style.left = "-120px";
    iDiv.style.top = "220px";
    document.getElementsByTagName('body')[0].appendChild(iDiv);
    this.surface = iDiv;

    var iDiv = document.createElement('div');
    iDiv.style.position = "absolute";
    iDiv.style.width = "83px";
    iDiv.style.height = "84px";
    iDiv.style.background = "url(chicken.gif)";
    iDiv.style.display = "none";
    document.getElementsByTagName('body')[0].appendChild(iDiv);
    this.player = iDiv;
 
    this.loadLevel();
    this.updatePosition();
    this.copyPosition();
    this.getTimestamp();

    setInterval(function()
    {
      sokoban.convergePosition();
    }, 1000/30);
  },

  move:function(dx, dy)
  {
    var newobj = this.getmap(this.x + dx, this.y + dy);
    var advobj = this.getmap(this.x + dx*2, this.y + dy*2);

    if ( newobj != "." && newobj != "O" && this.isTooFar() )
      return;

    var logmove = {};
    if ( (newobj == "*" || newobj == "0") && (advobj == "." || advobj == "O" || advobj == "S") )
    {
      logmove = {action:(dx+2) + (dy+1)*3, ts:this.getTimestamp(), player:{x:this.x, y:this.y}, moves:[{x:this.x+dx, y:this.y+dy, t:newobj}, {x:this.x+dx*2, y:this.y+dy*2, t:advobj}]};
      this.setBlock(this.x + dx, this.y + dy, newobj == "*" ? "." : "O");
      this.setBlock(this.x + dx*2, this.y + dy*2, advobj == 'O' ? '0' : '*');
      var newobj = this.getmap(this.x + dx, this.y + dy);

      if ( this.hasFinished() )
      {
        this.history.push(logmove);
        this.report();
        this.nextLevel(+1);
        return;
      }
    } else
      logmove = {action:(dx+2) + (dy+1)*3, ts:this.getTimestamp(), player:{x:this.x, y:this.y}, moves:[]};

    if ( newobj != "." && newobj != "O" && newobj != "S" )
      return;
  
    this.history.push(logmove);
    this.x += dx;
    this.y += dy;
    this.updatePosition();
  },

  back:function()
  {
    if ( this.history.length == 0 )
      return;

    var logmove = this.history.pop();
    this.x = logmove.player.x;
    this.y = logmove.player.y;
    this.updatePosition();
 
    for (var i in logmove.moves)
      this.setBlock(logmove.moves[i].x, logmove.moves[i].y, logmove.moves[i].t);
  },

  getTimestamp:function()
  {
    if ( typeof(this.basetime) == "undefined" )
      this.basetime = (new Date()).getTime();

    return (new Date()).getTime() - this.basetime;
  },

  report:function()
  {
    var movelog = {file:"sokoban", level:this.currentLevel+1, nmoves:this.history.length, moves:[]};
    for ( var i in this.history )
    {
      movelog.moves.push(this.history[i].action);
      movelog.moves.push(this.history[i].ts);
    }

    var xmlHttp = new XMLHttpRequest();
    xmlHttp.open("POST", "http://api.valky.eu/log/");
    xmlHttp.setRequestHeader("Content-Type", "application/json;charset=UTF-8");
    xmlHttp.send(JSON.stringify(movelog));
  },

  go:function(dir)
  {
    this.nextLevel(dir);
  },

  // private
  isTooFar:function()
  {
    return Math.abs(this.currentx - this.targetx) > 5 ||
      Math.abs(this.currenty - this.targety) > 5;
  },

  nextLevel:function(dir)
  {
    this.currentLevel += dir;
    if ( this.currentLevel < 0 )
      this.currentLevel = 0;
    if ( this.currentLevel >= levels.length )
      this.currentLevel = levels.length - 1;

    this.loadLevel();
    this.updatePosition();
    this.copyPosition();
  },

  loadLevel:function()
  {
    this.player.style.display = "none";
    document.getElementById("welcome").innerHTML = "Sokoban, level " + (this.currentLevel+1); //navigator.userAgent;
    this.level = levels[this.currentLevel];
    this.surface.innerHTML = this.build();
    this.history = [];
    this.player.style.display = "";
  },

  hasFinished:function()
  {
    return this.level.join(",").indexOf("*") == -1;
  },

  copyPosition:function()
  {
    this.currentx = this.targetx;
    this.currenty = this.targety;
  },

  convergePosition:function()
  {
    this.currentx = this.currentx * 0.6 + this.targetx * 0.4;
    this.currenty = this.currenty * 0.6 + this.targety * 0.4;
    this.player.style.left = this.currentx.toFixed(1) + "px";
    this.player.style.top = this.currenty.toFixed(1) + "px";
  },

  setBlock:function(x, y, t)
  {
    var id = "blk_"+x+"_"+y+"_";
    var src = "free.gif";
    var flat = t == "." || t == "O" || t == "S";
    switch ( t )
    {
      case '.': src = "free.gif"; break;
      case '*': src = "block.gif"; break;
      case '0': src = "block1.gif"; break;
      case 'O': src = "dest.gif"; break;
    }

    document.getElementById(id + "b").style.display = flat ? "" : "none";
    document.getElementById(id + "t").style.display = flat ? "none" : "";
    document.getElementById(id + "l").style.display = flat ? "none" : "";
    document.getElementById(id + "r").style.display = flat ? "none" : "";
    document.getElementById(id + "b").src = src;
    document.getElementById(id + "t").src = src;
    document.getElementById(id + "l").src = src;
    document.getElementById(id + "r").src = src;
   
    this.setmap(x, y, t);
  },

  updatePosition:function()
  {
    var translate = 'scale(1, 0.5) rotate(-30deg) translate('+x*50+'px,'+y*50+'px)';

    var cosa = Math.cos(-30/180*Math.PI);
    var sina = Math.sin(-30/180*Math.PI);

    var x = this.x*50;
    var y = this.y*50;
    var nx = x * cosa - y * sina;
    var ny = x * sina + y * cosa;

    this. /*div.style.left*/ targetx = (-20 + -120 + nx); // + "px";
    this. /*div.style.top*/ targety = (-55 + 220 + ny*0.5); // + "px";


    var z = ((15-x)+y*16)*10 + 9;
    this.player.style.zIndex = z;
  },

  level: levels[0],

  getmap:function(x, y)
  {
    return this.level[y].charAt(x);
  },

  setmap:function(x, y, t)
  {
    this.level[y] = this.level[y].substr(0, x) + t + this.level[y].substr(x+1);
  },

  build:function()
  {
    var level = this.level;

    block = function(x, y, t)
    {
      var src = "free.gif";
      if ( t == '#' )
        src = "wall.gif";
      if ( t == '*' )
        src = "block.gif";
      if ( t == 'O' )
        src = "dest.gif";
      if ( t == '0' )
        src = "block1.gif";
      if ( t == 'S' )
      {
        sokoban.x = x;
        sokoban.y = y;
      }

      var translate = 'scale(1, 0.5) rotate(-30deg) translate('+x*50+'px,'+y*50+'px)';

      var z = ((15-x)+y*16)*10;
      var flat = t == "." || t == "O" || t == "S";
      var id = "blk_"+x+"_"+y+"_";
      var alpha = (0.4+y/16/2 - x/19/3).toFixed(2);

      return '' + 
        '<img id="'+id+'b" src="'+src+'" style="opacity:'+alpha+'; width:50px; height:50px; position:absolute; display:' + (!flat ? 'none' : '') + '; z-index:'+(z+0)+'; -webkit-transform: '+translate+'">' +
        '<img id="'+id+'t" src="'+src+'" style="width:50px; height:50px; position:absolute; display:' + (flat ? 'none' : '') + '; z-index:'+(z+4)+'; -webkit-transform: '+translate+' translate(10px, -20px)">' +
        '<img id="'+id+'r" src="'+src+'" style="width:50px; height:50px; position:absolute; display:' + (flat ? 'none' : '') + '; z-index:'+(z+2)+'; -webkit-transform: '+translate+' skewX(-30deg) translate(13px,15px) scale(1, 0.5)">' +
        '<img id="'+id+'l" src="'+src+'" style="width:50px; height:50px; position:absolute; display:' + (flat ? 'none' : '') + '; z-index:'+(z+1)+'; -webkit-transform: '+translate+' skewY(-60deg) translate(-20px,-45px) scale(0.25, 1)">';
    }

    var lvl = "";
    for (var y=0; y<16; y++)
      for (var x=0; x<19; x++) 
        lvl += block(x, y, this.getmap(x,y));

    return lvl;
  }
};