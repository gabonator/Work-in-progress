
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
  chicken.onLoad();
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
		case tvKey.KEY_RETURN:
		case tvKey.KEY_PANEL_RETURN:
			widgetAPI.sendReturnEvent();
      document.getElementById("welcome").innerHTML = "KEY_PANEL_RETURN";
			break;
		case tvKey.KEY_LEFT:
      document.getElementById("welcome").innerHTML = "LEFT";
      chicken.move(-1, 0);
			break;
		case tvKey.KEY_RIGHT:
      document.getElementById("welcome").innerHTML = "RIGHT";
      chicken.move(+1, 0);
			break;
		case tvKey.KEY_UP:
      document.getElementById("welcome").innerHTML = "UP";
      chicken.move(0, -1);
			break;
		case tvKey.KEY_DOWN:
      document.getElementById("welcome").innerHTML = "DOWN";
      chicken.move(0, +1);
			break;
		case tvKey.KEY_ENTER:
		case tvKey.KEY_PANEL_ENTER:
      document.getElementById("welcome").innerHTML = "ENTER";
			break;
		default:
      document.getElementById("welcome").innerHTML = "KEY "+keyCode;
			break;
	}
};
