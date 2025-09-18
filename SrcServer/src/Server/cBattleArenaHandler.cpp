#include "sinbaram/sinLinkHeader.h"
#include "cBattleArenaHandler.h"
#include <Database/SQLConnection.h>

extern int SendQuickMessage2(rsPLAYINFO* lpPlayInfo, char* szMessage);
extern int SendToAll(char* Buff, int Size);
extern int CreateCommandItem(rsPLAYINFO* lpPlayInfo, rsPLAYINFO* lpPlayInfo2, char* szItem);

cBATTLEARENA cBattleArena;

cBATTLEARENA::cBATTLEARENA()
{
	eState = BATTLEARENASTATE_WaitingEvent;
	bStarted = false;
	dwTick = 0;
	dwTickWaiting = 0;
	dwLastStartHour = 0;
}

void cBATTLEARENA::Load()
{
	vConfig.clear();

	auto db = SQLConnection::GetConnection(DATABASEID_ServerDB);

	if (db->Open())
	{
		if (db->Prepare("SELECT * FROM BattleArenaConfig ORDER BY iHour ASC"))
		{
			if (db->Execute(false))
			{
				while (db->NextRow())
				{
					BattleArenaConfig Config;
					db->GetData(1, PARAMTYPE_Integer,  &Config.iHour);
					db->GetData(2, PARAMTYPE_Integer , &Config.iWaitTime);
					db->GetData(3, PARAMTYPE_Integer, &Config.iDuration);

					vConfig.push_back(Config);
				}
			}
		}

		db->Close();
	}
}

void cBATTLEARENA::Main()
{
	if (!dwTick && !dwTickWaiting && !bStarted)
	{
		SYSTEMTIME st;
		GetLocalTime(&st);

		if (dwLastStartHour != st.wHour)
		{
			for (vector<BattleArenaConfig>::iterator it = vConfig.begin(); it < vConfig.end(); it++)
			{
				auto Config = it._Ptr;
				if (st.wHour == Config->iHour && dwLastStartHour != st.wHour)
				{
					StartEvent(Config);
					dwLastStartHour = st.wHour;
					break;
				}
			}
		}
	}

	if (dwTickWaiting && dwTickWaiting + sConfig.iWaitTime * 60000 < GetCurrentTime())
	{
		dwTick = GetCurrentTime();
		dwTickWaiting = 0;
		eState = BATTLEARENASTATE_Running;
		iRedPoints = 0;
		iBluePoints = 0;
		SendMessageToAll("> A Battle Arena está fechada, o evento começou!");
	}
	else if (dwTick != 0)
	{
		if (dwTick + sConfig.iDuration * 60000 < GetCurrentTime())
		{
			EndEvent();
			return;
		}
		// gerenciar running
		ProcessOnRunning();
	}
	else if (dwTickWaiting)
	{
		// gerenciar waiting
		ProcessOnWaiting();
	}
}

void cBATTLEARENA::SendOpenWindow(rsPLAYINFO* lpPlayInfo)
{
	BattleArenaUser* pUser = FindUser(lpPlayInfo);

	if (pUser)
	{
		SendQuickMessage2(lpPlayInfo, "> Você já está em um time.");
		return;
	}

	// aqui envia o pacote pro game
	BattleArenaOpenWindow sPacket;
	sPacket.size = sizeof(BattleArenaOpenWindow);
	sPacket.code = smTRANSCODE_BA_OPENWINDOW;
	sPacket.eEventState = eState;
	sPacket.iTimeLeft = GetNextEventTime();
	lpPlayInfo->lpsmSock->Send((char*)&sPacket, sPacket.size, TRUE);
}

void cBATTLEARENA::HandlePacket(BattleArenaJoin* psPacket, rsPLAYINFO* lpPlayInfo)
{
	if (eState == BATTLEARENASTATE_WaitingPlayers)
	{
		int Team = JoinArena(lpPlayInfo, psPacket->Team);
		if (Team)
		{
			psPacket->Team = Team;
			lpPlayInfo->lpsmSock->Send((char*)psPacket, psPacket->size, TRUE);
		}
	}
}

void cBATTLEARENA::forcetest()
{
	if (eState == BATTLEARENASTATE_WaitingEvent)
	{
		sConfig.iWaitTime = 1;
		sConfig.iDuration = 5;
		dwTick = 0;
		dwTickWaiting = GetCurrentTime();
		bStarted = true;
		eState = BATTLEARENASTATE_WaitingPlayers;
		SendMessageToAll("iniciou a arena");
	}
	else
		EndEvent();
}

void cBATTLEARENA::LeftArena(rsPLAYINFO* lpPlayInfo)
{
	map<rsPLAYINFO*, BattleArenaUser>::iterator it = vBlueTeam.find(lpPlayInfo);
	bool bremoved = false;

	if (it != vBlueTeam.end())
	{
		// kickar do time azul
		vBlueTeam.erase(it);
		bremoved = true;
	}
	else
	{
		it = vRedTeam.find(lpPlayInfo);
		if (it != vRedTeam.end())
		{
			// kickar do time vermelho
			vRedTeam.erase(it);
			bremoved = true;
		}
	}

	if (bremoved)
	{
		TRANS_CHATMESSAGE TransChatMessage;
		TransChatMessage.code = smTRANSCODE_WHISPERMESSAGE;
		wsprintf(TransChatMessage.szMessage, "> %s saiu da arena.", lpPlayInfo->szName);
		TransChatMessage.size = lstrlen(TransChatMessage.szMessage) + 32;
		TransChatMessage.dwIP = 0;
		TransChatMessage.dwObjectSerial = 0;

		SendToEveryone((char*)&TransChatMessage, TransChatMessage.size);
	}
}

void cBATTLEARENA::HandleKill(rsPLAYINFO* lpKillerInfo)
{
	auto pUser = FindUser(lpKillerInfo);

	if (pUser)
	{
		if (pUser->eTeam == BATTLETEAM_Red)
			iRedPoints++;
		else if (pUser->eTeam == BATTLETEAM_Blue)
			iBluePoints++;

		pUser->iKills++;
	}
}

void cBATTLEARENA::StartEvent(BattleArenaConfig* pConfig)
{
	memcpy(&sConfig, pConfig, sizeof(BattleArenaConfig));
	dwTick = 0;
	dwTickWaiting = GetCurrentTime();
	bStarted = true;
	eState = BATTLEARENASTATE_WaitingPlayers;

	SendMessageToAll("> A Battle Arena está aberta, corra!");
}

void cBATTLEARENA::EndEvent()
{
	if (eState == BATTLEARENASTATE_Running)
	{
		// DAR OS PREMIOS E TIRAR A GALERA DA ARENA
		if (iRedPoints > iBluePoints)
		{
			for (auto player : vRedTeam)
			{
				rsPLAYINFO* lpPlayInfo = player.first;
				if (lpPlayInfo && lpPlayInfo->lpsmSock)
				{
					CreateCommandItem(lpPlayInfo, lpPlayInfo, "cx102");
				}
			}

			SendMessageToAll("> O time vermelho é o vencedor da Battle Arena!");
		}
		else if (iBluePoints > iRedPoints)
		{
			for (auto player : vBlueTeam)
			{
				rsPLAYINFO* lpPlayInfo = player.first;
				if (lpPlayInfo && lpPlayInfo->lpsmSock)
				{
					CreateCommandItem(lpPlayInfo, lpPlayInfo, "cx102");
				}
			}

			SendMessageToAll("> O time azul é o vencedor da Battle Arena!");
		}
		else
		{
			SendMessageToAll("> O evento Battle Arena terminou em empate!");
		}
	}

	smTRANS_COMMAND smTransCommand;
	smTransCommand.code = smTRANSCODE_BA_LEAVE;
	smTransCommand.size = sizeof(smTRANS_COMMAND);
	SendToEveryone((char*)&smTransCommand, smTransCommand.size);

	dwTick = 0;
	dwTickWaiting = 0;
	bStarted = false;
	eState = BATTLEARENASTATE_WaitingEvent;

	vBlueTeam.clear();
	vRedTeam.clear();

	SendMessageToAll("> A Battle Arena terminou!");
}

int cBATTLEARENA::GetNextEventTime()
{
	if (eState == BATTLEARENASTATE_WaitingEvent)
	{
		int hourdif = 0, mindif = 0, secdif = 0;
		SYSTEMTIME st;
		BattleArenaConfig* pConfig = nullptr;
		GetLocalTime(&st);

		for (vector<BattleArenaConfig>::iterator it = vConfig.begin(); it < vConfig.end(); it++)
		{
			auto config = it._Ptr;
			if (config->iHour >= st.wHour)
			{
				pConfig = config;
				break;
			}
		}

		if (!pConfig && vConfig.size())
		{
			pConfig = vConfig.begin()._Ptr;
			hourdif = 24 - st.wHour;
			if (st.wMinute > 0 || st.wSecond > 0)
				hourdif--;
			mindif = 60 - st.wMinute;
			secdif = 60 - st.wSecond;
			st.wHour = 0;
			st.wMinute = 0;
			st.wSecond = 0;
		}

		if (pConfig)
		{
			hourdif += pConfig->iHour - st.wHour;
			if (st.wMinute > 0 || st.wSecond > 0)
				hourdif--;
			mindif += 60 - st.wMinute;
			secdif += 60 - st.wSecond;

			int result = 0;
			result += secdif;
			result += mindif * 60;
			result += hourdif * 60 * 60;
			return result;
		}
	}

	return 0;
}

BattleArenaUser* cBATTLEARENA::FindUser(rsPLAYINFO* lpPlayInfo)
{
	map<rsPLAYINFO*, BattleArenaUser>::iterator it = vBlueTeam.find(lpPlayInfo);

	if (it != vBlueTeam.end())
		return &it->second;
	else
	{
		it = vRedTeam.find(lpPlayInfo);
		if (it != vRedTeam.end())
			return &it->second;
	}

	return nullptr;
}

int cBATTLEARENA::JoinArena(rsPLAYINFO* lpPlayInfo, int Team)
{
	if (vRedTeam.size() > vBlueTeam.size())
		Team = 2;
	else if (vBlueTeam.size() > vRedTeam.size())
		Team = 1;
	else
		Team = rand() % 2 + 1;

	if (Team == 1)
	{
		if (vRedTeam.size() >= MAX_TEAM_SIZE)
		{
			SendQuickMessage2(lpPlayInfo, "> Esse time está cheio.");
			return 0;
		}

		// entrar no time vermelho
		BattleArenaUser User;
		lstrcpy(User.szName, lpPlayInfo->szName);
		User.eTeam = BATTLETEAM_Red;
		User.dwObjectSerial = lpPlayInfo->dwObjectSerial;
		vRedTeam.insert(std::pair<rsPLAYINFO*, BattleArenaUser>(lpPlayInfo, User));
		return 1;
	}
	else if (Team == 2)
	{
		if (vBlueTeam.size() >= MAX_TEAM_SIZE)
		{
			SendQuickMessage2(lpPlayInfo, "> Esse time está cheio.");
			return 0;
		}

		// entrar no time azul
		BattleArenaUser User;
		lstrcpy(User.szName, lpPlayInfo->szName);
		User.eTeam = BATTLETEAM_Blue;
		User.dwObjectSerial = lpPlayInfo->dwObjectSerial;
		vBlueTeam.insert(std::pair<rsPLAYINFO*, BattleArenaUser>(lpPlayInfo, User));
		return 2;
	}
	return 0;
}

void cBATTLEARENA::ProcessOnWaiting()
{
	static int iProcessOnWaitingWheel = 0;

	if (iProcessOnWaitingWheel % 8 == 0)
	{
		BattleArenaSyncData sPacket;
		sPacket.code = smTRANSCODE_BA_SYNCDATA;
		sPacket.size = sizeof(BattleArenaSyncData);
		sPacket.iTimeLeft = ((dwTickWaiting + sConfig.iWaitTime * 60000) - GetCurrentTime()) / 1000;
		sPacket.eEventState = eState;

		SendToEveryone((char*)&sPacket, sPacket.size);

		SendTop10Kill();
	}

	iProcessOnWaitingWheel++;
}

void cBATTLEARENA::ProcessOnRunning()
{
	static int iProcessOnRunningWheel = 0;

	for (auto player : vBlueTeam)
		if (player.first->Position.Area != 49)
			LeftArena(player.first);

	for (auto player : vRedTeam)
		if (player.first->Position.Area != 49)
			LeftArena(player.first);

	if (iProcessOnRunningWheel % 8 == 0)
	{
		BattleArenaSyncData sPacket;
		sPacket.code = smTRANSCODE_BA_SYNCDATA;
		sPacket.size = sizeof(BattleArenaSyncData);
		sPacket.iTimeLeft = ((dwTick + sConfig.iDuration * 60000) - GetCurrentTime()) / 1000;
		sPacket.eEventState = eState;
		sPacket.iRedPoints = iRedPoints;
		sPacket.iBluePoints = iBluePoints;

		SendToEveryone((char*)&sPacket, sPacket.size);

		SendTop10Kill();
	}

	iProcessOnRunningWheel++;
}

void cBATTLEARENA::SendToEveryone(char* psPacket, int size)
{
	for (auto player : vBlueTeam)
	{
		if (player.first && player.first->lpsmSock)
			player.first->lpsmSock->Send(psPacket, size, TRUE);
	}
	for (auto player : vRedTeam)
	{
		if (player.first && player.first->lpsmSock)
			player.first->lpsmSock->Send(psPacket, size, TRUE);
	}
}

void cBATTLEARENA::SendMessageToAll(char* szMessage)
{
	TRANS_CHATMESSAGE TransChatMessage;
	TransChatMessage.code = smTRANSCODE_WHISPERMESSAGE;
	lstrcpy(TransChatMessage.szMessage, szMessage);
	TransChatMessage.size = lstrlen(TransChatMessage.szMessage) + 32;
	TransChatMessage.dwIP = 3;
	TransChatMessage.dwObjectSerial = 0;
	SendToAll((char*)&TransChatMessage, TransChatMessage.size);
}

void cBATTLEARENA::SendTop10Kill()
{
	vector<BattleArenaUser> vUsers;
	for (auto user : vBlueTeam)
		vUsers.push_back(user.second);
	for (auto user : vRedTeam)
		vUsers.push_back(user.second);

	sort(vUsers.begin(), vUsers.end(), [](BattleArenaUser a, BattleArenaUser b) { return a.iKills > b.iKills; });

	BattleArenaRanking sPacket = {};
	sPacket.code = smTRANSCODE_BA_RANKING;
	sPacket.size = sizeof(BattleArenaRanking);

	int limit = vUsers.size() > 10 ? 10 : vUsers.size();
	int cnt = 0;

	for (auto it = vUsers.begin(); it < vUsers.end(); it++)
	{
		if (cnt >= limit)
			break;

		memcpy(&sPacket.sPlayers[cnt++], it._Ptr, sizeof(BattleArenaUser));
	}

	/*for (int i = 0; i < ; i++)
	{
	auto user = vUsers.at(i);
	memcpy(&sPacket.sPlayers[i], &user , sizeof(BattleArenaUser));
	}*/

	SendToEveryone((char*)&sPacket, sPacket.size);
}