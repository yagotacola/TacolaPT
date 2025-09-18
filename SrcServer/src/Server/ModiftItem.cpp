#include "ModifyItem.h"
#include <Database/SQLConnection.h>
#include <Character/playmain.h>


extern void LeIniStr(char* Section, char* Key, char* szFileIni, char* Var1);

bool SplitByToken(const std::string& String, std::vector<std::string>& Output, char Token, bool RemoveToken)
{
	unsigned Position = String.find(Token);
	unsigned InitialPosition = 0;
	Output.clear();

	if (RemoveToken)
	{
		while (Position != std::string::npos)
		{
			Output.push_back(String.substr(InitialPosition, Position - InitialPosition));
			InitialPosition = Position + 1;

			Position = String.find(Token, InitialPosition);
		};

		Output.push_back(String.substr(InitialPosition, std::min<size_t>(Position, String.size()) - InitialPosition));
	}
	else
	{
		while (Position != std::string::npos)
		{
			Output.push_back(String.substr(InitialPosition, Position - InitialPosition + 1));
			InitialPosition = Position + 1;

			Position = String.find(Token, InitialPosition + 1);
		};

		Output.push_back(String.substr(InitialPosition, std::min<size_t>(Position, String.size()) - InitialPosition + 1));
	};

	return Output.empty() == true ? false : true;
}

ModifyItem rsModifyItem;

ModifyItem::ModifyItem()
{

}

ModifyItem::~ModifyItem()
{
}

int ModifyItem::GetNextItem(int Code, int Base)
{
	return 0;
}

int ModifyItem::GetUpgradeItem(int Code)
{
#ifdef DISABLE_TRADEUPGRADE
	return 0;
#else
	if (m_Flag == 1)
	{
		for (int i = 0; i < m_Upgrades.size(); i++)
		{
			for (int c = 0; c < m_Upgrades[i].size(); c++)
			{
				if (m_Upgrades[i][c] == Code)
				{
					if (c + 1 >= m_Upgrades[i].size())
						return 0;
					else
						return m_Upgrades[i][c + 1];
				}
			}
		}
	}
	return 0;
#endif
}

void ModifyItem::Load()
{
#ifdef DISABLE_TRADEUPGRADE
	return;
#else
	char Sequence[512] = { 0 };
	auto pcDB = SQLConnection::GetConnection(DATABASEID_ServerDB);
	if (pcDB->Open())
	{
		if (pcDB->Prepare("SELECT * FROM ServerDB.dbo.UpgradeSequence"))
		{
			pcDB->Execute();

			m_Flag = 1;
			while (true)
			{
				pcDB->GetData(2, PARAMTYPE_String,  Sequence, sizeof(Sequence) );
				this->PushSequence(Sequence);

				ZeroMemory(Sequence, sizeof(Sequence));
				if (!pcDB->NextRow())
					break;
			}
		}
		pcDB->Close();
	}
	m_Flag = 0;
#endif
}

void ModifyItem::SetFlag(int Flag)
{
	m_Flag = Flag;
}

void ModifyItem::PushSequence(std::string Sequence)
{
	std::vector<std::string> Codes;
	if (SplitByToken(Sequence, Codes, ' ', true))
	{
		std::vector<int> Data;
		for (unsigned i = 0; i < Codes.size(); i++)
		{
			for (int c = 0; c < MAX_ITEM; c++)
			{
				if (strcmpi(sItem[c].LastCategory, Codes[i].c_str()) == 0)
				{
					Data.push_back(sItem[c].CODE);
					break;
				}
			}
		}

		if (m_Flag == 1)
			m_Upgrades.push_back(Data);
	}
}

bool ModifyItem::IsItemOkay(sITEM* Item)
{
	if ((Item->CODE & sinITEM_MASK2) == sinSA1)
		return false;

	if (Item->sItemInfo.SpecialItemFlag[0] == CHECK_COPY_ITEM ||
		(Item->sItemInfo.ItemKindCode != ITEM_KIND_NORMAL && Item->sItemInfo.ItemKindCode != ITEM_KIND_AGING) ||
		(Item->sItemInfo.CODE & sinITEM_MASK2) == sinMA1 ||
		(Item->sItemInfo.CODE & sinITEM_MASK2) == sinMA2 ||
		(Item->sItemInfo.CODE & sinITEM_MASK2) == sinQW1 ||
		(Item->sItemInfo.CODE & sinITEM_MASK2) == sinPZ1 ||
		(Item->sItemInfo.CODE & sinITEM_MASK2) == sinPZ2 ||
		(Item->sItemInfo.CODE & sinITEM_MASK2) == sinFO1 ||
		(Item->sItemInfo.CODE & sinITEM_MASK2) == sinSP1 ||
		(Item->sItemInfo.CODE & sinITEM_MASK2) == sinWR1 ||
		(Item->sItemInfo.CODE & sinITEM_MASK2) == sinDR1 ||
		(Item->sItemInfo.CODE & sinITEM_MASK2) == sinGP1 ||
		(Item->sItemInfo.CODE & sinITEM_MASK2) == sinCH1 ||
		(Item->sItemInfo.CODE >= (sinOR2 | sin06) && Item->sItemInfo.CODE <= (sinOR2 | sin25)) ||
		Item->sItemInfo.CODE == (sinGF1 | sin01) ||
		Item->sItemInfo.CODE == (sinGF1 | sin02) ||
		Item->sItemInfo.CODE == (sinGF1 | sin05) ||
		Item->sItemInfo.CODE == (sinGF1 | sin06) ||
		Item->sItemInfo.CODE == (sinOR2 | sin27) ||
		Item->sItemInfo.CODE == (sinOA1 | sin32) ||
		Item->sItemInfo.CODE == (sinOR2 | sin28) ||
		Item->sItemInfo.CODE == (sinOA1 | sin33) ||
		Item->sItemInfo.CODE == (sinOR2 | sin29) ||
		Item->sItemInfo.CODE == (sinOA1 | sin34) ||
		Item->sItemInfo.CODE == (sinOR2 | sin30) ||
		Item->sItemInfo.CODE == (sinOA1 | sin35) ||
		Item->sItemInfo.CODE == (sinDB1 | sin31) ||
		Item->sItemInfo.CODE == (sinDB1 | sin32) ||
		Item->sItemInfo.CODE == (sinSP1 | sin15) ||
		Item->sItemInfo.CODE == (sinSP1 | sin27) ||
		Item->sItemInfo.CODE == (sinSP1 | sin28) ||
		Item->sItemInfo.CODE == (sinSP1 | sin29) ||
		Item->sItemInfo.CODE == (sinSP1 | sin30) ||
		Item->sItemInfo.CODE == (sinSP1 | sin31) ||
		Item->sItemInfo.CODE == (sinSP1 | sin32) ||
		Item->sItemInfo.CODE == (sinSP1 | sin33) ||
		Item->sItemInfo.CODE == (sinSP1 | sin35) ||
		Item->sItemInfo.CODE == (sinOR2 | sin33) ||
		Item->sItemInfo.CODE == (sinOR2 | sin31) ||
		Item->sItemInfo.CODE == (sinOR2 | sin32) ||
		Item->sItemInfo.CODE == (sinOA1 | sin51) ||
		Item->sItemInfo.CODE == (sinOA1 | sin52) ||
		Item->sItemInfo.CODE == (sinDS1 | sin31) ||
		Item->sItemInfo.CODE == (sinOA1 | sin36) ||
		Item->sItemInfo.CODE == (sinSP1 | sin36) ||
		Item->sItemInfo.CODE == (sinOA1 | sin37) ||
		Item->sItemInfo.CODE == (sinOA2 | sin33) ||
		Item->sItemInfo.CODE == (sinSP1 | sin34) ||
		Item->sItemInfo.CODE == (sinSP1 | sin37) ||
		Item->sItemInfo.CODE == (sinSP1 | sin38) ||
		Item->sItemInfo.CODE == (sinBI1 | sin84) ||
		Item->sItemInfo.CODE == (sinOA2 | sin34) ||
		Item->sItemInfo.CODE == (sinSP1 | sin39) ||
		Item->sItemInfo.CODE == (sinDA1 | sin54) ||
		Item->sItemInfo.CODE == (sinDA2 | sin54) ||
		Item->sItemInfo.CODE == (sinDA1 | sin55) ||
		Item->sItemInfo.CODE == (sinDA2 | sin55) ||
		Item->sItemInfo.CODE == (sinOR2 | sin36) ||
		Item->sItemInfo.CODE == (sinOR2 | sin37) ||
		Item->sItemInfo.CODE == (sinOR2 | sin38) ||
		Item->sItemInfo.CODE == (sinOR2 | sin39) ||
		Item->sItemInfo.CODE == (sinOR2 | sin40) ||
		Item->sItemInfo.CODE == (sinOA1 | sin39) ||
		Item->sItemInfo.CODE == (sinOA1 | sin41) ||
		Item->sItemInfo.CODE == (sinOA1 | sin38) ||
		Item->sItemInfo.CODE == (sinOR2 | sin34) ||
		Item->sItemInfo.CODE == (sinOR2 | sin35)
		)
	{
		return false;
	}

	int kk = 0;
	if ((Item->sItemInfo.CODE & sinITEM_MASK2) == sinOS1)
		if ((Item->sItemInfo.CODE & sinITEM_MASK3) >= sin21 && (Item->sItemInfo.CODE & sinITEM_MASK3) <= sin34)
			return false;

	for (kk = 0; kk < NotSet_Item_CODECnt; kk++)
		if (NotSet_Item_CODE[kk] == Item->sItemInfo.CODE)
			return false;

	for (kk = 0; kk < NotSet_Item_MASKCnt; kk++)
		if ((Item->sItemInfo.CODE & sinITEM_MASK2) == NotSet_Item_MASK[kk])
			return false;

	for (kk = 0; kk < NotSet_Item_KINDCnt; kk++)
		if (NotSet_Item_KIND[kk] == Item->sItemInfo.ItemKindCode)
			return false;

	return true;
}

bool ModifyItem::IsStoneOkay(sITEM* Item)
{
	if ((Item->CODE & sinITEM_MASK2) != sinSA1)
		return false;

	return true;
}

bool ModifyItem::IsAtRange(sITEM* Item)
{
	int Code = Item->CODE & sinITEM_MASK2;

	if (m_Flag == 0)
	{
		return true;
	}
	else if (m_Flag == 1)
	{
		for (int i = 0; i < m_Upgrades.size(); i++)
		{
			for (int c = 0; c < m_Upgrades[i].size(); c++)
			{
				if (m_Upgrades[i][c] == Item->CODE)
				{
					return true;
				}
			}
		}
	}

	return false;
}

extern int SetAgingItem(sITEMINFO* pItem, int AgingNum);
extern int spJobCode;

bool ModifyItem::GetResultFromItem(sITEM* Item, sITEMINFO* Buffer, byte Operation, int Type, int Spec)
{
	extern sDEF_ITEMINFO* DefaultItems;
	extern int DefaultItemCount;

	switch (Operation)
	{
	case 0:
		if (Item->CODE != (sinSA1 | sin01))
			return false;
		break;
	case 1:
		if (Item->CODE != (sinSA1 | sin02))
			return false;
		break;
	}

	if (Buffer->bUpgraded)
		return false;

	if (Operation == 0)
	{
		for (int i = 0; i < DefaultItemCount; i++)
		{
			if (DefaultItems[i].Item.CODE == Buffer->CODE)
			{
				CreatePerfItem(Buffer, &DefaultItems[i], Spec, 0);
				return true;
			}
		}
	}
	else if (Operation == 1)
	{
		int UpgradeItem = GetUpgradeItem(Buffer->CODE);
		for (int i = 0; i < DefaultItemCount; i++)
		{
			if (DefaultItems[i].Item.CODE == UpgradeItem)
			{
				int aging = Buffer->ItemAgingNum[0];
				spJobCode = Spec;
				CreatePerfItem(Buffer, &DefaultItems[i], Spec, 0);
				spJobCode = 0;
				if (aging)
					SetAgingItem(Buffer, aging);
				Buffer->bUpgraded = TRUE;
				return true;
			}
		}
	}

	return false;
}
