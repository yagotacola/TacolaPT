#include "CBattleEventsWindow.h"

CBattleEventsWindow Instance;
CBattleEventsWindow* CBattleEventsWindow::GetInstance()
{
    return &Instance;
}

CBattleEventsWindow::CBattleEventsWindow()
{
}

CBattleEventsWindow::~CBattleEventsWindow()
{
    if (m_pWindow)
        delete m_pWindow;
}

void CBattleEventsWindow::Init()
{
    if (m_pWindow)
    {
        delete m_pWindow;
        m_pWindow = 0;
    }

    BuildMainWindow();
}

void CBattleEventsWindow::Draw()
{
    if (!m_pWindow || !m_pWindow->isVisible())
        return;

    m_pWindow->Render(0, 0, WinSizeX, WinSizeY, 0, 0);
}

bool CBattleEventsWindow::OnMouseClick(bool flag)
{
    if (!m_pWindow || !m_pWindow->isVisible())
        return false;

    if (m_pWindow->OnMouseClick(flag ? Down : Up, 0, 0, WinSizeX, WinSizeY, 0, 0))
        return true;

    return false;
}

void CBattleEventsWindow::OnMouseMove()
{
    if (!m_pWindow || !m_pWindow->isVisible())
        return;

    m_pWindow->OnMouseMove(0, 0, WinSizeX, WinSizeY, 0, 0);
}

void CBattleEventsWindow::OnMouseScroll(int zDelta)
{
    if (!m_pWindow || !m_pWindow->isVisible())
        return;

    m_pWindow->OnMouseScroll(zDelta, 0, 0, WinSizeX, WinSizeY, 0, 0);
}

void CBattleEventsWindow::Open()
{
    m_pWindow->show();
}

void CBattleEventsWindow::Close()
{
    m_pWindow->hide();
}

void CBattleEventsWindow::Accept()
{
    smTRANS_COMMAND smTransCommand;

    smTransCommand.size = sizeof(smTRANS_COMMAND);
    smTransCommand.code = smTRANSCODE_HG_ENTER;

    if (smWsockServer)
        smWsockServer->Send((char*)&smTransCommand, smTransCommand.size, TRUE);

    m_pWindow->hide();
}

void CBattleEventsWindow::BuildMainWindow()
{
    char szDir[256];

    m_pWindow = new UIWindow_(OBJID_Main1, "Game\\BattleEvents\\Window\\Window.png", 0, 0, false);
    m_pWindow->hide();
    m_pWindow->setX((WinSizeX - m_pWindow->getWidth()) / 2);
    m_pWindow->setY((WinSizeY - m_pWindow->getHeight()) / 2);

    m_pWindow->AddElement(new UIButton_(OBJID_Close1, "Game\\BattleEvents\\Window\\btnclose.png", "Game\\BattleEvents\\Window\\btnclose_.png", 355, 7, true, false, std::bind(&CBattleEventsWindow::Close, this)));
    m_pWindow->AddElement(new UIButton_(OBJID_Accept1, "Game\\BattleEvents\\Window\\Accept.png", "Game\\BattleEvents\\Window\\Accept_.png", (m_pWindow->getWidth() - 130) / 2, 300, true, false, std::bind(&CBattleEventsWindow::Accept, this)));

    auto pTitle = new UIImage_(0, "Game\\UI\\BattleEvents\\Window\\title.png", 0, 0);
    pTitle->setX((m_pWindow->getWidth() - pTitle->getWidth()) / 2);
    pTitle->setY(14);
    m_pWindow->AddElement(pTitle);

    auto pReward = new UIImage_(0, "Game\\BattleEvents\\Window\\chance.png", 0, 0);
    pReward->setX((m_pWindow->getWidth() - pReward->getWidth()) / 2);
    pReward->setY(120);
    m_pWindow->AddElement(pReward);
    //Itens
    for (int i = 0; i < 10; i++)
    {
        sprintf_s(szDir, "Game\\BattleEvents\\Window\\Items\\item%d.png", i + 1);
        auto pItem = new UIImage_(0, szDir, 0, 0);
        pItem->setX(80 + ((i > 4) ? ((i - 5) * 50) : (i * 50)));
        pItem->setY(154 + ((i > 4) ? 46 : 0));
        m_pWindow->AddElement(pItem);
    }
}

void CBattleEventsWindow::Resize()
{
    if (m_pWindow && m_pWindow->isVisible())
    {
        m_pWindow->setX((WinSizeX - m_pWindow->getWidth()) / 2);
        m_pWindow->setY((WinSizeY - m_pWindow->getHeight()) / 2);
    }
}
