<?
// Disable safe mode for using shell_exec command
$widgetPath = "widgets";

$crlf = "\n";

$q = '<?xml version="1.0" encoding="UTF-8"?>'.$crlf;
$q.= '<rsp stat="ok">'.$crlf;
$q.= '<list>'.$crlf;

foreach (scandir($widgetPath) as $file)
{
  if ( substr($file, 0, 1) == "@" ) // synology
    continue; 

  if ( $file == "." || $file == ".." )
    continue;

  if ( is_dir($widgetPath."/".$file) )
  {
    $cmd = 'cd '.$widgetPath.'/'.$file.' && zip -r ../'.$file.'.zip * --exclude=*@eaDir*';
    $report = shell_exec($cmd);
    $cmd = str_replace("--", "-", $cmd);
    $q .= "<!-- command '".$cmd."'\n".$report."-->\n";
    $file .= ".zip";
  } else
    continue;

  if ( substr($file, -4) != ".zip" ) 
    continue;

  if ( !file_exists($widgetPath."/".$file) )
  {
    $q.= '  <!-- file "'.$file.'" not found! -->'.$crlf;
    continue;
  }

  $name = substr($file, 0, -4);

  $q.= '   <widget id="'.$name.'">'.$crlf;
  $q.= '       <title>'.$name.'</title>'.$crlf;
  $q.= '       <compression size="'.filesize($widgetPath."/".$file).'" type="zip"/>'.$crlf;
  $q.= '       <description></description>'.$crlf;
  $q.= '       <download>http://'.$_SERVER['HTTP_HOST'].'/'.$widgetPath.'/'.$file.'</download>'.$crlf;
  $q.= '   </widget>'.$crlf;
}

$q.= '</list>'.$crlf;
$q.= '</rsp>'.$crlf;

echo("<pre>".htmlspecialchars($q)."</pre>");
file_put_contents("widgetlist.xml", $q);
?>