#pragma once

#include "UILinker_.h"

#define BattleEventWindow (CBattleEventsWindow::GetInstance())

enum OBJID1
{
    OBJID_None1,
    OBJID_ONBox1,
    OBJID_OFFBox1,
    OBJID_Main1,
    OBJID_Close1,
    OBJID_Accept1,
};

class CBattleEventsWindow
{
public:
    CBattleEventsWindow();
    ~CBattleEventsWindow();

    static CBattleEventsWindow* GetInstance();

    void Init();
    void Draw();
    bool OnMouseClick(bool flag);
    void OnMouseMove();
    void OnMouseScroll(int zDelta);
    void Resize();
    void Open();
    void Close();
    void Accept();

    bool isOpen() { return ((m_pWindow && m_pWindow->isVisible()) ? true : false); }

private:
    UIWindow_* m_pWindow;

    void BuildMainWindow();
};

