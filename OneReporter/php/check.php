<?
  function keyString($key, $str)
  {
    $aux = array();
    $aux[] = $key;
    for ($i = 0; $i < strlen($str); $i++)
      $aux[] = ord($str[$i]);
    return $aux;
  }
  function nokeyString($str)
  {
    $aux = array();
    for ($i = 0; $i < strlen($str); $i++)
      $aux[] = ord($str[$i]);
    return $aux;
  }

function crc16($crc, $data)
{
  $oddparity = array( 0, 1, 1, 0, 1, 0, 0, 1, 1, 0, 0, 1, 0, 1, 1, 0 );

  // Even though we're just copying a byte from the input,
  // we'll be doing 16-bit computation with it.
  $cdata = $data;
  $cdata = ($cdata ^ $crc) & 0xff;
  $crc >>= 8;

  if ($oddparity[$cdata & 0x0F] ^ $oddparity[$cdata >> 4])
    $crc ^= 0xC001;

  $cdata <<= 6;
  $crc ^= $cdata;
  $cdata <<= 1;
  $crc ^= $cdata;
  return $crc;
}

function buffer($preamble, $data)
{
  $out = array();

  $crc = 0;
  $len = count($data);
  $crc = crc16($crc, $len+2);  
  for ($i=0; $i<$len; $i++)
    $crc = crc16($crc, $data[$i]);

/*  
  $out[] = 0x0f;
  $out[] = 0xc0;
  $out[] = 0xaa;
*/

  for ($i = 0; $i < count($preamble); $i++)
    $out[] = $preamble[$i];
  $out[] = $len+2;
  for ($i = 0; $i<$len; $i++)
    $out[] = $data[$i];
  $out[] = $crc & 0xff;
  $out[] = $crc >> 8;
  return $out;
}

function toRequest($arr)
{
  $resp = "";
  for ($i=0; $i<count($arr); $i++)
  {
    $asc = $arr[$i];
    $ch = chr($asc); 
    if ( ctype_alnum($ch) || strpos(" .,+-?!:;_=", $ch) !== false ) 
      $resp .= $ch;                 
    else
      $resp .= sprintf("%%%02x", $asc);
  }
  return $resp;
}

//print_r(buffer(array(0x0f, 0xc0, 0xaa), array(ord('o'), ord('n'), ord(','), ord('5'), ord('s'))));
//print_r(toRequest(buffer(array(0x0f, 0xd1, 0xaa), array(0xd1, ord('A'), ord('h'), ord('o'), ord('j'), ord('!')))));
?>