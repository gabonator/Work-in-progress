chicken = 
{
  div:null,
  x:300,
  y:150,

  // public
  onLoad:function()
  {
    var iDiv = document.createElement('div');
    iDiv.style.position = "absolute";
    iDiv.style.width = "83px";
    iDiv.style.height = "84px";
    iDiv.style.background = "url(chicken.gif)";
    document.getElementsByTagName('body')[0].appendChild(iDiv);
    this.div = iDiv;
    this._updatePosition();
  },
  move:function(dx, dy)
  {
    this.x += dx * 20;
    this.y += dy * 20;
    this._updatePosition();
  },

  // private
  _updatePosition:function()
  {
    this.div.style.left = this.x + "px";
    this.div.style.top = this.y + "px";
  }
};
