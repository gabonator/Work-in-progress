<?
  if ( $_SERVER["CONTENT_LENGTH"] == 256 )
  {
    require "remote.php";
    die();
  }

  require "manager.html";
//  require "view.html";
?>