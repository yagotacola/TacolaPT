#include "cDistribuidorWindow.h"
#include "ConfirmationBox.h"


void cDistribuidorWindow::Init()
{
	BuildWindow1();
}

void cDistribuidorWindow::Render()
{
	if (!pWindow1)
		return;

	pWindow1->Render(0, 0, WinSizeX, WinSizeY, 0, 0);
}

void cDistribuidorWindow::Resize()
{
	if (!pWindow1)
		return;

	pWindow1->setX((WinSizeX - pWindow1->getWidth()) / 2);
	pWindow1->setY((WinSizeY - pWindow1->getHeight()) / 2);
}

bool cDistribuidorWindow::OnMouseClick(bool down)
{
	if (!pWindow1 || !pWindow1->isVisible())
		return false;

	if (down && sinMessageBoxShowFlag)
		return false;

	return pWindow1->OnMouseClick(down ? Down : Up, 0, 0, WinSizeX, WinSizeY, 0, 0);
}

bool cDistribuidorWindow::OnMouseScroll(int zDelta)
{
	if (!pWindow1 || !pWindow1->isVisible())
		return false;
	return pWindow1->OnMouseScroll(zDelta, 0, 0, WinSizeX, WinSizeY, 0, 0);
}

void cDistribuidorWindow::OnMouseMove()
{
	if (!pWindow1 || !pWindow1->isVisible())
		return;

	pWindow1->OnMouseMove(0, 0, WinSizeX, WinSizeY, 0, 0);
}

map<int, int> mCounts;
void cDistribuidorWindow::HandlePacket(PacketOpenDistribuidor* psPacket)
{
	if (psPacket->bFirst)
	{
		mCounts.clear();
		ClearItems();
	}

	auto pList = pWindow1->GetElement<UIListBox_>(DIS_TabList);
	if (pList)
	{
		for (int i = 0; i < psPacket->Count; i++)
		{
			auto pListItem = pList->GetListItem<UIListItem_>(psPacket->Items[i].Section);
			if (pListItem)
			{
				auto pListWindow = pListItem->GetElement<UIWindow_>(DIS_WINDOWN);
				if (pListWindow)
				{
					int count = mCounts[psPacket->Items[i].Section];

					DistribuidorItem* pItem = new DistribuidorItem;
					pItem->Section = psPacket->Items[i].Section;
					pItem->ID = psPacket->Items[i].ID;//0x100 + count;
					pItem->AmountItens = psPacket->Items[i].AmountItens;
					pItem->ExpireItem = psPacket->Items[i].ExpireItem;

					for (int cnt = 0; cnt < MAX_ITEM; cnt++)
					{
						if (sItem[cnt].CODE == psPacket->Items[i].ItemInfo.CODE)
						{
							memcpy(&pItem->Item, &sItem[cnt], sizeof(sITEM));
							memcpy(&pItem->Item.sItemInfo, &psPacket->Items[i].ItemInfo, sizeof(sITEMINFO));
							break;
						}
					}



					int w = (pItem->Item.w * 21) / 100;
					int h = (pItem->Item.h * 21) / 100;


					auto pBgName = new UIImage_(pItem->ID, "game\\images\\Distribuidor\\bgnameitem.png", 60 + (160 * (count % 1)), 0 + (84 * (count / 1)));

					auto pTitle = new UIText_(pItem->ID, pItem->Item.sItemInfo.ItemName, 80 + (160 * (count % 1)), 20 + (84 * (count / 1)));
					auto pAmountItens = new UIText_(pItem->ID, (char*)FormatString("Quantidade: %d", pItem->AmountItens), 80 + (160 * (count % 1)), 40 + (84 * (count / 1)));
					auto pExpireItem = new UIText_(pItem->ID, (char*)FormatString("Expira: %02d/%02d/%02d ás %02d:%02d", pItem->ExpireItem.wDay, pItem->ExpireItem.wMonth, pItem->ExpireItem.wYear, pItem->ExpireItem.wHour, pItem->ExpireItem.wMinute), 80 + (160 * (count % 1)), 60 + (84 * (count / 1)));

					auto pBgItem = new UIImage_(pItem->ID, "game\\images\\Distribuidor\\bgitem.png", 2 + (160 * (count % 1)), 15 + (84 * (count / 1)));
					auto pImage = new UIImage_(pItem->ID, (char*)FormatString("image\\Sinimage\\Items\\%s\\it%s.bmp", pItem->Item.ItemFilePath, pItem->Item.DorpItem), 40 + (160 * (count % 1)), 5 + (84 * (count / 1)), pItem->Item.w - w, pItem->Item.h - h, std::bind(&cDistribuidorWindow::OnHoverItemImage, this, pItem));
					auto pButton = new UIButton_(pItem->ID, "game\\images\\Distribuidor\\xxx.png", "game\\images\\Distribuidor\\xxx.png", 258 + (160 * (count % 1)), 57 + (84 * (count / 1)), true, false, std::bind(&cDistribuidorWindow::OnButtonPrevGetClick, this, pItem));
					auto pButtonDelete = new UIButton_(pItem->ID, "game\\images\\Distribuidor\\yyy.png", "game\\images\\Distribuidor\\yyy.png", 305 + (160 * (count % 1)), 57 + (84 * (count / 1)), true, false, std::bind(&cDistribuidorWindow::OnButtonPrevDeleteClick, this, pItem));


					pImage->setX(pImage->getX() + ((0 - pImage->getWidth()) / 2));
					pImage->setY(pImage->getY() + ((96 - pImage->getHeight()) / 2));

					pListWindow->AddElement(pBgItem);
					pListWindow->AddElement(pBgName);
					pListWindow->AddElement(pTitle);
					pListWindow->AddElement(pImage);
					pListWindow->AddElement(pButton);
					pListWindow->AddElement(pButtonDelete);
					pListWindow->AddElement(pAmountItens);
					pListWindow->AddElement(pExpireItem);

					mCounts[psPacket->Items[i].Section]++;
					vItems.push_back(pItem);
				}
			}
		}
	}

	pWindow1->show();
}

void cDistribuidorWindow::BuildWindow1()
{
	pWindow1 = new UIWindow_(DIS_WINDOWN, "game\\images\\Distribuidor\\background.png", 0, 0);
	pWindow1->setX((WinSizeX - pWindow1->getWidth()) / 2);
	pWindow1->setY((WinSizeY - pWindow1->getHeight()) / 2);

	pWindow1->AddElement(new UIButton_(DIS_CLOSE, "game\\images\\Distribuidor\\fechar.png", "game\\images\\Distribuidor\\fechar_.png", 356, 6, true, false, std::bind(&cDistribuidorWindow::Close, this)));

	auto pList = new UIListBox_(DIS_TabList, 0, 0, pWindow1->getHeight(), 53);
	if (pList)
	{
		auto pPremiumTab = new UIListItem_(DIS_LIST_ITEM, "game\\images\\Distribuidor\\title.png", "game\\images\\Distribuidor\\title.png", 0, 0);
		auto pPremiumWindow = new UIWindow_(DIS_WINDOWN, 12, 85, 365, 286); // Espaço dos itens na background

		pPremiumWindow->AddElement(new UIImage_(DIS_TITLE_, "game\\images\\Distribuidor\\title-.png", 0, 0));

		auto pScroll = new UIVerticalScroll_(DIS_SCROLL, 350, 5, 0, 262, 0, 0);
		pScroll->hide();
		pPremiumWindow->SetScrollBar(pScroll);

		pPremiumTab->AddElement(pPremiumWindow);
		pList->AddListItem(pPremiumTab);

		pList->selectItem(DIS_LIST_ITEM);
	}


	pWindow1->AddElement(pList);

	pWindow1->hide();
}

void cDistribuidorWindow::Close()
{
	pWindow1->hide();
}

void cDistribuidorWindow::ClearItems()
{
	auto pList = pWindow1->GetElement<UIListBox_>(DIS_TabList);
	if (pList)
	{
		for (auto Item : vItems)
		{
			auto pListItem = pList->GetListItem<UIListItem_>(Item->Section);
			if (pListItem)
			{
				auto pListWindow = pListItem->GetElement<UIWindow_>(DIS_WINDOWN);
				if (pListWindow)
				{
					pListWindow->RemoveElementByID(Item->ID);
				}
			}

			delete Item;
		}
	}

	vItems.clear();
}


void cDistribuidorWindow::OnButtonGetClick(DistribuidorItem* pDistribuidorItem)
{

	if (!cInvenTory.CheckSetEmptyArea(&pDistribuidorItem->Item))
	{
		cMessageBox.ShowMessageEvent("Você não tem Espaço no Inventario!");
		return;
	}

	if (!cInvenTory.CheckSetOk(&pDistribuidorItem->Item, 1))
	{
		cMessageBox.ShowMessageEvent("Você ja ultrapassou o limite do peso!");
		return;
	}

	PacketGetItem sPacket;
	sPacket.code = OPCODE_DISTRIBUIDOR_GETITEM;
	sPacket.size = sizeof(sPacket);
	sPacket.ID = pDistribuidorItem->ID;
	sPacket.Section = pDistribuidorItem->Section;
	lstrcpy(sPacket.ItemCode, pDistribuidorItem->Item.LastCategory);
	smWsockServer->Send((char*)&sPacket, sPacket.size, TRUE);

	Close();

}

void cDistribuidorWindow::OnButtonPrevGetClick(DistribuidorItem* pDistribuidorItem)
{
	pLastItem = pDistribuidorItem;

	_ConfirmationBox.SetTitle("Distribuidor");
	_ConfirmationBox.SetText("Deseja Resgatar", "Este Item?");
	_ConfirmationBox.SetCallback([this](bool isChecked)
		{
			if (isChecked)
			{
				ConfirmGetItem();
			}
		});
	_ConfirmationBox.Start();


}



void cDistribuidorWindow::OnButtonDeleteClick(DistribuidorItem* pDistribuidorItem)
{
	PacketGetItem sPacket;
	sPacket.code = OPCODE_DISTRIBUIDOR_DELETE_ITEM;
	sPacket.size = sizeof(sPacket);
	sPacket.ID = pDistribuidorItem->ID;
	sPacket.Section = pDistribuidorItem->Section;
	lstrcpy(sPacket.ItemCode, pDistribuidorItem->Item.LastCategory);
	smWsockServer->Send((char*)&sPacket, sPacket.size, TRUE);

	Close();
}

void cDistribuidorWindow::OnButtonPrevDeleteClick(DistribuidorItem* pDistribuidorItem)
{
	pLastItem = pDistribuidorItem;
	_ConfirmationBox.SetTitle("Distribuidor");
	_ConfirmationBox.SetText("Deseja Deletar", "Este Item?");
	_ConfirmationBox.SetCallback([this](bool isChecked)
		{
			if (isChecked)
			{
				ConfirmDeleteItem();
			}
		});
	_ConfirmationBox.Start();


}

void cDistribuidorWindow::OnHoverItemImage(DistribuidorItem* pDistribuidorItem)
{
	pDistribuidorItem->Item.x = pCursorPos.x;
	pDistribuidorItem->Item.y = pCursorPos.y;

	cItem.ShowItemInfo(&pDistribuidorItem->Item, 0);
	sinShowItemInfoFlag = 1;
}

