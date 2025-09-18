#pragma once


struct PacketRelicInfo
{
	int size, code;
	int bRelic[12];
};

class CRelicHandler
{
public:
	static CRelicHandler* getInstance();

	void SendRelicInfo(rsPLAYINFO* lpPlayInfo);

	void UnlockRelic(rsPLAYINFO* lpPlayInfo, char* RelicCode);
	void UnlockRelic(rsPLAYINFO* lpPlayInfo, int Kind);

	int Relic[12] = {};
};

#define RELICHANDLER CRelicHandler::getInstance()