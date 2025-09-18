
#include "smlib3d\\smd3d.h"

#include "smwsock.h"
#include "character.h"
#include "playmain.h"

#include "fileread.h"


#include "netplay.h"

#include "sinbaram\\sinlinkheader.h"


#include "field.h"
#include "effectsnd.h"

#include "record.h"
#include "playsub.h"
#include "skillsub.h"
#include "damage.h"

#include "tjboy\\clanmenu\\tjclanDEF.h"
#include "tjboy\\clanmenu\\tjclan.h"
#include "tjboy\\clanmenu\\cE_CViewClanInfo.h"

#include "language.h"


#include "damage.h"
#include "AreaServer.h"

#include "srcserver\onserver.h"

extern HWND hwnd;

//�ʵ�� �ε�
int LoadFieldMap( int PosNum , sFIELD *lpField , smSTAGE3D *lpStage );


//���� ��Ʈ Ŭ������!
smSTAGE3D		*smStage = 0;
smSTAGE3D		*smGameStage[2] = { 0,0 };
sFIELD			*StageField[2] = { 0,0 };


rsRECORD_DBASE	rsRecorder;					//������ ���ӵ���Ÿ �����ġ

char szGameStageName[2][64];
DWORD			dwPlayTime=0;					//������ ������ �ð� ( �÷��� �� )
DWORD			dwMemError=8080;				//�޸� ���� Ȯ�� �ڵ�

int	smStageCount = 0;
int SkipNextField = 0;				//���� �ʵ�� �Ѿ

int	NightDayTime=0;					//�㳷 ����

int invPlayerArmor = 0;

DWORD	dwBattleTime =0;				//�ֱ� ���� �ð�
DWORD	dwBattleQuitTime =0;			//������ ���� �Ϸ� �Ҷ�
DWORD	dwCloseBoxTime = 0;				//�۾�â ���� �޼���

int		RestartPlayCount = 0;					//����� ���� ���� ī��Ʈ

DWORD SkillFalconPoint;					//���� ��ų ����Ʈ �����

int InvArmorFileCode[] =
{ 0 ,9,1, 5 };

int	DarkLevel = 0;					//��� ��
int	BackColor_R = 0;				//���� R
int	BackColor_G = 0;				//���� G
int	BackColor_B = 0;				//���� B

int	BackColor_mR = 0;				//���� ���氪 R
int	BackColor_mG = 0;				//���� ���氪 G
int	BackColor_mB = 0;				//���� ���氪 B

int	DarkLevel_Fix = 0;				//��� �� ����

int	DarkLightRange = 180*fONE;		//��οﶧ ���� ����

DWORD	dwGameWorldTime = 0;			//������ ����ð�
DWORD	dwGameHour = 12;					//������ ��
DWORD	dwGameMin  = 0;					//������ ��
DWORD	dwGameTimeOffset = 0;

int DarkLight = 0;

//���� ����
int WeatherMode = 0;
int Thunder = 0;

//PK���
int	PkMode = 0;

int DispApp_SkillPoint = 0;			//������ �ð����� ��ų ����Ʈ

int rcnt2;

int modelX = 255;
int modelZ = 512;
int wflag = 0;
int wrad = 0;

DWORD	UseEtherCoreCode = 0;			//��Ƽ�� �ھ� ���

int	RecordFailCount =0;				//���� ���� ī����

//���� �޾����� ȸ�� ī����
int	Record_BlockCount = 0;
int	Record_DefenceCount = 0;
int Record_RecvDamageCount = 0;
int Record_TotalRecvDamageCount = 0;


//���� ���콺 ������
DWORD	AutoMouse_LastCheckTime = 0;
DWORD	AutoMouse_StartCheckTime = 0;
int		AutoMouse_WM_Count = 0;
int 	AutoMouse_Distance = 0;
int		AutoMouse_Attack_Count = 0;

//ȭ��
//smPAT3D *PatTest;

//ȭ��
smPAT3D *PatArrow;
//���� ����Ʈ
smPAT3D *PatEffectShield =0;
//����ũ���� ����Ʈ
smPAT3D *PatSparkShield =0;
//��������ҷ��̼�
smPAT3D *PatDivineShield =0;
//���鸮 ����
smPAT3D *PatGodlyShield =0;
//����ĳ�� �հ�
smPAT3D *PatCrown =0;

//�׸���
smPAT3D *PatShadow[SHADOW_PAT_MAX] = { 0,0,0,0 };

//######################################################################################
//�� �� �� : �� �� ��
smPAT3D *PatIceFoot[ ICE_FOOT_PAT_MAX ];
//######################################################################################

int	Moving_DblClick = 0;		//���콺 �̵� ýũ ���� Ŭ��
POINT3D	MousePos_DblClick;

POINT3D	TracePos_DblClick;
int TraceMode_DblClick = 0;

int	ActionGameMode = 0;	//�׼ǰ��� ���


//smCHAR	chrPlayer;
smCHAR		*lpCurPlayer = 0;

DWORD	dwRotPlayDelayTime = 0;			//���ΰ� ������ ���� ������

/*
//ȸ�� �÷��̾� ������ ����
smCHAR *SelectRotPlayer( smCHAR *lpCurrentChar );
//ȸ�� �÷��̾� ������ ����
int	CloseRotPlayer();
//ȸ�� �÷��̾� ������ �ʱ�ȭ
smCHAR *InitRotPlayer();

lpCurPlayer = InitRotPlayer();

*/


scITEM	scItems[ DISP_ITEM_MAX ];			//ITEM

smCHAR	chrOtherPlayer[OTHER_PLAYER_MAX];

smCHAR_INFO	smCharInfo_Back;			//NPC ��ġ�� �⺻ ����Ÿ �ӽ� ����


int	MatEachBox;				//�� Ȯ�� �׵θ� �׸� ��Ʈ����
int	MatEachMenuBox;			//�޴� ��ư �׵θ�
int MatEnergyBox[2];		//������ ��Ʈ����
int MatLight[4];				//���� �� �̹��� ��Ʈ���� //glow.bmp

int	MatEachTradeButton[2];	//�޴� ������ ��ȯ ��ư 
int MatMonBroodImage[8];	//���� ���� �̹���

//���� ȸ�� ���ప
smTRANS_COMMAND	sPartyPosion;
DWORD			dwPartyPosionTime;

void*	lpDDS_ParTradeButton[4][2];			//�޴��� Ʈ���̵� ��ư
void*	lpDDS_ParTradeToolTip[4];			//�޴��� Ʈ���̵� ����


//�Ҳ� �ִϸ��̼�
char *szFlame[8] = {
	"image\\flame1.bmp",
	"image\\flame2.bmp",
	"image\\flame3.bmp",
	"image\\flame4.bmp",
	"image\\flame5.bmp",
	"image\\flame6.bmp",
	"image\\flame7.bmp",
	"image\\flame8.bmp"
};

char *szShine[] = {
	"image\\shine0.bmp",
	"image\\shine2.bmp",
	"image\\shine4.bmp",
	"image\\shine6.bmp",
	"image\\shine8.bmp",
	""
};

char *szBlood1[] = {
	"image\\blood\\b1_001.tga",
	"image\\blood\\b1_002.tga",
	"image\\blood\\b1_003.tga",
	"image\\blood\\b1_004.tga"
};

char *szBlood2[] = {
	"image\\blood\\b2_001.tga",
	"image\\blood\\b2_002.tga",
	"image\\blood\\b2_003.tga",
	"image\\blood\\b2_004.tga"
};


char *szShadowImageFile = "image\\bshadow.bmp";
//char *szShadowImageFile = "image\\shadow.tga";

//######################################################################################
//�� �� �� : �� �� ��
char *g_IceFootImageFileBuff[ ICE_FOOT_PAT_MAX ] =
{
	"image\\mk-r.tga",
	"image\\mk-l.tga",
};
//######################################################################################



//��� �δ� �ʱ�ȭ
void InitStageLoader()
{
	szGameStageName[0][0] = 0;
	szGameStageName[1][0] = 0;
	smGameStage[0]=0;
	smGameStage[1]=0;
}

//����� �о� �´�
smSTAGE3D *LoadStageFromField( sFIELD *lpField , sFIELD *lpSecondField )
{
	smSTAGE3D *lpstg;
	char *szStageFile;
	int cnt;
	int	Bip;
	char	szBuff[128];

	szStageFile = lpField->szName;

	if ( lpField==StageField[0] ) return smGameStage[0];
	if ( lpField==StageField[1] ) return smGameStage[1];

	lpstg = new smSTAGE3D;

	// ����Ʈ ����
	lpstg->VectLight.x = smConfig.MapLightVector.x;
	lpstg->VectLight.y = smConfig.MapLightVector.y;
	lpstg->VectLight.z = smConfig.MapLightVector.z;

	lpstg->Bright		= smConfig.MapBright;
	lpstg->Contrast		= smConfig.MapContrast;

	//����� �� �����忡 ���Ͽ� �ε� �Ѵ�
	AddLoaderStage( lpstg , szStageFile );

	if ( !lpstg->StageObject ) {
		//�˼� ���� ����
		//Ŭ���̾�Ʈ �α� ���� ���
		wsprintf( szBuff , "Stage Loading Error ( %s )",szStageFile );
		Record_ClinetLogFile( szBuff );
		delete lpstg;
		return NULL;
	}

	//���� ������Ʈ �߰�
	for( cnt=0;cnt<lpField->StgObjCount;cnt++ ) {
		Bip = lpField->GetStageObjectName( cnt , szBuff );
		if ( szBuff[0] ) {
			if ( Bip )
				lpstg->StageObject->AddObjectFile( szBuff , szBuff );
			else
				lpstg->StageObject->AddObjectFile( szBuff );
		}
	}

	if ( lpSecondField && lpSecondField==StageField[0] ) {
		if ( smGameStage[1] ) delete smGameStage[1];
		smGameStage[1] = lpstg;
		StageField[1] = lpField;
		LoadFieldMap( 1, lpField , lpstg );				//�ʵ�� �ε�
	}
	else {
		if ( !lpSecondField || lpSecondField==StageField[1] ) {
			if ( smGameStage[0] ) delete smGameStage[0];
			smGameStage[0] = lpstg;
			StageField[0] = lpField;
			LoadFieldMap( 0, lpField , lpstg );			//�ʵ�� �ε�
		}
	}


	if ( StageField[0] ) lstrcpy( szGameStageName[0] , StageField[0]->szName );
	if ( StageField[1] ) lstrcpy( szGameStageName[1] , StageField[1]->szName );


	DWORD	dwTime = GetCurrentTime();

	if ( dwLastRecvGameServerTime && dwLastRecvGameServerTime<dwTime ) dwLastRecvGameServerTime=dwTime;
	if ( dwLastRecvGameServerTime2 && dwLastRecvGameServerTime2<dwTime ) dwLastRecvGameServerTime2 = dwTime;
	if ( dwLastRecvGameServerTime3 && dwLastRecvGameServerTime3<dwTime ) dwLastRecvGameServerTime3 = dwTime;
	if ( dwLastRecvGameServerTime4 && dwLastRecvGameServerTime4<dwTime ) dwLastRecvGameServerTime4 = dwTime;

	if ( AreaServerMode ) {
		//���� ���� �����Ȯ�� �ð� ����
		if ( lpWSockServer_Area[0] ) lpWSockServer_Area[0]->dwDeadLockTime = dwTime;
		if ( lpWSockServer_Area[1] ) lpWSockServer_Area[1]->dwDeadLockTime = dwTime;
	}

	return lpstg;
}


//����� �о� �´� 
smSTAGE3D *LoadStageFromField2( sFIELD *lpField , sFIELD *lpSecondField )
{
	smSTAGE3D *lpstg;
	char *szStageFile;
	int cnt;
	int Bip;
	char szBuff[128];


	szStageFile = lpField->szName;

	if ( lpField==StageField[0] ) return smGameStage[0];
	if ( lpField==StageField[1] ) return smGameStage[1];

	lpstg = new smSTAGE3D;

	// ����Ʈ ����
	lpstg->VectLight.x = smConfig.MapLightVector.x;
	lpstg->VectLight.y = smConfig.MapLightVector.y;
	lpstg->VectLight.z = smConfig.MapLightVector.z;

	lpstg->Bright		= smConfig.MapBright;
	lpstg->Contrast		= smConfig.MapContrast;

	//����� �ε� �Ѵ�
//	smSTAGE3D_ReadASE( szStageFile , lpstg );
//	lpstg->Head = TRUE;

	//����� �� �����忡 ���Ͽ� �ε� �Ѵ�
	AddLoaderStage( lpstg , szStageFile );

	if ( !lpstg->StageObject ) {
		//�˼� ���� ����
		//Ŭ���̾�Ʈ �α� ���� ���
		wsprintf( szBuff , "Stage Loading Error ( %s )",szStageFile );
		Record_ClinetLogFile( szBuff );
		delete lpstg;
		return NULL;
	}

	//���� ������Ʈ �߰�
	for( cnt=0;cnt<lpField->StgObjCount;cnt++ ) {
		Bip = lpField->GetStageObjectName( cnt , szBuff );
		if ( szBuff[0] ) {
			if ( Bip )
				lpstg->StageObject->AddObjectFile( szBuff , szBuff );
			else
				lpstg->StageObject->AddObjectFile( szBuff );
		}
	}

	if ( lpSecondField && lpSecondField==StageField[0] ) {
		if ( smGameStage[1] ) delete smGameStage[1];
		smGameStage[1] = lpstg;
		StageField[1] = lpField;
		//�ʵ�� �ε�
		LoadFieldMap( 1, lpField , lpstg );
	}
	else {
		if ( !lpSecondField || lpSecondField==StageField[1] ) {
			if ( smGameStage[0] ) delete smGameStage[0];
			smGameStage[0] = lpstg;
			StageField[0] = lpField;
			//�ʵ�� �ε�
			LoadFieldMap( 0, lpField , lpstg );
		}
	}

	if ( StageField[0] ) lstrcpy( szGameStageName[0] , StageField[0]->szName );
	if ( StageField[1] ) lstrcpy( szGameStageName[1] , StageField[1]->szName );

	DWORD	dwTime = GetCurrentTime();
	if ( dwLastRecvGameServerTime && dwLastRecvGameServerTime<dwTime ) dwLastRecvGameServerTime=dwTime;
	if ( dwLastRecvGameServerTime2 && dwLastRecvGameServerTime2<dwTime ) dwLastRecvGameServerTime2 = dwTime;
	if ( dwLastRecvGameServerTime3 && dwLastRecvGameServerTime3<dwTime ) dwLastRecvGameServerTime3 = dwTime;
	if ( dwLastRecvGameServerTime4 && dwLastRecvGameServerTime4<dwTime ) dwLastRecvGameServerTime4 = dwTime;

	if ( AreaServerMode ) {
		//���� ���� �����Ȯ�� �ð� ����
		if ( lpWSockServer_Area[0] ) lpWSockServer_Area[0]->dwDeadLockTime = dwTime;
		if ( lpWSockServer_Area[1] ) lpWSockServer_Area[1]->dwDeadLockTime = dwTime;
	}

	return lpstg;
}

//����� �о� �´�
smSTAGE3D *LoadStage( char *szStageFile )
{
	smSTAGE3D *lpstg;

	if ( lstrcmpi( szGameStageName[0] , szStageFile )==0 ) return smGameStage[0];
	if ( lstrcmpi( szGameStageName[1] , szStageFile )==0 ) return smGameStage[1];

	lpstg = new smSTAGE3D;

	// ����Ʈ ����
	lpstg->VectLight.x = smConfig.MapLightVector.x;
	lpstg->VectLight.y = smConfig.MapLightVector.y;
	lpstg->VectLight.z = smConfig.MapLightVector.z;

	lpstg->Bright		= smConfig.MapBright;
	lpstg->Contrast	= smConfig.MapContrast;

	//����� �� �����忡 ���Ͽ� �ε� �Ѵ�
	AddLoaderStage( lpstg , szStageFile );

	smStageCount = (smStageCount+1)&1;

	if ( smGameStage[smStageCount] ) delete smGameStage[smStageCount];

	smGameStage[smStageCount] = lpstg;
	//ReadTextures();
	return lpstg;
}

//����� �о� �´�
smSTAGE3D *LoadStage2( char *szStageFile )
{
	smSTAGE3D *lpstg;

	if ( lstrcmpi( szGameStageName[0] , szStageFile )==0 ) return smGameStage[0];
	if ( lstrcmpi( szGameStageName[1] , szStageFile )==0 ) return smGameStage[1];

	lpstg = new smSTAGE3D;

	// ����Ʈ ����
	lpstg->VectLight.x = smConfig.MapLightVector.x;
	lpstg->VectLight.y = smConfig.MapLightVector.y;
	lpstg->VectLight.z = smConfig.MapLightVector.z;

	lpstg->Bright		= smConfig.MapBright;
	lpstg->Contrast	= smConfig.MapContrast;

	//����� �� �����忡 ���Ͽ� �ε� �Ѵ�
	smSTAGE3D_ReadASE( szStageFile , lpstg );
	lpstg->Head = TRUE;

	smStageCount = (smStageCount+1)&1;

	if ( smGameStage[smStageCount] ) delete smGameStage[smStageCount];

	smGameStage[smStageCount] = lpstg;
	//ReadTextures();
	return lpstg;
}


int PlayCounter = 0;

char PlayerName[64] = { 0,0,0,0 };


void InitStage()
{
//	int cnt;

	szGameStageName[0][0] = 0;
	szGameStageName[1][0] = 0;

/*
	smStage = new smSTAGE3D;

	// ����Ʈ ����
	smStage->VectLight.x = smConfig.MapLightVector.x;
	smStage->VectLight.y = smConfig.MapLightVector.y;
	smStage->VectLight.z = smConfig.MapLightVector.z;

	smStage->Bright		= smConfig.MapBright;
	smStage->Contrast	= smConfig.MapContrast;


//	smStage = smSTAGE3D_ReadASE( smConfig.szFile_Stage  );
	smStage = smSTAGE3D_ReadASE( smConfig.szFile_Stage , smStage );
*/
//	smStage = LoadStage( smConfig.szFile_Stage );
//	smStage = LoadStage( "field\\forest.ASE" );
/*
	smStage = LoadStage( "field\\village.ASE" );
	smStage = LoadStage( "field\\forest(attach).ASE" );
*/
//	smStage = LoadStage2( "field\\village.ASE" );
//	smStage = LoadStage2( smConfig.szFile_Stage  );
//	smStage = LoadStage2( "field\\forest(attach).ASE" );

	//�ʵ� �� �ʱ�ȭ
	InitFieldMap();


	 InitField();

	LoadFieldMap( 0, StageField[0] , smGameStage[0] );

/*
	for( cnt=0;cnt<smConfig.StageObjCnt;cnt++) {
		smStage->StageObject->AddObjectFile( smConfig.szFile_StageObject[cnt] );
	}
*/
}


void CloseStage()
{

	//if( smStage ) delete smStage;

	if ( smGameStage[1] ) delete smGameStage[1];
	if ( smGameStage[0] ) delete smGameStage[0];

}


struct _DRAW_LIGHTLIST {
	smLIGHT3D	*smLight;
	int			x,y,z;
};


_DRAW_LIGHTLIST	DrawLight[64];
_DRAW_LIGHTLIST	DrawLightSmall[64];
int DrawLightCnt;
int DrawLightSmallCnt;


int DrawLightImage(smSTAGE3D* lpStage, int x, int y, int z) { return TRUE; }


int DrawLightImage() { return TRUE; }

int SetStageDynLight(smSTAGE3D *lpStage , int x, int y, int z) { return TRUE; }




int doop = 0;



int DisplayStage(int x , int y, int z, int angX, int angY, int angZ ) { return TRUE; }

//######################################################################################
//�� �� �� : �� �� ��
void CreatePatIceFoot( int Num, int sizeX, int sizeZ ) { }
//######################################################################################

void CreatePatShadow( int Num , int sizeX , int sizeZ ) { }

void CreatePatShadow2(int Num, int sizeX, int sizeZ) {}


//������ ĳ���� ���
int AdminCharMode = 0;
//������ ĳ���� ���� ���濡 ����Ÿ ���� ����
int AdminCharDisable = 0;

//ĳ���� ���� ����Ʈ
static char szDataDirectory[256];
char szCharFileList[256][256];
int CharFileCnt;
int CharPlayCnt = 0;

//���� �̸����� ���� ���丮�� ã�� ����
static char *SetDirectoryFromFile( char *filename )
{
	int len;
	int cnt;

	lstrcpy( szDataDirectory , filename );

	len = lstrlen( szDataDirectory );

	for( cnt=len; cnt>=0 ; cnt-- )
		if ( szDataDirectory[cnt]=='\\' ) break;

	szDataDirectory[cnt+1] = NULL;

	return szDataDirectory;
}


//ĳ���� ���� ����Ʈ ����
int SetCharFileList( char *szCharFile )
{
	CharFileCnt = 0;
	char szFindPath[256];

	SetDirectoryFromFile( szCharFile );

	HANDLE hFindHandle;
	WIN32_FIND_DATA	fd;

	lstrcpy( szFindPath , szDataDirectory );
	lstrcat( szFindPath , "\\*.ini" );

	//������ ã��( Ȯ���� ���� ���� )
	hFindHandle = FindFirstFile( szFindPath , &fd );
	if ( hFindHandle==INVALID_HANDLE_VALUE ) {
		FindClose( hFindHandle );
		return 0;
	}
	while(1) {
		lstrcpy( szCharFileList[CharFileCnt] , szDataDirectory );
		lstrcat( szCharFileList[CharFileCnt] , fd.cFileName );
		CharFileCnt++;

		if ( FindNextFile( hFindHandle , &fd )==FALSE ) break;
		if ( CharFileCnt>255 ) break;
	}
	FindClose( hFindHandle );


	return TRUE;
}

void SetNextPlayerPattern()
{
	if ( lpCurPlayer->PatLoading ) return;

	//������ ĳ���� ���� ���濡 ����Ÿ ���� ����
	AdminCharDisable = TRUE;

	if ( AdminCharMode ) {
		memcpy( &lpCurPlayer->smCharInfo , &smCharInfo_Back , sizeof( smCHAR_INFO ) );
		ReformCharForm();
		AdminCharMode = 0;
		lpCurPlayer->PatLoading = TRUE;
		AddLoaderPattern( lpCurPlayer , lpCurPlayer->smCharInfo.szModelName, lpCurPlayer->smCharInfo.szModelName2 );
		lpCurPlayer->DisplayTools = TRUE;
		return;
	}

	AdminCharMode = 0;
	lpCurPlayer->PatLoading = TRUE;
	AddLoaderPattern( lpCurPlayer , szCharFileList[CharPlayCnt], lpCurPlayer->smCharInfo.szModelName2 );
	lpCurPlayer->DisplayTools = TRUE;

	CharPlayCnt++;
	if ( CharPlayCnt>=CharFileCnt ) CharPlayCnt = 0;
}

void SetPlayerBodyPattern( char *szBodyFile )
{
	char szBuff[256];
	FILE *fp;


	if ( lpCurPlayer->PatLoading ) return;

	wsprintf( szBuff , "char\\tmABCD\\%s.ini" , szBodyFile );
	fp = fopen( szBuff , "rb" );
	if ( !fp ) return;
	fclose(fp);
/*
	//������ ĳ���� ���� ���濡 ����Ÿ ���� ����
	AdminCharDisable = TRUE;
	AdminCharMode = 0;
*/
	lpCurPlayer->PatLoading = TRUE;
	AddLoaderPattern( lpCurPlayer , szBuff , lpCurPlayer->smCharInfo.szModelName2 );
	lpCurPlayer->DisplayTools = TRUE;
}

void SetPlayerPattern( char *szFile )
{
	FILE *fp;


	if ( lpCurPlayer->PatLoading ) return;

	fp = fopen( szFile , "rb" );
	if ( !fp ) return;
	fclose(fp);

	lpCurPlayer->PatLoading = TRUE;
	AddLoaderPattern( lpCurPlayer , szFile , 0 );
	lpCurPlayer->DisplayTools = TRUE;

	ReformCharForm();

	lpCurPlayer->smCharInfo.bUpdateInfo[0]++;
	SendSetObjectSerial( lpCurPlayer->dwObjectSerial ); 

}


char szNpcFileList[64][64];
int NpcFileCnt;
int NpcPlayCnt = 0;

char *NpcSelectedName = 0;

int SetNpcFileList( char *szNpcDirectory )
{
	NpcFileCnt = 0;
	char szFindPath[256];

	HANDLE hFindHandle;
	WIN32_FIND_DATA	fd;

	lstrcpy( szFindPath , szNpcDirectory );
	lstrcat( szFindPath , "*.npc" );

	hFindHandle = FindFirstFile( szFindPath , &fd );
	if ( hFindHandle==INVALID_HANDLE_VALUE ) {
		FindClose( hFindHandle );
		return 0;

	}
	while(1) {
		lstrcpy( szNpcFileList[NpcFileCnt] , szNpcDirectory ); 
		lstrcat( szNpcFileList[NpcFileCnt] , fd.cFileName );
		NpcFileCnt++;

		if ( FindNextFile( hFindHandle , &fd )==FALSE ) break;
		if ( NpcFileCnt>64 ) break;

	}
	FindClose( hFindHandle );

	return TRUE;
}

void SetNextNpcPattern()
{
	if ( lpCurPlayer->PatLoading ) return;

	if ( AdminCharMode==0 ) {
		memcpy( &smCharInfo_Back , &lpCurPlayer->smCharInfo , sizeof( smCHAR_INFO ) );
	}

	//������ ĳ���� ���� ���濡 ����Ÿ ���� ����
	AdminCharDisable = TRUE;

	AdminCharMode = 1;				//NPC ���� ���


	lpCurPlayer->smCharInfo.dwCharSoundCode = 0;

	//ĳ���� ���� ���Ͽ��� �ص��Ͽ� �����Ѵ�
	if ( smCharDecode( szNpcFileList[NpcPlayCnt] , &lpCurPlayer->smCharInfo ,0 ) ) {
		lpCurPlayer->PatLoading = TRUE;
		AddLoaderPattern( lpCurPlayer , lpCurPlayer->smCharInfo.szModelName );

		lpCurPlayer->DisplayTools = FALSE;
		lpCurPlayer->smCharInfo.SizeLevel = 1;

		NpcSelectedName = szNpcFileList[NpcPlayCnt];

		NpcPlayCnt++;
		if ( NpcPlayCnt>=NpcFileCnt ) NpcPlayCnt = 0;
	}
	ReformCharForm();
}

//////////////// ���� ȸ�� �Լ� ////////////////
int LaunchPartyPostion() { return TRUE; }

//���� ȸ�� ����
int SetPartyPosion( smTRANS_COMMAND *lpTransCommand )
{
	if ( dwPartyPosionTime ) {
		//�̹� ������
		LaunchPartyPostion();
	}

	dwPartyPosionTime = dwPlayTime+1000;
	memcpy( &sPartyPosion , lpTransCommand , sizeof(smTRANS_COMMAND) );

	return TRUE;
}



char szPlayerCode[32];
int CharacterJob = 0;			//���� �ڵ� �Ѱ���



extern	char *szNpcInfoPath;

DWORD	dwSoD_ResultTime = 0;		//SoD ��Ȳâ ���� �ð�


sBILLING_INFO	*sBiInfo = 0;


int InitPat3D() { return TRUE; }

int ClosePat3D() { return TRUE; }

int PartCnt = 0;



//int LoadTest = 0;


int		MsTraceCount = 0;
int		MsTraceMode = 0;
RECT	MsSelRect;
POINT	MsSelPos;

int		SelMouseButton =0;			//��� ���õ� ���콺 ��ư

smCHAR	*lpCharSelPlayer = 0;		//���� ĳ����
smCHAR	*lpCharMsTrace = 0;			//�̵� ��ǥ ĳ����

scITEM	*lpSelItem = 0;				//���õ� ������
scITEM	*lpMsTraceItem = 0;			//�̵� ��ǥ ������

int AttFlag = 0;
int	AttCancel;						//���� ���
int	AttAutoCont = 0;				//���� ���� ���

//���� ����
int TraceAttackPlay() { return TRUE; }

//���� ���
int CancelAttack()
{
	SelMouseButton = 0;
	MsTraceMode = FALSE;
	lpCharMsTrace = 0;
	lpMsTraceItem = 0;
	AttFlag = 0;

	return TRUE;
}


//�������� ���� ����ġ ���
int	DamageExp( smCHAR *lpChar , int AttackDamage )
{
	int AttackResult;

//#ifdef _LANGUAGE_CHINESE
//	lpCurPlayer->AttackExp = 0;
//	return TRUE;
//#endif

	//�����⸸ �ص� ����ġ �ö�
	if ( AttackDamage && lpChar->smCharInfo.State==smCHAR_STATE_ENEMY && 
		lpChar->smCharInfo.Brood!=smCHAR_MONSTER_USER && lpChar->smCharInfo.Life[0]>0 ) {

		AttackResult = (AttackDamage<<8)/lpChar->smCharInfo.Life[1];
		if ( AttackResult>256 ) AttackResult=256;
		AttackResult = ( lpChar->smCharInfo.Exp * AttackResult )>>8;
		AttackResult/=10;
		if ( AttackResult<=0 ) AttackResult = 1;
		lpCurPlayer->AttackExp = AttackResult;
	}

	return TRUE;
}


#define AUTO_DEAD_COUNT		(70*60*8)
int AutoDeathCounter = 0;
int FixedWidth = 200;
DWORD	dwClassDelayTime = 0;


//DWORD	dwLastModuleChk = 0;

int PlayPat3D() { return TRUE; }

extern int BGMatNum[2];
extern int RestoreTexFlag;



//���콺�� ���� �÷��̾���� ������ �����ش�
int GetMouseSelAngle( ) { return TRUE; }

//2���� �÷��̾��� ������ �����ش�
int GetCharAngle( smCHAR *lpChar1 , smCHAR *lpChar2 ) { return TRUE; }


int testframe = 0;
int	LastRendSucessCount = 0;			//�ֱ� ������ ������ ĳ���� ��
int	DispCharLimitMode = 0;				//0-��ü ǥ�� 1-�ٹ游 ǥ��

#define	DISP_CHAR_LIMIT			20
#define	DISP_CHAR_LIMIT_MAX		30
#define	DISP_CHAR_NEAR_DIST		( (10*64)*(10*64) )

int DrawPat3D( int x, int y, int z, int ax, int ay, int az ) { return TRUE; }

int DrawPat3D_Alpha() { return TRUE; }

//�׸��� �׸���
int DrawPatShadow(int x, int y, int z, int ax, int ay, int az ) { return TRUE; }

extern BYTE VRKeyBuff[256];

int Draw2DCounter = 0;

int DrawPat2D( int x, int y, int z, int ax, int ay, int az ) { return TRUE; }

extern int ViewPointLen ;
//int ViewPointLen = 28*SizeMAPCELL;
extern DWORD smBackColor;

int BGFace[2][3] = {
	{ 0 ,  1 , 2 },
	{ 1 ,  3 , 2 }
};




smOBJ3D *smBackGround;

void* *BackVideoSurface;
int BackVideoFrame;
int LastFrame ;

int BGMatNum[2];


int InitBackGround() { return TRUE; }

int CloseBackGround() { return TRUE; }


int BgFrame = 0;

int BGMain() { return TRUE; }

int ChangeBG( int BgNum ) { return TRUE; }

int DrawBG( int x, int y, int z, int ax, int ay, int az ) { return TRUE; }

RECT	PartyTradeButtonRect[4] = {
	{	00,0, 20, 20	},	
	{	25,0, 20, 20	},	
	{	50,0, 20, 20	},	
	{	75,0, 20, 20	}	
};

RECT	PartyTradeToolTipRect = { 1,18,70,28 };

POINT	PartyButtonPoint = { -1, -1 };

//��Ƽ �ŷ� ��û ��ư ��ġ�� ����
int GetPartyTradeButtonPos( int x, int y ) { return TRUE; }

//��Ƽ Ʈ���̵� ��û ��Ʈ Ŭ��
int DisplayPartyTradeButton() { return TRUE; }


/////////////////// Ȯ���� ĳ���� //////////////
smCHAR	chrEachPlayer;
smCHAR *chrEachMaster = 0;
int		EachTradeButton = 0;
int		EachTradeButtonMode = 0;
RECT	RectTradeButton;

POINT3D EachCameraPos;
int	DispEachMode = 0;


//BIP�� ��ġ ����Ʈ ��ǥ�� ���Ѵ�
int FindBipPoint( smPAT3D *lpPat , char *szObjNodeName ,int frame, int *nX, int *nY, int *nZ );

//Ȯ�� ĳ���� ����
int OpenEachPlayer( smCHAR *lpChar )
{
	if ( !lpChar || !lpChar->Flag || !lpChar->DisplayFlag ) return FALSE;
	if ( EachTradeButton ) return FALSE;

	memcpy( &chrEachPlayer , lpChar , sizeof( smCHAR ) );
	chrEachPlayer.SetMotionFromCode( CHRMOTION_STATE_STAND );
	chrEachPlayer.ActionPattern = 101;
	chrEachMaster = lpChar;

	chrEachPlayer.Flag = TRUE;

	if ( FindBipPoint( chrEachPlayer.AnimPattern , "Bip01 Head" , chrEachPlayer.frame ,
		&EachCameraPos.x , &EachCameraPos.y, &EachCameraPos.z )==NULL ) {

		EachCameraPos.y = chrEachPlayer.PatHeight-10*fONE;
		EachCameraPos.x = 0;
		EachCameraPos.z = 0;
	}

	//ī�޶� ��ġ ����
	if ( lpChar->smCharInfo.State==smCHAR_STATE_ENEMY || lpChar->smCharInfo.State==smCHAR_STATE_NPC ) {
		EachCameraPos.y += lpChar->smCharInfo.ArrowPosi[0]*fONE;
		EachCameraPos.z += lpChar->smCharInfo.ArrowPosi[1]*fONE;
		//EachCameraPos.y += -8000;//lpChar->smCharInfo.ArrowPosi[0]*fONE;
		//EachCameraPos.z += 8000;//lpChar->smCharInfo.ArrowPosi[1]*fONE;
	}

	return TRUE;
}

//Ȯ�� ĳ���� �ݱ�
int CloseEachPlayer()
{
	chrEachPlayer.Flag = 0;
	chrEachMaster  = 0;
	EachTradeButton = 0;

	return TRUE;
}

//Ȯ�� ĳ���� ����
int EachPlayerMain() { return TRUE; }

int DrawClanMark_EachBox( void* clanMark , int x, int y) { return TRUE; }


//Ȯ�� ĳ���� �׸���
int DrawEachPlayer( float fx , float fy , int SizeMode ) { return TRUE; }








/*
char *szBipName_RightHand = "Bip weapon01";//"Bip01 R Hand";//
	HvRightHand.ObjBip = AnimPat->GetObjectFromName(szBipName_RightHand) ;
//Ư�� ������Ʈ�� Ʈ���� �����Ͽ� �ִϸ��̼� ��Ŵ
int AnimObjectTree( smOBJ3D *tObj , int frame , int ax, int ay, int az )
*/

//BIP�� ��ġ ����Ʈ ��ǥ�� ���Ѵ�
int FindBipPoint( smPAT3D *lpPat , char *szObjNodeName , int frame , int *nX, int *nY, int *nZ )
{

	smOBJ3D	*lpObj;

	lpObj = lpPat->GetObjectFromName(szObjNodeName);
	if ( !lpObj ) return FALSE;


	smMATRIX *mWorld;
	POINT3D angle;

	ZeroMemory( &angle, sizeof( POINT3D ) );
	angle.y = (-angle.y+ANGLE_180)&ANGCLIP;

	mWorld = &lpObj->mWorld;

	AnimObjectTree( lpObj , frame , angle.x , angle.y , angle.z );

	*nX = mWorld->_41;
	*nZ = mWorld->_42;
	*nY = mWorld->_43;

	return TRUE;

}


//Ŭ���̾�Ʈ �α� ���� ���
int Record_ClinetLogFile( char *szMessage )
{
	HANDLE	hFile;
	DWORD	dwAcess;
	DWORD	FileLength;
	SYSTEMTIME	st;
	int len;
	char	szFileName[128];
	char	szBuff[256];

	GetLocalTime( &st );
	wsprintf( szFileName , "game.log" , st.wMonth , st.wDay );

	hFile = CreateFile( "game.log" , GENERIC_WRITE , FILE_SHARE_READ|FILE_SHARE_WRITE, NULL, OPEN_ALWAYS , FILE_ATTRIBUTE_NORMAL , NULL );
	if ( hFile==INVALID_HANDLE_VALUE ) return FALSE;

	wsprintf( szBuff , "%d-%d (%d:%d:%d) - %s" , st.wMonth , st.wDay , st.wHour, st.wMinute , st.wSecond , szMessage );
	len = lstrlen(szBuff);
	if ( szBuff[len-1]!='\n' ) {
		szBuff[len]='\r';
		szBuff[len+1]='\n';
		len +=2;
	}

	FileLength = GetFileSize( hFile , NULL );
	SetFilePointer( hFile , FileLength , NULL , FILE_BEGIN );
	WriteFile( hFile , szBuff , len , &dwAcess , NULL );
	CloseHandle( hFile );

	return TRUE;
}



int ParkPlayInit = 0;		//�ʱ�ȭ �÷�
int ParkPlayMode = 0;		//-�ø����� 0-�Ϲ� +�����ð�(�ִ� 1000)
int ParkPlaying = 0;		//������ �÷�����
RECT ParkPlayRect;

//�÷��̾� �ʱ�ȭ
int Init_ParkPlayer()
{
		return TRUE;
}

//�÷��̾� ���
int Play_ParkPlayer( char *szPath , int x, int y, int w, int h , int PlayMode )
{


	return TRUE;
}

//�÷��̾� ����
int Stop_ParkPlayer()
{


	return TRUE;
}
