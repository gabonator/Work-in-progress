var widgetAPI = new Common.API.Widget();
var tvKey = new Common.API.TVKeyValue();

var Main =
{
};

Main.onLoad = function()
{
	// Enable key event processing
	this.enableKeys();
	widgetAPI.sendReadyEvent();
  sokoban.onLoad();
};

Main.onUnload = function()
{

};

Main.enableKeys = function()
{
	document.getElementById("anchor").focus();
};

Main.keyDown = function()
{
	var keyCode = event.keyCode;

	switch(keyCode)
	{
		case tvKey.KEY_ENTER:
      sokoban.back();
      break;
		case tvKey.KEY_CH_UP:
      sokoban.go(+1);
      break;
		case tvKey.KEY_CH_DOWN:
      sokoban.go(-1);
      break;
		case tvKey.KEY_PANEL_RETURN:
			widgetAPI.sendReturnEvent();
			break;
		case tvKey.KEY_LEFT:
      sokoban.move(-1, 0);
			break;
		case tvKey.KEY_RIGHT:
      sokoban.move(+1, 0);
			break;
		case tvKey.KEY_UP:
      sokoban.move(0, -1);
			break;
		case tvKey.KEY_DOWN:
      sokoban.move(0, +1);
			break;
	}
};
