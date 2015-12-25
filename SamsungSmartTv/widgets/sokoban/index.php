<?
  if ($_SERVER['REQUEST_METHOD']=='OPTIONS') 
  {
    header('Access-Control-Allow-Origin : *');   
    header('Access-Control-Allow-Methods : POST, GET, OPTIONS, PUT, DELETE');
    header('Access-Control-Allow-Headers : X-Requested-With, content-type');
    die();
  }
//  header("Access-Control-Allow-Origin: *");
//  header("Access-Control-Allow-Methods: POST, GET, OPTIONS");
//  header("Access-Control-Allow-Headers: Content-Type");
//  header("Access-Control-Max-Age: 86400");
//  die();
      /*
  $headers = getallheaders();
  $xJSON = ( strpos($headers["Content-Type"], "application/json" ) !== false) ? file_get_contents("php://input") : "{}";
  
  $transfer = "";
	$types = "";
	$rec = "";

	foreach ($_GET as $k => $v)
	{
		if ( $rec != "" )
			$rec .= ",";
		$rec .= $k.":\"".$v."\"";
	}

	foreach ($_POST as $k => $v)
	{
		if ( $rec != "" )
			$rec .= ",";
		$rec .= $k.":\"".$v."\"";
	}

	$rec = "add(time:\"".getTs()."\", ip:\"".$_SERVER["REMOTE_ADDR"]."\", json:".$xJSON.", args:{".$rec."}, agent:\"".$_SERVER["HTTP_USER_AGENT"]."\"});\n";
//$rec = $headers["Content-Type"]." - ".file_get_contents("php://input");
	$f = fopen("data/".getCurrent(), "a");
	fwrite($f, $rec);
	fclose($f);

  function getCurrent()
  {
    return date("Y-m-d").".txt";
  }
  function getTs()
  {
    return date("Y-m-d H:i:s");
  }
*/
echo ("ok");
?>
