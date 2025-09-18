#include <iostream>
#include <vector>
#include <stdio.h> 

#include "sinbaram/sinLinkHeader.h"
#include "field.h"
//#include "..\\Database\Database.h"
#include "CHellsGateHandler.h"
#include "Database.h"


int	rsRegist_ItemSecCode(rsPLAYINFO* lpPlayInfo, TRANS_ITEMINFO* lpTransItemInfo, int NewItem);
int srSetItemFromCode(psITEM* lpsItem, char* szCoed);



extern int		rsOpenNPC_RandomPos;
extern STG_AREA* FindStageField(int x, int z);
extern smCHAR* OpenMonsterFromName(char* szName, int x, int y, int z, rsPLAYINFO* lpPlayInfo = 0);

CHellsGate::CHellsGate()
{
	m_bEventFlag = false;
	m_nState = STATE_STOP;
	m_nEventIndex = 0;
	m_nEventStage = 0;
	m_dwEventTime = 0;
	m_dwDelayTime = 0;

	m_bNpcFlag = false;
	m_lpCharEventNpc = NULL;
	ZeroMemory(&m_smTransNpcInfo, sizeof(smTRNAS_PLAYERINFO));

	m_lpCharBoss = NULL;
	m_vlpCharMonster.clear();
	m_vHellsGateInfo.clear();
	m_vMonsterInfo.clear();
	m_vPlayersInfo.clear();
}

CHellsGate::~CHellsGate()
{
}

void CHellsGate::Init()
{
	m_vHellsGateInfo.clear();
	m_vMonsterInfo.clear();

	std::shared_ptr<Database> db = Database::GetConnection(DATABASEID_BattleEvents);


	if (db->Open())
	{
		if (db->Prepare("SELECT * FROM HellsGate"))
		{
			if (db->Execute())
			{
				m_vHellsGateInfo.clear();

				sEventInfo EvenInfo;

				for (int i = 0; i < MAX_EVENT_INFO; i++)
				{
					ZeroMemory(&EvenInfo, sizeof(sEventInfo));

					db->GetData(&EvenInfo.nHora, 0, 2, PARAMTYPE_IntegerX);
					db->GetData(&EvenInfo.nTempo, 0, 3, PARAMTYPE_IntegerX);
					db->GetData(&EvenInfo.nPLimite, 0, 4, PARAMTYPE_IntegerX);
					db->GetData(&EvenInfo.nMLimite, 0, 5, PARAMTYPE_IntegerX);
					db->GetData(&EvenInfo.szItemID, 32, 6, PARAMTYPE_StringX);

					m_vHellsGateInfo.push_back(EvenInfo);

					if (!db->NextRow())
						break;
				}
			}
		}

		if (db->Prepare("SELECT * FROM HellsGateMonster"))
		{
			if (db->Execute())
			{
				m_vMonsterInfo.clear();

				sMonsterInfo MonInfo;

				for (int i = 0; i < MAX_MONSTER_INFO; i++)
				{
					ZeroMemory(&MonInfo, sizeof(sMonsterInfo));

					db->GetData(&MonInfo.sBoss, 32, 2, PARAMTYPE_StringX);
					db->GetData(&MonInfo.sMob[0], 32, 3, PARAMTYPE_StringX);
					db->GetData(&MonInfo.sMob[1], 32, 4, PARAMTYPE_StringX);
					db->GetData(&MonInfo.sMob[2], 32, 5, PARAMTYPE_StringX);
					db->GetData(&MonInfo.sMob[3], 32, 6, PARAMTYPE_StringX);

					m_vMonsterInfo.push_back(MonInfo);

					if (!db->NextRow())
						break;
				}
			}
		}
		db->Close();
	}
}
extern char szNpcFileList[64][64];
extern int SetNpcFileList(char* szNpcDirectory);
void CHellsGate::AddNpc()
{
	STG_AREA* lpStgArea;

	lpStgArea = &StageArea[3];

	if (!m_lpCharEventNpc)
		m_lpCharEventNpc = new smCHAR;

	if (m_lpCharEventNpc && m_bNpcFlag == false)
	{
		SetNpcFileList("GameServer\\npc\\SistemaHG.NPC");

		for (int NpcFileCnt = 0; NpcFileCnt < 64; NpcFileCnt++)
		{
			if (lstrcmpi(szNpcFileList[NpcFileCnt], "GameServer\\npc\\SistemaHG.NPC") == 0)
			{
				m_lpCharEventNpc->smCharInfo.dwCharSoundCode = 0;

				if (smCharDecode(szNpcFileList[NpcFileCnt], &m_lpCharEventNpc->smCharInfo, 0))
				{
					m_lpCharEventNpc->PatLoading = TRUE;
					m_lpCharEventNpc->OnStageField = -1;
					AddLoaderPattern(m_lpCharEventNpc, m_lpCharEventNpc->smCharInfo.szModelName, 0);
					m_lpCharEventNpc->smCharInfo.SizeLevel = 1;
					m_lpCharEventNpc->DisplayTools = FALSE;
				}

				sprintf_s(m_smTransNpcInfo.smCharInfo.szModelName2, sizeof(m_smTransNpcInfo.smCharInfo.szModelName2), szNpcFileList[NpcFileCnt]);
				break;
			}
		}

		int x = 357;
		int z = -17293;
		m_smTransNpcInfo.code = 1;
		m_smTransNpcInfo.size = sizeof(smTRNAS_PLAYERINFO);
		m_smTransNpcInfo.smCharInfo.State = 0;
		m_smTransNpcInfo.smCharInfo.Life[0] = 100;
		m_smTransNpcInfo.smCharInfo.Mana[0] = 100;
		m_smTransNpcInfo.smCharInfo.Life[1] = 100;
		m_smTransNpcInfo.x = x << FLOATNS;
		m_smTransNpcInfo.z = z << FLOATNS;
		m_smTransNpcInfo.y = lpStgArea->lpStage->GetHeight(m_smTransNpcInfo.x, m_smTransNpcInfo.z);
		m_smTransNpcInfo.ax = m_lpCharEventNpc->Angle.x;
		m_smTransNpcInfo.ay = m_lpCharEventNpc->Angle.y;
		m_smTransNpcInfo.az = m_lpCharEventNpc->Angle.z;
		m_smTransNpcInfo.state = 0;

		rsOpenNPC_RandomPos = -1;
		m_bNpcFlag = true;
		lpStgArea->OpenNpc(&m_smTransNpcInfo);
	}
}

void CHellsGate::DelNpc()
{
	smCHAR* lpChar;

	if (m_bNpcFlag)
	{
		lpChar = srFindCharFromSerial(m_smTransNpcInfo.dwObjectSerial);

		if (lpChar)
		{
			lpChar->Close();

			ZeroMemory(&m_smTransNpcInfo, sizeof(smTRNAS_PLAYERINFO));
			m_bNpcFlag = false;

			if (m_lpCharEventNpc)
			{
				delete m_lpCharEventNpc;
				m_lpCharEventNpc = NULL;
			}
		}
	}
}

void CHellsGate::AddMonster(int nStageIndex)
{
	int x, y, z = 0;
	smCHAR* lpChar;
	STG_AREA* lpStgArea;

	lpStgArea = &StageArea[23];

	if (lpStgArea && nStageIndex)
	{
		//Centro da Arena
		x = -3626;
		z = -43500;
		x <<= FLOATNS;
		z <<= FLOATNS;
		y = lpStgArea->lpStage->GetHeight(x, z);

		//Summona o Boss do Round
		if (m_lpCharBoss == NULL && !m_vMonsterInfo.empty())
		{
			m_lpCharBoss = OpenMonsterFromName(m_vMonsterInfo[nStageIndex - 1].sBoss, x, y, z);
		}

		//Summona Mob ate a quantidade definida
		while (m_vlpCharMonster.size() < (unsigned)m_vHellsGateInfo[m_nEventIndex].nMLimite)
		{
			//Gera uma posição aleatoria próxima 
			int x2 = rand() % (128 * fONE);
			int z2 = rand() % (128 * fONE);
			x2 -= 64 * fONE;
			z2 -= 64 * fONE;

			//Sommona um monstro randomico entre os definidos no SQL
			lpChar = OpenMonsterFromName(m_vMonsterInfo[nStageIndex - 1].sMob[rand() % 4], x + x2, y, z + z2);

			if (lpChar)
			{
				m_vlpCharMonster.push_back(lpChar);
			}
		}
	}
}

void CHellsGate::KillBoss()
{
	if (m_lpCharBoss)
	{
		if (m_lpCharBoss->Flag && m_lpCharBoss->MotionInfo->State != CHRMOTION_STATE_DEAD)
		{
			m_lpCharBoss->smCharInfo.Life[0] = 0;
			m_lpCharBoss->SetMotionFromCode(CHRMOTION_STATE_DEAD);
		}
	}
	m_lpCharBoss = NULL;
}

void CHellsGate::KillMonster()
{
	for (auto monster : m_vlpCharMonster)
	{
		if (monster->Flag && monster->MotionInfo->State != CHRMOTION_STATE_DEAD)
		{
			monster->smCharInfo.Life[0] = 0;
			monster->SetMotionFromCode(CHRMOTION_STATE_DEAD);
		}
	}
	m_vlpCharMonster.clear();
}

void CHellsGate::SendNextStage(rsPLAYINFO* lpPlayInfo)
{
	if ((unsigned)m_nEventStage > m_vMonsterInfo.size()) return;

	smTRANS_HGINFO smTransHgInfo;

	ZeroMemory(&smTransHgInfo, sizeof(smTRANS_HGINFO));
	smTransHgInfo.size = sizeof(smTRANS_HGINFO);
	smTransHgInfo.code = smTRANSCODE_HG_NEXT_STAGE;
	smTransHgInfo.Flag = m_bEventFlag ? 1 : 0;
	smTransHgInfo.Stage = m_nEventStage;
	smTransHgInfo.dwTime = m_dwEventTime ? (m_dwEventTime - dwPlayServTime) : 0;
	smTransHgInfo.dwDelay = m_dwDelayTime ? (m_dwDelayTime - dwPlayServTime) : 0;

	if (m_lpCharBoss)
		smTransHgInfo.dwBossSerial = m_lpCharBoss->dwObjectSerial;

	if (m_bEventFlag)
	{
		if (!m_vMonsterInfo.empty() && ((unsigned)m_nEventStage < m_vMonsterInfo.size()))
		{
			sprintf_s(smTransHgInfo.szBossName, m_vMonsterInfo[m_nEventStage].sBoss);
		}
	}

	if (lpPlayInfo && lpPlayInfo->lpsmSock)
		lpPlayInfo->lpsmSock->Send((char*)&smTransHgInfo, smTransHgInfo.size, TRUE);
}

void CHellsGate::Main()
{
	smTRANS_COMMAND		smTransCommand;
	TRANS_CHATMESSAGE	TransChatMessage;

	SYSTEMTIME  st;
	GetLocalTime(&st);

	if (!m_vHellsGateInfo.empty())
	{
		if (m_nState == STATE_STOP)
		{
			for (unsigned i = 0; i < m_vHellsGateInfo.size(); i++)
			{
				//Abre a arena minutos antes do evento iniciar
				if (st.wHour == m_vHellsGateInfo[i].nHora - 1 && st.wMinute == 55)
				{
					SERVERCHAT->SendChatAllEx(EChatColor::CHATCOLOR_Global, "HellsGate> > A Arena Infernal está aberta!");
					ZeroMemory(&TransChatMessage, sizeof(TRANS_CHATMESSAGE));
					sprintf_s(TransChatMessage.szMessage, "> A Arena Infernal está aberta! (cuidado)");
					TransChatMessage.code = smTRANSCODE_WHISPERMESSAGE;
					TransChatMessage.size = 32 + lstrlen(TransChatMessage.szMessage);
					TransChatMessage.dwIP = 3;
					TransChatMessage.dwObjectSerial = 0;

					for (int cnt = 0; cnt < CONNECTMAX; cnt++)
					{
						if (rsPlayInfo[cnt].lpsmSock && rsPlayInfo[cnt].dwObjectSerial)
						{
							rsPlayInfo[cnt].lpsmSock->Send((char*)&TransChatMessage, TransChatMessage.size, true);
						}
					}

					//AddNpc();

					m_bEventFlag = true;
					m_nState = STATE_HG_INIT;
					m_nEventIndex = i;
					m_dwEventTime = 0;
					m_nEventStage = 0;
					m_dwDelayTime = dwPlayServTime + (5 * 60 * 1000); //Tempo restando para iniciar o evento
					break;
				}
			}
		}

		//Inicia o evento
		if (m_nState == STATE_HG_INIT && st.wHour == m_vHellsGateInfo[m_nEventIndex].nHora && st.wMinute == 0)
		{
			//Se tiver players
			if (!m_vPlayersInfo.empty())
			{
				SERVERCHAT->SendChatAllEx(EChatColor::CHATCOLOR_Global, "HellsGate> > A Arena Infernal começou!");
				ZeroMemory(&TransChatMessage, sizeof(TRANS_CHATMESSAGE));
				sprintf_s(TransChatMessage.szMessage, "A Arena Infernal começou!(boss)");
				TransChatMessage.code = smTRANSCODE_WHISPERMESSAGE;
				TransChatMessage.size = 32 + lstrlen(TransChatMessage.szMessage);
				TransChatMessage.dwIP = 3;
				TransChatMessage.dwObjectSerial = 0;

				for (int cnt = 0; cnt < CONNECTMAX; cnt++)
				{
					if (rsPlayInfo[cnt].lpsmSock && rsPlayInfo[cnt].dwObjectSerial)
					{
						rsPlayInfo[cnt].lpsmSock->Send((char*)&TransChatMessage, TransChatMessage.size, true);
					}
				}

				m_nState = STATE_HG_START;
			}
			else
			{
				//Se nao tiver player, finaliza
				m_bEventFlag = false;
				m_dwDelayTime = 0;
				m_nState = STATE_HG_END;
			}
		}

		if (m_nState == STATE_HG_START)
		{
			if (m_dwEventTime == 0 && m_nEventStage == 0)
			{
				//Iniciar primeiro estagio 
				m_dwEventTime = dwPlayServTime + (m_vHellsGateInfo[m_nEventIndex].nTempo * 60 * 1000);
				m_dwDelayTime = 0;
			}
			else
			{
				if (m_dwEventTime > dwPlayServTime)
				{
					if (m_lpCharBoss == NULL)
					{
						//Enquanto o estagio for menor que a quantidade de Boss
						if ((unsigned)m_nEventStage < m_vMonsterInfo.size())
						{
							if (m_dwDelayTime < dwPlayServTime)
							{
								m_nEventStage++;

								AddMonster(m_nEventStage);

								for (auto player : m_vPlayersInfo)
								{
									rsPLAYINFO* lpPlayInfo = srFindUserFromSerial(player->dwObjectSerial);
									if (lpPlayInfo && lpPlayInfo->Position.Area == 23)
									{
										SendNextStage(lpPlayInfo);
									}
								}
							}

						}
						else
						{
							//Finaliza o evento
							m_bEventFlag = false;
							m_dwDelayTime = 0;
							m_nEventStage = 0;
							m_nState = STATE_HG_END;
						}
					}

					if (m_lpCharBoss)
					{
						//Enquanto o Boss estiver vivo
						if (m_lpCharBoss->smCharInfo.Life[0] > 0
							&& m_lpCharBoss->MotionInfo
							&& m_lpCharBoss->MotionInfo->State != CHRMOTION_STATE_DEAD)
						{
							//Verifica se algum monstro morreu e remove do vector
							if (!m_vlpCharMonster.empty())
							{
								for (unsigned i = 0; i < m_vlpCharMonster.size(); i++)
								{
									if (m_vlpCharMonster[i] && m_vlpCharMonster[i]->Flag)
									{
										if (m_vlpCharMonster[i]->smCharInfo.Life[0] <= 0
											&& m_vlpCharMonster[i]->MotionInfo
											&& m_vlpCharMonster[i]->MotionInfo->State == CHRMOTION_STATE_DEAD)
										{
											m_vlpCharMonster.erase(m_vlpCharMonster.begin() + i);
										}
									}
									else
									{
										m_vlpCharMonster.erase(m_vlpCharMonster.begin() + i);
									}
								}
							}

							//Adiciona mais mosntros se necessario
							AddMonster(m_nEventStage);
						}
						else
						{
							//O Boss morreu
							m_lpCharBoss = NULL;
							KillMonster();
							m_dwDelayTime = dwPlayServTime + (20 * 1000); //Delay pra nascer o proximo Boss

							for (auto player : m_vPlayersInfo)
							{
								rsPLAYINFO* lpPlayInfo = srFindUserFromSerial(player->dwObjectSerial);
								if (lpPlayInfo && lpPlayInfo->Position.Area == 23)
								{
									SendNextStage(lpPlayInfo);
								}
							}
						}
					}
				}
				else
				{
					//Acabou o tempo limite do evento
					m_bEventFlag = false;
					m_nEventStage = 0;
					m_dwDelayTime = 0;
					m_nState = STATE_HG_END;
				}
			}
		}

		if (m_nState == STATE_HG_END)
		{
			//Finaliza o evento
			if (m_dwDelayTime == 0)
			{
				KillBoss();
				KillMonster();
				DelNpc();
				SERVERCHAT->SendChatAllEx(EChatColor::CHATCOLOR_Global, "HellsGate> > A Arena Infernal terminou!");
				ZeroMemory(&TransChatMessage, sizeof(TRANS_CHATMESSAGE));
				sprintf_s(TransChatMessage.szMessage, "> A Arena Infernal terminou! (palmas)");
				TransChatMessage.code = smTRANSCODE_WHISPERMESSAGE;
				TransChatMessage.size = 32 + lstrlen(TransChatMessage.szMessage);
				TransChatMessage.dwIP = 3;
				TransChatMessage.dwObjectSerial = 0;

				for (int cnt = 0; cnt < CONNECTMAX; cnt++)
				{
					if (rsPlayInfo[cnt].lpsmSock && rsPlayInfo[cnt].dwObjectSerial)
					{
						rsPlayInfo[cnt].lpsmSock->Send((char*)&TransChatMessage, TransChatMessage.size, true);
					}
				}

				m_nEventStage = 0;
				m_dwDelayTime = dwPlayServTime + 30 * 1000; //Delay pra teleportar os players pra fora da arena

				ZeroMemory(&TransChatMessage, sizeof(TRANS_CHATMESSAGE));
				SERVERCHAT->SendChatAllEx(EChatColor::CHATCOLOR_Global, "HellsGate> > Todos serão teleportados em 30 segundos.");
				sprintf_s(TransChatMessage.szMessage, "> Você será teleportado em 30 segundos.");
				TransChatMessage.code = smTRANSCODE_WHISPERMESSAGE;
				TransChatMessage.size = 32 + lstrlen(TransChatMessage.szMessage);
				TransChatMessage.dwIP = 3;
				TransChatMessage.dwObjectSerial = 0;

				for (auto player : m_vPlayersInfo)
				{
					rsPLAYINFO* lpPlayInfo = srFindUserFromSerial(player->dwObjectSerial);
					if (lpPlayInfo && lpPlayInfo->Position.Area == 23)
					{
						lpPlayInfo->lpsmSock->Send((char*)&TransChatMessage, TransChatMessage.size, true);
						SendNextStage(lpPlayInfo);
					}
				}

				Reward();
			}

			if (m_dwDelayTime && m_dwDelayTime < dwPlayServTime)
			{
				ZeroMemory(&smTransCommand, sizeof(smTRANS_COMMAND));
				//Teleportar player pra fora da arena
				for (auto player : m_vPlayersInfo)
				{
					rsPLAYINFO* lpPlayInfo = srFindUserFromSerial(player->dwObjectSerial);
					if (lpPlayInfo && lpPlayInfo->Position.Area == 23)
					{
						smTransCommand.size = sizeof(smTRANS_COMMAND);
						smTransCommand.code = smTRANSCODE_HG_LEAVE;
						lpPlayInfo->lpsmSock->Send((char*)&smTransCommand, smTransCommand.size, TRUE);
					}
					delete player;
				}

				m_vPlayersInfo.clear();
				m_nState = STATE_STOP;
				m_nEventIndex = 0;
				m_dwEventTime = 0;
				m_dwDelayTime = 0;
			}
		}
	}
}

void CHellsGate::Accept(rsPLAYINFO* lpPlayInfo)
{
	if (m_nState == STATE_STOP || m_nState == STATE_HG_END)
		return;

	if (!lpPlayInfo || !lpPlayInfo->lpsmSock)
		return;

	//Se o player sair do evento, ele pode entrar novamente
	for (auto player : m_vPlayersInfo)
	{
		if (!lstrcmpi(player->PlayerName, lpPlayInfo->szName))
		{
			player->dwObjectSerial = lpPlayInfo->dwObjectSerial;

			SendNextStage(lpPlayInfo);
			Teleport(lpPlayInfo);
			return;
		}
	}

	if (m_vPlayersInfo.size() >= (unsigned)m_vHellsGateInfo[m_nEventIndex].nPLimite)
	{
		//Atingiu o Limite de Players
		TRANS_CHATMESSAGE TransChatMessage;


		SERVERCHAT->SendChatAllEx(EChatColor::CHATCOLOR_Global, "HellsGate> > A Arena está cheia!");
		ZeroMemory(&TransChatMessage, sizeof(TRANS_CHATMESSAGE));
		sprintf_s(TransChatMessage.szMessage, "> A Arena está cheia! (cuidado)");
		TransChatMessage.code = smTRANSCODE_WHISPERMESSAGE;
		TransChatMessage.size = 32 + lstrlen(TransChatMessage.szMessage);
		TransChatMessage.dwIP = 3;
		TransChatMessage.dwObjectSerial = 0;

		if (lpPlayInfo->lpsmSock)
			lpPlayInfo->lpsmSock->Send((char*)&TransChatMessage, TransChatMessage.size, TRUE);
		return;
	}

	//Adiciona o novo Player
	sPlayerInfo* player = new sPlayerInfo;

	if (player)
	{
		sprintf_s(player->PlayerName, lpPlayInfo->szName);
		sprintf_s(player->PlayerID, lpPlayInfo->szID);
		sprintf_s(player->PlayerIP, lpPlayInfo->lpsmSock->szIPAddr);
		player->dwObjectSerial = lpPlayInfo->dwObjectSerial;

		m_vPlayersInfo.push_back(player);

		SendNextStage(lpPlayInfo);
		Teleport(lpPlayInfo);
	}
}

void CHellsGate::Reward()
{
	//recompensa
	TRANS_CHATMESSAGE	TransChatMessage;
	TRANS_ITEMINFO		TransItemInfo;
	psITEM* lpsItem;

	for (auto player : m_vPlayersInfo)
	{
		rsPLAYINFO* lpPlayInfo = srFindUserFromSerial(player->dwObjectSerial);
		if (lpPlayInfo && lpPlayInfo->lpsmSock && lpPlayInfo->Position.Area == 23 && m_vHellsGateInfo[m_nEventIndex].szItemID[0])
		{
			lpsItem = new psITEM;
			srSetItemFromCode(lpsItem, m_vHellsGateInfo[m_nEventIndex].szItemID);

			ZeroMemory(&TransItemInfo, sizeof(TRANS_ITEMINFO));
			TransItemInfo.code = smTRANSCODE_PUTITEM;
			TransItemInfo.size = sizeof(TRANS_ITEMINFO);
			memcpy(&TransItemInfo.Item, &lpsItem->ItemInfo, sizeof(sITEMINFO));
			rsRegist_ItemSecCode(lpPlayInfo, &TransItemInfo, 1);

			lpPlayInfo->lpsmSock->Send((char*)&TransItemInfo, TransItemInfo.size, true);

			ZeroMemory(&TransChatMessage, sizeof(TRANS_CHATMESSAGE));
			sprintf_s(TransChatMessage.szMessage, "> Você Recebeu %s como Recompensa!", lpsItem->ItemInfo.ItemName);
			TransChatMessage.code = smTRANSCODE_WHISPERMESSAGE;
			TransChatMessage.size = 32 + lstrlen(TransChatMessage.szMessage);
			TransChatMessage.dwIP = 3;
			TransChatMessage.dwObjectSerial = 0;

			lpPlayInfo->lpsmSock->Send((char*)&TransChatMessage, TransChatMessage.size, true);

			delete lpsItem;
		}
	}
}

void CHellsGate::Teleport(rsPLAYINFO* lpPlayInfo)
{
	smTRANS_COMMAND smTransCommand;

	int x = -3626;
	int z = -43500;
	x <<= FLOATNS;
	z <<= FLOATNS;

	smTransCommand.size = sizeof(smTRANS_COMMAND);
	smTransCommand.code = smTRANSCODE_HG_ENTER;
	smTransCommand.WParam = 23;
	smTransCommand.LParam = x;
	smTransCommand.SParam = z;

	if (lpPlayInfo)
		lpPlayInfo->lpsmSock->Send((char*)&smTransCommand, smTransCommand.size, TRUE);
}
