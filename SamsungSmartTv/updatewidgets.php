<?
// Disable safe mode for using shell_exec command
$widgetPath = "widgets";

$crlf = "\n";

$q = '<?xml version="1.0" encoding="UTF-8"?>'.$crlf;
$q.= '<rsp stat="ok">'.$crlf;
$q.= '<list>'.$crlf;

$cmd = "rm ".$widgetPath."/*.zip";
$report = shell_exec($cmd);
$q .= "<!-- command '".$cmd."' ".$report."-->\n";

foreach (scandir($widgetPath) as $name)
{
  if ( substr($name, 0, 1) == "@" ) // synology
    continue; 

  if ( $name== "." || $name == ".." )
    continue;

  if ( is_dir($widgetPath."/".$name) )
  {
    $apid = $name."_".rand(1000, 9999);
    $arch = $apid.".zip";
    $cmd = 'cd '.$widgetPath.'/'.$name.' && zip -r ../'.$arch.' * --exclude=*@eaDir*';
    $report = shell_exec($cmd);
    $cmd = str_replace("--", "-", $cmd);
    $q .= "<!-- command '".$cmd."'\n".$report."-->\n";
  } else
    continue;

  if ( !file_exists($widgetPath."/".$arch) )
  {
    $q.= '  <!-- file "'.$arch.'" not found! -->'.$crlf;
    continue;
  }

  $q.= '   <widget id="'.$apid.'">'.$crlf;
  $q.= '       <title>'.$name.'</title>'.$crlf;
  $q.= '       <compression size="'.filesize($widgetPath."/".$arch).'" type="zip"/>'.$crlf;
  $q.= '       <description></description>'.$crlf;
  $q.= '       <download>http://'.$_SERVER['HTTP_HOST'].'/'.$widgetPath.'/'.$arch.'</download>'.$crlf;
  $q.= '   </widget>'.$crlf;
}

$q.= '</list>'.$crlf;
$q.= '</rsp>'.$crlf;

echo("<pre>".htmlspecialchars($q)."</pre>");
file_put_contents("widgetlist.xml", $q);
?>