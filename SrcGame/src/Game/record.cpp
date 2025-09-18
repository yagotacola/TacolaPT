#include "globals.h"

#include "smlib3d\\smd3d.h"

#include "smwsock.h"
#include "character.h"
#include "avictrl.h"
#include "playmain.h"
#include "srcsound\\dxwav.h"
#include "fileread.h"

#include "particle.h"
#include "netplay.h"

#include "sinbaram\\sinlinkheader.h"
#include "hobaram\\holinkheader.h"

#include "record.h"
#include "playsub.h"

#include "field.h"

#include "TextMessage.h"
#include "srcServer\onserver.h"
#include "Montarias\\CMountHandler.h"

char* szRecordHeader = "RC 1.50";			//���� ����ü
DWORD	dwRecordVersion = 150;					//��� ����ü ����

char* szRecordUserDataDir = "userdata";
char* szRecordUserBackupDataDir = "userdata_backup";
char* szRecordUserInfoDir = "userinfo";
char* szRecordWareHouseDir = "warehouse";
char* szRecordDeleteDir = "deleted";
char* szPostBoxDir = "PostBox";

sLAST_QUEST_INFO	RecordLastQuestInfo;			//���� ����Ʈ ����

//#define	CHAR_NAME_MAXLEN	(18+6)
#define	CHAR_NAME_MAXLEN	(16+2)

int	Permit_CheckMoney = TOTAL_CHECK_MONEY_MAX;
int	Permit_CheckExp = TOTAL_CHECK_EXP_MAX;

extern rsSERVER_CONFIG		rsServerConfig;				//���� ���� ����
extern DWORD				dwPlayServTime;				//���� �ð�
extern time_t				tServerTime;				//������ �ð� ( ���� ó���� )
extern int					Server_DebugCount;						//����� ó�� ī����




int rsPutItem_PointTicket(rsPLAYINFO* lpPlayInfo, int Price);


/*
//������ ��
#define ITEM_CODER_MAX		1000000
#define COPY_ITEM_MAX		1000

struct	sITEM_CODE_CMP {
	DWORD	dwCode;
	DWORD	dwKey;
	DWORD	dwSum;

	DWORD	OpenCounter;
};

struct sITEMCODER {
	sITEM_CODE_CMP	sItemCode[ITEM_CODER_MAX];
	int sItemCodeCount;
	int CopyItemCount;
};

struct sCOPYITEM {
	int sItemCodeCount;
	sITEM_CODE_CMP sItemCode[COPY_ITEM_MAX];
};
*/

//extern HINSTANCE hinst; 
#include "resource.h"

static char LastAcessID[64];



//////////////////////////////////////////////////////////////////////////////////////////////
struct sREC_DATABUFF {
	rsPLAYINFO* lpPlayInfo;
	DWORD		dwConnectCount;
	char		szName[32];
	char		szFileName[128];
	char		szBackupFileName[128];
	TRANS_RECORD_DATA	TransRecData;
};

#define	REC_DATABUFF_MAX		128
#define	REC_DATABUFF_MASK		127
#define	REC_DATABUFF_LIMIT		64

sREC_DATABUFF* sRecDataBuff = 0;
int				sRecDataBuffCount;
HANDLE			hRecThread = 0;
DWORD			dwRecThreadId;
DWORD			dwLastRecDataTime = 0;

//ũ��Ƽ�� ����
CRITICAL_SECTION	cRecDataSection;				//���� ����� ũ��Ƽ�ü���
CRITICAL_SECTION	cSaveDataSection;				//�������� ũ��Ƽ�ü���

extern int isItemCostume;
extern sITEM InvenCostume;


int CheckRecWaitData(char* szName);



int	EncodeFileName(char* szName, char* szDecodeName)
{
	int	len;
	int cnt;
	int cnt2;
	BYTE ch1, ch2;
	DWORD ch;

	len = lstrlen(szName);

	cnt2 = 0;

	for (cnt = 0; cnt < len; cnt++) {
		ch = (DWORD)szName[cnt];
		ch1 = (BYTE)(ch >> 4) & 0xF;
		ch2 = (BYTE)ch & 0xF;
		ch1 += 'a';
		ch2 += 'a';
		szDecodeName[cnt2++] = (char)ch1;
		szDecodeName[cnt2++] = (char)ch2;
	}
	szDecodeName[cnt2] = 0;

	return TRUE;
}


static int GetUserCode(char* szName)
{
	int cnt, len;
	BYTE ch;
	BYTE* lpData = (BYTE*)szName;

	len = lstrlen(szName);

	ch = 0;
	/*
		if ( ch>='a' && ch<='z' ) {//�빮�� �ҹ��ڷ�
			Sum2 += (ch-0x20)*(cnt+1);
	*/

	for (cnt = 0; cnt < len; cnt++) {
		if (lpData[cnt] >= 'a' && lpData[cnt] <= 'z') {
			ch += (lpData[cnt] - 0x20);				//�ҹ��� �빮�ڷ� ���
		}
		else
			ch += lpData[cnt];
	}

	return ch;
}


//������ ���� ��� ���ϱ�
int GetPostBoxFile(char* szID, char* szFileName)
{

	if (szID[4] == 0 && szID[3] >= '0' && szID[3] <= '9' && (
		((szID[0] == 'c' || szID[0] == 'C') && (szID[1] == 'o' || szID[1] == 'O') && (szID[2] == 'm' || szID[2] == 'M')) ||
		((szID[0] == 'l' || szID[0] == 'L') && (szID[1] == 'p' || szID[1] == 'P') && (szID[2] == 't' || szID[2] == 'T')))
		) {
		wsprintf(szFileName, "%s\\%d\\��%s.dat", szPostBoxDir, GetUserCode(szID), szID);
		return TRUE;
	}

	if (szID[3] == 0 &&
		((szID[0] == 'p' || szID[0] == 'P') && (szID[1] == 'r' || szID[1] == 'R') && (szID[2] == 'n' || szID[2] == 'N')) ||
		((szID[0] == 'c' || szID[0] == 'C') && (szID[1] == 'o' || szID[1] == 'O') && (szID[2] == 'n' || szID[2] == 'N'))
		) {
		wsprintf(szFileName, "%s\\%d\\��%s.dat", szPostBoxDir, GetUserCode(szID), szID);
		return TRUE;
	}

	wsprintf(szFileName, "%s\\%d\\%s.dat", szPostBoxDir, GetUserCode(szID), szID);

	return TRUE;
}


static int GetUserInfoFile(char* szID, char* szFileName)
{
	//wsprintf( szFileName , "%s\\%s.dat" , szRecordUserInfoDir , szID );

	if (szID[4] == 0 && szID[3] >= '0' && szID[3] <= '9' && (
		((szID[0] == 'c' || szID[0] == 'C') && (szID[1] == 'o' || szID[1] == 'O') && (szID[2] == 'm' || szID[2] == 'M')) ||
		((szID[0] == 'l' || szID[0] == 'L') && (szID[1] == 'p' || szID[1] == 'P') && (szID[2] == 't' || szID[2] == 'T')))
		) {
		wsprintf(szFileName, "DataServer\\%s\\%d\\��%s.dat", szRecordUserInfoDir, GetUserCode(szID), szID);
		return TRUE;
	}

	if (szID[3] == 0 &&
		((szID[0] == 'p' || szID[0] == 'P') && (szID[1] == 'r' || szID[1] == 'R') && (szID[2] == 'n' || szID[2] == 'N')) ||
		((szID[0] == 'c' || szID[0] == 'C') && (szID[1] == 'o' || szID[1] == 'O') && (szID[2] == 'n' || szID[2] == 'N'))
		) {
		wsprintf(szFileName, "DataServer\\%s\\%d\\��%s.dat", szRecordUserInfoDir, GetUserCode(szID), szID);
		return TRUE;
	}

	wsprintf(szFileName, "DataServer\\%s\\%d\\%s.dat", szRecordUserInfoDir, GetUserCode(szID), szID);

	return TRUE;
}

int GetUserDataFile(char* szName, char* szFileName)
{
	//wsprintf( szFileName , "%s\\%s.dat" , szRecordUserDataDir , szName );
	wsprintf(szFileName, "DataServer\\%s\\%d\\%s.dat", szRecordUserDataDir, GetUserCode(szName), szName);

	return TRUE;
}

int GetTT_ServerPath(char* szServerID, char* szTTServerPath)
{
	int cnt;

	szTTServerPath[0] = 0;

	for (cnt = 0; cnt < rsServerConfig.TT_DataServer_Count; cnt++) {
		if (lstrcmpi(szServerID, rsServerConfig.TT_DataServer[cnt].szServerID) == 0) {
			lstrcpy(szTTServerPath, rsServerConfig.TT_DataServer[cnt].szServerPath);
			return TRUE;
		}
	}

	return FALSE;
}


int GetRealID(char* szID, char* szRealID)
{

	int cnt, len;

	len = lstrlen(szID);
	lstrcpy(szRealID, szID);
	for (cnt = len - 1; cnt >= 0; cnt--) {
		if (szRealID[cnt] == '@') {
			szRealID[cnt] = 0;
			return TRUE;
		}
	}


	return FALSE;
}

//����ID ���ϱ�
int SetServerID(char* szID, char* szServerID)
{
	char szFile[64];
	int cnt, len;

	if (rsServerConfig.TT_DataServer_Count) {
		lstrcpy(szFile, szID);
		len = lstrlen(szFile);
		for (cnt = len - 1; cnt >= 0; cnt--) {
			if (szFile[cnt] == '@') {
				lstrcpy(szServerID, szFile + cnt + 1);
				szServerID[4] = 0;
				return TRUE;
			}
		}
	}

	return FALSE;
}


static int GetUserInfoFile2(char* szID, char* szFileName, char* szServerID)
{
	//wsprintf( szFileName , "%s\\%s.dat" , szRecordUserInfoDir , szID );
	char szTTServerPath[128];
	GetTT_ServerPath(szServerID, szTTServerPath);

	char szRealID[64];

	GetRealID(szID, szRealID);

	if (szID[4] == 0 && szID[3] >= '0' && szID[3] <= '9' && (
		((szID[0] == 'c' || szID[0] == 'C') && (szID[1] == 'o' || szID[1] == 'O') && (szID[2] == 'm' || szID[2] == 'M')) ||
		((szID[0] == 'l' || szID[0] == 'L') && (szID[1] == 'p' || szID[1] == 'P') && (szID[2] == 't' || szID[2] == 'T')))
		) {
		wsprintf(szFileName, "%s\\DataServer\\%s\\%d\\��%s.dat", szTTServerPath, szRecordUserInfoDir, GetUserCode(szRealID), szRealID);
		return TRUE;
	}

	if (szID[3] == 0 &&
		((szID[0] == 'p' || szID[0] == 'P') && (szID[1] == 'r' || szID[1] == 'R') && (szID[2] == 'n' || szID[2] == 'N')) ||
		((szID[0] == 'c' || szID[0] == 'C') && (szID[1] == 'o' || szID[1] == 'O') && (szID[2] == 'n' || szID[2] == 'N'))
		) {
		wsprintf(szFileName, "%s\\DataServer\\%s\\%d\\��%s.dat", szTTServerPath, szRecordUserInfoDir, GetUserCode(szRealID), szRealID);
		return TRUE;
	}

	wsprintf(szFileName, "%s\\DataServer\\%s\\%d\\%s.dat", szTTServerPath, szRecordUserInfoDir, GetUserCode(szRealID), szRealID);

	return TRUE;
}

int GetUserDataFile2(char* szName, char* szFileName, char* szServerID)
{
	char szTTServerPath[128];
	GetTT_ServerPath(szServerID, szTTServerPath);
	/*
		char szRealID[64];
		int cnt,len;

		len = lstrlen( szID );
		lstrcpy( szRealID , szID );
		for(cnt=len-1;cnt>=0;cnt--) {
			if ( szRealID[cnt]=='@' ) {
				szRealID[cnt] = 0;
				break;
			}
		}
	*/
	wsprintf(szFileName, "%s\\DataServer\\%s\\%d\\%s.dat", szTTServerPath, szRecordUserDataDir, GetUserCode(szName), szName);

	return TRUE;
}


static int GetDeleteDataFile(char* szName, char* szFileName)
{
	wsprintf(szFileName, "DataServer\\%s\\%s.dat", szRecordDeleteDir, szName);

	return TRUE;
}


static int GetUserDataBackupFile(char* szName, char* szFileName)
{
	//wsprintf( szFileName , "%s\\%s.dat" , szRecordUserBackupDataDir , szName );
	wsprintf(szFileName, "DataServer\\%s\\%d\\%s.dat", szRecordUserBackupDataDir, GetUserCode(szName), szName);

	return TRUE;
}

static int GetWareHouseFile(char* szName, char* szFileName)
{
	//wsprintf( szFileName , "%s\\%s.war" , szRecordWareHouseDir , szName );

	char* szID = szName;

	if (szID[4] == 0 && szID[3] >= '0' && szID[3] <= '9' && (
		((szID[0] == 'c' || szID[0] == 'C') && (szID[1] == 'o' || szID[1] == 'O') && (szID[2] == 'm' || szID[2] == 'M')) ||
		((szID[0] == 'l' || szID[0] == 'L') && (szID[1] == 'p' || szID[1] == 'P') && (szID[2] == 't' || szID[2] == 'T')))
		) {
		wsprintf(szFileName, "DataServer\\%s\\%d\\��%s.dat", szRecordWareHouseDir, GetUserCode(szID), szID);
		return TRUE;
	}

	if (szID[3] == 0 &&
		((szID[0] == 'p' || szID[0] == 'P') && (szID[1] == 'r' || szID[1] == 'R') && (szID[2] == 'n' || szID[2] == 'N')) ||
		((szID[0] == 'c' || szID[0] == 'C') && (szID[1] == 'o' || szID[1] == 'O') && (szID[2] == 'n' || szID[2] == 'N'))
		) {
		wsprintf(szFileName, "DataServer\\%s\\%d\\��%s.dat", szRecordWareHouseDir, GetUserCode(szID), szID);
		return TRUE;
	}

	wsprintf(szFileName, "DataServer\\%s\\%d\\%s.war", szRecordWareHouseDir, GetUserCode(szName), szName);

	return TRUE;
}

static int GetUserDataFile_BackupDay(char* szName, char* szFileName, int Day)
{
	wsprintf(szFileName, "%s\\%d\\%s\\%d\\%s.dat",
		rsServerConfig.szBackupPath, Day,
		szRecordUserDataDir, GetUserCode(szName), szName);

	return TRUE;
}

static int GetWareHouseFile_Backup(char* szName, char* szFileName, int Day)
{

	char* szID = szName;
	char szBuff[256];

	wsprintf(szBuff, "%s\\%d", rsServerConfig.szBackupPath, Day);

	if (szID[4] == 0 && szID[3] >= '0' && szID[3] <= '9' && (
		((szID[0] == 'c' || szID[0] == 'C') && (szID[1] == 'o' || szID[1] == 'O') && (szID[2] == 'm' || szID[2] == 'M')) ||
		((szID[0] == 'l' || szID[0] == 'L') && (szID[1] == 'p' || szID[1] == 'P') && (szID[2] == 't' || szID[2] == 'T')))
		) {
		wsprintf(szFileName, "%s\\%s\\%d\\��%s.dat", szBuff, szRecordWareHouseDir, GetUserCode(szID), szID);
		return TRUE;
	}

	if (szID[3] == 0 &&
		((szID[0] == 'p' || szID[0] == 'P') && (szID[1] == 'r' || szID[1] == 'R') && (szID[2] == 'n' || szID[2] == 'N')) ||
		((szID[0] == 'c' || szID[0] == 'C') && (szID[1] == 'o' || szID[1] == 'O') && (szID[2] == 'n' || szID[2] == 'N'))
		) {
		wsprintf(szFileName, "%s\\%s\\%d\\��%s.dat", szBuff, szRecordWareHouseDir, GetUserCode(szID), szID);
		return TRUE;
	}

	wsprintf(szFileName, "%s\\%s\\%d\\%s.war", szBuff, szRecordWareHouseDir, GetUserCode(szName), szName);

	return TRUE;
}



//����Ÿ ���弭�� ���丮 ����
int CreateDataServerDirectory()
{
	int cnt;
	char szBuff[256];

	CreateDirectory("DataServer", NULL);				//���丮 ����

	wsprintf(szBuff, "DataServer\\%s", szRecordUserInfoDir);
	CreateDirectory(szBuff, NULL);				//���丮 ����
	wsprintf(szBuff, "DataServer\\%s", szRecordUserDataDir);
	CreateDirectory(szBuff, NULL);				//���丮 ����
	wsprintf(szBuff, "DataServer\\%s", szRecordWareHouseDir);
	CreateDirectory(szBuff, NULL);				//���丮 ����
	wsprintf(szBuff, "DataServer\\%s", szRecordUserBackupDataDir);
	CreateDirectory(szBuff, NULL);				//���丮 ����
	wsprintf(szBuff, "DataServer\\%s", szRecordDeleteDir);
	CreateDirectory(szBuff, NULL);				//���丮 ����


	for (cnt = 0; cnt < 256; cnt++) {
		wsprintf(szBuff, "DataServer\\%s\\%d", szRecordUserInfoDir, cnt);
		CreateDirectory(szBuff, NULL);			//���丮 ����
	}
	for (cnt = 0; cnt < 256; cnt++) {
		wsprintf(szBuff, "DataServer\\%s\\%d", szRecordUserDataDir, cnt);
		CreateDirectory(szBuff, NULL);			//���丮 ����
	}
	for (cnt = 0; cnt < 256; cnt++) {
		wsprintf(szBuff, "DataServer\\%s\\%d", szRecordWareHouseDir, cnt);
		CreateDirectory(szBuff, NULL);			//���丮 ����
	}
	for (cnt = 0; cnt < 256; cnt++) {
		wsprintf(szBuff, "DataServer\\%s\\%d", szRecordUserBackupDataDir, cnt);
		CreateDirectory(szBuff, NULL);			//���丮 ����
	}

	//������ ���丮 �����
	if (CreateDirectory(szPostBoxDir, NULL)) {			//���丮 ����
		for (cnt = 0; cnt < 256; cnt++) {
			wsprintf(szBuff, "%s\\%d", szPostBoxDir, cnt);
			CreateDirectory(szBuff, NULL);				//���丮 ����
		}
	}

	return TRUE;
}



//ĳ���� ���� ���� �ڵ� ���ϱ�
DWORD	GetCharInfoCode(smCHAR_INFO* lpCharInfo)
{
	int cnt;
	int size;
	BYTE* lpCharBuff;
	DWORD	dwKey;
	DWORD	dwCode;

	size = sizeof(smCHAR_INFO);
	lpCharBuff = (BYTE*)lpCharInfo;

	dwKey = 0;

	for (cnt = 0; cnt < size; cnt++) {
		dwKey += lpCharBuff[cnt];
	}

	dwCode = 0;

	for (cnt = 0; cnt < size; cnt++) {
		dwCode += (dwKey + cnt) * lpCharBuff[cnt];
	}

	return dwCode;
}

//sUSESKILL sinSkill;
/*
/////////////��ų ���̺� ����ü
struct sSKILL{
	char	sSkillName[32];			//��ų �̸�
	DWORD	CODE;					//��ų �ڵ�
	char    FileName[32];			//��ų ���� �̸�
	int     Flag;					//��밡�� �÷�
	int     Use;					//����Ʈ �Ҵ簡�� �÷�
	int     Point;					//��ų�� �Ҵ�� ����Ʈ
	int     ShortKey;				//��� Ű
	int     MousePosi;				//��ų ���콺 ������
	int     Position;
	int     UseTime;				//��� �ð�
	int     CheckTime;				//���ð��� üũ�Ѵ�
	int     GageLength;				//�����͸� ������ ����
	float     GageLength2;			//�����͸� ������ ����
	float   Mastery;				//�����͸� ���� ��ġ
	int     UseSkillCount;			//��ų��� ��ġ
	float	UseSkillMastery;		//���� �ö󰡴� ��ġ
	int     UseSkillMasteryGage;	//���� �ö󰡴� ������
	int     UseSkillFlag;			//1�� ��� 0�� ���Ұ�
	int     PlusState[5];			//�÷���
	sSKILL_INFO Skill_Info;
};

/////////////���� ���ǰ��ִ� ��ų ����ü
struct sUSESKILL{
	sSKILL UseSkill[SIN_MAX_USE_SKILL]; //����Ҽ��ִ� ��ų
	sSKILLBOX SkillBox[SIN_MAX_USE_SKILL];
	sSKILL *pLeftSkill;		//���콺 ���� ��ư�� �Ҵ�� ��ų
	sSKILL *pRightSkill;	//���콺 �����ʿ� �Ҵ�� ��ų
	int   SkillPoint;

};
//����� ��ų ����
struct	RECORD_SKILL {
	BYTE	bSkillPoint[SIN_MAX_USE_SKILL];			//��ų ����Ʈ
	WORD	wSkillMastery[SIN_MAX_USE_SKILL];		//��ų ���õ�
	BYTE	bShortKey[SIN_MAX_USE_SKILL];			//��� Ű
	WORD	wSelectSkill[2];						//���õ� ��ų
	//int		RemainPoint;
};

*/

//��ų ����
int	RecordSkill(RECORD_SKILL* lpRecordSkill)
{
	int cnt;
	int mcnt;

	for (cnt = 0; cnt < SIN_MAX_USE_SKILL; cnt++) {
		mcnt = cnt & 15;							//��ų ���� ���� ������ ���� ( �迭�� 16���� ��Ƴ��� 16�� �迭�� 0�� ���� )

		lpRecordSkill->bSkillPoint[mcnt] = sinSkill.UseSkill[cnt].Point;
		if (sinSkill.UseSkill[cnt].Point > 255) lpRecordSkill->bSkillPoint[mcnt] = 255;

		if (sinSkill.UseSkill[cnt].UseSkillCount < 10000)		//��ų���õ� �ְ�ġ
			lpRecordSkill->wSkillMastery[mcnt] = sinSkill.UseSkill[cnt].UseSkillCount;
		else
			lpRecordSkill->wSkillMastery[mcnt] = 10000;

		lpRecordSkill->bShortKey[mcnt] = sinSkill.UseSkill[cnt].ShortKey | (sinSkill.UseSkill[cnt].MousePosi << 4);
	}

	lpRecordSkill->wSelectSkill[0] = 0;
	lpRecordSkill->wSelectSkill[1] = 0;

	if (sinSkill.pLeftSkill && sinSkill.pLeftSkill->CODE != SKILL_NORMAL_ATTACK) {
		lpRecordSkill->wSelectSkill[0] = sinSkill.pLeftSkill->Skill_Info.SkillNum + 1;
	}
	if (sinSkill.pRightSkill && sinSkill.pRightSkill->CODE != SKILL_NORMAL_ATTACK) {
		lpRecordSkill->wSelectSkill[1] = sinSkill.pRightSkill->Skill_Info.SkillNum + 1;
	}

	return TRUE;
}



//����Ʈ�� ȹ���� ��ų ����Ʈ
int GetSkillPoint_LevelQuest(int Level, DWORD dwLevelQuestLog)
{
	int Point = 0;

	if (dwLevelQuestLog & QUESTBIT_LEVEL_30 && Level >= 30) {

	}
	if (dwLevelQuestLog & QUESTBIT_LEVEL_55 && Level >= 55) {
		Point++;
	}
	if (dwLevelQuestLog & QUESTBIT_LEVEL_70 && Level >= 70) {
		Point++;
	}
	if (dwLevelQuestLog & QUESTBIT_LEVEL_80 && Level >= 80) {
		Point += 2;
	}

	return Point;
}

//����Ʈ�� ȹ���� ���� ����Ʈ
int GetStatePoint_LevelQuest(int Level, DWORD dwLevelQuestLog)
{
	int Point = 0;

	if (dwLevelQuestLog & QUESTBIT_LEVEL_30 && Level >= 30) {
		Point += 5;
	}
	if (dwLevelQuestLog & QUESTBIT_LEVEL_55 && Level >= 55) {

	}
	if (dwLevelQuestLog & QUESTBIT_LEVEL_70 && Level >= 70) {
		Point += 5;
	}
	if (dwLevelQuestLog & QUESTBIT_LEVEL_80 && Level >= 80) {
		Point += 5;
	}

	if (dwLevelQuestLog & QUESTBIT_LEVEL_80_2 && Level >= 80) {		//80�� �̻� ����7�� �ش� (+2)
		Point += (Level - 79) * 2;
	}

	if (dwLevelQuestLog & QUESTBIT_LEVEL_90_2 && Level >= 90) {		//90�� �̻� ����10�� �ش� (+2+3)
		Point += (Level - 89) * 3;
	}

	return Point;
}


//��ų ����
int	RestoreSkill(RECORD_SKILL* lpRecordSkill, DWORD dwLevelQuestLog)
{
	int cnt, mcnt;
	int	Point, EPoint;

	Point = 0;
	EPoint = 0;

	if (lpRecordSkill->bSkillPoint[0] > 0 && lpRecordSkill->bSkillPoint[15] == 0) {
		lpRecordSkill->bSkillPoint[0] = 0;
		lpRecordSkill->wSkillMastery[0] = 0;
		lpRecordSkill->bShortKey[0] = 0;
	}

	for (cnt = 0; cnt < SIN_MAX_USE_SKILL; cnt++) {
		mcnt = cnt & 15;							//��ų ���� ���� ������ ���� ( �迭�� 16���� ��Ƴ��� 16�� �迭�� 0�� ���� )

		if (cnt > 0) {	//�ָ��� ����
			sinSkill.UseSkill[cnt].Point = lpRecordSkill->bSkillPoint[mcnt];
			sinSkill.UseSkill[cnt].UseSkillCount = lpRecordSkill->wSkillMastery[mcnt];
			sinSkill.UseSkill[cnt].ShortKey = lpRecordSkill->bShortKey[mcnt] & 0xF;
			sinSkill.UseSkill[cnt].MousePosi = lpRecordSkill->bShortKey[mcnt] >> 4;
			sinSkill.UseSkill[cnt].Position = cnt + 1;
			//Point += sinSkill.UseSkill[cnt].Point;
		}
	}

	for (cnt = 1; cnt < 13; cnt++) {
		Point += sinSkill.UseSkill[cnt].Point;
	}
	for (cnt = 13; cnt < SIN_MAX_USE_SKILL; cnt++) {
		EPoint += sinSkill.UseSkill[cnt].Point;
	}


	sinSkill.UseSkill[0].Point = 1;
	sinSkill.UseSkill[0].UseSkillFlag = 1;
	sinSkill.UseSkill[0].Position = 1;


	sinSkill.pLeftSkill = &sinSkill.UseSkill[lpRecordSkill->wSelectSkill[0]];
	sinSkill.pRightSkill = &sinSkill.UseSkill[lpRecordSkill->wSelectSkill[1]];

	if (lpCurPlayer->smCharInfo.Level >= 10) {
		sinSkill.SkillPoint = ((lpCurPlayer->smCharInfo.Level - 8) / 2) - Point;
		sinSkill.SkillPoint += GetSkillPoint_LevelQuest(lpCurPlayer->smCharInfo.Level, dwLevelQuestLog);		//����Ʈ�� ���� ����Ʈ

		if (sinSkill.SkillPoint < 0) {
			//��ų ����Ʈ ���� ( ��ų �ʱ�ȭ )
			for (cnt = 0; cnt < 13; cnt++) {
				sinSkill.UseSkill[cnt].Point = 0;
				sinSkill.UseSkill[cnt].UseSkillCount = 0;
			}
			sinSkill.SkillPoint = 0;
		}
	}
	else {
		sinSkill.SkillPoint = 0;
	}


	if (lpCurPlayer->smCharInfo.Level >= 60) {
		sinSkill.SkillPoint4 = ((lpCurPlayer->smCharInfo.Level - 58) / 2) - EPoint;

		if (sinSkill.SkillPoint4 < 0) {
			//��ų ����Ʈ ���� ( ��ų �ʱ�ȭ )
			for (cnt = 13; cnt < SIN_MAX_USE_SKILL; cnt++) {
				sinSkill.UseSkill[cnt].Point = 0;
				sinSkill.UseSkill[cnt].UseSkillCount = 0;
			}
			sinSkill.SkillPoint4 = 0;
		}
	}
	else {
		sinSkill.SkillPoint4 = 0;
	}


	cInvenTory.SetItemToChar();
	CSKILL->InitReformSkillPointForm();

	return TRUE;
}


//��ų ýũ
int	CheckSkillPoint(int Level, RECORD_SKILL* lpRecordSkill, int* spTotal, DWORD dwLevelQuestLog)
{
	int cnt, mcnt;
	int	Point, EPoint;
	int SkillPoint;
	int ExtraPoint;

	Point = 0;
	EPoint = 0;

	//for(cnt=1;cnt<SIN_MAX_USE_SKILL;cnt++) {
	for (cnt = 1; cnt < 13; cnt++) {
		if (lpRecordSkill->bSkillPoint[cnt] > 10) return FALSE;
		Point += abs(lpRecordSkill->bSkillPoint[cnt]);
	}

	for (cnt = 13; cnt < SIN_MAX_USE_SKILL; cnt++) {
		mcnt = cnt & 15;
		if (lpRecordSkill->bSkillPoint[mcnt] > 10) return FALSE;
		EPoint += abs(lpRecordSkill->bSkillPoint[mcnt]);
	}

	if (spTotal) *spTotal = (Point + (EPoint << 16));

	if (Level >= 10) {
		SkillPoint = ((Level - 8) / 2) - Point;
		SkillPoint += GetSkillPoint_LevelQuest(Level, dwLevelQuestLog);		//����Ʈ�� ȹ���� ��ų ����Ʈ

		if (SkillPoint < 0) {
			//��ų ����Ʈ ���� ( ��ų �ʱ�ȭ )
			return FALSE;
		}
	}
	else {
		if (Point > 0) return FALSE;
	}

	if (Level >= 60) {
		ExtraPoint = ((Level - 58) / 2) - EPoint;
		if (ExtraPoint < 0) {
			//Ȯ�彺ų ����Ʈ ���� ( ��ų �ʱ�ȭ )
			return FALSE;
		}
	}
	else {
		if (EPoint > 0) return FALSE;
	}

	return TRUE;
}


//99
//ĳ���� ������Ʈ ���� ���Ӱ� �����Ѵ�
int ReformCharStatePoint(smCHAR_INFO* lpCharInfo, DWORD dwLevelQuestLog)
{
	int Total;
	int NewState;

	Total = abs(lpCharInfo->Strength) +
		abs(lpCharInfo->Spirit) +
		abs(lpCharInfo->Dexterity) +
		abs(lpCharInfo->Health) +
		abs(lpCharInfo->Talent) +
		abs(lpCharInfo->StatePoint);

	//99�� �⺻ġ
	NewState = 99 + ((lpCharInfo->Level - 1) * 5);
	NewState += GetStatePoint_LevelQuest(lpCharInfo->Level, dwLevelQuestLog);		//����Ʈ�� ȹ���� ���� ����Ʈ

	lpCharInfo->StatePoint += (NewState - Total);

	if (lpCharInfo->StatePoint <= -10) {
		//ĳ���� �ɷ�ġ ���� �߻�
		lpCharInfo->Strength = 1;
		lpCharInfo->Spirit = 8;
		lpCharInfo->Dexterity = 1;
		lpCharInfo->Health = 8;
		lpCharInfo->Talent = 1;
		if (lpCharInfo->StatePoint < 0) lpCharInfo->StatePoint = 0;

		return FALSE;
	}
	if (lpCharInfo->StatePoint < 0) lpCharInfo->StatePoint = 0;

	return TRUE;
}


extern int iSecondsInCity;

//���� ���� ����Ÿ ���
int RecordGameData(sGAME_SAVE_INFO* lpGameSaveInfo)
{
	lpGameSaveInfo->Head = dwRecordVersion;

	lpGameSaveInfo->CameraMode = cInterFace.sInterFlags.CameraAutoFlag;

	if (lpCurPlayer->OnStageField >= 0)
		lpGameSaveInfo->PlayStageNum = StageField[lpCurPlayer->OnStageField]->FieldCode;
	else
		lpGameSaveInfo->PlayStageNum = -1;

	//�α� �ƿ� ��ǥ
	lpGameSaveInfo->PosX = lpCurPlayer->pX;
	lpGameSaveInfo->PosZ = lpCurPlayer->pZ;

	//������ ����� ����ID ����
	if (lstrlen(UserAccount) < 32) {
		lstrcpy(lpGameSaveInfo->szMasterID, UserAccount);
	}

	//Ŭ���̾�Ʈ���� ������ ȹ���� ����ġ�� �� ���
	lpGameSaveInfo->TotalExp = GetTotalExp() ^ lpGameSaveInfo->PosX;
	lpGameSaveInfo->TotalMoney = GetTotalMoney() ^ lpGameSaveInfo->PosZ;
	lpGameSaveInfo->TotalSubExp = GetTotalSubExp();

	//��ų ����
	RecordSkill(&lpGameSaveInfo->SkillInfo);
	//�⺻���� ����Ű����
	lpGameSaveInfo->ShortKey_NormalAttack = sinSkill.UseSkill[0].ShortKey | (sinSkill.UseSkill[0].MousePosi << 4);


	sQUEST_INFO	QuestInfo;
	DWORD	QuestCode;

	ZeroMemory(&QuestInfo, sizeof(sQUEST_INFO));
	QuestCode = sinSaveQuest(&QuestInfo.Data);
	QuestInfo.wQuestCode[0] = (WORD)QuestCode;
	memcpy(&lpGameSaveInfo->QuestInfo, &QuestInfo, sizeof(sQUEST_INFO));

	memcpy(&lpGameSaveInfo->LastQuestInfo, &RecordLastQuestInfo, sizeof(sLAST_QUEST_INFO));		//���� ����Ʈ ���

	lpGameSaveInfo->sPetInfo[0] = (short)cHelpPet.PetKind;
	lpGameSaveInfo->sPetInfo[1] = (short)cHelpPet.PetShow;

	lpGameSaveInfo->dwLevelQuestLog = sinQuest_levelLog;
	lpGameSaveInfo->dwElementaryQuestLog = haElementaryQuestLog;

	for (int j = 0; j < SINUPKEEPITEM_MAX; j++)
	{
		if (chaPremiumitem.UpKeepItem[j].Visible == true)
		{
			switch (chaPremiumitem.UpKeepItem[j].TGAImageNumber)
			{
			case nsPremiumItem::EXPUP_POTION:
				lpGameSaveInfo->dwTime_PrimeItem_ExpUp = chaPremiumitem.UpKeepItem[j].IconTime[1] - chaPremiumitem.UpKeepItem[j].IconTime[0];
				break;
			case nsPremiumItem::THIRD_EYES:
				lpGameSaveInfo->dwTime_PrimeItem_X2 = chaPremiumitem.UpKeepItem[j].IconTime[1] - chaPremiumitem.UpKeepItem[j].IconTime[0];
				break;
			case nsPremiumItem::VAMPIRIC_CUS:
				lpGameSaveInfo->dwTime_PrimeItem_VampCuspid = chaPremiumitem.UpKeepItem[j].IconTime[1] - chaPremiumitem.UpKeepItem[j].IconTime[0];
				break;
			case nsPremiumItem::MANA_RECHAR_P:
				lpGameSaveInfo->dwTime_PrimeItem_ManaRecharg = chaPremiumitem.UpKeepItem[j].IconTime[1] - chaPremiumitem.UpKeepItem[j].IconTime[0];
				break;
			case nsPremiumItem::MIGHT_OF_AWELL:
				lpGameSaveInfo->dwTime_PrimeItem_MightofAwell = chaPremiumitem.UpKeepItem[j].IconTime[1] - chaPremiumitem.UpKeepItem[j].IconTime[0];
				break;
			case nsPremiumItem::MANA_REDUCE_P:
				lpGameSaveInfo->dwTime_PrimeItem_ManaReduce = chaPremiumitem.UpKeepItem[j].IconTime[1] - chaPremiumitem.UpKeepItem[j].IconTime[0];
				break;
			case nsPremiumItem::PHENIX_PET:
				lpGameSaveInfo->dwTime_PrimeItem_PhenixPet = chaPremiumitem.UpKeepItem[j].IconTime[1] - chaPremiumitem.UpKeepItem[j].IconTime[0];
				break;
			case nsPremiumItem::HELP_PET_TERRY:
			case nsPremiumItem::HELP_PET_NEPSYS:
			case nsPremiumItem::HELP_PET_IO:
			case nsPremiumItem::HELP_PET_MUTE:
				lpGameSaveInfo->dwTime_PrimeItem_HelpPet = chaPremiumitem.UpKeepItem[j].IconTime[1] - chaPremiumitem.UpKeepItem[j].IconTime[0];
				break;
			case nsPremiumItem::VAMPIRIC_CUS_EX:
				lpGameSaveInfo->dwTime_PrimeItem_VampCuspid_EX = chaPremiumitem.UpKeepItem[j].IconTime[1] - chaPremiumitem.UpKeepItem[j].IconTime[0];
				break;
			case nsPremiumItem::STAMINA_REDUCE_P:
				lpGameSaveInfo->dwTime_PrimeItem_StaminaReduce = chaPremiumitem.UpKeepItem[j].IconTime[1] - chaPremiumitem.UpKeepItem[j].IconTime[0];
				break;
			case nsPremiumItem::MOUNT:
				lpGameSaveInfo->dwTime_PrimeItem_Mount = chaPremiumitem.UpKeepItem[j].IconTime[1] - chaPremiumitem.UpKeepItem[j].IconTime[0];
				lpGameSaveInfo->dwPrimeItem_MountParam = lpCurPlayer->pMount ? lpCurPlayer->pMount->GetMountID() : 0;
				break;
			}

			continue;
		}
	}

	return TRUE;
}

//���� ���� ����Ÿ ���
int RestoreGameData(sGAME_SAVE_INFO* lpGameSaveInfo)
{
	cInterFace.sInterFlags.CameraAutoFlag = lpGameSaveInfo->CameraMode;
	if (lpGameSaveInfo->QuestInfo.wQuestCode[0]) {
		sinLoadQuest(lpGameSaveInfo->QuestInfo.wQuestCode[0], &lpGameSaveInfo->QuestInfo.Data);
	}

	memcpy(&RecordLastQuestInfo, &lpGameSaveInfo->LastQuestInfo, sizeof(sLAST_QUEST_INFO));		//���� ����Ʈ ���
	//����Ʈ���� ���忡 ����
	SetQuestBoard();

	if (sBiInfo) {
		sBiInfo->PCRNo = lpGameSaveInfo->PCRNo;
		sBiInfo->EventPlay[0] = lpGameSaveInfo->EventPlay[0];
		sBiInfo->EventPlay[1] = lpGameSaveInfo->EventPlay[1];
	}

	cHelpPet.PetKind = (int)lpGameSaveInfo->sPetInfo[0];
	cHelpPet.PetShow = (int)lpGameSaveInfo->sPetInfo[1];
	sinQuest_levelLog = lpGameSaveInfo->dwLevelQuestLog;
	haElementaryQuestLog = lpGameSaveInfo->dwElementaryQuestLog;
	/*
		if ( sBiInfo->PCRNo>0 ) {
			//�ǽù� �����
			cPCBANGPet.PetKind = TRUE;
			cPCBANGPet.ShowPet();
		}
	*/
	//���� ĳ�� ����
	cSinSiege.SetTaxRate(lpGameSaveInfo->BlessCastleTax);	//���� ����
	//���� ĳ�� ������ Ŭ�� ����
	SetBlessCastleMaster(lpGameSaveInfo->dwBlessCastleMaster, 0);

	return TRUE;
}

//����� ����Ʈ ��� �߰�
int Record_LastQuest(WORD	wQuestCode)
{
	int cnt;

	cnt = RecordLastQuestInfo.LastQuestCount & LAST_QUEST_MASK;
	RecordLastQuestInfo.wLastQuest[cnt] = wQuestCode;
	RecordLastQuestInfo.LastQuestCount++;

	return TRUE;
}

//���� ����Ʈ �˻�
int FindLastQuestCode(WORD wQuestCode)
{
	int cnt, mcnt, start;

	if (RecordLastQuestInfo.LastQuestCount > LAST_QUEST_MASK)
		start = RecordLastQuestInfo.LastQuestCount - LAST_QUEST_MASK;
	else
		start = 0;

	for (cnt = start; cnt < RecordLastQuestInfo.LastQuestCount; cnt++) {
		mcnt = cnt & LAST_QUEST_MASK;
		if (RecordLastQuestInfo.wLastQuest[mcnt] == wQuestCode) {
			return TRUE;		//����Ʈ ã�Ҵ�
		}
	}
	return FALSE;
}

/*
#define	LAST_QUEST_MAX		32
#define	LAST_QUEST_MASK		31

struct	sLAST_QUEST_INFO {
	WORD wLastQuest[LAST_QUEST_MAX];
	int	LastQuestCount;
}
*/
//��� ����Ÿ ������ �̻� ���� Ȯ��
int CheckRecordDataItem(TRANS_RECORD_DATA* lpRecordData)
{
	int DataSize, size;
	int ItemCount;
	int cnt;
	int SizeCount;

	BYTE* lpRecordItem;

	DataSize = lpRecordData->DataSize;
	ItemCount = lpRecordData->ItemCount;
	lpRecordItem = lpRecordData->Data;

	SizeCount = 0;

	for (cnt = 0; cnt < ItemCount; cnt++) {

		size = ((int*)lpRecordItem)[0];
		SizeCount += size;
		lpRecordItem += size;

		if (SizeCount > DataSize || SizeCount < 0)
			return FALSE;
	}

	if (SizeCount == DataSize) return TRUE;

	return FALSE;
}
/*
//����� ������ ����Ÿ�� 150 �������� ������ȯ
int	ConvertItem_Server150(TRANS_RECORD_DATA *lpTransRecordData )
{
	BYTE	*lpRecItem;
	sRECORD_ITEM	sRecordItem[INVENTORY_MAXITEM*2];

	int cnt;
	int CompSize;

	lpRecItem = (BYTE *)lpTransRecordData->Data;

	for( cnt=0;cnt<lpTransRecordData->ItemCount;cnt++ ) {
		//���� ����Ÿ �ص� ( Z/NZ ��� )
		DecodeCompress( (BYTE *)lpRecItem , (BYTE *)&sRecordItem[cnt] );
		rsReformItem_Server( &sRecordItem[cnt].sItemInfo );					//������ �ű� ����
		lpRecItem += ((int *)lpRecItem)[0];
	}

	lpTransRecordData->DataSize = 0;
	lpRecItem = (BYTE *)lpTransRecordData->Data;

	for( cnt=0;cnt<lpTransRecordData->ItemCount;cnt++ ) {
		//����Ÿ ���� ( Z/NZ ��� )
		CompSize = EecodeCompress( (BYTE *)&sRecordItem[cnt] , (BYTE *)lpRecItem , sizeof(sRECORD_ITEM) );
		lpRecItem += CompSize;
		lpTransRecordData->DataSize += CompSize;
	}

	lpTransRecordData->size = ((DWORD)lpRecItem)-((DWORD)lpTransRecordData);

	return TRUE;
}
*/



//������ ����Ÿ�� �����Ͽ� ����
int rsRECORD_DBASE::MakeRecordData(smCHAR_INFO* lpCharInfo, sITEM* lpItems, sITEM* lpItems2, sITEM* lpMouseItem)
{
	int cnt;

	BYTE* lpRecItem;
	sRECORD_ITEM	sRecordItem;
	int		CompSize;

	lstrcpy(TransRecordData.szHeader, szRecordHeader);
	memcpy(&TransRecordData.smCharInfo, lpCharInfo, sizeof(smCHAR_INFO));

	TransRecordData.smCharInfo.wVersion[0] = Version_CharInfo;

	ZeroMemory(&TransRecordData.GameSaveInfo, sizeof(sGAME_SAVE_INFO));

	TransRecordData.ThrowItemCount = 0;

	RecordGameData(&TransRecordData.GameSaveInfo);
	//ĳ���� ���� �ڵ� ����
	TransRecordData.GameSaveInfo.dwChkSum_CharInfo = GetCharInfoCode(lpCharInfo);

	TransRecordData.ItemCount = 0;
	lpRecItem = TransRecordData.Data;
	TransRecordData.DataSize = 0;

	for (cnt = 0; cnt < INVENTORY_MAXITEM; cnt++) {
		if (lpItems[cnt].Flag) {
			sRecordItem.ItemCount = cnt;
			sRecordItem.x = lpItems[cnt].x;
			sRecordItem.y = lpItems[cnt].y;
			sRecordItem.ItemPosition = lpItems[cnt].ItemPosition;
			memcpy(&sRecordItem.sItemInfo, &lpItems[cnt].sItemInfo, sizeof(sITEMINFO));

			//����Ÿ ���� ( Z/NZ ��� )
			CompSize = EecodeCompress((BYTE*)&sRecordItem, (BYTE*)lpRecItem, sizeof(sRECORD_ITEM));

			lpRecItem += CompSize;
			TransRecordData.DataSize += CompSize;

			TransRecordData.ItemCount++;
		}
	}

	TransRecordData.ItemSubStart = TransRecordData.ItemCount;

	for (cnt = 0; cnt < INVENTORY_MAXITEM; cnt++) {
		if (lpItems2[cnt].Flag) {
			sRecordItem.ItemCount = cnt;
			sRecordItem.x = lpItems2[cnt].x;
			sRecordItem.y = lpItems2[cnt].y;
			sRecordItem.ItemPosition = lpItems2[cnt].ItemPosition;
			memcpy(&sRecordItem.sItemInfo, &lpItems2[cnt].sItemInfo, sizeof(sITEMINFO));

			CompSize = EecodeCompress((BYTE*)&sRecordItem, (BYTE*)lpRecItem, sizeof(sRECORD_ITEM));

			lpRecItem += CompSize;
			TransRecordData.DataSize += CompSize;

			TransRecordData.ItemCount++;
		}
	}

	if (lpMouseItem && lpMouseItem->Flag) {
		sRecordItem.ItemCount = 0;
		sRecordItem.x = 0;
		sRecordItem.y = 0;
		sRecordItem.ItemPosition = -1;
		memcpy(&sRecordItem.sItemInfo, &lpMouseItem->sItemInfo, sizeof(sITEMINFO));

		CompSize = EecodeCompress((BYTE*)&sRecordItem, (BYTE*)lpRecItem, sizeof(sRECORD_ITEM));

		lpRecItem += CompSize;
		TransRecordData.DataSize += CompSize;

		TransRecordData.ItemCount++;
	}


	TransRecordData.code = smTRANSCODE_RECORDDATA;
	TransRecordData.size = ((DWORD)lpRecItem) - ((DWORD)&TransRecordData);

	return TRUE;
}


int ClientRecordPotion[3][4];
int ClientRecordPotionFlag = 0;

int ResetClientRecordPotion(sGAME_SAVE_INFO* lpGameSaveInfo)
{
	int cnt, cnt2;

	if (!lpGameSaveInfo->sPotionUpdate[0] || lpGameSaveInfo->sPotionUpdate[0] != lpGameSaveInfo->sPotionUpdate[1])
		return FALSE;

	ClientRecordPotionFlag = TRUE;

	for (cnt = 0; cnt < 3; cnt++)
		for (cnt2 = 0; cnt2 < 4; cnt2++)
			ClientRecordPotion[cnt][cnt2] = lpGameSaveInfo->sPotionCount[cnt][cnt2];


	return TRUE;
}

//���� �˻��
int AddRecordPotion(DWORD dwPotionCode, int PotionCount)
{
	int Count = PotionCount;
	int x = -1;
	int y = -1;

	if (ClientRecordPotionFlag == 0) return 0;

	switch (dwPotionCode) {
	case (sinPL1 | sin01):		//����(��)
		x = 0; y = 0;
		break;
	case (sinPL1 | sin02):		//����(��)
		x = 0; y = 1;
		break;
	case (sinPL1 | sin03):		//����(��)
		x = 0; y = 2;
		break;
	case (sinPL1 | sin04):		//����(��)
		x = 0; y = 3;
		break;

	case (sinPM1 | sin01):		//���(��)
		x = 1; y = 0;
		break;
	case (sinPM1 | sin02):		//���(��)
		x = 1; y = 1;
		break;
	case (sinPM1 | sin03):		//���(��)
		x = 1; y = 2;
		break;
	case (sinPM1 | sin04):		//���(��)
		x = 1; y = 3;
		break;

	case (sinPS1 | sin01):		//�ٷ�(��)
		x = 2; y = 0;
		break;
	case (sinPS1 | sin02):		//�ٷ�(��)
		x = 2; y = 1;
		break;
	case (sinPS1 | sin03):		//�ٷ�(��)
		x = 2; y = 2;
		break;
	case (sinPS1 | sin04):		//�ٷ�(��)
		x = 2; y = 3;
		break;
	}

	if (x >= 0 && y >= 0) {
		ClientRecordPotion[x][y] += Count;
		return ClientRecordPotion[x][y];
	}

	return 0;
}



//�ҷ��� ����Ÿ ������ �ش� ��ġ�� ����
int rsRECORD_DBASE::ResotrRecordData(smCHAR_INFO* lpCharInfo, sITEM* lpItems, sITEM* lpItems2, sITEM* lpMouseItem)
{
	int cnt;
	int cnt2, cnt3;
	sITEM* lpChkItem[512];
	int		ChkCnt;
	int		CopyItemCount;
	int		BadItemCount;
	int		SetFlag;
	DWORD	dwItemCode;
	int		WeightError = 0;
	int		PostionError = 0;
	int		SvrPotionError = 0;
	int		ReformItemCount = 0;
	DWORD	dwCode;
	sITEMINFO* lpsItemInfo;

	BYTE* lpRecItem;
	sITEM* lpSaveItem;
	sRECORD_ITEM	sRecordItem;
	sITEM	sItem_Buff;
	char	szMsgBuff[128];
	int		PotionCnt;

	CheckCharForm();

	memcpy(lpCharInfo, &TransRecordData.smCharInfo, sizeof(smCHAR_INFO));
	lpCharInfo->bUpdateInfo[0] = 0;

	//���� ���� ���
	ResetClientRecordPotion(&TransRecordData.GameSaveInfo);

	//ĳ���� ���� ���� Ȯ��
	CheckCharForm();
	//ũ�� ýũ
	CheckCracker();
	/*
		hResource = FindResource( hinst , MAKEINTRESOURCE(IDR_GOODITEM1), "GOODITEM" );
		hLoadRes = LoadResource( hinst , (HRSRC)hResource );
		lpCopyItems = (sCOPYITEM *)LockResource( hLoadRes );
	*/
	if (smConfig.DebugMode && smConfig.szFile_Player[0]) {
		//��ڴ� ��Ų �ٲٱ� ����
		lstrcpy(lpCharInfo->szModelName, smConfig.szFile_Player);
		lpCharInfo->szModelName[0] = 0;
	}

	ZeroMemory(lpItems, sizeof(sITEM) * INVENTORY_MAXITEM);
	ZeroMemory(lpItems2, sizeof(sITEM) * INVENTORY_MAXITEM);

	lpRecItem = (BYTE*)&TransRecordData.Data;

	ChkCnt = 0;
	CopyItemCount = 0;
	BadItemCount = 0;

	// pluto ����Ʈ ���� ����  ĳ���� ������ ����
	if (TransRecordData.GameSaveInfo.dwTime_PrimeItem_MightofAwell)
	{
		if (lpCharInfo->Weight[0]<0 || lpCharInfo->Weight[0]>lpCharInfo->Weight[1] + 300) {
			WeightError = TRUE;
			//��ŷ �õ��� ���� �ڵ� �Ű�
			SendSetHackUser2(1900, lpCharInfo->Weight[0]);
		}
	}
	else if (TransRecordData.GameSaveInfo.dwTime_PrimeItem_MightofAwell2)
	{
		if (lpCharInfo->Weight[0]<0 || lpCharInfo->Weight[0]>lpCharInfo->Weight[1] + 500) {
			WeightError = TRUE;
			//��ŷ �õ��� ���� �ڵ� �Ű�
			SendSetHackUser2(1900, lpCharInfo->Weight[0]);
		}
	}
	else
	{
		if (lpCharInfo->Weight[0]<0 || lpCharInfo->Weight[0]>lpCharInfo->Weight[1]) {
			WeightError = TRUE;
			//��ŷ �õ��� ���� �ڵ� �Ű�
			SendSetHackUser2(1900, lpCharInfo->Weight[0]);
		}
	}

	for (cnt = 0; cnt < TransRecordData.ItemCount; cnt++) {

		lpsItemInfo = 0;
		//���� ����Ÿ �ص� ( Z/NZ ��� )
		DecodeCompress((BYTE*)lpRecItem, (BYTE*)&sRecordItem);
		/*
				//����Ÿ ���� ( Z/NZ ��� )
				EecodeCompress( (BYTE *)&sRecordItem , (BYTE *)szTestBuff , sizeof(sRECORD_ITEM) );

				if ( ((int *)szTestBuff)[0]!=((int *)lpRecItem)[0] ) {
					SetFlag = SetFlag;
				}
		*/

		SetFlag = TRUE;
		dwItemCode = sRecordItem.sItemInfo.CODE & sinITEM_MASK2;

		//������ ������ ����
		for (cnt2 = 0; cnt2 < TransRecordData.ThrowItemCount; cnt2++) {
			if (TransRecordData.ThrowItemInfo[cnt2].dwCode == sRecordItem.sItemInfo.CODE &&
				TransRecordData.ThrowItemInfo[cnt2].dwKey == sRecordItem.sItemInfo.ItemHeader.Head &&
				TransRecordData.ThrowItemInfo[cnt2].dwSum == sRecordItem.sItemInfo.ItemHeader.dwChkSum) {
				SetFlag = FALSE;
				break;
			}
		}

		/*
		#define sinWA1			0x01010000	//Axes
		#define sinWC1			0x01020000	//Claws
		#define sinWH1			0x01030000	//Hammer & So On
		#define sinWM1			0x01040000	//Magicial Stuffs
		#define sinWP1			0x01050000	//Poles & Spears
		#define sinWS1			0x01060000	//Shooters
		#define sinWS2			0x01070000	//Swords
		#define sinWT1			0x01080000	//Throwing Arms

		#define sinDA1			0x02010000	//Armor
		#define sinDB1			0x02020000	//Boots
		#define sinDG1			0x02030000	//Gloves
		#define sinDS1			0x02040000	//Shields
		*/
		//PostionError
		if (sRecordItem.ItemPosition > 3) {
			dwCode = sRecordItem.sItemInfo.CODE >> 24;
			if (dwCode == 1) {
				PostionError++;				//���� ����
			}
			dwCode = sRecordItem.sItemInfo.CODE >> 16;
			if (dwCode == 0x0201 || dwCode == 0x0204) {
				PostionError++;				//���� , ����
			}
		}
		if (sRecordItem.ItemPosition != 2 && CheckItemForm(&sRecordItem.sItemInfo) == FALSE) 
		{
			SetFlag = FALSE;
		//	SendSetHackUser2( 1950 , 0 );
		}

		if (!sRecordItem.sItemInfo.ItemHeader.Head || !sRecordItem.sItemInfo.ItemHeader.dwChkSum) {

			if (sRecordItem.sItemInfo.ItemName[0]) 
			{
				SetFlag = FALSE;
			//	SendSetHackUser2(1950, 0);
			}
		}

		if (TransRecordData.GameSaveInfo.TT_ServerID) {
			if ((sRecordItem.sItemInfo.CODE & sinITEM_MASK2) == sinBC1) {		//���� ������
				SetFlag = FALSE;
			}
		}


		//���� 0 ¥�� ����
		if ((sRecordItem.sItemInfo.CODE & sinITEM_MASK1) == (sinPM1 & sinITEM_MASK1)) {
			if (sRecordItem.sItemInfo.PotionCount <= 0) {
				SetFlag = FALSE;
			}
			else {
				//���� �˻��
				PotionCnt = AddRecordPotion(sRecordItem.sItemInfo.CODE, -sRecordItem.sItemInfo.PotionCount);
				if (PotionCnt < 0) {
					sRecordItem.sItemInfo.PotionCount += PotionCnt;
					SvrPotionError -= PotionCnt;		//������ ���� ���

					if (sRecordItem.sItemInfo.PotionCount <= 0) {
						SetFlag = FALSE;
					}
				}
			}
		}

		if (DeleteEventItem_TimeOut(&sRecordItem.sItemInfo) == TRUE && sRecordItem.ItemPosition != 2) {
			SetFlag = FALSE;

			CHATGAMEHANDLE->AddChatBoxTextEx(EChatColor::CHATCOLOR_Notice, mgItemTimeOut, sRecordItem.sItemInfo.ItemName);

			//	if ( sRecordItem.sItemInfo.CODE==(sinOR2|sin01) ) 
			if (sRecordItem.sItemInfo.CODE == (sinOR2 | sin01) ||  // ��������
				sRecordItem.sItemInfo.CODE == (sinOR2 | sin06) || sRecordItem.sItemInfo.CODE == (sinOR2 | sin07) || //Ŭ��ġ����
				sRecordItem.sItemInfo.CODE == (sinOR2 | sin08) || sRecordItem.sItemInfo.CODE == (sinOR2 | sin09) || //Ŭ��ġ����
				sRecordItem.sItemInfo.CODE == (sinOR2 | sin10) || sRecordItem.sItemInfo.CODE == (sinOR2 | sin11) || //Ŭ��ġ����
				sRecordItem.sItemInfo.CODE == (sinOR2 | sin12) || sRecordItem.sItemInfo.CODE == (sinOR2 | sin13) || //Ŭ��ġ����
				sRecordItem.sItemInfo.CODE == (sinOR2 | sin14) || sRecordItem.sItemInfo.CODE == (sinOR2 | sin15) || //Ŭ��ġ����
				sRecordItem.sItemInfo.CODE == (sinOR2 | sin16) || sRecordItem.sItemInfo.CODE == (sinOR2 | sin17) || //Ŭ��ġ����
				sRecordItem.sItemInfo.CODE == (sinOR2 | sin18) || sRecordItem.sItemInfo.CODE == (sinOR2 | sin19) || //Ŭ��ġ����
				sRecordItem.sItemInfo.CODE == (sinOR2 | sin20) || sRecordItem.sItemInfo.CODE == (sinOR2 | sin21) || //Ŭ��ġ����
				sRecordItem.sItemInfo.CODE == (sinOR2 | sin22) || sRecordItem.sItemInfo.CODE == (sinOR2 | sin23) || //Ŭ��ġ���� 
				sRecordItem.sItemInfo.CODE == (sinOR2 | sin24) || sRecordItem.sItemInfo.CODE == (sinOR2 | sin25) || //Ŭ��ġ����
				sRecordItem.sItemInfo.CODE == (sinOR2 | sin31) || sRecordItem.sItemInfo.CODE == (sinOR2 | sin32) || // ����� - ���� ���� �� �߰�(�ٺ�, ǻ��)
				sRecordItem.sItemInfo.CODE == (sinOR2 | sin27) || sRecordItem.sItemInfo.CODE == (sinOA1 | sin32) || //����� - ��Ÿ��, ��Ÿ�ƹķ� �߰�
				sRecordItem.sItemInfo.CODE == (sinOR2 | sin28) || sRecordItem.sItemInfo.CODE == (sinOA1 | sin33) || //����� - �̺�Ʈ ��, �̺�Ʈ �ƹķ� �߰�(7��)
				sRecordItem.sItemInfo.CODE == (sinOR2 | sin29) || sRecordItem.sItemInfo.CODE == (sinOA1 | sin34) || //����� - �̺�Ʈ ��, �̺�Ʈ �ƹķ� �߰�(1�ð�)
				sRecordItem.sItemInfo.CODE == (sinOR2 | sin30) || sRecordItem.sItemInfo.CODE == (sinOA1 | sin35) || //����� - �̺�Ʈ ��, �̺�Ʈ �ƹķ� �߰�(1��)
				sRecordItem.sItemInfo.CODE == (sinOA1 | sin36) || sRecordItem.sItemInfo.CODE == (sinOA1 | sin37) || // �庰 - ���� �����, ��Ʈ �ƹķ�
				sRecordItem.sItemInfo.CODE == (sinOR2 | sin33) ||																		// �庰 - ��Ʈ��

			  // ����� - �ڽ�Ƭ �߰�

				sRecordItem.sItemInfo.CODE == (sinSP1 | sin34) || // ����� - ȣ���� ĸ�� �߰�

				// �庰 - �ҿｺ�� ��� �����۵�
				sRecordItem.sItemInfo.CODE == (sinOR2 | sin36) ||
				sRecordItem.sItemInfo.CODE == (sinOR2 | sin37) ||
				sRecordItem.sItemInfo.CODE == (sinOR2 | sin38) ||
				sRecordItem.sItemInfo.CODE == (sinOR2 | sin39) ||
				sRecordItem.sItemInfo.CODE == (sinOR2 | sin40) ||
				sRecordItem.sItemInfo.CODE == (sinOA1 | sin39) ||
				sRecordItem.sItemInfo.CODE == (sinOA1 | sin40) ||
				sRecordItem.sItemInfo.CODE == (sinOA1 | sin41) ||
				sRecordItem.sItemInfo.CODE == (sinOA1 | sin42) ||

				// �庰 - ���� �̺�Ʈ �ƹķ�, ��
				sRecordItem.sItemInfo.CODE == (sinOA1 | sin38) ||
				sRecordItem.sItemInfo.CODE == (sinOR2 | sin34) ||
				sRecordItem.sItemInfo.CODE == (sinOR2 | sin35) ||

				// �庰 - ���� ����
				sRecordItem.sItemInfo.CODE == (sinDS1 | sin31) ||
				sRecordItem.sItemInfo.CODE == (sinDS1 | sin32) ||
				sRecordItem.sItemInfo.CODE == (sinDS1 | sin33) ||

				sRecordItem.sItemInfo.expireTime > 0

				)




			{
				memcpy(&sItem_Buff.sItemInfo, &sRecordItem.sItemInfo, sizeof(sITEMINFO));
				//	OverDay_Item_Delete( &sItem_Buff ); // ��¥�� ������������ ��������� �޽���â���� �����ش�
			}
		}

		if (SetFlag) {

			if (dwItemCode != sinPM1 && dwItemCode != sinPL1 && dwItemCode != sinPS1) {
				for (cnt3 = 0; cnt3 < ChkCnt; cnt3++) {

					if (sRecordItem.sItemInfo.ItemName[0] && CompareItems(&sRecordItem.sItemInfo, &lpChkItem[cnt3]->sItemInfo) == TRUE) {
						CopyItemCount++;
						break;
					}
				}
			}
			else {
				cnt3 = ChkCnt;
			}

			//2�� ���� ��
			if (!sRecordItem.sItemInfo.Temp0)
				sRecordItem.sItemInfo.Temp0 = sRecordItem.sItemInfo.ItemHeader.dwChkSum + sRecordItem.sItemInfo.CODE;

			if (cnt3 >= ChkCnt) {

				if (cnt < TransRecordData.ItemSubStart)
					lpSaveItem = &lpItems[sRecordItem.ItemCount];
				else
					lpSaveItem = &lpItems2[sRecordItem.ItemCount];


				if (sRecordItem.ItemPosition == -1) {
					//���콺�� ��� �ִ� ������
					if (lpMouseItem)
						lpSaveItem = lpMouseItem;
					else
						lpSaveItem = &lpItems2[INVENTORY_MAXITEM - 1];

					sRecordItem.ItemPosition = 0;
				}

				lpSaveItem->x = sRecordItem.x;
				lpSaveItem->y = sRecordItem.y;
				lpSaveItem->ItemPosition = sRecordItem.ItemPosition;
				lpSaveItem->Flag = TRUE;
				memcpy(&lpSaveItem->sItemInfo, &sRecordItem.sItemInfo, sizeof(sITEMINFO));

				if (dwItemCode != sinPM1 && dwItemCode != sinPL1 && dwItemCode != sinPS1)
					lpChkItem[ChkCnt++] = lpSaveItem;

			}
			/*
						if ( ReformItemCount<5 && lpsItemInfo ) {
						//if ( ReformItemCount<100 && lpsItemInfo ) {
							//�������� ������ ������ Ȯ��
							if ( lpsItemInfo->ItemName[0] ) {
								dwLastCheckItemTime = 0;
								SendCheckItemToServer( lpsItemInfo );
							}
						}
			*/
		}
		lpRecItem += ((int*)lpRecItem)[0];
	}

	//���� ���� ����Ÿ ���
	RestoreGameData(&TransRecordData.GameSaveInfo);

	//���� �ȵ� �� ����
	if (TransRecordData.GameSaveInfo.LastMoeny > 0) {
		CheckCharForm();	//ĳ���� ���� ���� Ȯ��
		lpCharInfo->Money = TransRecordData.GameSaveInfo.LastMoeny - 1;
		ReformCharForm();	//ĳ���� ���� ���� �ޱ�
	}
	/*
		//�����Ҽ� �ִµ�
		cnt = lpCharInfo->Level*5-40;
		if ( cnt<10 ) cnt=10;
		cnt *= 10000;
		if ( lpCharInfo->Money>cnt ) {
			SendSetHackUser2( 1960, lpCharInfo->Money );			//�� �ѵ� �ʰ�
			CheckCharForm();	//ĳ���� ���� ���� Ȯ��
			lpCharInfo->Money = cnt;
			ReformCharForm();	//ĳ���� ���� ���� �ޱ�
			SendSaveMoney();
		}
	*/

	if (CopyItemCount) {
		//���� �������� ������ ��� �Ű� 
		SendCopyItemUser(CopyItemCount);
	}
	if (BadItemCount) {
		//������ �������� ������ ��� �Ű�
		SendCopyItemUser(BadItemCount + 10000);
	}
	if (PostionError) {
		PostionError += 10000;
		SendSetHackUser2(1900, PostionError);		//��������� ���� ����
		SendSetHackUser2(99, 0);					//��������� ���� ����
	}

	if (SvrPotionError) {
		SvrPotionError += 20000;
		SendSetHackUser2(1900, SvrPotionError);	//��������� ���� ����
		SendSetHackUser2(99, 0);					//��������� ���� ����
	}



	//UnlockResource( hResource );
	CheckCharForm();
	cInvenTory.LoadItemInfo();
	CheckCharForm();

	//��ų ����
	RestoreSkill(&TransRecordData.GameSaveInfo.SkillInfo, TransRecordData.GameSaveInfo.dwLevelQuestLog);
	//�⺻���� ����� ����
	sinSkill.UseSkill[0].ShortKey = TransRecordData.GameSaveInfo.ShortKey_NormalAttack & 0xF;
	sinSkill.UseSkill[0].MousePosi = TransRecordData.GameSaveInfo.ShortKey_NormalAttack >> 4;

	// ����� - �ν��� ������(�����) ����
	if (TransRecordData.GameSaveInfo.wLifeBoosterUsing[0] && TransRecordData.GameSaveInfo.wLifeBoosterUsing[1]) {
		CSKILL->SetBoosterItem(sinBC1 + TransRecordData.GameSaveInfo.wLifeBoosterUsing[0], TransRecordData.GameSaveInfo.wLifeBoosterUsing[1] * 60);

		lpCurPlayer->dwLifeBoosterCode = sinBC1 + TransRecordData.GameSaveInfo.wLifeBoosterUsing[0];	// �ν��� ���� �ڵ�
		lpCurPlayer->dwLifeBoosterTime = dwPlayTime + (DWORD)TransRecordData.GameSaveInfo.wLifeBoosterUsing[1] * 1000; // �ν��� ��� �� ���� �ð� ����
	}
	// ����� - �ν��� ������(���) ����
	if (TransRecordData.GameSaveInfo.wManaBoosterUsing[0] && TransRecordData.GameSaveInfo.wManaBoosterUsing[1]) {
		CSKILL->SetBoosterItem(sinBC1 + TransRecordData.GameSaveInfo.wManaBoosterUsing[0], TransRecordData.GameSaveInfo.wManaBoosterUsing[1] * 60);

		lpCurPlayer->dwManaBoosterCode = sinBC1 + TransRecordData.GameSaveInfo.wManaBoosterUsing[0];	// �ν��� ���� �ڵ�
		lpCurPlayer->dwManaBoosterTime = dwPlayTime + (DWORD)TransRecordData.GameSaveInfo.wManaBoosterUsing[1] * 1000; // �ν��� ��� �� ���� �ð� ����
	}
	// ����� - �ν��� ������(�ٷ�) ����
	if (TransRecordData.GameSaveInfo.wStaminaBoosterUsing[0] && TransRecordData.GameSaveInfo.wStaminaBoosterUsing[1]) {
		CSKILL->SetBoosterItem(sinBC1 + TransRecordData.GameSaveInfo.wStaminaBoosterUsing[0], TransRecordData.GameSaveInfo.wStaminaBoosterUsing[1] * 60);

		lpCurPlayer->dwStaminaBoosterCode = sinBC1 + TransRecordData.GameSaveInfo.wStaminaBoosterUsing[0];	// �ν��� ���� �ڵ�
		lpCurPlayer->dwStaminaBoosterTime = dwPlayTime + (DWORD)TransRecordData.GameSaveInfo.wStaminaBoosterUsing[1] * 1000; // �ν��� ��� �� ���� �ð� ����
	}

	// �庰 - ��ų ������
	if (TransRecordData.GameSaveInfo.wSkillDelayUsing[0] && TransRecordData.GameSaveInfo.wSkillDelayUsing[1]) {
		CSKILL->SetSkillDelayItem(sinBC1 + TransRecordData.GameSaveInfo.wSkillDelayUsing[0], TransRecordData.GameSaveInfo.wSkillDelayUsing[1] * 60);

		lpCurPlayer->dwSkillDelayCode = sinBC1 + TransRecordData.GameSaveInfo.wSkillDelayUsing[0];
		lpCurPlayer->dwSkillDelayTime = dwPlayTime + (DWORD)TransRecordData.GameSaveInfo.wSkillDelayUsing[1] * 1000;
	}

	//���� ���� ����
	if (TransRecordData.GameSaveInfo.wForceOrbUsing[0] && TransRecordData.GameSaveInfo.wForceOrbUsing[1]) {
		// ����� - ���� ���� ���� �߰� 
		if (TransRecordData.GameSaveInfo.wForceOrbUsing[0] >= sin01 && TransRecordData.GameSaveInfo.wForceOrbUsing[0] <= sin16) // �Ϲ� ����
		{
			cInvenTory.SetForceOrb(sinFO1 + TransRecordData.GameSaveInfo.wForceOrbUsing[0], TransRecordData.GameSaveInfo.wForceOrbUsing[1]);
		}
		else if (TransRecordData.GameSaveInfo.wForceOrbUsing[0] >= sin21 && TransRecordData.GameSaveInfo.wForceOrbUsing[0] <= sin32) // ���� ����
		{
			cInvenTory.SetMagicForceOrb(sinFO1 + TransRecordData.GameSaveInfo.wForceOrbUsing[0], TransRecordData.GameSaveInfo.wForceOrbUsing[1]);
		}
		else if (TransRecordData.GameSaveInfo.wForceOrbUsing[0] >= sin35 && TransRecordData.GameSaveInfo.wForceOrbUsing[0] <= sin37) // ���� ���� ����
		{
			cInvenTory.SetBillingMagicForceOrb(sinFO1 + TransRecordData.GameSaveInfo.wForceOrbUsing[0], TransRecordData.GameSaveInfo.wForceOrbUsing[1]);
		}

		lpCurPlayer->dwForceOrbCode = sinFO1 + TransRecordData.GameSaveInfo.wForceOrbUsing[0];		//�������� ���� �ڵ�
		lpCurPlayer->dwForceOrbTime = dwPlayTime + (DWORD)TransRecordData.GameSaveInfo.wForceOrbUsing[1] * 1000;
		AssaParticle_ShelltomWeapon(lpCurPlayer, (DWORD)TransRecordData.GameSaveInfo.wForceOrbUsing[1] * 70, ((TransRecordData.GameSaveInfo.wForceOrbUsing[0]) >> 8) - 1);
	}

	//�����̾� ������ ���ð� ǥ��
	int	PrimeItem_Time;
	if (TransRecordData.GameSaveInfo.dwTime_PrimeItem_X2) {
		PrimeItem_Time = TransRecordData.GameSaveInfo.dwTime_PrimeItem_X2;
		if (PrimeItem_Time > 0) {
			chaPremiumitem.SetThirdEyesTime(PrimeItem_Time);
			switch (TransRecordData.GameSaveInfo.dwPrimeItem_PackageCode) {
			case PRIME_ITEM_PACKAGE_NONE:
				chaPremiumitem.SetUpKeepItem(nsPremiumItem::THIRD_EYES, chaPremiumitem.m_ThirdEyesTime, true, UpKeepItemName[0], 100);
				break;
			case PRIME_ITEM_PACKAGE_BRONZE:
				chaPremiumitem.SetUpKeepItem(nsPremiumItem::THIRD_EYES, chaPremiumitem.m_ThirdEyesTime, true, UpKeepItemName[0], 20);
				break;
			case PRIME_ITEM_PACKAGE_SILVER:
				chaPremiumitem.SetUpKeepItem(nsPremiumItem::THIRD_EYES, chaPremiumitem.m_ThirdEyesTime, true, UpKeepItemName[0], 100);
				break;
			case PRIME_ITEM_PACKAGE_GOLD:
				chaPremiumitem.SetUpKeepItem(nsPremiumItem::THIRD_EYES, chaPremiumitem.m_ThirdEyesTime, true, UpKeepItemName[0], 40);
				break;
			case PRIME_ITEM_PACKAGE_ULTRA:	// pluto ���丮�� ��Ű��
				chaPremiumitem.SetUpKeepItem(nsPremiumItem::THIRD_EYES, chaPremiumitem.m_ThirdEyesTime, true, UpKeepItemName[0], 50);
				break;
			default:	// ����� - ����ġ���� ����(50%)�����۰� �ߺ� ����� ���(PRIME_ITEM_PACKAGE_NONE_50_EXPUP , PRIME_ITEM_PACKAGE_NONE_100_EXPUP)
				chaPremiumitem.SetUpKeepItem(nsPremiumItem::THIRD_EYES, chaPremiumitem.m_ThirdEyesTime, true, UpKeepItemName[0], 100);
				break;
			}
		}
	}
	if (TransRecordData.GameSaveInfo.dwTime_PrimeItem_ExpUp) {
		PrimeItem_Time = TransRecordData.GameSaveInfo.dwTime_PrimeItem_ExpUp;
		if (PrimeItem_Time > 0) {
			chaPremiumitem.SetExpUpPotionTime(PrimeItem_Time);
			switch (TransRecordData.GameSaveInfo.dwPrimeItem_PackageCode) {
			case PRIME_ITEM_PACKAGE_NONE:
				chaPremiumitem.SetUpKeepItem(nsPremiumItem::EXPUP_POTION, chaPremiumitem.m_ExpUpPotionTime, true, UpKeepItemName[1], 30);
				break;
			case PRIME_ITEM_PACKAGE_BRONZE:
				chaPremiumitem.SetUpKeepItem(nsPremiumItem::EXPUP_POTION, chaPremiumitem.m_ExpUpPotionTime, true, UpKeepItemName[1], 10);
				break;
			case PRIME_ITEM_PACKAGE_SILVER:
				chaPremiumitem.SetUpKeepItem(nsPremiumItem::EXPUP_POTION, chaPremiumitem.m_ExpUpPotionTime, true, UpKeepItemName[1], 20);
				break;
			case PRIME_ITEM_PACKAGE_GOLD:
				chaPremiumitem.SetUpKeepItem(nsPremiumItem::EXPUP_POTION, chaPremiumitem.m_ExpUpPotionTime, true, UpKeepItemName[1], 30);
				break;
#ifdef _LANGUAGE_VEITNAM
			case PRIME_ITEM_PACKAGE_ULTRA:	//��Ʈ����û
				chaPremiumitem.SetUpKeepItem(nsPremiumItem::EXPUP_POTION, chaPremiumitem.m_ExpUpPotionTime, true, UpKeepItemName[1], 50);
				break;
#else
			case PRIME_ITEM_PACKAGE_ULTRA:
				chaPremiumitem.SetUpKeepItem(nsPremiumItem::EXPUP_POTION, chaPremiumitem.m_ExpUpPotionTime, true, UpKeepItemName[1], 40);
				break;
#endif

			case PRIME_ITEM_PACKAGE_BRONZE2:	// pluto ����� ��Ű��2
				chaPremiumitem.SetUpKeepItem(nsPremiumItem::EXPUP_POTION, chaPremiumitem.m_ExpUpPotionTime, true, UpKeepItemName[1], 10);
				break;
			case PRIME_ITEM_PACKAGE_SILVER2:	// pluto �ǹ� ��Ű��2
				chaPremiumitem.SetUpKeepItem(nsPremiumItem::EXPUP_POTION, chaPremiumitem.m_ExpUpPotionTime, true, UpKeepItemName[1], 20);
				break;
			case PRIME_ITEM_PACKAGE_GOLD2:	// pluto ��� ��Ű��2
				chaPremiumitem.SetUpKeepItem(nsPremiumItem::EXPUP_POTION, chaPremiumitem.m_ExpUpPotionTime, true, UpKeepItemName[1], 30);
				break;
			case PRIME_ITEM_PACKAGE_ULTRA2: // pluto ���丮�� ��Ű��2
				chaPremiumitem.SetUpKeepItem(nsPremiumItem::EXPUP_POTION, chaPremiumitem.m_ExpUpPotionTime, true, UpKeepItemName[1], 40);
				break;
			case PRIME_ITEM_PACKAGE_NONE_50_EXPUP: // ����� - ����ġ���� ����(50%) ������ ���� 
				chaPremiumitem.SetUpKeepItem(nsPremiumItem::EXPUP_POTION, chaPremiumitem.m_ExpUpPotionTime, true, UpKeepItemName[1], 50);
				break;
			case PRIME_ITEM_PACKAGE_NONE_100_EXPUP: // ����� - ����ġ���� ����(100%) ������ ���� 
				chaPremiumitem.SetUpKeepItem(nsPremiumItem::EXPUP_POTION, chaPremiumitem.m_ExpUpPotionTime, true, UpKeepItemName[1], 100);
				break;
			}
		}
	}

	if (TransRecordData.GameSaveInfo.dwTime_PrimeItem_VampCuspid) {
		PrimeItem_Time = TransRecordData.GameSaveInfo.dwTime_PrimeItem_VampCuspid;
		if (PrimeItem_Time > 0) {
			chaPremiumitem.SetVampiricCuspidTime(PrimeItem_Time);
			chaPremiumitem.SetUpKeepItem(nsPremiumItem::VAMPIRIC_CUS, chaPremiumitem.m_VampiricCuspidTime, true, UpKeepItemName[2]);
		}
	}
	if (TransRecordData.GameSaveInfo.dwTime_PrimeItem_ManaRecharg) {
		PrimeItem_Time = TransRecordData.GameSaveInfo.dwTime_PrimeItem_ManaRecharg;
		if (PrimeItem_Time > 0) {
			chaPremiumitem.SetManaRechargingPTime(PrimeItem_Time);
			chaPremiumitem.SetUpKeepItem(nsPremiumItem::MANA_RECHAR_P, chaPremiumitem.m_ManaRechargingPTime, true, UpKeepItemName[3]);
		}
	}

	// �庰 - ���Ǹ� Ŀ���� EX
	if (TransRecordData.GameSaveInfo.dwTime_PrimeItem_VampCuspid_EX) {
		PrimeItem_Time = TransRecordData.GameSaveInfo.dwTime_PrimeItem_VampCuspid_EX;
		if (PrimeItem_Time > 0) {
			chaPremiumitem.SetVampiricCuspidEXTime(PrimeItem_Time);
			chaPremiumitem.SetUpKeepItem(nsPremiumItem::VAMPIRIC_CUS_EX, chaPremiumitem.m_VampiricCuspidEXTime, true, UpKeepItemName[11]);
		}
	}

	/*
	if (TransRecordData.GameSaveInfo.dwPrimeItem_PackageCode ) {
		PrimeItem_Time = TransRecordData.GameSaveInfo.dwPrimeItem_PackageCode - GetPlayTime_T();
		if( PrimeItem_Time < 0 ){

			chaPremiumitem.SetThirdEyesTime( PrimeItem_Time );
			chaPremiumitem.SetUpKeepItem(nsPremiumItem::THIRD_EYES,chaPremiumitem.m_ThirdEyesTime,true,UpKeepItemName[0]);

			chaPremiumitem.SetExpUpPotionTime( PrimeItem_Time );
			chaPremiumitem.SetUpKeepItem(nsPremiumItem::EXPUP_POTION,chaPremiumitem.m_ExpUpPotionTime,true,UpKeepItemName[1]);
		}
	}
	*/

	// pluto ���� ���ེ ����
	if (TransRecordData.GameSaveInfo.dwTime_PrimeItem_ManaReduce)
	{
		PrimeItem_Time = TransRecordData.GameSaveInfo.dwTime_PrimeItem_ManaReduce;
		if (PrimeItem_Time > 0)
		{
			chaPremiumitem.SetManaReducePotionTime(PrimeItem_Time);
			switch (TransRecordData.GameSaveInfo.dwPrimeItem_PackageCode)
			{
			case PRIME_ITEM_PACKAGE_NONE:
				chaPremiumitem.SetManaReducePotionValue(30);	// pluto ���� ���ེ ���� 30% ����
				chaPremiumitem.SetUpKeepItem(nsPremiumItem::MANA_REDUCE_P, chaPremiumitem.m_ManaReducePotiontime, true, UpKeepItemName[5], 30);
				break;
			case PRIME_ITEM_PACKAGE_BRONZE2:
				chaPremiumitem.SetManaReducePotionValue(10);	// pluto ���� ���ེ ���� 10% ����
				chaPremiumitem.SetUpKeepItem(nsPremiumItem::MANA_REDUCE_P, chaPremiumitem.m_ManaReducePotiontime, true, UpKeepItemName[5], 10);
				break;
			case PRIME_ITEM_PACKAGE_SILVER2:
				chaPremiumitem.SetManaReducePotionValue(20);	// pluto ���� ���ེ ���� 20% ����
				chaPremiumitem.SetUpKeepItem(nsPremiumItem::MANA_REDUCE_P, chaPremiumitem.m_ManaReducePotiontime, true, UpKeepItemName[5], 20);
				break;
			case PRIME_ITEM_PACKAGE_GOLD2:
				chaPremiumitem.SetManaReducePotionValue(30);	// pluto ���� ���ེ ���� 30% ����
				chaPremiumitem.SetUpKeepItem(nsPremiumItem::MANA_REDUCE_P, chaPremiumitem.m_ManaReducePotiontime, true, UpKeepItemName[5], 30);
				break;
			case PRIME_ITEM_PACKAGE_ULTRA2:
				chaPremiumitem.SetManaReducePotionValue(40);	// pluto ���� ���ེ ���� 40% ����
				chaPremiumitem.SetUpKeepItem(nsPremiumItem::MANA_REDUCE_P, chaPremiumitem.m_ManaReducePotiontime, true, UpKeepItemName[5], 40);
				break;
			default:	// ����
				chaPremiumitem.SetManaReducePotionValue(30);	// pluto ���� ���ེ ���� 30% ����
				chaPremiumitem.SetUpKeepItem(nsPremiumItem::MANA_REDUCE_P, chaPremiumitem.m_ManaReducePotiontime, true, UpKeepItemName[5], 30);
				break;
			}
		}
	}
	// pluto ����Ʈ ���� ����
	if (TransRecordData.GameSaveInfo.dwTime_PrimeItem_MightofAwell)
	{
		PrimeItem_Time = TransRecordData.GameSaveInfo.dwTime_PrimeItem_MightofAwell;
		if (PrimeItem_Time > 0)
		{
			chaPremiumitem.SetMightOfAwellTime(PrimeItem_Time);
			chaPremiumitem.SetMightOfAwellWeight(300);
			chaPremiumitem.SetUpKeepItem(nsPremiumItem::MIGHT_OF_AWELL, chaPremiumitem.m_MightofAwellTime, true, UpKeepItemName[4], 300);
			//switch( TransRecordData.GameSaveInfo.dwPrimeItem_PackageCode )
			//{
			//	case PRIME_ITEM_PACKAGE_NONE:
			//		chaPremiumitem.SetUpKeepItem( nsPremiumItem::MIGHT_OF_AWELL, chaPremiumitem.m_MightofAwellTime, true, UpKeepItemName[4], 20);
			//		break;
			//	case PRIME_ITEM_PACKAGE_BRONZE2:
			//		chaPremiumitem.SetUpKeepItem( nsPremiumItem::MIGHT_OF_AWELL, chaPremiumitem.m_MightofAwellTime, true, UpKeepItemName[4], 10);
			//		break;
			//	case PRIME_ITEM_PACKAGE_SILVER2:
			//		chaPremiumitem.SetUpKeepItem( nsPremiumItem::MIGHT_OF_AWELL, chaPremiumitem.m_MightofAwellTime, true, UpKeepItemName[4], 20);
			//		break;
			//	case PRIME_ITEM_PACKAGE_GOLD2:
			//		chaPremiumitem.SetUpKeepItem( nsPremiumItem::MIGHT_OF_AWELL, chaPremiumitem.m_MightofAwellTime, true, UpKeepItemName[4], 30);
			//		break;
			//	case PRIME_ITEM_PACKAGE_ULTRA2:
			//		chaPremiumitem.SetUpKeepItem( nsPremiumItem::MIGHT_OF_AWELL, chaPremiumitem.m_MightofAwellTime, true, UpKeepItemName[4], 40);
			//		break;
			//}
		}
	}
	// pluto ����Ʈ ���� ����2
	if (TransRecordData.GameSaveInfo.dwTime_PrimeItem_MightofAwell2)
	{
		PrimeItem_Time = TransRecordData.GameSaveInfo.dwTime_PrimeItem_MightofAwell2;
		if (PrimeItem_Time > 0)
		{
			chaPremiumitem.SetMightOfAwellTime(PrimeItem_Time);
			chaPremiumitem.SetMightOfAwellWeight(500);
			chaPremiumitem.SetUpKeepItem(nsPremiumItem::MIGHT_OF_AWELL, chaPremiumitem.m_MightofAwellTime, true, UpKeepItemName[4], 500);
			//switch( TransRecordData.GameSaveInfo.dwPrimeItem_PackageCode )
			//{
			//	case PRIME_ITEM_PACKAGE_NONE:
			//		chaPremiumitem.SetUpKeepItem( nsPremiumItem::MIGHT_OF_AWELL, chaPremiumitem.m_MightofAwellTime, true, UpKeepItemName[4], 20);
			//		break;
			//	case PRIME_ITEM_PACKAGE_BRONZE2:
			//		chaPremiumitem.SetUpKeepItem( nsPremiumItem::MIGHT_OF_AWELL, chaPremiumitem.m_MightofAwellTime, true, UpKeepItemName[4], 10);
			//		break;
			//	case PRIME_ITEM_PACKAGE_SILVER2:
			//		chaPremiumitem.SetUpKeepItem( nsPremiumItem::MIGHT_OF_AWELL, chaPremiumitem.m_MightofAwellTime, true, UpKeepItemName[4], 20);
			//		break;
			//	case PRIME_ITEM_PACKAGE_GOLD2:
			//		chaPremiumitem.SetUpKeepItem( nsPremiumItem::MIGHT_OF_AWELL, chaPremiumitem.m_MightofAwellTime, true, UpKeepItemName[4], 30);
			//		break;
			//	case PRIME_ITEM_PACKAGE_ULTRA2:
			//		chaPremiumitem.SetUpKeepItem( nsPremiumItem::MIGHT_OF_AWELL, chaPremiumitem.m_MightofAwellTime, true, UpKeepItemName[4], 40);
			//		break;
			//}
		}
	}

	// pluto ��(�ؿ�)
	if (TransRecordData.GameSaveInfo.dwTime_PrimeItem_PhenixPet)
	{
		PrimeItem_Time = TransRecordData.GameSaveInfo.dwTime_PrimeItem_PhenixPet;
		if (PrimeItem_Time > 0)
		{
			chaPremiumitem.SetPhenixPetTime(PrimeItem_Time);
			chaPremiumitem.SetUpKeepItem(nsPremiumItem::PHENIX_PET, chaPremiumitem.m_PhenixPetTime, true, UpKeepItemName[6], 500);
			cPCBANGPet.PetKind = TRUE;
			cPCBANGPet.ShowPet();
		}
		else if (PrimeItem_Time < 0)
		{
			lpCharInfo->GravityScroolCheck[1] = 0;
			cPCBANGPet.ClosePet();
		}
	}

	// ����� - ���� ����� �� �߰�
	if (TransRecordData.GameSaveInfo.dwTime_PrimeItem_HelpPet)
	{
		PrimeItem_Time = TransRecordData.GameSaveInfo.dwTime_PrimeItem_HelpPet;
		if (PrimeItem_Time > 0)
		{
			chaPremiumitem.SetHelpPetTimeTime(PrimeItem_Time);
			chaPremiumitem.SetUpKeepItem(cHelpPet.PetKind + 7, chaPremiumitem.m_HelpPetTime, true, UpKeepItemName[cHelpPet.PetKind + 6], 500);
			//	chaPremiumitem.SetUpKeepItem( nsPremiumItem::HELP_PET, chaPremiumitem.m_HelpPetTime, true, UpKeepItemName[6], 500);

			for (int m = 0; m < SINUPKEEPITEM_MAX; m++)
			{
				if (chaPremiumitem.UpKeepItem[m].TGAImageNumber == nsPremiumItem::HELP_PET_TERRY)
				{
					lpCharInfo->GravityScroolCheck[1] = 1;
				}
			}

			cHelpPet.ShowPet();
		}
		else if (PrimeItem_Time < 0)
		{
			lpCharInfo->GravityScroolCheck[1] = 0;
			cHelpPet.ClosePet();
		}
	}

	else
	{
		lpCharInfo->GravityScroolCheck[1] = 0;
		cHelpPet.ClosePet(); // ����� - ����� �� ���� ���� ����
	}

	// ����� - �ٷ� ���ེ ����
	if (TransRecordData.GameSaveInfo.dwTime_PrimeItem_StaminaReduce)
	{
		PrimeItem_Time = TransRecordData.GameSaveInfo.dwTime_PrimeItem_StaminaReduce;
		if (PrimeItem_Time > 0)
		{
			chaPremiumitem.SetStaminaReducePotionTime(PrimeItem_Time);
			chaPremiumitem.SetStaminaReducePotionValue(30);	// ����� - �ٷ� ���ེ ���� 30% ����
			chaPremiumitem.SetUpKeepItem(nsPremiumItem::STAMINA_REDUCE_P, chaPremiumitem.m_StaminaReducePotiontime, true, UpKeepItemName[12], 30);

		}
	}

	if (TransRecordData.GameSaveInfo.dwTime_PrimeItem_StaminaReduce)
	{
		PrimeItem_Time = TransRecordData.GameSaveInfo.dwTime_PrimeItem_StaminaReduce;
		if (PrimeItem_Time > 0)
		{
			chaPremiumitem.SetStaminaReducePotionTime(PrimeItem_Time);
			chaPremiumitem.SetStaminaReducePotionValue(30);	// ����� - �ٷ� ���ེ ���� 30% ����
			chaPremiumitem.SetUpKeepItem(nsPremiumItem::STAMINA_REDUCE_P, chaPremiumitem.m_StaminaReducePotiontime, true, UpKeepItemName[12], 30);

		}
	}

	if (TransRecordData.GameSaveInfo.dwTime_PrimeItem_Mount)
	{
		PrimeItem_Time = TransRecordData.GameSaveInfo.dwTime_PrimeItem_Mount;

		if (PrimeItem_Time > 0)
		{
			chaPremiumitem.m_MountTime = PrimeItem_Time;
			chaPremiumitem.m_MountParam = TransRecordData.GameSaveInfo.dwPrimeItem_MountParam;
			chaPremiumitem.SetUpKeepItem(nsPremiumItem::MOUNT, chaPremiumitem.m_MountTime, true, "Montaria");
			cMountManager.AddMount(lpCurPlayer, static_cast<EMountID>(chaPremiumitem.m_MountParam), true, false);
		}
	}

	if (TransRecordData.GameSaveInfo.dwTime_Hat)
	{
		chaPremiumitem.ChangeBigHead(TransRecordData.GameSaveInfo.HatKind, TransRecordData.GameSaveInfo.dwTime_Hat);
	}

	return TRUE;
}


extern sITEM		InvenCostume;
extern int isItemCostume;

//������ ����Ÿ�� �����Ͽ� ������ ����
int rsRECORD_DBASE::SendRecordDataToServer(smWINSOCK* lpsmSock)
{
	int cnt;
	int PartTotal;
	char* lpData;
	int TotalLen;
	int len;

	TRANS_RECORD_DATAS TransRecord;
	TRANS_RECORD_DATA* lpTransRecord;

	lpTransRecord = &TransRecordData;
	lpData = (char*)lpTransRecord;

	cnt = 0;
	TotalLen = 0;
	PartTotal = lpTransRecord->size / TRANS_RECORD_LEN;
	if ((lpTransRecord->size % TRANS_RECORD_LEN) != 0) {
		if (lpTransRecord->size > TRANS_RECORD_LEN)
			PartTotal++;
	}

	while (1) {

		len = lpTransRecord->size - TotalLen;
		if (len > TRANS_RECORD_LEN) len = TRANS_RECORD_LEN;

		TransRecord.code = smTRANSCODE_RECORDDATA;
		TransRecord.size = len + 32;
		TransRecord.Count = cnt;
		TransRecord.Total = PartTotal;
		TransRecord.TransSize = len;

		memcpy(TransRecord.szData, &lpData[TotalLen], len);

		lpsmSock->Send((char*)&TransRecord, TransRecord.size, TRUE);
		cnt++;

		TotalLen += len;
		if (TotalLen >= lpTransRecord->size) break;
	}

	return TRUE;
}

//�� ��� ���Ϸ� ����
extern int RecordHackLogMoney(smCHAR_INFO* lpCharInfo);

#define	RECORD_ITEM_INFO_HEAD_SIZE		44



//������ ����Ÿ�� �����Ͽ� ����
int rsRECORD_DBASE::RecvRecordDataFromServer(TRANS_RECORD_DATAS* lpTransRecord)
{

	char* lpData;

	lpData = (char*)&TransRecordData;

	memcpy(&lpData[lpTransRecord->Count * TRANS_RECORD_LEN], lpTransRecord->szData, lpTransRecord->TransSize);
	TransDataBlock[lpTransRecord->Count] = 1;

	int cnt = 0;
	for (cnt = 0; cnt < lpTransRecord->Total; cnt++)
		if (!TransDataBlock[cnt]) break;

	if (cnt == lpTransRecord->Total && TransRecordData.code == smTRANSCODE_RECORDDATA) {
		//���� �Ϸ�
		TransRecordData.code = 0;
		return TRUE;
	}

	TransLastPartCount = lpTransRecord->Count;

	return FALSE;
}

#ifdef _W_SERVER
int	CheckPlayExpTable[15] = {
	40000,			//0
	100000,			//1
	300000,			//2
	500000,			//3
	800000,			//4
	1200000,		//5
	1600000,		//6
	2000000,		//7
	3000000,		//8
	4000000,		//9
	4000000,		//10
	6000000,		//11
	6000000,		//12
	8000000,		//13
	8000000			//14
};
#else
int	CheckPlayExpTable[15] = {
	0,		//0
	0,		//1
	0,		//2
	0,		//3
	0,		//4
	0,		//5
	0,		//6
	0,		//7
	0,		//8
	0,		//9
	0,		//10
	0,		//11
	0,		//12
	0,		//13
	0		//14
};
#endif


#include	"checkname.h"		//������ ����

//ĳ���Ͱ� ���� �ϴ��� ������ �˻��Ͽ� Ȯ��
int rsRECORD_DBASE::IsData(char* szName)
{
	char	szFile[256];
	WIN32_FIND_DATA		ffd;
	HANDLE				hFind;

	//���Ϻҷ�����
	//wsprintf( szFile , "userdata\\%s.dat" , szName );

	//CreateDirectory( szRecordUserDataDir , NULL );			//���丮 ����
	//CreateDirectory( szRecordUserBackupDataDir , NULL );			//���丮 ����

	if (lstrlen(szName) >= CHAR_NAME_MAXLEN) return TRUE;

	if (!c_CheckName(".\\CharacterNameList", szName)) return TRUE;    // <--- ��� �߰� �� �ʴϴ�.(������)

	GetUserDataFile(szName, szFile);

	hFind = FindFirstFile(szFile, &ffd);
	FindClose(hFind);
	if (hFind != INVALID_HANDLE_VALUE) {
		return TRUE;
	}

	return FALSE;
}








int CheckRecWaitData(char* szName)
{


	return FALSE;
}

//�ð� Ȯ���Ͽ� ����õ�
int rsTimeRecData()
{
	DWORD dwTime;

	dwTime = GetCurrentTime();

	if (hRecThread && (dwTime - dwLastRecDataTime) > 5000) {			//����õ����� 5�� ����
		ResumeThread(hRecThread);						//���� ������ Ȱ��ȭ
		return TRUE;
	}

	return FALSE;
}













int SaveCloseUserRecord(char* szUserName, int Level, int Exp, int Money)
{
	HANDLE	hFile;
	DWORD	dwAcess;
	DWORD	FileLength;
	char	szFileName[128];
	char	szBuff[256];
	int		TotalMoney = 0;


	wsprintf(szFileName, "UserRecord.txt");

	wsprintf(szBuff, "%s		����(%d)	����ġ(%d)	��(%d)\r\n", szUserName, Level, Exp, Money);

	hFile = CreateFile(szFileName, GENERIC_WRITE, FILE_SHARE_READ | FILE_SHARE_WRITE, NULL, OPEN_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
	if (hFile == INVALID_HANDLE_VALUE) return FALSE;

	FileLength = GetFileSize(hFile, NULL);
	SetFilePointer(hFile, FileLength, NULL, FILE_BEGIN);
	WriteFile(hFile, szBuff, lstrlen(szBuff), &dwAcess, NULL);
	CloseHandle(hFile);

	return TRUE;
}

//â�� �� ���
int SaveWareHouseRecord(char* szUserName, int Money, int Weight1, int Weight2)
{
	HANDLE	hFile;
	DWORD	dwAcess;
	DWORD	FileLength;
	char	szFileName[128];
	char	szBuff[256];
	int		TotalMoney = 0;


	wsprintf(szFileName, "UserRecord.txt");

	wsprintf(szBuff, "ID( %s )	â��(%d)	����( %d/%d )\r\n", szUserName, Money, Weight1, Weight2);

	hFile = CreateFile(szFileName, GENERIC_WRITE, FILE_SHARE_READ | FILE_SHARE_WRITE, NULL, OPEN_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
	if (hFile == INVALID_HANDLE_VALUE) return FALSE;

	FileLength = GetFileSize(hFile, NULL);
	SetFilePointer(hFile, FileLength, NULL, FILE_BEGIN);
	WriteFile(hFile, szBuff, lstrlen(szBuff), &dwAcess, NULL);
	CloseHandle(hFile);

	return TRUE;
}

/*
/////////////////////////////////////////// ���� ///////////////////////////////////////////
static int TempNewCharacterInit[4][6] =
{
	//JodCode, Strentch, Sprit, Talent, Defence, Health
	{2,        24,       8,     25,     18,      24}, //Mech
	{1,        28,       6,     21,     17,      27}, //Fighter
	{4,        26,       9,     20,     19,      25}, //PikeMan
	{3,        17,      11,     21,     27,      23}  //Archer
};

int TotalMoney =0;			//�� �ݾ� * 1000��


//������ ����Ÿ�� �����Ͽ� Ŭ���̾�Ʈ�� ����
int ConvertInitGameBetaData( char *szName )
{
	int cnt;
	char *lpData;
	char szFile[64];
	FILE *fp;
	int level;
	int	recFlag = 0;

	TRANS_RECORD_DATA TransRecordData;
	TRANS_RECORD_DATA *lpTransRecord;

	lpData = (char *)&TransRecordData;
	lpTransRecord = &TransRecordData;

	//���Ϻҷ�����
	wsprintf( szFile , "userdata\\%s.dat" , szName );
	//GetUserDataFile( szName , szFile );

	fp = fopen( szFile , "rb" );
	if ( fp ) {
		fread( lpTransRecord , sizeof(TRANS_RECORD_DATA) , 1, fp );
		fclose( fp );
	}
	else
		return FALSE;

	if ( lpTransRecord->smCharInfo.Level>=60 ||
		lpTransRecord->smCharInfo.Money>=10000000 ) {
		//����Ÿ ���
		SaveCloseUserRecord( szName , lpTransRecord->smCharInfo.Level , lpTransRecord->smCharInfo.Exp , lpTransRecord->smCharInfo.Money  );
	}

	//���� 20% �ٿ�
	level =  ( lpTransRecord->smCharInfo.Level * 80 )/100;
	if ( ((lpTransRecord->smCharInfo.Level * 80 )%100)>0 ) level ++;	//������ ����
	lpTransRecord->smCharInfo.Level = level;
	TotalMoney += lpTransRecord->smCharInfo.Money;						//�� ���� �հ�
	lpTransRecord->smCharInfo.Money = level * 1000;						//�� ���� * 1000

	//���� ����ġ ����
	lpTransRecord->smCharInfo.Next_Exp = GetNextExp( lpTransRecord->smCharInfo.Level );
	lpTransRecord->smCharInfo.Exp = GetNextExp( lpTransRecord->smCharInfo.Level-1 );

	switch( lpTransRecord->smCharInfo.JOB_CODE ) {
	case 1:
		lstrcpy( lpTransRecord->smCharInfo.szModelName , "char\\tmABCD\\B001.ini" );
		break;
	case 2:
		lstrcpy( lpTransRecord->smCharInfo.szModelName , "char\\tmABCD\\A001.ini" );
		break;
	case 3:
		lstrcpy( lpTransRecord->smCharInfo.szModelName , "char\\tmABCD\\D001.ini" );
		break;
	case 4:
		lstrcpy( lpTransRecord->smCharInfo.szModelName , "char\\tmABCD\\C001.ini" );
		break;
	}

	//�ɷ�ġ �ʱ�ȭ
	for( cnt=0;cnt<4;cnt++ ) {
		if ( TempNewCharacterInit[ cnt ][0]==(int)lpTransRecord->smCharInfo.JOB_CODE ) {
			lpTransRecord->smCharInfo.Strength	= TempNewCharacterInit[ cnt ][1];
			lpTransRecord->smCharInfo.Spirit	= TempNewCharacterInit[ cnt ][2];
			lpTransRecord->smCharInfo.Talent	= TempNewCharacterInit[ cnt ][3];
			lpTransRecord->smCharInfo.Dexterity	= TempNewCharacterInit[ cnt ][4];
			lpTransRecord->smCharInfo.Health	= TempNewCharacterInit[ cnt ][5];
			break;
		}
	}

	//ĳ���� ������Ʈ ���� ���Ӱ� �����Ѵ�
	ReformCharStatePoint( &lpTransRecord->smCharInfo );

	//ĳ���� ���� ����
	ReformCharForm( &lpTransRecord->smCharInfo );

	if ( lpTransRecord->GameSaveInfo.Head<dwRecordVersion &&
		lstrcmp( lpTransRecord->szHeader , szRecordHeader )!=0 ) {
		//������ ����Ÿ �߰� ĳ���� ���� �ڵ� ���� ���
		lpTransRecord->GameSaveInfo.dwChkSum_CharInfo = GetCharInfoCode( &lpTransRecord->smCharInfo );
	}
	//��ų �ʱ�ȭ
	ZeroMemory( &lpTransRecord->GameSaveInfo.SkillInfo , sizeof( RECORD_SKILL ) );

	lpTransRecord->ItemCount = 0;
	lpTransRecord->DataSize = 0;
	lpTransRecord->GameSaveInfo.LastMoeny = 0;
	lpTransRecord->ThrowItemCount = 0;

	GetUserDataFile( szName , szFile );

	lpTransRecord->size = sizeof(TRANS_RECORD_DATA)-(sizeof(sRECORD_ITEM)*RECORD_ITEM_MAX);

	fp = fopen( szFile , "wb" );
	if ( fp ) {
		fwrite( lpTransRecord , lpTransRecord->size , 1, fp );
		fclose( fp );
	}


	return TRUE;
}

int InitBetaUserData()
{
	HANDLE hFindHandle;
	WIN32_FIND_DATA	fd;
	char	szFindPath[64];
	char	szUserName[64];
	int		cnt,len;

	lstrcpy( szFindPath , "UserData\\*.dat" );

	hFindHandle = FindFirstFile( szFindPath , &fd );
	if ( hFindHandle!=INVALID_HANDLE_VALUE ) {
		while(1) {
			lstrcpy( szUserName , fd.cFileName );
			len = lstrlen( szUserName );

			for( cnt=0;cnt<len;cnt++ ) {
				if ( szUserName[cnt]=='.' ) {
					szUserName[cnt] = 0;
					break;
				}
			}

			//������ ����Ÿ�� �����Ͽ� Ŭ���̾�Ʈ�� ����
			ConvertInitGameBetaData( szUserName );

			//���� ���� ã��
			if ( FindNextFile( hFindHandle , &fd )==FALSE ) break;
		}
	}

	FindClose( hFindHandle );

	return TRUE;
}

int InitBetaUserInfo()
{
	HANDLE hFindHandle;
	WIN32_FIND_DATA	fd;
	char	szFindPath[64];
	char	szUserName[64];
	char	szSrcFile[128];
	char	szConvertFile[128];
	int		cnt,len;

	lstrcpy( szFindPath , "UserInfo\\*.dat" );

	hFindHandle = FindFirstFile( szFindPath , &fd );
	if ( hFindHandle!=INVALID_HANDLE_VALUE ) {
		while(1) {
			lstrcpy( szUserName , fd.cFileName );
			len = lstrlen( szUserName );

			for( cnt=0;cnt<len;cnt++ ) {
				if ( szUserName[cnt]=='.' ) {
					szUserName[cnt] = 0;
					break;
				}
			}

			//������ ����Ÿ�� �����Ͽ� Ŭ���̾�Ʈ�� ����
			//ConvertInitGameBetaData( szUserName );
			GetUserInfoFile( szUserName , szConvertFile );
			wsprintf( szSrcFile , "UserInfo\\%s" , fd.cFileName );

			CopyFile( szSrcFile , szConvertFile , FALSE );

			//���� ���� ã��
			if ( FindNextFile( hFindHandle , &fd )==FALSE ) break;
		}
	}

	FindClose( hFindHandle );

	return TRUE;
}

//������ ����Ÿ�� �����Ͽ� Ŭ���̾�Ʈ�� ����
//int ConvertInitGameBetaData( char *szName )

//Ŭ���� ��Ÿ �׽��� �ʱ�ȭ
int	InitCloseBetaUser()
{
	//����Ÿ ���弭�� ���丮 ����
	CreateDataServerDirectory();

	InitBetaUserData();
	InitBetaUserInfo();

	return TRUE;
}















*/








int PeekMonMsg();
int	MonQuit = 0;
HWND hDialog;
HWND hWndMon;
extern HINSTANCE hinst;								// current instance
//�޽��� ���׷��̵� ���� �޴�â ���ν���
LONG APIENTRY DialogProc(HWND hWnd, UINT messg, WPARAM wParam, LPARAM lParam);
LONG APIENTRY MonitorProc(HWND hWnd, UINT messg, WPARAM wParam, LPARAM lParam);

#define RECORD_MONEY_LIMIT		100000


int CheckUserData(char* szName)
{
	char* lpData;
	char szFile[256];
	FILE* fp;
	int	recFlag = 0;

	TRANS_RECORD_DATA TransRecordData;
	TRANS_RECORD_DATA* lpTransRecord;

	lpData = (char*)&TransRecordData;
	lpTransRecord = &TransRecordData;

	GetUserDataFile(szName, szFile);

	fp = fopen(szFile, "rb");
	if (fp) {
		fread(lpTransRecord, sizeof(TRANS_RECORD_DATA), 1, fp);
		fclose(fp);
	}
	else
		return FALSE;

	if (lpTransRecord->smCharInfo.Level >= 70 ||
		lpTransRecord->smCharInfo.Money >= RECORD_MONEY_LIMIT) {
		//����Ÿ ���
		SaveCloseUserRecord(szName, lpTransRecord->smCharInfo.Level, lpTransRecord->smCharInfo.Exp, lpTransRecord->smCharInfo.Money);
	}

	/*
		fp = fopen( szFile , "wb" );
		if ( fp ) {
			fwrite( lpTransRecord , lpTransRecord->size , 1, fp );
			fclose( fp );
		}
	*/

	return TRUE;
}

int CheckWareHouseData(char* szFile)
{
	TRANS_WAREHOUSE	TransWareHouse;
	sWAREHOUSE	WareHouse;
	FILE* fp;
	int cnt, len;
	char szName[256];

	fp = fopen(szFile, "rb");
	if (fp) {
		fread(&TransWareHouse, sizeof(TRANS_WAREHOUSE), 1, fp);
		fclose(fp);
	}
	else
		return FALSE;

	DecodeCompress((BYTE*)&TransWareHouse.Data, (BYTE*)&WareHouse);

	if (WareHouse.Weight[0] > WareHouse.Weight[1] || WareHouse.Money >= RECORD_MONEY_LIMIT) {

		lstrcpy(szName, szFile);
		len = lstrlen(szName);

		for (cnt = 0; cnt < len; cnt++) {
			if (szName[cnt] == '.') {
				szName[cnt] = 0;
				break;
			}
		}
		for (cnt = cnt; cnt >= 0; cnt--) {
			if (szName[cnt] == '\\') {
				cnt++;
				break;
			}
		}
		SaveWareHouseRecord(szName + cnt, WareHouse.Money, WareHouse.Weight[0], WareHouse.Weight[1]);
	}

	return TRUE;
}

int CheckUserDataFull()
{
	HANDLE hFindHandle;
	WIN32_FIND_DATA	fd;
	char	szFindPath[64];
	char	szUserName[64];
	char	szMsgBuff[256];
	int		cnt, len;
	int		UserCnt;
	int		CharCount = 0;

	for (UserCnt = 0; UserCnt < 256; UserCnt++) {

		wsprintf(szFindPath, "DataServer\\UserData\\%d\\*.dat", UserCnt);

		wsprintf(szMsgBuff, "ĳ���� Ȯ���� ( %d/255 ) - %d", UserCnt, CharCount);
		SetWindowText(GetDlgItem(hDialog, IDC_EDIT1), szMsgBuff);


		hFindHandle = FindFirstFile(szFindPath, &fd);
		if (hFindHandle != INVALID_HANDLE_VALUE) {
			while (1) {
				lstrcpy(szUserName, fd.cFileName);
				len = lstrlen(szUserName);

				for (cnt = 0; cnt < len; cnt++) {
					if (szUserName[cnt] == '.') {
						szUserName[cnt] = 0;
						break;
					}
				}

				CheckUserData(szUserName);
				CharCount++;

				PeekMonMsg();		//�޼��� �߰� ó��

				//���� ���� ã��
				if (FindNextFile(hFindHandle, &fd) == FALSE) break;
				if (MonQuit) break;
			}
		}
		FindClose(hFindHandle);
	}

	return TRUE;
}

int CheckWareHouseDataFull()
{
	HANDLE hFindHandle;
	WIN32_FIND_DATA	fd;
	char	szFindPath[64];
	char	szUserName[64];
	char	szUserPath[64];
	char	szMsgBuff[256];

	int		cnt, len;
	int		UserCnt;
	int		CharCount = 0;

	for (UserCnt = 0; UserCnt < 256; UserCnt++) {

		wsprintf(szFindPath, "DataServer\\WareHouse\\%d\\*.war", UserCnt);

		wsprintf(szMsgBuff, "�����ۺ����� Ȯ���� ( %d/255 ) - %d", UserCnt, CharCount);
		SetWindowText(GetDlgItem(hDialog, IDC_EDIT1), szMsgBuff);

		hFindHandle = FindFirstFile(szFindPath, &fd);
		if (hFindHandle != INVALID_HANDLE_VALUE) {
			while (1) {
				lstrcpy(szUserName, fd.cFileName);
				len = lstrlen(szUserName);

				for (cnt = 0; cnt < len; cnt++) {
					if (szUserName[cnt] == '.') {
						szUserName[cnt] = 0;
						break;
					}
				}

				wsprintf(szUserPath, "DataServer\\WareHouse\\%d\\%s", UserCnt, fd.cFileName);
				CheckWareHouseData(szUserPath);

				CharCount++;
				PeekMonMsg();		//�޼��� �߰� ó��

				//���� ���� ã��
				if (FindNextFile(hFindHandle, &fd) == FALSE) break;
				if (MonQuit) break;
			}
		}
		FindClose(hFindHandle);
	}

	return TRUE;
}

// ���� ����â â ����
HWND CreateDialogWnd();

//������ ��ϵ� ��ü ����Ÿ�� Ȯ���Ͽ� �ǽɰ��� ������ ã�´�
int	CheckServerRecordData()
{
	DeleteFile("UserRecord.txt");
	CreateDialogWnd();
	CheckUserDataFull();
	if (MonQuit) return FALSE;
	CheckWareHouseDataFull();
	if (MonQuit) return FALSE;

	return TRUE;
}


// ���� ����â â ����
HWND CreateDialogWnd()
{

	char* szAppName = "������������ - �����";
	WNDCLASS wndclass;


	wndclass.style = CS_HREDRAW | CS_VREDRAW | CS_DBLCLKS;
	wndclass.lpfnWndProc = MonitorProc;
	wndclass.cbClsExtra = 0;
	wndclass.cbWndExtra = 0;
	wndclass.hInstance = hinst;
	wndclass.hIcon = NULL;
	wndclass.hCursor = LoadCursor(NULL, IDC_ARROW);
	wndclass.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
	wndclass.lpszMenuName = NULL;
	wndclass.lpszClassName = szAppName;
	RegisterClass(&wndclass);

	hWndMon = CreateWindow(szAppName, szAppName,
		WS_OVERLAPPEDWINDOW | WS_POPUP | WS_EX_TOPMOST, CW_USEDEFAULT,
		CW_USEDEFAULT, 320, 240, NULL, NULL,
		hinst, NULL);


	ShowWindow(hWndMon, SW_HIDE);
	UpdateWindow(hWndMon);


	hDialog = CreateDialog(hinst, "IDD_DIALOG", hWndMon, (DLGPROC)DialogProc);
	/*
		int x,y;
		x = (GetSystemMetrics( SM_CXSCREEN )/2) - 128;
		y = (GetSystemMetrics( SM_CYSCREEN )/2) - 90 ;
		SetWindowPos( hDialog , 0, x, y, 0, 0, SWP_NOSIZE|SWP_NOZORDER );
	*/
	ShowWindow(hDialog, SW_SHOW);
	UpdateWindow(hDialog);

	return hDialog;
}

//�޽��� ���׷��̵� ���� �޴�â ���ν���
LONG APIENTRY DialogProc(HWND hWnd, UINT messg, WPARAM wParam, LPARAM lParam)
{

	//char szTemp[128];

	switch (messg)
	{
	case WM_INITDIALOG:
		break;

	case WM_CLOSE:
		DestroyWindow(hWnd);
		break;

	case WM_PAINT:
		break;

	case WM_COMMAND:
		switch (LOWORD(wParam)) {
		case IDOK:
			SendMessage(hWnd, WM_CLOSE, 0, 0);
			MonQuit = TRUE;
			break;
		}

		break;

	default:
		return FALSE;
		break;
	}
	return FALSE;
}

LONG APIENTRY MonitorProc(HWND hWnd, UINT messg, WPARAM wParam, LPARAM lParam)
{

	//char szTemp[128];

	switch (messg)
	{
	case WM_CREATE:
		break;

	default:
		return DefWindowProc(hWnd, messg, wParam, lParam);
		break;

	}
	return FALSE;
}

int PeekMonMsg()
{
	MSG msg;

	while (1) {
		if (PeekMessage(&msg, 0, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		else
			break;
	}
	return TRUE;
}








///////////////////// ĳ���� ��� ����Ÿ�� ���� //////////////////////


static char decode[512];
static char line[512];

static char* GetWord(char* q, char* p)
{

	while ((*p == 32) || (*p == 9)) // SPACE or TAB or ':'�� ���� ��Ŵ
	{
		p++;
	}

	while ((*p != 32) && (*p != 9)) // SPACE or TAB
	{
		if (*p == '\n' || *p == '\r') break;
		*q++ = *p++;
	}
	*q++ = 0;	// end of one string, put Null character

	return p;
}






/*
static int GetUserInfoFile( char *szID , char *szFileName )
{
	//wsprintf( szFileName , "%s\\%s.dat" , szRecordUserInfoDir , szID );

	if ( szID[4]==0 && szID[3]>='0' && szID[3]<='9' && (
		((szID[0]=='c' || szID[0]=='C') && (szID[1]=='o' || szID[1]=='O') && (szID[2]=='m' || szID[2]=='M')) ||
		((szID[0]=='l' || szID[0]=='L') && (szID[1]=='p' || szID[1]=='P') && (szID[2]=='t' || szID[2]=='T')) )
		) {
		wsprintf( szFileName , "DataServer\\��%s\\%d\\%s.dat" , szRecordUserInfoDir , GetUserCode(szID) , szID );
		return TRUE;
	}

	if ( szID[3]==0 &&
		((szID[0]=='p' || szID[0]=='P') && (szID[1]=='r' || szID[1]=='R') && (szID[2]=='n' || szID[2]=='N')) ||
		((szID[0]=='c' || szID[0]=='C') && (szID[1]=='o' || szID[1]=='O') && (szID[2]=='n' || szID[2]=='N'))
		) {
		wsprintf( szFileName , "DataServer\\��%s\\%d\\%s.dat" , szRecordUserInfoDir , GetUserCode(szID) , szID );
		return TRUE;
	}

	wsprintf( szFileName , "DataServer\\%s\\%d\\%s.dat" , szRecordUserInfoDir , GetUserCode(szID) , szID );

	return TRUE;
}

static int GetUserDataFile( char *szName , char *szFileName )
{
	//wsprintf( szFileName , "%s\\%s.dat" , szRecordUserDataDir , szName );
	wsprintf( szFileName , "DataServer\\%s\\%d\\%s.dat" , szRecordUserDataDir , GetUserCode(szName) , szName );

	return TRUE;
}
*/


//ĳ���� ���� ���Ͽ��� �ص��Ͽ� �����Ѵ�
int RestoreBackupData(char* szListFile, char* BackupPath)
{

	FILE* fp, * fp2, * fp3;
	char strBuff[256];
	char* p;
	WIN32_FIND_DATA		ffd;
	HANDLE				hFind;
	sPLAY_USER_DATA		sPlayUserData;
	int cnt;
	int flag;

	char szInfoFile[256];
	char szSrcDataFile[256];
	char szDestDataFile[256];
	char szLogBuff[256];
	char szFile[256];

	fp = fopen(szListFile, "rb");
	if (fp == NULL) return FALSE;

	fp3 = fopen("BackupData.log", "wb");
	if (fp3 == NULL) {
		fclose(fp);
		return FALSE;
	}

	CreateDirectory("BackupUser", 0);

	while (!feof(fp))//  feof: file end���� �о�� 
	{
		if (fgets(line, 255, fp) == NULL)	break;

		p = GetWord(decode, line);

		///////////////// �̸� ///////////////////////
		if (decode[0]) {
			p = GetWord(strBuff, p);

			if (strBuff[0]) {

				///////////////// ��� ���� ///////////////////
				GetUserInfoFile(decode, szInfoFile);
				GetUserDataFile(strBuff, szDestDataFile);
				lstrcpy(szSrcDataFile, BackupPath);
				lstrcat(szSrcDataFile, szDestDataFile);
				///////////////////////////////////////////////

				flag = TRUE;

				hFind = FindFirstFile(szSrcDataFile, &ffd);
				FindClose(hFind);
				if (hFind != INVALID_HANDLE_VALUE) {
					//�ҽ� ����Ÿ ���� ����
					fp2 = fopen(szInfoFile, "rb");
					if (fp2) {
						fread(&sPlayUserData, sizeof(sPLAY_USER_DATA), 1, fp2);
						fclose(fp2);

						for (cnt = 0; cnt < sPLAY_CHAR_MAX; cnt++) {
							if (sPlayUserData.szCharName[cnt][0]) {
								if (lstrcmpi(sPlayUserData.szCharName[cnt], strBuff) == 0) {
									break;
								}
							}
						}

						if (cnt >= sPLAY_CHAR_MAX) {
							//�����ȿ� ĳ���� ����
							hFind = FindFirstFile(szDestDataFile, &ffd);
							FindClose(hFind);
							if (hFind == INVALID_HANDLE_VALUE) {
								//���� ĳ���� ���� ���� �ʴ´� . ������ ĳ�� ����
								for (cnt = 0; cnt < sPLAY_CHAR_MAX; cnt++) {
									if (!sPlayUserData.szCharName[cnt][0]) {
										lstrcpy(sPlayUserData.szCharName[cnt], strBuff);
										fp2 = fopen(szInfoFile, "wb");
										if (fp2) {
											fwrite(&sPlayUserData, sizeof(sPLAY_USER_DATA), 1, fp2);
											fclose(fp2);
										}
										break;
									}
								}
							}
							else {
								flag = FALSE;
								wsprintf(szLogBuff, "%s (%s) -> ���� ( �ű�ĳ�������� )\r\n", decode, strBuff);
								fwrite(szLogBuff, lstrlen(szLogBuff), 1, fp3);
							}
						}

						if (flag) {
							//���� ����

							wsprintf(szFile, "BackupUser\\%s.dat", strBuff);
							CopyFile(szDestDataFile, szFile, TRUE);

							CopyFile(szSrcDataFile, szDestDataFile, FALSE);

							wsprintf(szLogBuff, "%s (%s) -> ����\r\n", decode, strBuff);
							fwrite(szLogBuff, lstrlen(szLogBuff), 1, fp3);
						}
					}
					else {
						wsprintf(szLogBuff, "%s (%s) -> ���� ( �����̾��� )\r\n", decode, strBuff);
						fwrite(szLogBuff, lstrlen(szLogBuff), 1, fp3);
					}
				}
				else {
					wsprintf(szLogBuff, "%s (%s) -> ���� ( �ҽ����Ͼ��� )\r\n", decode, strBuff);
					fwrite(szLogBuff, lstrlen(szLogBuff), 1, fp3);
				}
			}
		}
	}


	fclose(fp3);
	fclose(fp);

	return TRUE;
}


/*
	DWORD	dwLoginServerIP;		//�α����� ������ IP
	DWORD	dwLoginServerSafeKey;	//�α����� �������� ���� ����Ű
*/
#ifdef _W_SERVER

#ifdef _LANGUAGE_ENGLISH
#ifndef _LANGUAGE_PHILIPIN
#define	LOGIN_SERVER_KEY		0x512234a5		//����
#define	LOGIN_SERVER_SHIFT		6
#else 
#define	LOGIN_SERVER_KEY		0x542634c3
#define	LOGIN_SERVER_SHIFT		4
#endif
#endif

//�߱�
#ifdef _LANGUAGE_CHINESE
#define	LOGIN_SERVER_KEY		0x512234a5
#define	LOGIN_SERVER_SHIFT		6
#endif

#ifdef _LANGUAGE_BRAZIL
#define	LOGIN_SERVER_KEY		0x532254a5
#define	LOGIN_SERVER_SHIFT		5
#endif

#ifdef _LANGUAGE_ARGENTINA		//�Ƹ���Ƽ�� (����� ���ð� �ӽ� ����)
#define	LOGIN_SERVER_KEY		0x532254a5
#define	LOGIN_SERVER_SHIFT		5
#endif

#ifdef _LANGUAGE_VEITNAM
#define	LOGIN_SERVER_KEY		0x442934c3
#define	LOGIN_SERVER_SHIFT		3
#endif

#ifdef _LANGUAGE_JAPANESE
#define	LOGIN_SERVER_KEY		0x542634c5
#define	LOGIN_SERVER_SHIFT		6
/*
#define	LOGIN_SERVER_KEY		0x542634c3
#define	LOGIN_SERVER_SHIFT		4
*/
#endif

#ifdef _LANGUAGE_THAI
#define	LOGIN_SERVER_KEY		0x533734c3
#define	LOGIN_SERVER_SHIFT		7
#endif


//�α��� ���� ���� Ű ����
DWORD	rsGetLoginSafeKey(smCHAR_INFO* lpCharInfo, DWORD dwSpdSumCode)
{
	DWORD	dwCode = dwSpdSumCode;
	DWORD	dwCode2 = lpCharInfo->dwObjectSerial ^ LOGIN_SERVER_KEY;

	if (!dwCode)
		dwCode = GetSpeedSum(lpCharInfo->szName);

	dwCode = dwCode * ((dwCode2 >> LOGIN_SERVER_SHIFT) | (dwCode2 << LOGIN_SERVER_SHIFT));

	return	dwCode;
}

//�α��� ���� ����Ű ����
int rsSet_LoginServerSafeKey(smCHAR_INFO* lpCharInfo)
{

	lpCharInfo->dwLoginServerSafeKey = rsGetLoginSafeKey(lpCharInfo);

	return TRUE;
}

//�α��� ���� ����Ű Ȯ��
int	rsCheck_LoginServerSafeKey(smCHAR_INFO* lpCharInfo, DWORD dwSpdSumCode)
{
	if (lpCharInfo->dwLoginServerSafeKey == rsGetLoginSafeKey(lpCharInfo, dwSpdSumCode))
		return TRUE;

	return FALSE;
}

#else
DWORD	rsGetLoginSafeKey(smCHAR_INFO* lpCharInfo, DWORD dwSpdSumCode)
{
	return TRUE;
}
int rsSet_LoginServerSafeKey(smCHAR_INFO* lpCharInfo)
{
	return TRUE;
}
int	rsCheck_LoginServerSafeKey(smCHAR_INFO* lpCharInfo, DWORD dwSpdSumCode)
{
	return TRUE;
}
#endif







