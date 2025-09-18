#include "sinbaram\\sinLinkHeader.h"
#include "CHellsGateHandler.h"
#include "field.h"
#include "FontImage.h"
#include "BellatraFontEffect.h"

extern int WarpFieldNearPos(int FieldNum, int x, int z, int* mx, int* mz);

CHellsGate::CHellsGate()
{
    m_bEventFlag = false;
    m_nStage = 0;
    m_dwBossSerial = 0;
    m_dwEventTime = 0;
    m_dwDelayTime = 0;
}

CHellsGate::~CHellsGate()
{
}

void CHellsGate::Init()
{
    m_LifeBar[0] = CreateTextureMaterial("Game\\BattleEvents\\life.png", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);
    m_LifeBar[1] = CreateTextureMaterial("Game\\BattleEvents\\life_.png", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);
    Images[5] = CreateTextureMaterial("game\\images\\UI\\target\\life.png", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);
    Images[6] = CreateTextureMaterial("game\\images\\UI\\target\\life_.png", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);
}



void CHellsGate::Main()
{
    if (m_dwDelayTime)
    {
        if (m_dwDelayTime <= dwPlayTime)
            m_dwDelayTime = 0;
    }

    if (m_dwDelayTime)
    {
        if (m_dwDelayTime <= dwPlayTime)
            m_dwDelayTime = 0;
    }
}

void CHellsGate::DrawHP(smCHAR* pcUnitData)
{
    char		szBuff[255];
    int x = (WinSizeX - 474) / 2;
    int y = 25;

         dsDrawTexImage(Images[5], x, y, 474, 58, 255);//407
         dsDrawTexImage(Images[6], x + 43, y + 22, (386 * (float)((float)pcUnitData->smCharInfo.Life[0] / (float)pcUnitData->smCharInfo.Life[1])), 16, 255);
       

         float fPercent = (float)((float)pcUnitData->smCharInfo.Life[0] / (float)pcUnitData->smCharInfo.Life[1]);

         sprintf(szBuff, "%.2f%%", fPercent * 100);
         SetTextColor(0, RGB(255, 255, 255));
         dsTextLineOut(x + 50, y + 21, pcUnitData->smCharInfo.szName, lstrlen(pcUnitData->smCharInfo.szName));
         dsTextLineOut(x + 367, y + 21, szBuff, lstrlen(szBuff));
        
    
}

void CHellsGate::Draw()
{
    smCHAR* lpChar = 0;
    int			nMin = 0;
    int			nSec = 0;
    char		szBuff[255];

    if (lpCurPlayer && lpCurPlayer->OnStageField >= 0 && lpCurPlayer->OnStageField < 2 &&
        StageField[lpCurPlayer->OnStageField]->FieldCode == 23)
    {
        if (m_bEventFlag)
        {
            if (m_dwDelayTime)
            {
                nMin = (m_dwDelayTime - dwPlayTime) / 1000;
                nSec = nMin % 60;
                nMin = nMin / 60;
                sprintf_s(szBuff, "Iniciando em: %02d:%02d", nMin, nSec);
                DrawFontImage(szBuff, 20, 150, D3DCOLOR_RGBA(255, 255, 255, 255), 0.5f);
            }
            else if (m_dwEventTime)
            {
                nMin = (m_dwEventTime - dwPlayTime) / 1000;
                nSec = nMin % 60;
                nMin = nMin / 60;
                sprintf_s(szBuff, "Tempo Restante: %02d:%02d", nMin, nSec);
                DrawFontImage(szBuff, 20, 150, D3DCOLOR_RGBA(255, 255, 255, 255), 0.5f);
            }

            if (m_szBossName[0])
            {
                sprintf(szBuff, "Proximo Boss: %s", m_szBossName);
                DrawFontImage(szBuff, 20, 180, D3DCOLOR_RGBA(255, 255, 255, 255), 0.5f);
            }

            for (int cnt = 0; cnt < OTHER_PLAYER_MAX; cnt++)
            {
                if (chrOtherPlayer[cnt].Flag && chrOtherPlayer[cnt].smCharInfo.szName[0] && chrOtherPlayer[cnt].dwObjectSerial == m_dwBossSerial)
                {
                    lpChar = &chrOtherPlayer[cnt];
                    break;
                }
            }

            if (!lpChar)
                return;

            int x = (WinSizeX - 474) / 2;
            int y = 100;

            if (lpChar->smCharInfo.Life[0] > 0)
            {
                dsDrawTexImage(m_LifeBar[0], x, y, 474, 58, 255);//407
                dsDrawTexImage(m_LifeBar[1], x + 43, y + 22, (386 * (float)((float)lpChar->smCharInfo.Life[0] / (float)lpChar->smCharInfo.Life[1])), 16, 255);

                float fPercent = (float)((float)lpChar->smCharInfo.Life[0] / (float)lpChar->smCharInfo.Life[1]);

                sprintf(szBuff, "%.2f%%", fPercent * 100);
                SetTextColor(0, RGB(255, 255, 255));
                dsTextLineOut(x + 50, y + 21, lpChar->smCharInfo.szName, lstrlen(lpChar->smCharInfo.szName));
                dsTextLineOut(x + 367, y + 21, szBuff, lstrlen(szBuff));
            }
        }
        else
        {
            if (m_dwDelayTime)
            {
                if (m_dwDelayTime > dwPlayTime)
                {
                    nMin = (m_dwDelayTime - dwPlayTime) / 1000;
                    nSec = nMin % 60;
                    nMin = nMin / 60;
                    sprintf_s(szBuff, "Teleportando em: %02d:%02d", nMin, nSec);
                    DrawFontImage(szBuff, WinSizeX - 250, 200, D3DCOLOR_RGBA(200, 40, 40, 255), 0.5f);
                }

            }
        }
    }
}

void CHellsGate::RecvNextStage(smTRANS_HGINFO* lpTransHgInfo)
{
    m_bEventFlag = lpTransHgInfo->Flag ? true : false;
    m_nStage = lpTransHgInfo->Stage;
    m_dwDelayTime = lpTransHgInfo->dwDelay ? (lpTransHgInfo->dwDelay + dwPlayTime) : 0;
    m_dwEventTime = lpTransHgInfo->dwTime ? (lpTransHgInfo->dwTime + dwPlayTime) : 0;
    m_dwBossSerial = lpTransHgInfo->dwBossSerial;

    sprintf_s(m_szBossName, lpTransHgInfo->szBossName);
}
