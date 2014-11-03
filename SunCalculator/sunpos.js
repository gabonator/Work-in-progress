function SunPosition()
{
}

SunPosition.prototype.GetPosition = function(date, pos)
{
	var fElapsedJulianDays = date.days;
	var fDecimalHours = date.hours;
	var fEclipticLongitude;
	var fEclipticObliquity;
	var fRightAscension;
	var fDeclination;
	var DEG2RAD = Math.PI/180;

	// Auxiliary variables
	var fY;
	var fX;

	// Calculate ecliptic coordinates (ecliptic longitude and obliquity of the 
	// ecliptic in radians but without limiting the angle to be less than 2*Pi 
	// (i.e., the result may be greater than 2*Pi)
	{
		var fOmega=2.1429 - 0.0010394594 * fElapsedJulianDays;
		var fMeanLongitude = 4.8950630 + 0.017202791698*fElapsedJulianDays; // Radians
		var fMeanAnomaly = 6.2400600 + 0.0172019699 * fElapsedJulianDays;
		fEclipticLongitude = fMeanLongitude + 0.03341607 * Math.sin( fMeanAnomaly ) 
			+ 0.00034894 * Math.sin( 2.0*fMeanAnomaly )-0.0001134
			- 0.0000203 * Math.sin(fOmega);
		fEclipticObliquity = 0.4090928 - 6.2140e-9 * fElapsedJulianDays
			+0.0000396 * Math.cos(fOmega);
	}

	// Calculate celestial coordinates ( right ascension and declination ) in radians 
	// but without limiting the angle to be less than 2*Pi (i.e., the result may be 
	// greater than 2*Pi)
	{
		var fSin_EclipticLongitude = Math.sin( fEclipticLongitude );
		fY = Math.cos( fEclipticObliquity ) * fSin_EclipticLongitude;
		fX = Math.cos( fEclipticLongitude );
		fRightAscension = Math.atan2( fY,fX );
		if( fRightAscension < 0.0 ) fRightAscension += Math.PI*2;
		fDeclination = Math.asin( Math.sin( fEclipticObliquity )*fSin_EclipticLongitude );
	}

	// Calculate local coordinates ( azimuth and zenith angle ) in degrees
	{
		var fGreenwichMeanSiderealTime = 6.6974243242 + 0.0657098283*fElapsedJulianDays + fDecimalHours;
		var fLocalMeanSiderealTime = (fGreenwichMeanSiderealTime*15.0 + pos.long)*DEG2RAD;
		var fHourAngle = fLocalMeanSiderealTime - fRightAscension;
		var fLatitudeInRadians = pos.lat*DEG2RAD;
		var fCos_Latitude  = Math.cos( fLatitudeInRadians );
		var fSin_Latitude  = Math.sin( fLatitudeInRadians );
		var fCos_HourAngle = Math.cos( fHourAngle );
		fZenithAngle = (Math.acos( fCos_Latitude*fCos_HourAngle
			*Math.cos(fDeclination) + Math.sin( fDeclination )*fSin_Latitude));
		fY = -Math.sin( fHourAngle );
		fX = Math.tan( fDeclination )*fCos_Latitude - fSin_Latitude*fCos_HourAngle;
		fAzimuth = Math.atan2( fY, fX );
		if ( fAzimuth < 0.0 ) 
			fAzimuth += 2*Math.PI;
		// Parallax Correction
		var fEarthMeanRadius  = 6371.01; // In km
		var fAstronomicalUnit = 149597890.0; // In km
		var fParallax = (fEarthMeanRadius/fAstronomicalUnit) * Math.sin(fZenithAngle);
		fZenithAngle += fParallax;
	}

  return {zenithAngle:fZenithAngle/DEG2RAD, azimuth:fAzimuth/DEG2RAD};
}
