#include "cSorteio.h"
#include "TitleBox/TitleBox.h"

char KeysMsg[256] = { 0 };
#define MaxSorteioitens 30

cSorteio::~cSorteio()
{
    if (pWindow1)
        delete pWindow1;
}

void cSorteio::Init()
{
    ClearLoadedImages();
    if (pWindow1)
    {
        delete pWindow1;
        pWindow1 = 0;
    }

    BuildImages();
}

void cSorteio::Draw()
{
    if (!pWindow1 || !pWindow1->isVisible())
        return;

    if (pWindow1->isVisible())
    {
        sprintf_s(KeysMsg, " Fichas: %d", Keys);
        auto SetKeys = pWindow1->GetElement<UIText_>(_Keys);
        SetKeys->setText(KeysMsg);
    }

    BaseX = (WinSizeX - 404) / 2;
    BaseY = (WinSizeY - 414) / 2;

    pWindow1->Render(BaseX, BaseY, WinSizeX, WinSizeY, 0, 0);
}

void cSorteio::RecvKeysFromServer(smTRANS_COMMAND* lpTransCommand)
{
    Keys = lpTransCommand->WParam;
}

void cSorteio::BuildImages()
{
   
    char Itens[256] = { 0 };
    int cnt = 1;

    pWindow1 = new UIWindow_(WindowMain, "game\\images\\SorteioItens\\window.png", 0, 0);

    pWindow1->AddElement(new UIButton_(Buttons, "game\\images\\SorteioItens\\Trocar.png", "game\\images\\SorteioItens\\Trocar_.png", 154, 300, true, false, std::bind(&cSorteio::ConfirmSorteio, this)));
    pWindow1->AddElement(new UIButton_(CLOSE, "game\\images\\SorteioItens\\btnclose.png", "game\\images\\SorteioItens\\btnclose_.png", 370, 6, true, false, std::bind(&cSorteio::Close, this)));

    for (int i = 1; i <= MaxSorteioitens; i++)
    {
        int b = i;
        if (cnt > 10) cnt = 1; cnt++;
        sprintf_s(Itens, "game\\images\\SorteioItens\\Itens\\item%d.bmp", i);

        if (i <= 10)
        {
            auto pImage = new UIImage_(ImageItens, Itens, 25 + 26 * cnt, 175);
            pWindow1->AddElement(pImage);
        }
        if (i > 10 && i <= 20)
        {
            auto pImage = new UIImage_(ImageItens, Itens, 25 + 26 * cnt, 200);
            pWindow1->AddElement(pImage);
        }
        if (i > 20 && i <= 30)
        {
            auto pImage = new UIImage_(ImageItens, Itens, 25 + 26 * cnt, 225);
            pWindow1->AddElement(pImage);
        }
        /*
        if (i > 30)
        {
        auto pImage = new UIImageOld(ImageItens, Itens, 25 + 26 * cnt, 225);
        pWindow1->AddElement(pImage);
        }*/
    }

    /*pWindow1->AddElement(new UITextOld(Text, "Roleta de Itens", 120, 200));
    pWindow1->AddElement(new UITextOld(Text, "Troque uma Ficha Por um Item da nossa Lista", 50, 250, true));
    pWindow1->AddElement(new UITextOld(Text, "Ao Participar o Sistema Sorteará um Item", 50, 270, true));
    pWindow1->AddElement(new UITextOld(Text, "Desejo a Você uma Boa Sorte!", 50, 290, true));*/

    sprintf_s(KeysMsg, "Tentativas: %d", Keys);
    pWindow1->AddElement(new UIText_(_Keys, KeysMsg, 40, 305, true));

    pWindow1->hide();
}

bool cSorteio::OnMouseClick(bool flag)
{
    if (!pWindow1 || !pWindow1->isVisible())
        return false;

    bool bRet = false;

    if (pWindow1->OnMouseClick(flag ? Down : Up, BaseX, BaseY, WinSizeX, WinSizeY, 0, 0))
        bRet = true;

    return bRet;
}

void cSorteio::ConfirmSorteio()
{
    sITEMINFO* lpItemInfo = 0;

  /* if (Keys <= 1)
    {
        TitleBox::GetInstance()->SetText("Fichas Insuficientes", 3);
        //AddChatBuff("Fichas Insuficientes");
        return;
    }

    lpItemInfo = FindItemFromCode(sinSP1 | sin64);

    if (lpItemInfo)
    {
        SendUseItemCodeToServer(lpItemInfo);
        cInvenTory.DeleteInvenItemToServer(lpItemInfo->CODE, lpItemInfo->ItemHeader.Head, lpItemInfo->ItemHeader.dwChkSum);
    }*/

    smTRANS_COMMAND sPacket;
    sPacket.size = sizeof(smTRANS_COMMAND);
    sPacket.code = OPCODE_SEND_SORTEIO_ITENS;
    sPacket.WParam = 1;
    smWsockServer->Send((char*)&sPacket, sPacket.size);

    pWindow1->hide();
}