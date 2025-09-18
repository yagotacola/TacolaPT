#pragma once
#include "battlearena.h"

struct sOBJECT
{
	int ID;
	int Mat;
	int Mat_;
	int x, y, w, h;
	bool bSelected;
};


class cBATTLEARENA
{
public:
	void Init();
	void Main();
	void Draw();
	bool LButtonDown();
	void HandlePacket(BattleArenaOpenWindow* psPacket);
	void HandlePacket(BattleArenaJoin* psPacket);
	void HandlePacket(BattleArenaSyncData* psPacket);
	void HandlePacket(BattleArenaRanking* psPacket);

	void LeaveArena();

	bool isOpen() { return OpenFlag; }
	bool isInsideArena() { return bIsInsideArena; }
	bool isStarted() { return eState == BATTLEARENASTATE_Running; }
	bool isAlly(smCHAR* lpChar) { return lpChar->iTeam == SelectedTeam; }
	int GetTeam() { return SelectedTeam; }

private:
	enum ID
	{
		BACKGROUND,
		EXIT,
		EXIT_,
		START,
		START_,
		DEFAULT,
		RED,
		BLUE,
		PLACAR,
		TIMEBG,
		TABBG,
		TABBLUE,
		TABRED,

		MAX_MAT,
	};

	int SelectedTeam;
	int iTimeLeft;
	EBattleArenaState eState;
	int Mat[MAX_MAT];
	std::vector<sOBJECT> vObjects;
	int BaseX, BaseY;
	bool bIsInsideArena;
	int iRedPoints, iBluePoints;

	void SendJoinArena();
	void AddObject(int ID, int Mat, int Mat_, int x, int y, int w, int h, bool bSelected = false);
	sOBJECT* FindObject(int ID);
	bool OpenFlag = false;
	void Open();
	void Close();
	void SelectTeam(sOBJECT* pObj);
	void SelectTeam(int ID);

	BattleArenaUser vPlayers[10];
};

extern cBATTLEARENA cBattleArena;