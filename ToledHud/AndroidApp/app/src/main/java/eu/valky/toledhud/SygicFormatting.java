package eu.valky.toledhud;

class CSygicFormatting {
    public enum SygicUnits
    {
        Kilometers,
        Miles
    };

    private static SygicUnits m_eSettingsUnits = SygicUnits.Kilometers;

    CLocalizedDistance LocalizedDistance(int nDistanceMeters, boolean bRound)
    {
        return new CLocalizedDistance(nDistanceMeters, bRound);
    }

    CLocalizedSpeed LocalizedSpeed(int nSpeedKmh, boolean bRound)
    {
        return new CLocalizedSpeed(nSpeedKmh, bRound);
    }

    void setUnits(SygicUnits eUnits)
    {
        m_eSettingsUnits = eUnits;
    }

    public class CLocalizedDistance {
        public int m_nDistance;
        public ToledData.ToledUnits m_eUnits;

        public CLocalizedDistance(int nDistanceMeters, boolean bRound) {
            switch (CSygicFormatting.m_eSettingsUnits) {
                case Kilometers:
                    this.m_eUnits = ToledData.ToledUnits.Meters;
                    this.m_nDistance = nDistanceMeters;

                    if ( bRound )
                        this.m_nDistance = CSygicFormatting.RoundDistance(this.m_nDistance);
                    break;

                case Miles:
                    this.m_nDistance = (int)(nDistanceMeters * 328084.0 / 100000.0);

                    if ( bRound )
                        this.m_nDistance = CSygicFormatting.RoundDistance(this.m_nDistance);

                    if (this.m_nDistance < 1000) // less than 1000 feets
                    {
                        this.m_eUnits = ToledData.ToledUnits.Feet;
                    } else if (this.m_nDistance < 10 * 5280)  // less than 10 miles
                    {
                        this.m_nDistance = this.m_nDistance * 10 / 5280;
                        this.m_eUnits = ToledData.ToledUnits.DotMile;
                    } else {
                        this.m_nDistance = this.m_nDistance / 5280;
                        this.m_eUnits = ToledData.ToledUnits.Miles;
                    }
                    break;
            }
        }
    }

    public class CLocalizedSpeed {
        public int m_nSpeed;
        public ToledData.ToledUnits m_eUnits;

        public CLocalizedSpeed(int nKmh, boolean bRound) {
            switch (CSygicFormatting.m_eSettingsUnits) {
                case Kilometers:
                    this.m_nSpeed = nKmh;
                    this.m_eUnits = ToledData.ToledUnits.Meters;
                    break;

                case Miles:
                    this.m_nSpeed = nKmh * 1000 / 1609;
                    this.m_eUnits = ToledData.ToledUnits.Miles;
                    break;
            }
            if ( bRound )
            {
                int nAccuracy = 5;
                this.m_nSpeed += nAccuracy / 2;
                this.m_nSpeed = this.m_nSpeed - (this.m_nSpeed % nAccuracy);
            }
        }
    }

    static int RoundDistance(int nNumber)
    {
        if ( nNumber < 5 )
            return 0;

        if ( nNumber < 30 )
        {
            nNumber += 2;
            return nNumber - nNumber%5;
        }
        if ( nNumber < 250 )
        {
            nNumber += 5;
            return nNumber - nNumber%10;
        }
        if ( nNumber < 800 )
        {
            nNumber += 25;
            return nNumber - nNumber%50;
        }
        if ( nNumber < 10000 )
        {
            nNumber += 50;
            return nNumber - nNumber%100;
        }

        nNumber += 500;
        return nNumber - nNumber%1000;
    }

    public ToledData.ToledDirection FromSygicDirection(int nDirection)
    {
        final int DirectionStart			= 20;
        final int DirectionEasyLeft		=  6;
        final  int DirectionEasyRight		=  4;
        final  int DirectionEnd			= 19;
        final  int DirectionVia            = 15;
        final  int DirectionKeepLeft		=  2;
        final  int 	DirectionKeepRight		=  0;
        final  int DirectionLeft			= 10;
        final  int DirectionOutOfRoute		= 21;
        final  int DirectionRight			=  8;
        final  int DirectionSharpLeft		= 14;
        final  int DirectionSharpRight		= 12;
        final  int DirectionStraight		= 16;
        final  int DirectionUTurnLeft		= 18;
        final  int DirectionUTurnRight		= 17;
        final  int DirectionRoundaboutSE	= 23;
        final  int DirectionRoundaboutE	= 24;
        final  int DirectionRoundaboutNE	= 25;
        final  int DirectionRoundaboutN	= 26;
        final  int DirectionRoundaboutNW	= 27;
        final  int DirectionRoundaboutW	= 28;
        final  int DirectionRoundaboutSW	= 29;
        final  int DirectionRoundaboutS	= 30;
        // 31..39 UK roundabouty
        final  int DirectionUkRoundaboutSE	= 23+10;
        final  int DirectionUkRoundaboutE	= 24+10;
        final  int DirectionUkRoundaboutNE	= 25+10;
        final  int DirectionUkRoundaboutN	= 26+10;
        final  int DirectionUkRoundaboutNW	= 27+10;
        final  int DirectionUkRoundaboutW	= 28+10;
        final  int DirectionUkRoundaboutSW	= 29+10;
        final  int DirectionUkRoundaboutS	= 30+1;

        final  int DirectionFerry			= 40;
        final  int DirectionStateBoundary	= 41;
        final  int DirectionExitRight		= 43;
        final  int DirectionFollow			= 42;
        final  int DirectionExitLeft		= 44;
        final  int DirectionMotorway		= 45;

        final  int DirectionTunnel         = 50;


        switch (nDirection) {
            case -1:
                return ToledData.ToledDirection.None;
            case DirectionStart:
                return ToledData.ToledDirection.IconQ;
            case DirectionEasyLeft:
                return ToledData.ToledDirection.EasyLeft;
            case DirectionEasyRight:
                return ToledData.ToledDirection.EasyRight;
            case DirectionEnd:
                return ToledData.ToledDirection.IconFinish;
            case DirectionVia:
                return ToledData.ToledDirection.IconFinish;
            case DirectionKeepLeft:
                return ToledData.ToledDirection.EasyLeft;
            case DirectionKeepRight:
                return ToledData.ToledDirection.EasyRight;
            case DirectionLeft:
                return ToledData.ToledDirection.Left;
            case DirectionOutOfRoute:
                return ToledData.ToledDirection.AnimationWaiting3;
            case DirectionRight:
                return ToledData.ToledDirection.Right;
            case DirectionSharpLeft:
                return ToledData.ToledDirection.SharpLeft;
            case DirectionSharpRight:
                return ToledData.ToledDirection.SharpRight;
            case DirectionStraight:
                return ToledData.ToledDirection.Straight;
            case DirectionUTurnLeft:
                return ToledData.ToledDirection.UturnLeft;
            case DirectionUTurnRight:
                return ToledData.ToledDirection.UturnRight;
            case DirectionRoundaboutSE:
                return ToledData.ToledDirection.Rb5;
            case DirectionRoundaboutE:
                return ToledData.ToledDirection.Rb3;
            case DirectionRoundaboutNE:
                return ToledData.ToledDirection.Rb2;
            case DirectionRoundaboutN:
                return ToledData.ToledDirection.Rb12;
            case DirectionRoundaboutNW:
                return ToledData.ToledDirection.Rb11;
            case DirectionRoundaboutW:
                return ToledData.ToledDirection.Rb9;
            case DirectionRoundaboutSW:
                return ToledData.ToledDirection.Rb7;
            case DirectionRoundaboutS:
                return ToledData.ToledDirection.IconQ;

            case DirectionFerry:
                return ToledData.ToledDirection.AnimationWaiting2;
            case DirectionStateBoundary:
                return ToledData.ToledDirection.AnimationWaiting2;
            case DirectionExitRight:
                return ToledData.ToledDirection.ExitRight;
            case DirectionFollow:
                return ToledData.ToledDirection.Straight;
            case DirectionExitLeft:
                return ToledData.ToledDirection.ExitLeft;
            case DirectionMotorway:
                return ToledData.ToledDirection.AnimationWaiting2;
            case DirectionTunnel:
                return ToledData.ToledDirection.AnimationWaiting2;

            default:
                return ToledData.ToledDirection.AnimationWaiting2;
        }
    }


}
