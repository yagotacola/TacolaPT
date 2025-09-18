#pragma once

#define MAX_TEAM_SIZE 10

enum EBattleArenaState
{
	BATTLEARENASTATE_WaitingEvent,
	BATTLEARENASTATE_WaitingPlayers,
	BATTLEARENASTATE_Running,
};

enum EBattleTeam
{
	BATTLETEAM_None,
	BATTLETEAM_Red,
	BATTLETEAM_Blue,
};

struct BattleArenaUser
{
	char szName[32];
	DWORD dwObjectSerial;
	EBattleTeam eTeam;
	int iKills;

	BattleArenaUser()
	{
		ZeroMemory(szName, 32);
		dwObjectSerial = 0;
		iKills = 0;
	}
};

struct BattleArenaConfig
{
	int iHour;
	int iWaitTime;
	int iDuration;
};

struct BattleArenaOpenWindow
{
	int size, code;

	int iTimeLeft;
	EBattleArenaState eEventState;
};

struct BattleArenaJoin
{
	int size, code;

	int Team;
};

struct BattleArenaSyncData
{
	int size, code;

	EBattleArenaState eEventState;
	int iTimeLeft;
	int iRedPoints;
	int iBluePoints;

	BattleArenaSyncData()
	{
		eEventState = BATTLEARENASTATE_WaitingEvent;
		iTimeLeft = 0;
		iRedPoints = 0;
		iBluePoints = 0;
	}
};

struct BattleArenaRanking
{
	int size, code;

	BattleArenaUser sPlayers[10];
};