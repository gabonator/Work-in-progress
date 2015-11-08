package eu.valky.toledhud;

public class ToledData
{
	public enum ToledDirection {
		EasyRight(1),
		Right(3),
		SharpRight(4),
		SharpLeft(6),
		Left(8),
		EasyLeft(9),
		UturnRight(11),
		UturnLeft(12),
		Rb2(13),
		Rb3(15),
		Rb5(16),
		Rb7(18),
		Rb9(21),
		Rb11(22),
		Rb12(24),
		AnimationWaiting(45),
		AnimationWaiting2(46),
		AnimationWaiting3(47),
		IconM(42),
		IconC(43),
		IconQ(26),
		IconR(29),
		IconFinish(30), // P
		IconT(31),
		ExitLeft(34),
		ExitRight(35),
		Straight(0),
		None(0);

        private int mValue;
        private ToledDirection(int value) {
            mValue = value;
        }
        public int getValue() {
            return mValue;
        }
	}

	public enum ToledUnits {
		Meters(0),
		Miles(1),
		DotMile(2),
		Feet(3),
		None(4);

        private int mValue;

        private ToledUnits(int value) {
            mValue = value;
        }

        public int getValue() {
            return mValue;
        }
	}

	public enum ToledInfo {
		None(0),
		Call(1),
		Sms(2);

        private int mValue;

        private ToledInfo(int value) {
            mValue = value;
        }

        public int getValue() {
            return mValue;
        }
	}

	public boolean bRouteAvailable = true;
	public int nPrimaryDistance = 123;
	public ToledDirection ePrimaryDirection = ToledDirection.Left;
	public int nSecondaryDistance = 456;
	public ToledDirection eSecondaryDirection = ToledDirection.Right;
	public int nSpeedCameraDistance = 90;
	public int nSpeedCameraLimit = 130;
	public int nCurrentSpeed = 145;
	public int nDistanceToDestination = 56;

	public ToledUnits eSpeed = ToledUnits.Meters;
	public ToledUnits eSpeedCamera = ToledUnits.None;
	public ToledUnits eDestination = ToledUnits.Meters;
	public ToledUnits ePrimary = ToledUnits.Meters;
	public ToledUnits eSecondary = ToledUnits.Meters;
	public ToledInfo eInfo = ToledInfo.None;
	public boolean bLcdOn = true;

	public void setWaiting()
	{
		bRouteAvailable = false;
		nPrimaryDistance = 0;
		ePrimaryDirection = ToledDirection.AnimationWaiting;
		nSecondaryDistance = 0;
		eSecondaryDirection = ToledDirection.None;
		nSpeedCameraDistance = 0;
		nSpeedCameraLimit = 0;
		nCurrentSpeed = 0;
		nDistanceToDestination = 0;
	}

	public byte[] GetBacklightPacket(int nBacklightValue)
	{
		byte[] buffer = new byte[5];
		buffer[0] = 'S';
		// D1: hud use 1=yes, 0=no
		buffer[1] = (byte)1;
		// D2: 0=manual brightness, 1=auto
		buffer[2] = (byte)((nBacklightValue == -1) ? 1 : 0);
		// D3: manual brightness level, 1..6
		buffer[3] = (byte)((nBacklightValue > -1) ? nBacklightValue : 0);
		// D4: reserved
		buffer[4] = (byte)0;
		return buffer;
	}

	public byte[] GetInstructionsPacket()
	{
		byte[] buffer = new byte[35];

		buffer[0] = (byte) 'H';
		buffer[1] = (byte) (this.bRouteAvailable ? 1 : 0);
		buffer[2] = (byte) (this.nPrimaryDistance >> 24);
		buffer[3] = (byte) (this.nPrimaryDistance >> 16);
		buffer[4] = (byte) (this.nPrimaryDistance >> 8);
		buffer[5] = (byte) (this.nPrimaryDistance);
		buffer[6] = (byte) (this.ePrimaryDirection.getValue());
		buffer[7] = (byte) (this.nSecondaryDistance >> 24);
		buffer[8] = (byte) (this.nSecondaryDistance >> 16);
		buffer[9] = (byte) (this.nSecondaryDistance >> 8);
		buffer[10] = (byte) (this.nSecondaryDistance);
		buffer[11] = (byte) (this.eSecondaryDirection.getValue());
		buffer[12] = (byte) (this.nSpeedCameraDistance >> 24);
		buffer[13] = (byte) (this.nSpeedCameraDistance >> 16);
		buffer[14] = (byte) (this.nSpeedCameraDistance >> 8);
		buffer[15] = (byte) (this.nSpeedCameraDistance);
		buffer[16] = (byte) (this.nSpeedCameraLimit >> 24);
		buffer[17] = (byte) (this.nSpeedCameraLimit >> 16);
		buffer[18] = (byte) (this.nSpeedCameraLimit >> 8);
		buffer[19] = (byte) (this.nSpeedCameraLimit);
		buffer[20] = (byte) (this.nCurrentSpeed >> 24);
		buffer[21] = (byte) (this.nCurrentSpeed >> 16);
		buffer[22] = (byte) (this.nCurrentSpeed >> 8);
		buffer[23] = (byte) (this.nCurrentSpeed);
		buffer[24] = (byte) (this.nDistanceToDestination >> 24);
		buffer[25] = (byte) (this.nDistanceToDestination >> 16);
		buffer[26] = (byte) (this.nDistanceToDestination >> 8);
		buffer[27] = (byte) (this.nDistanceToDestination);
		buffer[28] = (byte) (this.eSpeed.getValue());
		buffer[29] = (byte) (this.eSpeedCamera.getValue());
		buffer[30] = (byte) (this.eDestination.getValue());
		buffer[31] = (byte) (this.ePrimary.getValue());
		buffer[32] = (byte) (this.eSecondary.getValue());
		buffer[33] = (byte) (this.eInfo.getValue());
		buffer[34] = (byte) (this.bLcdOn ? 1 : 0);

		return buffer;
	}

	static int ntest = 0;

	public byte[] GetFullPacket(byte inner[])
	{
		byte[] buffer = new byte[1+inner.length+2]; // 34+4 = 38
		buffer[0] = '$';

		for (int i=0; i<inner.length; i++)
			buffer[i+1] = inner[i];

		byte nCrc = 0;

		for (int i=0; i<1+inner.length; i++)
			nCrc += buffer[i];

		buffer[1+inner.length+0] = (byte)(nCrc & 0xff);
		//if ( buffer.length == 8 )
		//	buffer[1+inner.length+1] = (byte)(buffer.length-1);
		//else
			buffer[1+inner.length+1] = (byte)(buffer.length-2);
		return buffer;
	}

}
