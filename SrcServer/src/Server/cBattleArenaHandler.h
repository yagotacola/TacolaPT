#pragma once

#include "battlarena.h"

#include <unordered_map>

class cBATTLEARENA
{
public:
	cBATTLEARENA();

	void Load();
	void Main();

	void SendOpenWindow(rsPLAYINFO* lpPlayInfo);

	void HandlePacket(BattleArenaJoin* psPacket, rsPLAYINFO* lpPlayInfo);

	void forcetest();

	void LeftArena(rsPLAYINFO* lpPlayInfo);

	void HandleKill(rsPLAYINFO* lpKillerInfo);

private:
	std::map<rsPLAYINFO*, BattleArenaUser> vBlueTeam;
	std::map<rsPLAYINFO*, BattleArenaUser> vRedTeam;
	int iRedPoints;
	int iBluePoints;

	std::vector<BattleArenaConfig> vConfig;
	BattleArenaConfig sConfig;

	EBattleArenaState eState;
	bool bStarted;
	DWORD dwTick;
	DWORD dwTickWaiting;
	DWORD dwLastStartHour;

	void StartEvent(BattleArenaConfig* pConfig);
	void EndEvent();
	int GetNextEventTime();
	BattleArenaUser* FindUser(rsPLAYINFO* lpPlayInfo);
	int JoinArena(rsPLAYINFO* lpPlayInfo, int Team);
	void ProcessOnWaiting();
	void ProcessOnRunning();
	void SendToEveryone(char* psPacket, int size);
	void SendMessageToAll(char* szMessage);
	void SendTop10Kill();
};

extern cBATTLEARENA cBattleArena;