#pragma once

#include "UILinker_.h"

struct PacketRelicInfo
{
    int size, code;
    int bRelic[12];
};

class CRelicWindow
{
public:
    static CRelicWindow* getInstance();

    void Init();
    void Render();
    bool OnMouseClick(bool flag);
    void OnMouseMove();

    bool isOpen() { return pWindow1 && pWindow1->isVisible(); }
    void Open();
    void Close();
    void Resize();

    void HandlePacket(PacketRelicInfo* psPacket);

    bool GetRelic(int index) { return bRelic[index]; }

    bool RelicIsActivete(int Kind) { return bRelic[Kind] == TRUE; }

protected:
    void BuildWindow1();
    void Help();
    void UpdateRelicImages();
    void HoverRelic(int index);

public:
    UIWindow_* pWindow1;
    int bRelic[12] = {};
};

#define RELICWINDOW CRelicWindow::getInstance()
