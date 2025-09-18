#pragma once

class cTARGET
{
public:

	void DrawImage(int Mat, int x, int y, int w, int h);
	void Init();
	void DrawTarget();
	void Draw(smCHAR* lpEachPlayer);
	void Text(smCHAR* lpEachPlayer);
	bool LButtonDown();
	bool MouseIn();
	bool StopMotion();

	enum MAT
	{
		BACKGROUND,
		TARGETBG,
		TARGETCLAN,
		TARGETHP,
		TARGETMP,
		TYPEDEMON,
		TYPEMECHANIC,
		TYPEMUTANT,
		TYPENORMAL,
		TYPENPC,
		TYPEPLAYER,
		TYPEUNDEAD,
		MORE,
		MORE_,
		DROPTOP,
		DROPMID,
		DROPBOT,
		RANKNOOB,
		RANKPRATA,
		RANKOURO,
		RANKMASTER,
		RANKGMASTER,
		RANKRMASTER,
		OVERLAY,
		MAX_MAT,
	};

	int BaseX, BaseY;

	int Mat[MAX_MAT];
	int troca, troca_, grupo, grupo_, clan, clan_, amigo, amigo_;

	bool DropDownFlag;
	DWORD TargetSerial;
	void OpenDropDown();
	std::map<int, char*> vOptions;
	void handleOption(int code);
};

extern cTARGET cTarget;