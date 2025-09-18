
#include "sinbaram/sinLinkHeader.h"
#include "srcserver\\onserver.h"
#include "cSorteio_.h"


extern int srSetItemFromCode(psITEM* lpsItem, char* szCoed);
extern int rsRegist_ItemSecCode(rsPLAYINFO* lpPlayInfo, TRANS_ITEMINFO* lpTransItemInfo, int NewItem);
extern int CreateCommandItem(rsPLAYINFO* lpPlayInfo, rsPLAYINFO* lpPlayInfo2, char* szItem);
extern int rsPutItem2(rsPLAYINFO* lpPlayInfo, sITEMINFO* lpItem);

extern int SendQuickMessage2(rsPLAYINFO* lpPlayInfo, char* szMessage);

extern int rsDeleteInvenItem(rsPLAYINFO* lpPlayInfo, DWORD dwCode, DWORD dwHead, DWORD dwChkSum);

extern int rsSendMessageAll(char* szText, DWORD dwColor);
extern int RecordLog(char* lpLogName, char* lpBuff);

extern int GetPostBoxFile(char* szID, char* szFileName);
int SendReward2(char* id, char* name, char* ItemName, int iQuantity, int gold)
{
    char	szFileName[64];


    if (!id[0]) return FALSE;

    GetPostBoxFile(id, szFileName);

    FILE* pFile = NULL;
    fopen_s(&pFile, szFileName, "a+");

    if (pFile)
    {
        for (int i = 0; i < iQuantity; i++)
        {
            fprintf(pFile, "%s		%s		%d		\"%s\"\r\n", name, ItemName, gold, "Recompensa de Desafio");
        }

        fclose(pFile);

        return TRUE;
    }

    return TRUE;
}


void cSorteio_::SendSorteio(rsPLAYINFO* lpPlayInfo)
{
#ifdef _W_SERVER
    if (lpPlayInfo)
    {
        SQL* SQL = SQL::GetInstance();

        if (SQL->IsConnected())
        {
            int QtnItens = 0;
            char szItem[50][16];
            char MsgPlayer[255] = { 0 };
            SQL->EnterSqlSection();

            if (SQL->Execute("SELECT * FROM [EPT].[dbo].[RoletaItens]"))
            {
                while (SQL->Fetch())
                {
                    SQL->GetDataValue(1, szItem[QtnItens]);
                    QtnItens++;
                }

                if (QtnItens <= 0) return;

                int cnt = rand() % QtnItens;

                psITEM* lpsItem = new psITEM;
                TRANS_ITEMINFO TransItemInfo;

               // CreateCommandItem(lpPlayInfo, lpPlayInfo, szItem[cnt]);

               // CreateItemPerf(lpsItem, szItem[cnt], 2);

                SendReward2(lpPlayInfo->szID, lpPlayInfo->szName, szItem[cnt], 1, 0);

                
            //    ReformItem(&lpsItem->ItemInfo);
             //   TransItemInfo.code = smTRANSCODE_PUTITEM;
              //  TransItemInfo.size = sizeof(TRANS_ITEMINFO);
              //  memcpy(&TransItemInfo.Item, &lpsItem->ItemInfo, sizeof(sITEMINFO));
              //  rsRegist_ItemSecCode(lpPlayInfo, &TransItemInfo, 1);


                wsprintf(MsgPlayer, "SorteioHG : %s Recolheu o Item Cod [%s] da RoletaKeys ->", lpPlayInfo->szName, szItem[cnt]);
                char msg[64] = { 0 };
                rsPLAYINFO* Player = nullptr;
                Player = FindUserFromID(lpPlayInfo->szID);

             
                RecordLog("SorteioHG", MsgPlayer);

                if (srSetItemFromCode(lpsItem, szItem[cnt]))
                {
                    SERVERCHAT->SendChatEx(Player, EChatColor::CHATCOLOR_Global, "SorteioHG> Parabéns [%s] acaba de ganhar um [%s]", lpPlayInfo->szName, lpsItem->ItemInfo.ItemName);

                    wsprintf(MsgPlayer, "SorteioHG : Parabéns %s acaba de ganhar um %s!", lpPlayInfo->szName, lpsItem->ItemInfo.ItemName);
                  //  rsSendMessageAll(MsgPlayer, 3);

                    ///*wsprintf(MsgPlayer, "Roleta de Itens : Parabéns %s acaba de ganhar um %s!", lpPlayInfo->szName, lpsItem->ItemInfo.ItemName);
                    //SendQuickMessage2(lpPlayInfo, MsgPlayer); */

                   //* wsprintf(MsgPlayer, "Loteria : %s Recolheu o Item Name[%s] Cod [%s] da RoletaKeys ->", lpPlayInfo->szName, lpsItem->ItemInfo.ItemName, szItem[cnt]);
                    RecordLog("SorteioItensKey", MsgPlayer);
                }
            }
        }
    }
#endif
}

void cSorteio_::RecvGetItemKeys(rsPLAYINFO* lpPlayInfo)
{
    smTRANS_COMMAND smTransCommand = { };
    int QtnsChaves = 1;

    for (int cnt = 1; cnt < INVEN_ITEM_INFO_MAX; cnt++)
    {
        if (lpPlayInfo->InvenItemInfo[cnt].dwCode == (sinSP1 | sin64))
            QtnsChaves++;
    }

    smTransCommand.size = sizeof(smTRANS_COMMAND);
    smTransCommand.code = OPCODE_RECVKEYS_SORTEIO_ITENS;
    smTransCommand.WParam = QtnsChaves;
    lpPlayInfo->lpsmSock->Send((char*)&smTransCommand, smTransCommand.size);
}

void cSorteio_::OpenNpcSorteio(rsPLAYINFO* lpPlayInfo)
{
    smTRANS_COMMAND sPacket;
    sPacket.code = OPCODE_OPEN_SORTEIO_ITENS;
    sPacket.size = sizeof(smTRANS_COMMAND);
    lpPlayInfo->lpsmSock->Send((char*)&sPacket, sPacket.size);
}