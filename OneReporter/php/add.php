<?
  require "check.php";

	//error_reporting(E_ALL);
	$rec = "";
	foreach ($_GET as $k => $v)
	{
		if ( $rec != "" )
			$rec .= ",";
		$rec .= safe($k).":\"".safe($v)."\"";
	}
  $lhash = calchash( $_SERVER["QUERY_STRING"] );
  $valid = $lhash == $_GET["hash"] ? "1" : "0";
	$rec = "add({ts:".time().", date:\"".getmDate()."\", time:\"".getmTime()."\", ip:\"".$_SERVER["REMOTE_ADDR"]."\", valid:".$valid.", args:{".$rec."}});\n";

	$f = fopen(getCurrent(), "a");
	fwrite($f, $rec);
	//echo $rec;
	fclose($f);
/*
F
C0
AA
7
on,5s
5E
2A
-----

*/

  {
    $message = date("H:i m.d.Y");
    $req0 = toRequest(buffer(array(0x0f, 0xd1, 0xaa), array(0xdd, 0x01)));

    $req1 = toRequest(buffer(array(0x0f, 0xd1, 0xaa), keyString(0xd1, $message)));
    $message = "No sensor!"; //dev_2d4741422330399b

    if (isset($_GET["dev_2d4741422330399b"]))
    {
      $raw = $_GET["dev_2d4741422330399b"];
      $message = "T=".substr($raw, 3, 5)." H=".substr($raw, 9, 4);
    }

    $req2 = toRequest(buffer(array(0x0f, 0xd1, 0xaa), keyString(0xd2, $message)));
    $req3 = toRequest(buffer(array(0x0f, 0xc0, 0xaa), nokeyString("on,5s")));

    $resp = "";
    $resp .= "{";
    $resp .= "\"dev_2d474142233038c5\": \"".$req0."\"";
    $resp .= ",";
//    $resp .= "\"delay\":\"30\"";
//    $resp .= ",";
    $resp .= "\"dev_2d474142233038c5\": \"".$req1."\"";
    $resp .= ",";
//    $resp .= "\"delay\":\"30\"";
//    $resp .= ",";
    $resp .= "\"dev_2d474142233038c5\": \"".$req2."\"";
    $resp .= ",";
    $resp .= "\"dev_2d474142233235a9\": \"".$req3."\"";
    $resp .= "}";
/*
    $arrResp = explode( ",", $resp );
    for ($i = 0; $i < count($arrResp); $i++)
    {
      if ($i > 0)
      {
        usleep(1000 * 500);
        echo(",");
      }
      echo $arrResp[$i];
    }*/
    echo($resp);
    file_put_contents("debug", $resp);
//    echo("{\"dev_2d474142233038c5\": \"".$req2."\"}");
  }


//  echo("{\"dev_2d474142233235a9\": \"".$req."\"}");
//	echo("{ \"my_key\": \"my_value\", \"second\":\"xyz\"}");

  function getCurrent()
  {
    return "data/".date("Y-m-d").".txt";
  }
  function getTs()
  {
    return date("Y-m-d H:i:s");
  }
  function getmDate()
  {
    return date("Y-m-d");
  }
  function getmTime()
  {
    return date("H:i:s");
  }
	function calchash($str)
	{
		$str = substr($str, 0, -8)."00000000";
	  $crcbase = 0x8971A134;
		$crchead = "GAB28y4\\2013";
		$crc = $crcbase;

		for ($i=0; $i<strlen($crchead); $i++)
			$crc = crc_update($crc, ord($crchead[$i]));
		$crc = ~$crc;
		for ($i=0; $i<strlen($str); $i++)
			$crc = crc_update($crc, ord($str[$i]));
		$crc = ~$crc;

		return substr(sprintf("%08x", $crc), -8);
	}

	function crc_update($crc, $dat)
	{
  	$ctab = array( 0x00000000, 0x1db71064, 0x3b6e20c8, 0x26d930ac,
    0x76dc4190, 0x6b6b51f4, 0x4db26158, 0x5005713c,
    0xedb88320, 0xf00f9344, 0xd6d6a3e8, 0xcb61b38c,
    0x9b64c2b0, 0x86d3d2d4, 0xa00ae278, 0xbdbdf21c);

    $tbl_idx = $crc ^ ($dat >> (0 * 4));
    $crc = $ctab[$tbl_idx & 0x0f] ^ (($crc >> 4) & 0x0fffffff);
    $tbl_idx = $crc ^ ($dat >> (1 * 4));
    $crc = $ctab[ $tbl_idx & 0x0f] ^ (($crc >> 4) & 0x0fffffff);
    return $crc;
	}

  function safe($a)
  {
    $r = "";
    for ($i = 0; $i < strlen($a); $i++)
    {
      $c = $a[$i];
      if ( ($c >= 'a' && $c <= 'z') ||
           ($c >= 'A' && $c <= 'Z') ||
           ($c >= '0' && $c <= '9') ||
           ($c == ' ' || $c == '_' || $c == '#' || $c == '-' || $c == '+' || $c == ',' || $c == '.' || $c == '?' ) 
         )
      {
        $r .= $c;
      } else
      {
        $r .= sprintf("\\u%04x", ord($c));
      }
    }
    return $r;
  }
?>