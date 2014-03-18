document.onkeyup   = function ( e ) { onKey( ( window.event ) ? event.keyCode : e.keyCode, 0 ); }
document.onkeydown = function ( e ) { onKey( ( window.event ) ? event.keyCode : e.keyCode, 1 ); }

function onKey( k, on )
{
  var index = -1;

  switch (k) 
  {
    case 37: index = 75; break; // left
    case 38: index = 72; break; // up
    case 39: index = 77; break; // right
    case 40: index = 80; break; // down
  }

  switch (String.fromCharCode(k))
  {
    case ' ': index = 57; break;
    case 'M': index = 50; break;
    case 'N': index = 49; break;
    case 'Q': index = 16; break;
    case 'Y': index = 21; break;
  }

  if ( index == -1 )
    return;

  _data[0x8e8a+index] = on;
}
