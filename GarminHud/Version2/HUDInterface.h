/***********************************************************************/
/*            Class HUDInterface                                       */
/*                                                                     */
/* Controlling Garmin Head Up Display                                  */
/* Pure virtual class. Method SendPacket needs to be overridden        */
/* within an inheriting class by a function with the same signature.   */
/* This method does the actual sending of the bytes to the HUD.        */
/* Sending can be done by simple write  to a (virtual) COM port        */
/* assigned to the Bluetooth SSP device or by direct access to the     */
/* Bluetooth stack or using an external Serial Bluetooth Module like   */
/* the HC-05.                                                          */
/*                                                                     */
/* This class is based on the code of gabonator, see                   */
/* https://github.com/gabonator/Work-in-progress/tree/master/GarminHud */
/*                                                                     */
/* Frank Huebenthal 2015, huebenthal (at) uxis.de                      */
/***********************************************************************/

#if !defined(HUDINTERFACE_H__INCLUDED_)
#define HUDINTERFACE_H__INCLUDED_

class HUDInterface
{
protected:
	void SendHud(unsigned char* pBuf, int nLen);
	int Digit(int n);
	virtual int SendPacket(const unsigned char* pBuf, int nLen) = 0;
public:
	typedef enum {
		SharpRight = 0x02,
		Right = 0x04,
		EasyRight = 0x08,
		Straight = 0x10,
		EasyLeft = 0x20,
		Left = 0x40,
		SharpLeft = 0x80,
		LeftDown = 0x81,
		RightDown = 0x82,
		AsDirection = 0x00
	} eOutAngle;
	typedef enum {
		Off = 0x00,
		Lane = 0x01,
		LongerLane = 0x02,
		LeftRoundabout = 0x04,
		RightRoundabout = 0x08,
		ArrowOnly = 0x80
	} eOutType;
	typedef enum {
		None = 0,
		Metres = 1,
		Kilometres = 3,
		Miles = 5
	} eUnits;
	typedef enum {
		DotsRight = 0x01,
		OuterRight = 0x02,
		MiddleRight = 0x04,
		InnerRight = 0x08,
		InnerLeft = 0x10,
		MiddleLeft = 0x20,
		OuterLeft = 0x40,
		DotsLeft = 0x80
	} eLane;
	HUDInterface();
	virtual ~HUDInterface();

	void SetTime(int nH, int nM, bool bColon = true, bool bFlag = false, bool bTraffic = false);
	void SetDistance(int nDist, eUnits unit, bool bDecimal = false, bool bLeadingZero = false);
	void SetDirection(eOutAngle nDir, eOutType nType = Lane, eOutAngle nRoundaboutOut = AsDirection);
	void SetLanes(unsigned char nArrow, unsigned char nOutline);
	void SetSpeedWarning(int nSpeed, int nLimit, bool bSpeeding = false, bool bIcon = false, bool bSlash = true);
	void ShowCameraIcon();
	void ShowGpsLabel();
};
#endif