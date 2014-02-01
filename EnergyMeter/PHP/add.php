<?
	//error_reporting(E_ALL);
	$rec = "";
	foreach ($_GET as $k => $v)
	{
		if ( $rec != "" )
			$rec .= ",";
		$rec .= $k.":\"".$v."\"";
	}
  $lhash = calchash( $_SERVER["QUERY_STRING"] );
  $valid = $lhash == $_GET["hash"] ? "1" : "0";
	$rec = "add({ts:".time().", date:\"".getmDate()."\", time:\"".getmTime()."\", ip:\"".$_SERVER["REMOTE_ADDR"]."\", valid:".$valid.", args:{".$rec."}});\n";

	$f = fopen(getCurrent(), "a");
	fwrite($f, $rec);
	//echo $rec;
	fclose($f);
	echo("Ok.");

  function getCurrent()
  {
    return date("Y-m-d").".txt";
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

?>
Response: Helo!