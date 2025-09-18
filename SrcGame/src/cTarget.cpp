#include "sinbaram/sinLinkHeader.h"
#include "TJBOY/clanmenu/cE_CViewClanInfo.h"
#include "cTarget.h"
#include "field.h"

extern bool isMousePos(int x, int y, int w, int h);
//extern int DrawClanMark_EachBox(LPDIRECT3DTEXTURE9 clanMark, int x, int y);

cTARGET cTarget;

extern POINT3D EachCameraPos;
extern Graphics::Camera* frameCamera;

void cTARGET::DrawImage(int Mat, int x, int y, int w, int h)
{
	HoDrawTexImage(Mat, x, y, w, h, w, h, 255);
}

void cTARGET::DrawTarget()
{
	int mx = MidX;
	int my = MidY;

	MidX = WinSizeX - 60;
	MidY = 80 + BaseY;

	int sizeBackup = WinSizeX;
	int sizeBackupy = WinSizeY;

	WinSizeX = 800;
	WinSizeY = 600;

	auto backupViewport = Graphics::Graphics::GetInstance()->GetRenderer()->GetViewport();

	SetDxProjection((g_PI / 5.3f), WinSizeX, WinSizeY, 20.f, 4000.f);

	Graphics::Graphics::GetInstance()->GetRenderer()->SetViewport(Graphics::Viewport(WinSizeX, WinSizeY));
	frameCamera->SetProjection((g_PI / 4.4f), (float)WinSizeX / (float)WinSizeY, 20.f, 4000.f);

	smRender.SMSHIFT_PERSPECTIVE_WIDTH = RENDCLIP_DEFAULT_SHIFT_PERSPECTIVE_WIDTH * 5;

	smRender.SMMULT_PERSPECTIVE_HEIGHT = (int)(RENDCLIP_DEFAULT_MULT_PERSPECTIVE_HEIGHT + 25.6f) * 11;

	int dist = 300 * fONE;

	smCHAR_SetCameraPosi(EachCameraPos.x, EachCameraPos.y + 50, dist + EachCameraPos.z, 0, ANGLE_180, 0);

	static auto renderTarget = Graphics::Graphics::GetInstance()->GetRenderTargetFactory()->Create(false);

	if (renderTarget && frameCamera)
	{
		if (Graphics::Graphics::GetInstance()->SetRenderTarget(renderTarget))
		{
			Graphics::Graphics::GetInstance()->Clear();

			auto backupAmbientColor = Graphics::Graphics::GetInstance()->GetRenderer()->GetAmbientColor();
			frameCamera->SetPosition(Math::Vector3(EachCameraPos.x / 256.0f, (EachCameraPos.y + 50) / 256.0f, (dist + EachCameraPos.z) / 256.0f), Math::Vector3(EachCameraPos.x / 256.0f, EachCameraPos.y / 256.0f, 0.0f));

			Graphics::Graphics::GetInstance()->GetRenderer()->SetAmbientColor(Math::Color(0.0f, 0.0f, 0.0f, 1.0f));
			Graphics::Graphics::GetInstance()->GetRenderer()->PushCamera(frameCamera);
			chrEachMaster->Draw(true);
			Graphics::Graphics::GetInstance()->GetRenderer()->PopCamera();
			Graphics::Graphics::GetInstance()->GetRenderer()->SetAmbientColor(backupAmbientColor);
			Graphics::Graphics::GetInstance()->UnsetRenderTarget();
		}

		int w = 57;
		int h = 57;
		int iOffset = (int)((float)w * 0.1f);

		{
			if (Graphics::Sprite::Default->Begin(true))
			{
				Graphics::Sprite::Default->PushTranslation(Math::Vector2(MidX - (w >> 1) + (iOffset >> 1), MidY - (h >> 1) + (iOffset >> 1)));

				w -= iOffset;
				h -= iOffset;

				Graphics::Sprite::Default->Draw(renderTarget->Texture(), Math::Color::White, Math::RectInt((WinSizeX >> 1) - (w >> 1), (WinSizeY >> 1) - (h >> 1), w, h));
				Graphics::Sprite::Default->End();
				Graphics::Sprite::Default->PopTransform();
			}
		}
	}

	Graphics::Graphics::GetInstance()->GetRenderer()->SetViewport(backupViewport);

	MidX = mx;
	MidY = my;

	smRender.SMSHIFT_PERSPECTIVE_WIDTH = 0;
	smRender.SMMULT_PERSPECTIVE_HEIGHT = RENDCLIP_DEFAULT_MULT_PERSPECTIVE_HEIGHT;

	WinSizeX = sizeBackup;
	WinSizeY = sizeBackupy;
	SetDxProjection((g_PI / 4.4f), WinSizeX, WinSizeY, 20.f, 4000.f);
}

void cTARGET::Init()
{
	Mat[BACKGROUND] = CreateTextureMaterial("game\\GUI\\Target\\0.png", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);
	Mat[TARGETBG] = CreateTextureMaterial("game\\GUI\\Target\\1.png", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);
	Mat[TARGETHP] = CreateTextureMaterial("game\\GUI\\Target\\2.png", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);
	Mat[TYPEDEMON] = CreateTextureMaterial("game\\GUI\\Target\\type\\demon.tga", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);
	Mat[TYPEMECHANIC] = CreateTextureMaterial("game\\GUI\\Target\\type\\mechanic.tga", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);
	Mat[TYPEMUTANT] = CreateTextureMaterial("game\\GUI\\Target\\type\\mutant.tga", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);
	Mat[TYPENORMAL] = CreateTextureMaterial("game\\GUI\\Target\\type\\normal.tga", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);
	Mat[TYPENPC] = CreateTextureMaterial("game\\GUI\\Target\\type\\npc.tga", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);
	Mat[TYPEPLAYER] = CreateTextureMaterial("game\\GUI\\Target\\type\\player.tga", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);
	Mat[TYPEUNDEAD] = CreateTextureMaterial("game\\GUI\\Target\\type\\undead.tga", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);
	troca = CreateTextureMaterial("game\\GUI\\Target\\trade.bmp", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);
	troca_ = CreateTextureMaterial("game\\GUI\\Target\\trade_.bmp", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);
	grupo = CreateTextureMaterial("game\\GUI\\Target\\party.bmp", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);
	grupo_ = CreateTextureMaterial("game\\GUI\\Target\\party_.bmp", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);
	clan = CreateTextureMaterial("game\\GUI\\Target\\adclan.bmp", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);
	clan_ = CreateTextureMaterial("game\\GUI\\Target\\adclan_.bmp", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);
	amigo = CreateTextureMaterial("game\\GUI\\Target\\Lamigo.bmp", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);
	amigo_ = CreateTextureMaterial("game\\GUI\\Target\\Lamigo_.bmp", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);

	Mat[RANKNOOB] = CreateTextureMaterial("game\\patente\\noob.tga", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);
	Mat[RANKPRATA] = CreateTextureMaterial("game\\patente\\prata.tga", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);
	Mat[RANKOURO] = CreateTextureMaterial("game\\patente\\ouro.tga", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);
	Mat[RANKMASTER] = CreateTextureMaterial("game\\patente\\master.tga", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);
	Mat[RANKGMASTER] = CreateTextureMaterial("game\\patente\\grandmaster.tga", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);
	Mat[RANKRMASTER] = CreateTextureMaterial("game\\patente\\royalmaster.tga", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);
	Mat[OVERLAY] = CreateTextureMaterial("game\\patente\\targetoverlay_patente.tga", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);
}

void cTARGET::Draw(smCHAR* lpEachPlayer)
{
	if (!cInterFace.sInterFlags.MapOnFlag)
		return;

	unsigned int stage = lpCurPlayer->OnStageField >= 0 && lpCurPlayer->OnStageField < 2 ? StageField[lpCurPlayer->OnStageField]->FieldCode : 0;
	BaseX = (WinSizeX - 301) / 2;

	if (stage == 33 || stage == 30)
		BaseY = 15;
	else
		BaseY = 3;


	if (TargetSerial != lpEachPlayer->dwObjectSerial)
	{
		if (DropDownFlag)
			OpenDropDown();

		TargetSerial = lpEachPlayer->dwObjectSerial;
	}

	dsDrawTexImage(Mat[TARGETBG], smScreenWidth - 105, BaseY + 35, 85, 85, 255);

	DrawTarget();

	DrawImage(Mat[BACKGROUND], smScreenWidth - 284, BaseY + 20, 275, 131);

	float hppercent = (float)(155 * ((float)lpEachPlayer->smCharInfo.Life[0] / (float)lpEachPlayer->smCharInfo.Life[1]));
	dsDrawTexImage(Mat[TARGETHP], (smScreenWidth - 110) - (int)hppercent, BaseY + 66, (int)hppercent, 16, 255);
	int type = TYPENPC;

	switch (chrEachMaster->smCharInfo.Brood)
	{
	case smCHAR_MONSTER_MUTANT:
		type = TYPEMUTANT;
		break;

	case smCHAR_MONSTER_UNDEAD:
		type = TYPEUNDEAD;
		break;

	case smCHAR_MONSTER_DEMON:
		type = TYPEDEMON;
		break;

	case smCHAR_MONSTER_MECHANIC:
		type = TYPEMECHANIC;
		break;

	case smCHAR_MONSTER_NORMAL:
		type = TYPENORMAL;
		break;

	case smCHAR_MONSTER_USER:
		type = TYPEPLAYER;
		break;
	}

	if (chrEachMaster->smCharInfo.State == smCHAR_STATE_NPC)
		type = TYPENPC;
	else if (chrEachMaster->smCharInfo.State == smCHAR_STATE_USER || chrEachMaster->PkMode_CharState == smCHAR_STATE_USER)
		type = TYPEPLAYER;

	dsDrawTexImage(Mat[type], (smScreenWidth - 121), BaseY + 89, 16, 16, 255);

	if (type == TYPEPLAYER && EachTradeButton)
	{
		DrawImage(troca, smScreenWidth - 121, BaseY + 112, 20, 20);
		if (isMousePos(smScreenWidth - 121, BaseY + 112, 20, 20))
			DrawImage(troca_, smScreenWidth - 121, BaseY + 112, 20, 20);
		DrawImage(grupo, smScreenWidth - 121, BaseY + 133, 20, 20);
		if (isMousePos(smScreenWidth - 121, BaseY + 133, 20, 20))
			DrawImage(grupo_, smScreenWidth - 121, BaseY + 133, 20, 20);
		DrawImage(amigo, smScreenWidth - 121, BaseY + 153, 20, 20);
		if (isMousePos(smScreenWidth - 121, BaseY + 153, 20, 20))
			DrawImage(amigo_, smScreenWidth - 121, BaseY + 153, 20, 20);
		if (EachTradeButtonMode) {
			DrawImage(clan, smScreenWidth - 121, BaseY + 173, 20, 20);
			if (isMousePos(smScreenWidth - 121, BaseY + 173, 20, 20))
				DrawImage(clan_, smScreenWidth - 121, BaseY + 173, 20, 20);
		}

	}

	if (DropDownFlag)
	{
		int count = 0;
		for (auto opt : vOptions)
		{
			if (opt.second)
			{
				if (!count)
				{

				}
				else if (count > 0 && count < vOptions.size() - 1)
				{

				}
				else if (count == vOptions.size() - 1)
				{

				}

				count++;
			}
		}
	}

	Text(lpEachPlayer);
}

void cTARGET::Text(smCHAR* lpEachPlayer)
{
	SIZE size = {};
	char buff[255];
	wsprintf(buff, "Level: %d", lpEachPlayer->smCharInfo.Level);
	GetFontTextExtentPoint(buff, lstrlen(buff), &size);

	SetTextColor(0, RGB(255, 255, 255));
	dsTextLineOut(smScreenWidth - 200, BaseY + 45, buff, lstrlen(buff));

	ZeroMemory(buff, 255);

	size = {};
	wsprintf(buff, "%d/%d", lpEachPlayer->smCharInfo.Life[0], lpEachPlayer->smCharInfo.Life[1]);
	GetFontTextExtentPoint(buff, lstrlen(buff), &size);
	dsTextLineOut(smScreenWidth - 200, BaseY + 66, buff, lstrlen(buff));

	if (DropDownFlag)
	{
		int count = 0;
		for (auto opt : vOptions)
		{
			if (opt.second)
			{
				size = {};
				GetFontTextExtentPoint(opt.second, lstrlen(opt.second), &size);

				if (isMousePos(BaseX + 309 + ((87 - size.cx) / 2), BaseY + 16 + (count * 25) + ((25 - size.cy) / 2), size.cx, size.cy))
					SetTextColor(0, RGB(230, 180, 150));
				else
					SetTextColor(0, RGB(255, 255, 255));

				dsTextLineOut(BaseX + 309 + ((87 - size.cx) / 2), BaseY + 16 + (count * 25) + ((25 - size.cy) / 2), opt.second, lstrlen(opt.second));
				count++;
			}
		}
	}

}

bool cTARGET::LButtonDown()
{
	if (!cInterFace.sInterFlags.MapOnFlag)
		return false;

	bool result = false;


	if (isMousePos(smScreenWidth - 121, BaseY + 112, 20, 20))//troca
	{
		handleOption(1);
	}

	if (isMousePos(smScreenWidth - 121, BaseY + 133, 20, 20))//grupo
	{
		handleOption(2);
	}

	if (isMousePos(smScreenWidth - 121, BaseY + 153, 20, 20))//amigo
	{
		handleOption(3);
	}

	if (isMousePos(smScreenWidth - 121, BaseY + 173, 20, 20))//clan
	{
		handleOption(4);
	}



	return false;
}

bool cTARGET::MouseIn()
{
	return isMousePos(BaseX, BaseY, 340 + 95, 111);
}

bool cTARGET::StopMotion()
{
	if (isMousePos(smScreenWidth - 114, BaseY + 160, 20, 20) || isMousePos(smScreenWidth - 45, BaseY + 160, 20, 20)
		|| isMousePos(smScreenWidth - 91, BaseY + 160, 20, 20) || isMousePos(smScreenWidth - 68, BaseY + 160, 20, 20))
		return true;

	return false;
}

void cTARGET::OpenDropDown()
{
	if (DropDownFlag)
	{
		vOptions.clear();
		DropDownFlag = 0;
	}
	else
	{
		if (EachTradeButton)
		{
			//vOptions.insert(std::pair<int, char*>(1, "Troca"));
			//vOptions.insert(std::pair<int, char*>(2, "Grupo"));
			//vOptions.insert(std::pair<int, char*>(3, "Adicionar"));
			if (EachTradeButtonMode)
				//vOptions.insert(std::pair<int, char*>(4, "Clan"));

				DropDownFlag = 1;
		}
	}
}

extern void g_IsCheckClanMember(smCHAR* pChar);
extern char* mgRequestTrade;
extern char* mgRequestTrade2;

void cTARGET::handleOption(int code)
{
	char szBuff[500];

	switch (code)
	{
	case 1:
		if (GetTradeDistanceFromCode(chrEachMaster->dwObjectSerial) == TRUE)
		{

			SendRequestTrade(chrEachMaster->dwObjectSerial, 0);
			wsprintf(szBuff, mgRequestTrade, chrEachMaster->smCharInfo.szName);
		}
		else
		{
			wsprintf(szBuff, mgRequestTrade2, chrEachMaster->smCharInfo.szName);
		}

		//AddChatBuff(szBuff);
		break;

	case 2:
		wsprintf(szBuff, "//party %s", chrEachMaster->smCharInfo.szName);
		SendChatMessageToServer(szBuff);
		break;

	case 3:
		InterfaceParty.latest_Insert(chrEachMaster->smCharInfo.szName);
		InterfaceParty.friend_Insert(chrEachMaster->smCharInfo.szName);

		InterfaceParty.Main_menuSet(2);
		InterfaceParty.chat_changeMENU(1);
		if (InterfaceParty.PartyPosState == PARTY_NONE)	ShowParty();
		break;

	case 4:
		g_IsCheckClanMember(chrEachMaster);
		break;
	}

	OpenDropDown();
}
