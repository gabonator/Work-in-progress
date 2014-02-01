<?
	$ip = $_SERVER["REMOTE_ADDR"];
	$mac = isset($_COOKIE["_boardId"]) ? $_COOKIE["_boardId"] : $ip; //"deadbeeffeed"; // TODO: ziskat z devicu a potom vymazat nech to neloguje
	$type = isset($_COOKIE["_boardType"]) ? $_COOKIE["_boardType"] : "Unknown";
	$platform = isset($_COOKIE["_boardPlatform"]) ? $_COOKIE["_boardPlatform"] : "Unknown";
	$ts = time();

//	file_put_contents("devices/".$mac.".dbg", print_r($_SERVER, true)."\n".print_r($_POST, true)."\n".print_r($_GET, true)."\n".print_r($_COOKIE, true));

  $transfer = "";
	$types = "";
	$rec = "";
	foreach ($_GET as $k => $v)
	{
		if ( $rec != "" )
			$rec .= ",";
		$rec .= $k.":\"".$v."\"";
		$transfer .= $k."=".$v."&";
	}
	foreach ($_POST as $k => $v)
	{
		if ($k == "dummy" )
      continue;
//		if ($k == "ow_280cd781040000a4")
//			$k = "ow_purple";
		if ( $rec != "" )
    {
			$rec .= ",";
			$types .= ",";
    }
		$rec .= $k.":\"".$v."\"";
    $types .= $k;
		$transfer .= $k."=".$v."&";
	}

	$rec = "add({timestamp:".$ts.", time:\"".getTs()."\", ip:\"".$ip."\", args:{".$rec."}});\n";

	$f = fopen("data/".getCurrent(), "a");
	fwrite($f, $rec);
	//echo $rec;
	fclose($f);

	$f = fopen("devices/".$mac.".txt", "w");
	fwrite($f, "addDevice({ip:\"".$ip."\", mac:\"".$mac."\", type:\"".$type."\", platform:\"".$platform."\", last:".$ts.", sensors:\"".$types."\"});\n");
	fclose($f);

	$f = fopen("devices/".$mac.".last", "w");
	fwrite($f, $rec);
	fclose($f);


	$relay = "http://agro.valky.eu/sklenik/remote.php";
	echo(file($relay."?".$transfer."mac=".$mac));

	echo("Ok.");

  function getCurrent()
  {
    return date("Y-m-d").".txt";
  }
  function getTs()
  {
    return date("Y-m-d H:i:s");
  }

?>