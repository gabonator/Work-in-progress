<?
  if (isset($_GET["imei"]))
  {
    require "add.php";
  } else
  {
    require "chart.html";
  }
?>