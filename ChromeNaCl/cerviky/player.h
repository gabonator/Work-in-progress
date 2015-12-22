#ifndef __PLAYER_H__
#define __PLAYER_H__

class CPlayer
{
public:
	int m_nKeyLeft;
	int m_nKeyRight;
	int m_nKeyAction;

	// extras
	enum EExtra {
		EENone = 0,
		EEWalkThrough = 1,		// biela prechadza cez ostatnych aj seba, 5-10s
		EEFlower = 2,			// roztroji sa, 1x
		EEShooter = 3,			// vystreli a spravi dieru, 3x
		EEBuldozeer = 4,		// pred sebou vymazava, 5s
		EESwapper = 5,			// prehodi predok za zadok, 3x
		EEEraser = 6,			// koho zrazi, ten zmizne z mapy
		EERespawn = 7,			// objavi sa niekde inde na mape
		EEShield = 8,			// vie sa prerazit cez 40 pixelov, automaticky aktivovane
		EECrosser = 9,			// moze prechadzat sam cez seba
		
		EESlowMo = 10,			// ostatnych spomali az zastavi na 5sekund
		EETurbo = 11,			// brutalna rychlost na 5sekund

		EEDouble = 12,			// zdvoji pocet pouziti / interval
		EEThroughWall = 13,
		EEDisease = 14,
		EESwapControls = 15
	};

	COLORREF m_cColor;
	
	int m_nId;
	EExtra m_nExtraAvailable;
	EExtra m_nExtraActivated; // jedno aktivne jedno v zasobe?
	int m_nExtraValidUntil;
	int m_nExtraCount;
	float m_fExtraCounter;

	int m_nExtraNewDuration;
	int m_nExtraNewCount;

	float m_fSteering;			// pocas zivota moze zbierat powerupy
	float m_fSpeed;

	int m_nLastKey;
	int m_nCurrentKey;

	// Evaluation
	int m_nTotalScore;
	int m_nScore;

	bool m_bAlive;
	bool m_bRobot;

public:
	CPlayer(int nId);
	bool IsMyColor(COLORREF c);
	bool IsAlive();
	void Randomize();
};

#endif