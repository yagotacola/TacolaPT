#include "sinbaram/sinLinkHeader.h"

#include "cDistribuidorHandler.h"

#include <Database/SQLConnection.h>

cDistribuidorHandler* pcDistribuidorHandler = nullptr;
extern int srSetItemFromCode(psITEM* lpsItem, char* szCoed);

void SendMessageEvent(rsPLAYINFO* lpPlayInfo, char* Message)
{
	TRANS_CHATMESSAGE sPacket;
	sPacket.code = smTRANSCODE_MESSAGEBOX;
	lstrcpy(sPacket.szMessage, Message);
	sPacket.size = lstrlen(sPacket.szMessage) + 32;
	lpPlayInfo->lpsmSock->Send((char*)&sPacket, sPacket.size, TRUE);
}

char* FormatString(char* fmt, ...)
{
	static char buff[4096];

	ZeroMemory(buff, sizeof(buff));

	va_list args;

	va_start(args, fmt);
	vsprintf(buff, fmt, args);
	va_end(args);

	return buff;
}



extern int CreateCommandItem(rsPLAYINFO* lpPlayInfo, rsPLAYINFO* lpPlayInfo2, char* szItem);
extern int RecordLog(char* lpLogName, char* lpBuff);
extern int	rsSendMoneyToUser(rsPLAYINFO* lpPlayInfo, int Money);
extern int rsSendMessageAll(char* szText, DWORD dwColor);

cDistribuidorHandler* cDistribuidorHandler::getInstance()
{
	if (!pcDistribuidorHandler)
		pcDistribuidorHandler = new cDistribuidorHandler();
	return pcDistribuidorHandler;
}

void cDistribuidorHandler::SendOpenDistribuidor(rsPLAYINFO* lpPlayInfo)
{
	if (!lpPlayInfo || !lpPlayInfo->lpsmSock)
		return;

	auto db = SQLConnection::GetConnection(DATABASEID_ServerDB);
	PacketOpenDistribuidor sPacket;
	sPacket.code = OPCODE_OPEN_DISTRIBUIDOR;
	sPacket.size = sizeof(sPacket);
	sPacket.Count = 0;
	sPacket.bFirst = true;

	if (db->Open())
	{

		if (db->Prepare("SELECT ID FROM DistribuidorItem Where PlayerName = ? And GetDate() >= DateEnd"))
		{
			char playerName[32];  lstrcpy(playerName, lpPlayInfo->szName);

			db->BindInputParameter(playerName, 1, PARAMTYPE_String);
			if (db->Execute(false))
			{
				while (db->NextRow())
				{

					db->GetData(1, PARAMTYPE_Integer, &sPacket.Items[sPacket.Count].ID, 4);

					if (db->Prepare("DELETE FROM DistribuidorItem WHERE ID=?"))
					{
						db->BindInputParameter(&sPacket.Items[sPacket.Count].ID, 1, PARAMTYPE_Integer);
						db->Execute(false);
					}

				}
			}
		}

		db->Close();
	}

	if (db->Open())
	{
		if (db->Prepare("SELECT  ID, CodeIT, AmountItens, DateEnd, SubTag FROM DistribuidorItem Where PlayerName=? ORDER BY DateStart DESC"))
		{
			char playerName[32];  lstrcpy(playerName, lpPlayInfo->szName);

			db->BindInputParameter(playerName, 1, PARAMTYPE_String);

			if (db->Execute(false))
			{
				while (db->NextRow())
				{
					char ItemCode[32];
					db->GetData(1, PARAMTYPE_Integer, &sPacket.Items[sPacket.Count].ID, 4);
					db->GetData(2, PARAMTYPE_String, ItemCode, 32);
					db->GetData(3, PARAMTYPE_Integer, &sPacket.Items[sPacket.Count].AmountItens, 4);
					db->GetData(4, PARAMTYPE_Time, &sPacket.Items[sPacket.Count].ExpireItem, sizeof(SYSTEMTIME));
					db->GetData(5, PARAMTYPE_Integer, &sPacket.Items[sPacket.Count].Section, 4);

					psITEM psItem;

					if (srSetItemFromCode(&psItem, ItemCode))
					{
						memcpy(&sPacket.Items[sPacket.Count].ItemInfo, &psItem.ItemInfo, sizeof(sITEMINFO));
						sPacket.Count++;

						if (sPacket.Count >= 13)
						{
							lpPlayInfo->lpsmSock->Send((char*)&sPacket, sPacket.size, TRUE);
							ZeroMemory(sPacket.Items, sizeof(sPacket.Items));
							sPacket.Count = 0;
							sPacket.bFirst = false;
						}
					}
				}
			}
		}
		db->Close();
	}

	lpPlayInfo->lpsmSock->Send((char*)&sPacket, sPacket.size, TRUE);
}


void cDistribuidorHandler::HandlePacket(rsPLAYINFO* lpPlayInfo, PacketGetItem* psPacket)
{
	auto db = SQLConnection::GetConnection(DATABASEID_ServerDB);



	if (db->Open())
	{
		if (db->Prepare("SELECT AmountItens, CodeIT FROM DistribuidorItem WHERE  PlayerName=? And ID=?"))
		{
			char playerName[32];  lstrcpy(playerName, lpPlayInfo->szName);

			db->BindInputParameter(playerName, 1, PARAMTYPE_String);
			db->BindInputParameter(&psPacket->ID, 2, PARAMTYPE_Integer);

			int AmountItens; char ItemCode[32];
			char szbuff[255] = { 0 };

			if (db->Execute())
			{

				db->GetData(1, PARAMTYPE_Integer, &AmountItens, 4 );
				db->GetData(2, PARAMTYPE_String, ItemCode, 32 );

				psITEM psItem;

				if (srSetItemFromCode(&psItem, ItemCode))
				{
					if (psItem.ItemInfo.CODE == (sinGG1 | sin01))
					{
						rsSendMoneyToUser(lpPlayInfo, AmountItens);
						//RecordLog("Distribuidor", FormatString("O player [ %s ] retirou [ %d ] de gold!", playerName, AmountItens));
					}
					else
					{
						for (int i = 1; i <= AmountItens; i++)
						{
							CreateCommandItem(lpPlayInfo, lpPlayInfo, ItemCode);
						}

						//RecordLog("Distribuidor", FormatString("O player [ %s ] retirou o item ( [ %s - [%s] @%d@%d ] ) - Quantidade= %d", playerName, psItem.ItemInfo.ItemName, ItemCode, psItem.ItemInfo.ItemHeader.Head, psItem.ItemInfo.ItemHeader.dwChkSum, AmountItens));
					}
				}


				SendMessageEvent(lpPlayInfo, "Recolhido com Sucesso!");


				if (db->Prepare("DELETE FROM DistribuidorItem  WHERE  PlayerName=? And ID=?"))
				{
					char playerName[32];  lstrcpy(playerName, lpPlayInfo->szName);
					db->BindInputParameter(playerName, 1, PARAMTYPE_String);
					db->BindInputParameter(&psPacket->ID, 2, PARAMTYPE_Integer);
					db->Execute(false);
				}

				SendOpenDistribuidor(lpPlayInfo);
			}
		}
		db->Close();

	}

}


void cDistribuidorHandler::DelItemDistribuidor(rsPLAYINFO* lpPlayInfo, PacketGetItem* psPacket)
{
	auto db = SQLConnection::GetConnection(DATABASEID_ServerDB);

	if (db->Open())
	{

		if (db->Prepare("DELETE FROM DistribuidorItem  WHERE  PlayerName=? And ID=?"))
		{
			char playerName[32];  lstrcpy(playerName, lpPlayInfo->szName);
			db->BindInputParameter(playerName, 1, PARAMTYPE_String);
			db->BindInputParameter(&psPacket->ID, 2, PARAMTYPE_Integer);
			SendMessageEvent(lpPlayInfo, "Item Deletado Com Sucesso!");
			db->Execute(false);
		}

		db->Close();
	}
}

void cDistribuidorHandler::InsertDistribuidor(rsPLAYINFO* lpPlayInfo, char* CodeIT, int AmountItens, int DateEnd)
{
	auto db = SQLConnection::GetConnection(DATABASEID_ServerDB);

	if (db->Open())
	{
		char query[255] = { 0 };

		wsprintf(query, "INSERT INTO DistribuidorItem  ([PlayerName],[CodeIT],[AmountItens],[DateStart],[DateEnd],[SubTag]) values (?,?,?,GetDate(),DATEADD(HOUR, %d, Getdate()),%d)", DateEnd * 24, 5);

		if (db->Prepare(query))
		{
			char playerName[32];  lstrcpy(playerName, lpPlayInfo->szName);
			db->BindInputParameter(playerName, 1, PARAMTYPE_String);
			db->BindInputParameter(CodeIT, 2, PARAMTYPE_String);
			db->BindInputParameter(&AmountItens, 3, PARAMTYPE_Integer);
			db->Execute(false);
		}
		db->Close();
	}
}


void cDistribuidorHandler::InsertDistribuidor(char* playerName, char* CodeIT, int AmountItens, int DateEnd)
{
	auto db = SQLConnection::GetConnection(DATABASEID_ServerDB);

	if (db->Open())
	{
		char query[255] = { 0 };

		wsprintf(query, "INSERT INTO DistribuidorItem  ([PlayerName],[CodeIT],[AmountItens],[DateStart],[DateEnd],[SubTag]) values (?,?,?,GetDate(),DATEADD(HOUR, %d, Getdate()),%d)", DateEnd * 24, 5);

		if (db->Prepare(query))
		{
			db->BindInputParameter(playerName, 1, PARAMTYPE_String);
			db->BindInputParameter(CodeIT, 2, PARAMTYPE_String);
			db->BindInputParameter(&AmountItens, 3, PARAMTYPE_Integer);
			db->Execute(false);
		}
		db->Close();
	}
}


void cDistribuidorHandler::YouHaveItem(rsPLAYINFO* lpPlayInfo)
{
	auto db = SQLConnection::GetConnection(DATABASEID_ServerDB);
	TRANS_CHATMESSAGE TransChatMessage;

	if (db->Open())
	{
		if (db->Prepare("SELECT * FROM DistribuidorItem Where PlayerName=? ORDER BY DateStart DESC"))
		{
			char playerName[32];  lstrcpy(playerName, lpPlayInfo->szName);

			db->BindInputParameter(playerName, 1, PARAMTYPE_String);

			if (db->Execute())
			{
				wsprintf(TransChatMessage.szMessage, "> Você Possui Item no Distribuidor!");
				TransChatMessage.code = smTRANSCODE_WHISPERMESSAGE;
				TransChatMessage.size = 32 + lstrlen(TransChatMessage.szMessage);
				TransChatMessage.dwIP = 3;
				TransChatMessage.dwObjectSerial = 0;
				lpPlayInfo->lpsmSock->Send((char*)&TransChatMessage, TransChatMessage.size, TRUE);
			}
		}
		db->Close();
	}
}