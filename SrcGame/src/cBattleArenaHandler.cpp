#include "sinbaram/sinLinkHeader.h"
#include "cBattleArenaHandler.h"
#include "FontImage.h"
#include "field.h"

extern bool isMousePos(int x, int y, int w, int h);
extern int WarpField2(int Num);

cBATTLEARENA cBattleArena;

void cBATTLEARENA::Init()
{
	// aqui carrega as imagens do npc
	Mat[BACKGROUND] = CreateTextureMaterial("game\\battlearena1\\NPC\\background.tga", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);
	Mat[EXIT] = CreateTextureMaterial("game\\battlearena1\\NPC\\exit.tga", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);
	Mat[EXIT_] = CreateTextureMaterial("game\\battlearena1\\NPC\\exit_.tga", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);
	Mat[START] = CreateTextureMaterial("game\\battlearena1\\NPC\\start.tga", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);
	Mat[START_] = CreateTextureMaterial("game\\battlearena1\\NPC\\start_.tga", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);
	Mat[DEFAULT] = CreateTextureMaterial("game\\battlearena1\\NPC\\default.tga", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);
	Mat[BLUE] = CreateTextureMaterial("game\\battlearena1\\NPC\\blue_.tga", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);
	Mat[RED] = CreateTextureMaterial("game\\battlearena1\\NPC\\red_.tga", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);
	Mat[PLACAR] = CreateTextureMaterial("game\\battlearena1\\placar.tga", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);
	Mat[TIMEBG] = CreateTextureMaterial("game\\battlearena1\\timebg.tga", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);
	Mat[TABBG] = CreateTextureMaterial("game\\battlearena1\\TAB\\bg1.png", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);
	Mat[TABBLUE] = CreateTextureMaterial("game\\battlearena1\\TAB\\azul.png", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);
	Mat[TABRED] = CreateTextureMaterial("game\\battlearena1\\TAB\\vermelho.png", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);
}

void cBATTLEARENA::Main()
{
	if (bIsInsideArena && lpCurPlayer->OnStageField >= 0 && StageField[lpCurPlayer->OnStageField]->FieldCode != 49)
	{
		LeaveArena();
	}
}

void cBATTLEARENA::Draw()
{
	// aqui printa o npc na tela

	if (OpenFlag)
	{
		BaseX = (WinSizeX - 531) / 2;
		BaseY = (WinSizeY - 435) / 2;

		dsDrawTexImage(Mat[BACKGROUND], BaseX, BaseY, 429, 362, 255);

		for (auto obj : vObjects)
		{
			if (obj.ID == START)
			{
				if (eState == BATTLEARENASTATE_WaitingPlayers && isMousePos(BaseX + obj.x, BaseY + obj.y, obj.w, obj.h))
					dsDrawTexImage(obj.Mat_, BaseX + obj.x, BaseY + obj.y, obj.w, obj.h, 255);
				else
					dsDrawTexImage(obj.Mat, BaseX + obj.x, BaseY + obj.y, obj.w, obj.h, 255);
			}
			else
			{
				if (isMousePos(BaseX + obj.x, BaseY + obj.y, obj.w, obj.h) || obj.bSelected)
					dsDrawTexImage(obj.Mat_, BaseX + obj.x, BaseY + obj.y, obj.w, obj.h, 255);
				else
					dsDrawTexImage(obj.Mat, BaseX + obj.x, BaseY + obj.y, obj.w, obj.h, 255);
			}
		}

		char buff[255];

		if (eState == BATTLEARENASTATE_WaitingEvent)
		{
			int day = 0, hour = 0, min = 0, sec = 0;
			sec = (iTimeLeft - GetCurrentTime()) / 1000;
			min = sec / 60;
			hour = min / 60;
			day = hour / 24;

			wsprintf(buff, "%02d:%02d:%02d:%02d", day, hour % 24, min % 60, sec % 60);
		}
		else if (eState == BATTLEARENASTATE_WaitingPlayers)
		{
			wsprintf(buff, "Esperando jogadores...");
		}
		else if (eState == BATTLEARENASTATE_Running)
		{
			wsprintf(buff, "Evento em andamento...");
		}

		SetTextColor(0, RGB(255, 0, 0));
		dsTextLineOut(BaseX + 121, BaseY + 142, buff, lstrlen(buff));
	}
	else if (bIsInsideArena)
	{
		if (eState == BATTLEARENASTATE_Running)
		{
			BaseX = (WinSizeX - 715) / 2;
			BaseY = 0;
			/*dsDrawTexImage(Mat[PLACAR], BaseX, BaseY, 489, 97, 255);*/
			dsDrawTexImage(Mat[PLACAR], BaseX, BaseY, 701, 105, 255);

			char buff[255];
			wsprintf(buff, "%d", iRedPoints);
			DrawFontImage(buff, BaseX + 100, 25, D3DCOLOR_RGBA(255, 0, 0, 255), 0.8);
			wsprintf(buff, "%d", iBluePoints);
			DrawFontImage(buff, BaseX + 580, 25, D3DCOLOR_RGBA(0, 148, 255, 255), 0.8);
		}

		//dsDrawTexImage(Mat[TIMEBG], (WinSizeX - 70) / 2, 105, 70, 18, 255);

		char buff[255];
		int hour = 0, min = 0, sec = 0;
		sec = iTimeLeft;
		min = sec / 60;
		hour = min / 60;

		wsprintf(buff, "%02d:%02d:%02d", hour % 24, min % 60, sec % 60);
		SIZE sz = {};
		GetTextExtentPoint(0, buff, lstrlen(buff), &sz);
		SetTextColor(0, RGB(255, 255, 255));
		dsTextLineOut((WinSizeX - sz.cx) / 2, 28, buff, lstrlen(buff));

		if (VRKeyBuff[VK_TAB])
		{
			int iX = (WinSizeX - 589) / 2;
			int iY = (WinSizeY - 373) / 2;
			int startY = 37;
			int sizeY = 30;

			dsDrawTexImage(Mat[TABBG], iX, iY, 590, 374, 255);

			for (int i = 0; i < 10; i++)
			{
				if (vPlayers[i].dwObjectSerial)
				{
					char buff[15];
					wsprintf(buff, "%d", vPlayers[i].iKills);
					dsTextLineOut(iX + 100, iY + startY + (sizeY * i) + 12, vPlayers[i].szName, lstrlen(vPlayers[i].szName));
					dsTextLineOut(iX + 328, iY + startY + (sizeY * i) + 12, buff, lstrlen(buff));

					dsDrawTexImage(Mat[vPlayers[i].eTeam == EBattleTeam::BATTLETEAM_Red ? TABRED : TABBLUE], iX + 460, iY + startY + (sizeY * i) + 2, 28, 28, 255);
				}
			}
		}
	}
}

bool cBATTLEARENA::LButtonDown()
{
	// aqui gerencia os clicks no npc
	if (OpenFlag)
	{
		for (vector<sOBJECT>::iterator it = vObjects.begin(); it < vObjects.end(); it++)
		{
			auto obj = it._Ptr;
			if (isMousePos(BaseX + obj->x, BaseY + obj->y, obj->w, obj->h))
			{
				switch (obj->ID)
				{
				case EXIT:
					Close();
					break;
				case BLUE:
				case RED:
					SelectTeam(obj);
					break;
				case START:
					if (eState == BATTLEARENASTATE_WaitingPlayers)
					{
						SendJoinArena();
						Close();
					}
					break;
				}
			}
		}
	}

	return false;
}

void cBATTLEARENA::HandlePacket(BattleArenaOpenWindow* psPacket)
{
	// aqui recebe o pacote e abre o npc
	iTimeLeft = (psPacket->iTimeLeft * 1000) + GetCurrentTime();
	eState = psPacket->eEventState;

	Open();
}

void cBATTLEARENA::HandlePacket(BattleArenaJoin* psPacket)
{
	SelectedTeam = psPacket->Team;
	bIsInsideArena = true;

	int ix = 0, iz = 0, x = 0, z = 0;
	if (SelectedTeam == 1)
	{
		ix = -23408;
		iz = 20393;
	}
	else
	{
		ix = -24269;
		iz = 20403;
	}

	WarpFieldNearPos(49, ix * fONE, iz * fONE, &x, &z);

	lpCurPlayer->SetPosi(ix * fONE, 0, iz * fONE, 0, 0, 0);
	TraceCameraPosi.x = lpCurPlayer->pX;
	TraceCameraPosi.y = lpCurPlayer->pY;
	TraceCameraPosi.z = lpCurPlayer->pZ;
	TraceTargetPosi.x = lpCurPlayer->pX;
	TraceTargetPosi.y = lpCurPlayer->pY;
	TraceTargetPosi.z = lpCurPlayer->pZ;
}

void cBATTLEARENA::HandlePacket(BattleArenaSyncData* psPacket)
{
	eState = psPacket->eEventState;

	iTimeLeft = psPacket->iTimeLeft;
	iRedPoints = psPacket->iRedPoints;
	iBluePoints = psPacket->iBluePoints;
}

void cBATTLEARENA::HandlePacket(BattleArenaRanking* psPacket)
{
	memcpy(&vPlayers, &psPacket->sPlayers, sizeof(BattleArenaUser) * 10);
}

void cBATTLEARENA::LeaveArena()
{
	iBluePoints = 0;
	iRedPoints = 0;
	SelectedTeam = 0;
	bIsInsideArena = false;
	eState = BATTLEARENASTATE_WaitingEvent;
	OpenFlag = false;
	WarpField2(3);
}


void cBATTLEARENA::SendJoinArena()
{
	/*if (!SelectedTeam)
	{
		cMessageBox.ShowMessageEvent("Selecione um time.");
		return;
	}*/

	BattleArenaJoin psPacket;
	psPacket.size = sizeof(BattleArenaJoin);
	psPacket.code = smTRANSCODE_BA_JOIN;
	psPacket.Team = 0;
	smWsockServer->Send((char*)&psPacket, psPacket.size, TRUE);
}

void cBATTLEARENA::AddObject(int ID, int Mat, int Mat_, int x, int y, int w, int h, bool bSelected)
{
	sOBJECT obj;

	obj.ID = ID;
	obj.Mat = Mat;
	obj.Mat_ = Mat_ ? Mat_ : Mat;
	obj.x = x;
	obj.y = y;
	obj.w = w;
	obj.h = h;
	obj.bSelected = bSelected;

	vObjects.push_back(obj);
}

sOBJECT* cBATTLEARENA::FindObject(int ID)
{
	for (vector<sOBJECT>::iterator it = vObjects.begin(); it < vObjects.end(); it++)
	{
		sOBJECT* obj = it._Ptr;
		if (obj && obj->ID == ID)
			return obj;
	}

	return nullptr;
}

void cBATTLEARENA::Open()
{
	// aqui adiciona os objetos na tela
	AddObject(EXIT, Mat[EXIT], Mat[EXIT_], 385, 45, 20, 23);
	AddObject(START, Mat[START], Mat[START_], 128, 326, 175, 29);

	/*AddObject(RED, Mat[DEFAULT], Mat[RED], 100, 339, 52, 51, true);
	AddObject(BLUE, Mat[DEFAULT], Mat[BLUE], 170, 339, 52, 51, false);
	SelectTeam(RED);*/

	OpenFlag = true;
}

void cBATTLEARENA::Close()
{
	OpenFlag = false;
	vObjects.clear();
}

void cBATTLEARENA::SelectTeam(sOBJECT* pObj)
{
	/*if (pObj->ID == RED)
	{
		SelectedTeam = 1;
		sOBJECT* pBlue = FindObject(BLUE);
		if (pBlue)
			pBlue->bSelected = false;
	}
	else
	{
		SelectedTeam = 2;
		sOBJECT* pRed = FindObject(RED);
		if (pRed)
			pRed->bSelected = false;
	}

	pObj->bSelected = true;*/
}

void cBATTLEARENA::SelectTeam(int ID)
{
	sOBJECT* pObj = FindObject(ID);
	if (pObj)
		SelectTeam(pObj);
}
