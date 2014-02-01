<?
//	$from = isset($_GET["from"]) ? $_GET["from"] : "0000000000";
//add({timestamp:1387657558, time:"2013-12-21 21:25:58", ip:"192.168.1.50", args:{ow_green:"20.50",ow_yellow:"20.62",ow_black:"20.06",ow_red:"20.62",dht11_temp:"21",dht11_hum:"21",light:"1019",bmp085_baro:"101.819",bmp085_temp:"18.91"}});

/*
	if ( strlen($from) != 1 )
	{
		$from = "0000000000";
	}
*/
  if ( !isset($day) )
	  $day = $_GET["day"];

  $storage = array();
  $range = array();

  function JsonGetArray($json, $id)
  {
    $result = array();

    $starti = strpos($json, $id.":{");
		$endi = strpos($json, "}");
		if ( $starti === FALSE || $endi === FALSE )
      return $result;

		$starti += strlen($id)+2;
    if ( $endi <= $starti )
      return $result;

		$arrstr = substr($json, $starti, $endi - $starti);
		$arr = explode(",", $arrstr);
		foreach ($arr as $assign)
    {
      $delimi = strpos($assign, ":");
      $key = substr($assign, 0, $delimi);
      $value = substr($assign, $delimi+2, strlen($assign)-$delimi-3);
      $result[$key] = $value;
    }    
    return $result;
  }
  function JsonGetAttr($json, $id)
  {
    $starti = strpos($json, $id.":");
		$endi = strpos($json, ",");
		if ( $starti === FALSE || $endi === FALSE )
      return "";
		$starti += strlen($id)+1;
		if ( $endi <= $starti )
      return "";
		$result = substr($json, $starti, $endi - $starti);
    return $result;
  }

  function StorageAdd($ts, $key, $value)
  {
    global $storage;

    $ts = intval($ts);

    if ( count($storage) == 0 )
    {
      $storage["ts"] = array();
    }
    $n = count($storage["ts"]);
    if ( $n == 0 || $storage["ts"][$n-1] < $ts )
	    $storage["ts"][$n++] = $ts;

    if ( !array_key_exists($key, $storage) )
      $storage[$key] = array();

    for ($i = sizeof($storage[$key]); $i < $n-1; $i++)
      $storage[$key][$i] = NAN;

    $storage[$key][$n-1] = $value;
  }

	function CheckRange($key, $value)
  {
    global $range;
    if ( is_nan($value) )
      return;

    if ( !array_key_exists( $key, $range ) )
    {
      $range[$key] = array();
      $range[$key]["min"] = $value;
      $range[$key]["max"] = $value;
      $range[$key]["avg"] = 0;
      $range[$key]["cnt"] = 0;
    }

    if ( $value < $range[$key]["min"] )
      $range[$key]["min"] = $value;
    if ( $value > $range[$key]["max"] )
      $range[$key]["max"] = $value;
    $range[$key]["avg"] += $value;
    $range[$key]["cnt"] ++;
  }

  function FinishRange()
  {
    global $range;
		foreach ($range as $key => $value)
		  $range[$key]["avg"] = round($range[$key]["avg"]/$range[$key]["cnt"], 2);
  }

	function Simplify($input, $interval)
  {
    $result = array();
    $last = -1;
    $index = 0;

    $counts = array();
		foreach ($input as $key => $value)
		  $counts[$key] = 0;
		foreach ($input as $key => $value)
      $result[$key] = array();

    for ( $i = 0; $i < count($input["ts"]); $i++ )
    {
      $ts = $input["ts"][$i]/60;
      $minute = ($ts/60)%60;
      if ( $last == -1 )
      {
        $last = $minute;
        $last -= $last % $interval;
      }

			foreach ($input as $key => $array)
      {
        $ivalue = $i < count($array) ? $array[$i] : NAN;
        if ( is_string($ivalue) )
          $ivalue = floatval($array[$i]);
        if ( is_nan( $ivalue ) )
          continue;

        CheckRange( $key, $ivalue );

				$counts[$key]++;
  	    $result[$key][$index] += $ivalue;
      }

			// inrange?
			$inrange = $ts < $last+$interval;
			if (!$inrange)
      {
				foreach ($input as $key => $array)
        {
          if ( $counts[$key] == 0 )
            $result[$key][$index] = NAN;
          else
    		    $result[$key][$index] /= $counts[$key];
  		    $counts[$key] = 0;
          if ( $key == "ts" )
	  		    $result[$key][$index] = floor($result[$key][$index]);
          else
	  		    $result[$key][$index] = round($result[$key][$index], 3);
        }

			  $last = $ts;
			  $index++;
      }
    }

			foreach ($input as $key => $array)
			{
        if ( $counts[$key] < 1 )
          continue;

 		    $result[$key][$index] /= $counts[$key];
        if ( $key == "ts" )
	 		    $result[$key][$index] = floor($result[$key][$index]);
        else
  		    $result[$key][$index] = round($result[$key][$index], 3);
			}
		FinishRange();
    return $result;
  }

	function WriteStorage($storage, $fname, $id)
  {
    global $range;
    // Export!
  	$out = "";
    $out.= "addmulti({\n";
    $out.= "  id:\"".$id."\",\n";
  	foreach ($storage as $key => $array)
    {
      $out.= "  ".$key.":{stat:{min:".round($range[$key]["min"], 3).", max:".round($range[$key]["max"], 3).", avg:".round($range[$key]["avg"], 3)."}, data:\n";
      $out.= "    [";
      for ( $i = 0; $i < count($array); $i++ )
      {
        if ( $i > 0 )
          $out .= ", ";
        $out.= $array[$i];
      }
      $out.= "]\n";
      $out.= "  },\n";
    }
    $out.= "});\n";
    file_put_contents($fname, $out);
  }

	function WriteStats($storage, $fname, $id)
  {
    global $range;
    // Export!
  	$out = "";
    $out.= "addmulti({\n";
    $out.= "  id:\"".$id."\",\n";
  	foreach ($storage as $key => $array)
      $out.= "  ".$key.":{stat:{min:".round($range[$key]["min"], 3).", max:".round($range[$key]["max"], 3).", avg:".round($range[$key]["avg"], 3)."}},\n";
    $out.= "});\n";
    file_put_contents($fname, $out);
  }


  $key = "add({timestamp:";
  $keyl = strlen($key);
  $f = fopen("data/".$day.".txt", "r");
	while (!feof($f))
	{
		$line = fgets( $f );
		if (strlen($line) < 5)
		  continue;

		$line = substr($line, 4, strlen($line)-2);
		$args = JsonGetArray($line, "args");
    $ts = JsonGetAttr($line, "timestamp");

    if ( $ts == "" || sizeof($args) == 0 )
      continue;
		foreach ($args as $arg => $value)
      StorageAdd($ts, $arg, $value);
	}

  $simplified = Simplify($storage, 30);
	WriteStorage( $simplified, "cache/".$day."_30.txt", $_GET["day"]);
	WriteStats( $simplified, "cache/".$day."_stat.txt", $_GET["day"]);

	fclose($f);
?>