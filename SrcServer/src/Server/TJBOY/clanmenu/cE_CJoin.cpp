
#define CE_CJOIN_CPP
#include <windows.h>
#include <stdio.h>
#include <tchar.h>
#include <math.h>

#include "tjclanDEF.h"

#ifdef USE_PROSTONTALE		

#include "..\\..\\sinbaram\\SinLinkHeader.h"

#include "..\\..\\language.h"

#endif

#include "tjclan.h"
#include "cE_report.h"
#include "cE_CJoin.h"
#include "cE_CViewClanInfo.h"
#include "..\\isaocheck\\auth.h"
#include "..\\isaocheck\\isaocheck.h"



CLANEntity_JOIN::CLANEntity_JOIN()
{
	nJoinAnswer = 0;
	ZeroMemory(szTemp, sizeof(szTemp));
	ZeroMemory(szTemp1, sizeof(szTemp1));
}

CLANEntity_JOIN::~CLANEntity_JOIN()
{
}

int CLANEntity_JOIN::Init(int Life)
{
	life = Life;
	ZeroMemory(szUserJoin, sizeof(szUserJoin));
	return 1;
}

int CLANEntity_JOIN::Clear()
{
	return 1;
}

void CLANEntity_JOIN::Main()
{
	int i;

	switch(C_menuN)
	{
		case CLAN_CLANWONOVER:
		i = chkeckMenuN();
		switch(i)
		{
			case 0:
			menuMouseOver[0] = 1;
			break;
			default:
			memset(menuMouseOver, -1, sizeof(int) * 30);
			break;
		}
		
		{
			
			switch(i)
			{
				case 0:
				C_menuN = CLAN_AllEnd;



				C_menuN2 = -1;
				CLAN_ERROR_ret = -1;
				break;
				default:
				break;

			}
		}
		break;
		case CLAN_JOIN_before:

		switch(C_menuN2)
		{
			case 0:
			ANSdata.ret_val = -1;

			WebDB.Resume();
			WebDB.isClanMember(cldata.szID, cldata.gserver, cldata.ChaName);
			C_menuN2 = 1;
		#ifdef CLAN_DEBUG
			DebugMessage("CLAN_JOIN_before���� WebDB.isClanMember(���̵� : %s,���Ӽ��� : %s,ĳ�����̸� : %s)", cldata.szID, cldata.gserver, cldata.ChaName);
		#endif
			break;
			case 1:
			switch(ANSdata.ret_val)
			{
				case 100:

				WebDB.Suspend();

				C_menuN = CLAN_JOIN_After;
				menuInit(C_menuN);
				joinAnswer = 100;

				C_menuN2 = 0;
			#ifdef CLAN_DEBUG
				DebugMessage("CLAN_JOIN_before���� �����ڵ� 100");
			#endif
				break;

				case 1:
				case 2:
				case 5:
				case 101:
				case 103:
				case 104:
				WebDB.Suspend();
				C_menuN = CLAN_JOIN_After;
				menuInit(C_menuN);
				joinAnswer = 101;

				C_menuN2 = 0;
			#ifdef CLAN_DEBUG
				DebugMessage("CLAN_JOIN_before���� Ŭ�� ���ԺҰ�(%d)", ANSdata.ret_val);
			#endif

				break;
				case 4:
				case 3:
				case 0:
				case 105:
				WebDB.Suspend();
				C_menuN = CLAN_JOIN;

				menuInit(C_menuN);

				C_menuN2 = 0;
			#ifdef CLAN_DEBUG
				DebugMessage("CLAN_JOIN_before���� Ŭ�����԰���(%d)", ANSdata.ret_val);
			#endif

				break;
				case ISAO_ERR_TCP_CONNECT:
				WebDB.Suspend();

				C_menuN = CLAN_ERROR;
				wsprintf(szErrorMsg, "%s (55)", clanszError_Msg.szMsg);
				cClanReport.InitMsg(szErrorMsg);
				cClanReport.menuInit(C_menuN, clanszError_Msg.pos.x, clanszError_Msg.pos.y);
			#ifdef CLAN_DEBUG
				DebugMessage("CLAN_JOIN_before���� ������ �����Ҽ� ����(%d)", ANSdata.ret_val);
			#endif
				break;
				default:
				if(ANSdata.ret_val != -1)
				{
					WebDB.Suspend();

					C_menuN = CLAN_ERROR;
					wsprintf(szErrorMsg, "%s (56)", clanszError_Msg.szMsg);
					cClanReport.InitMsg(szErrorMsg);
					cClanReport.menuInit(C_menuN, clanszError_Msg.pos.x, clanszError_Msg.pos.y);

					C_menuN2 = 0;
				#ifdef CLAN_DEBUG
					DebugMessage("CLAN_JOIN_before���� ����Ʈ����(%d)", ANSdata.ret_val);
				#endif
				}
				break;
			}
			break;
		}
		break;

		case CLANUSER_JOIN:

		i = chkeckMenuN();
		switch(i)
		{
			case 0:
			menuMouseOver[0] = 1;
			break;
			default:
			memset(menuMouseOver, -1, sizeof(int) * 30);
			break;
		}
		
		{
			
			i = i;
			switch(i)
			{
				case 0:
				C_menuN = CLAN_AllEnd;



				C_menuN2 = -1;
				CLAN_ERROR_ret = -1;
				break;
				default:
				i = i;
				break;

			}
		}
		break;


		case CLAN_JOIN:
		i = chkeckMenuN();
		memset(menuMouseOver, -1, sizeof(int) * 30);
		switch(i)
		{
			case 0:
			menuMouseOver[0] = 1;
			break;
			case 1:
			menuMouseOver[1] = 1;
			break;
			default:
			memset(menuMouseOver, -1, sizeof(int) * 30);
			break;
		}
		
		{
			
			switch(i)
			{
				case 0:

				wsprintf(szUserJoin, clanClanJoinMsg.szMsg, cldata.szJoinClanName, cldata.szJoinClanChipName, cldata.ChaName);

				CheckMsgPos(&clanClanJoinMsg, BOX_MAX_WIDTH, 0);
				C_menuN = CLANUSER_JOIN;

				menuInit(C_menuN);
				CLAN_ERROR_ret = CLAN_JOIN_After;
				nJoinAnswer = 1;



				break;
				case 1:
				nJoinAnswer = 0;
				C_menuN = CLAN_AllEnd;
				break;

				default:
				break;
			}
		}
		break;

		case CLAN_JOIN_After:
		C_menuN = CLAN_AllEnd;
		break;


		case CLAN_IS_CHECK_MEMBER_END:
		C_menuN = CLAN_AllEnd;
		break;


		case CLAN_IS_CHECK_MEMBER:
		switch(C_menuN2)
		{
			case 0:
			ANSdata.ret_val = -1;
			WebDB.Resume();
			WebDB.isCheckClanMember(cldata.gserver, cldata.TargetChar->smCharInfo.szName);
			C_menuN2 = 1;
			break;
			case 1:
			if(ANSdata.ret_val != -1)
			{

				if(ANSdata.ret_val == 0)
				{
					WebDB.Suspend();


					CLANMSG clanMsg;
					wsprintf(clanMsg.szMsg, "%s", "Error");
					clanMsg.pos.x = 0;
					clanMsg.pos.y = 0;
					CheckMsgPos(&clanMsg, BOX_MAX_WIDTH, 0);

					C_menuN = CLAN_ERROR;

					char TempBufferMsg[256];
					wsprintf(TempBufferMsg, ClanIs4DayCheckMsg.szMsg, cldata.TargetChar->smCharInfo.szName);
					cClanReport.InitMsg(TempBufferMsg);
					cClanReport.menuInit(C_menuN, clanszError_Msg.pos.x, clanszError_Msg.pos.y);

					CLAN_ERROR_ret = CLAN_IS_CHECK_MEMBER_END;

				}
				else if(ANSdata.ret_val == 1)
				{
					WebDB.Suspend();


					C_menuN = CLAN_IS_CHECK_MEMBER_END;
					C_menuN2 = 0;
					OpenFlag = 1;
					joinAnswer = 0;
					ClanCharMove = 1;

				}
				else
				{
					WebDB.Suspend();


					CLANMSG clanMsg;
					wsprintf(clanMsg.szMsg, "%s", "Error");
					clanMsg.pos.x = 0;
					clanMsg.pos.y = 0;
					CheckMsgPos(&clanMsg, BOX_MAX_WIDTH, 0);

					C_menuN = CLAN_ERROR;

					char TempBufferMsg[256];

				#ifdef	_LANGUAGE_JAPANESE
					wsprintf(TempBufferMsg, "�N�����E��\n4���o�߂�?�F�b�N��Error");
				#else
					wsprintf(TempBufferMsg, "Ŭ��Ż��\n4�ϰ��üũ��Error");
				#endif
					cClanReport.InitMsg(TempBufferMsg);
					cClanReport.menuInit(C_menuN, clanszError_Msg.pos.x, clanszError_Msg.pos.y);

					CLAN_ERROR_ret = CLAN_IS_CHECK_MEMBER_END;
				}
			}
		}
		break;

		case CLAN_JOIN_chip:
		switch(C_menuN2)
		{
			case 0:
			ANSdata.ret_val = -1;

			WebDB.Resume();
		#ifdef USE_PROSTONTALE		
			WebDB.joinClanMember(cldata.szID, cldata.gserver, cldata.ChaName,

								 cldata.name, cldata.clanJoinCharID, cldata.clanJoinID, sinChar->Level, cldata.clanJoinJob, cldata.clanJoinLevel, cldata.isSubChip);
		#ifdef CLAN_DEBUG
			DebugMessage("CLAN_JOIN_chip���� WebDB.joinClanMember(���̵� : %s,���Ӽ��� : %s,Ŭ���� : %s,Ŭ���̸� : %s, ������ ĳ���� : %s,  ������ ���̵� : %s, ���� : %d, �� : %d", cldata.szID, cldata.gserver, cldata.ChaName, cldata.name, cldata.clanJoinCharID, cldata.clanJoinID, sinChar->Level, sinChar->JOB_CODE);
		#endif

		#else
			WebDB.joinClanMember(cldata.szID, cldata.gserver, cldata.ChaName,

								 cldata.name, cldata.clanJoinCharID, cldata.clanJoinID, 70, 1, 50, cldata.isSubChip);
		#endif




			C_menuN2 = 1;

			break;
			case 1:
			if(ANSdata.ret_val != -1)
			{
				ANSdata.ret_val = ANSdata.ret_val;

			}

			switch(ANSdata.ret_val)
			{

				case 0:
				WebDB.Suspend();


				C_menuN = CLAN_ERROR;
				menuInit(C_menuN);
				wsprintf(szErrorMsg, "%s (64)", clanszError_Msg.szMsg);
				cClanReport.InitMsg(szErrorMsg);
				cClanReport.menuInit(C_menuN, clanszError_Msg.pos.x, clanszError_Msg.pos.y);
				CLAN_ERROR_ret = CLAN_JOIN_After;

				C_menuN2 = 0;
			#ifdef CLAN_DEBUG
				DebugMessage("CLAN_JOIN_chip���� Ʈ����ǿ���");
			#endif
				break;
				case 1:
				WebDB.Suspend();
				C_menuN = CLAN_JOIN_chip_YES;
				menuInit(C_menuN);

				AddClanWon();

				void SetClanWon();



				C_menuN2 = 0;
			#ifdef CLAN_DEBUG
				DebugMessage("CLAN_JOIN_chip���� ���Լ���");
			#endif
				break;
				case 2:
				WebDB.Suspend();



				C_menuN = CLAN_ERROR;
				wsprintf(szErrorMsg, "%s (49)", clanszError_Msg.szMsg);
				cClanReport.InitMsg(szErrorMsg);
				cClanReport.menuInit(C_menuN, clanszError_Msg.pos.x, clanszError_Msg.pos.y);
				CLAN_ERROR_ret = CLAN_JOIN_After;

				C_menuN2 = 0;
			#ifdef CLAN_DEBUG
				DebugMessage("CLAN_JOIN_chip���� ���� ���Խ�Ű���� Ŭ������ �̹� �ٸ� Ŭ���� ���������� ���(�ڱ� Ŭ������)");
			#endif
				break;
				case 3:
				WebDB.Suspend();


				C_menuN = CLAN_ERROR;
				wsprintf(szErrorMsg, "%s (50)", clanszError_Msg.szMsg);
				cClanReport.InitMsg(szErrorMsg);
				cClanReport.menuInit(C_menuN, clanszError_Msg.pos.x, clanszError_Msg.pos.y);
				CLAN_ERROR_ret = CLAN_JOIN_After;

				C_menuN2 = 0;
			#ifdef CLAN_DEBUG
				DebugMessage("CLAN_JOIN_chip���� Ŭ���� �������� �ʰų� Ŭ�� ���� �ƴѰ��");
			#endif
				break;
				case 4:
				WebDB.Suspend();
				C_menuN = CLAN_CLANWONOVER;
				cClanJoin.menuInit(C_menuN);





				CLAN_ERROR_ret = CLAN_JOIN_After;

				C_menuN2 = 0;
			#ifdef CLAN_DEBUG
				DebugMessage("CLAN_JOIN_chip���� Ŭ�� ��� �����÷ο�");
			#endif
				break;
				case 100:
				WebDB.Suspend();
				C_menuN = CLAN_ERROR;
				wsprintf(szErrorMsg, "%s (52)", clanszError_Msg.szMsg);
				cClanReport.InitMsg(szErrorMsg);
				cClanReport.menuInit(C_menuN, clanszError_Msg.pos.x, clanszError_Msg.pos.y);
				CLAN_ERROR_ret = CLAN_JOIN_After;

				C_menuN2 = 0;
			#ifdef CLAN_DEBUG
				DebugMessage("CLAN_JOIN_chip���� �����ڵ� 100");
			#endif

				break;
				case ISAO_ERR_TCP_CONNECT:
				WebDB.Suspend();
				C_menuN = CLAN_ERROR;
				wsprintf(szErrorMsg, "%s (53)", clanszError_Msg.szMsg);
				cClanReport.InitMsg(szErrorMsg);
				cClanReport.menuInit(C_menuN, clanszError_Msg.pos.x, clanszError_Msg.pos.y);
			#ifdef CLAN_DEBUG
				DebugMessage("CLAN_JOIN_chip���� ������ ���� �ȵ�");
			#endif
				break;



				default:
				if(ANSdata.ret_val != -1)
				{
					WebDB.Suspend();


					C_menuN = CLAN_ERROR;
					wsprintf(szErrorMsg, "%s (54)", clanszError_Msg.szMsg);
					cClanReport.InitMsg(szErrorMsg);
					cClanReport.menuInit(C_menuN, clanszError_Msg.pos.x, clanszError_Msg.pos.y);
					CLAN_ERROR_ret = CLAN_JOIN_After;

					C_menuN2 = 0;
				#ifdef CLAN_DEBUG
					DebugMessage("CLAN_JOIN_chip���� ����Ʈ����");
				#endif
				}
				break;
			}
			break;
		}
		break;

		case CLAN_JOIN_chip_NO:
		wsprintf(szTemp, clanClanJoinCancelMsg.szMsg, cldata.clanJoinCharID);



		strcpy(szTemp1, clanszError_Msg.szMsg);
		strcpy(clanszError_Msg.szMsg, szTemp);


		CheckMsgPos(&clanszError_Msg, BOX_MAX_WIDTH, 0);

		C_menuN = CLAN_ERROR;
		cClanReport.InitMsg(szTemp);
		cClanReport.menuInit(C_menuN, clanszError_Msg.pos.x, clanszError_Msg.pos.y);

		strcpy(clanszError_Msg.szMsg, szTemp1);

		CLAN_ERROR_ret = CLAN_AllEnd;
		break;
		case CLAN_JOIN_chip_YES:
		wsprintf(szTemp, clanClanJoinsucesssMsg.szMsg, cldata.clanJoinCharID);

		strcpy(szTemp1, clanszError_Msg.szMsg);
		strcpy(clanszError_Msg.szMsg, szTemp);


		CheckMsgPos(&clanszError_Msg, BOX_MAX_WIDTH, 0);

		strcpy(szTemp, clanszError_Msg.szMsg);

		C_menuN = CLAN_ERROR;
		cClanReport.InitMsg(szTemp);
		cClanReport.menuInit(C_menuN, clanszError_Msg.pos.x, clanszError_Msg.pos.y);
		strcpy(clanszError_Msg.szMsg, szTemp1);
		CLAN_ERROR_ret = CLAN_AllEnd;




		void SetClanWon();
		SetClanWon();

		break;

	}
}

void CLANEntity_JOIN::menuInit(int num)
{
	int bx = 0, by = 0;
	switch(num)
	{
		case CLAN_CLANWONOVER:
		menuSu = 3;
	#ifdef USE_PROSTONTALE		
		bx = 32;
		by = 16;
	#else
		bx = 32;
		by = 16;
	#endif
		menuPos[0].left = BackStartPos.x + BUTTON1_X;
		menuPos[0].top = BackStartPos.y + BUTTON1_Y;
		menuPos[0].right = menuPos[0].left + bx;
		menuPos[0].bottom = menuPos[0].top + by;


		menuPos[1].left = BackStartPos.x + clanClanWonOver.pos.x;
		menuPos[1].top = BackStartPos.y + clanClanWonOver.pos.y;

	#ifdef USE_PROSTONTALE		
		bx = 64;
		by = 16;
	#else
		bx = 64;
		by = 16;
	#endif
		menuPos[2].left = BackStartPos.x + BUTTON1_BOX_X;
		menuPos[2].top = BackStartPos.y + BUTTON1_BOX_Y;
		menuPos[2].right = menuPos[2].left + bx;
		menuPos[2].bottom = menuPos[2].top + by;
		break;
		case CLANUSER_JOIN:
		menuSu = 3;
	#ifdef USE_PROSTONTALE		
		bx = 32;
		by = 16;
	#else
		bx = 32;
		by = 16;
	#endif
		menuPos[0].left = BackStartPos.x + BUTTON1_X;
		menuPos[0].top = BackStartPos.y + BUTTON1_Y;
		menuPos[0].right = menuPos[0].left + bx;
		menuPos[0].bottom = menuPos[0].top + by;


		menuPos[1].left = BackStartPos.x + clanClanJoinMsg.pos.x;
		menuPos[1].top = BackStartPos.y + clanClanJoinMsg.pos.y;

	#ifdef USE_PROSTONTALE		
		bx = 64;
		by = 16;
	#else
		bx = 64;
		by = 16;
	#endif
		menuPos[2].left = BackStartPos.x + BUTTON1_BOX_X;
		menuPos[2].top = BackStartPos.y + BUTTON1_BOX_Y;
		menuPos[2].right = menuPos[2].left + bx;
		menuPos[2].bottom = menuPos[2].top + by;

		break;
		case CLAN_JOIN:


		menuSu = 5;
	#ifdef USE_PROSTONTALE		
		bx = 32;
		by = 16;
	#else
		bx = 32;
		by = 16;
	#endif

		menuPos[0].left = BackStartPos.x + BUTTON2_X;
		menuPos[0].top = BackStartPos.y + BUTTON2_Y;
		menuPos[0].right = menuPos[0].left + bx;
		menuPos[0].bottom = menuPos[0].top + by;


	#ifdef USE_PROSTONTALE		
		bx = 32;
		by = 16;
	#else
		bx = 32;
		by = 16;
	#endif

		menuPos[1].left = BackStartPos.x + BUTTON3_X;
		menuPos[1].top = BackStartPos.y + BUTTON3_Y;
		menuPos[1].right = menuPos[1].left + bx;
		menuPos[1].bottom = menuPos[1].top + by;

		menuPos[2].left = BackStartPos.x + 150;
		menuPos[2].top = BackStartPos.y + 150;
		menuPos[2].right = menuPos[2].left + bx;
		menuPos[2].bottom = menuPos[2].top + by;


		menuPos[3].left = BackStartPos.x + clanJoin.pos.x;
		menuPos[3].top = BackStartPos.y + clanJoin.pos.y;
		menuPos[3].right = menuPos[3].left + 280;
		menuPos[3].bottom = menuPos[3].top + 250;

	#ifdef USE_PROSTONTALE		
		bx = 64;
		by = 16;
	#else
		bx = 64;
		by = 16;
	#endif

		menuPos[4].left = BackStartPos.x + BUTTON2_BOX_X;
		menuPos[4].top = BackStartPos.y + BUTTON2_BOX_Y;
		menuPos[4].right = menuPos[4].left + bx;
		menuPos[4].bottom = menuPos[4].top + by;

	#ifdef USE_PROSTONTALE		
		bx = 64;
		by = 16;
	#else
		bx = 64;
		by = 16;
	#endif

		menuPos[5].left = BackStartPos.x + BUTTON3_BOX_X;
		menuPos[5].top = BackStartPos.y + BUTTON3_BOX_Y;
		menuPos[5].right = menuPos[6].left + bx;
		menuPos[5].bottom = menuPos[6].top + by;

		break;
	}

}

void CLANEntity_JOIN::Draw() {}

void CLANEntity_JOIN::AddClanWon()
{
	int i;
	for(i = 0; i < CLANWON_MAX - 1; i++)
	{
		if(cldata.clanWon[i][0] == 0)
		{
			strcpy(cldata.clanWon[i], cldata.clanJoinCharID);
			nClanWon_Num += 1;

			cldata.nTotalClanWonCount = nClanWon_Num;
			cldata.nCurrentClanWon_Num += 1;
			break;
		}
	}







	for(i = 0; i < CLANWON_MAX - 1; i++)
	{
		if(cldata.clanWon[i][0] != 0)
		{
			//fd2("Ŭ��������Ʈ  cldata.clanWon[%d] = %s  ", i, cldata.clanWon[i]);
		}
	}

}



















int nClanWonLevelTable[] = {
		0,0,0,0,0,0,0,0,0,0,
		0,0,0,0,0,0,0,0,0,0,
		0,0,0,0,0,0,0,0,0,0,
		0,0,0,0,0,0,0,0,0,0,
		20,21,
		22,23,
		24,25,
		26,27,
		28,29,
		30,31,
		32,33,
		34,35,
		36,37,
		38,39,
		40,41,
		42,43,
		44,45,
		46,47,
		48,49,
		50,51,
		52,53,
		54,55,
		56,57,
		58,59,
		60,61,
		62,63,
		64,65,
		66,67,
		68,69,
		70,71,
		72,73,
		74,75,
		76,77,
		78,80,


};

void CLANEntity_JOIN::SetLevelTable()
{







}

BOOL CLANEntity_JOIN::CheckClanWon(int level)
{
	int nMaxClanWonCount = 0;
	nMaxClanWonCount = nClanWonLevelTable[level];
	if(nMaxClanWonCount > cldata.nCurrentClanWon_Num)
	{


		return TRUE;
	}




	return TRUE;
}


int CLANEntity_JOIN::GetMaxClanWonCount(int level)
{
	return nClanWonLevelTable[level];
}












void SetLevelTable(int makeclanlevel, int makeclanlevel_clanwon, int addclanwonlevel_start, int addlevel, int addclanwon_num, int maxlevel)
{
	cClanJoin.SetLevelTable();
}


BOOL CheckClanWon(int level)
{
	BOOL bReturn = 0;
	bReturn = cClanJoin.CheckClanWon(level);
	return bReturn;
}

