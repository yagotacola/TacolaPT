#include "sinbaram/sinLinkHeader.h"
#include "Alerta.h"
#include "srcserver\\onserver.h"
#include <Database/SQLConnection.h>
Alerta cAlertaHandler;

Alerta* Alerta::getInstance()
{
    return &cAlertaHandler;
}

void Alerta::Init()
{
    vEnabled.clear();
    auto db = SQLConnection::GetConnection(DATABASEID_ServerDB);

    if (db->Open())
    {
        if (db->Prepare("SELECT ItemCode FROM DropLogAlert"))
        {
            if (db->Execute(false))
            {
                while (db->NextRow())
                {
                    char ItemCode[32];
                    db->GetData(1, PARAMTYPE_String, ItemCode);

                    for (int cnt = 0; cnt < MAX_ITEM; cnt++)
                    {
                        if (!lstrcmpi(sItem[cnt].LastCategory, ItemCode))
                        {
                            vEnabled[sItem[cnt].CODE] = true;
                            break;
                        }
                    }
                }
            }
        }
        db->Close();
    }
}

void Alerta::AddItemLog(rsPLAYINFO* lpPlayInfo, smCHAR* lpChar, sITEMINFO* lpItemInfo)
{
    if (!vEnabled[lpItemInfo->CODE])
        return;

    AlertaInfo sLog;
    sLog.Head = lpItemInfo->ItemHeader.Head;
    sLog.ChkSum = lpItemInfo->ItemHeader.dwChkSum;
    lstrcpy(sLog.ItemName, lpItemInfo->ItemName);
    vAlertaInfo.push_back(sLog);
}

using namespace std;


void SendMessageToAll32(std::string sender, std::string message)
{
    SERVERCHAT->SendChatAllEx(EChatColor::CHATCOLOR_Global, "%s> %s", sender.c_str(), message.c_str());
}

void Alerta::ProcessItemLog(char* PlayerName, DWORD Code, DWORD Head, DWORD ChkSum)
{
    if (!vEnabled[Code])
        return;

    for (auto it = vAlertaInfo.begin(); it != vAlertaInfo.end(); it++)
    {
        auto sLog = (*it);
        if (sLog.Head == Head && sLog.ChkSum == ChkSum)
        {

            TRANS_CHATMESSAGE	TransChatMessage;
            rsPLAYINFO* lpPlayInfo;
            char mensagem[70] = { 0 };
            wsprintf(mensagem, " [ %s ] Dropou [ %s ]. ", PlayerName, sLog.ItemName);
            //rsSendMessageAll(mensagem, 15);
            SendMessageToAll32("Arena", mensagem);
           // SERVERCHAT->SendChatEx(Player, EChatColor::CHATCOLOR_Global, "SorteioHG> Parabéns [%s] acaba de ganhar um [%s]", lpPlayInfo->szName, lpsItem->ItemInfo.ItemName);
            //	rsSendServerChatMessageToUser2(3, mensagem);

            TransChatMessage.code = smTRANSCODE_MESSAGEBOX;
            TransChatMessage.dwIP = 0;
            TransChatMessage.dwObjectSerial = 0;
            wsprintf(TransChatMessage.szMessage, mensagem);
            TransChatMessage.size = 32 + lstrlen(TransChatMessage.szMessage);
            lpPlayInfo->lpsmSock->Send((char*)&TransChatMessage, TransChatMessage.size, TRUE);

            vAlertaInfo.erase(it);
            break;
        }
    }
}