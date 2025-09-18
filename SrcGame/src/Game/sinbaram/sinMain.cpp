/*----------------------------------------------------------------------------*
*	���ϸ� :  sinMain.cpp
*	�ϴ��� :  �Źٶ� ����
*	�ۼ��� :  ����������Ʈ 12��
*	������ :  �ڻ�
*-----------------------------------------------------------------------------*/
#define _SINBARAM_TEST   //����ÿ��� �׻� ���ش� 

#include "sinLinkHeader.h"
#include "..\\Shop\\NewShop.h"
#include "..//cSkinChanger.h"

/*----------------------------------------------------------------------------*
*					         ���� ����
*-----------------------------------------------------------------------------*/

smCHAR_INFO *sinChar;		 //ĳ���� ���� ����ü 
smCHAR_INFO sinCharDisplay;  //ĳ���� ���� ����ü 
int sinbaram_Stop = 0;

#ifndef _CHEADER
#define _CHEADER

#include "..\AntiCheat.h"


#endif

CAntiCheat * pcAntiCheat = NULL;
#include "..//CoinShop.h"
#include "..//BattlePass.h"
#include "..//CBattleEventsWindow.h"
#include "..//CHellsGateHandler.h"
#include "..//TCore.h"
#include "..//cTarget.h"
#include "..//cSorteio.h"
#include "..//cDistribuidorWindow.h"
#include "..//cBattleArenaHandler.h"
#include "..//CRelicWindow.h"
void sinInit()
{
	InitSub();
	InitCursor(); 
	cItem.Init();
	CSKILL->Init();
	cInvenTory.Init();
	cCharStatus.Init();
	cInterFace.Init();
	cShop.Init();
	cTrade.Init();
	cMessageBox.Init();
	cSin3D.Init();
	cSinHelp.Init();
	cSinWarpGate.Init();
	g_CreatePetSystem();
	cHelpPet.Init();
	cSinSod2.Init();
	cKill.Init();
	cBattleArena.Init();
	cSkinChanger.Init();
	g_PCBang_CreatePetSystem();
	cPCBANGPet.Init();
	WarMode.Init();
	DISTRIBUIDORWINDOW->Init();
	chaSiege.init();
	chaQuest.init();
	chaPremiumitem.init();
	Caravana::GetInstance()->Init();
	BattlePass::GetInstance()->Init();
	Sorteio->Init();
	CHellsGateHandler->Init();
	BattleEventWindow->Init();
	RELICWINDOW->Init();
	TCORE::GetInstance()->init();
	
	
	void web_DB_start();
	void clanMENU_INIT(int setN);
	clanMENU_INIT(1);


	Settings::GetInstance()->Init();
}

DWORD dwSinTime = 0;

void sinMain()
{
	sinMouseMain();	
	sinKeyClickMain();

	if (sinGetMouseButton(0) == TRUE)
		sinProc(SINLBUTTONDOWN);
	if (sinGetMouseButton(1) == TRUE)
		sinProc(SINRBUTTONDOWN);

	if (MouseButtonUpEvent == SINLBUTTONUP) {
		sinProc(SINLBUTTONUP);
		MouseButtonUpEvent = 0;

	}

	if (MouseButtonUpEvent == SINRBUTTONUP) {
		sinProc(SINRBUTTONUP);
		MouseButtonUpEvent = 0;

	}

	sinProc(SINMOUSEMOVE);

	MainSub();
	cItem.Main();
	cInterFace.Main();
	CSKILL->Main();
	cInvenTory.Main();
	cCharStatus.Main();
	cShop.Main();
	cTrade.Main();
	cMessageBox.Main();
	cSinHelp.Main();
	cSinWarpGate.Main();
	cHelpPet.Main();
	cSinSod2.Main();
	cBattleArena.Main();
	chaSiege.Main();
	chaQuest.Main();
	chaPremiumitem.Main();
	CHellsGateHandler->Main();
	void ktj_imsi_clanMENU_Main();
	ktj_imsi_clanMENU_Main();

	ShowInterFace();
	cPCBANGPet.Main();


	if (sinbaram_Stop) {
		dwSinTime++;
		if (dwSinTime >= 3 * 70) sinbaram_Stop = 0;
	}
	else dwSinTime = 0;

}

void sinDraw()
{
	GRAPHICENGINE->GetDevice()->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
	GRAPHICENGINE->GetDevice()->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
	GRAPHICENGINE->GetDevice()->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);

	dsDrawOffsetArray = dsARRAY_TOP;

	// Premiuns por baixo das outras coisas
	chaPremiumitem.DrawUp();
	cBattleArena.Draw();
	chaPremiumitem.DrawText();

	dsDrawOffsetArray = dsARRAY_RIGHT | dsARRAY_BOTTOM;
	DrawInterfaceParty();

	dsDrawOffsetArray = dsARRAY_BOTTOM;

	cCharStatus.Draw();

	cCharStatus.DrawCharText();

	dsDrawOffsetArray = dsARRAY_BOTTOM;

	CSKILL->Draw();

	dsDrawOffsetArray = dsARRAY_TOP;

	CSKILL->DrawUp();

	dsDrawOffsetArray = dsARRAY_BOTTOM;

	cInvenTory.Draw();

	cInvenTory.DrawInvenText();

	dsDrawOffsetArray = dsARRAY_TOP;

	cShop.Draw();

	cShop.DrawShopText();

	DISTRIBUIDORWINDOW->Render();

	RELICWINDOW->Render();
	cTrade.Draw();

	cTrade.DrawTradeText();

	dsDrawOffsetArray = dsARRAY_BOTTOM;

	cInterFace.Draw();

	cInterFace.DrawInterText();
	cSkinChanger.Draw();
	
	cItem.Draw();


	dsDrawOffsetArray = dsARRAY_TOP;

	cSinHelp.Draw();

	cSinHelp.DrawText();

	cSinWarpGate.Draw();

	cSinWarpGate.DrawText();

	sinDrawInterEffect();

	dsDrawOffsetArray = dsARRAY_TOP;
	void ktj_imsi_clanMENU_Draw();
	ktj_imsi_clanMENU_Draw();

	Sorteio->Draw();
	dsDrawOffsetArray = dsARRAY_BOTTOM;

	sinDrawText();

	dsDrawOffsetArray = dsARRAY_TOP;

	cHelpPet.Draw();

	cHelpPet.DrawText();

	cSinSod2.Draw();

	cSinSod2.DrawText();

	chaSiege.Draw();

	chaSiege.DrawText();


	if (lpCurPlayer)
	{
		lpCurPlayer->score.draw();
	}

	chaQuest.Draw();

	chaPremiumitem.Draw();

	cMessageBox.Draw();

	cMessageBox.DrawMessageText();

	dsDrawOffsetArray = dsARRAY_TOP;

	WarMode.Draw();
	cKill.Draw();
	Settings::GetInstance()->Draw();
	BattleEventWindow->Draw();
	CHellsGateHandler->Draw();
	TCORE::GetInstance()->Draw();
	BattlePass::GetInstance()->Draw();
	if (GRAPHICDEVICE) 
	{
		DrawCursor();
	}

	GAMECOREHANDLE->pcItemInfoBox->Render(0, 0, RESOLUTION_WIDTH, RESOLUTION_HEIGHT, 0, 0);
	GAMECOREHANDLE->pcSkillInfoBox->Render(0, 0, RESOLUTION_WIDTH, RESOLUTION_HEIGHT, 0, 0);
}

void sinDrawText()
{
	EffectTestDrawText();
	EffectTestDrawText2();
}

void sinProc(int Message)
{

	switch (Message)
	{
		
	case SINLBUTTONDOWN:
		if (sinbaram_Stop)return;
		if (cSkinChanger.isOpen())
		{
			if (!cSkinChanger.LButtonDown())
			{
				cInvenTory.CheckMousePotionNumForm();
				cInvenTory.LButtonDown(pCursorPos.x, pCursorPos.y);
				cInvenTory.ReFormMousePotionNum();
			}
			break;
		}
		if (Sorteio->OnMouseClick(true)) break;
		if (DISTRIBUIDORWINDOW->OnMouseClick(true)) break;
		if (RELICWINDOW->OnMouseClick(true)) break;
		if (BattleEventWindow->OnMouseClick(true))
			break;
		cInvenTory.CheckMousePotionNumForm();
		cMessageBox.LButtonDown(pCursorPos.x, pCursorPos.y);
		if (cBattleArena.LButtonDown())
			break;
		cSinSod2.LButtonDown(pCursorPos.x, pCursorPos.y);    //�Źٶ� Sod2
		if (sinMessageBoxShowFlag && !MyShopExpBox && !nName)return;   //ȫ������ �Է¶����� ��ġ�� ���� ��.�� ũ�� // �庰 - �Է�â
		

		

		
		cInterFace.LButtonDown(pCursorPos.x, pCursorPos.y);  //�������̽� 
		cCharStatus.LButtonDown(pCursorPos.x, pCursorPos.y); //ĳ���� �������ͽ� 
		cInvenTory.LButtonDown(pCursorPos.x, pCursorPos.y);  //�κ��丮 
		CSKILL->LButtonDown(pCursorPos.x, pCursorPos.y);      //��ų 
		cTrade.LButtonDown(pCursorPos.x, pCursorPos.y);      //Ʈ���̵� 
		cItem.LButtonDown(pCursorPos.x, pCursorPos.y);       //������ 
		cShop.LButtonDown(pCursorPos.x, pCursorPos.y);       //���� 
		cSin3D.LButtonDown(pCursorPos.x, pCursorPos.y);      //�Źٶ� 3D
		cSinHelp.LButtonDown(pCursorPos.x, pCursorPos.y);    //�Źٶ� �����
		cSinWarpGate.LButtonDown(pCursorPos.x, pCursorPos.y);//�Źٶ� ��������Ʈ
		cHelpPet.LButtonDown(pCursorPos.x, pCursorPos.y);    //�Źٶ� �� �����
		cInvenTory.ReFormMousePotionNum();                  //�������ش� 
		chaSiege.LButtonDown(pCursorPos.x, pCursorPos.y);
		chaQuest.LButtonDown(pCursorPos.x, pCursorPos.y);
		chaPremiumitem.LButtonDown(pCursorPos.x, pCursorPos.y);
		WarMode.Button();
		BattlePass::GetInstance()->Button();
		Settings::GetInstance()->Button();
		CustomHud::GetInstance()->GotClick = true;
		TCORE::GetInstance()->MouseIn();
		break;
	case SINLBUTTONUP:
		if (sinbaram_Stop)return;
	
		BattleEventWindow->OnMouseClick(false);
		cMessageBox.LButtonUp(pCursorPos.x, pCursorPos.y);   //�޼��� �ڽ� 
		if (sinMessageBoxShowFlag)return;
		Sorteio->OnMouseClick();
		DISTRIBUIDORWINDOW->OnMouseClick(false);
		RELICWINDOW->OnMouseClick(false);
		cInterFace.LButtonUp(pCursorPos.x, pCursorPos.y);    //�������̽� 
		cCharStatus.LButtonUp(pCursorPos.x, pCursorPos.y);   //ĳ���� �������ͽ� 
		cInvenTory.LButtonUp(pCursorPos.x, pCursorPos.y);    //�κ��丮 
		cShop.LButtonUp(pCursorPos.x, pCursorPos.y);		    //���� 
		CSKILL->LButtonUp(pCursorPos.x, pCursorPos.y);	    //��ų 
		cTrade.LButtonUp(pCursorPos.x, pCursorPos.y);	    //Ʈ���̵� 
		cSin3D.LButtonUp(pCursorPos.x, pCursorPos.y);        //�Źٶ� 3D
		cSinHelp.LButtonUp(pCursorPos.x, pCursorPos.y);      //�Źٶ� �����
		cSinWarpGate.LButtonUp(pCursorPos.x, pCursorPos.y);  //�Źٶ� ��������Ʈ
		cHelpPet.LButtonUp(pCursorPos.x, pCursorPos.y);      //�Źٶ� �� �����
		cSinSod2.LButtonUp(pCursorPos.x, pCursorPos.y);      //�Źٶ� Sod2
		//������ �׽�Ʈ
		chaSiege.LButtonUp(pCursorPos.x, pCursorPos.y);
		break;

	case SINRBUTTONDOWN:
		if (MyShopSendButton)return;
		if (sinbaram_Stop)return;
		cMessageBox.RButtonDown(pCursorPos.x, pCursorPos.y); //�޼��� �ڽ� 
		if (sinMessageBoxShowFlag)return;
		cInterFace.RButtonDown(pCursorPos.x, pCursorPos.y);  //�������̽� 
		cCharStatus.RButtonDown(pCursorPos.x, pCursorPos.y); //ĳ���� �������ͽ� 
		cShop.RButtonDown(pCursorPos.x, pCursorPos.y);       //���� 
		cInvenTory.RButtonDown(pCursorPos.x, pCursorPos.y);  //�κ��丮 
		CSKILL->RButtonDown(pCursorPos.x, pCursorPos.y);      //��ų 
		cTrade.RButtonDown(pCursorPos.x, pCursorPos.y);      //Ʈ���̵� 
		cItem.RButtonDown(pCursorPos.x, pCursorPos.y);       //������ 
		cSin3D.RButtonDown(pCursorPos.x, pCursorPos.y);      //�Źٶ� 3D
		cSinHelp.RButtonDown(pCursorPos.x, pCursorPos.y);    //�Źٶ� �����
		cSinWarpGate.RButtonDown(pCursorPos.x, pCursorPos.y);//�Źٶ� ��������Ʈ
		cHelpPet.RButtonDown(pCursorPos.x, pCursorPos.y);    //�Źٶ� �� �����
		cSinSod2.RButtonDown(pCursorPos.x, pCursorPos.y);    //�Źٶ� Sod2

		break;

	case SINRBUTTONUP:
		if (sinbaram_Stop)return;
		cMessageBox.RButtonUp(pCursorPos.x, pCursorPos.y);   //�޼��� �ڽ� 
		if (sinMessageBoxShowFlag)return;
		cInterFace.RButtonUp(pCursorPos.x, pCursorPos.y);    //�������̽� 
		cCharStatus.RButtonUp(pCursorPos.x, pCursorPos.y);   //ĳ���� �������ͽ� 
		cInvenTory.RButtonUp(pCursorPos.x, pCursorPos.y);    //�κ��丮 
		cShop.RButtonUp(pCursorPos.x, pCursorPos.y);		    //���� 
		CSKILL->RButtonUp(pCursorPos.x, pCursorPos.y);	    //��ų 
		cTrade.RButtonUp(pCursorPos.x, pCursorPos.y);	    //Ʈ���̵� 
		cMessageBox.RButtonUp(pCursorPos.x, pCursorPos.y);   //�޼��� �ڽ� 
		cSin3D.RButtonUp(pCursorPos.x, pCursorPos.y);        //�Źٶ� 3D
		cSinHelp.RButtonUp(pCursorPos.x, pCursorPos.y);      //�Źٶ� �����
		cSinWarpGate.RButtonUp(pCursorPos.x, pCursorPos.y);  //�Źٶ� ��������Ʈ
		cHelpPet.RButtonUp(pCursorPos.x, pCursorPos.y);		//�Źٶ� �� �����
		cSinSod2.RButtonUp(pCursorPos.x, pCursorPos.y);		//�Źٶ� Sod2
		break;

	case SINMOUSEMOVE:
		DISTRIBUIDORWINDOW->OnMouseMove();
		BattleEventWindow->OnMouseMove();
		RELICWINDOW->OnMouseMove();
		break;

	case SINKEYDOWN:
		if (NewShop::GetInstance()->openFlag && NewShop::GetInstance()->editingNick)
			return;

		if (sinGetKeyClick(VK_RETURN))
		{
			extern int MessageButtonPosi;
			MessageButtonPosi = 1;
			cMessageBox.LButtonDown(pCursorPos.x, pCursorPos.y);
		}

		if (sinbaram_Stop)return;
		cMessageBox.KeyDown();
		if (sinMessageBoxShowFlag)return;
		cInterFace.KeyDown();    //�������̽� 
		cCharStatus.KeyDown();   //ĳ���� �������ͽ� 
		cInvenTory.KeyDown();    //�κ��丮 
		cShop.KeyDown();		 //���� 
		CSKILL->KeyDown();	     //��ų 
		cTrade.KeyDown();	     //Ʈ���̵� 
		cSin3D.KeyDown();		 //�Źٶ� 3D 
		cSinHelp.KeyDown();		 //�Źٶ� �����
		cSinWarpGate.KeyDown();  //�Źٶ� ��������Ʈ
		cHelpPet.KeyDown();      //�Źٶ� Ű�ٿ�
		cSinSod2.KeyDown();		 //�Źٶ� Sod2
		chaSiege.KeyDown();

		if (sinGetKeyClick('K'))
		{
			if (!WarMode.fOpen)
				WarMode.Open();
			else
				WarMode.Close();
		}

		if (sinGetKeyClick('M'))
		{
			CMINIMAPHANDLE->bLargeMiniMap = !CMINIMAPHANDLE->bLargeMiniMap;
			CMINIMAPHANDLE->iMiniMapSize = CMINIMAPHANDLE->bLargeMiniMap ? MINIMAP_LARGE_SIZE : MINIMAP_SMALL_SIZE;
			CMINIMAPHANDLE->OnMiniMapSizeChanged();
		}

		if (sinGetKeyClick('X')) {
			cHelpPet.PetMessage("*System", 3);
			if (!ExitButtonClick)ExitButtonClick = 1;
			else ExitButtonClick = 0;
			cInterFace.CheckAllBox(SIN_SYSTEM); //â�� �ϳ��� ���� 
		}
		if (sinGetKeyClick('R')) {
			cHelpPet.PetMessage("*RunAndWalk", 3);
			if (cInterFace.sInterFlags.RunFlag)cInterFace.sInterFlags.RunFlag = 0;
			else cInterFace.sInterFlags.RunFlag = 1;
		}
		if (sinGetKeyClick(VK_TAB)) {
			cHelpPet.PetMessage("*Mini_Map", 3);
			if (cInterFace.sInterFlags.MapOnFlag)cInterFace.sInterFlags.MapOnFlag = 0;
			else cInterFace.sInterFlags.MapOnFlag = 1;
		}
		if (sinGetKeyClick('Z')) {
			cInterFace.sInterFlags.CameraAutoFlag++;
			if (cInterFace.sInterFlags.CameraAutoFlag > 2)cInterFace.sInterFlags.CameraAutoFlag = 0;

		}
		if (sinGetKeyClick('D')) {
			cHelpPet.PetMessage("*Party", 3);
			ShowParty();
		}
		if (sinGetKeyClick('Q')) {
			cHelpPet.PetMessage("*Quest", 3);
			ShowQuest();
		}

		if (sinGetKeyClick('L')) {

			if (QuestWindow::GetInstance()->openOverlay) {
				QuestWindow::GetInstance()->openOverlay = false;
			}
			else {
				QuestWindow::GetInstance()->openOverlay = true;
			}					
		}
	

		if (sinGetKeyClick(VK_SPACE)) { //â�� �ݾ��ش� 
			cMessageBox.CloseMessage();
			if (!cCraftItem.OpenFlag && !cAging.OpenFlag && !SmeltingItem.OpenFlag && !ManufactureItem.m_OpenFlag || !cMixtureReset.OpenFlag || cSocket.OpenFlag || cElement.OpenFlag) //����¡�� �ͽ��������� ������������ ESC�� �Դ´� // ������ - �ͽ��� ���� â �߰�
				cInterFace.CheckAllBox(SIN_ALL_CLOSE); //â�� �� �ݾ��ش� 

		}
		if (smConfig.DebugMode) { // ��ġ�� �������� �׽�Ʈ Ű    
			if (sinGetKeyClick('T') && sinGetKeyClick(VK_CONTROL)) {
				if (sinTestFlag)sinTestFlag = 0;
				else sinTestFlag = 1;
			}

			if (sinGetKeyClick('F') && sinGetKeyClick(VK_CONTROL)) { //��¥ ����  
				if (cShop.OpenFlag == SIN_CLOSE)cShop.OpenFlag = SIN_OPEN;
				else cShop.OpenFlag = SIN_CLOSE;

			}
			if (sinGetKeyClick('G') && sinGetKeyClick(VK_CONTROL)) { //��¥ ���� 
				if (cCraftItem.OpenFlag == SIN_CLOSE)cCraftItem.OpenFlag = SIN_OPEN;
				else cCraftItem.OpenFlag = SIN_CLOSE;
			}
			if (sinGetKeyClick('H') && sinGetKeyClick(VK_CONTROL)) { //��¥ ����¡ 
				if (cCraftItem.ForceFlag == SIN_CLOSE)cCraftItem.ForceFlag = SIN_OPEN;
				else cCraftItem.ForceFlag = SIN_CLOSE;
			}
			//if(sinGetKeyClick('J') && sinGetKeyClick(VK_CONTROL) ){ //��¥ â�� 
			//	if(cCraftItem.ForceFlag== SIN_CLOSE)cCraftItem.ForceFlag = SIN_OPEN; 
			//	else cCraftItem.ForceFlag = SIN_CLOSE;
			//}
			//if(sinGetKeyClick('K') && sinGetKeyClick(VK_CONTROL) ){ //��¥ ��ų  
			//	if(SkillMasterFlag== SIN_CLOSE)SkillMasterFlag = SIN_OPEN; 
			//	else SkillMasterFlag = SIN_CLOSE;
			//}

		}
#ifdef _SINBARAM_TEST
		sinTestKey(); //�׽�Ʈ Ű (����ÿ��� �������� �ʴ´�)
#endif


		break;

	}

}

/*----------------------------------------------------------------------------*
*							    ���� ���� 									  *
*-----------------------------------------------------------------------------*/
void sinClose()
{
	//ktj : ��db�� �ӽü����Լ�.  =============================== start
	void clanMENU_close();
	clanMENU_close();
	//=========================================================== end

	CloseSub();			 //������� ���� 
	cInvenTory.Close();  //�κ��丮 ���� 
	cCharStatus.Close(); //ĳ���� �������ͽ� ���� 
	cInterFace.Close();  //�������̽� ���� 
	cItem.Close();       //������ ����
	CSKILL->Close();		 //��ųâ ���� 
	cShop.Close();		 //���� ���� 
	cTrade.Close();
	cMessageBox.Close(); //�޼��� �ڽ� ���� 
	cSin3D.Close();
	cSinHelp.Close();    //�Źٶ� �����
	cSinWarpGate.Close();//�Źٶ� ��������Ʈ
	cHelpPet.Close();	 //�Źٶ� �굵���
	cSinSod2.Close();	 //�Źٶ� Sod2
	//��öȣ : 2005-11-21 ���� 9:00:31
	cPCBANGPet.Close();
}

