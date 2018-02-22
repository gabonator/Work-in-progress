<?
class Astro
{
  private $longitude;
  private $latitude;

  public function __construct($longitude, $latitude)
  {
    $this->longitude = $longitude;
    $this->latitude = $latitude;
  }

  private function Sunrise($date, $pos)
  {
    $RADS = M_PI/180.0;
    $DEGS = 180.0/M_PI;

    $days = $this->SunriseDay($date["year"], $date["month"], $date["day"]) + 0.5;

    // mean longitude of the Sun
    $sunLong = $this->SunriseNormalize(280.461 * $RADS + .9856474 * $RADS * $days);

    // mean anomaly of the Sun
    $anomaly = $this->SunriseNormalize(357.528 * $RADS + .9856003 * $RADS * $days);

    // Find the ecliptic longitude of the Sun
    $lambda = $this->SunriseNormalize($sunLong + 1.915 * $RADS * sin($anomaly) + .02 * $RADS * sin(2.0 * $anomaly));

    // Obliquity of the ecliptic
    $obliq = 23.439 * $RADS - .0000004 * $RADS * $days;
 
    // Find the RA and DEC of the Sun
    $alpha = atan2( cos($obliq) * sin($lambda), cos($lambda) );
    $delta = asin( sin($obliq) * sin($lambda) );

    // Find the Equation of Time in minutes
    $sunLong2 = $sunLong - $alpha;
    if ($sunLong < M_PI) 
      $sunLong2 += M_PI * 2;

    $equation = 1440.0 * (1.0 - $sunLong2 / M_PI / 2.0);

    $hourAngle = $this->SunriseHourangle( $pos["lat"], $delta );

    // Compute sunrise / sunset times
    $dbSunrise = 12.0 - 12.0 * $hourAngle / M_PI - $pos["long"] / 15.0 + $equation / 60.0;
    $dbSunset  = 12.0 + 12.0 * $hourAngle / M_PI - $pos["long"] / 15.0 + $equation / 60.0;

    if ( $dbSunrise > 24.0 ) 
      $dbSunrise -= 24.0;
    if ( $dbSunset > 24.0 )  
      $dbSunset  -= 24.0;

    if ( $dbSunrise < 0.0 ) 
      $dbSunrise += 24.0;
    if ( $dbSunset < 0.0 )
      $dbSunset  += 24.0;

    // Conversion of angle to hours and minutes
    $yearPhase = $alpha * $DEGS;
    if ($yearPhase < 0)
      $yearPhase += 360;

    return array("phase" => $yearPhase, "daylen" => $DEGS * $hourAngle / 7.5, "sunrise" => $dbSunrise, "sunset" => $dbSunset, "time" => $days - 0.5);
  }

  private function SunriseDay( $y, $m, $d )
  {
    // get count of days relative to Year 2000
    //_ASSERT( y >= 1901 && y <= 2099 );
    $luku = floor(- 7 * ($y + ($m + 9) / 12) / 4 + 275 * $m / 9 + $d);
    // avoid overflow
    $luku += $y * 367;
    return $luku - 730531;
  }

  private function SunriseNormalize( $x )
  {
    $b = 0.5 * $x / M_PI;
    $a = 2 * M_PI * ( $b - floor( $b ) );
    if ( $a < 0 ) 
      $a += 2*M_PI;
    return $a;
  }

  private function SunriseHourangle( $dbLat, $dbDeclin )
  {
    $RADS = M_PI/180.0;
    $dfo = $RADS * (0.5 * /*SunDia*/ 0.53 + /*Air Refraction*/ 34.0 / 60.0 ); 
    if ( $dbLat < 0.0 ) 
      $dfo = -$dfo;

    $fo = tan( $dbDeclin + $dfo ) * tan( $dbLat * $RADS );

    if ( $fo > 0.99999 ) 
      $fo = M_PI;
    else if ( fo < -0.99999 ) 
      $fo = 0.0;
    else
      $fo = asin( $fo ) + M_PI / 2.0;

    return $fo;
  }

  public function CalculateSunrise()
  {
    $pos = array("long" => $this->longitude, "lat" => $this->latitude); 
    $date = array("day" => gmdate("j"), "month" => gmdate("n"), "year" => gmdate("Y"));
    $time = array("hour" => gmdate("G"), "minute" => gmdate("i"));

    $sunrise = $this->Sunrise($date, $pos);
    $sunrise["timezone"] = date("Z")/60/60;
    $sunrise["date"] = $date;
    $sunrise["season"] = ["spring", "summer", "autumn", "winter"][floor($sunrise["phase"]/90)];

    $dbCurrentTime = $time["hour"] + $time["minute"] / 60.0;
    $sunrise["currentTime"] = $dbCurrentTime + $sunrise["timezone"];

    if ( $sunrise["daylen"] < 0.0001 )
      $sunrise["current"] = "polar_night";
    else if ( $sunrise["daylen"] > 23.999 )
      $sunrise["current"] = "polar_day";
    else
    {
      if ( $sunrise["sunset"] > $sunrise["sunrise"] )
      {
        if ( $dbCurrentTime > $sunrise["sunrise"] && $dbCurrentTime <= $sunrise["sunset"])
          $sunrise["current"] = "day";
        else
          $sunrise["current"] = "night";
      } 
      else
      {
        if ( $dbCurrentTime > $sunrise["sunset"] && $dbCurrentTime <= $sunrise["sunrise"])
          $sunrise["current"] = "night";
        else
          $sunrise["current"] = "day";
      }
    }
    return $sunrise;
  }
}
?>