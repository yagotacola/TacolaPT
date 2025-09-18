#include <GameCore.h>
#include "ChatHandle.h"
#include "character.h"
#include "..//TCore.h"


extern smCONFIG	smConfig;
extern int WarpField2(int Num);
extern int ServerHideMode;
extern int WaveCameraMode;

extern smCHAR_INFO* sinChar;


namespace CHAT
{

	Handle::Handle() : CBaseHandle()
	{

	}
	Handle::Handle(EHandle eID) : CBaseHandle(eID)
	{

	}
	Handle::~Handle()
	{

	}
	void Handle::Init()
	{

	}
	void Handle::Shutdown()
	{

	}
	void Handle::ProcessPacket(PacketItemLinkChat* psPacket, BOOL bLoginServer)
	{
		psPacket->code = PACKET_CHATITEMLINK;

		bLoginServer ? smWsockServer->Send((char*)psPacket, psPacket->size, TRUE) : smWsockUserServer->Send((char*)psPacket, psPacket->size, TRUE);
	}
	void Handle::AddChatBoxText(char* pszText, EChatColor iColor)
	{
		extern int GameMode;

		if (GameMode == 2)
			CHATBOX->AddMessage(pszText, iColor);
	}
	void Handle::AddChatBoxTextEx(EChatColor iColor, char* pszText, ...)
	{
		va_list vl;

		char szText[128];

		va_start(vl, pszText);
		_vsnprintf_s(szText, _countof(szText), _TRUNCATE, pszText, vl);
		va_end(vl);

		AddChatBoxText(szText, iColor);
	}
	void Handle::SendChat(BOOL bLoginServer, const char* pszChat)
	{
		extern smWINSOCK* smWsockServer;
		extern smWINSOCK* smWsockDataServer;

		int iChatLen = STRLEN(pszChat);

		if ((iChatLen < MAX_CHATLENGTH) && (iChatLen > 0))
		{
			PacketChat sPacket;
			sPacket.size = sizeof(PacketChat) + iChatLen + 1;
			sPacket.code = PACKET_CHAT_GAME;
			STRINGCOPY(sPacket.szChat, pszChat);

			bLoginServer ? smWsockServer->Send((char*)&sPacket, sPacket.size, TRUE) : smWsockUserServer->Send((char*)&sPacket, sPacket.size, TRUE);
		}
	}
	BOOL Handle::AnalyzeChat(char* pszBuff)
	{
		bool iRet = TRUE;

		char szChatCommandParam1[256] = { 0 };

		// Comandos Player
		if (ChatCommand("/camera_wave_off", pszBuff))
		{
			WaveCameraMode = FALSE;
		}
		else if (ChatCommand("/camera_wave_on", pszBuff))
		{
			WaveCameraMode = TRUE;
		}
		else if (ChatCommand("/save", pszBuff))
		{
			if (SaveGameData())
				CHATBOX->AddMessage("> Jogo salvo com sucesso.");
			else
				CHATBOX->AddMessage("> Falha ao salvar.");
		}
		else if (ChatCommand("/ranking", pszBuff))
		{
			RankingWindow::GetInstance()->OpenNPCRanking();
		}
		else if (ChatCommand("/mix", pszBuff))
		{
			MixWindow::GetInstance()->ReadMix();
		}
		else if (ChatCommand("/damage", pszBuff))
		{
			if (smConfig.showDamage)
			{
				smConfig.showDamage = FALSE;
				CHATBOX->AddMessage("> Mostrador de dano Ligado!");
			}
			else
			{
				smConfig.showDamage = TRUE;
				CHATBOX->AddMessage("> Mostrador de dano desligado!");
			}
		}
		else if (ChatCommand("/fps", pszBuff))
		{
			extern BOOL bShowFPS;
			
			if (bShowFPS)
			{
			
				bShowFPS = FALSE;
				CHATBOX->AddMessage("> FPS agora não está visível");
				
			}
			else
			{
				bShowFPS = TRUE;
				CHATBOX->AddMessage("> FPS está agora visível");
				
			}
		}
		else if (ChatCommand("/vip", pszBuff))
		{
			if (VIP::GetInstance()->getVipLevel())
				VIP::GetInstance()->vipCommands();
		}

		if (lpCurPlayer->vipLevel > 0) {
			if (ChatCommand("/core", pszBuff))
			{
				TCORE::GetInstance()->tcoreOpen();
			}
			
			
		}


		// Comandos GM
		if (smConfig.DebugMode)
		{
			if (ChatCommand("/set_absorb", pszBuff))
			{
				if (GetParameterString(pszBuff, 1, szChatCommandParam1))
				{
					if (lpCharSelPlayer != nullptr && lpCharSelPlayer->smCharInfo.State == smCHAR_STATE_ENEMY)
					{
						SendChat(FALSE, FormatString("/set_absorb %d %d", lpCharSelPlayer->dwObjectSerial, atoi(szChatCommandParam1)));
						iRet = FALSE;
					}
				}
			}
			
			else if (ChatCommand("/talk", pszBuff))
			{
				if (GetParameterString(pszBuff, 1, szChatCommandParam1))
				{
					if (lpCharSelPlayer != nullptr && lpCharSelPlayer->smCharInfo.State != smCHAR_STATE_USER)
					{
						SendChat(FALSE, FormatString("/talk %d %s", lpCharSelPlayer->dwObjectSerial, szChatCommandParam1));
						iRet = FALSE;
					}
				}
			}

			else if (ChatCommand("/field", pszBuff))
			{
				GetParameterString(pszBuff, 1, szChatCommandParam1);
				WarpField2(atoi(szChatCommandParam1));
			}

			else if (ChatCommand("/hide", pszBuff))
			{
				ServerHideMode = TRUE;
				CHATBOX->AddMessage("> Você agora está invisível");
			}

			else if (ChatCommand("/show", pszBuff))
			{
				ServerHideMode = FALSE;
				CHATBOX->AddMessage("> Você agora está visível");
			}

			else if (ChatCommand("/PassRankUp", pszBuff))
			{
				if (sinChar->ChangeJob < 3)
				{
					sinChar->ChangeJob++;
					CSKILL->SearchUseSkill();
					CHATBOX->AddMessage("> Você passou de ranque!");
				}
				else
					CHATBOX->AddMessage("> Ranque máximo atingido!");
			}
		}

		return iRet;
	}
}