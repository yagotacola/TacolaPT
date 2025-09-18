#include "..\..\globals.h"

#define CE_CHATLIST_CPP
#include <windows.h>
#include <stdio.h>
#include <tchar.h>
#include <math.h>

#include "tjclanDEF.h"

#ifdef USE_PROSTONTALE		//=========== ?????????

#include "..\\..\\sinbaram\\SinLinkHeader.h"
#include "..\\..\\HoBaram\\HoLinkHeader.h"
#include "..\\..\\HoBaram\\HoTextFile.h"

#endif

#include "tjclan.h"

#include "tjscroll.h"
#include "cE_chatlist.h"

#include "cE_report.h"
#include "cE_CViewClanInfo.h"
#include "..\\isaocheck\\auth.h"
#include "..\\isaocheck\\isaocheck.h"

#include "..\\ygy\\ygyheader.h"
#include "../../../MicVolume.h"


#ifdef USE_PROSTONTALE		//=========== ?????????
#else
extern int MouseDblClick;		//tjclan.cpp
#endif

extern int TJmb2[3];

extern int vrunRuning;					//vrun.dat? ????


// ??? (??? ??)
extern int sinChatEnter;          //?? ?? (???? ???? ?? ?? ??? )
extern int SubChatHeight;	      //??? ?? ?? ?? ? 	


#define MOUSE0_2() TJmb2[0]


int OpenBuf_x[50] = { 800, 800, 800, 800, 800, 800,
800, 800, 800, 800, 800, 800, 800, 800, 800, 800, 800, 800,
750,700,650,600,560,550,548,546,544,540,539,-1,-1 };
//750,700,650,633,631,629,627,-1, -1};

int CloseBuf_x[50] = { 500,556,606,656,706,756,800 };

extern POINT	pCursorPos;
extern char szConnServerName[16];

extern BOOL bMic;
int g_nMicBtn;
int micInit;

//????????? ???? ????.
int chatlistSPEAKERflag()
{
	return cClanChatting.Chatting_button;			//??? on,off 
}

//0,1? ?????.
void chatlistSPEAKERflagChg(int flag)
{
	cClanChatting.Chatting_button = flag;			//??? on,off 


	if (flag == 0) {		//???? ??
		for (int i = 0; i < 40; i++) {
			banisF[i] = 0;			//?????? ???? ????? ???.
		}
		void clan_chat_WhisperPartyPlayer_close();	//hoparty.cpp?? ??.
		clan_chat_WhisperPartyPlayer_close();	//hoparty.cpp?? ??.
	}
}



//*****************************************************************************
CLANEntity_chatting::CLANEntity_chatting()
{
	ZeroMemory(&ClanChatList, sizeof(CHATLIST));
	nBoxMove = 0;
	bIsDrawBoxFinish = 0;
	hChatListBoxLine = 0;
	hChatListBoxTitle = NULL;
	for (int i = 0; i < 2; i++)
	{
		hButtonClose[i] = NULL;
		hClanWon[i] = NULL;
		hChatIcon[i] = NULL;
		//???
#ifdef PARKMENU
		hMicOption[i] = NULL;
		hMicVOLUPDOWN[i] = NULL;
#endif
	}

	hMark = NULL;
	Chatting_button = 0;
	nSaveClanWonPos = -1;
	nDoublClick = -1;

	//???
#ifdef PARKMENU
	MicOpt_button = 0;
	g_nMicBtn = 0;
	hMicOptTitle = NULL;
	hMicSortLine = NULL;
	hMicONBack = NULL;
	hMicONChk = NULL;
	hMicVolBar = NULL;
#endif
}

CLANEntity_chatting::~CLANEntity_chatting()
{
	if (hChatListBoxTitle != NULL)
	{
		hChatListBoxTitle->Release();
		hChatListBoxTitle = NULL;
	}

	//######################################################################################
	//? ? ? : ? ? ?
	if (hChatClanWon)
	{
		hChatClanWon->Release();
		hChatClanWon = NULL;
	}
	//######################################################################################


	for (int i = 0; i < 2; i++)
	{
		if (hButtonClose[i] != NULL)
		{
			hButtonClose[i]->Release();
			hButtonClose[i] = NULL;
		}
		if (hClanWon[i] != NULL)
		{
			hClanWon[i]->Release();
			hClanWon[i] = NULL;
		}
		if (hChatIcon[i] != NULL)
		{
			hChatIcon[i]->Release();
			hChatIcon[i] = NULL;
		}
	}

	//???
	if (hClanChatToolTip != NULL)
	{
		hClanChatToolTip->Release();
		hClanChatToolTip = NULL;
	}
	if (hBtnCloseToolTip != NULL)
	{
		hBtnCloseToolTip->Release();
		hBtnCloseToolTip = NULL;
	}
}




//*****************************************************************************
int CLANEntity_chatting::Init(int Life)
{
	life = Life;
	InitClanChatList();
	return 1;
}

void CLANEntity_chatting::Close()
{
#ifdef USE_PROSTONTALE
	if (hMark) { hMark->Release();  hMark = NULL; }

	//######################################################################################
	//? ? ? : ? ? ?
	if (hChatListBoxTitle != NULL)
	{
		hChatListBoxTitle->Release();
		hChatListBoxTitle = NULL;
	}

	for (int i = 0; i < 2; i++)
	{
		if (hButtonClose[i] != NULL)
		{
			hButtonClose[i]->Release();
			hButtonClose[i] = NULL;
		}
		if (hClanWon[i] != NULL)
		{
			hClanWon[i]->Release();
			hClanWon[i] = NULL;
		}
		if (hChatIcon[i] != NULL)
		{
			hChatIcon[i]->Release();
			hChatIcon[i] = NULL;
		}
	}


	//???
	if (hBtnCloseToolTip)
	{
		hBtnCloseToolTip->Release();
		hBtnCloseToolTip = NULL;
	}
	if (hClanChatToolTip)
	{
		hClanChatToolTip->Release();
		hClanChatToolTip = NULL;
	}


	if (hChatClanWon)
	{
		hChatClanWon->Release();
		hChatClanWon = NULL;
	}
	//######################################################################################

#endif
}













int cN_Pressf = 0;	//???? ?? ??
int cN_PressfDBL = 0;	//???? ???? ?? ??.



void cN_PressfDBL_clear()
{
	cN_PressfDBL = 0;
}



void CLANEntity_chatting::chat_WhisperPartyPlayer2(int num)
{
	//??? =================================================== start
	if (cN_Pressf == 0) {
		cN_Pressf = num;		//???
		return;
	}
	else {
		cN_PressfDBL = cN_Pressf;
		cN_Pressf = 0;
#ifdef  USE_PROSTONTALE
		WhisperPartyPlayer(szChatClanWon[(cN_PressfDBL - 4)]);
#endif
	}
	//??? =================================================== end
}





//??->??->????,?????? ????? ????.
void CLANEntity_chatting::chat_WhisperPartyPlayer(int num)
{

	//??? =================================================== start
	if (num != -1) {
		cN_Pressf = num;		//???
		return;
	}
	//??? =================================================== end

	//???? ================================================= start
	else {
		if (cN_PressfDBL == cN_Pressf) {
			cN_PressfDBL = 0;	//?????? ?????.
			return;
		}

		cN_PressfDBL = cN_Pressf;
#ifdef  USE_PROSTONTALE
		//WhisperPartyPlayer( cldata.clanWon[  (cN_PressfDBL - 4)  ]   );
		WhisperPartyPlayer(szChatClanWon[(cN_PressfDBL - 4)]);
#endif
	}
	//???? ================================================= end
}


void clan_chat_WhisperPartyPlayer_close()	//hoparty.cpp?? ??.
{
	cClanChatting.chat_WhisperPartyPlayer_close();
}
//????? ???? ???.
void CLANEntity_chatting::chat_WhisperPartyPlayer_close()
{
	//cN_PressfDBL =0;
	cN_Pressf = 0;

	//i+nScl_Bar
	//if(ClanChatList.clanWon[i+nScl_Bar])
	//{
}













//
void chatList_Main_CHATLIST_END()
{
	bOpenChatList = FALSE;   //?????? ???.
}


//*****************************************************************************
int ret_menuN = 0;
void CLANEntity_chatting::Main()
{


	int i;
	char szFile[255];
	char server;
	char uniqueclanmark[64];
	if (life == 0) return;


	//??, ???? ???? ????
	ret_menuN = 0;

	switch (ChatList_CmenuN)
	{
	case CHATLIST_END:
		//C_menuN = CLAN_AllEnd;				
		OpenFlag = 0;
		ChatList_CmenuN = 0;
		ChatList_CmenuN2 = 0;
		//ktj
		ClanCharMove = 0;
		ClanCLCharMove = 0;
		cnt = 0;
		CLAN_ERROR_ret = -1;
		//bIsClose = FALSE;			
		//MOUSE0()=0;	
		ClanCLCharMove = 0;
		ret_menuN = 3;

		g_nMicBtn = 0;

		void TJBscrollWheelClear_ChatL();	//hoparty.cpp? ???????
		TJBscrollWheelClear_ChatL();		//hoparty.cpp? ???????
		break;

	case CHATLIST_READDATA:

		switch (ChatList_CmenuN2) {
		case 0:
			bIsReadData = TRUE;
			ClanCLCharMove = 1;		//??? ??? ???????.

			ANSdata.ret_val = -1;

			WebDB.Resume();		//?db? ????.
			//??? ?????? ???.
			WebDB.ReadClan(cldata.szID, cldata.gserver, cldata.ClanZang_Name);
			ChatList_CmenuN2 = 1;
			break;
		case 1:


			switch (ANSdata.ret_val)
			{
				//ygy
			case 0://??? ??? ??
				WebDB.Suspend();
				//ktj : ??.
				/*
				wsprintf(szErrorMsg, "??? ??? ??");
				C_menuN = CHATLIST_ERROR;
				menuInit(C_menuN);
				CLAN_ERROR_ret=CLAN_AllEnd;		//?????????????.
				C_menuN2=-1;
				*/

				ChatList_CmenuN = CHATLIST_END;		//?????????????.
				ChatList_CmenuN2 = -1;
				break;
			case 1://????? ????????? ??
				WebDB.Suspend();
				ParsigClanWon(ANSdata.ret_Buf);
				server = cldata.ClanMark[0];
				strcpy(uniqueclanmark, &cldata.ClanMark[3]);

				wsprintf(szFile, "%s\\%s\\%c_%s.%s", SAVE_DIR, szConnServerName, server, uniqueclanmark, SAVE_EXE);
#ifdef  USE_PROSTONTALE

				if (strcmp(szFile_hMark, szFile) != 0) {
					strcpy(szFile_hMark, szFile);
					hMark = LoadDibSurfaceOffscreen(szFile_hMark);


					extern char loadis[256];
					wsprintf(loadis, "??? %s ", szFile_hMark);


					if (hMark == NULL)
					{
						wsprintf(loadis, "?????. %s ", szFile_hMark);

						ChatList_CmenuN = CHATLIST_READ_CLANMARK;
						ChatList_CmenuN2 = 0;
						break;
					}
				}

#else
				hMark = (HBITMAP)LoadImage(NULL, szFile,
					IMAGE_BITMAP,
					0, 0,
					LR_LOADFROMFILE);
#endif


				ChatList_CmenuN = CLAN_DISPLAY_OPEN;	//stats? 0?? 6?????? ? ??????????
				menuInit(ChatList_CmenuN);
				ChatList_CmenuN2 = -1;
				break;
			case 100:
				WebDB.Suspend();
				/*
				//ygy : ????
				wsprintf(szErrorMsg, sz100Error);
				C_menuN = CHATLIST_ERROR;
				menuInit(C_menuN);
				CLAN_ERROR_ret=CLAN_AllEnd;		//?????????????.
				C_menuN2=-1;
				*/

				ChatList_CmenuN = CHATLIST_END;		//?????????????.
				ChatList_CmenuN2 = -1;
				break;
			case ISAO_ERR_TCP_CONNECT:
				WebDB.Suspend();
				//ygy : ????				
				ChatList_CmenuN = CLAN_ERROR;
				//cClanReport.InitMsg(szServerConnectErrorMsg);
				//cClanReport.menuInit(C_menuN);

				break;

			default:
				if (ANSdata.ret_val != -1) {		//????? ?? ?? ??? ??.
					WebDB.Suspend();
					ChatList_CmenuN = 254;				//??????? ????? ????? ??.
					menuInit(ChatList_CmenuN);

					ChatList_CmenuN2 = -1;
				}
				break;
			}
			break;
		}
		break;
	case CLAN_DISPLAY_BEFORE:
		ChatList_CmenuN = CLAN_DISPLAY_INFO;
		menuInit(ChatList_CmenuN);
		break;


	case CLAN_DISPLAY_INFO:
		i = chkeckMenuN();
		switch (i) {
		case 0:
			menuMouseOver[0] = 1;
			break;
		case 1:
			menuMouseOver[1] = 1;
			break;
		case 12:
			i = i;
			break;
		case 13:
			i = i;
			break;

		case 24:
			menuMouseOver[24] = 1;
			break;
		case 25:
			if (g_nMicBtn == 0)
				break;
			else if (g_nMicBtn == 1)
				menuMouseOver[25] = 1;
			break;
		case 26:
			if (g_nMicBtn == 0)
				break;
			else if (g_nMicBtn == 1)
				menuMouseOver[26] = 1;
			break;
		case 27:
			if (g_nMicBtn == 0)
				break;
			else if (g_nMicBtn == 1)
				menuMouseOver[27] = 1;
			break;
		case 28:
			if (g_nMicBtn == 0)
				break;
			else if (g_nMicBtn == 1)
				menuMouseOver[28] = 1;
			break;
		case 29:
			if (g_nMicBtn == 0)
				break;
			else if (g_nMicBtn == 1)
				menuMouseOver[29] = 1;
			break;

		default:
			memset(menuMouseOver, -1, sizeof(int) * 30);
			break;
		}




		extern BOOL IsDrawGuideHelp; //???? ?? ??? ??
		//ygy : ? ???
		if (!IsDrawGuideHelp) {
			if (TJwheel != 0) {			//ktj : wheel>0 ? ??? ???  wheel<0 ? ?? ???
				scrIconPos.top = tscr_CL.ret_WHEELpoint(TJwheel, scrIconPos.top);
				nScl_Bar = tscr_CL.topScrollLineNum(scrIconPos.top);
				TJwheel = 0;
			}
		}
		//ygy : ? ???


#ifdef USE_PROSTONTALE		//=========== ?????????
		if (MOUSE0_2())
#else
		if (MOUSE0())
#endif
		{



			//
			i = i;
			//i = chkeckMenuN();
			//pCursorPos.x = pCursorPos.x;
			switch (i)
			{


			case 16:			//????? ??? ? ??????
			case 17:
			case 18:
			case 19:
			case 20:
			case 21:
			case 22:
			case 23:
				//???? ???? ??????.
				if (cldata.clanWon[(i - 16) + nScl_Bar][0] != 0)
				{
					chat_WhisperPartyPlayer((i - 12) + nScl_Bar);	//i?? 4? ?????? 0???????
				}
				break;


			case 4:				//???? ??? ???? ?????????.
			case 5:
			case 6:
			case 7:
			case 8:
			case 9:
			case 10:
			case 11:
#ifdef USE_PROSTONTALE		//=========== ?????????
				MOUSE0_2() = 0;
#else
				MOUSE0() = 0;
#endif						

				//???? ???? ??????.
				if (cldata.clanWon[(i - 4) + nScl_Bar][0] != 0)
				{
					chat_WhisperPartyPlayer2(i + nScl_Bar);	//i?? 4? ?????? 0???????
				}

				if (!banisF[(i - 4) + nScl_Bar])
				{
					ZeroMemory(banisF, sizeof(banisF));
					banisF[(i - 4) + nScl_Bar] = !banisF[(i - 4) + nScl_Bar];
				}


				/*if(banisF[ (i-4) + nScl_Bar] == 0)
					banisF[ (i-4) + nScl_Bar] += 1;
				else if(banisF[ (i-4) + nScl_Bar] == 1){
					banisF[ (i-4) + nScl_Bar] += 1;
				}
				else
				{
					ZeroMemory(banisF,sizeof(banisF));
					banisF[ (i-4) + nScl_Bar] = !banisF[  (i-4) + nScl_Bar  ];
				}
				*/
				break;


			case 0:


				//ktj : ??
				//Chatting_button = !Chatting_button;

				//?? ?? ?? ??
#ifdef USE_PROSTONTALE		//=========== ?????????
				int IsClanChatting();
				IsClanChatting();
#endif


				//banisF[0] = !banisF[0];
				//C_menuN = CLAN_DISPLAY_CLOSE;
				//bIsClose = TRUE;				
				//AddSize = 0;
				//cnt = 0;
#ifdef USE_PROSTONTALE		//=========== ?????????
				MOUSE0_2() = 0;
#else
				C_menuN = CLAN_DISPLAY_CLOSE;
				MOUSE0() = 0;
				bIsClose = TRUE;
				AddSize = 0;
				cnt = 0;
#endif		

				break;
			case 1:

#ifdef USE_PROSTONTALE		//=========== ?????????
				ChatList_CmenuN = CHATLIST_END;
				//C_menuN2 = -1;		
				cnt = 0;
				//AddSize = 0;
				CLAN_ERROR_ret = -1;
				ClanCLCharMove = 0;
				OpenFlag = 0;
				ChatList_CmenuN = 0;
				ChatList_CmenuN2 = 0;
				//ktj
				ClanCharMove = 0;
				ClanCLCharMove = 0;
				bOpenChatList = FALSE;
				//??, ???? ???? ????
				ret_menuN = 3;
				g_nMicBtn = 0;
#else
				ChatList_CmenuN = CLAN_DISPLAY_CLOSE;
				bIsClose = TRUE;
				AddSize = 0;
				cnt = 0;
#endif

				break;
			case 12:
				nScl_Bar = tscr_CL.topScrollLineNum(pCursorPos.y);
				//ktj : ??? ??? ?????
				scrIconPos.top = pCursorPos.y - 8;

				break;




			case 15:									//================??? ??
				if (cN_PressfDBL != 0) break;		//????? ????????? ?? ????.
				//tjScroll.cpp
				void TJBscrollWheelClear_ChatL();
				TJBscrollWheelClear_ChatL();

				ChatList_CmenuN = CHATLIST_END;
				//C_menuN2 = -1;		
				cnt = 0;
				//AddSize = 0;
				CLAN_ERROR_ret = -1;
				ClanCLCharMove = 0;
				OpenFlag = 0;
				ChatList_CmenuN = 0;
				ChatList_CmenuN2 = 0;
				//ktj
				ClanCharMove = 0;
				ClanCLCharMove = 0;
				bOpenChatList = FALSE;
				//??, ???? ???? ????
				ret_menuN = 1;
				g_nMicBtn = 0;
				break;


			case 14:									//================??? ??
				if (cN_PressfDBL != 0) break;		//????? ????????? ?? ????.

				//tjScroll.cpp
				void TJBscrollWheelClear_ChatL();
				TJBscrollWheelClear_ChatL();

				ChatList_CmenuN = CHATLIST_END;
				//C_menuN2 = -1;		
				cnt = 0;
				//AddSize = 0;
				CLAN_ERROR_ret = -1;
				ClanCLCharMove = 0;
				OpenFlag = 0;
				ChatList_CmenuN = 0;
				ChatList_CmenuN2 = 0;
				//ktj
				ClanCharMove = 0;
				ClanCLCharMove = 0;
				bOpenChatList = FALSE;
				ret_menuN = 2;
				g_nMicBtn = 0;
			case 24:

				MOUSE0_2() = 0;
				if (g_nMicBtn == 1)
					g_nMicBtn = 0;
				else if (g_nMicBtn == 0)
				{
					g_nMicBtn = 1;
					if (micInit == 0)
					{
						micInit = cmicvol.Init();
						if (micInit != 0)
							nVol = (int)(cmicvol.VolDevice(&cmicvol.m_MicIn) / cmicvol.nVolStep);
					}
				}
				break;
			case 25:
				MOUSE0_2() = 0;
				if (g_nMicBtn == 1)
					g_nMicBtn = 0;
				break;
			case 26:
				MOUSE0_2() = 0;
				if (bMic == FALSE)
				{
					bMic = TRUE;
					void ParkSetMicOnOFF();
					ParkSetMicOnOFF();
				}
				break;
			case 27:
				MOUSE0_2() = 0;
				if (bMic == TRUE)
				{
					bMic = FALSE;
					void ParkSetMicOnOFF();
					ParkSetMicOnOFF();
				}
				break;
			case 28:
				MOUSE0_2() = 0;
				if (micInit != 0)
				{
					nVol = nVol - 10;
					if (nVol < 0)
					{
						nVol = 0;
						break;
					}
					else
					{
						float ntmp;
						ntmp = ((float)nVol / 10) * cmicvol.nVolStep;
						if (ntmp <= 0)
							ntmp = 0;
						cmicvol.SetDeviceCtrl(&cmicvol.m_MicIn, ntmp);
						break;
					}
				}
				break;
			case 29:
				MOUSE0_2() = 0;
				if (micInit != 0)
				{
					nVol = nVol + 10;
					if (nVol >= 90)
					{
						nVol = 90;
						break;
					}
					else
					{
						float ntmp;
						ntmp = ((float)nVol / 10) * cmicvol.nVolStep;
						if (ntmp >= cmicvol.m_MicIn.nMax)
							ntmp = (float)cmicvol.m_MicIn.nMax;
						cmicvol.SetDeviceCtrl(&cmicvol.m_MicIn, ntmp);
						break;
					}
				}
				break;
			default:
				//ygy : ????
				MOUSE0_2() = 0;
				break;

			}
		}




		//???? ?? ??  ======================================================== start
		//?? ???...  ?????
		if (MouseDblClick)
		{
			switch (i) {
			case 16:
			case 17:
			case 18:
			case 19:
			case 20:
			case 21:
			case 22:
			case 23:

				//DoubleClick(i);
#ifdef USE_PROSTONTALE		//=========== ?????????
				chat_WhisperPartyPlayer(-1);
#endif

				MouseDblClick = 0;
				break;
			}
		}
		//???? ?? ??  ======================================================== end



		break;


	case CLAN_DISPLAY_OPEN:

		OCcnt++;
		if (OpenBuf_x[OCcnt] == -1)
		{
			bOpenChatList = TRUE;
			ChatList_CmenuN = CLAN_DISPLAY_INFO;
			menuInit(ChatList_CmenuN);
			OCcnt--;
		}
		else {
			ChatListBoxX = OpenBuf_x[OCcnt];
		}

		break;

	case CLAN_DISPLAY_CLOSE:
		OCcnt--;
		if (OCcnt == 0)
		{
			bOpenChatList = FALSE;
			ChatList_CmenuN = CHATLIST_END;
			menuInit(ChatList_CmenuN);
			OCcnt = 0;
			//AddSize = 0;
		}
		ChatListBoxX = OpenBuf_x[OCcnt];

		break;



	case CLAN_CLOSE_END_BEFORE:
		bIsClose = TRUE;
		AddSize = 0;
		cnt = 0;
		ChatList_CmenuN = CLAN_CLOSE_ENDING;
		break;

	case CLAN_CLOSE_ENDING:
		OCcnt--;
		if (OCcnt == 0)
		{
			ChatList_CmenuN2 = 0;
			OpenFlag = 1;
			joinAnswer = 0;
			ChatList_CmenuN = CLAN_NPC_START;
			menuInit(ChatList_CmenuN);
			OCcnt = 0;
			AddSize = 0;
		}
		ChatListBoxX = OpenBuf_x[OCcnt];
		break;



		//======================================================================
	case CHATLIST_READ_CLANMARK:
		//======================================================================

		switch (ChatList_CmenuN2) {
		case 0:
			ANSdata.ret_val = -1;

			WebDB.Resume();		//?db? ????.
			//WebDB.MarkREAD(cldata.ClanMark);
			WebDB.MarkREAD(cldata.name, cldata.ClanMark);
			ChatList_CmenuN2 = 1;
			break;
		case 1:

			switch (ANSdata.ret_val)
			{
				//ygy
			case 1://?? ?? ?? ??
				WebDB.Suspend();
				//wsprintf(szFile,"image\\clanDATA\\%s.%s",cldata.name,cldata.ClanMark);
				//#ifdef  USE_PROSTONTALE
				//hMark = LoadDibSurfaceOffscreen(szFile);

				//#else
				//hMark = (HBITMAP)LoadImage(NULL,szFile,
				//			IMAGE_BITMAP,
				//			0,0,
				//			LR_LOADFROMFILE);
				//#endif
				ChatList_CmenuN = CHATLIST_READDATA;
				ChatList_CmenuN2 = 0;

				break;
			case 2://?? ?? ?? ??
				WebDB.Suspend();

				//wsprintf(szErrorMsg, szReadClanMarkErrorMsg);
				//ChatList_CmenuN = CLAN_REAMMAKR_ERROR;
				//cClanReport.InitMsg(szReadClanMarkErrorMsg);
				//menuInit(ChatList_CmenuN);
				//CLAN_ERROR_ret=CLAN_AllEnd;		//?????????????.			
				//ChatList_CmenuN2=-1;	
				break;
			case ISAO_ERR_TCP_CONNECT:
				WebDB.Suspend();
				//wsprintf(szErrorMsg, szServerConnectErrorMsg);
				//ChatList_CmenuN = CLAN_REAMMAKR_ERROR;
				//cClanReport.InitMsg(szServerConnectErrorMsg);				
				//menuInit(ChatList_CmenuN);
				//C_menuN2=-1;	
				break;

			default:
				if (ANSdata.ret_val != -1) {		//????? ?? ?? ??? ??.
					WebDB.Suspend();

					//ChatList_CmenuN = 254;				//??????? ????? ????? ??.
					//menuInit(ChatList_CmenuN );

					//C_menuN2=-1;
				}
				break;
			}
		}
		break;
	}

}




//*****************************************************************************



//***************************************************************************************
void CLANEntity_chatting::menuInit(int num)
{
	int bx = 0, by = 0;
	int      nNext = 0, nMenuPos = 0, nAdd = 0, nWidth = 0;
	int      nFirstIconSave = 0;
	char szFile[255];
	char server;
	char UniqueClanMark[64];

	switch (num) {
	case CLAN_DISPLAY_INFO:
		if (vrunRuning == 0)			//vrun.dat ? ??????
		{
			ChatList_menuSu = 23;
		}
		else if (vrunRuning == 1)		//vrun.dat ? ?????
		{
			ChatList_menuSu = 30;
		}
		nScl_Bar = 0;
		SortClanWonList();
		server = cldata.ClanMark[0];
		strcpy(UniqueClanMark, &cldata.ClanMark[3]);




		wsprintf(szFile, "%s\\%s\\%c_%s.%s", SAVE_DIR, szConnServerName, server, UniqueClanMark, SAVE_EXE);
#ifdef  USE_PROSTONTALE

		if (strcmp(szFile_hMark, szFile) != 0) {
			strcpy(szFile_hMark, szFile);

			if (hMark) { hMark->Release();  hMark = NULL; }

			hMark = LoadDibSurfaceOffscreen(szFile_hMark);

			extern char loadis[256];
			wsprintf(loadis, "??? %s ", szFile_hMark);


			if (hMark == NULL)
			{
				wsprintf(loadis, "?????. %s ", szFile_hMark);
				ChatList_CmenuN = CHATLIST_READ_CLANMARK;
				ChatList_CmenuN2 = 0;

			}
		}




#else
		if (hMark == NULL) {
			hMark = (HBITMAP)LoadImage(NULL, szFile,
				IMAGE_BITMAP,
				0, 0,
				LR_LOADFROMFILE);

		}
#endif


#ifdef USE_PROSTONTALE		//=========== ?????????
		bx = 20;
		by = 20;
#else		
		bx = 20;
		by = 20;
#endif

		ChatList_menuPos[0].left = CHATICON_X;//174;		//yes
		ChatList_menuPos[0].top = CHATICON_Y;//353;
		ChatList_menuPos[0].right = ChatList_menuPos[0].left + bx;
		ChatList_menuPos[0].bottom = ChatList_menuPos[0].top + by;

#ifdef USE_PROSTONTALE		//=========== ?????????
		bx = 20;
		by = 20;
#else		
		bx = 20;
		by = 20;
#endif

		ChatList_menuPos[1].left = CHATCLOSE_X;//254		//no
		ChatList_menuPos[1].top = CHATICON_Y; //353
		ChatList_menuPos[1].right = ChatList_menuPos[1].left + bx;
		ChatList_menuPos[1].bottom = ChatList_menuPos[1].top + by;

		//yes, no ??? ??
#ifdef USE_PROSTONTALE		//=========== ?????????
		bx = 68;
		by = 27;
#else		
		bx = 68;
		by = 27;
#endif

		ChatList_menuPos[2].left = BackStartPos.x + BUTTON1_BOX_X;//166;		//yes ??? ??
		ChatList_menuPos[2].top = BackStartPos.y + BUTTON1_BOX_Y;//348
		ChatList_menuPos[2].right = ChatList_menuPos[2].left + bx;
		ChatList_menuPos[2].bottom = ChatList_menuPos[2].top + by;

#ifdef USE_PROSTONTALE		//=========== ?????????
		bx = 68;
		by = 27;
#else		
		bx = 68;
		by = 27;;
#endif

		ChatList_menuPos[3].left = BackStartPos.x + BUTTON2_BOX_X;	//246	//no ??? ??
		ChatList_menuPos[3].top = BackStartPos.y + BUTTON2_BOX_Y;//348
		ChatList_menuPos[3].right = ChatList_menuPos[3].left + bx;
		ChatList_menuPos[3].bottom = ChatList_menuPos[3].top + by;

		//===============??? ?? ??=====================



#ifdef USE_PROSTONTALE		//=========== ?????????
		bx = 13;
		by = 17;
#else
		bx = 13;
		by = 17;
#endif

		ChatList_menuPos[4].left = CHATING_CLANWON_LIST_X;	//246	//no ??? ??
		ChatList_menuPos[4].top = CHATING_CLANWON_LIST_Y;//348
		ChatList_menuPos[4].right = ChatList_menuPos[4].left + bx;
		ChatList_menuPos[4].bottom = ChatList_menuPos[4].top + by;

#ifdef USE_PROSTONTALE		//=========== ?????????
		bx = 13;
		by = 17;
#else
		bx = 13;
		by = 17;
#endif

		ChatList_menuPos[5].left = CHATING_CLANWON_LIST_X;
		ChatList_menuPos[5].top = CHATING_CLANWON_LIST_Y + (CHATING_CLANWON_LIST_CAP * 1);
		ChatList_menuPos[5].right = ChatList_menuPos[5].left + bx;
		ChatList_menuPos[5].bottom = ChatList_menuPos[5].top + by;

#ifdef USE_PROSTONTALE		//=========== ?????????
		bx = 13;
		by = 17;
#else
		bx = 13;
		by = 17;
#endif

		ChatList_menuPos[6].left = CHATING_CLANWON_LIST_X;
		ChatList_menuPos[6].top = CHATING_CLANWON_LIST_Y + (CHATING_CLANWON_LIST_CAP * 2);
		ChatList_menuPos[6].right = ChatList_menuPos[6].left + bx;
		ChatList_menuPos[6].bottom = ChatList_menuPos[6].top + by;

#ifdef USE_PROSTONTALE		//=========== ?????????
		bx = 13;
		by = 17;
#else
		bx = 13;
		by = 17;
#endif

		ChatList_menuPos[7].left = CHATING_CLANWON_LIST_X;
		ChatList_menuPos[7].top = CHATING_CLANWON_LIST_Y + (CHATING_CLANWON_LIST_CAP * 3);
		ChatList_menuPos[7].right = ChatList_menuPos[7].left + bx;
		ChatList_menuPos[7].bottom = ChatList_menuPos[7].top + by;

#ifdef USE_PROSTONTALE		//=========== ?????????
		bx = 13;
		by = 17;
#else
		bx = 13;
		by = 17;
#endif

		ChatList_menuPos[8].left = CHATING_CLANWON_LIST_X;
		ChatList_menuPos[8].top = CHATING_CLANWON_LIST_Y + (CHATING_CLANWON_LIST_CAP * 4);
		ChatList_menuPos[8].right = ChatList_menuPos[8].left + bx;
		ChatList_menuPos[8].bottom = ChatList_menuPos[8].top + by;

#ifdef USE_PROSTONTALE		//=========== ?????????
		bx = 13;
		by = 17;
#else
		bx = 13;
		by = 17;
#endif

		ChatList_menuPos[9].left = CHATING_CLANWON_LIST_X;
		ChatList_menuPos[9].top = CHATING_CLANWON_LIST_Y + (CHATING_CLANWON_LIST_CAP * 5);
		ChatList_menuPos[9].right = ChatList_menuPos[9].left + bx;
		ChatList_menuPos[9].bottom = ChatList_menuPos[9].top + by;

#ifdef USE_PROSTONTALE		//=========== ?????????
		bx = 13;
		by = 17;
#else
		bx = 13;
		by = 17;
#endif

		ChatList_menuPos[10].left = CHATING_CLANWON_LIST_X;
		ChatList_menuPos[10].top = CHATING_CLANWON_LIST_Y + (CHATING_CLANWON_LIST_CAP * 6);
		ChatList_menuPos[10].right = ChatList_menuPos[10].left + bx;
		ChatList_menuPos[10].bottom = ChatList_menuPos[10].top + by;

#ifdef USE_PROSTONTALE		//=========== ?????????
		bx = 13;
		by = 17;
#else
		bx = 13;
		by = 17;
#endif

		ChatList_menuPos[11].left = CHATING_CLANWON_LIST_X;
		ChatList_menuPos[11].top = CHATING_CLANWON_LIST_Y + (CHATING_CLANWON_LIST_CAP * 7);
		ChatList_menuPos[11].right = ChatList_menuPos[11].left + bx;
		ChatList_menuPos[11].bottom = ChatList_menuPos[11].top + by;

		//ktj ?????
		tscr_CL.Init(0);


		nMenuPos = 12;
		//================??? ?
		//if(nTotalClanWon> CHATING_DISPLAY_MAX)		
		if (nClanWon_Num > CHATING_DISPLAY_MAX)
		{

#ifdef USE_PROSTONTALE		//=========== ?????????
			bx = 16;
			by = 16;
#else
			bx = 16;
			by = 16;
#endif


			ChatList_menuPos[nMenuPos].left = CHATLIST_SBAR_X;
			ChatList_menuPos[nMenuPos].top = CHATLIST_SBAR_Y;
			ChatList_menuPos[nMenuPos].right = ChatList_menuPos[nMenuPos].left + 8;
			ChatList_menuPos[nMenuPos].bottom = ChatList_menuPos[nMenuPos].top + 160;
			//nClanWon[nIconPos] = 1;

			//ktj ?????
			tscr_CL.Init(1);
			tscr_CL.Init(ChatList_menuPos[nMenuPos].top,
				ChatList_menuPos[nMenuPos].top + 160,
				nClanWon_Num, CHATING_DISPLAY_MAX);


			scrIconPos.left = ChatList_menuPos[nMenuPos].left - 5;
			scrIconPos.top = ChatList_menuPos[nMenuPos].top + 2;
		}

		nMenuPos = 13;  //??
		//ChatList_menuPos[nMenuPos].left = 724;	
		//ChatList_menuPos[nMenuPos].top = CHATING_CLANWON_LIST_Y+ 3;
		//ChatList_menuPos[nMenuPos].right = ChatList_menuPos[nMenuPos].left + 56;
		//ChatList_menuPos[nMenuPos].bottom = ChatList_menuPos[nMenuPos].top + 17;

		nMenuPos += 1; //??
		ChatList_menuPos[nMenuPos].left = 665;
		ChatList_menuPos[nMenuPos].top = CHATLIST_BOX_Y + 10;

		ChatList_menuPos[nMenuPos].right = ChatList_menuPos[nMenuPos].left + 50;
		ChatList_menuPos[nMenuPos].bottom = ChatList_menuPos[nMenuPos].top + 23;

		nMenuPos += 1; //??
		ChatList_menuPos[nMenuPos].left = 603;
		ChatList_menuPos[nMenuPos].top = CHATLIST_BOX_Y + 10;
		ChatList_menuPos[nMenuPos].right = ChatList_menuPos[nMenuPos].left + 56;
		ChatList_menuPos[nMenuPos].bottom = ChatList_menuPos[nMenuPos].top + 23;



#ifdef USE_PROSTONTALE		//=========== ?????????
		bx = 64;
		by = 17;
#else
		bx = 64;
		by = 17;
#endif

		ChatList_menuPos[16].left = ChatList_menuPos[4].left + 35;
		ChatList_menuPos[16].top = ChatList_menuPos[4].top;
		ChatList_menuPos[16].right = ChatList_menuPos[16].left + bx;
		ChatList_menuPos[16].bottom = ChatList_menuPos[16].top + by;


		ChatList_menuPos[17].left = ChatList_menuPos[5].left + 35;
		ChatList_menuPos[17].top = ChatList_menuPos[5].top;
		ChatList_menuPos[17].right = ChatList_menuPos[17].left + bx;
		ChatList_menuPos[17].bottom = ChatList_menuPos[17].top + by;

		ChatList_menuPos[18].left = ChatList_menuPos[6].left + 35;
		ChatList_menuPos[18].top = ChatList_menuPos[6].top;
		ChatList_menuPos[18].right = ChatList_menuPos[18].left + bx;
		ChatList_menuPos[18].bottom = ChatList_menuPos[18].top + by;

		ChatList_menuPos[19].left = ChatList_menuPos[7].left + 35;
		ChatList_menuPos[19].top = ChatList_menuPos[7].top;
		ChatList_menuPos[19].right = ChatList_menuPos[19].left + bx;
		ChatList_menuPos[19].bottom = ChatList_menuPos[19].top + by;

		ChatList_menuPos[20].left = ChatList_menuPos[8].left + 35;
		ChatList_menuPos[20].top = ChatList_menuPos[8].top;
		ChatList_menuPos[20].right = ChatList_menuPos[20].left + bx;
		ChatList_menuPos[20].bottom = ChatList_menuPos[20].top + by;

		ChatList_menuPos[21].left = ChatList_menuPos[9].left + 35;
		ChatList_menuPos[21].top = ChatList_menuPos[9].top;
		ChatList_menuPos[21].right = ChatList_menuPos[21].left + bx;
		ChatList_menuPos[21].bottom = ChatList_menuPos[21].top + by;

		ChatList_menuPos[22].left = ChatList_menuPos[10].left + 35;
		ChatList_menuPos[22].top = ChatList_menuPos[10].top;
		ChatList_menuPos[22].right = ChatList_menuPos[22].left + bx;
		ChatList_menuPos[22].bottom = ChatList_menuPos[22].top + by;

		ChatList_menuPos[23].left = ChatList_menuPos[11].left + 35;
		ChatList_menuPos[23].top = ChatList_menuPos[11].top;
		ChatList_menuPos[23].right = ChatList_menuPos[23].left + bx;
		ChatList_menuPos[23].bottom = ChatList_menuPos[23].top + by;

		break;
	case CLAN_DISPLAY_OPEN: //?? ???
		SortClanWonList();
		ChatList_menuSu = 9;
		nScl_Bar = 0;

#ifdef USE_PROSTONTALE		//=========== ?????????
		bx = 20;
		by = 20;
#else		
		bx = 20;
		by = 20;
#endif

		ChatList_menuPos[0].left = BackStartPos.x + CHATICON_X;//174;		//yes
		ChatList_menuPos[0].top = BackStartPos.y + CHATICON_Y;//353;
		ChatList_menuPos[0].right = ChatList_menuPos[0].left + bx;
		ChatList_menuPos[0].bottom = ChatList_menuPos[0].top + by;

#ifdef USE_PROSTONTALE		//=========== ?????????
		bx = 20;
		by = 20;
#else		
		bx = 20;
		by = 20;
#endif

		ChatList_menuPos[1].left = BackStartPos.x + CHATCLOSE_X;//254		//no
		ChatList_menuPos[1].top = BackStartPos.y + CHATICON_Y; //353
		ChatList_menuPos[1].right = ChatList_menuPos[1].left + bx;
		ChatList_menuPos[1].bottom = ChatList_menuPos[1].top + by;

		//yes, no ??? ??
#ifdef USE_PROSTONTALE		//=========== ?????????
		bx = 68;
		by = 27;
#else		
		bx = 68;
		by = 27;
#endif

		ChatList_menuPos[2].left = BackStartPos.x + BUTTON1_BOX_X;//166;		//yes ??? ??
		ChatList_menuPos[2].top = BackStartPos.y + BUTTON1_BOX_Y;//348
		ChatList_menuPos[2].right = ChatList_menuPos[2].left + bx;
		ChatList_menuPos[2].bottom = ChatList_menuPos[2].top + by;

#ifdef USE_PROSTONTALE		//=========== ?????????
		bx = 68;
		by = 27;
#else		
		bx = 68;
		by = 27;;
#endif

		ChatList_menuPos[3].left = BackStartPos.x + BUTTON2_BOX_X;	//246	//no ??? ??
		ChatList_menuPos[3].top = BackStartPos.y + BUTTON2_BOX_Y;//348
		ChatList_menuPos[3].right = ChatList_menuPos[3].left + bx;
		ChatList_menuPos[3].bottom = ChatList_menuPos[3].top + by;

		//===============??? ?? ??=====================
#ifdef USE_PROSTONTALE		//=========== ?????????
		bx = 139;
		by = 30;
#else
		bx = 139;
		by = 30;
#endif

		ChatList_menuPos[4].left = BackStartPos.x + 10;	//246	//no ??? ??
		ChatList_menuPos[4].top = BackStartPos.y + 55;//348
		ChatList_menuPos[4].right = ChatList_menuPos[4].left + bx;
		ChatList_menuPos[4].bottom = ChatList_menuPos[4].top + by;


		//=================================================

#ifdef USE_PROSTONTALE		//=========== ?????????
		bx = 139;
		by = 30;
#else
		bx = 139;
		by = 30;
#endif

		ChatList_menuPos[4].left = BackStartPos.x + CHATING_CLANWON_LIST_X;	//246	//no ??? ??
		ChatList_menuPos[4].top = BackStartPos.y + CHATING_CLANWON_LIST_Y;//348
		ChatList_menuPos[4].right = ChatList_menuPos[4].left + bx;
		ChatList_menuPos[4].bottom = ChatList_menuPos[4].top + by;

#ifdef USE_PROSTONTALE		//=========== ?????????
		bx = 139;
		by = 30;
#else
		bx = 139;
		by = 30;
#endif

		ChatList_menuPos[5].left = BackStartPos.x + CHATING_CLANWON_LIST_X;
		ChatList_menuPos[5].top = BackStartPos.y + CHATING_CLANWON_LIST_Y + (CHATING_CLANWON_LIST_CAP * 1);
		ChatList_menuPos[5].right = ChatList_menuPos[5].left + bx;
		ChatList_menuPos[5].bottom = ChatList_menuPos[5].top + by;

#ifdef USE_PROSTONTALE		//=========== ?????????
		bx = 139;
		by = 30;
#else
		bx = 139;
		by = 30;
#endif

		ChatList_menuPos[6].left = BackStartPos.x + CHATING_CLANWON_LIST_X;
		ChatList_menuPos[6].top = BackStartPos.y + CHATING_CLANWON_LIST_Y + (CHATING_CLANWON_LIST_CAP * 2);
		ChatList_menuPos[6].right = ChatList_menuPos[6].left + bx;
		ChatList_menuPos[6].bottom = ChatList_menuPos[6].top + by;

#ifdef USE_PROSTONTALE		//=========== ?????????
		bx = 139;
		by = 30;
#else
		bx = 139;
		by = 30;
#endif

		ChatList_menuPos[7].left = BackStartPos.x + CHATING_CLANWON_LIST_X;
		ChatList_menuPos[7].top = BackStartPos.y + CHATING_CLANWON_LIST_Y + (CHATING_CLANWON_LIST_CAP * 3);
		ChatList_menuPos[7].right = ChatList_menuPos[7].left + bx;
		ChatList_menuPos[7].bottom = ChatList_menuPos[7].top + by;

		//ktj ?????
		tscr_CL.Init(0);


		nMenuPos = 8;
		//================??? ?
		//if(nTotalClanWon> CHATING_DISPLAY_MAX)		
		if (nClanWon_Num > CHATING_DISPLAY_MAX)
		{

#ifdef USE_PROSTONTALE		//=========== ?????????
			bx = 16;
			by = 16;
#else
			bx = 16;
			by = 16;
#endif


			ChatList_menuPos[nMenuPos].left = BackStartPos.x + CHATLIST_SBAR_X;
			ChatList_menuPos[nMenuPos].top = BackStartPos.y + CHATLIST_SBAR_Y;
			ChatList_menuPos[nMenuPos].right = ChatList_menuPos[nMenuPos].left + 8;
			ChatList_menuPos[nMenuPos].bottom = ChatList_menuPos[nMenuPos].top + 160;
			//nClanWon[nIconPos] = 1;

			//ktj ?????
			tscr_CL.Init(1);
			tscr_CL.Init(ChatList_menuPos[nMenuPos].top, //BackStartPos.y + SCROOBAR_TOP, 
				ChatList_menuPos[nMenuPos].top + 160,//256,
				//g_nClanIconNum, CLANHELPICON_DISPLAY_MAX);
				nClanWon_Num, CHATING_DISPLAY_MAX);


			scrIconPos.left = ChatList_menuPos[nMenuPos].left - 5;//BackStartPos.x + 275-5;//SCROLLBAR_LEFT-4;
			scrIconPos.top = ChatList_menuPos[nMenuPos].top + 2;//BackStartPos.y  + 87 -8;//(BackStartPos.y + SCROOBAR_TOP)-8;
		}

		break;

	}
}




void CLANEntity_chatting::Draw()
{
	int i = 0, nIconCount = 0;
	int nIconPos = 0;
	int nSaveTop = 0, nAdd = 0;
	int nStrLen = 0;
	char szDrawMenuMsg[2024];
	ZeroMemory(szDrawMenuMsg, sizeof(char) * 2024);
	int nMenuPos = 0;

#ifdef USE_PROSTONTALE		//=========== ?????????
#else





	int j = 0;

#endif


	//ChatListBoxX=0;
		//ChatListBoxY=0;
	switch (ChatList_CmenuN)
	{
	case CHATLIST_END:
	case CHATLIST_READDATA:
		DrawBox();
		break;
	case CLAN_DISPLAY_INFO:
		DrawBox();
		Draw_C_menuN();
		break;


	case CLAN_DISPLAY_OPEN:
		DrawBox();
		break;
	case CLAN_DISPLAY_CLOSE:
	case CLAN_CLOSE_ENDING:
		DrawBox();
		break;

	}

	/*
	if(vrunRuning == 1)
	{
		if(bMic==TRUE)
		{
			if(sinChatEnter)
			{
				dsDrawTexImage( hMicChatIcon, 7, 580-SubChatHeight , 32, 32, 255);
			}
			else
			{
				dsDrawTexImage( hMicChatIcon, 7, 580 , 32, 32, 255);
			}
		}
	}
	*/


}


void CLANEntity_chatting::InitClanWon()
{
	/*
	strcpy(szChatClanWon[0], "??");
	strcpy(szChatClanWon[1] , "?");
	strcpy(szChatClanWon[2], "??");
	strcpy(szChatClanWon[3] , "??");
	strcpy(szChatClanWon[4] , "??");
	strcpy(szChatClanWon[5] , "??");
	*/

	nTotalClanWon = 6;
	nRest_Num = nTotalClanWon - CHATING_DISPLAY_MAX;
}

void CLANEntity_chatting::SortClanWonList()
{

	int ZangL = strlen(cldata.ClanZang_Name);
	int ZangL2 = strlen(cldata.SubChip);
	BOOL bFlag = FALSE;
	int i;

	ZeroMemory(szChatClanWon, sizeof(szChatClanWon));

	if (cldata.myPosition == CLANCHIP)
	{
		if (cldata.SubChip[0] != 0)
		{
			if (cldata.SubChip[0] != 0)
				strcpy(szChatClanWon[0], cldata.SubChip);
			for (i = 0; i < nClanWon_Num; i++)
			{
				if (i > CLANWON_MAX) break;
				else
				{
					if (bFlag)
					{
						strcpy(szChatClanWon[i + 1], cldata.clanWon[i + 1]);
					}
					else
					{
						//????? ???.........
						if (((ZangL2 == lstrlen(cldata.clanWon[i])) && strcmp(cldata.clanWon[i], cldata.SubChip) == 0))
						{
							strcpy(szChatClanWon[i + 1], cldata.clanWon[i + 1]);
							bFlag = TRUE;
						}
						else
						{
							strcpy(szChatClanWon[i + 1], cldata.clanWon[i]);
						}

					}
				}
			}
		}
		else
		{
			memcpy(szChatClanWon, cldata.clanWon, sizeof(cldata.clanWon));
		}
	}

	//????? ????.
	int j = 0;
	if ((cldata.myPosition == CLANUSER) || (cldata.myPosition == CLAN_SUBCHIP))
	{
		i = 0;
		strcpy(szChatClanWon[0], cldata.ClanZang_Name);
		if (cldata.SubChip[0] != 0)
		{
			if (strcmp(cldata.ChaName, cldata.SubChip) != 0) {
				strcpy(szChatClanWon[1], cldata.SubChip);
				i = 1;
			}

		}
		while (i < nClanWon_Num)
		{

			//???? ????? ???.........
			if (((ZangL == lstrlen(cldata.clanWon[j])) && strcmp(cldata.clanWon[j], cldata.ClanZang_Name) == 0)
				|| ((ZangL2 == lstrlen(cldata.clanWon[j])) && strcmp(cldata.clanWon[j], cldata.SubChip) == 0))
			{
				j++;

			}
			else
			{
				++i;
				strcpy(szChatClanWon[i], cldata.clanWon[j]);
				j++;

			}

		}
	}

}

void CLANEntity_chatting::Load2()
{
#ifdef USE_PROSTONTALE		//=========== ?????????
	hChatListBoxLine =
		CreateTextureMaterial("image\\party\\party_win.tga", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);

	hChatListBoxTitle2 =
		CreateTextureMaterial("image\\party\\title-clan.tga", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);

	hChatMicOpt = CreateTextureMaterial("image\\party\\quest_win.tga", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);

#endif
}

void CLANEntity_chatting::Load()
{
#ifdef USE_PROSTONTALE		//=========== ?????????
	hChatListBoxLine =
		CreateTextureMaterial("image\\party\\party_win.tga", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);


	hChatListBoxTitle2 =
		CreateTextureMaterial("image\\party\\title-clan.tga", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);

	hChatListBoxTitle = LoadDibSurfaceOffscreen("image\\party\\title-clan.bmp");

	//hChatListBoxTitle = LoadDibSurfaceOffscreen("image\\party\\title-clan.bmp");	




	hButtonClose[0] = LoadDibSurfaceOffscreen("image\\party\\close_.bmp");
	hButtonClose[1] = LoadDibSurfaceOffscreen("image\\party\\ButtonExit.bmp");
	hClanWon[0] = LoadDibSurfaceOffscreen("image\\party\\party_man_0.bmp");
	hClanWon[1] = LoadDibSurfaceOffscreen("image\\party\\party_man_1.bmp");
	hChatIcon[0] = LoadDibSurfaceOffscreen("image\\party\\ButtonChatting_.bmp");
	hChatIcon[1] = LoadDibSurfaceOffscreen("image\\party\\ButtonChatting.bmp");
	hChatClanWon = LoadDibSurfaceOffscreen("image\\party\\chattng-icon-c.bmp");

	hMicOption[0] = LoadDibSurfaceOffscreen("image\\party\\ButtonMike_.bmp");
	hMicOption[1] = LoadDibSurfaceOffscreen("image\\party\\ButtonMike.bmp");
	hMicOptTitle = LoadDibSurfaceOffscreen("image\\party\\mike-title.bmp");
	hMicSortLine = LoadDibSurfaceOffscreen("image\\party\\mike-line.bmp");
	hMicONBack = LoadDibSurfaceOffscreen("image\\party\\mike-onoffbox.bmp");
	hMicONChk = LoadDibSurfaceOffscreen("image\\party\\mike-onoff.bmp");
	hMicVolBar = LoadDibSurfaceOffscreen("image\\party\\mike-updown.bmp");
	hMicVOLUPDOWN[0] = LoadDibSurfaceOffscreen("image\\party\\mike-btdown.bmp");
	hMicVOLUPDOWN[1] = LoadDibSurfaceOffscreen("image\\party\\mike-btup.bmp");
	hMicOptToolTip = LoadDibSurfaceOffscreen("image\\party\\ButtonInfo-clan2.bmp");
	hChatMicOpt = CreateTextureMaterial("image\\party\\quest_win.tga", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);

	//???
	hClanChatToolTip = LoadDibSurfaceOffscreen("image\\party\\ButtonInfo-chatting.bmp");
	hBtnCloseToolTip = LoadDibSurfaceOffscreen("image\\party\\ButtonInfo-5.bmp");

#else
	hChatListBoxLine = (HBITMAP)LoadImage(NULL, "image\\party\\party_win.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	hChatListBoxTitle = (HBITMAP)LoadImage(NULL, "image\\party\\title-clan.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	hChatIcon[0] = (HBITMAP)LoadImage(NULL, "image\\party\\ButtonChatting_.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	hChatIcon[1] = (HBITMAP)LoadImage(NULL, "image\\party\\ButtonChatting.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	hButtonClose[0] = (HBITMAP)LoadImage(NULL, "image\\party\\close_.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	hButtonClose[1] = (HBITMAP)LoadImage(NULL, "image\\party\\ButtonExit.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	hClanWon[0] = (HBITMAP)LoadImage(NULL, "image\\party\\party_man_0.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	hClanWon[1] = (HBITMAP)LoadImage(NULL, "image\\party\\party_man_1.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	hChatListParty = (HBITMAP)LoadImage(NULL, "image\\party\\title-Party.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	hChatListFriend = (HBITMAP)LoadImage(NULL, "image\\party\\title-chatting1.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	hChatClanWon = (HBITMAP)LoadImage(NULL, "image\\party\\chattng-icon-c.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	hBtnCloseToolTip = (HBITMAP)LoadImage(NULL, "image\\party\\ButtonInfo-5.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);

#endif
}

void CLANEntity_chatting::DisplayInfo()
{
#ifdef USE_PROSTONTALE		//=========== ?????????

#else
	BITMAP   bit;
	HDC hdc = GetDC(g_hwnd);
	HDC sorDC = CreateCompatibleDC(hdc);
	HDC destdc = CreateCompatibleDC(hdc);

	SelectObject(destdc, Dback.hb);		//off?????.	



	SelectObject(sorDC, hChatListBoxLine);
	GetObject(hChatListBoxLine, sizeof(BITMAP), &bit);
	//BitBlt(destdc,x,y+9,bit.bmWidth,bit.bmHeight,sorDC,0,0,SRCCOPY);
	StretchBlt(destdc, OpenBuf_x[cnt], 94 + 9, AddSize, bit.bmHeight, sorDC, 0, 0, AddSize, bit.bmHeight, SRCCOPY);

	SelectObject(sorDC, hChatListBoxTitle);
	GetObject(hChatListBoxTitle, sizeof(BITMAP), &bit);
	//BitBlt(destdc,x,y,bit.bmWidth,bit.bmHeight,sorDC,0,0,SRCCOPY);
	StretchBlt(destdc, OpenBuf_x[cnt], 94, AddSize, bit.bmHeight, sorDC, 0, 0, AddSize, bit.bmHeight, SRCCOPY);

	DeleteDC(sorDC);
	DeleteDC(destdc);

	ReleaseDC(g_hwnd, hdc);
	Draw();

#endif
}

void CLANEntity_chatting::ChatListUserData(char* id, char* gserver, char* chaid)
{
	strcpy(ClanChatList.szUserID, id);
	strcpy(ClanChatList.szChaName, chaid);
	strcpy(ClanChatList.szGameServer, gserver);
}

void CLANEntity_chatting::ChatListParsingIsClanMember(char* data)
{

	//chk_readStrBuf("CName=", data, cldata.name);
	//chk_readStrBuf("CNote=", data, cldata.explanation);	
	chk_readStrBuf("CZang=", data, ClanChatList.szClanZang_Name);
	//chk_readStrBuf("CStats=", data, cldata.stats);	
	//chk_readStrBuf("CSec=", data, cldata.sec);
	//ParsingData("CRegiD=", data, cldata.szRegiD);
	//ParsingData("CLimitD=", data, cldata.limitD);
	//chk_readStrBuf("CRegiD=", data, cldata.szRegiD);
	//chk_readStrBuf("CLimitD=", data, cldata.limitD);
	//chk_readStrBuf("CDelActive=", data, cldata.DelActive);
	//chk_readStrBuf("CIMG=", data, cldata.ClanMark);

}


void CLANEntity_chatting::DrawBox()
{

#ifdef USE_PROSTONTALE		//=========== ?????????	

	dsDrawTexImage(hChatListBoxTitle2,
		ChatListBoxX, CHATLIST_BOX_Y, 256, 32, 255);

	dsDrawTexImage(hChatListBoxLine,
		ChatListBoxX, CHATLIST_BOX_Y + 8, 256, 256, 255);

	if (g_nMicBtn == 1)
		dsDrawTexImage(hChatMicOpt, ChatListBoxX - 198, CHATLIST_BOX_Y + 23, 256, 256, 255);

#else
	BITMAP   bit;
	HDC hdc = GetDC(g_hwnd);
	HDC sorDC = CreateCompatibleDC(hdc);
	HDC destdc = CreateCompatibleDC(hdc);

	SelectObject(destdc, Dback.hb);		//off?????.	


	SelectObject(sorDC, hChatListBoxLine);
	GetObject(hChatListBoxLine, sizeof(BITMAP), &bit);

	StretchBlt(destdc, ChatListBoxX, 94 + 9, 256, bit.bmHeight, sorDC, 0, 0, 256, bit.bmHeight, SRCCOPY);

	SelectObject(sorDC, hChatListBoxTitle);
	GetObject(hChatListBoxTitle, sizeof(BITMAP), &bit);

	StretchBlt(destdc, ChatListBoxX, 94, 256, bit.bmHeight, sorDC, 0, 0, 256, bit.bmHeight, SRCCOPY);

	if (cnt < 6)
	{
		cnt += 1;
		AddSize += 50;
	}

	DeleteDC(sorDC);
	DeleteDC(destdc);

	ReleaseDC(g_hwnd, hdc);

#endif	
}









int cnt__00 = 0;
void CLANEntity_chatting::Draw_C_menuN()
{
	SortClanWonList();
	int nMenuPos, i;
	char szClanWon[40];

	if (Chatting_button > 0)
		DrawSprite(ChatList_menuPos[0].left, ChatList_menuPos[0].top, hChatIcon[1], 0, 0, 20, 20, 1);
	else DrawSprite(ChatList_menuPos[0].left, ChatList_menuPos[0].top, hChatIcon[0], 0, 0, 20, 20, 1);

	if (menuMouseOver[0] > 0)
	{
		DrawSprite(ChatList_menuPos[0].left, ChatList_menuPos[0].top, hChatIcon[1], 0, 0, 20, 20, 1);
		DrawSprite(ChatList_menuPos[0].left - 28, ChatList_menuPos[0].top - 23, hClanChatToolTip, 0, 0, 76, 27, 1);
	}

	if (menuMouseOver[1] > 0)
	{
		DrawSprite(ChatList_menuPos[1].left, ChatList_menuPos[1].top, hButtonClose[1], 0, 0, 20, 20, 1);
		DrawSprite(ChatList_menuPos[1].left - 28, ChatList_menuPos[1].top - 23, hBtnCloseToolTip, 0, 0, 76, 27, 1);
	}
	else DrawSprite(ChatList_menuPos[1].left, ChatList_menuPos[1].top, hButtonClose[0], 0, 0, 20, 20, 1);

	nMenuPos = 4;

	if (vrunRuning == 1)
	{
		if (menuMouseOver[24] > 0)
		{
			DrawSprite(ChatList_menuPos[24].left, ChatList_menuPos[24].top, hMicOption[1], 0, 0, 20, 20, 1);
			DrawSprite(ChatList_menuPos[24].left - 28, ChatList_menuPos[24].top - 23, hMicOptToolTip, 0, 0, 76, 27, 1);
		}
		else DrawSprite(ChatList_menuPos[24].left, ChatList_menuPos[24].top, hMicOption[0], 0, 0, 20, 20, 1);
	}

	if (g_nMicBtn == 1)
	{
		
		DrawSprite(446, 196, hMicOptTitle, 0, 0, 17, 23, 1);

	
		DrawSprite(419, 225, hMicSortLine, 0, 0, 174, 3, 1);

		DrawSprite(511, 249, hMicONBack, 0, 0, 14, 14, 1);
		DrawSprite(559, 249, hMicONBack, 0, 0, 14, 14, 1);

		if (micInit != 0)
		{
			
			DrawSprite(438, 300, hMicVolBar, 0, 0, 135, 16, 1);
		}

		
		DrawSprite(ChatList_menuPos[24].left, ChatList_menuPos[24].top, hMicOption[1], 0, 0, 20, 20, 1);

		
		if (menuMouseOver[25] == 1)
		{
			DrawSprite(ChatList_menuPos[25].left, ChatList_menuPos[25].top, hButtonClose[1], 0, 0, 20, 20, 1);
			DrawSprite(ChatList_menuPos[25].left - 28, ChatList_menuPos[25].top - 23, hBtnCloseToolTip, 0, 0, 76, 27, 1);
		}
		else DrawSprite(ChatList_menuPos[25].left, ChatList_menuPos[25].top, hButtonClose[0], 0, 0, 20, 20, 1);

		if (bMic == TRUE)
		{
			DrawSprite(ChatList_menuPos[26].left + 2, ChatList_menuPos[26].top + 2, hMicONChk, 0, 0, 10, 10, 1);
		}
		else
			DrawSprite(ChatList_menuPos[27].left + 2, ChatList_menuPos[27].top + 2, hMicONChk, 0, 0, 10, 10, 1);

		if (micInit != 0)
		{
			//??? ?? up
			if (menuMouseOver[28] == 1)
				DrawSprite(ChatList_menuPos[28].left, ChatList_menuPos[28].top, hMicVOLUPDOWN[0], 0, 0, 16, 16, 1);

			//??? ?? down
			if (menuMouseOver[29] == 1)
				DrawSprite(ChatList_menuPos[29].left, ChatList_menuPos[29].top, hMicVOLUPDOWN[1], 0, 0, 16, 16, 1);

			DrawSprite(455 + nVol, 304, hMicONChk, 0, 0, 10, 10, 1);
		}


		
		//Draw_C_TextPark(parkTextVO , 470, 200, 154, 236, 252, 2);

		//Draw_C_TextPark(parkTextMIC , 438, 251, 255, 255, 255, 0);

		//Draw_C_TextPark(parkTextMicON , 492, 251, 255, 255, 255, 0);
		//Draw_C_TextPark(parkTextMicOFF , 539, 251, 255, 255, 255, 0);

		if (micInit != 0)
		{
			//Draw_C_TextPark(parkTextVol, 438, 283, 255, 255, 255, 0);

			//Draw_C_TextPark(parkTextVolLow, 438, 320, 255, 255, 255, 0);

			//Draw_C_TextPark(parkTextVolHigh, 560, 320, 255, 255, 255, 0);
		}
		else
		{
			//Draw_C_TextPark(parkTextVolErr1, 438, 283, 255, 255, 255, 0);
			//Draw_C_TextPark(parkTextVolErr2, 438, 303, 255, 255, 255, 0);
		}

		extern int vrunRuning;
		if (vrunRuning == 1)
		{
			int cnt = 0;

			extern char voiceInfoStr[256];
			if (voiceInfoStr[0] != 0)
			{
				Draw_C_TextPark(voiceInfoStr, 438, 360, 255, 255, 255, 0);
			}
		}
	}

	nMenuPos = 4;

	if (cldata.myPosition == CLANCHIP)
	{
		for (i = 0; i < CHATING_DISPLAY_MAX; i++)
		{
			if (i == nClanWon_Num) break;
			if (ClanChatList.clanWon[i + nScl_Bar])
			{

				lstrcpy(szClanWon, szChatClanWon[i + nScl_Bar]);

				if ((i + nScl_Bar) == (cN_PressfDBL - 4))
				{
					DrawSprite(ChatList_menuPos[nMenuPos].left, ChatList_menuPos[nMenuPos].top, hChatClanWon, 0, 0, 16, 16, 1);
					Draw_C_Text2(szClanWon, ChatList_menuPos[nMenuPos].left + 35, ChatList_menuPos[nMenuPos].top + 3);
				}
				else if ((i + nScl_Bar) == (cN_Pressf - 4))
				{
					if ((cldata.SubChip[0] != 0) && (lstrcmp(szChatClanWon[i + nScl_Bar], cldata.SubChip) == 0))
						DrawSprite(ChatList_menuPos[nMenuPos].left, ChatList_menuPos[nMenuPos].top, hSubChip, 0, 0, 13, 17, 1);
					else
						DrawSprite(ChatList_menuPos[nMenuPos].left, ChatList_menuPos[nMenuPos].top, hClanWon[0], 0, 0, 13, 17, 1);

					Draw_C_Text3(szClanWon, ChatList_menuPos[nMenuPos].left + 35, ChatList_menuPos[nMenuPos].top + 3);
				}


				else {



					
					
						if ((cldata.SubChip[0] != 0) && (strcmp(szChatClanWon[i + nScl_Bar], cldata.SubChip) == 0))
						{
							DrawSprite(ChatList_menuPos[nMenuPos].left, ChatList_menuPos[nMenuPos].top, hSubChip, 0, 0, 13, 17, 1);

							Draw_C_Text(szClanWon, ChatList_menuPos[nMenuPos].left + 35, ChatList_menuPos[nMenuPos].top + 3);
						}
						else
						{


							
							DrawSprite(ChatList_menuPos[nMenuPos].left, ChatList_menuPos[nMenuPos].top, hClanWon[0], 0, 0, 13, 17, 1);
							Draw_C_Text(szClanWon, ChatList_menuPos[nMenuPos].left + 35, ChatList_menuPos[nMenuPos].top + 3);


						}

				}

				nMenuPos += 1;
			}
		}
	}

	if ((cldata.myPosition == CLANUSER) || (cldata.myPosition == CLAN_SUBCHIP))
	{
		for (i = 0; i < CHATING_DISPLAY_MAX; i++)
		{
			if (i == nClanWon_Num) break;
			if (szChatClanWon[i + nScl_Bar])
			{
				lstrcpy(szClanWon, szChatClanWon[i + nScl_Bar]);

				if ((i + nScl_Bar) == (cN_PressfDBL - 4))
				{
					DrawSprite(ChatList_menuPos[nMenuPos].left, ChatList_menuPos[nMenuPos].top, hChatClanWon, 0, 0, 16, 16, 1);
					Draw_C_Text2(szClanWon, ChatList_menuPos[nMenuPos].left + 35, ChatList_menuPos[nMenuPos].top + 3);
				}

				else if ((i + nScl_Bar) == (cN_Pressf - 4))
				{
					if (lstrcmp(szChatClanWon[i + nScl_Bar], cldata.ClanZang_Name) == 0)
						DrawSprite(ChatList_menuPos[nMenuPos].left, ChatList_menuPos[nMenuPos].top, cldata.hClanMark16, 0, 0, 16, 16, 1);
					else if ((cldata.SubChip[0] != 0) && (lstrcmp(szChatClanWon[i + nScl_Bar], cldata.SubChip) == 0))
						DrawSprite(ChatList_menuPos[nMenuPos].left, ChatList_menuPos[nMenuPos].top, hSubChip, 0, 0, 13, 17, 1);
					else
						DrawSprite(ChatList_menuPos[nMenuPos].left, ChatList_menuPos[nMenuPos].top, hClanWon[0], 0, 0, 13, 17, 1);

					Draw_C_Text3(szClanWon, ChatList_menuPos[nMenuPos].left + 35, ChatList_menuPos[nMenuPos].top + 3);
				}

				else
				{

					if (lstrcmp(szChatClanWon[i + nScl_Bar], cldata.ClanZang_Name) == 0)
						DrawSprite(ChatList_menuPos[nMenuPos].left, ChatList_menuPos[nMenuPos].top, cldata.hClanMark16, 0, 0, 16, 16, 1);
					else if ((cldata.SubChip[0] != 0) && (lstrcmp(szChatClanWon[i + nScl_Bar], cldata.SubChip) == 0))
						DrawSprite(ChatList_menuPos[nMenuPos].left, ChatList_menuPos[nMenuPos].top, hSubChip, 0, 0, 13, 17, 1);
					else
					{
						DrawSprite(ChatList_menuPos[nMenuPos].left, ChatList_menuPos[nMenuPos].top, hClanWon[0], 0, 0, 13, 17, 1);
						Draw_C_Text3(szClanWon, ChatList_menuPos[nMenuPos].left + 35, ChatList_menuPos[nMenuPos].top + 3);
					}
					Draw_C_Text(szClanWon, ChatList_menuPos[nMenuPos].left + 35, ChatList_menuPos[nMenuPos].top + 3);
				}
				nMenuPos += 1;
			}
		}
	}

	nMenuPos = 12;

	if (nClanWon_Num > CHATING_DISPLAY_MAX)
	{
		DrawSprite(ChatList_menuPos[nMenuPos].left, ChatList_menuPos[nMenuPos].top, hScl_Bar, 0, 0, 8, 160, 1);

		dsDrawTexImage(hScl_icon_tj, scrIconPos.left, scrIconPos.top, 16, 16, 255);
	}

	char buf[256];
	wsprintf(buf, "[%s]", cldata.name);

	Draw_C_Text3(buf, ChatListBoxX + 115, CHATLIST_BOX_Y + 38);
}

void CLANEntity_chatting::InitClanChatList()
{
	OCcnt = 0;
	ChatListBoxX = 800;
	ChatListBoxY = 94;

	cnt = 0;
	AddSize = 0;
}

void CLANEntity_chatting::MoveClose()
{
	ChatList_CmenuN = CLAN_DISPLAY_CLOSE;
}

void CLANEntity_chatting::NoScroll()
{
	OCcnt = 28;
	ChatListBoxX = OpenBuf_x[OCcnt];
	OCcnt += 1;

	bOpenChatList = TRUE;
}


/*///////////////////////////////////////////////////////////////////////////
: ???? :
: ? ? ? : ???? ?? ?? ?? ????.
: ? ? ? :
: ???? :
///////////////////////////////////////////////////////////////////////////*/
int CLANEntity_chatting::chkMenu(int x, int y, RECT* r)
{
	if (r->left <= x && x <= r->right)
		if (r->top <= y && y <= r->bottom)
			return 1;
	return 0;			//???? ????.
}
int CLANEntity_chatting::chkeckMenuN()
{
	int i;

	for (i = 0; i < ChatList_menuSu; i++) {
		if (chkMenu(pCursorPos.x, pCursorPos.y, &ChatList_menuPos[i])) {
			return i;
		}
	}
	return -1;
}


//===========================================
void CLANEntity_chatting::DoubleClick(int i)
{
	if (banisF[(i - 4) + nScl_Bar] == 1)
		banisF[(i - 4) + nScl_Bar] = 2;
	else if (banisF[(i - 4) + nScl_Bar] == 2) banisF[(i - 4) + nScl_Bar] = 0;
	else
	{
		banisF[(i - 4) + nScl_Bar] = 2;
	}
}