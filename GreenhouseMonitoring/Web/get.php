<?
  $q = isset($_GET["q"]) ? $_GET["q"] : "data";

	if ( $q == "data" )
	{
  	$from = isset($_GET["from"]) ? $_GET["from"] : "0000000000";

  	if ( strlen($from) != 10 )
  	{
  		$from = "0000000000";
  	}
    $key = "add({timestamp:";
    $keyl = strlen($key);
    $f = fopen("data/".$_GET["day"].".txt", "r");
  	while (!feof($f))
  	{
  		$line = fgets( $f );
  		$ts = strstr($line, $key);
  		if ( $ts )
  		{
  			$ts = ( substr($ts, $keyl, 10) );
  			if ( $ts > $from )
  				echo($line);
  		}
  	}
  	fclose($f);
  }

	if ( $q == "cached" )
	{
	  $day = $_GET["day"];
	  if ( !file_exists("cache/".$day."_30.txt") )
    {
      require "simplify.php";
    }
    readfile ("cache/".$day."_30.txt");
  }

	if ( $q == "stat" )
	{
	  $day = $_GET["day"];
	  if ( !file_exists("cache/".$day."_stat.txt") )
    {
      require "simplify.php";
    }
    readfile ("cache/".$day."_stat.txt");
  }

	if ( $q == "mapping" )
	{
	  $id = $_GET["id"];
	  @readfile ("devices/".$id.".map");
  }

	if ( $q == "reading" )
	{
	  $id = $_GET["id"];
	  @readfile ("devices/".$id.".last");
  }

  if ( $q == "devices" )
  {
		if ($handle = opendir("devices/")) 
    {
      while (false !== ($entry = readdir($handle))) 
      {
        if ( substr($entry, -4) != ".txt" )
          continue;

				echo(file_get_contents("devices/".$entry));
      }
      closedir($handle);
    }
  }

  if ( $q == "days" )
  {
    $prefix = $_GET["prefix"];
    $prefixl = strlen($prefix);
		echo("addReports([");

		if ($handle = opendir("data/")) 
    {
      while (false !== ($entry = readdir($handle))) 
      {
        if ( substr($entry, -4) != ".txt" )
          continue;

        if ( substr($entry, 0, $prefixl) != $prefix )
          continue;

    		echo("\"".substr($entry,0,-4)."\",");

      }
      closedir($handle);
    }
		echo("]);");
  }

  if ( $q == "remote" )
  {
    $l = $_GET["link"];
    readfile($l);
  }

?>