<?php
class SynoDLMSearchUlozto
{
  private $searchUrl = "http://ulozto.cz/hledej?q=";

  public function __construct() 
  {
  }

  public function prepare($curl, $query) 
  {
    $headers = array
    (
      "X-Requested-With: XMLHttpRequest"
    );  
    curl_setopt($curl, CURLOPT_HTTPHEADER, $headers); 
    curl_setopt($curl, CURLOPT_URL, $this->searchUrl.urlencode($query));
    curl_setopt($curl, CURLOPT_RETURNTRANSFER, true);
    curl_setopt($curl, CURLOPT_SSL_VERIFYHOST, false);
    curl_setopt($curl, CURLOPT_SSL_VERIFYPEER, false);                
  }

  public function parse($plugin, $response) 
  {
//    $plugin->addResult("dummy name", "http://ulozto.cz/123", 1235, "2015-01-01 10:00:00", "http://ulozto.cz/123", "", 1213, 99, "Unknown category"); return 1;

    $regex_key = "kapp\\(kn\\[\\\"(.*)\\\"";
    $regex_data = "var kn = (\\{.*?\\});";
    preg_match("/".$regex_key."/", $response, $matches);
    $key = $matches[1];

    preg_match("/".$regex_data."/", $response, $matches);
    $raw_data = $matches[1];
    $jsondata = json_decode($raw_data);
    $data = array();
    foreach ($jsondata as $key=>$value)
      $data[$key] = $value;
    $result = "";

    blowfish($data[$key]);
    $subdata = array();
    $entries = 0;
    foreach ($data as $row)
    {
      $subdata[] = decrypt($row);
      if ( count($subdata) == 7 )
      {
        $this->pushEntry($plugin, $subdata);
        $entries++;
        $subdata = array();
      }
    }
    return $entries;
  }
 
  private function match($txt, $regex)
  {
    preg_match("/".$regex."/", $txt, $matches);
    return $matches[1];
  }

  private function pushEntry($plugin, $data)
  {
    $url = $data[0];
    $mainInfo = str_replace("\n", "", $data[6]);

    $img = self::match($mainInfo, "\\<img src=\\\"(.*?)\\\"");
    if ($img != "")
      $img = "<img src='".$img."'>";

    $rating = self::match($mainInfo, "fileRating.*?em>(.*?)<");
    $name = $this->match($mainInfo, "class=\"name.*?\">(.*?)<");
    $size = self::match($mainInfo, "fileSize\">(.*?)<");
    $time = self::match($mainInfo, "fileTime\">(.*?)<");

    $hash = "";
    $seeds = $rating*100;
    $leechs = 0;
    $category = "Movie";

    $plugin->addResult($name, "http://ulozto.cz".$url, intval($size), "2015-04-15 00:00:00", "http://ulozto.cz".$url, $hash, $seeds, $leechs, $category);
  }
}

?>