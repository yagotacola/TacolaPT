#include "sinbaram/sinLinkHeader.h"
#include "CRelicHandler.h"
#include "Database/SQLConnection.h"
#include "SrcServer/onserver.h"
CRelicHandler cRelicHandler;


CRelicHandler* CRelicHandler::getInstance()
{
	return &cRelicHandler;
}

void CRelicHandler::SendRelicInfo(rsPLAYINFO* lpPlayInfo)
{
	PacketRelicInfo sPacket;
	sPacket.size = sizeof(sPacket);
	sPacket.code = OPCODE_RELIC_INFO;

	char PlayerName[32];
	wsprintf(PlayerName, "%s", lpPlayInfo->smCharInfo.szName);

	auto db = SQLConnection::GetConnection(DATABASEID_ServerDB);

	if (db->Open())
	{


		if (db->Prepare("IF NOT EXISTS(SELECT * FROM Reliquias WHERE PlayerName=?) BEGIN INSERT INTO Reliquias VALUES (?, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0) END"))
		{
			db->BindInputParameter(PlayerName, 1, PARAMTYPE_String);
			db->BindInputParameter(PlayerName, 2, PARAMTYPE_String);
			db->Execute();
		}

		char query[256] = { 0 };
		int i = 0;
		while (i <= 11)
		{

			wsprintf(query, "SELECT Relic%d From Reliquias Where PlayerName=?", i);

			if (db->Prepare(query))
			{
				db->BindInputParameter(PlayerName, 1, PARAMTYPE_String);

				if (db->Execute())
				{
					
					db->GetData(1, PARAMTYPE_Integer, &Relic[i]);
					lpPlayInfo->relic[i] = Relic[i];
				}

			}
			i++;
		}

		memcpy(sPacket.bRelic, Relic, sizeof(int) * 12);

		lpPlayInfo->lpsmSock->Send((char*)&sPacket, sPacket.size, TRUE);
		db->Close();
	}


}

void CRelicHandler::UnlockRelic(rsPLAYINFO* lpPlayInfo, char* RelicCode)
{
}


void CRelicHandler::UnlockRelic(rsPLAYINFO* lpPlayInfo, int Kind)
{
	char PlayerName[32];
	wsprintf(PlayerName, "%s", lpPlayInfo->smCharInfo.szName);

	if (Kind >= 0 && Kind <= 11)
	{
		auto db = SQLConnection::GetConnection(DATABASEID_ServerDB);

		if (db->Open())
		{
			char query[256] = { 0 };

			wsprintf(query, "UPDATE Reliquias SET Relic%d=1 WHERE PlayerName=?", Kind);

			if (db->Prepare(query))
			{
				db->BindInputParameter(PlayerName, 1, PARAMTYPE_String);

				db->Execute();

				SendRelicInfo(lpPlayInfo);
			}

			db->Close();
		}

	}

}