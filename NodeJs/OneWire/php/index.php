<?
  if (isset($_GET["addraw"]))
  {
    $ip = $_SERVER["REMOTE_ADDR"];
//    $rec = "raw:".$_GET["addraw"];
    $args = "";
    foreach($_GET as $k => $v)
    {
      if ($args != "") $args.=", ";
      $args .= $k.":".$v;
    }
   
    $rec = "add({timestamp:".time().", time:\"".getTs()."\", ip:\"".$ip."\", args:{".$args."}});\n";

    $f = fopen("data/".getCurrent(), "a");  
    fwrite($f, $rec);
	  fclose($f);

	  echo("Written:".$args);
	  die();
  }

  function getCurrent()
  {
    return date("Y-m-d").".txt";
  }
  function getTs()
  {
    return date("Y-m-d H:i:s");
  }
  require "chart.html";
?>