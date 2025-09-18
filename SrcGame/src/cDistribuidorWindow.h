#pragma once

#include "UILinker_.h"

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

enum DistribuidorID
{
	DIS_WINDOWN = 0,
	DIS_CLOSE,
	DIS_TITLE_,
	DIS_None,
	DIS_TabList,
	DIS_LIST_ITEM = 5,
	DIS_SCROLL,
};

struct DistribuidorItem
{
	int ID;
	int Section;
	sITEM Item;
	int AmountItens;
	SYSTEMTIME ExpireItem;
};

class cDistribuidorWindow
{
public:
	static cDistribuidorWindow* getInstance() { static cDistribuidorWindow instance; return &instance; };
	void Init();
	void Render();
	void Resize();

	bool isOpen() { if (pWindow1) return pWindow1->isVisible(); else return false; }

	bool OnMouseClick(bool down);
	bool OnMouseScroll(int zDelta);
	void OnMouseMove();

	void HandlePacket(PacketOpenDistribuidor* psPacket);

	void ConfirmGetItem() { OnButtonGetClick(pLastItem); }
	void ConfirmDeleteItem() { OnButtonDeleteClick(pLastItem); }
	void Open() { pWindow1->show(); };

protected:
	void BuildWindow1();
	void Close();
	void ClearItems();

	void OnButtonGetClick(DistribuidorItem* pDistribuidorItem);
	void OnButtonPrevGetClick(DistribuidorItem* pDistribuidorItem);
	void OnHoverItemImage(DistribuidorItem* pDistribuidorItem);
	void OnButtonDeleteClick(DistribuidorItem* pDistribuidorItem);
	void OnButtonPrevDeleteClick(DistribuidorItem* pDistribuidorItem);
private:
	UIWindow_* pWindow1;
	vector<DistribuidorItem*> vItems;
	DistribuidorItem* pLastItem;
};

#define DISTRIBUIDORWINDOW cDistribuidorWindow::getInstance()