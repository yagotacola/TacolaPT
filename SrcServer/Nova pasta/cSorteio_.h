#pragma once

#include "smPacket.h"

class cSorteio_
{
public:
    static cSorteio_* getInstance() { static cSorteio_ instance; return &instance; };

    void SendSorteio(rsPLAYINFO* lpPlayInfo);
    void OpenNpcSorteio(rsPLAYINFO* lpPlayInfo);
    void RecvGetItemKeys(rsPLAYINFO* lpPlayInfo);

};

#define Sorteio_ cSorteio_::getInstance()
