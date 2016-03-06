<?php
class SynoDLMSearchUlozto
{
  private $searchUrl = "http://ulozto.cz/hledej?q=";
  private $blowfish;

  public function __construct() 
  {
    include "blowfish.php";
    $this->blowfish = new Blowfish();
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

    $this->blowfish->init($data[$key]);
    $subdata = array();
    $entries = 0;
    $skipFirst = true;

    foreach ($data as $row)
    {
      $subdata[] = self::trim($this->blowfish->decrypt($row));

      if ( count($subdata) == 7 )
      {
        if ( $skipFirst )
          $skipFirst = false;
        else
        {
          $this->pushEntry($plugin, $subdata);
          $entries++;
        }

        $subdata = array();
      }
    }

    return $entries;
  }
 
  private function match($txt, $regex)
  {
    preg_match("/".$regex."/", $txt, $matches);

    if ( count($matches) == 2 )
      return $matches[1];

    array_shift($matches);
    return $matches;
  }

  private function pushEntry($plugin, $data)
  {
    $url = $data[0];
    $mainInfo = str_replace("\n", "", $data[6]);

    $img = self::match($mainInfo, "\\<img src=\\\"(.*?)\\\"");
    if ($img != "")
      $img = "<img src='".$img."'>";

    $rating = self::match($mainInfo, "fileRating.*?em>(.*?)<");
    $name = self::match($mainInfo, "class=\"name.*?\">(.*?)<");
    $size = self::match($mainInfo, "fileSize\">(.*?) (B|MB|GB|kB)<");
    $time = self::match($mainInfo, "fileTime\">(.*?)<");

    $image = self::match($mainInfo, "\\<img src=\\\"(.*?)\\\"");

    $size = self::calculateSize($size[0], $size[1]);

    $hash = md5($url);
    $seeds = $rating*10+100; // 100 -> 0 votes, 110 -> 1 vote, 90 -> -1 vote
    $leechs = 0;

    $year = self::match($name, ".*\\b((19|20)\\d{2})\\b");
    $year = count($year) == 2 ? $year[0] : date("Y");

    $download = "http://ulozto.cz".$url;
    $about = "http://ulozto.cz".$url."?g_rating=".$rating."&g_img=".str_replace("http://", "", $image)."&g_time=".$time;

    $category = self::getCategoryByName($name);
    $plugin->addResult($name, $download, $size, $year."-04-01", $about, $hash, $seeds, $leechs, $category);
  }

  private function calculateSize($number, $units)
  {
    $number = floatval($number);
    $mul = 1.0;
    if ( $units == "kB" )
      $mul = 1024.0;
    if ( $units == "MB" )
      $mul = 1024.0*1024.0;
    if ( $units == "GB" )
      $mul = 1024.0*1024.0*1024.0;

    $aux = floor($number * $mul);

    return $aux;
  }

  private function trim($str)
  {
    while ( strlen($str) > 0 && ord(substr($str, strlen($str)-1, 1)) == 0 )
      $str = substr($str, 0, strlen($str)-1);
      
    return $str;
  }

  private function getCategoryByName($name)
  {
    $fileTypes = array(
      ".torrent" 	=> "Torrent",

      ".rar" 			=> "Compressed archive",
      ".zip" 			=> "Compressed archive",
      ".7z" 			=> "Compressed archive",
      

      ".pdf" 			=> "Document",
      ".txt" 			=> "Document",

      ".srt"			=> "Subtitles",

      ".avi"			=> "Video",
      ".mpg"			=> "Video",
      ".mkv"			=> "Video",
      ".mp4"			=> "Video",
      ".wmv"			=> "Video",
      ".mov"			=> "Video",

      ".mp3"			=> "Audio",
    
      ".gif"			=> "Image",
      ".jpg"			=> "Image",
      ".jpeg"			=> "Image",

      ".apk"			=> "Android application",

      ".iso"			=> "ISO Image"
    );

    foreach ($fileTypes as $ext => $fileType) 
    {
      if ( strstr($name, $ext) !== false )
        return $fileType;
    }

    return "Unknown category";
  }
}
?>