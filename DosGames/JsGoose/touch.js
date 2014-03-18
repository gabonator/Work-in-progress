var msdown = false;

function mousepos(evt)
{
  var rect = can.getBoundingClientRect();
  var x = evt.clientX, y = evt.clientY;
  if ( evt.changedTouches ) 
  {
    x = evt.changedTouches[0].screenX*2; // iphone4
    y = evt.changedTouches[0].screenY*2;
  }
  x = (x - rect.left)*320/rect.width;
  y = (y - rect.top)*200/rect.height;
  return {x:Math.floor(x), y:Math.floor(y)};
}

window.ondevicemotion = function(event) {  
  var spd = event.accelerationIncludingGravity.y/3*30;
  if ( spd < -40 ) spd = -40;
  if ( spd > 40 ) spd = 40;

  _data[0x8e8a+75] = ( spd < -10 ) ? 1 : 0;
  _data[0x8e8a+77] = ( spd > +10 ) ? 1 : 0;
  _data[0x8e8a+72] = ( event.accelerationIncludingGravity.x < 3 ) ? 1 : 0;
  _data[0x8e8a+80] = ( event.accelerationIncludingGravity.x > 8 ) ? 1 : 0;

  spd = Math.floor(spd) & 0xffff;
  _data16set(0x952C, spd);

} 

canvas.addEventListener('mousemove', function(evt) 
{
  evt.preventDefault();
  var pos = mousepos(evt);
  if ( pos.y < 40 )
  {
    _data[0x8e8a+72] = 1;
    _data[0x8e8a+80] = 0;
  } else {
    _data[0x8e8a+72] = 0;
    _data[0x8e8a+80] = ( _data16get(0x952A) > 16 ) ? 1 : 0;
  }
  if ( !msdown /*&& pos.y > 168*/)
    _data16set(0x1B8F, pos.x-160+128);
}, false);

canvas.addEventListener('mousedown', _mousedown, false);
canvas.addEventListener('touchstart', _mousedown, false);
canvas.addEventListener('mouseup', _mouseup, false);
canvas.addEventListener('touchend', _mouseup, false);

function _mousedown(evt) 
{
  evt.preventDefault();
//  document.getElementById("dbg").value = "x=" + mousepos(evt).x + " y="+mousepos(evt).y;
  msdown = true;
  var pos = mousepos(evt);
  if ( pos.y > 168 )
    return;

  if ( pos.y > 128 && pos.y < 168 && pos.x < 80 )
    _data[0x8e8a+49] = 1;
  else
  if ( pos.y > 128 && pos.y < 168 && pos.x > 320-80 )
    _data[0x8e8a+50] = 1;
  else    
    _data[0x8e8a+57] = 1;
}

function _mouseup(evt)
{
  evt.preventDefault();
  msdown = false;
  _data[0x8e8a+49] = 0;
  _data[0x8e8a+50] = 0;
  _data[0x8e8a+57] = 0;
  _data[0x8e8a+72] = 0;
  _data[0x8e8a+80] = 0;
}
