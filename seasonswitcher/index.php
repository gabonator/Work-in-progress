<?php

if ( !isset($_GET["longitude"]) || !isset($_GET["latitude"]) )
{
  header('HTTP/1.0 400 Bad Request', true, 400);
  echo("Bad request, try: http://api.gabo.guru/seasonswitcher/?longitude=17.733766&latitude=48.286168");
  die();
}

require "astro.php";
  
$sunrise = new Astro(floatval($_GET["longitude"]), floatval($_GET["latitude"]));
$current = $sunrise->CalculateSunrise();

header("Location: http://api.gabo.guru/seasonswitcher/images/".$current["season"]."/".$current["current"].".jpg", true, 302);
?>