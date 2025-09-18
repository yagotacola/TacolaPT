#pragma once



struct PacketOpenDistribuidor
{
	int size, code;

	struct {
		int ID;
		int Section;
		sITEMINFO ItemInfo;
		int AmountItens;
		SYSTEMTIME ExpireItem;
	} Items[13];
	int Count;
	bool bFirst;
};

struct PacketGetItem
{
	int size, code;

	int Section;
	char ItemCode[32];
	int ID;
};

class cDistribuidorHandler
{
public:
	static cDistribuidorHandler* getInstance();

	void SendOpenDistribuidor(rsPLAYINFO* lpPlayInfo);
	void HandlePacket(rsPLAYINFO* lpPlayInfo, PacketGetItem* psPacket);
	void DelItemDistribuidor(rsPLAYINFO* lpPlayInfo, PacketGetItem* psPacket);
	void InsertDistribuidor(rsPLAYINFO* lpPlayInfo, char* CodeIT, int AmountItens = 1, int DateEnd = 7);
	void InsertDistribuidor(char* playerName, char* CodeIT, int AmountItens, int DateEnd);
	void YouHaveItem(rsPLAYINFO* lpPlayInfo);
};

#define DISTRIBUIDORHANDLER cDistribuidorHandler::getInstance()