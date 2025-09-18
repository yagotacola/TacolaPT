#pragma once
#include "sinbaram\\sinLinkHeader.h"

//#define DISABLE_TRADEUPGRADE

struct RangeItem
{
	int StartNum;
	int EndNum;
};

class ModifyItem
{
public:
	ModifyItem();
	~ModifyItem();

	int GetNextItem(int Code, int Base);
	int GetUpgradeItem(int Code);

	void Load();
	void SetFlag(int Flag);
	void PushSequence(std::string Sequence);

	bool IsItemOkay(sITEM* Item);
	bool IsStoneOkay(sITEM* Item);
	bool IsAtRange(sITEM* Item);

	bool GetResultFromItem(sITEM* Item, sITEMINFO* Buffer, byte Operation, int Type, int Spec);
private:
	int m_Flag;

	std::vector<std::vector<int>> m_Upgrades;
};

extern ModifyItem rsModifyItem;

