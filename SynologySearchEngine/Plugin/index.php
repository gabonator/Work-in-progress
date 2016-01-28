<html>
<head>
<meta charset="UTF-8">
</head>
<?
  ini_set('display_errors', 1);
  require "search.php";

  class Plugin
  {
    public function addResult($title, $download, $size, $datetime, $page, $hash, $seeds, $leechs, $category)
    {
      echo "Adding: ".$title. ", url: ".$download." size: ".$size." date: ".$datetime."<br>";
    }
  };

  $plugin = new Plugin();

  $curl = curl_init();

	$t = new SynoDLMSearchUlozto();
  $t->prepare($curl, "rozpravka");
  $response = curl_exec($curl);
  echo("result:".$t->parse($plugin, $response));
  $status = curl_getinfo($curl,CURLINFO_HTTP_CODE); 
  echo("status: ".$status);
  curl_close($curl); 

?>
</html>