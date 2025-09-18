#include "stdafx.h"
#include "CRelicWindow.h"

CRelicWindow cRelicWindow;

POINT RelicPoint[12] = {
    {67, 71},  {123, 71},  {178, 71},  {234, 71},
    {67, 171}, {123, 171}, {178, 171}, {234, 171},
    {67, 273}, {124, 269}, {182, 269}, {239, 269},
};

CRelicWindow* CRelicWindow::getInstance()
{
    return &cRelicWindow;
}

void CRelicWindow::Init()
{
    BuildWindow1();
}

void CRelicWindow::Render()
{
    if (!pWindow1)
        return;

    pWindow1->Render(0, 0, WinSizeX, WinSizeY, 0, 0);
}

bool CRelicWindow::OnMouseClick(bool flag)
{
    if (!pWindow1)
        return false;

    return pWindow1->OnMouseClick(flag ? Down : Up, 0, 0, WinSizeX, WinSizeY, 0, 0);
}

void CRelicWindow::OnMouseMove()
{
    if (!pWindow1)
        return;

    pWindow1->OnMouseMove(0, 0, WinSizeX, WinSizeY, 0, 0);
}

void CRelicWindow::Open()
{
    pWindow1->setX((WinSizeX - pWindow1->getWidth()) / 2);
    pWindow1->setY((WinSizeY - pWindow1->getHeight()) / 2);
    pWindow1->show();
}

void CRelicWindow::Close()
{
    if (!pWindow1)
        return;

    pWindow1->hide();
}

void CRelicWindow::Resize()
{
    if (!pWindow1)
        return;

    pWindow1->setX((WinSizeX - pWindow1->getWidth()) / 2);
    pWindow1->setY((WinSizeY - pWindow1->getHeight()) / 2);
}

void CRelicWindow::HandlePacket(PacketRelicInfo* psPacket)
{
    memcpy(bRelic, psPacket->bRelic, sizeof(int) * 12);
    UpdateRelicImages();
}

void CRelicWindow::BuildWindow1()
{
    pWindow1 = new UIWindow_(0, "game\\images\\Relic\\background.png", 0, 0);
    pWindow1->setX((WinSizeX - pWindow1->getWidth()) / 2);
    pWindow1->setY((WinSizeY - pWindow1->getHeight()) / 2);

    pWindow1->AddElement(new UIButton_(-1, "game\\images\\Relic\\close.png", "game\\images\\Relic\\close_.png", 295, 13, true, false, std::bind(&CRelicWindow::Close, this)));
   // pWindow1->AddElement(new UIButton(-1, "game\\images\\Relic\\help.png", "game\\images\\Relic\\help_.png", 282, 27, true, false, std::bind(&CRelicWindow::Help, this)));

    pWindow1->hide();
}

void CRelicWindow::Help()
{
}

void CRelicWindow::UpdateRelicImages()
{
    if (!pWindow1)
        return;

    for (int i = 0; i < 12; i++)
    {
        if (bRelic[i])
        {
            auto pImage = pWindow1->GetElement<UIImage_>(i + 1);
            if (!pImage)
            {
                pImage = new UIImage_(i + 1, (char*)FormatString("game\\images\\Relic\\%d.png", i + 1), RelicPoint[i].x, RelicPoint[i].y);
                pImage->setHoverFunc(std::bind(&CRelicWindow::HoverRelic, this, i));
                pWindow1->AddElement(pImage);
            }
        }
    }
}

char* RelicName[] = {
    "Foice do Babel",
    "Juba do Fúria",
    "Elmo do Valento",
    "Chifres do Kelvezu",
    "Máscara do Mokova",
    "Vestido do Shy",
    "Vestes do Tulla",
    "Espada do Draxos",
    "Aeronave do Greedy",
    "Tridente do Yagditha",
    "Asa do Midranda",
};

void CRelicWindow::HoverRelic(int index)
{
    sITEM Item = {};

    for (int cnt = 0; cnt < MAX_ITEM; cnt++)
    {
        if (sItem[cnt].CODE == (sinRR1 | (sin01 + (index << 8))))
        {
            memcpy(&Item, &sItem[cnt], sizeof(sITEM));
            lstrcpy(Item.sItemInfo.ItemName, RelicName[index]);
            Item.x = pCursorPos.x;
            Item.y = pCursorPos.y;
            break;
        }
    }

    sinShowItemInfoFlag = 1;
    GAMECOREHANDLE->pcItemInfoBox->PrepareShowItem(&Item, FALSE, FALSE, FALSE);

}
